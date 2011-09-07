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
#include "globject.h"

class MainWindow : public QGLWidget {
    Q_OBJECT

private:
    QList<GlObject *> listChilds;
    QList<GlObject *> drawPuffer;
    QTimeLine* timeLine;

    bool animation;

    DialogSetting* setting;
    Settings* set;
    GlMainMenu* mainMenu;
    GlMenuGenre* menuGenre;
    GlMenuInterpret* menuInterpret;
    GlMenuAlben* menuAlben;

public:
    MainWindow(QWidget *parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0 );
    ~MainWindow();

    void (MainWindow::*doAnimation)(QPainter* p);
    void (MainWindow::*doAnimation_second)(QPainter* p);

    void mainMenu_RollOut(QPainter* p) { mainMenu->rollOut(p); }
    void menuGenre_RollIn(QPainter* p) { menuGenre->rollIn(p); }
    void menuInterpret_RollIn(QPainter* p) { menuInterpret->rollIn(p); }

public slots:
    void animationDone();

    void interpretSelected(QString);

    void newChildToDraw(GlObject*);

    void mainMenu_ButtonGenre_clicked();
    void mainMenu_ButtonInterpret_clicked();

    void setLarge();
    void setMenuGenre_RollIn();
    void setMenuInterpret_RollIn();

protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
