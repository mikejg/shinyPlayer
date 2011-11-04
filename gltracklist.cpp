#include "gltracklist.h"

GlTrackList::GlTrackList(GlObject* parent) : GlObject(parent)
{
    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;
    startPos = 0;

    fontColor = QColor(255,255,255,128);
    fontSize = 20;
    itemHeight = fontSize + 10;
}

void GlTrackList::clear()
{
    listItem.clear();
    currentItem = 0;
    newChildToDraw(this);
}

void GlTrackList::draw(QPainter* p)
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

    for(int i = 0; i < 14; i++)
    {
        if(i + startPos < listItem.size())
        {
            QRect re(10, getY() + i * itemHeight,
                     getWidth()/2 - 20, itemHeight);
            drawTextLeft(p, re, listItem.at(i+startPos)->title());

            re = QRect(getWidth()/2 + 10, getY() + i * itemHeight,
                       getWidth()/2 -20, itemHeight);
            drawTextRight(p, re, listItem.at(i+startPos)->interpret());
            if( (i + startPos)  == currentItem)
              {
                p->fillRect(QRect(10, getY() + 2 + itemHeight * i, getWidth() - 20 , itemHeight - 4), QColor(0,0,0,125));
              }
        }
    }
}

void GlTrackList::drawTextLeft(QPainter *p, QRect rect, QString text)
{
    /*Text in die Liste schreiben
      - Font von QPainter holen und mit eigenen Werten überschreiben
      - Den Stift von QPainter mit der Schriftfarbe setzten
      - Text in ein Rechteck schreiben*/

    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);

    p->setPen(fontColor);
    p->drawText(rect,Qt::AlignLeft | Qt::AlignVCenter,text);
}

void GlTrackList::drawTextRight(QPainter *p, QRect rect, QString text)
{
    /*Text in die Liste schreiben
      - Font von QPainter holen und mit eigenen Werten überschreiben
      - Den Stift von QPainter mit der Schriftfarbe setzten
      - Text in ein Rechteck schreiben*/

    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);

    p->setPen(fontColor);
    p->drawText(rect,Qt::AlignRight | Qt::AlignVCenter,text);
}


MetaPaket GlTrackList::nextItem()
{
    MetaPaket mp;
    mp.isEmpty = true;

    if(currentItem + 1 < listItem.size())
    {
        currentItem++;
        mp = listItem.at(currentItem)->getMetaPaket();
    }

    return mp;
}

void GlTrackList::mouseReleaseEvent(QMouseEvent *event)
{
    /*Wurde die Maus innerhalb des eigenen Rechtecks gedrückt wird in
      der Liste nach einem Button oder Listeneintrag gesucht und seine
      Funktion mouseReleaseEvent aufgerufen*/

    QRect rect = geometry();

    if(rect.contains(event->pos()))
    {
        //qDebug() << QString("%1").arg((event->pos().y() - listY) / itemHeight);
        int i = ((event->pos().y() - getY()) / itemHeight) + startPos;
        if(i < listItem.size())
        {
            itemClicked(listItem.at(i)->getMetaPaket());
            currentItem = i;
            newChildToDraw(this);
        }
    }
}

void GlTrackList::newTracks(QList<MetaPaket>list)
{
    MetaPaket mp;
    GlTrackListItem* item;
    foreach(mp, list)
    {
        item = new GlTrackListItem(this);
        item->setMetaPaket(mp);
        listItem.append(item);
    }
}

void GlTrackList::newTrack(MetaPaket mp)
{
    GlTrackListItem* item = new GlTrackListItem(this);
    item->setMetaPaket(mp);
    listItem.append(item);
}

MetaPaket GlTrackList::prevItem()
{
    MetaPaket mp;
    mp.isEmpty = true;

    if(currentItem - 1 < listItem.size() && currentItem > 0)
    {
        currentItem--;
        mp = listItem.at(currentItem)->getMetaPaket();
    }

    return mp;
}
int GlTrackList::indexOf(MetaPaket mp)
{
    MetaPaket tmp;
    for( int i = 0; i < listItem.size(); i++)
    {
        tmp = listItem.at(i)->getMetaPaket();
        if(tmp.url == mp.url)
            return i;
    }
    return -1;
}

GlTrackListItem::GlTrackListItem(GlObject *parent) : GlObject(parent)
{

}
