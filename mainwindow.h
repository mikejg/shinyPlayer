#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QPainter>
#include <QList>
#include <QTimeLine>

#include "dialogsetting.h"
#include "settings.h"
#include "glmainmenu.h"
#include "glmenuinterpret.h"
#include "glmenugenre.h"
#include "glmenualben.h"
#include "glmenuplayer.h"
#include "globject.h"
#include "play_engine.h"

class MainWindow : public QGLWidget {
    Q_OBJECT

private:
    QList<GlObject *> listChilds;
    QList<GlObject *> drawPuffer;
    QTimeLine* timeLine;

    bool animation;

    DialogSetting* setting;
    Settings* set;
    Play_Engine* playEngine;
    GlMainMenu* mainMenu;
    GlMenuGenre* menuGenre;
    GlMenuInterpret* menuInterpret;
    GlMenuAlben* menuAlben;
    GlMenuPlayer* menuPlayer;

public:
    MainWindow(QWidget *parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0 );
    ~MainWindow();

    void (MainWindow::*doAnimation)(QPainter* p);
    void (MainWindow::*doAnimation_second)(QPainter* p);

    void mainMenu_RollIn(QPainter* p) { mainMenu->rollIn(p); }
    void mainMenu_RollOut(QPainter* p) { mainMenu->rollOut(p); }
    void menuAlben_RollIn(QPainter* p) { menuAlben->rollIn(p); }
    void menuAlben_RollOut(QPainter* p) { menuAlben->rollOut(p); }
    void menuGenre_RollIn(QPainter* p) { menuGenre->rollIn(p); }
    void menuInterpret_RollIn(QPainter* p) { menuInterpret->rollIn(p); }
    void menuInterpret_RollOut(QPainter* p) { menuInterpret->rollOut(p); }
    void menuPlayer_RollIn(QPainter* p) { menuPlayer->rollIn(p); }
    void menuPlayer_RollOut(QPainter* p) { menuPlayer->rollOut(p); }

public slots:
    void albumSelected(QString, QString);
    void animationDone();

    void interpretSelected(QString);

    void newChildToDraw(GlObject*);

    void mainMenu_ButtonGenre_clicked();
    void mainMenu_ButtonInterpret_clicked();
    void mainMenu_ButtonPlayer_clicked();

    void menuAlben_ButtonInterpret_clicked();
    void menuAlben_ButtonMain_clicked();
    void menuAlben_ButtonPlayer_clicked();

    void menuInterpret_ButtonMain_clicked();
    void menuInterpret_ButtonPlayer_clicked();

    void menuPlayer_ButtonMain_clicked();

    void setLarge();
    void setMainMenu_RollIn();
    void setMenuAlben_RollIn();
    void setMenuGenre_RollIn();
    void setMenuInterpret_RollIn();
    void setMenuPlayer_RollIn();

protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
