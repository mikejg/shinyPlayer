#include "glmenusampler.h"

GlMenuSampler::GlMenuSampler(GlObject* parent) : GlObject(parent)
{
    backGroundColor = QColor(Qt::black);
    setGeometry(0,0,800,600);
    setVisible(false);

    listWidget = new GlListWidget(this);
    listWidget->setGeometry(30,20,400,560);
    connect(listWidget, SIGNAL(itemClicked(QString)), this, SIGNAL(samplerSelected(QString)));
    //listWidget->setImage();

    buttonMain = new GlButton(this);
    buttonMain->setGeometry(530, 48,200,30);
    buttonMain->setBackGroundPixmap(QPixmap(":/images/button.png"));
    buttonMain->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    buttonMain->setText("Main");
    buttonMain->setImage();
    connect(buttonMain, SIGNAL(clicked()), this, SIGNAL(buttonMainClicked()));

    buttonPlayer = new GlButton(this);
    buttonPlayer->setGeometry(530,108,200,30);
    buttonPlayer->setBackGroundPixmap(QPixmap(":/images/button.png"));
    buttonPlayer->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    buttonPlayer->setText("Player");
    buttonPlayer->setImage();
    connect(buttonPlayer, SIGNAL(clicked()), this, SIGNAL(buttonPlayerClicked()));
}

void GlMenuSampler::draw(QPainter *p)
{
    if(backGroundColor.isValid())
    {
        p->setBrush(backGroundColor);
        p->drawRect(geometry());
    }

    for(int i = 0; i < listChilds.size(); i++)
        listChilds.at(i)->draw(p);
}

void GlMenuSampler::mousePressEvent(QMouseEvent *event)
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

void GlMenuSampler::mouseReleaseEvent(QMouseEvent *event)
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

void GlMenuSampler::rollIn(QPainter *p)
{
    /*Alle Kindobjekte werden eingerollt*/

    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;


    buttonMain->drawImageAt(p, angle, per);
    buttonPlayer->drawImageAt(p, angle, per);
    listWidget->drawImageAt(p, angle, per);
}

void GlMenuSampler::rollOut(QPainter *p)
{
    int per = getPercent();
    int angle = int((per/100.) * 90);

    if(per < 0 || per > 100) return;


    buttonMain->drawImageAt(p, angle, per);
    buttonPlayer->drawImageAt(p, angle, per);
    listWidget->drawImageAt(p, angle, per);
}

void GlMenuSampler::setDatabase(Database *d)
{
    db = d;
    listWidget->insertItem(db->getSampler(), false);
}

void GlMenuSampler::setLarge()
{
    /*Alles auf 1024 x 768 zoomen*/

    setGeometry(0,0,1024,768);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}
