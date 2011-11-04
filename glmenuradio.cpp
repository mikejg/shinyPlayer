#include "glmenuradio.h"

GlMenuRadio::GlMenuRadio(GlObject* parent) : GlObject(parent)
{
    setGeometry(0,0,800,600);
    setBackGroundPixmap(QPixmap(":/images/player.png"));

    radiolist = new GlRadioList(this);
    connect(radiolist, SIGNAL(radioItemClicked(QString)), this, SIGNAL(radioItemClicked(QString)));

    buttonMain = new GlButton(this);
    buttonMain->setGeometry(3,3,48,48);
    buttonMain->setBackGroundPixmap(QPixmap(":/images/home.png"));
    connect(buttonMain, SIGNAL(clicked()), this, SIGNAL(buttonMain_clicked()));
}

void GlMenuRadio::draw(QPainter *p)
{
    drawBackGroundPixmap(p);
    radiolist->draw(p);
    buttonMain->draw(p);
}

void GlMenuRadio::mousePressEvent(QMouseEvent *event)
{
    /*Überprüft ob die Maus über einem Button gedrückt wurde und
      führt die Funktion mousePressEvent des gedrückten Buttons aus*/

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

void GlMenuRadio::mouseReleaseEvent(QMouseEvent *event)
{
    /*siehe mouseReleaseEvent*/
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

void GlMenuRadio::rollIn(QPainter *p)
{
    /*Alle Kindobjekte werden eingerollt*/

    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;

    drawImageAt(p, angle, per);
}

void GlMenuRadio::rollOut(QPainter *p)
{
    /*Alle Kindobjekte werden eingerollt*/

    int per = getPercent();
    int angle = int((per/100.)* 90);

    if(per < 0 || per > 100) return;

    drawImageAt(p, angle, per);
}

void GlMenuRadio::setLarge()
{
    /*Alles auf 1024 x 768 zoomen*/

    setGeometry(0,0,1024,768);
    backGroundPixmap = backGroundPixmap.scaled(1024, 768);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}
