#include "glmenuplayer.h"

GlMenuPlayer::GlMenuPlayer(GlObject* parent) : GlObject(parent)
{
    setGeometry(0,0,800,600);
    setBackGroundPixmap(QPixmap(":/images/player.png"));

    trackList = new GlTrackList(this);
    trackList->setGeometry(2,90,796,438);
    connect(trackList, SIGNAL(itemClicked(MetaPaket)), this, SLOT(playTrackListItem(MetaPaket)));

    buttonMain = new GlButton(this);
    buttonMain->setGeometry(3,3,48,48);
    buttonMain->setBackGroundPixmap(QPixmap(":/images/home.png"));
    connect(buttonMain, SIGNAL(clicked()), this, SIGNAL(buttonMain_clicked()));

    buttonDown = new GlButton(this);
    buttonDown->setGeometry(473,551,31,31);
    connect(buttonDown, SIGNAL(clicked()), this, SLOT(buttonDown_clicked()));

    buttonUp = new GlButton(this);
    buttonUp->setGeometry(298,551,31,31);
    connect(buttonUp, SIGNAL(clicked()), this, SLOT(buttonUp_clicked()));

    buttonFor = new GlButton(this);
    buttonFor->setGeometry(433,551,40,31);
    connect(buttonFor, SIGNAL(clicked()), this, SLOT(nextSong()));

    buttonBack = new GlButton(this);
    buttonBack->setGeometry(330,551,40,31);
    connect(buttonBack, SIGNAL(clicked()), this, SLOT(prevSong()));

    buttonPause = new GlButton(this);
    buttonPause->setGeometry(370,540,63,50);

    buttonClear = new GlButton(this);
    buttonClear->setGeometry(749,3,48,48);
    buttonClear->setBackGroundPixmap(QPixmap(":/images/clear.png"));
    connect(buttonClear, SIGNAL(clicked()), trackList, SLOT(clear()));
    animation = new GlAnimation(this);
    animation->setGeometry(2,90,796,438);
}

void GlMenuPlayer::buttonDown_clicked()
{
    if(trackList->getStartPos() + 15 < trackList->getListSize())
    {
        trackList->setImage();
        animation->setImage(trackList->getImage());
        trackList->setStartPos( trackList->getStartPos() + 15);
        trackList->setImage();
        animation->setImage2(trackList->getImage());
        animation->startScrollUp();
    }
    else
    {
        trackList->setImage();
        animation->setImage(trackList->getImage());
        animation->startJumpUp();
    }
}

void GlMenuPlayer::buttonUp_clicked()
{
    if(trackList->getStartPos() == 0)
    {
        trackList->setImage();
        animation->setImage(trackList->getImage());
        animation->startJumpDown();
        return;
    }

    if(trackList->getStartPos() - 15 < 0)
    {
        trackList->setImage();
        animation->setImage(trackList->getImage());
        trackList->setStartPos(0);
        trackList->setImage();
        animation->setImage2(trackList->getImage());
        animation->startScrollDown();
        return;
    }

    trackList->setImage();
    animation->setImage(trackList->getImage());
    trackList->setStartPos( trackList->getStartPos() -15);
    trackList->setImage();
    animation->setImage2(trackList->getImage());
    animation->startScrollDown();
    return;
}

void GlMenuPlayer::draw(QPainter *p)
{
    drawBackGroundPixmap(p);
    trackList->draw(p);
    buttonMain->draw(p);
    buttonClear->draw(p);
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

void GlMenuPlayer::insertNewPlaylist(QString pl)
{
    QList<MetaPaket> paketList = db->getTracksFromPlaylist(pl);
    trackList->newTracks(paketList);

    int index = trackList->indexOf(paketList.at(0));
    if(index >= 0)
    {
        trackList->setCurrentItem(index);
        playEngine->play(paketList.at(0).url);
    }
}

void GlMenuPlayer::insertNewSampler(QString sampler)
{
    QList<MetaPaket> paketList = db->getTracksFromSampler(sampler);
    trackList->newTracks(paketList);

    int index = trackList->indexOf(paketList.at(0));
    if(index >= 0)
    {
        trackList->setCurrentItem(index);
        playEngine->play(paketList.at(0).url);
    }
}
void GlMenuPlayer::insertNewTitle(MetaPaket mp)
{
    trackList->newTrack(mp);
    trackList->setCurrentItem(trackList->indexOf(mp));
    playEngine->play(mp.url);
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

void GlMenuPlayer::nextSong()
{
    MetaPaket mp = trackList->nextItem();

    if(!mp.isEmpty)
    {
        playEngine->play(mp.url);
    }

    if(this->isVisible() && trackList->isVisible())
        newChildToDraw(trackList);
}

void GlMenuPlayer::playTrackListItem(MetaPaket mp)
{
    playEngine->play(mp.url);
}

void GlMenuPlayer::prevSong()
{
    MetaPaket mp = trackList->prevItem();

    if(!mp.isEmpty)
    {
        playEngine->play(mp.url);
    }

    if(this->isVisible() && trackList->isVisible())
        newChildToDraw(trackList);
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

void GlMenuPlayer::setPlayEngine(Play_Engine *pe)
{
    playEngine = pe;

    connect(playEngine, SIGNAL(finished()), this, SLOT(nextSong()));
    connect(buttonPause, SIGNAL(clicked()), playEngine, SLOT(pause()));
}
