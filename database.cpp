#include "database.h"

Database::Database(QObject* parent) : QObject(parent)
{
}

QStringList Database::getInterpreten(QString s)
{
    /*Die Funktion ist virtual und hat einen Rückgabewert. Wenn ich
      nichts mache gibts böse warnungen. Sieht nicht gut aus.*/

    Q_UNUSED (s);
    QStringList tmp;
    return tmp;
}
