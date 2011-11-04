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
    itemHeight = fontSize + 10;

    buttonDown = new GlButton(this);
    buttonDown->setBackGroundPixmap(QPixmap(":/images/button400.png"));
    buttonDown->setBackGroundPixmapPressed(QPixmap(":/images/button400_pressed.png"));
    connect(buttonDown, SIGNAL(clicked()), this, SLOT(buttonDown_clicked())),

    buttonUp = new GlButton(this);
    buttonUp->setBackGroundPixmap(QPixmap(":/images/button400.png"));
    buttonUp->setBackGroundPixmapPressed(QPixmap(":/images/button400_pressed.png"));
    connect(buttonUp, SIGNAL(clicked()), this, SLOT(buttonUp_clicked()));

    animation = new GlAnimation(this);
    animation->setXoffset(5);
}

void GlListWidget::buttonUp_clicked()
{
    if(startPos + 15 < listItem.size())
    {
        animation->setImage(getListImage(true));
        startPos = startPos + 15;
        animation->setImage2(getListImage(true));
        animation->startScrollUp();
    }
    else
    {
        animation->setImage(getListImage(true));
        animation->startJumpUp();
    }
}

void GlListWidget::buttonDown_clicked()
{
    if(startPos == 0)
    {
        animation->setImage(getListImage(true));
        animation->startJumpDown();
        return;
    }

    if(startPos - 15 < 0)
    {
        animation->setImage(getListImage(true));
        startPos = 0;
        animation->setImage2(getListImage(true));
        animation->startScrollDown();
        return;
    }

    animation->setImage(getListImage(true));
    startPos = startPos - 15;
    animation->setImage2(getListImage(true));
    animation->startScrollDown();
    return;
}

void GlListWidget::draw(QPainter *p)
{
    /*Zeichnet das listWidget.
      - Schwarzes Rechteck zeichenen
      - Farbverlauf für die Liste zeichnen
      - Buttons zum scrollen zeichnen
      - Text in die Liste schreiben*/

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
            QRect re(listX + 10, listY + i * itemHeight,
                     listWidth - 20, itemHeight);
            drawText(p, re, listItem.at(i+startPos)->getText());
        }
    }
}

void GlListWidget::drawText(QPainter *p, QRect rect, QString text)
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

QImage GlListWidget::getListImage(bool fullSize)
{
    /*erstellt einen Screenshot Liste. Wird zum drehen der Liste
      benötigt. Siehe auch draw(QPainter* p)*/

    QPixmap returnPixmap(listWidth, listHeight);
    QPainter p(&returnPixmap);
    p.fillRect(QRect(0,0,listWidth,listHeight), Qt::black);
    QLinearGradient gradient( listWidth/2, 0,
                              listWidth/2, listHeight);
    gradient.setColorAt(0, gradientColorAt0);
    gradient.setColorAt(1, gradientColorAt1);
    p.setBrush(QBrush(gradient));
    QPainterPath pa;
    QRect rect(0, 0, listWidth,listHeight);
    pa.addRoundedRect(rect, borderRadius, borderRadius);
    pen.setWidth(border); //Strichbreite
    pen.setColor(borderColor); //Strichfarbe
    p.setPen(pen);
    p.drawPath(pa);

    for(int i = 0; i < 16; i++)
    {
        if(i + startPos < listItem.size())
        {
            QRect re(10, i * itemHeight,
                     listWidth - 20, itemHeight);
            drawText(&p, re, listItem.at(i+startPos)->getText());
        }
    }
    p.end();

    if(!fullSize)
        returnPixmap = returnPixmap.scaled(listWidth * 0.95, listHeight * 0.95);

    return returnPixmap.toImage();
}

void GlListWidget::insertItem(QString text)
{
    //Fliegt raus, wird nichtmehr benötigt.
    GlListWidgetItem* item = new GlListWidgetItem(this);
    item->setText(text);
    listItem.append(item);
    setImage();
}

void GlListWidget::insertItem(QStringList l, bool a)
{
    /*Einfügen einer neuen QStringList. Die alte Liste dreht sich weg und die
      neue Liste dreht sich ein
      - Aktuellen Screenshot in die Animation schieben
      - Liste löschen
      - neue Liste erstellen
      - Screenshot mit der neuen Liste als zweites Bild in die Animation schieben
      - animation starten.*/

    animation->setImage(getListImage());
    listItem.clear();
    startPos = 0;
    GlListWidgetItem* item;
    for (int i = 0; i < l.size(); i++)
    {
        item = new GlListWidgetItem(this);
        item->setText(l.at(i));
        listItem.append(item);
    }
    setImage();
    if(a)
    {
        animation->setImage2(getListImage());
        animation->startRotation();
    }
}

void GlListWidget::mousePressEvent(QMouseEvent *event)
{
    /*Siehe mouseReleaseEvent*/
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
    /*Wurde die Maus innerhalb des eigenen Rechtecks gedrückt wird in
      der Liste nach einem Button oder Listeneintrag gesucht und seine
      Funktion mouseReleaseEvent aufgerufen*/
    QRect rect;
    for(int i = 0; i < listChilds.size(); i++)
       {
         rect = listChilds.at(i)->geometry();
         if(listChilds.at(i)->isVisible() && rect.contains(event->pos()))
           {
             listChilds.at(i)->mouseReleaseEvent(event);
           }
       }

    rect = QRect(listX, listY, listWidth, listHeight);
    if(rect.contains(event->pos()))
    {
        //qDebug() << QString("%1").arg((event->pos().y() - listY) / itemHeight);
        int i = ((event->pos().y() - listY) / itemHeight) + startPos;
        if(i < listItem.size())
        {
            itemClicked(listItem.at(i)->getText());
        }
    }
}

void GlListWidget::setGeometry(int posX, int posY, int w, int h)
{
    /* Buttons und Liste positionieren*/
    GlObject::setGeometry(posX,posY,w,h);

    buttonUp->setGeometry(posX,posY,400,30);
    buttonDown->setGeometry(posX, posY + h - 30, 400, 30);

    listX = posX;
    listY = posY + 35;
    listWidth = w;
    listHeight = h - 70;

    animation->setGeometry(listX-5, listY-2, listWidth+10, listHeight+4);
    setImage();
}

void GlListWidget::setLarge()
{
    /*Alles auf 1024 x 768 zoomen. getCenter liefert den Mittelpunkt von sich.
      Der Mittelpunkt wird verschoben und die hälfte von newWidth wird von X des
      Mittelpunkts abgezogen. Das ergibt newX.
      - Neue Werte setzen.
      - Buttons vergrössern
      - Liste vergrössern
      - Bereich für die Animation vergrössern
      - Image für die Animationen neu setzen.*/

    int newX, newY, newHeight, newWidth;
    QPoint c;

    fontSize = (int)(fontSize * 1.28);
    itemHeight = (int)(itemHeight * 1.28);

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

    animation->setGeometry(listX-5, listY-2, listWidth+10, listHeight+4);

    setImage();
}

GlListWidgetItem::GlListWidgetItem(GlObject* parent) : GlObject(parent)
{

}
