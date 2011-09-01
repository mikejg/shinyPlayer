/*DB_Amarok_Embedded stellt alle Funktionen zur Verfügung
  die man braucht um auf eine Amarok Datenbank zuzugreifen.
  Amarok verwaltet seine Daten in einer sql-embedded Datenbank*/


#ifndef DB_AMAROK_EMBEDDED_H
#define DB_AMAROK_EMBEDDED_H

#include "database.h"
#include "mysql.h"

#include <QString>
#include <QDir>

class DB_Amarok_Embedded : public Database
{
    Q_OBJECT

private:
    MYSQL *mysql;
    MYSQL_RES *results;
    MYSQL_ROW record;
public:
    DB_Amarok_Embedded(QObject* parent);

    QStringList getInterpreten(QString s);
    void openDataBase();


};

#endif // DB_AMAROK_EMBEDDED_H
