#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include "database.h"

struct Settings
{
    bool embeddedSql;
    QString embeddedPath;

    Database* db;
};

#endif // SETTINGS_H
