#include "gltextlabel.h"

GlTextLabel::GlTextLabel(GlObject* parent) : GlObject(parent)
{
    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;

    fontColor = QColor(255,255,255,128);
    fontSize = 20;
}

void GlTextLabel::draw(QPainter *p)
{
    QLinearGradient gradient(getX(), getY() + getHeight()/2,
                             getX() + getWidth(), getY() + getHeight()/2);
    gradient.setColorAt(0, gradientColorAt0);
    gradient.setColorAt(1, gradientColorAt1);
    p->setBrush(QBrush(gradient));
    QPainterPath pa;
    pa.addRoundedRect(geometry(), borderRadius, borderRadius);
    pen.setWidth(border); //Strichbreite
    pen.setColor(borderColor); //Strichfarbe
    p->setPen(pen);
    p->drawPath(pa);

    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    pen.setColor(fontColor);
    p->setFont(font);
    p->setPen(pen);
    QRect rect = geometry();
    rect.setX(rect.x() + 10);
    p->drawText(rect, text, QTextOption(Qt::AlignVCenter));
}
