#ifndef GLMENUPLAYER_H
#define GLMENUPLAYER_H

#include "globject.h"
#include "gltracklist.h"
#include "glcoverview.h"
#include "glinfoview.h"
#include "glbutton.h"
#include "glanimation.h"
#include "glcombobox.h"
#include "glvizualizer.h"
#include "settings.h"
#include "metapaket.h"
#include "play_engine.h"

class GlMenuPlayer : public GlObject
{
    Q_OBJECT
private:
    GlAnimation* animation;
    GlTrackList* trackList;
    GlCoverView* coverView;
    GlInfoView* infoView;
    GlVizualizer* vizualizer;
    GlButton* buttonMain;
    GlButton* buttonDown;
    GlButton* buttonUp;
    GlButton* buttonFor;
    GlButton* buttonBack;
    GlButton* buttonPause;
    GlButton* buttonClear;
    GlComboBox* comboBoxView;
    QString cbViewString;

    Database* db;
    Play_Engine* playEngine;
    QString infoString;

    QColor fontColor;
    int fontSize;

public:
    GlMenuPlayer(GlObject* parent = 0);

    void draw(QPainter *p);

    void insertNewAlbum(QString interpret, QString album);
    void insertNewPlaylist(QString pl);
    void insertNewQuick(int y1, int y2, uint pastTime, int point, bool boolRandom);
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
    void comboBoxOpen(GlComboBox* cb);
    void comboBoxClosed(GlComboBox* cb);
    void nextSong();
    void playTrackListItem(MetaPaket);
    void prevSong();
    void setNewPoints(MetaPaket);

signals:
    void buttonMain_clicked();
};

#endif // GLMENUPLAYER_H
