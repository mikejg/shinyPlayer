#include "glbutton.h"
#include <QTimer>

GlButton::GlButton(GlObject* parent) : GlObject(parent)
{
    fontColor = QColor(255,255,255,128);
    fontSize = 20;
    isPressed = false;
}

void GlButton::draw(QPainter *p)
{
    if(isPressed)
        drawBackGroundPixmapPressed(p);
    else
        drawBackGroundPixmap(p);
    drawText(p);
}

void GlButton::drawBackGroundPixmapPressed(QPainter* p)
{
    if(!backGroundPixmapPressed.isNull())
      {
        p->drawPixmap(QPoint(getX(),getY()), backGroundPixmapPressed);
      }
}

void GlButton::drawText(QPainter* p)
{
    if(stringText.isNull()) return;

    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);

    p->setPen(fontColor);
    p->drawText(QRect(getX(),getY()+2,getWidth(), getHeight()),Qt::AlignHCenter,stringText);

}

void GlButton::mousePressEvent(QMouseEvent *event)
{
    isPressed = true;
    newChildToDraw(this);
}

void GlButton::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed = false;
    newChildToDraw(this);

    QTimer::singleShot(100,this,SIGNAL(clicked()));
}

void GlButton::setLarge()
{
    fontSize = (int)(fontSize * 1.28);
    int newX, newY, newHeight, newWidth;
    QPoint c;

    newHeight = (int)(getHeight() * 1.28);
    newWidth = (int)(getWidth() * 1.28);
    c = getCenter();
    newX = (int)(c.x() * 1.28) - (int)(newWidth / 2);
    newY = (int)(c.y() * 1.28) - (int)(newHeight / 2);

    setGeometry(newX, newY, newWidth, newHeight);
    backGroundPixmap = backGroundPixmap.scaled(newWidth,newHeight);
    backGroundPixmapPressed = backGroundPixmapPressed.scaled(newWidth,newHeight);
    setImage();
}
