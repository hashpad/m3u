#pragma once

#include <QMap>
#include <QString>
#include <QUrl>

struct M3UEntry {
    QString url;
    QString name;
    QMap<QString, QString> attributes;
};

QList<QString> getUniqueGroups(const QList<M3UEntry> &entries);
void downloadM3U(const QUrl url, QObject *context,
                 std::function<void(const QList<M3UEntry> &)> callback);

QList<M3UEntry> parseM3U(QString text);
