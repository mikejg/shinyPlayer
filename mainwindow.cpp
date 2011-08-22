#include "mainwindow.h"

#include <QStringList>
#include <QString>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f) :
        QGLWidget(parent, shareWidget, f)
{
    set = new Settings;

    setting = new DialogSetting(this,0,set);
    QStringList* errorList = new QStringList();
    QString errorString;

    /*Im Konstruktor von DialogSetting liest die Einstellungen ein.
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
}

MainWindow::~MainWindow()
{

}

