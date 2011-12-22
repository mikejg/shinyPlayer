#include "glradiolist.h"

GlRadioList::GlRadioList(GlObject* parent) : GlObject(parent)
{
    setGeometry(2,90,796,438);
    setBackGroundPixmap(QPixmap(":/images/backgroundRadio.png"));

    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;

    fontColor = QColor(255,255,255,128);
    fontSize = 30;
    itemHeight = fontSize + 10;
    currentItem = -1;

    GlRadioListItem* item = new GlRadioListItem(this);
    item->setText("Radio Unartig");
    item->setUrl("http://www.unart.tv:8000");
    connect(item, SIGNAL(clicked(QString)), this, SIGNAL(radioItemClicked(QString)));
    connect(item, SIGNAL(clicked(GlRadioListItem*)), this, SLOT(itemClicked(GlRadioListItem*)));
    list.append(item);

    item = new GlRadioListItem(this);
    item->setText("SWR 3");
    item->setUrl("http://swr.ic.llnwd.net/stream/swr_mp3_m_swr3a");
    connect(item, SIGNAL(clicked(QString)), this, SIGNAL(radioItemClicked(QString)));
    connect(item, SIGNAL(clicked(GlRadioListItem*)), this, SLOT(itemClicked(GlRadioListItem*)));
    list.append(item);
}

void GlRadioList::draw(QPainter *p)
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

    drawBackGroundPixmap(p);

    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);

    p->setPen(fontColor);
    int pos = (list.size() * itemHeight) / 2;
    pos = getHeight()/2 - pos/2;

    for(int i = 0; i < 14; i++)
    {
        if(i < list.size())
        {
            QRect re(10, getY() + pos + i * itemHeight,
                     getWidth()- 20, itemHeight);
            list.at(i)->setGeometry(re.x(),re.y(), re.width(), re.height());
            p->drawText(re, Qt::AlignHCenter, list.at(i)->getText());

            if( list.at(i)  == cItem)
              {
                p->fillRect(re, QColor(0,0,0,125));
              }
        }
    }
}

void GlRadioList::itemClicked(GlRadioListItem* item)
{
    cItem = item;
    newChildToDraw(this);
}

void GlRadioList::mouseReleaseEvent(QMouseEvent *event)
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

void GlRadioList::setLarge()
{
    fontSize = (int)(fontSize * 1.28);
    itemHeight = fontSize + 10;

    int newX, newY, newHeight, newWidth;
    QPoint c;

    newHeight = (int)(getHeight() * 1.28);
    newWidth = (int)(getWidth() * 1.28);
    c = getCenter();
    newX = (int)(c.x() * 1.28) - (int)(newWidth / 2);
    newY = (int)(c.y() * 1.28) - (int)(newHeight / 2);

    setGeometry(newX, newY, newWidth, newHeight);
    backGroundPixmap = backGroundPixmap.scaled(newWidth,newHeight);
}

GlRadioListItem::GlRadioListItem(GlObject *parent) : GlObject(parent)
{

}

void GlRadioListItem::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    clicked(url);
    clicked(this);
}
