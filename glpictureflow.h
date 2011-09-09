#ifndef GLPICTUREFLOW_H
#define GLPICTUREFLOW_H

#include "globject.h"
#include "glbutton.h"

#include <QTimeLine>

enum FadeStyle {
    NoFade,
    FadeDown,
    FadeRight,
    FadeUp,
    FadeLeft
};

enum MirrorStyle {
    NoMirror,
    MirrorOverX,
    MirrorOverY
};

class GlPictureFlow : public GlObject
{
    Q_OBJECT
private:
    QList<QImage> images;
    QStringList alben;
    QTimeLine* timeLine;
    QPoint pt0, pt1, pt2, pt3, pt4, pt5,
           pt6, pt7, pt8, pt9, pt10, pt11;

    int distShort;
    int distLong;
    int centerImage;
    int sizeSmall;
    int sizeBig;

    GlButton* buttonLeft;
    GlButton* buttonRigth;
    GlButton* buttonTracks;

public:
    GlPictureFlow(GlObject* parent = 0);

    void addImage(QImage i);

    void clear() {images.clear(); centerImage = 0;}

    void draw(QPainter *p);
    void draw_backward(QPainter* p);
    void draw_forward(QPainter* p);
    void t_drawImageAt(QPainter *p, const QPoint &loc,const QImage &imgage, int w, int h, int angle,int posDif);

    void (GlPictureFlow::*for_backward)(QPainter* p);

    QImage mirrorImage(const QImage &i, MirrorStyle mirrorStyle=MirrorOverX,
                                     FadeStyle fadeStyle=FadeDown);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void setAlben(QStringList sl) {alben = sl;}
    void setLarge();

public slots:
    void done();
    void newPercent(int per) { setPercent(per); this->newChildToDraw(this); }
    void startBackward();
    void startForward();

signals:
    void albumClicked(QString);
};

#endif // GLPICTUREFLOW_H
