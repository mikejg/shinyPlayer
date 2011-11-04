#include "glpictureflow.h"
#include <QTimer>

GlPictureFlow::GlPictureFlow(GlObject* parent) : GlObject(parent)
{
    setGeometry(0,0,800,300);
    setPercent(0);
    for_backward = &GlPictureFlow::draw_forward;

    buttonLeft = new GlButton(this);
    buttonLeft->setGeometry(280,270,60,30);
    buttonLeft->setBackGroundPixmap(QPixmap(":/images/pictureFlowLeft.png"));
    buttonLeft->setBackGroundPixmapPressed(QPixmap(":/images/pictureFlowLeftPressed.png"));
    buttonLeft->setText("<");
    connect(buttonLeft, SIGNAL(clicked()), this, SLOT(startForward()));

    buttonRigth = new GlButton(this);
    buttonRigth->setGeometry(460,270,60,30);
    buttonRigth->setBackGroundPixmap(QPixmap(":/images/pictureFlowRigth.png"));
    buttonRigth->setBackGroundPixmapPressed(QPixmap(":/images/pictureFlowRigthPressed.png"));
    buttonRigth->setText(">");
    connect(buttonRigth, SIGNAL(clicked()), this, SLOT(startBackward()));

    buttonTracks = new GlButton(this);
    buttonTracks->setGeometry(340,270,120,30);
    buttonTracks->setBackGroundPixmap(QPixmap(":/images/button120.png"));
    buttonTracks->setBackGroundPixmapPressed(QPixmap(":/images/button120Pressed.png"));
    buttonTracks->setText("Tracks");
    connect(buttonTracks, SIGNAL(clicked()), this, SIGNAL(buttonTracks_Clicked()));

    timeLine = new QTimeLine(350, this);
    timeLine->setLoopCount(1);
    timeLine->setFrameRange(0, 100);
    timeLine->setCurveShape(QTimeLine::EaseInCurve);

    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(newPercent(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(done()));

    distShort = 50;
    distLong = 150;

    sizeSmall = 130;
    sizeBig = 150;

    pt0.setX(50); pt0.setY(150);
    pt1.setX(100); pt1.setY(150);
    pt2.setX(150); pt2.setY(150);
    pt3.setX(200); pt3.setY(150);
    pt4.setX(250); pt4.setY(150);
    pt5.setX(400); pt5.setY(150);
    pt6.setX(750); pt6.setY(150);
    pt7.setX(700); pt7.setY(150);
    pt8.setX(650); pt8.setY(150);
    pt9.setX(600); pt9.setY(150);
    pt10.setX(550); pt10.setY(150);
    pt11.setX(400); pt11.setY(150);
}

void GlPictureFlow::addImage(QImage i)
{
    i = i.scaled(sizeBig,sizeBig);
    i = mirrorImage(i);
    images.append(i);
}

void GlPictureFlow::done()
{
    setPercent(0);
    if(for_backward == &GlPictureFlow::draw_forward)
       centerImage++;

    if(for_backward == &GlPictureFlow::draw_backward)
       centerImage--;

    QTimer::singleShot(100, this, SIGNAL(animationDone()));
   // newAlbum(alben.at(centerImage));
}

void GlPictureFlow::draw(QPainter *p)
{
    //qDebug() << Q_FUNC_INFO << "start";
    p->setBrush(Qt::black);
    p->drawRect(geometry());

    buttonRigth->draw(p);
    buttonLeft->draw(p);
    buttonTracks->draw(p);

    if(!alben.isEmpty())
        (this->*for_backward)(p);
    //qDebug() << Q_FUNC_INFO << "end";
}

void GlPictureFlow::draw_backward(QPainter* p)
{
    QPoint point;
    int dist;
    int i;
    int angle;
    int size;

    QFont font = p->font();
    font.setPixelSize(20);
    font.setBold(true);
    p->setFont(font);

       p->setPen(QColor(255,255,255,125));
       p->drawText(QRect(0,0,getWidth(),30),Qt::AlignHCenter,alben.at(centerImage));
    centerAlbum = alben.at(centerImage);
    i = centerImage - 5;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt0.x() + dist);
        point.setY(pt0.y());

        size = int((getPercent()/100.) * (sizeSmall));
        t_drawImageAt(p, point, images.at(i), size,size*1.5,-50,0);
      }
    i = centerImage - 4;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt1.x() + dist);
        point.setY(pt1.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall, sizeSmall*1.5,-50,0);
      }
    i = centerImage - 3;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt2.x() + dist);
        point.setY(pt2.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall, sizeSmall*1.5,-50,0);
      }
    i = centerImage -2;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt3.x() + dist);
        point.setY(pt3.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall, sizeSmall*1.5,-50,0);
      }

    i = centerImage - 1;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distLong));
        point.setX(pt4.x() + dist);
        point.setY(pt4.y());

        size = int((getPercent()/100.) * (sizeBig - sizeSmall)) + sizeSmall;
        angle = -50 + int((getPercent()/100.) * 50);
        t_drawImageAt(p, point, images.at(i), size,size*1.5,angle,0);
      }

    i = centerImage + 4;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt7.x() + dist);
        point.setY(pt7.y());

        size = sizeSmall - int((getPercent()/100.) * (sizeSmall));
        t_drawImageAt(p, point, images.at(i), size,size*1.5,50,0);
      }

    i = centerImage + 3;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt8.x() + dist);
        point.setY(pt8.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall, sizeSmall*1.5,50,0);
      }

    i = centerImage + 2;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt9.x() + dist);
        point.setY(pt9.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall, sizeSmall*1.5,50,0);
      }

    i = centerImage + 1;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distShort));
        point.setX(pt10.x() + dist);
        point.setY(pt10.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall, sizeSmall*1.5,50,0);
    }

    i = centerImage;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (distLong));
        point.setX(pt11.x() + dist);
        point.setY(pt11.y());

        angle = int((getPercent()/100.) * (50));

        size = int((getPercent()/100.) * (sizeSmall - sizeBig)) + sizeBig;
        t_drawImageAt(p, point, images.at(i), size,size*1.5,angle,0);
      }
}

