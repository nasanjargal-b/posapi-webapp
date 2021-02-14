//
// Created by nasanjargal on 2021.02.14.
//

#include "Logger.h"
#include <QtCore>

QMutex logMutex;


void logMessageHandler(QtMsgType type, const QMessageLogContext &ctx, const QString &msgRaw) {
    QMutexLocker locker(&logMutex);

    QString msg = QString::fromUtf8(msgRaw.toStdString().data());
    QFile logFile(QString("%1/posapi-%2.log").arg(QCoreApplication::applicationDirPath(),QDate::currentDate().toString("yyyyMMdd")));
    logFile.open(QIODevice::Append | QIODevice::Text);
    QTextStream logOut(&logFile);
    logOut.setCodec("UTF-8");
    QTextStream conOut(stdout);
    conOut.setCodec("UTF-8");

    const char *file = ctx.file ? ctx.file : "";
    const char *function = ctx.function ? ctx.function : "";
    const char *date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toUtf8().data();
    switch (type) {
        case QtInfoMsg:
            logOut << QString().sprintf("%s  Info   : %s", date, msg.toUtf8().data()) << endl;
            conOut << QString().sprintf("%s  Info   : %s (%s:%u, %s)", date, msg.toUtf8().data(), file, ctx.line, function) << endl;
            break;
        case QtDebugMsg:
#ifdef QT_DEBUG
            logOut << QString().sprintf("%s  Debug  : %s", date, msg.toUtf8().data()) << endl;
            conOut << QString().sprintf("%s  Debug  : %s (%s:%u, %s)", date, msg.toUtf8().data(), file, ctx.line, function) << endl;
#endif
            break;
        case QtWarningMsg:
            logOut << QString().sprintf("%s  Warning: %s", date, msg.toUtf8().data()) << endl;
            conOut << QString().sprintf("%s  Warning: %s (%s:%u, %s)", date, msg.toUtf8().data(), file, ctx.line, function) << endl;
            break;
        case QtCriticalMsg:
        case QtFatalMsg:
            logOut << QString().sprintf("%s  Error  : %s", date, msg.toUtf8().data()) << endl;
            conOut << QString().sprintf("%s  Error  : %s (%s:%u, %s)", date, msg.toUtf8().data(), file, ctx.line, function) << endl;
            break;
    }
}

void setLogger() {
    qInstallMessageHandler(logMessageHandler);
}
