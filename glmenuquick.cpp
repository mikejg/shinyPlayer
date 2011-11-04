#include "glmenuquick.h"

GlMenuQuick::GlMenuQuick(GlObject* parent) : GlObject(parent)
{
    setGeometry(0,0,800,600);

    balkenOben = QPixmap(":/images/mainBalkenOben.png");
    yBalkenOben = 95;

    balkenUnten = QPixmap(":/images/mainBalkenUnten.png");
    yBalkenUnten = 520;

    buttonMain = new GlButton(this);
    buttonMain->setGeometry(3,10,48,48);
    buttonMain->setBackGroundPixmap(QPixmap(":/images/home.png"));
    buttonMain->setImage();
    connect(buttonMain, SIGNAL(clicked()), this, SIGNAL(buttonMain_clicked()));

    buttonClear = new GlButton(this);
    buttonClear->setGeometry(749,10,48,48);
    buttonClear->setBackGroundPixmap(QPixmap(":/images/clear.png"));
    buttonClear->setImage();
    connect(buttonClear, SIGNAL(clicked()), this, SLOT(buttonClear_clicked()));

    buttonOK = new GlButton(this);
    buttonOK->setGeometry(370,490, 60, 60);
    connect(buttonOK, SIGNAL(clicked()), this, SLOT(buttonOK_clicked()));

    labelYear = new GlTextLabel(this);
    labelYear->setGeometry(90,195,300,30);
    labelYear->setText("YEAR");
    labelYear->setImage();

    comboBoxYear = new GlComboBox(this);
    connect(comboBoxYear, SIGNAL(open(GlComboBox*)), this, SLOT(comboBoxOpen(GlComboBox*)));
    connect(comboBoxYear, SIGNAL(closed(GlComboBox*)), this, SLOT(comboBoxClosed(GlComboBox*)));
    comboBoxYear->setGeometry(410,195,300,30);
    comboBoxYear->setImage();
    comboBoxYear->insertItem("1960 - 1970");
    comboBoxYear->insertItem("1970 - 1980");
    comboBoxYear->insertItem("1980 - 1990");
    comboBoxYear->insertItem("1990 - 2000");
    comboBoxYear->insertItem("2000 - 2010");
    comboBoxYear->insertItem("2010 - 2020");

    labelRandom = new GlTextLabel(this);
    labelRandom->setGeometry(90,315,300,30);
    labelRandom->setText("RANDOM");
    labelRandom->setImage();

    comboBoxRandom = new GlComboBox(this);
    connect(comboBoxRandom, SIGNAL(open(GlComboBox*)), this, SLOT(comboBoxOpen(GlComboBox*)));
    connect(comboBoxRandom, SIGNAL(closed(GlComboBox*)), this, SLOT(comboBoxClosed(GlComboBox*)));
    comboBoxRandom->setGeometry(410,315,300,30);
    comboBoxRandom->setImage();
    comboBoxRandom->insertItem("On");
    comboBoxRandom->insertItem("Off");

    labelPoints= new GlTextLabel(this);
    labelPoints->setGeometry(90,255,300,30);
    labelPoints->setText("POINTS");
    labelPoints->setImage();

    comboBoxPoints = new GlComboBox(this);
    connect(comboBoxPoints, SIGNAL(open(GlComboBox*)), this, SLOT(comboBoxOpen(GlComboBox*)));
    connect(comboBoxPoints, SIGNAL(closed(GlComboBox*)), this, SLOT(comboBoxClosed(GlComboBox*)));
    comboBoxPoints->setGeometry(410,255,300,30);
    comboBoxPoints->setImage();
    comboBoxPoints->insertItem("2 or greater");
    comboBoxPoints->insertItem("4 or greater");
    comboBoxPoints->insertItem("6 or greater");
    comboBoxPoints->insertItem("8 or greater");
    //comboBoxPoints->insertItem("greater or 5");

    labelAdded= new GlTextLabel(this);
    labelAdded->setGeometry(90,375,300,30);
    labelAdded->setText("ADDED");
    labelAdded->setImage();

    comboBoxAdded = new GlComboBox(this);
    connect(comboBoxAdded, SIGNAL(open(GlComboBox*)), this, SLOT(comboBoxOpen(GlComboBox*)));
    connect(comboBoxAdded, SIGNAL(closed(GlComboBox*)), this, SLOT(comboBoxClosed(GlComboBox*)));
    comboBoxAdded->setGeometry(410,375,300,30);
    comboBoxAdded->setImage();
    comboBoxAdded->insertItem(" 1 Week");
    comboBoxAdded->insertItem(" 2 Week");
    comboBoxAdded->insertItem(" 3 Week");
    comboBoxAdded->insertItem(" 1 Months");
    comboBoxAdded->insertItem(" 3 Months");
    comboBoxAdded->insertItem(" 6 Months");
    comboBoxAdded->insertItem(" 9 Months");
    comboBoxAdded->insertItem(" last year");
}

