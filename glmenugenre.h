#ifndef GLMENUGENRE_H
#define GLMENUGENRE_H

#include "globject.h"
#include "gllistwidget.h"
#include "glbutton.h"

class GlMenuGenre : public GlObject
{
    Q_OBJECT
private:
    QColor backGroundColor;
    GlListWidget* listWidget;
    GlButton* buttonMain;
    GlButton* buttonPlayer;

public:
    GlMenuGenre(GlObject* parent = 0);
    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void rollIn(QPainter* p);

    void setLarge();
};

#endif // GLMENUGENRE_H
