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

QStringList Database::getPlaylist()
{
    QStringList tmp;
    return tmp;
}

QStringList Database::getSampler()
{
    QStringList tmp;
    return tmp;
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

QList<MetaPaket> Database::getTracksFromAlbum(QString interpret, QString album)
{
    Q_UNUSED (interpret);
    Q_UNUSED (album);

    QList<MetaPaket> dummy;
    return dummy;
}

QList<MetaPaket> Database::getTracksFromPlaylist(QString playlist)
{
    Q_UNUSED (playlist);

    QList<MetaPaket> dummy;
    return dummy;
}

QList<MetaPaket> Database::getTracksFromQuick(QString year)
{
    Q_UNUSED (year);

    QList<MetaPaket> dummy;
    return dummy;
}

QList<MetaPaket> Database::getTracksFromSampler(QString sampler)
{
    Q_UNUSED (sampler);

    QList<MetaPaket> dummy;
    return dummy;
}
