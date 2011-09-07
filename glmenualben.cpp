#include "glmenualben.h"

GlMenuAlben::GlMenuAlben(GlObject* parent) : GlObject(parent)
{
    backGroundColor = QColor(Qt::black);
    setGeometry(0,0,800,600);
    setVisible(false);

    pictureFlow = new GlPictureFlow(this);
}

void GlMenuAlben::draw(QPainter *p)
{
    p->setBrush(backGroundColor);
    p->drawRect(geometry());

    pictureFlow->draw(p);
}
void GlMenuAlben::mousePressEvent(QMouseEvent *event)
{
    /*Überprüft ob die Maus über einem Kindobjekt gedrückt wurde und
      führt die Funktion mousePressEvent des Kindobjekts aus*/

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

void GlMenuAlben::mouseReleaseEvent(QMouseEvent *event)
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
void GlMenuAlben::newInterpret(QString interpret)
{
    QStringList alben = db->getAlbenFromInterpret(interpret);
    pictureFlow->clear();
    pictureFlow->setPercent(0);

    QString album;
    QPixmap pixmap;
    foreach (album, alben)
    {
        pixmap = db->getCover(interpret, album);
        pictureFlow->addImage(pixmap.toImage());
    }
    pictureFlow->setAlben(alben);
    newChildToDraw(this);
}

void GlMenuAlben::setLarge()
{
    setGeometry(0,0,1024, 768);
    pictureFlow->setLarge();
}
