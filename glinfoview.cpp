#include "glinfoview.h"
#include <QFile>

GlInfoView::GlInfoView(GlObject *parent) :
    GlObject(parent)
{
    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;
    fontColor = QColor(255,255,255,128);
    fontSize = 25;

    cbPoints = new GlComboBox(this);
    cbPoints->setGeometry(300, 209, 200,30);
    cbPoints->setFill(false);

    connect(cbPoints, SIGNAL(open(GlComboBox*)), this, SLOT(comboBoxOpen(GlComboBox*)));
    connect(cbPoints, SIGNAL(closed(GlComboBox*)), this, SLOT(comboBoxClosed(GlComboBox*)));

    cbPoints->insertItem(QString("0 Points"));
    cbPoints->insertItem(QString("1 Points"));
    cbPoints->insertItem(QString("2 Points"));
    cbPoints->insertItem(QString("3 Points"));
    cbPoints->insertItem(QString("4 Points"));
    cbPoints->insertItem(QString("5 Points"));
    cbPoints->insertItem(QString("6 Points"));
    cbPoints->insertItem(QString("7 Points"));
    cbPoints->insertItem(QString("8 Points"));
    cbPoints->insertItem(QString("9 Points"));
    cbPoints->insertItem(QString("10 Points"));
}

void GlInfoView::comboBoxClosed(GlComboBox* cb)
{
    qDebug() << Q_FUNC_INFO;

    for(int i = 0; i < listChilds.size(); i++)
       {
         listChilds.at(i)->setVisible(true);
       }
    newChildToDraw(this->getParent());
    QString t = cb->getText().left(2);
    mp.points = t.toInt();

    setNewPoints(mp);
}

void GlInfoView::comboBoxOpen(GlComboBox* cb)
{
    for(int i = 0; i < listChilds.size(); i++)
       {
         listChilds.at(i)->setVisible(false);
       }

    cb->setVisible(true);
    newChildToDraw(cb);
}

void GlInfoView::draw(QPainter *p)
{
    p->fillRect(geometry(), Qt::black);
    QLinearGradient gradient( getWidth()/2, getY(),
                              getWidth()/2, getY() + getHeight());

    gradient.setColorAt(0, gradientColorAt0);
    gradient.setColorAt(1, gradientColorAt1);
    p->setBrush(QBrush(gradient));
    QPainterPath pa;
    QRect rect = geometry();
    pa.addRoundedRect(rect, borderRadius, borderRadius);
    pen.setWidth(border); //Strichbreite
    pen.setColor(borderColor); //Strichfarbe
    p->setPen(pen);
    p->drawPath(pa);

    QFile testFile(mp.coverUrl);
    if(testFile.exists())
    {
        coverImg.load(mp.coverUrl);
        coverImg = coverImg.scaled(200, 200);
        p->drawImage(getX() + 75,
                     getY() + getHeight()/2 - 100,
                     coverImg);
    }


    QFont font = p->font();
    font.setPixelSize(fontSize);
    font.setBold(true);
    p->setFont(font);
    p->setPen(fontColor);

    QRect re(getX() + 300,
             getY() + getHeight()/2 + 10,
             400, 30);
    p->drawText(re, mp.interpret);

    QRect re1(getX() + 300,
             getY() + getHeight()/2 + 40,
             400, 30);
    p->drawText(re1, mp.album);

    QRect re2(getX() + 300,
             getY() + getHeight()/2 + 70,
             400, 30);
    p->drawText(re2, mp.title);

    cbPoints->draw(p);
}

void GlInfoView::mousePressEvent(QMouseEvent *event)
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

void GlInfoView::mouseReleaseEvent(QMouseEvent *event)
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
