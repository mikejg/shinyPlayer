#ifndef GLLISTWIDGET_H
#define GLLISTWIDGET_H

#include "globject.h"
#include "glbutton.h"

#include <QColor>
#include <QPen>
#include <QList>

class GlListWidgetItem : public GlObject
{
    Q_OBJECT
private:
    QString stringText;

public:
    GlListWidgetItem(GlObject* parent = 0);

    QString getText() { return stringText; }
    void setText(QString t) { stringText = t; }

};

class GlListWidget : public GlObject
{
private:
    GlButton* buttonDown;
    GlButton* buttonUp;

    QList<GlListWidgetItem *> listItem;
    QColor backGroundColor;
    QColor borderColor;
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QColor fontColor;
    QPen pen;

    int listX;
    int listY;
    int listWidth;
    int listHeight;
    int border;
    int borderRadius;
    int fontSize;
    int startPos;

public:
    GlListWidget(GlObject* parent = 0);
    void draw(QPainter *p);
    void drawText(QPainter *p, QRect rect, QString text);

    void insertItem(QString text);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void setGeometry(int posX, int posY, int w, int h);
    void setLarge();
};



#endif // GLLISTWIDGET_H
