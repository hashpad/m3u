#pragma once

#include "db/sql.h"

struct AppContext {
    explicit AppContext(const QString& path) : dbManager(path) {};
    DatabaseManager dbManager;
};
