#include "glmenuplayer.h"

GlMenuPlayer::GlMenuPlayer(GlObject* parent) : GlObject(parent)
{
    setGeometry(0,0,800,600);
    setBackGroundPixmap(QPixmap(":/images/player.png"));

    trackList = new GlTrackList(this);
    trackList->setGeometry(2,90,796,438);

    buttonMain = new GlButton(this);
    buttonMain->setGeometry(3,3,48,48);
    buttonMain->setBackGroundPixmap(QPixmap(":/images/home.png"));
    connect(buttonMain, SIGNAL(clicked()), this, SIGNAL(buttonMain_clicked()));
}

void GlMenuPlayer::draw(QPainter *p)
{
    drawBackGroundPixmap(p);
    trackList->draw(p);
    buttonMain->draw(p);
}

void GlMenuPlayer::insertNewAlbum(QString interpret, QString album)
{
    QList<MetaPaket> paketList = db->getTracksFromAlbum(interpret, album);
    trackList->newTracks(paketList);

    int index = trackList->indexOf(paketList.at(0));
    if(index >= 0)
    {
        trackList->setCurrentItem(index);
        playEngine->play(paketList.at(0).url);
    }
}

void GlMenuPlayer::mousePressEvent(QMouseEvent *event)
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

void GlMenuPlayer::mouseReleaseEvent(QMouseEvent *event)
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
void GlMenuPlayer::rollIn(QPainter *p)
{
    /*Alle Kindobjekte werden eingerollt*/

    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;

    drawImageAt(p, angle, per);
}

void GlMenuPlayer::rollOut(QPainter *p)
{
    /*Alle Kindobjekte werden eingerollt*/

    int per = getPercent();
    int angle = int((per/100.)* 90);

    if(per < 0 || per > 100) return;

    drawImageAt(p, angle, per);
}
