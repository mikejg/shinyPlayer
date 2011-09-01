#include "db_amarok_embedded.h"


DB_Amarok_Embedded::DB_Amarok_Embedded(QObject* parent) : Database(parent)
{
}

void DB_Amarok_Embedded::openDataBase()
{
    const QString defaultsFile = getEmbeddedPath() + "/my.cnf";
    const QString databaseDir =  getEmbeddedPath() + "/mysqle";

    char* defaultsLine = qstrdup( QString( "--defaults-file=%1" ).arg( defaultsFile ).toAscii().data() );
    char* databaseLine = qstrdup( QString( "--datadir=%1" ).arg( databaseDir ).toAscii().data() );

    static const int num_elements = 8;
       char **server_options = new char* [ num_elements + 1 ];
       server_options[0] = const_cast<char*>( "amarokmysqld" );
       server_options[1] = defaultsLine;
       server_options[2] = databaseLine;

       // CAUTION: if we ever change the table type we will need to fix a number of MYISAM specific
       // functions, such as FULLTEXT indexing.
       server_options[3] = const_cast<char*>( "--default-table-type=MYISAM" );
       server_options[4] = const_cast<char*>( "--default-storage-engine=MYISAM" );
       server_options[5] = const_cast<char*>( "--loose-skip-innodb" );
       server_options[6] = const_cast<char*>( "--skip-grant-tables" );
       server_options[7] = const_cast<char*>( "--myisam-recover=FORCE" );
       server_options[num_elements] = 0;

       char **server_groups = new char* [ 3 ];
       server_groups[0] = const_cast<char*>( "amarokserver" );
       server_groups[1] = const_cast<char*>( "amarokclient" );
       server_groups[2] = 0;

   if( mysql_server_init(num_elements, server_options, server_groups) != 0 )
       {
         qDebug("mysql_library_init fault");
       }

    mysql = mysql_init( NULL );

    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "amarokclient");
    mysql_options(mysql, MYSQL_OPT_USE_EMBEDDED_CONNECTION, NULL);
    mysql_real_connect(mysql, NULL,NULL,NULL, "amarok", 0,NULL,0);
}

QStringList DB_Amarok_Embedded::getInterpreten(QString s)
{
    /*Liefert eine Liste mit allen Interpreten mit dem Anfangsbuchstaben*/

    QString inter;
    QStringList stringListInterpret;
    QString queryString = "SELECT name FROM artists WHERE name LIKE '" + s + "%'";
    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);
    while((record = mysql_fetch_row(results)))
         {
            stringListInterpret << record[0];
            inter = record[0];
         }

    mysql_free_result(results);
    return stringListInterpret;
}
