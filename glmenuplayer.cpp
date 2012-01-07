#include "glmenuplayer.h"
#include <QTimer>
#include <QDateTime>
#include "time.h"

GlMenuPlayer::GlMenuPlayer(GlObject* parent) : GlObject(parent)
{
    setGeometry(0,0,800,600);
    setBackGroundPixmap(QPixmap(":/images/player.png"));

    srand( (unsigned) time(NULL) ) ;

    ledArtist = false;
    ledBoom = new LedBoom(this);
    connect(ledBoom, SIGNAL(newUsbDevice()), this, SLOT(newUsbDevice()));

    fontColor = QColor(255,255,255,128);
    fontSize = 20;

    trackList = new GlTrackList(this);
    viewObject = trackList;
    trackList->setGeometry(2,90,796,438);
    trackList->setVisible(true);
    connect(trackList, SIGNAL(itemClicked(MetaPaket)), this, SLOT(playTrackListItem(MetaPaket)));

    coverView = new GlCoverView(this);
    coverView->setGeometry(2,90,796,438);
    coverView->setVisible(false);

    infoView = new GlInfoView(this);
    infoView->setGeometry(2,90,796,438);
    infoView->setVisible(false);
    connect(infoView, SIGNAL(setNewPoints(MetaPaket)), this, SLOT(setNewPoints(MetaPaket)));

    vizualizer = new GlVizualizer(this);
    vizualizer->setGeometry(2,90,796,438);
    vizualizer->setVisible(false);
    vizualizer->setStopIt(true);

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

    comboBoxView = new GlComboBox(this);
    comboBoxView->setGeometry(645,12,100,30);
    comboBoxView->setFirstText(QString("List"));
    comboBoxView->setImage();
    connect(comboBoxView, SIGNAL(open(GlComboBox*)), this, SLOT(comboBoxOpen(GlComboBox*)));
    connect(comboBoxView, SIGNAL(closed(GlComboBox*)), this, SLOT(comboBoxClosed(GlComboBox*)));
    comboBoxView->insertItem(QString("List"));
    comboBoxView->insertItem(QString("Cover"));
    comboBoxView->insertItem(QString("Info"));
    comboBoxView->insertItem(QString("Viz"));
    cbViewString = "List";

    comboBoxLed = new GlComboBox(this);
    comboBoxLed->setGeometry(55,12,150,30);
    comboBoxLed->setFirstText("LED");
    comboBoxLed->setImage();
    comboBoxLed->insertItem(QString("Time"));
    comboBoxLed->insertItem(QString("Artist"));
    comboBoxLed->insertItem(QString("Boom"));
    comboBoxLed->insertItem(QString("Animation"));

    connect(comboBoxLed, SIGNAL(open(GlComboBox*)), this, SLOT(comboBoxLedOpen(GlComboBox*)));
    connect(comboBoxLed, SIGNAL(closed(GlComboBox*)), this, SLOT(comboBoxLedClosed(GlComboBox*)));

    timer_ledAnimation = new QTimer(this);
    timer_ledAnimation->setSingleShot(true);
    connect(timer_ledAnimation, SIGNAL(timeout()), this, SLOT(ledTimer_Animation_timeout()));

    timer_ledTime = new QTimer(this);
    timer_ledTime->setSingleShot(true);
    connect(timer_ledTime, SIGNAL(timeout()), this, SLOT(ledTimer_Time_timeout()));
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

void GlMenuPlayer::comboBoxClosed(GlComboBox* cb)
{

    for(int i = 0; i < listChilds.size(); i++)
       {
         listChilds.at(i)->setVisible(true);
       }

    trackList->setVisible(false);
    coverView->setVisible(false);
    infoView->setVisible(false);
    vizualizer->setStopIt(true);
    vizualizer->setVisible(false);

    disconnect(playEngine, SIGNAL(dataReady(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)),
            vizualizer, SLOT(insertScope(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)));

    if(cbViewString == QString("List"))
    {
        trackList->setImage();
        animation->setImage( trackList->getImage());
    }

    if(cbViewString == QString("Cover"))
    {
        coverView->setImage();
        animation->setImage(coverView->getImage());
    }

    if(cbViewString == QString("Info"))
    {
        infoView->setImage();
        animation->setImage(infoView->getImage());
    }

    if(cb->getText() == QString("Cover"))
    {
        coverView->setVisible(true);
        coverView->setCoverUrl(playEngine->coverUrl());
        coverView->setImage();
        animation->setImage2(coverView->getImage());
        viewObject = coverView;
    }

    if(cb->getText() == QString("List"))
    {
        trackList->setVisible(true);
        trackList->setImage();
        animation->setImage2(trackList->getImage());
        viewObject = trackList;
    }

    if(cb->getText() == QString("Info"))
    {
        infoView->setMetaPaket( playEngine->getMetaPaket());
        infoView->setVisible(true);
        infoView->setImage();
        animation->setImage2(infoView->getImage());
        viewObject = infoView;
    }

    if(cb->getText() == QString("Viz"))
    {
        vizualizer->setVisible(true);
        vizualizer->setImage();
        vizualizer->setStopIt(false);
        animation->setImage2(vizualizer->getImage());
        viewObject = vizualizer;
        connect(playEngine, SIGNAL(dataReady(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)),
                vizualizer, SLOT(insertScope(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)));
        QTimer::singleShot(500, vizualizer, SLOT(doit()));
    }

    cbViewString = cb->getText();
    newChildToDraw(cb);

    animation->startScrollDown();
}

void GlMenuPlayer::comboBoxOpen(GlComboBox* cb)
{
    for(int i = 0; i < listChilds.size(); i++)
       {
         listChilds.at(i)->setVisible(false);
       }

    cb->setVisible(true);
    newChildToDraw(cb);
}

void GlMenuPlayer::comboBoxLedClosed(GlComboBox *cb)
{
    buttonMain->setVisible(true);
    buttonDown->setVisible(true);
    buttonUp->setVisible(true);
    buttonFor->setVisible(true);
    buttonBack->setVisible(true);
    buttonPause->setVisible(true);
    buttonClear->setVisible(true);
    comboBoxView->setVisible(true);

    ledArtist = false;
    ledAnimation = false;
    ledTime = false;

    timer_ledAnimation->stop();
    timer_ledTime->stop();

    ledBoom->setStopIt(true);

    disconnect(playEngine, SIGNAL(dataReady(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)),
            ledBoom, SLOT(insertScope(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)));
    if(cb->getText() == QString("Time"))
    {
        ledTime = true;
        ledStartTime();
        timer_ledTime->start(300000);
    }

    if(cb->getText() == QString("Artist"))
    {
        ledArtist = true;
        ledLaufschrift(playEngine->getMetaPaket().interpret);
    }

    if(cb->getText() == QString("Boom"))
    {
        connect(playEngine, SIGNAL(dataReady(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)),
                ledBoom, SLOT(insertScope(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)));
        ledBoom->setStopIt(false);
        ledBoom->clearLed();
        ledBoom->doit();
    }

    if(cb->getText() == QString("Animation"))
    {
        ledAnimation = true;
        ledPlayAnimation();
        timer_ledAnimation->start(30000);
    }

    viewObject->setVisible(true);
    newChildToDraw(this);
}

void GlMenuPlayer::comboBoxLedOpen(GlComboBox *cb)
{
    for(int i = 0; i < listChilds.size(); i++)
       {
         listChilds.at(i)->setVisible(false);
       }

    cb->setVisible(true);
    newChildToDraw(cb);
}

char GlMenuPlayer::convertASCII_to_FlashTable(char c)
{
    //Nur Grossbuchstaben
    if(c > 96 && c < 123)
    {
        c = c - 32;
        //A ist im Flash 0, B = 1, usw
        c = c - 65;
        return c;
    }

    //A ist im Flash 0, B = 1 usw
    if(c > 64 && c < 91)
        return c - 65;

    //Leerzeichen ist im Flash 26
    if (c == 32)
        return 26;

    //Der Rest wird Leerzeichen
        return 26;

}

void GlMenuPlayer::draw(QPainter *p)
{
    drawBackGroundPixmap(p);
    if(trackList->isVisible())
        trackList->draw(p);
    if(coverView->isVisible())
        coverView->draw(p);
    if(infoView->isVisible())
        infoView->draw(p);
    buttonMain->draw(p);
    buttonClear->draw(p);
    comboBoxView->draw(p);
    comboBoxLed->draw(p);

    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);

    p->setPen(fontColor);
    QRect re(0,55,800,30);
    p->drawText(re, Qt::AlignHCenter, infoString);
}

