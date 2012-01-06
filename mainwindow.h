#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QPainter>
#include <QList>
#include <QTimeLine>

#include "usbconfig.h"
#include "dialogsetting.h"
#include "settings.h"
#include "glmainmenu.h"
#include "glmenuinterpret.h"
#include "glmenugenre.h"
#include "glmenualben.h"
#include "glmenuplayer.h"
#include "glmenuplaylist.h"
#include "glmenuquick.h"
#include "glmenusampler.h"
#include "glmenuradio.h"
#include "globject.h"
#include "play_engine.h"

extern "C"
{
#include "hiddata.h"
}


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
    GlMenuPlaylist* menuPlaylist;
    GlMenuQuick* menuQuick;
    GlMenuRadio* menuRadio;
    GlMenuSampler* menuSampler;

    usbDevice_t *dev;
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
    void menuPlaylist_RollIn(QPainter* p) { menuPlaylist->rollIn(p);}
    void menuPlaylist_RollOut(QPainter* p) { menuPlaylist->rollOut(p);}
    void menuRadio_RollIn(QPainter* p) { menuRadio->rollIn(p);}
    void menuRadio_RollOut(QPainter* p) { menuRadio->rollOut(p);}
    void menuSampler_RollIn(QPainter* p) { menuSampler->rollIn(p);}
    void menuSampler_RollOut(QPainter* p) { menuSampler->rollOut(p);}
    void menuQuick_RollIn(QPainter* p) { menuQuick->rollIn(p); }
    void menuQuick_RollOut(QPainter* p) { menuQuick->rollOut(p); }

    usbDevice_t* openDevice(void);

public slots:
    void albumSelected(QString, QString);
    void animationDone();

    void interpretSelected(QString);

    void newChildToDraw(GlObject*);

    void mainMenu_ButtonGenre_clicked();
    void mainMenu_ButtonInterpret_clicked();
    void mainMenu_ButtonPlayer_clicked();
    void mainMenu_ButtonPlaylist_clicked();
    void mainMenu_ButtonQuick_clicked();
    void mainMenu_ButtonSampler_clicked();
    void mainMenu_ButtonRadio_clicked();

    void menuAlben_ButtonInterpret_clicked();
    void menuAlben_ButtonMain_clicked();
    void menuAlben_ButtonPlayer_clicked();

    void menuInterpret_ButtonMain_clicked();
    void menuInterpret_ButtonPlayer_clicked();

    void menuPlayer_ButtonMain_clicked();

    void menuPlaylist_ButtonMain_clicked();
    void menuPlaylist_ButtonPlayer_clicked();

    void menuQuick_ButtonMain_clicked();

    void menuRadio_ButtonMain_clicked();

    void menuSampler_ButtonMain_clicked();
    void menuSampler_ButtonPlayer_clicked();

    void playlistSelected(QString);

    void quickSelected(int, int, uint, int, bool);
    void radioSelected(QString);

    void samplerSelected(QString);
    void setLarge();
    void setMainMenu_RollIn();
    void setMenuAlben_RollIn();
    void setMenuGenre_RollIn();
    void setMenuInterpret_RollIn();
    void setMenuPlayer_RollIn();
    void setMenuPlaylist_RollIn();
    void setMenuRadio_RollIn();
    void setMenuSampler_RollIn();
    void setMenuQuick_RollIn();

    void titleSelected(MetaPaket);

protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
