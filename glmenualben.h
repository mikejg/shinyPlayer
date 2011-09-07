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
    Database* db;
    QColor backGroundColor;

public:
    GlMenuAlben(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void newInterpret(QString interpret);

    void setDatabase(Database* d) { db = d; }
    void setLarge();
};

#endif // GLMENUALBEN_H
