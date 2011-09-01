/*GlButtonList hält eine anzahl von GlButtons. Wird ein
  Button angeklickt sendet GlButtonList das Signal
  buttonClicked mit dem Text des Buttons*/

#ifndef GLBUTTONLIST_H
#define GLBUTTONLIST_H

#include "globject.h"
#include "glbutton.h"

#include <QList>
class GlButtonList : public GlObject
{
    Q_OBJECT

private:
    QList<GlButton *> buttonList;

public:
    GlButtonList(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setGeometry(int posX, int posY, int w, int h);
    void setLarge();

public slots:
    void clicked();

signals:
    void buttonClicked(QString);
};

#endif // GLBUTTONLIST_H
