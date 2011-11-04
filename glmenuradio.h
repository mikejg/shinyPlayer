#ifndef GLMENURADIO_H
#define GLMENURADIO_H

#include "globject.h"
#include "glradiolist.h"
#include "glbutton.h"

class GlMenuRadio : public GlObject
{
    Q_OBJECT
private:
    GlRadioList* radiolist;
    GlButton* buttonMain;

public:
    GlMenuRadio(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void rollIn(QPainter* p);
    void rollOut(QPainter* p);

    void setLarge();
signals:
    void radioItemClicked(QString);
    void buttonMain_clicked();
};

#endif // GLMENURADIO_H
