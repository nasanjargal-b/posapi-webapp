//
// Created by nasanjargal on 2021.02.13.
//

#include "PosController.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "PosAPI.h"

using namespace vatps;

QHttpServerResponse convertResponse(QJsonObject object) {
    if (object.contains("success")) {
        if (!object["success"].toBool()) {
            return QHttpServerResponse("application/json", QJsonDocument(object).toJson(), QHttpServerResponse::StatusCode::InternalServerError);
        }
    }
    return QHttpServerResponse(object);
}

PosController::PosController(QHttpServer *httpServer) : QObject(httpServer), httpServer(httpServer) {
    init();
}

void PosController::init() {

    httpServer->route("/checkApi", QHttpServerRequest::Method::GET, [this](const QHttpServerRequest &request) {
        return convertResponse(checkApi());
    });
    httpServer->route("/getInformation", QHttpServerRequest::Method::GET, [this](const QHttpServerRequest &request) {
        return convertResponse(getInformation());
    });

    httpServer->route("/callFunction/<arg>", QHttpServerRequest::Method::POST, [this](QString funcName, const QHttpServerRequest &request) {
        return convertResponse(callFunction(funcName.toUtf8(), request.body()));
    });

    httpServer->route("/put", QHttpServerRequest::Method::POST, [this](const QHttpServerRequest &request) {
        return convertResponse(put(request.body()));
    });

    httpServer->route("/returnBill", QHttpServerRequest::Method::POST, [this](const QHttpServerRequest &request) {
        return convertResponse(returnBill(request.body()));
    });

    httpServer->route("/sendData", QHttpServerRequest::Method::GET, [this](const QHttpServerRequest &request) {
        return convertResponse(sendData());
    });
}

QJsonObject PosController::checkApi() {
    QMutexLocker locker(&reqLock);
    const QJsonDocument &document = QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::checkApi()));
    return document.object();
}

QJsonObject PosController::getInformation() {
    QMutexLocker locker(&reqLock);
    const QJsonDocument &document = QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::getInformation()));
    return document.object();
}

QJsonObject PosController::callFunction(QByteArray funcName, QByteArray param) {
    QMutexLocker locker(&reqLock);
    const QJsonDocument &document = QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::callFunction(funcName.toStdString(), param.toStdString())));
    return document.object();
}

QJsonObject PosController::put(QByteArray param) {
    QMutexLocker locker(&reqLock);
    const QJsonDocument &document = QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::put(param.toStdString())));
    QJsonObject object = document.object();

    /**
     * Төлбөрийн баримтын журамд заагдсаны дагуу хадгалагдах ёсгүй мэдээллүүдийг масклаж өөрчлөнө.
     * 1. lottery
     * 2. qrData
     */
    if (object.contains("lottery")) {
        QString lottery = object["lottery"].toString().replace(QRegExp("[a-zA-Z0-9]"), "*");
        object["lottery"] = lottery;
    }
    if (object.contains("qrData")) object["qrData"] = "QR DATA";

    qInfo() << "put: " << QString::fromUtf8(QJsonDocument(object).toJson());
    return document.object();
}

QJsonObject PosController::returnBill(QByteArray param) {
    QMutexLocker locker(&reqLock);
    const QJsonDocument &document = QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::returnBill(param.toStdString())));
    qInfo() << "returnBill: " << QString::fromUtf8(document.toJson());
    return document.object();
}

QJsonObject PosController::sendData() {
    QMutexLocker locker(&reqLock);
    const QJsonDocument &document = QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::sendData()));
    qInfo() << "sendData: " << QString::fromUtf8(document.toJson());
    return document.object();
}
