#ifndef GLMENUSAMPLER_H
#define GLMENUSAMPLER_H

#include "globject.h"
#include "gllistwidget.h"
#include "settings.h"

class GlMenuSampler : public GlObject
{
    Q_OBJECT
private:
    QColor backGroundColor;
    GlListWidget* listWidget;
    GlButton* buttonMain;
    GlButton* buttonPlayer;
    Database* db;

public:
    GlMenuSampler(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void rollIn(QPainter *p);
    void rollOut(QPainter *p);

    void setDatabase(Database* d);
    void setLarge();

signals:
    void samplerSelected(QString);
    void buttonMainClicked();
    void buttonPlayerClicked();

};

#endif // GLMENUSAMPLER_H
