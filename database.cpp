#include "database.h"

Database::Database(QObject* parent) : QObject(parent)
{
}

QPixmap Database::getCover(QString i, QString a)
{
    Q_UNUSED (i);
    Q_UNUSED (a);
    return QPixmap();
}

QString Database::getStringFromQuery(QString queryString)
{
    Q_UNUSED (queryString);
    return QString();
}

QStringList Database::getStringListFromQuery(QString queryString)
{
    /*Die Funktion ist virtual und hat einen Rückgabewert. Wenn ich
      nichts mache gibts böse warnungen. Sieht nicht gut aus.*/

    Q_UNUSED (queryString);
    QStringList tmp;
    return tmp;
}
