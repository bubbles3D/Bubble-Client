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

    connect(sock, SIGNAL(connected()), this, SLOT(init()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(processIncommingData()));
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

void NetworkClient::modifications(QList<QPair<QString, bool> > keys)
{
    QVariantMap map;
    QVariantList list;

    for(int i = 0; i < keys.size(); ++i)
    {
        QPair<QString, bool> pair = keys.at(i);
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
//    QList<QPair<QString, bool> > list;
//    QPair<QString, bool> pair("UP", true);
//    list.append(pair);
//    qDebug() << "Sending list";
//    this->modifications(list);
}
