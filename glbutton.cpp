#include "glbutton.h"
#include <QTimer>

GlButton::GlButton(GlObject* parent) : GlObject(parent)
{
    /*Standartwerte setzen*/
    fontColor = QColor(255,255,255,128);
    fontSize = 20;
    isPressed = false;
}

void GlButton::draw(QPainter *p)
{
    /*Button je nachdem ob gedrückt oder nicht anzeigen*/
    if(isPressed)
        drawBackGroundPixmapPressed(p);
    else
        drawBackGroundPixmap(p);
    drawText(p);
}

void GlButton::drawBackGroundPixmapPressed(QPainter* p)
{
    /*Button mit dem Bild für gedrückt anzeigen*/
    if(!backGroundPixmapPressed.isNull())
      {
        p->drawPixmap(QPoint(getX(),getY()), backGroundPixmapPressed);
      }
}

void GlButton::drawText(QPainter* p)
{
    /*Text auf den Button schreiben
      - Font von QPainter holen und mit eigenen Werten überschreiben
      - Den Stift von QPainter mit der Schriftfarbe setzten
      - Text in ein Rechteck schreiben*/
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
    /*Wird ausgeführt wenn die Maus auf den Button gedrückt wird
      - isPressed auf true setzen
      - neuzeichnen des Buttons veranlassen*/
    isPressed = true;
    newChildToDraw(this);
}

void GlButton::mouseReleaseEvent(QMouseEvent *event)
{
    /*Wird ausgeführt wenn die Maus auf den Button gelöst wird
      - isPressed auf false setzen
      - neuzeichnen des Buttons veranlassen
      - nach 100 ms wird das Signal clicked gesendet*/

    isPressed = false;
    newChildToDraw(this);

    QTimer::singleShot(100,this,SIGNAL(clicked()));
}

void GlButton::setLarge()
{
    /*Alles auf 1024 x 768 zoomen. getCenter liefert den Mittelpunkt des Buttons.
      Der Mittelpunkt wird verschoben und die hälfte von newWidth wird von X des
      Mittelpunkts abgezogen. Das ergibt newX. Zum Schluss wird image neu gesetzt.
      Das brauchen wir für die animationen.*/

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