void GlPictureFlow::draw_forward(QPainter *p)
{
    //qDebug() << Q_FUNC_INFO << "start";
    QPoint point;
    int dist;
    int i;
    int angle;
    int size;

    QFont font = p->font();
    font.setPixelSize(20);
    font.setBold(true);
    p->setFont(font);

       p->setPen(QColor(255,255,255,125));
    p->drawText(QRect(0,0,getWidth(),30),Qt::AlignHCenter,alben.at(centerImage));
    centerAlbum = alben.at(centerImage);

    i = centerImage - 4;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt1.x() + dist);
        point.setY(pt1.y());

        size = sizeSmall - int((getPercent()/100.) * (sizeSmall));
        t_drawImageAt(p, point, images.at(i), size,size*1.5,-50,0);
      }

    i = centerImage - 3;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt2.x() + dist);
        point.setY(pt2.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall,sizeSmall*1.5,-50,0);
      }

    i = centerImage - 2;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt3.x() + dist);
        point.setY(pt3.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall,sizeSmall*1.5,-50,0);
      }

    i = centerImage - 1;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt4.x() + dist);
        point.setY(pt4.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall,sizeSmall*1.5,-50,0);
      }

    i = centerImage;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distLong)));
        point.setX(pt5.x() + dist);
        point.setY(pt5.y());

        angle = int((getPercent()/100.) * (-50));

        size = int((getPercent()/100.) * (sizeSmall - sizeBig)) + sizeBig;
        t_drawImageAt(p, point, images.at(i), size,size*1.5,angle,0);
      }

    i = centerImage + 5;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt6.x() + dist);
        point.setY(pt6.y());

        size = int((getPercent()/100.) * (sizeSmall));
        t_drawImageAt(p, point, images.at(i), size,size*1.5,50,0);
      }

    i = centerImage + 4;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt7.x() + dist);
        point.setY(pt7.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall,sizeSmall*1.5, 50,0);
      }

    i = centerImage + 3;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt8.x() + dist);
        point.setY(pt8.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall,sizeSmall*1.5, 50,0);
      }

    i = centerImage + 2;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distShort)));
        point.setX(pt9.x() + dist);
        point.setY(pt9.y());
        t_drawImageAt(p, point, images.at(i), sizeSmall,sizeSmall*1.5,50,0);
      }

    i = centerImage + 1;
    if(i > -1 && i < images.size())
      {
        dist = int((getPercent()/100.) * (-(distLong)));
        point.setX(pt10.x() + dist);
        point.setY(pt10.y());

        size = int((getPercent()/100.) * (sizeBig - sizeSmall)) + sizeSmall;
        angle = 50 - int((getPercent()/100.) * 50);
        t_drawImageAt(p, point, images.at(i), size,size*1.5,angle,0);
      }
    //qDebug() << Q_FUNC_INFO << "end";
}

