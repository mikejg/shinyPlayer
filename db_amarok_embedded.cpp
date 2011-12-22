#include "db_amarok_embedded.h"
#include "QDateTime"

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


QString DB_Amarok_Embedded::fetchCover(QString uuid)
{
    qDebug() << QString( "--- ") << Q_FUNC_INFO << QString(" ---");

    QString path;
    QString queryString;
    QString purUuid = uuid;
    purUuid.remove("amarok-sqltrackuid://");

    QFile existFile(QDir::homePath() + "/.kde/share/apps/amarok/albumcovers/" + purUuid);
    if(existFile.exists())
    {
        qDebug("Cover exist");
        return QString(QDir::homePath() + "/.kde/share/apps/amarok/albumcovers/" + purUuid);
    }

    queryString = "SELECT devices.lastmountpoint, rpath, uniqueid FROM urls "
                  "INNER JOIN devices on urls.deviceid = devices.id "
                  "WHERE "
                    "urls.uniqueid = '" + uuid + "' ";

    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);
    while((record = mysql_fetch_row(results)))
    {
        path = record[0] + QString("/") + record[1];
    }
    mysql_free_result(results);

    QFile testFile(path);
    qDebug() << QString("path from database: ") << path;

    if(testFile.exists())
    {
        qDebug("File exist");

        QByteArray fileName = QFile::encodeName( path );
        const char *encodedName = fileName.constData();
        TagLib::MPEG::File mpegFile(encodedName);
        TagLib::ID3v2::Tag* tag = mpegFile.ID3v2Tag();

        QImage image;
        TagLib::ID3v2::FrameList l = tag->frameList("APIC");
        if(!l.isEmpty())
        {
           TagLib::ID3v2::AttachedPictureFrame *f =
           static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());
           image.loadFromData((const uchar *) f->picture().data(), f->picture().size());
           QString fileName = QDir::homePath() + "/.kde/share/apps/amarok/albumcovers/" + purUuid;
           image.save(fileName, "PNG");
           return fileName;
        }

    }
    return QString(":/images/noCover.png");
}

QStringList DB_Amarok_Embedded::getAlbenFromInterpret(QString s)
{
    s = s.replace("'", "''");
    QString queryString = "SELECT DISTINCT albums.name FROM tracks, albums, artists WHERE "
                  "tracks.album = albums.id AND tracks.artist = artists.id "
                  "AND artists.name = '" + s + "'";

     return getStringListFromQuery(queryString);
}

QPixmap DB_Amarok_Embedded::getCover(QString i, QString a)
{
    i = i.replace("'", "''");
    a = a.replace("'", "''");
    QPixmap pm;
    QString queryString = "SELECT images.path FROM albums "
                          "INNER JOIN artists ON albums.artist = artists.id "
                          "INNER JOIN images ON albums.image = images.id "
                          "WHERE "
                          "artists.name = '" + i + "' "
                          "AND "
                          "albums.name = '" + a + "' ";
    QString imagePath = getStringFromQuery(queryString);

    if(imagePath.startsWith(QString("amarok-sqltrackuid")))
    {
        imagePath = fetchCover(imagePath);
    }

    if(imagePath.isEmpty())
        pm.load(":/images/noCover.png");
    else
        pm.load(imagePath);

    return pm;
}

QStringList DB_Amarok_Embedded::getPlaylist()
{
    QString queryString = "SELECT name FROM playlists";
    return getStringListFromQuery(queryString);
}

QStringList DB_Amarok_Embedded::getSampler()
{
    QString queryString = "SELECT name from albums where albums.artist is NULL ";
    return getStringListFromQuery(queryString);
}

QStringList DB_Amarok_Embedded::getInterpreten(QString s)
{
    s = s.replace("'", "''");
    QString queryString = "SELECT name FROM artists WHERE name LIKE '" + s + "%'";
    return getStringListFromQuery(queryString);
}

QString DB_Amarok_Embedded::getStringFromQuery(QString queryString)
{
    QString returnString;
    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);

    if(results && (record = mysql_fetch_row(results)))
    {
        returnString = record[0];
    }
    mysql_free_result(results);

    return returnString;
}

