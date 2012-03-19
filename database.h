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
#include <QtCrypto>

#include <taglib/tstring.h>
#include <fileref.h>
#include <mpegfile.h>
#include <tag.h>
#include <attachedpictureframe.h>
#include <id3v2tag.h>


#include "metapaket.h"

class Database : public QObject
{
    Q_OBJECT

private:
    QString embeddedPath;
    QCA::Initializer init;

public:
    Database(QObject* parent);

    virtual QString fetchCover(QString uuid) {Q_UNUSED(uuid); return QString(":/images/noCover.png");}
 TagLib::String Qt4StringToString(QString s) {return TagLib::String(s.toLatin1().data(),
                                                                    TagLib::String::Latin1);}
 
    QString getEmbeddedPath() { return embeddedPath; }
    virtual QStringList getAlbenFromInterpret(QString s) { return getStringListFromQuery(s); }
    virtual QStringList getInterpreten(QString s) { return getStringListFromQuery(s); }
    virtual QPixmap getCover(QString i, QString a);
    virtual QString getCoverPath(QString i, QString a);
    virtual QStringList getPlaylist();
    virtual QStringList getSampler();
    virtual QString getStringFromQuery(QString queryString);
    virtual QStringList getStringListFromQuery(QString queryString);
    virtual QList<MetaPaket> getTracksFromAlbum(QString interpret, QString album);
    virtual QList<MetaPaket> getTracksFromPlaylist(QString playlist);
    virtual QList<MetaPaket> getTracksFromSampler(QString sampler);
    virtual QList<MetaPaket> getTracksFromQuick(int y1, int y2, uint t, int p, bool br);
    QString md5sum(QString s);
    virtual void openDataBase() {}
    virtual void openDataBase(QString server) { Q_UNUSED(server); }
    void setEmbeddedPath(QString ep) { embeddedPath = ep; }
    virtual void setNewPoints(MetaPaket mp);
    virtual void upDateAccess(MetaPaket mp) { Q_UNUSED(mp); }

};

#endif // DATABASE_H
