#include "globject.h"

GlObject::GlObject(GlObject* parent) : QObject(parent)
{
    visible = true;
    percent = -1;

    if(parent)
    {
        glParent = parent;
        glParent->addChild(this);

        /*mit einer Signal zu Signal Verbindung wird das Signal durch alle Ebenen
          zu einem SLOT von GLWidget MainWindow geschossen*/
        connect(this, SIGNAL(newChildToDraw(GlObject*)), parent, SIGNAL(newChildToDraw(GlObject*)));
        connect(this, SIGNAL(update()), parent, SIGNAL(update()));
    }
}

void GlObject::drawImageAt(QPainter *p, int angle, int per)
{
    /*Zeichnet das Image (Screenshot des Objekts) um die X-Achse gedreht*/
    p->save();
    int w = img.width() - int((per/100.) * (img.width() * 0.2));
    int h = img.height() - int((per/100.) * (img.height() * 0.2));

    QPoint loc = getCenter();
    QTransform trans;
     trans.rotate(angle, Qt::XAxis);
    trans.scale(qreal(w)/img.width(), qreal(h)/img.height());
    p->setTransform(trans * QTransform().translate(loc.x(),loc.y()),true);
    QPointF pt(-img.width()/2, -img.height()/2);
    p->drawImage(pt, img);
    p->restore();
}

void GlObject::drawImageAtY(QPainter *p, int angle, int per)
{
    /*Zeichnet das Image (Screenshot des Objekts) um die Y-Achse gedreht*/
    p->save();
    int w = img.width() - int((per/100.) * (img.width() * 0.2));
    int h = img.height() - int((per/100.) * (img.height() * 0.2));

    QPoint loc = getCenter();
    QTransform trans;
     trans.rotate(angle, Qt::YAxis);
    trans.scale(qreal(w)/img.width(), qreal(h)/img.height());
    p->setTransform(trans * QTransform().translate(loc.x(),loc.y()),true);
    QPointF pt(-img.width()/2, -img.height()/2);
    p->drawImage(pt, img);
    p->restore();
}

void GlObject::drawBackGroundPixmap(QPainter* p)
{
    /*Zeichnet das Hintergrundbild*/
    if(!backGroundPixmap.isNull())
      {
        p->drawPixmap(QPoint(x,y), backGroundPixmap);
      }
}

QPoint GlObject::getCenter()
{
    /*Liefert den Mittelpunkt des Objects*/
    return QPoint( x + width/2, y + height/2);
}

QPixmap GlObject::getPixmap()
{
    /*Zeichnet sich in ein Pixmap und gibt diese zurück*/
    QPixmap returnPixmap(width, height);

    //ins Pixmap zeichnen
    QPainter p(&returnPixmap);
    p.translate(QPoint(-x,-y));
    draw(&p);

    return returnPixmap;
}

bool GlObject::isVisible()
{
    return visible;
}

void GlObject::setGeometry(int posX, int posY, int w, int h)
{
    x = posX;
    y = posY;
    width = w;
    height = h;
}

void GlObject::setImage()
{
    /*Zeichnet sich selber. Img ist somit ein Screenshot von sich selber
      der für die Animationen gebrauch wird*/
    img = getPixmap().toImage();
}
