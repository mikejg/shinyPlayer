#ifndef GLMENUINTERPRET_H
#define GLMENUINTERPRET_H

#include "globject.h"
#include "gllistwidget.h"

class GlMenuInterpret : public GlObject
{
    Q_OBJECT
private:
    QColor backGroundColor;
    GlListWidget* listWidget;

public:
    GlMenuInterpret(GlObject* parent = 0);
    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );
};

#endif // GLMENUINTERPRET_H
