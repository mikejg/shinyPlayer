#ifndef GLCOMBOBOX_H
#define GLCOMBOBOX_H

#include "globject.h"
#include <QRect>

class GlComboBoxItem : public GlObject
{
    Q_OBJECT
private:
    QString text;

public:
    GlComboBoxItem(GlObject* parent = 0);

    QString getText() { return text; }

    void mouseReleaseEvent ( QMouseEvent * event );

    void setText(QString t) { text = t; }

signals:
    void clicked(QString);
};

class GlComboBox : public GlObject
{
    Q_OBJECT

private:
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QColor borderColor;
    QColor fontColor;
    QPen pen;
    QRect orgRect;

    int border;
    int borderRadius;
    int fontSize;
    int itemHeight;
    int closedHeight;
    //int orgY;

    bool isOpen;
    bool expandUp;

    QList<GlComboBoxItem*> list;

public:
    int orgY;


    GlComboBox(GlObject* parent = 0);

    void clear();

    void draw(QPainter *p);

    void insertItem(QString text);

    void mouseReleaseEvent ( QMouseEvent * event );

    void setGeometry(int posX, int posY, int w, int h);

    QString getText() { return list.first()->getText(); }

public slots:
    void itemClicked(QString);

signals:
    void open(GlComboBox*);
    void closed(GlComboBox*);
};

#endif // GLCOMBOBOX_H
