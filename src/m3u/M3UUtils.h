#pragma once

#include <QString>
#include <QUrl>
#include <QMap>

struct M3UEntry {
    QString url;
    QString name;
    QMap<QString, QString> attributes;
};

void downloadM3U(const QUrl url, QObject *context, std::function<void(const QVector<M3UEntry>&)> callback);

QVector<M3UEntry> parseM3U(const QString &text);