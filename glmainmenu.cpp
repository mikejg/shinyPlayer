#include "glmainmenu.h"

GlMainMenu::GlMainMenu(GlObject* parent) : GlObject(parent)
{
    //setBackGroundPixmap(QPixmap(":/images/main.png"));
    setGeometry(0,0,800,600);

    balkenOben = QPixmap(":/images/mainBalkenOben.png");
    yBalkenOben = 145;

    balkenUnten = QPixmap(":/images/mainBalkenUnten.png");
    yBalkenUnten = 470;

    buttonPlayer = newButton(QString("Player"), QRect(180,210,200,30));
    connect(buttonPlayer, SIGNAL(clicked()), this, SIGNAL(buttonPlayer_clicked()));

    buttonGenre = newButton(QString("Genre"), QRect(180,260,200,30));
    connect(buttonGenre, SIGNAL(clicked()), this, SIGNAL(buttonGenre_clicked()));

    buttonInterpret = newButton(QString("Interpret"), QRect(180,310,200,30));
    connect(buttonInterpret, SIGNAL(clicked()), this, SIGNAL(buttonInterpret_clicked()));

    buttonPlaylist = newButton(QString("Playlist"), QRect(180,360,200,30));
    connect(buttonPlaylist, SIGNAL(clicked()), this, SIGNAL(buttonPlaylist_clicked()));

    buttonSampler = newButton(QString("Sampler"), QRect(420,210,200,30));
    connect(buttonSampler, SIGNAL(clicked()), this, SIGNAL(buttonSampler_clicked()));

    buttonRadio = newButton(QString("Radio"), QRect(420, 260, 200, 30));
    connect(buttonRadio, SIGNAL(clicked()), this, SIGNAL(buttonRadio_clicked()));

    buttonQuick = newButton(QString("Quick & Dirty"), QRect(420, 310,200,30));
    connect(buttonQuick, SIGNAL(clicked()), this, SIGNAL(buttonQuick_clicked()));

    buttonSetting = newButton(QString("Setting"), QRect(420,360,200,30));
    connect(buttonSetting, SIGNAL(clicked()), this, SIGNAL(buttonSetting_clicked()));
    
    buttonPause = new GlButton(this);
    buttonPause->setGeometry(370,540,63,50);
    connect(buttonPause, SIGNAL(clicked()), this, SLOT(buttonPause_clicked()));
}


void GlMainMenu::buttonPause_clicked()
{
    qDebug("MainMenu, buttonPause clicked");
    system("/usr/sbin/pm-suspend");
}
void GlMainMenu::draw(QPainter *p)
{
    /*Zeichnet das Hauptmenü
      - Hintergrundbild zeichnen
      - Alle Buttons zeichnen*/

    //drawBackGroundPixmap(p);
    p->setBrush(Qt::black);
    p->drawRect(geometry());

    p->drawPixmap(0,yBalkenOben - balkenOben.height()/2, balkenOben);
    p->drawPixmap(0,yBalkenUnten - balkenUnten.height()/2, balkenUnten);

    for(int i = 0; i < listChilds.size(); i++)
        listChilds.at(i)->draw(p);
}

void GlMainMenu::mousePressEvent(QMouseEvent *event)
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

void GlMainMenu::mouseReleaseEvent(QMouseEvent *event)
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

GlButton* GlMainMenu::newButton(QString text, QRect rect)
{
    /*erstellet einen Button und gibt den Zeiger auf den Button zurück
      - Zeiger auf GlButton erstellen
      - Hintergrundbild setzen
      - Hintergrundbild für gedrücktem zustand setzen
      - Text setzen
      - Postion des Buttons setzen
      - Image setzen. Wird für die Animation gebrauch*/

    GlButton* button = new GlButton(this);
    button->setBackGroundPixmap(QPixmap(":/images/button.png"));
    button->setBackGroundPixmapPressed(QPixmap(":/images/button_pressed.png"));
    button->setText(text);
    button->setGeometry(rect.x(), rect.y(), rect.width(), rect.height());
    button->setImage();

    return button;
}

void GlMainMenu::rollIn(QPainter *p)
{
    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;

    buttonPlayer->drawImageAt(p, angle, per);
    buttonGenre->drawImageAt(p, angle, per);
    buttonInterpret->drawImageAt(p, angle, per);
    buttonPlaylist->drawImageAt(p, angle, per);
    buttonSampler->drawImageAt(p, angle, per);
    buttonRadio->drawImageAt(p, angle, per);
    buttonQuick->drawImageAt(p, angle, per);
    buttonSetting->drawImageAt(p, angle, per);

    QPixmap pm;
    pm = balkenOben.scaled(balkenOben.width(), balkenOben.height() - (per/100.)*balkenOben.height());
    p->drawPixmap(0, yBalkenOben - pm.height()/2, pm);

    pm = balkenUnten.scaled(balkenUnten.width(), balkenUnten.height() - (per/100.)*balkenUnten.height());
    p->drawPixmap(0, yBalkenUnten - pm.height()/2, pm);
}

void GlMainMenu::rollOut(QPainter *p)
{
    /*Ale Buttons werden weggerollt*/

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

    QPixmap pm;
    pm = balkenOben.scaled(balkenOben.width(), balkenOben.height() - (per/100.)*balkenOben.height());
    p->drawPixmap(0, yBalkenOben - pm.height()/2, pm);

    pm = balkenUnten.scaled(balkenUnten.width(), balkenUnten.height() - (per/100.)*balkenUnten.height());
    p->drawPixmap(0, yBalkenUnten - pm.height()/2, pm);
}

void GlMainMenu::setLarge()
{
    /*Alles auf 1024 x 768 zoomen
      - Hintergrundbild scalieren
      - Alle Buttons vergrössern*/

    setGeometry(0,0,1024,768);
    //backGroundPixmap = backGroundPixmap.scaled(1024,768);

    yBalkenOben = yBalkenOben * 1.28;
    yBalkenUnten = yBalkenUnten * 1.28;

    balkenOben = balkenOben.scaled(1024, 63);
    balkenUnten = balkenUnten.scaled(1024, 102);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}
