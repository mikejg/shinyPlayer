#include "mainwindow.h"

#include <QStringList>
#include <QString>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f) :
        QGLWidget(parent, shareWidget, f)
{
    animation = false;

    timeLine = new QTimeLine(500, this);
    timeLine->setLoopCount(1);
    timeLine->setFrameRange(0, 100);
    timeLine->setCurveShape(QTimeLine::EaseInCurve);

    set = new Settings;
    setGeometry(0,0,800,600);

    setting = new DialogSetting(this,0,set);
    QStringList* errorList = new QStringList();
    QString errorString;

    /*Der Konstruktor von DialogSetting liest die Einstellungen ein.
      Die Einstellungen werden getest und das Ergebnis in die
      ErrorList geschrieben.*/
    if(!setting->checkSetting(errorList))
    {
        //Die Strings in der errorList werden zu einen String zusammengefasst
        for(int i = 0; i < errorList->size(); i++)
            errorString = errorString + errorList->at(i);

        //Eine MessageBox wird aus dem errorString erzeugt
        int result = QMessageBox::warning(this, QString("Error"),
                                          errorString,
                                          "Cancel",
                                          "Edit",
                                          QString(),
                                          0,0);

        //Nach dem regulären Beenden der MessageBox wird der settingDialog angezeigt
        //Wird die MessageBox mit X beendet habt ihr Pech gehabt
        if(result)
        {
            //Wird der settingDialg mit X beendet Pech gehabt
            if(!setting->exec())
            {
                qDebug("Error Settings");
                return;
            }
        }
        else
        {
            qDebug("Error Settings");
            return;
        }
    }

    mainMenu = new GlMainMenu();

    listChilds.append(mainMenu);
    drawPuffer.append(mainMenu);

    connect(mainMenu, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));
    connect(mainMenu, SIGNAL(update()), this, SLOT(update()));

    connect(mainMenu, SIGNAL(buttonGenre_clicked()), this, SLOT(mainMenu_ButtonGenre_clicked()));
    //connect(mainMenu, SIGNAL(buttonInterpret_clicked()), this, SLOT(mainMenu_ButtonInterpret_clicked()));

    menuInterpret = new GlMenuInterpret();
    listChilds.append(menuInterpret);
    connect(menuInterpret, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));

    menuGenre = new GlMenuGenre();
    listChilds.append(menuGenre);
    connect(menuGenre, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));
    connect(menuGenre, SIGNAL(update()), this, SLOT(update()));

    //setLarge();
}

MainWindow::~MainWindow()
{

}

void MainWindow::animationDone()
{
    animation = false;
    timeLine->setDirection(QTimeLine::Forward);

    if(doAnimation == &MainWindow::menuGenre_RollIn)
    {
        drawPuffer.append(menuGenre);
        menuGenre->setVisible(true);
    }
}

void MainWindow::mainMenu_ButtonGenre_clicked()
{
    mainMenu->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::mainMenu_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), mainMenu, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMenuGenre_RollIn()));

    timeLine->start();
}

void MainWindow::mainMenu_ButtonInterpret_clicked()
{
    mainMenu->setVisible(false);
    menuInterpret->setVisible(true);
    newChildToDraw(menuInterpret);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
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

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
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

void MainWindow::newChildToDraw(GlObject * glObject)
{
    drawPuffer.append(glObject);
    update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    setAutoFillBackground(false);

    if(!drawPuffer.isEmpty())
    {
        drawPuffer.at(0)->draw(&p);
        drawPuffer.pop_front();
    }

    if(animation)
    {
        p.setClipRect(e->rect());
        p.fillRect(rect(), Qt::black);
        (this->*doAnimation)(&p);
    }
}

void MainWindow::setLarge()
{
    setGeometry(0,0,1024,768);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}

void MainWindow::setMenuGenre_RollIn()
{
    timeLine->disconnect();

    connect(timeLine, SIGNAL(frameChanged(int)), menuGenre, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(animationDone()));

    timeLine->setDirection(QTimeLine::Backward);
    doAnimation = &MainWindow::menuGenre_RollIn;

    timeLine->start();
}