void GlMenuPlayer::insertNewAlbum(QString interpret, QString album)
{
    QList<MetaPaket> paketList = db->getTracksFromAlbum(interpret, album);
    trackList->newTracks(paketList);

    int index = trackList->indexOf(paketList.at(0));
    if(index >= 0)
    {
        trackList->setCurrentItem(index);
        playEngine->play(paketList.at(0));
        infoString = paketList.at(0).interpret +
                     " - " +
                    paketList.at(0).title;

        if(coverView->isVisible())
            coverView->setCoverUrl(paketList.at(0).coverUrl);

        if(infoView->isVisible())
            infoView->setMetaPaket(paketList.at(0));
    }
}

void GlMenuPlayer::insertNewPlaylist(QString pl)
{
    QList<MetaPaket> paketList = db->getTracksFromPlaylist(pl);
    trackList->newTracks(paketList);

    int index = trackList->indexOf(paketList.at(0));

    for(int i = 0; i < paketList.size(); i++)
        qDebug() << paketList.at(i).coverUrl;

    if(index >= 0)
    {
        trackList->setCurrentItem(index);
        playEngine->play(paketList.at(0));
        infoString = paketList.at(0).interpret +
                     " - " +
                    paketList.at(0).title;

        if(coverView->isVisible())
            coverView->setCoverUrl(paketList.at(0).coverUrl);

        if(infoView->isVisible())
            infoView->setMetaPaket(paketList.at(0));

        //qDebug() << paketList.at(0).coverUrl;
    }
}
void GlMenuPlayer::insertNewQuick(int y1, int y2, uint pastTime, int point, bool boolRandom)
{
    QList<MetaPaket> paketList = db->getTracksFromQuick(y1, y2, pastTime, point, boolRandom);
    trackList->newTracks(paketList);

    int index = trackList->indexOf(paketList.at(0));

    for(int i = 0; i < paketList.size(); i++)
        qDebug() << paketList.at(i).coverUrl;

    if(index >= 0)
    {
        trackList->setCurrentItem(index);
        playEngine->play(paketList.at(0));
        infoString = paketList.at(0).interpret +
                     " - " +
                    paketList.at(0).title;

        if(coverView->isVisible())
            coverView->setCoverUrl(paketList.at(0).coverUrl);

        if(infoView->isVisible())
            infoView->setMetaPaket(paketList.at(0));

        //qDebug() << paketList.at(0).coverUrl;
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
        playEngine->play(paketList.at(0));
        infoString = paketList.at(0).interpret +
                     " - " +
                    paketList.at(0).title;
        if(coverView->isVisible())
            coverView->setCoverUrl(paketList.at(0).coverUrl);
    }
}
void GlMenuPlayer::insertNewTitle(MetaPaket mp)
{
    trackList->newTrack(mp);
    trackList->setCurrentItem(trackList->indexOf(mp));
    infoString = mp.interpret +
                 " - " +
                mp.title;
    if(coverView->isVisible())
        coverView->setCoverUrl(mp.coverUrl);
    playEngine->play(mp);
}

