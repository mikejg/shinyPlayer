#include "gllistwidget.h"
#include <QLinearGradient>
#include <QPainterPath>

GlListWidget::GlListWidget(GlObject* parent ) : GlObject(parent)
{
    backGroundColor = QColor(Qt::black);
    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;
    startPos = 0;

    fontColor = QColor(255,255,255,128);
    fontSize = 20;

    buttonDown = new GlButton(this);
    buttonDown->setBackGroundPixmap(QPixmap(":/images/button400.png"));
    buttonDown->setBackGroundPixmapPressed(QPixmap(":/images/button400_pressed.png"));

    buttonUp = new GlButton(this);
    buttonUp->setBackGroundPixmap(QPixmap(":/images/button400.png"));
    buttonUp->setBackGroundPixmapPressed(QPixmap(":/images/button400_pressed.png"));
}

void GlListWidget::draw(QPainter *p)
{
    p->fillRect(geometry(), Qt::black);
    QLinearGradient gradient( listX + listWidth/2, listY,
                              listX + listWidth/2, listY + listHeight);

    gradient.setColorAt(0, gradientColorAt0);
    gradient.setColorAt(1, gradientColorAt1);
    p->setBrush(QBrush(gradient));
    QPainterPath pa;
    QRect rect(listX, listY, listWidth,listHeight);
    pa.addRoundedRect(rect, borderRadius, borderRadius);
    pen.setWidth(border); //Strichbreite
    pen.setColor(borderColor); //Strichfarbe
    p->setPen(pen);
    p->drawPath(pa);

    buttonUp->draw(p);
    buttonDown->draw(p);

    for(int i = 0; i < 16; i++)
    {
        if(i + startPos < listItem.size())
        {
            QRect re(listX + 10, listY + i * 30,
                     listWidth - 20, 30);
            drawText(p, re, listItem.at(i+startPos)->getText());
        }
    }
}

void GlListWidget::drawText(QPainter *p, QRect rect, QString text)
{
    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);

    p->setPen(fontColor);
    p->drawText(rect,Qt::AlignLeft | Qt::AlignVCenter,text);
}

void GlListWidget::insertItem(QString text)
{
    GlListWidgetItem* item = new GlListWidgetItem(this);
    item->setText(text);
    listItem.append(item);
    setImage();
}

void GlListWidget::mousePressEvent(QMouseEvent *event)
{
    QRect rect;
    for(int i = 0; i < listChilds.size(); i++)
       {
         rect = listChilds.at(i)->geometry();
         if(listChilds.at(i)->isVisible() && rect.contains(event->pos()))
           {
             listChilds.at(i)->mousePressEvent(event);
           }
       }
}

void GlListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QRect rect;
    for(int i = 0; i < listChilds.size(); i++)
       {
         rect = listChilds.at(i)->geometry();
         if(listChilds.at(i)->isVisible() && rect.contains(event->pos()))
           {
             listChilds.at(i)->mouseReleaseEvent(event);
           }
       }
}

void GlListWidget::setGeometry(int posX, int posY, int w, int h)
{
    GlObject::setGeometry(posX,posY,w,h);

    buttonUp->setGeometry(posX,posY,400,30);
    buttonDown->setGeometry(posX, posY + h - 30, 400, 30);

    listX = posX;
    listY = posY + 35;
    listWidth = w;
    listHeight = h - 70;
}

void GlListWidget::setLarge()
{
    int newX, newY, newHeight, newWidth;
    QPoint c;

    newHeight = (int)(getHeight() * 1.28);
    newWidth = (int)(getWidth() * 1.28);
    c = getCenter();
    newX = (int)(c.x() * 1.28) - (int)(newWidth / 2);
    newY = (int)(c.y() * 1.28) - (int)(newHeight / 2);

    GlObject::setGeometry(newX, newY, newWidth, newHeight);
    buttonUp->setLarge();
    buttonDown->setLarge();

    listX = newX;
    listY = newY + buttonUp->getHeight() + 5;
    listWidth = newWidth;
    listHeight = newHeight - buttonUp->getHeight()*2 -10;

    setImage();
}

GlListWidgetItem::GlListWidgetItem(GlObject* parent) : GlObject(parent)
{

}
