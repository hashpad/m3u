#include "M3UUtils.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QVector>
#include <QTextStream>
#include <QtDebug>


void downloadM3U(const QUrl url, QObject *context, std::function<void(const QVector<M3UEntry>&)> callback) {
    auto *nam = new QNetworkAccessManager(context);
    QNetworkRequest request(url);
    auto* reply = nam->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, callback](){
        QVector<M3UEntry> entries;
        if (reply->error() == QNetworkReply::NoError){
            QByteArray data(reply->readAll());
            QString text(QString::fromUtf8(data));
            entries = parseM3U(text);
        } 
        callback(entries);

        reply->deleteLater();
    });
}

QVector<M3UEntry> parseM3U(const QString &text) {
    QVector<M3UEntry> entries;
    qInfo() << text;
    return entries;
}
