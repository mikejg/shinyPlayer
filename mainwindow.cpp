#include "mainwindow.h"

#include <QStringList>
#include <QString>
#include <QMessageBox>
#include <QDebug>

#include "db_amarok_embedded.h"

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

    set->db = new DB_Amarok_Embedded(this);
    set->db->setEmbeddedPath(set->embeddedPath);
    set->db->openDataBase();

    playEngine = new Play_Engine(this);

    mainMenu = new GlMainMenu();

    listChilds.append(mainMenu);
    drawPuffer.append(mainMenu);

    connect(mainMenu, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));
    connect(mainMenu, SIGNAL(update()), this, SLOT(update()));

    connect(mainMenu, SIGNAL(buttonGenre_clicked()), this, SLOT(mainMenu_ButtonGenre_clicked()));
    connect(mainMenu, SIGNAL(buttonInterpret_clicked()), this, SLOT(mainMenu_ButtonInterpret_clicked()));
    connect(mainMenu, SIGNAL(buttonPlayer_clicked()), this, SLOT(mainMenu_ButtonPlayer_clicked()));

    menuInterpret = new GlMenuInterpret();
    menuInterpret->setVisible(false);
    listChilds.append(menuInterpret);
    menuInterpret->setDatabase(set->db);

    connect(menuInterpret, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));
    connect(menuInterpret, SIGNAL(update()), this, SLOT(update()));
    connect(menuInterpret, SIGNAL(interpretSelected(QString)), this, SLOT(interpretSelected(QString)));
    connect(menuInterpret, SIGNAL(buttonMainClicked()), this, SLOT(menuInterpret_ButtonMain_clicked()));
    connect(menuInterpret, SIGNAL(buttonPlayerClicked()), this, SLOT(menuInterpret_ButtonPlayer_clicked()));

    menuGenre = new GlMenuGenre();
    listChilds.append(menuGenre);
    menuGenre->setVisible(false);

    connect(menuGenre, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));
    connect(menuGenre, SIGNAL(update()), this, SLOT(update()));

    menuAlben = new GlMenuAlben();
    menuAlben->setVisible(false);
    listChilds.append(menuAlben);
    menuAlben->setDatabase(set->db);

    connect(menuAlben, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));
    connect(menuAlben, SIGNAL(update()), this, SLOT(update()));
    connect(menuAlben, SIGNAL(newAlbumSelected(QString,QString)), this, SLOT(albumSelected(QString, QString)));
    connect(menuAlben, SIGNAL(backToInterpret()), this, SLOT(menuAlben_ButtonInterpret_clicked()));
    connect(menuAlben, SIGNAL(backToMain()), this, SLOT(menuAlben_ButtonMain_clicked()));
    connect(menuAlben, SIGNAL(backToPlayer()), this, SLOT(menuAlben_ButtonPlayer_clicked()));
    connect(menuAlben, SIGNAL(newTitleSelected(MetaPaket)), this, SLOT(titleSelected(MetaPaket)));

    menuPlayer = new GlMenuPlayer();
    menuPlayer->setVisible(false);
    listChilds.append(menuPlayer);
    menuPlayer->setDatabase(set->db);
    menuPlayer->setPlayEngine(playEngine);

    connect(menuPlayer, SIGNAL(newChildToDraw(GlObject*)), this, SLOT(newChildToDraw(GlObject*)));
    connect(menuPlayer, SIGNAL(update()), this, SLOT(update()));
    connect(menuPlayer, SIGNAL(buttonMain_clicked()), this, SLOT(menuPlayer_ButtonMain_clicked()));
    //setLarge();
}

MainWindow::~MainWindow()
{

}

void MainWindow::albumSelected(QString interpret, QString album)
{
    menuPlayer->insertNewAlbum(interpret, album);
}

void MainWindow::animationDone()
{
    /*SLOT: Wird ausgeführt wenn die Animation fertig ist*/
    animation = false;
    timeLine->setDirection(QTimeLine::Forward);

    menuInterpret->setPercent(-1);
    mainMenu->setPercent(-1);
    menuAlben->setPercent(-1);
    menuPlayer->setPercent(-1);

    if(doAnimation == &MainWindow::menuGenre_RollIn)
    {
        drawPuffer.append(menuGenre);
        menuGenre->setVisible(true);
    }

    if(doAnimation == &MainWindow::menuInterpret_RollIn)
    {
        drawPuffer.append(menuInterpret);
        update();
        menuInterpret->setVisible(true);
    }

    if(doAnimation == &MainWindow::menuAlben_RollIn)
    {
        drawPuffer.append(menuAlben);
        update();
        menuAlben->setVisible(true);
    }

    if(doAnimation == &MainWindow::mainMenu_RollIn)
    {
        drawPuffer.append(mainMenu);
        update();
        mainMenu->setVisible(true);
    }

    if(doAnimation == &MainWindow::menuPlayer_RollIn)
    {
        drawPuffer.append(menuPlayer);
        update();
        menuPlayer->setVisible(true);
    }
}

void MainWindow::interpretSelected(QString interpret)
{
    menuInterpret->setVisible(false);

    menuAlben->newInterpret(interpret);

    timeLine->disconnect();
    doAnimation = &MainWindow::menuInterpret_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), menuInterpret, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMenuAlben_RollIn()));

    timeLine->start();
}

