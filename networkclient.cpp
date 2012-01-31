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
    connect(m, SIGNAL(keyChanged(QString,bool)), this, SLOT(sendKeyState(QString,bool)));
    connect(m, SIGNAL(keyChanged(QString,bool)), this, SLOT(sendMouseState(QString,float, float, float)));
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
        QVariantMap v;
        v.insert("name", pair.first);
        v.insert("state", pair.second);
        list.append(v);
    }
    map.insert("modifications", list);

    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(map);

    qDebug() << "Sent " << json;

    sock->flush();
    sock->write(json+"$$");
}

void NetworkClient::processIncommingData()
{
    QByteArray mess = sock->readAll();

    qDebug() << "Received " <<  mess;

    QString str(mess);

    str.remove("$$");

    Model * m = Model::getInstance();
    m->setUpdatedPlayers(str);
}

void NetworkClient::sendKeyState(QString name, bool state)
{
    qDebug() << "In sendKeyState Slot";
    QList<QPair<QString, QVariant> > list;
    QPair<QString, QVariant> pair(name, state);
    list.append(pair);
    modifications(list);
}

void NetworkClient::sendMouseState(float x, float y, float z)
{
    qDebug() << "In sendMouseState Slot";
    QList<QPair<QString, QVariant> > list;
    QVariantMap obj;
    obj["x"] = x;
    obj["y"] = y;
    obj["z"] = z;
    QPair<QString, QVariant> pair("MOUSE", obj);
    list.append(pair);
    modifications(list);
}
