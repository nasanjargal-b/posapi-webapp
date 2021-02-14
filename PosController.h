//
// Created by nasanjargal on 2021.02.13.
//

#ifndef POSAPI_POSCONTROLLER_H
#define POSAPI_POSCONTROLLER_H


#include <QHttpServer>
#include <QMutex>

class ScheduleSender;

class PosController : public QObject {
    friend class ScheduleSender;

Q_OBJECT
private:
    QHttpServer *httpServer;
    QMutex reqLock;
public:
    PosController(QHttpServer *httpServer);

private:
    void init();

    QJsonObject checkApi();

    QJsonObject getInformation();

    QJsonObject callFunction(QByteArray funcName, QByteArray param);

    QJsonObject put(QByteArray param);

    QJsonObject returnBill(QByteArray param);

    QJsonObject sendData();
};


#endif //POSAPI_POSCONTROLLER_H
