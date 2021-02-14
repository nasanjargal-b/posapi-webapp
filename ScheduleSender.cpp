//
// Created by nasanjargal on 2021.02.14.
//

#include "ScheduleSender.h"
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

int scheduledTime = 0;

ScheduleSender::ScheduleSender(PosController *posController) : QObject(posController), posController(posController) {
    scheduledTime = QDateTime::currentDateTime().toString("hh").toInt();
    connect(&timer, &QTimer::timeout, this, &ScheduleSender::sendData, Qt::QueuedConnection);
    timer.start(1000);
}

void ScheduleSender::sendData() {
    const QDateTime &time = QDateTime::currentDateTime();
    if (scheduledTime == time.toString("hh").toInt()) {
        scheduledTime = time.addSecs(3600).toString("hh").toInt();
        qDebug() << "Next send time: " << scheduledTime;
        posController->sendData();
        qInfo() << "Авто sendData ажилласан.";
    }
}
