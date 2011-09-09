#include "glmenualben.h"

GlMenuAlben::GlMenuAlben(GlObject* parent) : GlObject(parent)
{
    backGroundColor = QColor(Qt::black);
    setGeometry(0,0,800,600);
    setVisible(false);

    pictureFlow = new GlPictureFlow(this);
    connect(pictureFlow, SIGNAL(albumClicked(QString)), this, SLOT(albumSelected(QString)));

    buttonInterpret = new GlButton(this);
    buttonInterpret->setGeometry(550,480,200,30);
    buttonInterpret->setBackGroundPixmap(QPixmap(":/images/button.png"));
    buttonInterpret->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    buttonInterpret->setText("Interpret");
    buttonInterpret->setImage();
    connect(buttonInterpret, SIGNAL(clicked()), this, SLOT(buttonInterpret_clicked()));

    buttonMain = new GlButton(this);
    buttonMain->setGeometry(50,420,200,30);
    buttonMain->setBackGroundPixmap(QPixmap(":/images/button.png"));
    buttonMain->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    buttonMain->setText("Main");
    buttonMain->setImage();
    connect(buttonMain, SIGNAL(clicked()), this, SLOT(buttonMain_clicked()));

    buttonPlayer = new GlButton(this);
    buttonPlayer->setGeometry(50,480,200,30);
    buttonPlayer->setBackGroundPixmap(QPixmap(":/images/button.png"));
    buttonPlayer->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    buttonPlayer->setText("Player");
    buttonPlayer->setImage();
    connect(buttonPlayer, SIGNAL(clicked()), this, SLOT(buttonPlayer_clicked()));
}

void GlMenuAlben::albumSelected(QString album)
{
    newAlbumSelected(stringInterpret, album);
}

void GlMenuAlben::buttonInterpret_clicked()
{
    pictureFlow->setImage();
    backToInterpret();
}

void GlMenuAlben::buttonMain_clicked()
{
    pictureFlow->setImage();
    backToMain();
}

void GlMenuAlben::buttonPlayer_clicked()
{
    pictureFlow->setImage();
    backToPlayer();
}

void GlMenuAlben::draw(QPainter *p)
{
    p->setBrush(backGroundColor);
    p->drawRect(geometry());

    pictureFlow->draw(p);
    buttonPlayer->draw(p);
    buttonMain->draw(p);
    buttonInterpret->draw(p);
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
    stringInterpret = interpret;
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
    pictureFlow->setImage();

    //newChildToDraw(this);
}

void GlMenuAlben::rollOut(QPainter *p)
{
    int per = getPercent();
    int angle = int((per/100.)* 90);

    if(per < 0 || per > 100) return;

    buttonMain->drawImageAt(p, angle, per);
    buttonPlayer->drawImageAt(p, angle, per);
    buttonInterpret->drawImageAt(p, angle, per);
    pictureFlow->drawImageAt(p, angle, per);
}

void GlMenuAlben::rollIn(QPainter *p)
{
    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;

    buttonMain->drawImageAt(p, angle, per);
    buttonPlayer->drawImageAt(p, angle, per);
    buttonInterpret->drawImageAt(p, angle, per);
    pictureFlow->drawImageAt(p, angle, per);
}

void GlMenuAlben::setLarge()
{
    setGeometry(0,0,1024, 768);
    pictureFlow->setLarge();

    buttonMain->setLarge();
    buttonInterpret->setLarge();
    buttonPlayer->setLarge();
}
