#include "db_qmdb_sql.h"
#include <QString>

//
DB_QMDB_SQL::DB_QMDB_SQL(QObject *parent) : Database(parent)
{

}

void DB_QMDB_SQL::openDataBase(QString server)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(server);
    db.setDatabaseName("qmdb");
    db.setUserName("qmdbuser");
    db.setPassword("qmdb");

    if(db.open()) qDebug() << "QMDB offen :)";
}

QStringList DB_QMDB_SQL::getAlbenFromInterpret(QString s)
{
    s = s.replace("'", "''");
    QStringList list;
    list = getStringListFromQuery(QString("SELECT DISTINCT t_album.name, t_artist.name FROM t_title "
                                           "INNER JOIN t_artist ON t_title.artist = t_artist.id "
                                           "INNER JOIN t_album ON t_title.album = t_album.id "
                                           "WHERE "
                                           "t_artist.name = '" + s + "' "));

    return list;
}

QPixmap DB_QMDB_SQL::getCover(QString i, QString a)
{
    QPixmap pixmap;
    QString filePath = QDir::homePath() + "/.config/Mike Gareiss/";
    filePath = filePath + md5sum(i + a);
    //qDebug() <<  filePath;
    QFile coverFile(filePath);
    if (coverFile.exists())
    {
      pixmap.load(filePath);
      //qDebug("covefile loaded");
      return pixmap;
    }

    QSqlQuery query(db);
    query.exec("SELECT hasImage, image, t_album.name, t_artist.name FROM t_album "
               "INNER JOIN t_artist ON t_album.artist = t_artist.id "
               "WHERE "
               "t_album.name = '" + a + "' "
               "AND "
               "t_artist.name = '" + i + "'");

    if(query.first())
    {
        if(query.value(0).toInt() == 1)
        {
            QString image = query.value(1).toString();
            QByteArray xcode;

            if(!image.contains("|end_stream|"))
            {
                qDebug("error sql - limit");
                pixmap.load(":/images/noCover.png", "PNG");
                return pixmap;
            }

            QStringList dat = image.split("|");
            if (dat.size() > 0)
            {
                   xcode.append(dat.at(0));
                   pixmap.loadFromData(QByteArray::fromBase64(xcode));
                   pixmap.save(filePath, "PNG");
                   return pixmap;
            }
        }
    }
    pixmap.load(":/images/noCover.png", "PNG");
    return pixmap;
}

QString DB_QMDB_SQL::getCoverPath(QString i, QString a)
{   
    QPixmap pixmap;
    QString filePath = QDir::homePath() + "/.config/Mike Gareiss/";
    filePath = filePath + md5sum(i + a);
    //qDebug() <<  filePath;
    QFile coverFile(filePath);
    if (coverFile.exists())
    {
      return filePath;
    }

    QSqlQuery query(db);
    query.exec("SELECT hasImage, image, t_album.name, t_artist.name FROM t_album "
               "INNER JOIN t_artist ON t_album.artist = t_artist.id "
               "WHERE "
               "t_album.name = '" + a + "' "
               "AND "
               "t_artist.name = '" + i + "'");

    if(query.first())
    {
        if(query.value(0).toInt() == 1)
        {
            QString image = query.value(1).toString();
            QByteArray xcode;

            if(!image.contains("|end_stream|"))
            {
                qDebug("error sql - limit");
                //pixmap.load(":/images/noCover.png", "PNG");
                return QString(":/images/noCover.png");
            }

            QStringList dat = image.split("|");
            if (dat.size() > 0)
            {
                   xcode.append(dat.at(0));
                   pixmap.loadFromData(QByteArray::fromBase64(xcode));
                   pixmap.save(filePath, "PNG");
                   return filePath;
            }
        }
    }
    return QString(":/images/noCover.png");
}

QStringList DB_QMDB_SQL::getInterpreten(QString s)
{
    QStringList list;
    list = getStringListFromQuery(QString("SELECT name FROM t_artist WHERE name LIKE '" + s + "%'"));

    return list;
}

QStringList DB_QMDB_SQL::getStringListFromQuery(QString queryString)
{
    QStringList sl;
    QSqlQuery query(db);
    query.exec(queryString);
    while(query.next())
    {
        sl << query.value(0).toString();
    }
    return sl;
}

QList<MetaPaket> DB_QMDB_SQL::getTracksFromAlbum(QString interpret, QString album)
{
    QList <MetaPaket> metaPakets;
    MetaPaket metaPaket;
    interpret = interpret.replace("'", "''");
    album = album.replace("'", "''");
    QSqlQuery query(db);

    query.exec("SELECT pfad, title, tracknr, t_artist.name, t_album.name, wertung FROM t_title "
               "INNER JOIN t_artist ON t_title.artist = t_artist.id "
               "INNER JOIN t_album ON t_title.album = t_album.id "
               "WHERE "
               "t_artist.name = '" + interpret + "' "
               "AND t_album.name = '" + album + "' "
                "ORDER BY tracknr, title");

    while(query.next())
    {
        metaPaket.isEmpty = false;
        metaPaket.url = query.value(0).toString();
        metaPaket.title = query.value(1).toString();
        metaPaket.interpret = query.value(3).toString();
        metaPaket.album = query.value(4).toString();
        metaPaket.coverUrl = getCoverPath(metaPaket.interpret, metaPaket.album);
        metaPaket.points = query.value(5).toInt();
        metaPaket.lastPlayed = 0;
        metaPakets.append(metaPaket);
    }

    return metaPakets;
}

void DB_QMDB_SQL::setNewPoints(MetaPaket mp)
{
    QString commentString = QString("QMDB#%1#%2").arg(mp.points).arg(mp.lastPlayed);
    qDebug() << commentString;
    QByteArray fileName = QFile::encodeName( mp.url );

    TagLib::MPEG::File f(fileName);
    if(f.isValid())
    {
        TagLib::ID3v2::Tag* id3v2 = f.ID3v2Tag();
        id3v2->setComment(Qt4StringToString(commentString));
        f.save();
   }
}


