#ifndef GLCOVERVIEW_H
#define GLCOVERVIEW_H

#include "globject.h"

class GlCoverView : public GlObject
{
    Q_OBJECT
private:
    QColor borderColor;
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QPen pen;

    int border;
    int borderRadius;

    QString coverUrl;
    QImage coverImg;

public:
    GlCoverView(GlObject *parent = 0);

    void draw(QPainter *p);

    void setCoverUrl(QString cu) { coverUrl = cu; }
signals:

public slots:

};

#endif // GLCOVERVIEW_H
