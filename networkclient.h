#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QtNetwork>

class NetworkClient : public QObject
{
    Q_OBJECT
public:
    explicit NetworkClient(QObject *parent = 0);

signals:

public slots:

private:
    QTcpSocket * sock;

};

#endif // NETWORKCLIENT_H
