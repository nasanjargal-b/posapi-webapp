//
// Created by nasanjargal on 2021.02.14.
//

#ifndef POSAPI_SCHEDULESENDER_H
#define POSAPI_SCHEDULESENDER_H

#include <QObject>
#include <QTimer>
#include "PosController.h"

class ScheduleSender : public QObject {
Q_OBJECT
private:
    QTimer timer;
    PosController *posController;
public:
    ScheduleSender(PosController *posController);

public slots:

    void sendData();
};


#endif //POSAPI_SCHEDULESENDER_H
