#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QHttpServer>
#include <QJsonObject>
#include "PosController.h"

QString searchConfigFile() {
    QString binDir = QCoreApplication::applicationDirPath();
    QString appName = QCoreApplication::applicationName();
    QFile file;
    file.setFileName(binDir + "/webapp.ini");
    if (!file.exists()) {
        file.setFileName("webapp.ini");
        if (!file.exists()) {
            file.setFileName("/etc/posapi/webapp.ini");
        }
    }
    if (file.exists()) {
        QString configFileName = QDir(file.fileName()).canonicalPath();
        qDebug("using config file %s", qPrintable(configFileName));
        return configFileName;
    } else {
        qFatal("config file not found");
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QSettings settings(searchConfigFile(), QSettings::IniFormat);

    QHttpServer httpServer;
    httpServer.route("/", []() {
        return "PosAPI Web application is started.";
    });

    PosController controller(&httpServer);

    const QHostAddress &address = QHostAddress(settings.value("host").toString());
    int port = settings.value("port").toInt();
    port = httpServer.listen(
            address,
            port);
    if (!port) {
        qCritical() << "Server failed to listen on a port.";
        return 0;
    }

    return QCoreApplication::exec();
}
