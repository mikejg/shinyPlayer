#include "glanimation.h"
#include <QDebug>

GlAnimation::GlAnimation(GlObject* parent) : GlObject(parent)
{
    timeLine = new QTimeLine(500, this);
    timeLine->setLoopCount(1);
    timeLine->setFrameRange(0, 100);
    timeLine->setCurveShape(QTimeLine::EaseInCurve);

    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));
}
void GlAnimation::done()
{
    /*SLOT: wird ausgeführt wenn die timeLine fertig ist.
            Das übergeordnete Object soll sich nach der
            Animation neu Zeichnen*/
    timeLine->setFrameRange(0, 100);
    timeLine->setDuration(500);
    newChildToDraw(getParent());
}

void GlAnimation::draw(QPainter *p)
{    /*Führt die Funktion in dem Funktionszeiger doAnimation aus*/
    (this->*doAnimation)(p);
}

void GlAnimation::jumpDown(QPainter *p)
{
    int per = getPercent();

    if(per < 0 || per > 100) return;
    p->fillRect(geometry(), Qt::black);

    QImage tmpImg = getImage();

    int t_height = (int)((1. - per/100.) * tmpImg.height());
    int t_y = tmpImg.height() - t_height;
    tmpImg = tmpImg.copy(0, 0, tmpImg.width(), t_height);

    p->drawImage(geometry().x() + 5, geometry().y() + t_y, tmpImg);
}

void GlAnimation::jumpUp(QPainter *p)
{
    int per = getPercent();

    if(per < 0 || per > 100) return;
    p->fillRect(geometry(), Qt::black);

    QImage tmpImg = getImage();

    int t_y = (int)((per/100.) * tmpImg.height());
    int t_height = tmpImg.height() -t_y;
    tmpImg = tmpImg.copy(0, t_y, tmpImg.width(), t_height);

    p->drawImage(geometry().x() + 5, geometry().y(), tmpImg);
}

void GlAnimation::newPercent(int per)
{   /*SLOT: wird ausgeführt wenn timeLine ein neues Frame hat.
            Percent wird neu gesetzt und ein Neuzeichnen wird gestartet*/
    setPercent(per);
    newChildToDraw(this);
}

void GlAnimation::rotateIn(QPainter *p)
{
    /*Eindrehen des Images. Der Winkel wird anhand der Prozente berechnet.
      Dort wo das Image gezeichnet werden soll wird ein schwarzes Rechteck
      gezeichnet, dann wird das gedrehte Image gezeichnet*/
    int per = getPercent();
    int angle = int((per/100.)* 90);

    if(per < 0 || per > 100) return;

    p->fillRect(geometry(), Qt::black);
    drawImageAtY(p, angle, per);
}

void GlAnimation::rotateOut(QPainter *p)
{
    /*Siehe rotateIn*/
    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;
    p->fillRect(geometry(), Qt::black);
    drawImageAtY(p, angle, per);
}

void GlAnimation::start()
{
    /*SLOT: */
    timeLine->start();
}
void GlAnimation::scrollDown(QPainter *p)
{
    int per = getPercent();

    if(per < 0 || per > 100) return;
    p->fillRect(geometry(), Qt::black);

    QImage tmpImg = getImage();

    int t_height = (int)((1. - per/100.) * tmpImg.height());
    int t_y = tmpImg.height() - t_height;
    tmpImg = tmpImg.copy(0, 0, tmpImg.width(), t_height);

    p->drawImage(geometry().x() + 5, geometry().y() + t_y, tmpImg);

    t_height = (int)((per/100.) * image2.height());
    t_y = image2.height() - t_height;
    tmpImg = image2.copy(0,t_y,image2.width(), t_height);

    p->drawImage(geometry().x() + 5, geometry().y(), tmpImg);
}

void GlAnimation::scrollUp(QPainter *p)
{
    int per = getPercent();

    if(per < 0 || per > 100) return;
    p->fillRect(geometry(), Qt::black);

    QImage tmpImg = getImage();

    int t_y = (int)((per/100.) * tmpImg.height());
    int t_height = tmpImg.height() -t_y;
    tmpImg = tmpImg.copy(0, t_y, tmpImg.width(), t_height);

    p->drawImage(geometry().x() + 5, geometry().y(), tmpImg);

    t_y = geometry().y() + tmpImg.height();
    t_height = (int)((per/100.) * image2.height());
    tmpImg = image2.copy(0,0,image2.width(), t_height);

    p->drawImage(geometry().x() + 5, t_y, tmpImg);
}

