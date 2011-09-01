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
    newChildToDraw(getParent());
}

void GlAnimation::draw(QPainter *p)
{    /*Führt die Funktion in dem Funktionszeiger doAnimation aus*/
    (this->*doAnimation)(p);
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