void GlMenuPlayer::ledLaufschrift(QString lt)
{
    if(dev == NULL) return;

    QByteArray text = lt.toLocal8Bit();
    char *data = new char[text.size() + 1];
    strcpy(data, text.data());

    bzero(buffer, sizeof(buffer));
    buffer[1] = 1;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der vorbereitung");
        return;
    }

    bzero(buffer, sizeof(buffer));

    for ( int i = 1; i < 9; i++)
    {
        if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
        {
            qDebug("Fehler bei nullchunk");
            return;
        }
    }

    bzero(buffer, sizeof(buffer));

    buffer[1] = 8;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der vorbereitung");
        //usbhidCloseDevice(dev);
        return;
    }

    bzero(buffer, sizeof(buffer));

    strncpy(&buffer[1], data , strlen(data));

    //uint i;
    for(int x = 1; x < 65; x++)
    {
         buffer[x] = convertASCII_to_FlashTable(buffer[x]);
    }

    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der Textübertragung");
        //usbhidCloseDevice(dev);
        return;
     }

    buffer[1] = 9;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei dem starten der Laufschrift");
        //usbhidCloseDevice(dev);
        return ;
    }
    delete [] data;

}

void GlMenuPlayer::ledPlayAnimation()
{
    if(dev == NULL)
        return;

    //Eine Zufallszahl zwischen a und b (incl. a und b) erzeugt man z.B. mit:
    //a + ( rand() % ( b - a + 1 ) )
    int la = 0 + ( rand() % ( 7 - 0 + 1 ) );

    bzero(buffer, sizeof(buffer));
    buffer[1] = 1;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der vorbereitung");
        return;
    }

    bzero(buffer, sizeof(buffer));

    for ( int i = 1; i < 9; i++)
    {
        if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
        {
            qDebug("Fehler bei nullchunk");
            return;
        }
    }

    bzero(buffer, sizeof(buffer));

    buffer[1] =4;
    buffer[2] = 30 + la;

    if( usbhidSetReport(dev, buffer, 3) != 0)
    {
        qDebug("Fehler beim starten der Animation");
    }
}