void MainWindow::mainMenu_ButtonGenre_clicked()
{
    /*SLOT: Wird ausgeführt wenn auf den Button Genre geklickt wurde
      - MainMenu abschalten
      - Alle Verbindungen von TimeLine trennen
      - den Funktionszeiger doAnimation mit der Funktion mainMenu_RollOut laden
      - Bool animation auf true setzen (Siehe paintEvent)
      - Signal neu verbinden
      - TimeLine starten*/

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
    /*Siehe mainMenu_ButtonGenre_clicked*/
    mainMenu->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::mainMenu_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), mainMenu, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMenuInterpret_RollIn()));

    timeLine->start();
}

void MainWindow::mainMenu_ButtonPlayer_clicked()
{
    /*Siehe mainMenu_ButtonGenre_clicked*/
    mainMenu->setVisible(false);
    menuPlayer->setImage();

    timeLine->disconnect();
    doAnimation = &MainWindow::mainMenu_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), mainMenu, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMenuPlayer_RollIn()));

    timeLine->start();
}

void MainWindow::menuAlben_ButtonInterpret_clicked()
{
    menuAlben->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::menuAlben_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), menuAlben, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMenuInterpret_RollIn()));

    timeLine->start();
}

void MainWindow::menuAlben_ButtonPlayer_clicked()
{
    menuPlayer->setImage();

    menuAlben->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::menuAlben_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), menuAlben, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMenuPlayer_RollIn()));

    timeLine->start();
}

void MainWindow::menuAlben_ButtonMain_clicked()
{
    menuAlben->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::menuAlben_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), menuAlben, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMainMenu_RollIn()));
    timeLine->start();
}

void MainWindow::menuInterpret_ButtonMain_clicked()
{
    menuInterpret->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::menuInterpret_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), menuInterpret, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMainMenu_RollIn()));

    timeLine->start();
}

void MainWindow::menuInterpret_ButtonPlayer_clicked()
{
    menuPlayer->setImage();

    menuInterpret->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::menuInterpret_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), menuInterpret, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMenuPlayer_RollIn()));

    timeLine->start();
}

void MainWindow::menuPlayer_ButtonMain_clicked()
{
    menuPlayer->setImage();

    menuPlayer->setVisible(false);

    timeLine->disconnect();
    doAnimation = &MainWindow::menuPlayer_RollOut;

    animation = true;
    connect(timeLine, SIGNAL(frameChanged(int)), menuPlayer, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(setMainMenu_RollIn()));

    timeLine->start();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
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

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
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

void MainWindow::newChildToDraw(GlObject * glObject)
{
    /*SLOT: Wird ausgeführt wenn ein GlObject das Signal newChildToDraw sendet
      - das GlObject in die Liste drawPuffer schreiben
      - update löst ein Neuzeichnen aus (paintEvent)*/
    drawPuffer.append(glObject);
    update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    setAutoFillBackground(false);

    /*Solange sich in drawPuffer GlObject befinden werden
      diese geholt und gezeichnet*/
    while(!drawPuffer.isEmpty())
    {
        //qDebug("draw paintEvent");
        drawPuffer.at(0)->draw(&p);
        drawPuffer.pop_front();
    }

    /*Ist Bool animation true wird ein schwarzes Rechteck gezeichnet
      und dann die Funktion in dem Funktionszeiger doAnimation ausgeführt*/
    if(animation)
    {
        p.setClipRect(e->rect());
        p.fillRect(rect(), Qt::black);
        (this->*doAnimation)(&p);
    }
}

void MainWindow::setLarge()
{
    /*Alles auf 1024 x 768 zoomen*/
    setGeometry(0,0,1024,768);

    for(int i = 0; i < listChilds.size(); i++)
    {
       listChilds.at(i)->setLarge();
    }
}

void MainWindow::setMainMenu_RollIn()
{
    timeLine->disconnect();

    connect(timeLine, SIGNAL(frameChanged(int)), mainMenu, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(animationDone()));

    timeLine->setDirection(QTimeLine::Backward);
    doAnimation = &MainWindow::mainMenu_RollIn;

    timeLine->start();
}

void MainWindow::setMenuAlben_RollIn()
{
    timeLine->disconnect();

    connect(timeLine, SIGNAL(frameChanged(int)), menuAlben, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(animationDone()));

    timeLine->setDirection(QTimeLine::Backward);
    doAnimation = &MainWindow::menuAlben_RollIn;

    timeLine->start();
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

void MainWindow::setMenuInterpret_RollIn()
{
    /*SLOT: Wird ausgeführt wenn sich TimeLine Beendet hat. Wurde in
            mainMenu_ButtonInterpret_clicked() verbunden.
            - Alle Verbindungen von TimeLine trennen
            - Verbindungen neu einrichten
            - TimeLine auf rückwärts zählen stellen
            - Funktionzeiger doAnimation mit der Funktion menuInterpret_RollIn laden*/

    timeLine->disconnect();

    connect(timeLine, SIGNAL(frameChanged(int)), menuInterpret, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(animationDone()));

    timeLine->setDirection(QTimeLine::Backward);
    doAnimation = &MainWindow::menuInterpret_RollIn;

    timeLine->start();
}

void MainWindow::setMenuPlayer_RollIn()
{
    timeLine->disconnect();

    connect(timeLine, SIGNAL(frameChanged(int)), menuPlayer, SLOT(newFrame(int)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(animationDone()));

    timeLine->setDirection(QTimeLine::Backward);
    doAnimation = &MainWindow::menuPlayer_RollIn;

    timeLine->start();
}

void MainWindow::titleSelected(MetaPaket mp)
{
    menuPlayer->insertNewTitle(mp);
}
