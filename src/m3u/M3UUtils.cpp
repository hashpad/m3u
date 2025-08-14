#include "m3u/M3UUtils.h"

#include <qcontainerfwd.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qregularexpression.h>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextStream>
#include <QtDebug>

QList<QString> getUniqueGroups(const QList<M3UEntry> &entries) {
    QSet<QString> uniqueGroups;
    for (const auto &entry : entries) {
        uniqueGroups.insert(entry.attributes["group-title"]);
    }
    return QList<QString>(uniqueGroups.begin(), uniqueGroups.end());
}

void downloadM3U(const QUrl url, QObject *context,
                 std::function<void(const QList<M3UEntry> &)> callback) {
    auto *nam = new QNetworkAccessManager(context);
    QNetworkRequest request(url);
    auto *reply = nam->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, callback]() {
        QList<M3UEntry> entries;
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data(reply->readAll());
            QString text(QString::fromUtf8(data));
            entries = parseM3U(text);
        }
        callback(entries);

        reply->deleteLater();
    });
}
static QString sanitize(QString input) { return input.remove('\r').trimmed(); }

static QString getM3UInfo(const QString &entryString, const QString &info) {
    QRegularExpression infoRe(".* " + info + "=\\\"([^\\\"]+)");
    auto infoReMatch = infoRe.match(entryString);
    if (infoReMatch.hasMatch()) {
        return sanitize(infoReMatch.captured(1));
    }
    return "";
}

static QString get(const QString &regex, const QString &entryString) {
    QRegularExpression re(regex);
    auto reMatch = re.match(entryString);
    if (reMatch.hasMatch()) {
        return sanitize(reMatch.captured(1));
    }
    return "";
}

static QString getName(const QString &entryString) {
    return sanitize(get(".*,(.*)", entryString));
}

static QString getUrl(const QString &entryString) {
    return sanitize(get(".*\n(.*)", entryString));
}

QList<M3UEntry> parseM3U(QString rawM3U) {
    QList<M3UEntry> entries;
    rawM3U = rawM3U.remove("#EXTM3U\r\n");
    QStringList entryStrings = rawM3U.split("#EXTINF:-1", Qt::SkipEmptyParts);

    for (const QString &entryString : entryStrings) {
        auto entry = M3UEntry();
        QMap<QString, QString> attributes;
        attributes.insert("tvg-name", getM3UInfo(entryString, "tvg-name"));
        attributes.insert("tvg-id", getM3UInfo(entryString, "tvg-id"));
        attributes.insert("group-title",
                          getM3UInfo(entryString, "group-title"));
        entry.attributes = attributes;
        entry.name = getName(entryString);
        entry.url = getUrl(entryString);

        entries.append(entry);
    }
    return entries;
}