void GlAnimation::startRotation()
{
    /*Startet den ersten Teil der Rotation.
      - Alle Verbindungen von timeLine beenden;
      - aufwärts zählen in timeLine einstellen;
      - Signale neu verbinden
      - den Funktionszeiger doAnimation setzen
      - timeLine starten*/

    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Forward);
    connect(timeLine, SIGNAL(finished()), this, SLOT(startRotation2()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));
    doAnimation = &GlAnimation::rotateOut;
    timeLine->start();
}
void GlAnimation::startJumpDown()
{
    timeLine->disconnect();
    timeLine->setFrameRange(0, 25);
    timeLine->setDuration(250);
    timeLine->setDirection(QTimeLine::Forward);

    connect(timeLine, SIGNAL(finished()), this, SLOT(startJumpDown2()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));

    doAnimation = &GlAnimation::jumpDown;
    timeLine->start();
}

void GlAnimation::startJumpDown2()
{
    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Backward);

    connect(timeLine, SIGNAL(finished()), this, SLOT(done()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));

    doAnimation = &GlAnimation::jumpDown;
    timeLine->start();
}

void GlAnimation::startJumpUp()
{
    timeLine->disconnect();
    timeLine->setFrameRange(0, 25);
    timeLine->setDuration(250);
    timeLine->setDirection(QTimeLine::Forward);

    connect(timeLine, SIGNAL(finished()), this, SLOT(startJumpUp2()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));

    doAnimation = &GlAnimation::jumpUp;
    timeLine->start();
}

void GlAnimation::startJumpUp2()
{
    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Backward);

    connect(timeLine, SIGNAL(finished()), this, SLOT(done()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));

    doAnimation = &GlAnimation::jumpUp;
    timeLine->start();
}
void GlAnimation::startRotation2()
{
    /*Startet den zweiten Teil der Rotation.
      - Image von GlObject mit dem zweiten Bild laden.
        Es wird immer nur das Image von GlObject gedreht.
      - Siehe startRotation();*/

    setImage(image2);
    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Backward);
    connect(timeLine, SIGNAL(finished()), this, SLOT(done()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));
    doAnimation = &GlAnimation::rotateIn;
    timeLine->start();
}

void GlAnimation::startScrollDown()
{
    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Forward);
    connect(timeLine, SIGNAL(finished()), this, SLOT(done()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));

    doAnimation = &GlAnimation::scrollDown;
    timeLine->start();
}

void GlAnimation::startScrollUp()
{
    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Forward);
    connect(timeLine, SIGNAL(finished()), this, SLOT(done()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));

    doAnimation = &GlAnimation::scrollUp;
    timeLine->start();
}

void GlAnimation::startZoomIn()
{
    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Forward);
    connect(timeLine, SIGNAL(finished()), this, SLOT(done()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));
    doAnimation = &GlAnimation::zoomIn;
    timeLine->start();
}

void GlAnimation::startZoomOut()
{
    timeLine->disconnect();
    timeLine->setDirection(QTimeLine::Backward);
    connect(timeLine, SIGNAL(finished()), this, SIGNAL(animationDone()));
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));
    doAnimation = &GlAnimation::zoomOut;
    timeLine->start();
}

void GlAnimation::zoomIn(QPainter *p)
{
    QRect rect = geometry();
    QImage image;
    int imageX, imageWidth;
    int per = getPercent();

    if(per < 0 || per > 100) return;
    p->fillRect(rect, Qt::black);

    imageWidth = (int)((per/100.) * getImage().width());
    imageX = getImage().width()/2 - imageWidth/2;
    image = getImage().copy(imageX, 0, imageWidth, getImage().height());

    p->drawImage(geometry().x() + imageX, geometry().y(), image);
}

void GlAnimation::zoomOut(QPainter *p)
{
    QRect rect = geometry();
    QImage image;
    int imageX, imageWidth;
    int per = getPercent();

    if(per < 0 || per > 100) return;
    p->fillRect(rect, Qt::black);

    imageWidth = (int)((per/100.) * getImage().width());
    imageX = getImage().width()/2 - imageWidth/2;
    image = getImage().copy(imageX, 0, imageWidth, getImage().height());

    p->drawImage(geometry().x() + imageX, geometry().y(), image);
}
