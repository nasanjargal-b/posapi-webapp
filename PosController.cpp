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
    return QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::checkApi())).object();
}

QJsonObject PosController::getInformation() {
    return QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::getInformation())).object();
}

QJsonObject PosController::callFunction(QByteArray funcName, QByteArray param) {
    return QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::callFunction(funcName.toStdString(), param.toStdString()))).object();
}

QJsonObject PosController::put(QByteArray param) {
    return QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::put(param.toStdString()))).object();
}

QJsonObject PosController::returnBill(QByteArray param) {
    return QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::returnBill(param.toStdString()))).object();
}

QJsonObject PosController::sendData() {
    return QJsonDocument::fromJson(QByteArray::fromStdString(PosAPI::sendData())).object();
}
