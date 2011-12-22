/* Database ist eine Abstrakte Klasse von der die Klassen
   für verschiedene Datenbanken abgeleitet werden. */

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include <QDebug>
#include <QList>

#include "metapaket.h"

class Database : public QObject
{
    Q_OBJECT

private:
    QString embeddedPath;

public:
    Database(QObject* parent);

    virtual QString fetchCover(QString uuid) {Q_UNUSED(uuid); return QString(":/images/noCover.png");}

    QString getEmbeddedPath() { return embeddedPath; }
    virtual QStringList getAlbenFromInterpret(QString s) { return getStringListFromQuery(s); }
    virtual QStringList getInterpreten(QString s) { return getStringListFromQuery(s); }
    virtual QPixmap getCover(QString i, QString a);
    virtual QStringList getPlaylist();
    virtual QStringList getSampler();
    virtual QString getStringFromQuery(QString queryString);
    virtual QStringList getStringListFromQuery(QString queryString);
    virtual QList<MetaPaket> getTracksFromAlbum(QString interpret, QString album);
    virtual QList<MetaPaket> getTracksFromPlaylist(QString playlist);
    virtual QList<MetaPaket> getTracksFromSampler(QString sampler);
    virtual QList<MetaPaket> getTracksFromQuick(int y1, int y2, uint t, int p, bool br);
    virtual void openDataBase() {}

    void setEmbeddedPath(QString ep) { embeddedPath = ep; }
    virtual void setNewPoints(MetaPaket mp);
};

#endif // DATABASE_H
