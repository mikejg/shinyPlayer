#ifndef GLMENUPLAYER_H
#define GLMENUPLAYER_H

#include "globject.h"
#include "gltracklist.h"
#include "glbutton.h"
#include "glanimation.h"
#include "settings.h"
#include "metapaket.h"
#include "play_engine.h"

class GlMenuPlayer : public GlObject
{
    Q_OBJECT
private:
    GlAnimation* animation;
    GlTrackList* trackList;
    GlButton* buttonMain;
    GlButton* buttonDown;
    GlButton* buttonUp;
    GlButton* buttonFor;
    GlButton* buttonBack;
    GlButton* buttonPause;
    GlButton* buttonClear;

    Database* db;
    Play_Engine* playEngine;

public:
    GlMenuPlayer(GlObject* parent = 0);

    void draw(QPainter *p);

    void insertNewAlbum(QString interpret, QString album);
    void insertNewPlaylist(QString pl);
    void insertNewSampler(QString sampler);
    void insertNewTitle(MetaPaket mp);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void setPlayEngine(Play_Engine* pe);

    void rollIn(QPainter* p);
    void rollOut(QPainter* p);

    void setDatabase(Database* d) { db = d; }

public slots:
    void buttonDown_clicked();
    void buttonUp_clicked();
    void nextSong();
    void playTrackListItem(MetaPaket);
    void prevSong();

signals:
    void buttonMain_clicked();
};

#endif // GLMENUPLAYER_H