QStringList DB_Amarok_Embedded::getStringListFromQuery(QString queryString)
{
    /*Liefert eine Liste aller Treffer aus der Datenbankanfrage in queryString
      Siehe auch get Interpret(QString s)*/

    QStringList stringListResults;
    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);
    while((record = mysql_fetch_row(results)))
         {
            stringListResults << record[0];
         }

    mysql_free_result(results);
    return stringListResults;
}

QList<MetaPaket> DB_Amarok_Embedded::getTracksFromAlbum(QString interpret, QString album)
{
    interpret = interpret.replace("'", "''");
    album = album.replace("'", "''");

    QList<MetaPaket> list;
    MetaPaket metaPaket;
    QString coverUrl;

    QString queryString = "SELECT images.path FROM albums "
                          "INNER JOIN artists ON albums.artist = artists.id "
                          "INNER JOIN images ON albums.image = images.id "
                          "WHERE "
                          "artists.name = '" + interpret + "' "
                          "AND "
                          "albums.name = '" + album + "' ";

    coverUrl = getStringFromQuery(queryString);
    if(coverUrl.startsWith(QString("amarok-sqltrackuid")))
    {
        coverUrl = fetchCover(coverUrl);
    }

    if (coverUrl.isEmpty())
        coverUrl = QString(":/images/noCover.png");

    queryString = "SELECT tracknumber, title, artists.name, albums.name, urls.rpath, devices.lastmountpoint, statistics.rating, statistics.url "
            "FROM tracks "
            "INNER JOIN artists ON tracks.artist = artists.id "
            "INNER JOIN albums ON tracks.album = albums.id "
            "INNER JOIN urls ON tracks.url = urls.id "
            "INNER JOIN devices on urls.deviceid = devices.id "
            "INNER JOIN statistics ON tracks.url = statistics.url "
            "WHERE "
            "artists.name = '" + interpret + "' "
            "AND albums.name = '" + album + "' "
            "ORDER BY tracknumber, title";
        const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
        mysql_query(mysql, query);
        results = mysql_store_result(mysql);
        while((record = mysql_fetch_row(results)))
             {
               metaPaket.isEmpty = false;
               metaPaket.url = QString(record[5]) + QString("/") + QString(record[4]);
               metaPaket.title = record[1];
               metaPaket.interpret = interpret;
               metaPaket.album = album;
               metaPaket.coverUrl = coverUrl;
               metaPaket.points = QString(record[6]).toInt();
               metaPaket.urlkey = QString(record[7]).toInt();
               list.append(metaPaket);
               qDebug() << metaPaket.title;
               qDebug() << QString("Points: ") << metaPaket.points;
             }
        mysql_free_result(results);
        return list;
}

QList<MetaPaket> DB_Amarok_Embedded::getTracksFromPlaylist(QString playlist)
{
    QList<MetaPaket> list;
    MetaPaket metaPaket;
    QString coverUrl;

    QString queryString = "SELECT urls.rpath, devices.lastmountpoint, title, artist, album, playlists.name, statistics.rating, statistics.url FROM playlist_tracks "
                          "INNER JOIN playlists ON playlist_tracks.playlist_id = playlists.id "
                          "INNER JOIN urls ON playlist_tracks.url = urls.uniqueid "
                          "INNER JOIN devices on urls.deviceid = devices.id "
                          "INNER JOIN statistics ON urls.id = statistics.url "
                          "WHERE playlists.name = '" + playlist + "' "
                          "ORDER BY artist, album;";

    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);
    while((record = mysql_fetch_row(results)))
    {
        metaPaket.isEmpty = false;
        metaPaket.url = QString(record[1]) + QString("/") + record[0];
        metaPaket.title = record[2];
        metaPaket.interpret = record[3];
        metaPaket.album = record[4];
        metaPaket.coverUrl = coverUrl;
        metaPaket.points = QString(record[6]).toInt();
        metaPaket.urlkey = QString(record[7]).toInt();
        list.append(metaPaket);
    }
    mysql_free_result(results);

    QString interpret;
    QString album;

    //foreach (MetaPaket metaPaket, list)
    for (int i = 0; i < list.size(); i++)
    {
        metaPaket = list.first();

        interpret = metaPaket.interpret.replace("'", "''");
        album = metaPaket.album.replace("'", "''");

        queryString = "SELECT images.path FROM albums "
                              "INNER JOIN artists ON albums.artist = artists.id "
                              "INNER JOIN images ON albums.image = images.id "
                              "WHERE "
                              "artists.name = '" + interpret + "' "
                              "AND "
                              "albums.name = '" + album + "' ";

        coverUrl = getStringFromQuery(queryString);

        if(coverUrl.startsWith(QString("amarok-sqltrackuid")))
        {
            coverUrl = fetchCover(coverUrl);
        }

        if (coverUrl.isEmpty())
            coverUrl = QString(":/images/noCover.png");

        metaPaket.coverUrl = coverUrl;

        list.pop_front();
        list.append(metaPaket);
    }

    return list;

}

