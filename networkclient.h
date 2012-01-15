#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QtNetwork>

class NetworkClient : public QObject
{
    Q_OBJECT
public:
    explicit NetworkClient(QObject *parent = 0);
    void startOn(QString host, qint16 port);

signals:

public slots:
    void init();
    void processIncommingData();

private:
    QTcpSocket * sock;

};

#endif // NETWORKCLIENT_H
