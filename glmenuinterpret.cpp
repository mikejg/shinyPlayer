#include "glmenuinterpret.h"

GlMenuInterpret::GlMenuInterpret(GlObject* parent) : GlObject(parent)
{
    backGroundColor = QColor(Qt::black);
    setGeometry(0,0,800,600);
    setVisible(false);

    listWidget = new GlListWidget(this);
    listWidget->setGeometry(30,20,400,560);
    connect(listWidget, SIGNAL(itemClicked(QString)), this, SIGNAL(interpretSelected(QString)));
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

    buttonList = new GlButtonList(this);
    buttonList->setGeometry(530,160,200,390);
    connect(buttonList, SIGNAL(buttonClicked(QString)), this, SLOT(buttonClicked(QString)));
}

void GlMenuInterpret::buttonClicked(QString s)
{
    /*SLOT: Wird ausgeführt wenn ein Button aus der ButtonList angeklickt wird.
      - aus der Datenbank werden alle Interpreten mit dem Anfangsbuchstaben gesucht
      - die Liste der Interpreten wird an listWidget übergeben*/

    listWidget->insertItem(db->getInterpreten(s));
}

void GlMenuInterpret::draw(QPainter *p)
{
    /*Zeichnet das Menü Interpret neu
      - erstmal ein Rechteck schwarz füllen
      - alle Kindobjekte zeichenen*/

    if(backGroundColor.isValid())
    {
        p->setBrush(backGroundColor);
        p->drawRect(geometry());
    }

    for(int i = 0; i < listChilds.size(); i++)
        listChilds.at(i)->draw(p);
}

void GlMenuInterpret::mousePressEvent(QMouseEvent *event)
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

void GlMenuInterpret::mouseReleaseEvent(QMouseEvent *event)
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

void GlMenuInterpret::rollIn(QPainter *p)
{
    /*Alle Kindobjekte werden eingerollt*/

    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;


    buttonMain->drawImageAt(p, angle, per);
    buttonPlayer->drawImageAt(p, angle, per);
    listWidget->drawImageAt(p, angle, per);
    buttonList->drawImageAt(p, angle, per);
}

void GlMenuInterpret::setLarge()
{
    /*Alles auf 1024 x 768 zoomen*/

    setGeometry(0,0,1024,768);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}
