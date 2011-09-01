#include "glbuttonlist.h"

GlButtonList::GlButtonList(GlObject* parent) : GlObject(parent)
{
    /*Erzeugt 26 Buttons für jeden Buchstaben im Alphabet einen*/

    GlButton* button;
    // Fuer die Buchstaben einen Zhler
    char b = 65;
    for(int zeile = 0; zeile < 7; zeile++)
       {
        for(int spalte = 0; spalte < 4; spalte++)
           {
            button = new GlButton(this);
            button->setGeometry(spalte*55,zeile*60,35,30);
            button->setBackGroundPixmap(QPixmap(":/images/button30.png"));
            button->setBackGroundPixmapPressed(QPixmap(":/images/button30_pressed.png"));
            button->setFontColor(QColor(255,255,255,128));
            button->setFontSize(20);
            button->setText(QString(&b).left(1));
            button->setObjectName(QString(&b).left(1));
            connect(button, SIGNAL(clicked()), this, SLOT(clicked()));
            buttonList.append(button);
            b++;
           }
       }
}

void GlButtonList::clicked()
{
    /*SLOT: Wird ausgeführt wenn ein Button angeklickt wurde
            QObject::sender liefert einen Zeiger auf den Absender des Signals
            Das Signal buttonClicked wird gesendet*/
    buttonClicked(sender()->objectName());
}

void GlButtonList::draw(QPainter *p)
{
    /*Zeichnet ein schwarzes Rechteck und dann die Buttons*/
    p->fillRect(geometry(), Qt::black);
    for(int i = 0; i < buttonList.size(); i++)
    {
        buttonList.at(i)->draw(p);
    }
}

void GlButtonList::mousePressEvent(QMouseEvent *event)
{
    /*Wurde die Maus innerhalb des eigenen Rechtecks gedrückt wird in
      der Liste nach einem Button gesucht und seine Funktion mousePressEvent
      aufgerufen*/

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

void GlButtonList::mouseReleaseEvent(QMouseEvent *event)
{
    /*Siehe mousePressEvent*/
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

void GlButtonList::setGeometry(int posX, int posY, int w, int h)
{
    /*Position des Buttons setzen*/
    GlObject::setGeometry(posX, posY, w, h);
    for(int i = 0; i < buttonList.size(); i++)
    {
        buttonList.at(i)->setGeometry(buttonList.at(i)->getX() + posX,
                                      buttonList.at(i)->getY() + posY,
                                      buttonList.at(i)->getWidth(),
                                      buttonList.at(i)->getHeight());
    }
    setImage();
}

void GlButtonList::setLarge()
{
    /*Alles auf 1024 x 768 zoomen. getCenter liefert den Mittelpunkt von sich.
      Der Mittelpunkt wird verschoben und die hälfte von newWidth wird von X des
      Mittelpunkts abgezogen. Das ergibt newX. Zum Schluss wird image neu gesetzt.
      Das brauchen wir für die animationen.*/

    QPoint c;
    int newX, newY, newHeight, newWidth;
    newHeight = (int)(getHeight() * 1.28);
    newWidth = (int)(getWidth() * 1.28);
    c = getCenter();
    newX = (int)(c.x() * 1.28) - (int)(newWidth / 2);
    newY = (int)(c.y() * 1.28) - (int)(newHeight / 2);
    GlObject::setGeometry(newX, newY, newWidth, newHeight);
    for(int i = 0; i < buttonList.size(); i++)
    {
        buttonList.at(i)->setLarge();
    }
    setImage();
}
