//
// Created by nasanjargal on 2021.02.13.
//

#ifndef POSAPI_POSCONTROLLER_H
#define POSAPI_POSCONTROLLER_H


#include <QHttpServer>

class PosController : public QObject {
Q_OBJECT
private:
    QHttpServer *httpServer;
public:
    PosController(QHttpServer *httpServer);

    QJsonObject sendData();
private:
    void init();

    QJsonObject checkApi();

    QJsonObject getInformation();

    QJsonObject callFunction(QByteArray funcName, QByteArray param);

    QJsonObject put(QByteArray param);

    QJsonObject returnBill(QByteArray param);
};


#endif //POSAPI_POSCONTROLLER_H
