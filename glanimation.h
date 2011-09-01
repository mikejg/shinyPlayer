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

public:
    GlAnimation(GlObject* parent = 0);

    void (GlAnimation::*doAnimation)(QPainter* p);
    void draw(QPainter *p);
    void setImage2(QImage i) { image2 = i; }

    void startRotation();

    void rotateIn(QPainter* p);
    void rotateOut(QPainter* p);

public slots:
    void done();
    void newPercent(int);
    void start();
    void startRotation2();

/*signals:
    void done();*/
};

#endif // GLANIMATION_H
