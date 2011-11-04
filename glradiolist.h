#ifndef GLRADIOLIST_H
#define GLRADIOLIST_H

#include"globject.h"
#include "QList"

class GlRadioListItem : public GlObject
{
    Q_OBJECT

private:
    QString text;
    QString url;

public:
    GlRadioListItem(GlObject* parent = 0);

    QString getText() { return text; }
    QString getUrl() { return url; }

    void mouseReleaseEvent(QMouseEvent *event);

    void setText(QString s) { text = s; }
    void setUrl(QString u) { url = u; }

signals:
    void clicked(QString);

};

class GlRadioList : public GlObject
{
    Q_OBJECT
private:
    QColor borderColor;
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QColor fontColor;
    QPen pen;

    int border;
    int borderRadius;
    int fontSize;
    int itemHeight;
    int currentItem;

    QList<GlRadioListItem*> list;

public:
    GlRadioList(GlObject* parent = 0);

    void draw(QPainter *p);

    void mouseReleaseEvent(QMouseEvent *event);

    void setLarge();

signals:
    void radioItemClicked(QString);
};

#endif // GLRADIOLIST_H
