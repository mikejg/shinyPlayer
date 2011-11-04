#include "gltracklistwidget.h"

GlTrackListWidget::GlTrackListWidget(GlObject* parent) : GlObject(parent)
{
    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;

    fontColor = QColor(255,255,255,128);
    fontSize = 20;
    itemHeight = fontSize + 10;

    animation = new GlAnimation(this);
    animation->setGeometry(5,305,790,290);
    connect(animation, SIGNAL(animationDone()), this, SIGNAL(animationDone()));

    setGeometry(5, 305, 790, 290);
    setVisible(false);
}

void GlTrackListWidget::draw(QPainter *p)
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

    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);

    p->setPen(fontColor);
    GlTrackListWidgetItem* item;
    foreach(item, itemList)
    {
        p->drawText(item->geometry(), Qt::AlignLeft | Qt::AlignVCenter, item->getText());
    }
}


void GlTrackListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    /*Wurde die Maus innerhalb des eigenen Rechtecks gedrückt wird in
      der Liste nach einem Button oder Listeneintrag gesucht und seine
      Funktion mouseReleaseEvent aufgerufen*/
    QRect rect;
    for(int i = 0; i < itemList.size(); i++)
       {
         rect = itemList.at(i)->geometry();
         if(itemList.at(i)->isVisible() && rect.contains(event->pos()))
           {
             qDebug() << itemList.at(i)->getText();
             newTitleSelected(itemList.at(i)->getMetaPaket());
           }
       }
}

void GlTrackListWidget::startZoomIn()
{
    setImage();
    animation->setImage(this->getImage());

    animation->startZoomIn();
}

void GlTrackListWidget::startZoomOut()
{
    setImage();
    animation->setImage(this->getImage());

    animation->startZoomOut();
}

void GlTrackListWidget::setLarge()
{
    fontSize = (int)(fontSize * 1.28);
    itemHeight = (int)(itemHeight * 1.28);

    int newX, newY, newHeight, newWidth;
    QPoint c;

    newHeight = (int)(getHeight() * 1.28);
    newWidth = (int)(getWidth() * 1.28);
    c = getCenter();
    newX = (int)(c.x() * 1.28) - (int)(newWidth / 2);
    newY = (int)(c.y() * 1.28) - (int)(newHeight / 2);

    setGeometry(newX, newY, newWidth, newHeight);
    animation->setGeometry(newX, newY, newWidth, newHeight);
}

void GlTrackListWidget::setTracks(QList<MetaPaket> mplist)
{
    itemList.clear();
    //qDebug() << mplist.size();

    GlTrackListWidgetItem* item;
    for( int i = 0; i < mplist.size(); i++)
    {
        item = new GlTrackListWidgetItem(this);
        item->setMetaPaket(mplist.at(i));
        if(i < 9)
        {
            item->setGeometry(getX()+5, getY() + 5 + i*itemHeight, getWidth()/2 - 10, itemHeight);
        }
        else
        {
            item->setGeometry(getWidth()/2 + 5, getY()+5 + (i -9)*itemHeight, getWidth()/2 - 10, itemHeight);
        }

        itemList.append(item);
    }
}

GlTrackListWidgetItem::GlTrackListWidgetItem(GlObject *parent) : GlObject(parent)
{

}
