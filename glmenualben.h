#ifndef GLMENUALBEN_H
#define GLMENUALBEN_H

#include "globject.h"
#include "glpictureflow.h"
#include "gltracklistwidget.h"
#include "settings.h"

class GlMenuAlben : public GlObject
{
    Q_OBJECT
private:
    GlPictureFlow* pictureFlow;
    GlTrackListWidget* trackList;
    GlButton* buttonMain;
    GlButton* buttonPlayer;
    GlButton* buttonInterpret;
    Database* db;
    QColor backGroundColor;
    QString stringInterpret;
    bool tracks;

public:
    GlMenuAlben(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void newInterpret(QString interpret);

    void rollIn(QPainter* p);
    void rollOut(QPainter* p);

    void setDatabase(Database* d) { db = d; }
    void setLarge();

public slots:
    void albumSelected(QString);
    void animationDone();
    void buttonInterpret_clicked();
    void buttonMain_clicked();
    void buttonPictureFlow_Tracks_Clicked();
    void buttonPlayer_clicked();
    void pictureFlow_animationDone();

signals:
    void backToInterpret();
    void backToMain();
    void backToPlayer();
    void newAlbumSelected(QString, QString);
    void newTitleSelected(MetaPaket);

};

#endif // GLMENUALBEN_H