QList<MetaPaket> DB_Amarok_Embedded::getTracksFromQuick(int y1, int y2, uint t, int p, bool br)
{
    QList<MetaPaket> list;
    MetaPaket metaPaket;
    QString coverUrl;
    QString album;
    QString interpret;

    QString queryString = "SELECT tracknumber, title, artists.name, albums.name, urls.rpath, devices.lastmountpoint, statistics.rating, statistics.url, tracks.createdate, years.name, statistics.accessdate "
            "FROM tracks "
            "INNER JOIN artists ON tracks.artist = artists.id "
            "INNER JOIN albums ON tracks.album = albums.id "
            "INNER JOIN urls ON tracks.url = urls.id "
            "INNER JOIN devices on urls.deviceid = devices.id "
            "INNER JOIN statistics ON tracks.url = statistics.url "
            "INNER JOIN years ON tracks.year = years.id ";

    QString stringWhere = "";
    QString stringAnd = "";
    bool boolWhere = false;

    if(y1 && y2)
    {
        stringWhere = QString("WHERE years.name > '%1' ").arg(y1);
        boolWhere = true;
        stringAnd = QString("AND years.name < '%1' ").arg(y2);
    }

    if(t)
    {
        if(boolWhere)
        {
            stringAnd = stringAnd + QString("AND tracks.createdate > " + QString("%1").arg(t) + " ");
        }
        else
        {
            stringWhere = QString("WHERE tracks.createdate > " + QString("%1").arg(t) + " ");
            boolWhere = true;
        }
    }

    if(p)
    {
        if(boolWhere)
        {
            stringAnd = stringAnd + QString("AND statistics.rating > " + QString("%1").arg(p) + " ");
        }

        else
        {
            stringWhere = QString("WHERE statistics.rating > " + QString("%1").arg(p) + " ");
            boolWhere = true;
        }
    }

    if(br)
    {
        queryString = queryString + " ORDER BY RAND() LIMIT 50" ;

    }
    else
    {
        queryString = queryString + stringWhere + stringAnd;
    }
    qDebug() << queryString;
    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);

    while((record = mysql_fetch_row(results)))
    {
        metaPaket.isEmpty = false;
        metaPaket.url = QString(record[5]) + QString("/") + QString(record[4]);
        metaPaket.title = record[1];
        metaPaket.interpret = record[2];
        metaPaket.album = record[3];
        metaPaket.points = QString(record[6]).toInt();
        metaPaket.urlkey = QString(record[7]).toInt();
        list.append(metaPaket);
    }
    mysql_free_result(results);

    for (int i = 0; i < list.size(); i++)
    {
        metaPaket = list.first();

        interpret = metaPaket.interpret.replace("'", "''");
        album = metaPaket.album.replace("'", "''");

        queryString = "SELECT images.path FROM albums "
                              "INNER JOIN artists ON albums.artist = artists.id "
                              "INNER JOIN images ON albums.image = images.id "
                              "WHERE "
                              "artists.name = '" + interpret + "' "
                              "AND "
                              "albums.name = '" + album + "' ";

        coverUrl = getStringFromQuery(queryString);

        if(coverUrl.startsWith(QString("amarok-sqltrackuid")))
        {
            coverUrl = fetchCover(coverUrl);
        }

        if (coverUrl.isEmpty())
            coverUrl = QString(":/images/noCover.png");

        metaPaket.coverUrl = coverUrl;

        list.pop_front();
        list.append(metaPaket);
    }

    return list;
}

