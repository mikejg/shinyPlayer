#ifndef GLTEXTLABEL_H
#define GLTEXTLABEL_H

#include "globject.h"

class GlTextLabel : public GlObject
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

    QString text;

public:
    GlTextLabel(GlObject* parent = 0);

    void draw(QPainter *p);

    void setText(QString t) { text = t; }

};

#endif // GLTEXTLABEL_H