void GlMenuPlayer::ledStartTime()
{
    if(dev == NULL)
        return;

    QDateTime zeit;
    int h, m, s;

    zeit = QDateTime::currentDateTime();
    h = zeit.toString("hh:mm:ss").section(':',0,0).toInt();
    m = zeit.toString("hh:mm:ss").section(':',1,1).toInt();
    s = zeit.toString("hh:mm:ss").section(':',2,2).toInt();

    bzero(buffer, sizeof(buffer));

    buffer[1] = 1;
    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei der vorbereitung");
        return;
    }

    bzero(buffer, sizeof(buffer));

    for ( int i = 1; i < 9; i++)
    {
        if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
        {
            qDebug("Fehler bei nullchunk");
            return;
        }
    }

    bzero(buffer, sizeof(buffer));
    buffer[1] = 10;
    buffer[2] = h;
    buffer[3] = m;
    buffer[4] = s;

    if( usbhidSetReport(dev, buffer, sizeof(buffer)) != 0)
    {
        qDebug("Fehler bei dem starten Zeit");
        return;
    }
}

void GlMenuPlayer::ledTimer_Time_timeout()
{
    timer_ledAnimation->start(30000);
    ledPlayAnimation();
}

void GlMenuPlayer::ledTimer_Animation_timeout()
{
    if(ledTime)
    {
        ledStartTime();
        timer_ledTime->start(300000);
    }

    if(ledAnimation)
    {
        ledPlayAnimation();
        timer_ledAnimation->start(30000);
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

void GlMenuPlayer::newUsbDevice()
{
    qDebug() << Q_FUNC_INFO;
    usbhidCloseDevice(dev);
    QTimer::singleShot(500, this, SLOT(openUsbDevice()));
}

void GlMenuPlayer::nextSong()
{
    MetaPaket mp = trackList->nextItem();

    if(!mp.isEmpty)
    {
        playEngine->play(mp);
        infoString = mp.interpret +
                     " - " +
                    mp.title;
        newChildToDraw(this);
    }

    if(ledArtist)
        ledLaufschrift(mp.interpret);

    if(this->isVisible() && trackList->isVisible())
        newChildToDraw(trackList);

    if(this->isVisible() && coverView->isVisible())
    {
        coverView->setImage();
        animation->setImage( coverView->getImage());

        coverView->setCoverUrl(mp.coverUrl);
        coverView->setImage();
        animation->setImage2(coverView->getImage());

        animation->startCoverNext();
    }

    if(this->isVisible() && infoView->isVisible())
    {
        infoView->setImage();
        animation->setImage( infoView->getImage());

        infoView->setMetaPaket(mp);
        infoView->setImage();
        animation->setImage2(infoView->getImage());

        animation->startCoverNext();
    }
}

usbDevice_t* GlMenuPlayer::openDevice()
{
    usbDevice_t     *device = NULL;
    unsigned char   rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
    char            vendorName[] = {USB_CFG_VENDOR_NAME, 0}, productName[] = {USB_CFG_DEVICE_NAME, 0};
    int             vid = rawVid[0] + 256 * rawVid[1];
    int             pid = rawPid[0] + 256 * rawPid[1];
    int             err;

        if ( (err = usbhidOpenDevice(&device, vid, vendorName, pid, productName, 0)) != 0) {
            qDebug("Fehler beim oeffnen des USB Device");
            return NULL;
        }
        return device;

}

void GlMenuPlayer::openUsbDevice()
{
    qDebug() << Q_FUNC_INFO;
    dev = openDevice();
    ledBoom->setUsbDevice(dev);
    ledBoom->setStopIt(false);
    ledBoom->doit();
}

void GlMenuPlayer::playTrackListItem(MetaPaket mp)
{
    playEngine->play(mp);
    infoString = mp.interpret +
                 " - " +
                mp.title;
    newChildToDraw(this);
    if(ledArtist)
        ledLaufschrift(mp.interpret);
}

void GlMenuPlayer::prevSong()
{
    MetaPaket mp = trackList->prevItem();

    if(!mp.isEmpty)
    {
        playEngine->play(mp);
        infoString = mp.interpret +
                     " - " +
                    mp.title;
        newChildToDraw(this);
    }

    if(ledArtist)
        ledLaufschrift(mp.interpret);

    if(this->isVisible() && trackList->isVisible())
        newChildToDraw(trackList);

    if(this->isVisible() && coverView->isVisible())
    {
        coverView->setImage();
        animation->setImage( coverView->getImage());

        coverView->setCoverUrl(mp.coverUrl);
        coverView->setImage();
        animation->setImage2(coverView->getImage());

        animation->startCoverPrev();
    }

    if(this->isVisible() && infoView->isVisible())
    {
        infoView->setImage();
        animation->setImage( infoView->getImage());

        infoView->setMetaPaket(mp);
        infoView->setImage();
        animation->setImage2(infoView->getImage());

        animation->startCoverPrev();
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


void GlMenuPlayer::setNewPoints(MetaPaket mp)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << mp.points;

    db->setNewPoints(mp);
}

void GlMenuPlayer::setPlayEngine(Play_Engine *pe)
{
    playEngine = pe;

    connect(playEngine, SIGNAL(finished()), this, SLOT(nextSong()));
    connect(buttonPause, SIGNAL(clicked()), playEngine, SLOT(pause()));
}

void GlMenuPlayer::setUsbDevice(usbDevice_t *d)
{
    dev = d;
    ledBoom->setUsbDevice(d);
}
