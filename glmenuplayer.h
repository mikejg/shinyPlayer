#ifndef GLMENUPLAYER_H
#define GLMENUPLAYER_H

#include "globject.h"
#include "gltracklist.h"
#include "glbutton.h"
#include "settings.h"
#include "metapaket.h"
#include "play_engine.h"

class GlMenuPlayer : public GlObject
{
    Q_OBJECT
private:
    GlTrackList* trackList;
    GlButton* buttonMain;

    Database* db;
    Play_Engine* playEngine;

public:
    GlMenuPlayer(GlObject* parent = 0);

    void draw(QPainter *p);

    void insertNewAlbum(QString interpret, QString album);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void setPlayEngine(Play_Engine* pe) { playEngine = pe; }

    void rollIn(QPainter* p);
    void rollOut(QPainter* p);

    void setDatabase(Database* d) { db = d; }

signals:
    void buttonMain_clicked();
};

#endif // GLMENUPLAYER_H
