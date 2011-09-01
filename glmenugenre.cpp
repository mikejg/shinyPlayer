#include "glmenugenre.h"

GlMenuGenre::GlMenuGenre(GlObject* parent) : GlObject(parent)
{
    backGroundColor = QColor(Qt::black);
    setGeometry(0,0,800,600);
    setVisible(false);

    listWidget = new GlListWidget(this);
    listWidget->setGeometry(30,20,400,560);
    //listWidget->setImage();

    buttonMain = new GlButton(this);
    buttonMain->setGeometry(530, 48,200,30);
    buttonMain->setBackGroundPixmap(QPixmap(":/images/button.png"));
    buttonMain->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    buttonMain->setText("Main");
    buttonMain->setImage();

    buttonPlayer = new GlButton(this);
    buttonPlayer->setGeometry(530,108,200,30);
    buttonPlayer->setBackGroundPixmap(QPixmap(":/images/button.png"));
    buttonPlayer->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    buttonPlayer->setText("Player");
    buttonPlayer->setImage();

}

void GlMenuGenre::draw(QPainter *p)
{
    if(backGroundColor.isValid())
    {
        p->setBrush(backGroundColor);
        p->drawRect(geometry());
    }

    for(int i = 0; i < listChilds.size(); i++)
        listChilds.at(i)->draw(p);
}

void GlMenuGenre::mousePressEvent(QMouseEvent *event)
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

void GlMenuGenre::mouseReleaseEvent(QMouseEvent *event)
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

void GlMenuGenre::rollIn(QPainter *p)
{

    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;
        qDebug() << QString("%1").arg(per);

    buttonMain->drawImageAt(p, angle, per);
    buttonPlayer->drawImageAt(p, angle, per);
    listWidget->drawImageAt(p, angle, per);
}

void GlMenuGenre::setLarge()
{
    setGeometry(0,0,1024,768);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}
