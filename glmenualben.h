#ifndef GLMENUALBEN_H
#define GLMENUALBEN_H

#include "globject.h"
#include "glpictureflow.h"
#include "settings.h"

class GlMenuAlben : public GlObject
{
    Q_OBJECT
private:
    GlPictureFlow* pictureFlow;
    GlButton* buttonMain;
    GlButton* buttonPlayer;
    GlButton* buttonInterpret;
    Database* db;
    QColor backGroundColor;
    QString stringInterpret;

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
    void buttonInterpret_clicked();
    void buttonMain_clicked();
    void buttonPlayer_clicked();

signals:
    void backToInterpret();
    void backToMain();
    void backToPlayer();
    void newAlbumSelected(QString, QString);

};

#endif // GLMENUALBEN_H
