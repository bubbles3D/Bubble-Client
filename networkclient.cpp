#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>

#include <qjson/serializer.h>

#include "networkclient.h"
#include "model.h"
#include "player.h"

NetworkClient::NetworkClient(QObject *parent) :
    QObject(parent)
{
    sock = new QTcpSocket(this);
    Model * m = Model::getInstance();

    connect(sock, SIGNAL(connected()), this, SLOT(init()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(processIncommingData()));
    connect(m, SIGNAL(keys(QList<QPair<QString,QVariant> >)), this, SLOT(modifications(QList<QPair<QString,QVariant> >)));

}

void NetworkClient::startOn(QString host, qint16 port)
{
    sock->connectToHost(host, port);
}

void NetworkClient::setName(QString name)
{
    this->name = name;
}

void NetworkClient::init()
{
    sock->write("init "+name.toAscii()+"$$");
}

void NetworkClient::modifications(QList<QPair<QString, QVariant> > keys)
{
    QVariantMap map;
    QVariantList list;

    for(int i = 0; i < keys.size(); ++i)
    {
        QPair<QString, QVariant> pair = keys.at(i);
        qDebug() << pair;
        QVariantMap v;
        v.insert("name", pair.first);
        v.insert("state", pair.second);
        list.append(v);
    }
    map.insert("modifications", list);

    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(map);

    qDebug() << json;

    sock->write(json+"$$");
}

void NetworkClient::processIncommingData()
{
    QByteArray mess = sock->readAll();

    qDebug("Total json string %s", QString(mess).toStdString().c_str());

    QString str(mess);

    str.remove("$$");

    Model * m = Model::getInstance();
    m->setUpdatedPlayers(str);

    //DEBUG
    QList<QPair<QString, QVariant> > list;
    QVariantMap point;
    point.insert("x", 10);
    point.insert("y", 10);
    point.insert("z", -10);
    QPair<QString, QVariant> pair("MOUSE", point);
    list.append(pair);

    QPair<QString, QVariant> pair2("UP", true);
    list.append(pair2);

    qDebug() << "Sending list";
    this->modifications(list);
}
