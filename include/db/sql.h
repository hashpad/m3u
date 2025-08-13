#pragma once
#include <qsqldatabase.h>

#include <QSqlDatabase>

struct Channel {
    QString tvgId, tvgName, displayName, url;
    int groupId;
};

class DatabaseManager {
   public:
    DatabaseManager(const QString& path);
    bool addChannel(const Channel& channel);
    bool addGroup(const QString& groupName);

    QList<Channel> getChannels();
    QList<Channel> getChannels(int groupId);
    QList<Channel> getChannels(const QString& groupName);

    int getGroupId(const QString& groupName);

   private:
    QSqlDatabase m_db;
};
