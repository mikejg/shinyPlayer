#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include "dialogsetting.h"
#include "settings.h"

class MainWindow : public QGLWidget {
    Q_OBJECT
private:
    DialogSetting* setting;
    Settings* set;
public:
    MainWindow(QWidget *parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0 );
    ~MainWindow();

};

#endif // MAINWINDOW_H
