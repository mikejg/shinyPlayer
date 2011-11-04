#include "glcombobox.h"

GlComboBox::GlComboBox(GlObject* parent) : GlObject(parent)
{
    borderColor = QColor(66, 74, 90);
    gradientColorAt1 = QColor(40,40,40);
    gradientColorAt0 = QColor(96,112,144);
    border = 1;
    borderRadius = 7;
    fontColor = QColor(255,255,255,128);
    fontSize = 20;
    itemHeight = fontSize + 10;

    isOpen = false;
    expandUp = false;
}

void GlComboBox::clear()
{
    list.at(0)->setText("");

    /*GlComboBoxItem* item;
    for(int i = 0; i < list.size(); i++)
    {
        item = list.at(i);
        item->disconnect();
        item->setVisible(false);
    }

    list.clear();

    item = new GlComboBoxItem(this);
    item->setText("");
    item->setGeometry(getX() +10, getY(), getWidth() - 20, getHeight());
    list.append(item);
    connect(item, SIGNAL(clicked(QString)), this, SLOT(itemClicked(QString)));*/
}

void GlComboBox::draw(QPainter *p)
{
    QLinearGradient gradient(getX(), orgY + closedHeight/2,
                             getX() + getWidth(), orgY + closedHeight/2);
    gradient.setColorAt(0, gradientColorAt0);
    gradient.setColorAt(1, gradientColorAt1);
    p->setBrush(QBrush(gradient));
    QPainterPath pa;
    pa.addRoundedRect(orgRect, borderRadius, borderRadius);
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
    p->drawText(list.at(0)->geometry(), list.at(0)->getText(), QTextOption(Qt::AlignVCenter));


    if(isOpen)
    {

        QPainterPath p2;
        if(expandUp)
        {
            QLinearGradient g(getX() + getWidth()/2, orgY - itemHeight * (list.size() -1),
                              getX() + getWidth()/2, orgY - 5 );
            g.setColorAt(0, gradientColorAt1);
            g.setColorAt(1, gradientColorAt0);

            QRect rect(getX(), orgY - itemHeight * (list.size() - 1) - 10, getWidth(), itemHeight * (list.size() - 1));
            p2.addRoundedRect(rect, borderRadius, borderRadius);
            p->setBrush(QBrush(g));
        }
        else
        {
            QLinearGradient g(getX() + getWidth()/2, orgY + itemHeight+5,
                              getX() + getWidth()/2, orgY + itemHeight * list.size());
            g.setColorAt(0, gradientColorAt1);
            g.setColorAt(1, gradientColorAt0);

            QRect rect(getX(), orgY + closedHeight +5, getWidth(), itemHeight * (list.size() - 1));
            p2.addRoundedRect(rect, borderRadius, borderRadius);
            p->setBrush(QBrush(g));
        }
        p->drawPath(p2);

        p->setFont(font);

        p->setPen(fontColor);

        for(int i = 1; i < list.size(); i++)
        {
            p->drawText(list.at(i)->geometry(), list.at(i)->getText());
        }
    }

}

void GlComboBox::insertItem(QString text)
{

    GlComboBoxItem* item = new GlComboBoxItem(this);
    item->setText(text);
    list.append(item);

    item->setGeometry(getX() + 10, getY() + getHeight() + (list.indexOf(item)-1) * itemHeight + 10,
                      getWidth() - 20, itemHeight);
    connect(item, SIGNAL(clicked(QString)), this, SLOT(itemClicked(QString)));


    if(item->getY() + itemHeight > 600)
    {
        expandUp = true;
        for(int i = 1; i < list.size(); i++)
        {
            item = list.at(i);
            item->setGeometry(getX() + 10, getY() - (list.indexOf(item)) * itemHeight - 10,
                              getWidth() - 20, itemHeight);
        }
    }
}


void GlComboBox::itemClicked(QString t)
{
    isOpen = false;
    list.at(0)->setText(t);
    setHeight(closedHeight);
    setY(orgY);
    setImage();
    closed(this);

}

void GlComboBox::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << Q_FUNC_INFO;

    if(!isOpen)
    {
        isOpen = true;
        if(expandUp)
        {
            setHeight(closedHeight + 5 + itemHeight * list.size());
            setY(orgY - itemHeight * list.size());
        }
        else
            setHeight(closedHeight + 5 + itemHeight * (list.size() - 1));

        open(this);
    }

    else
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
}

void GlComboBox::setGeometry(int posX, int posY, int w, int h)
{
    GlObject::setGeometry(posX, posY, w, h);
    closedHeight = h;
    orgY = posY;
    orgRect = geometry();

    GlComboBoxItem* item = new GlComboBoxItem(this);
    item->setText("");
    item->setGeometry(posX +10, posY, w - 20, h);
    list.append(item);
    connect(item, SIGNAL(clicked(QString)), this, SLOT(itemClicked(QString)));
}

GlComboBoxItem::GlComboBoxItem(GlObject *parent) : GlObject(parent)
{

}

void GlComboBoxItem::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    Q_UNUSED(event);

    clicked(text);
}
