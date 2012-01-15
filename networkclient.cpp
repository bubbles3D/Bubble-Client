#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>

#include "networkclient.h"
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

void NetworkClient::init()
{
    sock->write("init naruto$$");
}

void NetworkClient::processIncommingData()
{
    QByteArray mess = sock->readAll();

    qDebug("Total json string %s", QString(mess).toStdString().c_str());

    QString str(mess);

    str.remove("$$");

    //if (mess[mess.size()] == '$')
    QScriptValue sc;
    QScriptEngine engine;

    sc = engine.evaluate("(" + str + ")");

    qDebug("evaluated crap : %s", sc.toString().toStdString().c_str());

    if (sc.property("players").isArray())
    {
        QScriptValueIterator it(sc.property("players"));
        while (it.hasNext()) {
            it.next();
            Player p(it.value().property("name").toString(),
                     it.value().property("x").toInt32(),
                     it.value().property("y").toInt32(),
                     it.value().property("z").toInt32());
            qDebug("%s", p.toString().toStdString().c_str());
        }
    }
}
