/*GlMenuInterpret beinhaltet für jeden Buchstaben im
  Alphabet einen Button. Wird auf einen Button geklickt
  erscheinet in dem daneben stehenden ListWidget die
  Interpreten mit dem Anfangsbuchstaben des Buttons.
  Button A liefert alle Interpreten mit dem Anfangsbuch-
  staben A.*/

#ifndef GLMENUINTERPRET_H
#define GLMENUINTERPRET_H

#include "globject.h"
#include "gllistwidget.h"
#include "glbuttonlist.h"
#include "settings.h"

class GlMenuInterpret : public GlObject
{
    Q_OBJECT
private:
    QColor backGroundColor;
    GlListWidget* listWidget;
    GlButton* buttonMain;
    GlButton* buttonPlayer;
    GlButtonList* buttonList;
    Database* db;

public:
    GlMenuInterpret(GlObject* parent = 0);
    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void rollIn(QPainter *p);
    void rollOut(QPainter *p);

    void setDatabase(Database* d) { db = d; }
    void setLarge();

public slots:
    void buttonClicked(QString);

signals:
    void interpretSelected(QString);
    void buttonMainClicked();
    void buttonPlayerClicked();
};

#endif // GLMENUINTERPRET_H