void GlMenuQuick::buttonClear_clicked()
{
    comboBoxYear->clear();
    comboBoxRandom->clear();
    comboBoxPoints->clear();
    comboBoxAdded->clear();

    newChildToDraw(this);
}

void GlMenuQuick::buttonOK_clicked()
{
    qDebug() << Q_FUNC_INFO;
    db->getTracksFromQuick("2000");
}

void GlMenuQuick::draw(QPainter *p)
{
    p->setBrush(QColor(Qt::black));
    p->drawRect(geometry());

    p->drawPixmap(0,yBalkenOben - balkenOben.height()/2, balkenOben);
    p->drawPixmap(0,yBalkenUnten - balkenUnten.height()/2, balkenUnten);

    for(int i = 0; i < listChilds.size(); i++)
        listChilds.at(i)->draw(p);
}

void GlMenuQuick::mousePressEvent(QMouseEvent *event)
{
    /*Überprüft ob die Maus über einem Kindobjekt gedrückt wurde und
      führt die Funktion mousePressEvent des Kindobjekts aus*/

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

void GlMenuQuick::mouseReleaseEvent(QMouseEvent *event)
{
    /*Siehe mousePressEvent*/
    QRect rect;
    for(int i = 0; i < listChilds.size(); i++)
       {
         rect = listChilds.at(i)->geometry();
         if(listChilds.at(i)->isVisible() && rect.contains(event->pos()))
           {
             listChilds.at(i)->mouseReleaseEvent(event);
             return;
           }
       }
}

void GlMenuQuick::rollIn(QPainter *p)
{
    int per = getPercent();
    int angle = int((per/100.)* -90);

    if(per < 0 || per > 100) return;

    labelYear->drawImageAt(p, angle, per);
    comboBoxYear->drawImageAt(p, angle, per);
    labelRandom->drawImageAt(p, angle, per);
    comboBoxRandom->drawImageAt(p, angle, per);
    labelPoints->drawImageAt(p, angle, per);
    comboBoxPoints->drawImageAt(p, angle, per);
    labelAdded->drawImageAt(p, angle, per);
    comboBoxAdded->drawImageAt(p, angle, per);
    buttonMain->drawImageAt(p, angle, per);
    buttonClear->drawImageAt(p, angle, per);

    QPixmap pm;
    pm = balkenOben.scaled(balkenOben.width(), balkenOben.height() - (per/100.)*balkenOben.height());
    p->drawPixmap(0, yBalkenOben - pm.height()/2, pm);

    pm = balkenUnten.scaled(balkenUnten.width(), balkenUnten.height() - (per/100.)*balkenUnten.height());
    p->drawPixmap(0, yBalkenUnten - pm.height()/2, pm);
}

void GlMenuQuick::rollOut(QPainter *p)
{
    /*Ale Buttons werden weggerollt*/

    int per = getPercent();
    int angle = int((per/100.)*90);

    if(per < 0 || per > 100) return;

    labelYear->drawImageAt(p, angle, per);
    comboBoxYear->drawImageAt(p, angle, per);
    labelRandom->drawImageAt(p, angle, per);
    comboBoxRandom->drawImageAt(p, angle, per);
    labelPoints->drawImageAt(p, angle, per);
    comboBoxPoints->drawImageAt(p, angle, per);
    labelAdded->drawImageAt(p, angle, per);
    comboBoxAdded->drawImageAt(p, angle, per);
    buttonMain->drawImageAt(p, angle, per);
    buttonClear->drawImageAt(p, angle, per);

    QPixmap pm;
    pm = balkenOben.scaled(balkenOben.width(), balkenOben.height() - (per/100.)*balkenOben.height());
    p->drawPixmap(0, yBalkenOben - pm.height()/2, pm);

    pm = balkenUnten.scaled(balkenUnten.width(), balkenUnten.height() - (per/100.)*balkenUnten.height());
    p->drawPixmap(0, yBalkenUnten - pm.height()/2, pm);
}
void GlMenuQuick::comboBoxClosed(GlComboBox* cb)
{
    Q_UNUSED(cb);

    for(int i = 0; i < listChilds.size(); i++)
       {
         listChilds.at(i)->setVisible(true);
       }
    newChildToDraw(this);
}

void GlMenuQuick::comboBoxOpen(GlComboBox* cb)
{
    for(int i = 0; i < listChilds.size(); i++)
       {
         listChilds.at(i)->setVisible(false);
       }

    cb->setVisible(true);
    newChildToDraw(cb);
}
