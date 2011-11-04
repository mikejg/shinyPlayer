#ifndef GLMENUPLAYLIST_H
#define GLMENUPLAYLIST_H

#include "globject.h"
#include "gllistwidget.h"
#include "settings.h"

class GlMenuPlaylist : public GlObject
{
    Q_OBJECT
private:
    QColor backGroundColor;
    GlListWidget* listWidget;
    GlButton* buttonMain;
    GlButton* buttonPlayer;
    Database* db;

public:
    GlMenuPlaylist(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void rollIn(QPainter *p);
    void rollOut(QPainter *p);

    void setDatabase(Database* d);
    void setLarge();

signals:
    void playlistSelected(QString);
    void buttonMainClicked();
    void buttonPlayerClicked();

};

#endif // GLMENUPLAYLIST_H
