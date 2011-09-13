/* GlListWidget ist ähnlich dem QListWiget. */

#ifndef GLLISTWIDGET_H
#define GLLISTWIDGET_H

#include "globject.h"
#include "glbutton.h"
#include "glanimation.h"

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
    Q_OBJECT

private:
    GlButton* buttonDown;
    GlButton* buttonUp;
    GlAnimation* animation;

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
    int itemHeight;

public:
    GlListWidget(GlObject* parent = 0);
    void draw(QPainter *p);
    void drawText(QPainter *p, QRect rect, QString text);

    QImage getListImage(bool fullSize = false);

    void insertItem(QString text);
    void insertItem(QStringList l);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void setGeometry(int posX, int posY, int w, int h);
    void setLarge();

public slots:
    void buttonDown_clicked();
    void buttonUp_clicked();

signals:
    void itemClicked(QString);

};



#endif // GLLISTWIDGET_H