QList<MetaPaket> DB_Amarok_Embedded::getTracksFromSampler(QString sampler)
{
    QList<MetaPaket> list;
    MetaPaket metaPaket;
    QString coverUrl;

   /* QString queryString = "SELECT urls.rpath, title, artists.name, albums.name, url From tracks "
                          "INNER JOIN artists ON tracks.artist = artists.id "
                          "INNER JOIN albums ON tracks.album = albums.id "
                          "INNER JOIN urls ON tracks.url = urls.id "
                          "WHERE "
                          "albums.name = '" + sampler + "' "
                          "ORDER BY tracknumber, title";

    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);
    while((record = mysql_fetch_row(results)))
    {
        metaPaket.isEmpty = false;
        metaPaket.url = QString("/") + record[0];
        metaPaket.title = record[1];
        metaPaket.interpret = record[2];
        metaPaket.album = record[3];
        metaPaket.coverUrl = coverUrl;
        list.append(metaPaket);
    }
    mysql_free_result(results);*/

    QString queryString = "SELECT tracknumber, title, artists.name, albums.name, urls.rpath, devices.lastmountpoint, statistics.rating, statistics.url "
            "FROM tracks "
            "INNER JOIN artists ON tracks.artist = artists.id "
            "INNER JOIN albums ON tracks.album = albums.id "
            "INNER JOIN urls ON tracks.url = urls.id "
            "INNER JOIN devices on urls.deviceid = devices.id "
            "INNER JOIN statistics ON tracks.url = statistics.url "
            "WHERE "
            "albums.name = '" + sampler + "' "
            "ORDER BY tracknumber, title";

        const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
        mysql_query(mysql, query);
        results = mysql_store_result(mysql);
        while((record = mysql_fetch_row(results)))
             {
               metaPaket.isEmpty = false;
               metaPaket.url = QString(record[5]) + QString("/") + QString(record[4]);
               metaPaket.title = record[1];
               metaPaket.interpret = record[2];
               metaPaket.album = sampler;
               metaPaket.coverUrl = coverUrl;
               metaPaket.points = QString(record[6]).toInt();
               metaPaket.urlkey = QString(record[7]).toInt();
               list.append(metaPaket);
               qDebug() << metaPaket.title;
               qDebug() << QString("Points: ") << metaPaket.points;
             }
        mysql_free_result(results);

    QString interpret;
    QString album;

    for (int i = 0; i < list.size(); i++)
    {
        metaPaket = list.first();

        interpret = metaPaket.interpret.replace("'", "''");
        album = metaPaket.album.replace("'", "''");

        queryString = "SELECT images.path FROM albums "
                              "INNER JOIN artists ON albums.artist = artists.id "
                              "INNER JOIN images ON albums.image = images.id "
                              "WHERE "
                              "artists.name = '" + interpret + "' "
                              "AND "
                              "albums.name = '" + sampler + "' ";

        coverUrl = getStringFromQuery(queryString);

        if(coverUrl.startsWith(QString("amarok-sqltrackuid")))
        {
            coverUrl = fetchCover(coverUrl);
        }

        if (coverUrl.isEmpty())
            coverUrl = QString(":/images/noCover.png");

        metaPaket.coverUrl = coverUrl;

        list.pop_front();
        list.append(metaPaket);

        //qDebug() <<  metaPaket.coverUrl;
    }

    return list;

}

void DB_Amarok_Embedded::setNewPoints(MetaPaket mp)
{
    QString queryString = "UPDATE statistics SET rating = " +
            QString("%1").arg(mp.points) +
            " WHERE url = " +
            QString("%1").arg(mp.urlkey);

    const char* query = qstrdup( QString( "%1" ).arg( queryString ).toAscii().data() );
    mysql_query(mysql, query);
    results = mysql_store_result(mysql);
}
