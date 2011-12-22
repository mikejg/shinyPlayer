#include "glcoverview.h"
#include <QFile>

GlCoverView::GlCoverView(GlObject *parent) :
    GlObject(parent)
{
    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;
}

void GlCoverView::draw(QPainter *p)
{
    p->fillRect(geometry(), Qt::black);
    QLinearGradient gradient( getWidth()/2, getY(),
                              getWidth()/2, getY() + getHeight());

    gradient.setColorAt(0, gradientColorAt0);
    gradient.setColorAt(1, gradientColorAt1);
    p->setBrush(QBrush(gradient));
    QPainterPath pa;
    QRect rect = geometry();
    pa.addRoundedRect(rect, borderRadius, borderRadius);
    pen.setWidth(border); //Strichbreite
    pen.setColor(borderColor); //Strichfarbe
    p->setPen(pen);
    p->drawPath(pa);

    QFile testFile(coverUrl);
    if(testFile.exists())
    {
        coverImg.load(coverUrl);
        coverImg = coverImg.scaled(400,400);
        p->drawImage(getWidth()/2 + getX() - 200,
                     getHeight()/2 + getY() - 200,
                     coverImg);
    }
}
