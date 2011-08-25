#include "glmainmenu.h"

GlMainMenu::GlMainMenu(GlObject* parent) : GlObject(parent)
{
    setBackGroundPixmap(QPixmap(":/images/main.png"));
    setGeometry(0,0,800,600);

    buttonPlayer = newButton(QString("Player"), QRect(180,210,200,30));

    buttonGenre = newButton(QString("Genre"), QRect(180,260,200,30));
    connect(buttonGenre, SIGNAL(clicked()), this, SIGNAL(buttonGenre_clicked()));

    buttonInterpret = newButton(QString("Interpret"), QRect(180,310,200,30));
    connect(buttonInterpret, SIGNAL(clicked()), this, SIGNAL(buttonInterpret_clicked()));

    buttonPlaylist = newButton(QString("Playlist"), QRect(180,360,200,30));

    buttonSampler = newButton(QString("Sampler"), QRect(420,210,200,30));

    buttonRadio = newButton(QString("Radio"), QRect(420, 260, 200, 30));

    buttonQuick = newButton(QString("Quick & Dirty"), QRect(420, 310,200,30));

    buttonSetting = newButton(QString("Setting"), QRect(420,360,200,30));
}

void GlMainMenu::draw(QPainter *p)
{
    drawBackGroundPixmap(p);

    for(int i = 0; i < listChilds.size(); i++)
        listChilds.at(i)->draw(p);
}

void GlMainMenu::mousePressEvent(QMouseEvent *event)
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

void GlMainMenu::mouseReleaseEvent(QMouseEvent *event)
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

GlButton* GlMainMenu::newButton(QString text, QRect rect)
{
    GlButton* button = new GlButton(this);
    button->setBackGroundPixmap(QPixmap(":/images/button.png"));
    button->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    button->setText(text);
    button->setGeometry(rect.x(), rect.y(), rect.width(), rect.height());
    button->setImage();

    return button;
}

void GlMainMenu::rollOut(QPainter *p)
{
    int per = getPercent();
    int angle = int((per/100.)*90);

    if(per < 0 || per > 100) return;

    buttonPlayer->drawImageAt(p, angle, per);
    buttonGenre->drawImageAt(p, angle, per);
    buttonInterpret->drawImageAt(p, angle, per);
    buttonPlaylist->drawImageAt(p, angle, per);
    buttonSampler->drawImageAt(p, angle, per);
    buttonRadio->drawImageAt(p, angle, per);
    buttonQuick->drawImageAt(p, angle, per);
    buttonSetting->drawImageAt(p, angle, per);

}

void GlMainMenu::setLarge()
{
    setGeometry(0,0,1024,768);
    backGroundPixmap = backGroundPixmap.scaled(1024,768);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}
