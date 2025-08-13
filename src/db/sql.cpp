#include "db/sql.h"

#include <qlogging.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>

#include <QSqlError>
#include <QSqlRecord>

DatabaseManager::DatabaseManager(const QString& path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if (m_db.open()) {
        //
    }
}

bool DatabaseManager::addChannel(const Channel& channel) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO channels(tvg_id, tvg_name, group_id, display_name, url) "
        "VALUES(:tvg_id, :tvg_name, :group_id, :display_name, :url)");

    query.bindValue(":tvg_id", channel.tvgId);
    query.bindValue(":tvg_name", channel.tvgName);
    query.bindValue(":group_id", channel.groupId);
    query.bindValue(":display_name", channel.displayName);
    query.bindValue(":url", channel.url);
    bool success = query.exec();
    if (!success) {
        qDebug() << "Add Channel resulted in an error: " << query.lastError();
    }

    return true;
}

bool DatabaseManager::addGroup(const QString& groupName) {
    if (getGroupId(groupName) != -1) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO groups(name) VALUES(:name)");
    query.bindValue(":name", groupName);
    bool success = query.exec();
    if (!success)
        qDebug() << "Add Group resulted in an error: " << query.lastError();

    return success;
};

int DatabaseManager::getGroupId(const QString& groupName) {
    QSqlQuery query;
    query.prepare("SELECT id FROM groups WHERE name = (:name)");
    query.bindValue(":name", groupName);
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

QList<Channel> DatabaseManager::getChannels() { return getChannels(-1); }

QList<Channel> DatabaseManager::getChannels(int groupId) {
    QList<Channel> channels;
    QSqlQuery query;
    QString queryStr = "SELECT * FROM channels";
    if (groupId >= 0) {
        queryStr.append(" WHERE group_id = (:group_id)");
    }
    query.prepare(queryStr);
    query.bindValue(":group_id", groupId);
    int tvgIdIdx = query.record().indexOf("tvg_id");
    int tvgNameIdx = query.record().indexOf("tvg_name");
    int displayNameIdx = query.record().indexOf("display_name");
    int urlIdx = query.record().indexOf("url");
    while (query.next()) {
        Channel channel;
        channel.tvgId = query.value(tvgIdIdx).toString();
        channel.tvgName = query.value(tvgNameIdx).toString();
        channel.displayName = query.value(displayNameIdx).toString();
        channel.url = query.value(urlIdx).toString();
        channels.append(channel);
    }
    return channels;
}

QList<Channel> DatabaseManager::getChannels(const QString& groupName) {
    int groupId = getGroupId(groupName);
    return getChannels(groupId);
}