void GlPictureFlow::t_drawImageAt(QPainter *p, const QPoint &loc,const QImage &image, int w, int h, int angle, int posDif)
{
    p->save();
    QTransform trans;
    trans.rotate(angle, Qt::YAxis);
    trans.scale(qreal(w)/image.width(), qreal(h)/image.height());
    p->setTransform(trans * QTransform().translate(loc.x()+posDif, loc.y()), true);
    QPointF pt(-image.width()/2, -image.height()/2);
    p->drawImage(pt, image);

    p->restore();
}
QImage GlPictureFlow::mirrorImage(const QImage &i, MirrorStyle mirrorStyle,
                                 FadeStyle fadeStyle)
{
    QImage tmpImage = i;
    QImage returnImage(sizeBig,sizeBig*2,QImage::Format_ARGB32);

    if (mirrorStyle != NoMirror)
        tmpImage = tmpImage.mirrored(mirrorStyle == MirrorOverY,
                                     mirrorStyle == MirrorOverX);

    if (fadeStyle != NoFade)
    {
        QPoint p1, p2;

        if (fadeStyle == FadeDown)
            p2.setY(tmpImage.height()/2);
        else if (fadeStyle == FadeUp)
            p1.setY(tmpImage.height());
        else if (fadeStyle == FadeRight)
            p2.setX(tmpImage.width());
        else if (fadeStyle == FadeLeft)
            p1.setX(tmpImage.width());

        QLinearGradient gradient(p1, p2);
        gradient.setColorAt(0, QColor(0, 0, 0, 100));
        //gradient.setColorAt(1, Qt::transparent);
        gradient.setColorAt(1, Qt::black);

        QPainter p(&tmpImage);
        //p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        p.fillRect(0, 0, tmpImage.width(), tmpImage.height(), gradient);
        p.end();
    }

    QPainter painter(&returnImage);
    painter.fillRect(QRect(0,0,sizeBig, sizeBig*2), Qt::black);
    //painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.drawImage(QPoint(0,0), i);
    painter.drawImage(QPoint(0,sizeBig),tmpImage);
    painter.end();
    returnImage = returnImage.copy(0,0,sizeBig,sizeBig*1.5);
    return returnImage;
    //return tmpImage;
}

void GlPictureFlow::mousePressEvent(QMouseEvent *event)
{
    /*Überprüft ob die Maus über einem Kindobjekt gedrückt wurde und
      führt die Funktion mousePressEvent des Kindobjekts aus*/
    QRect rect(325,40,150,150);
    if(rect.contains(event->pos()))
    {
        albumClicked(alben.at(centerImage));
    }

    for(int i = 0; i < listChilds.size(); i++)
       {
         rect = listChilds.at(i)->geometry();
         if(listChilds.at(i)->isVisible() && rect.contains(event->pos()))
           {
             listChilds.at(i)->mousePressEvent(event);
           }
       }
}

void GlPictureFlow::mouseReleaseEvent(QMouseEvent *event)
{
    /*Siehe mousePressEvent*/
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
void GlPictureFlow::setLarge()
{
    setGeometry(0,0,1024, 384);

    pt0.setX(pt0.x() * 1.28); pt0.setY(pt0.y() * 1.28);
    pt1.setX(pt1.x() * 1.28); pt1.setY(pt1.y() * 1.28);
    pt2.setX(pt2.x() * 1.28); pt2.setY(pt2.y() * 1.28);
    pt3.setX(pt3.x() * 1.28); pt3.setY(pt3.y() * 1.28);
    pt4.setX(pt4.x() * 1.28); pt4.setY(pt4.y() * 1.28);
    pt5.setX(pt5.x() * 1.28); pt5.setY(pt5.y() * 1.28);
    pt6.setX(pt6.x() * 1.28); pt6.setY(pt6.y() * 1.28);
    pt7.setX(pt7.x() * 1.28); pt7.setY(pt7.y() * 1.28);
    pt8.setX(pt8.x() * 1.28); pt8.setY(pt8.y() * 1.28);
    pt9.setX(pt9.x() * 1.28); pt9.setY(pt9.y() * 1.28);
    pt10.setX(pt10.x() * 1.28); pt10.setY(pt10.y() * 1.28);
    pt11.setX(pt11.x() * 1.28); pt11.setY(pt11.y() * 1.28);


    distLong = distLong * 1.28;
    distShort = distShort * 1.28;
    sizeSmall = sizeSmall * 1.28;
    sizeBig = sizeBig * 1.28;

    buttonLeft->setLarge();
    buttonLeft->setGeometry(buttonLeft->getX()+2, buttonLeft->getY(),
                            buttonLeft->getWidth(), buttonLeft->getHeight());
    buttonRigth->setLarge();
    buttonTracks->setLarge();
}

void GlPictureFlow::startBackward()
{
    if(centerImage > 0)
    {
     for_backward = &GlPictureFlow::draw_backward;
     timeLine->start();
    }
}

void GlPictureFlow::startForward()
{
    if(centerImage <  images.size()-1)
      {
       for_backward = &GlPictureFlow::draw_forward;
       timeLine->start();
      }
}
