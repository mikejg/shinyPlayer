/*GlObject ist ähnlich dem QObject eine Basisklasse.
  Den ganzen Aufwand mit den eigenen Klassen wie GlButton,
  wird gemacht weil QGLWidget keine GUI-Klassen (QButton etc)
  aufnehmen kann*/

#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QMouseEvent>
#include <QDebug>
#include <QTransform>
#include <QImage>

class GlObject : public QObject
{
    Q_OBJECT

private:
    QImage img;
    int x, y, width, height;
    int percent;
    bool visible;

    GlObject* glParent;

public:
    QList<GlObject *> listChilds;
    QPixmap backGroundPixmap;

    GlObject(GlObject* parent = 0);
    void addChild(GlObject* c) { listChilds.append(c); }

    virtual void draw(QPainter* p) {Q_UNUSED(p);}
    void drawImageAt(QPainter *p, int angle, int per);
    void drawImageAtY(QPainter *p, int angle, int per);
    void drawBackGroundPixmap(QPainter* p);

    QRect geometry(){return QRect(x,y,width,height);}
    QPoint getCenter();
    int getHeight() { return height; }
    GlObject* getParent() { return glParent; }
    int getPercent() { return percent; }
    QPixmap getPixmap();
    int getWidth() { return width; }
    int getX() { return x; }
    int getY() { return y; }

    bool isVisible();

    virtual void mousePressEvent (QMouseEvent * event){event->ignore();}
    virtual void mouseReleaseEvent (QMouseEvent * event){event->ignore();}

    void setBackGroundPixmap(QPixmap pix) { backGroundPixmap = pix; }
    virtual void setGeometry(int posX, int posY, int w, int h);
    void setImage();
    void setImage(QImage i) { img = i; }
    virtual void setLarge() {}
    void setPercent(int p) { percent = p; }
    void setVisible(bool b) { visible = b; }

public slots:
    void newFrame(int f) { percent = f; update(); }

signals:
    void newChildToDraw(GlObject*);
    void update();

};

#endif // GLOBJECT_H
