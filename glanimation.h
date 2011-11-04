/*GlAnimation hat 2 Bilder. Einmal image von GlObject
  und image2 in private. GlAnimation stellt Funktionen
  bereit mit denen man 3D Animtionen anzeigen kann.
  Z.B das erste Bild dreht sich weg und das zweite Bild
  dreht sich hervor*/

#ifndef GLANIMATION_H
#define GLANIMATION_H

#include "globject.h"

#include <QTimeLine>

class GlAnimation : public GlObject
{
    Q_OBJECT

private:
    QTimeLine* timeLine;
    QImage image2;
    int xOffset;

public:
    GlAnimation(GlObject* parent = 0);

    void (GlAnimation::*doAnimation)(QPainter* p);
    void draw(QPainter *p);

    void jumpDown(QPainter* p);
    void jumpUp(QPainter* p);

    void rotateIn(QPainter* p);
    void rotateOut(QPainter* p);

    void scrollDown(QPainter* p);
    void scrollUp(QPainter* p);

    void setImage2(QImage i) { image2 = i; }
    void setXoffset(int xo) { xOffset = xo; }

    void startJumpDown();
    void startJumpUp();
    void startRotation();
    void startScrollDown();
    void startScrollUp();
    void startZoomIn();
    void startZoomOut();

    void zoomIn(QPainter* p);
    void zoomOut(QPainter* p);

public slots:
    void done();
    void newPercent(int);
    void start();
    void startJumpDown2();
    void startJumpUp2();
    void startRotation2();

signals:
    void animationDone();
};

#endif // GLANIMATION_H
