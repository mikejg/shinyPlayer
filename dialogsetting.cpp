#include "dialogsetting.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>


DialogSetting::DialogSetting(QWidget * parent , Qt::WindowFlags f, Settings* s) : QDialog(parent,f)
{
    /*Zeiger auf die Struktur Settings. Der Zeiger wird an alle Klassen weitergereit die
      auf die Settings zugreifen müssen*/
    globalSettings = s;

    /*Objekt QSettings erstellen. Es wird auch das Verzeichnis $HOME/.config/Mike Gareiss erstellt
      in dem Verzeichnis wird die Datei shinyPlayer.conf angelegt.*/
    settings = new QSettings("Mike Gareiss", "shinyPlayer");

    /*GUI Elemente für Amarok embedded*/
    cb_embeddedSql = new QCheckBox("Amarok Embended SQL default", this);
    le_embeddedSql = new QLineEdit(this);
    le_embeddedSql->setMinimumWidth(400);
    pb_embeddedSql = new QPushButton("Browse", this);
    fd_embeddedSql = new QFileDialog(this, "Open Directory", QDir::homePath());
    fd_embeddedSql->setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    fd_embeddedSql->setFilter(QDir::Hidden);
    fd_embeddedSql->setFileMode(QFileDialog::Directory);

    /*GUI Elemente für qmdb SQL*/

    cb_qmdbSql = new QCheckBox("qMDB SQL", this);
    le_qmdbServer = new QLineEdit(this);
    le_qmdbServer->setEnabled(false);

    pb_Ok = new QPushButton("OK", this);

    layoutMaster = new QVBoxLayout(this);
    layoutMaster->addWidget(cb_embeddedSql);
    layoutEmbeddedSql = new QHBoxLayout();
    layoutEmbeddedSql->addWidget(le_embeddedSql);
    layoutEmbeddedSql->addWidget(pb_embeddedSql);

    layoutMaster->addLayout(layoutEmbeddedSql);
    layoutMaster->addWidget(cb_qmdbSql);
    layoutMaster->addWidget(le_qmdbServer);
    layoutMaster->addWidget(pb_Ok);

    connect(cb_embeddedSql, SIGNAL(stateChanged(int)), this, SLOT(cb_embeddedSql_StateChanged(int)));
    connect(cb_qmdbSql, SIGNAL(stateChanged(int)), this, SLOT(cb_qmdbSql_StateChanged(int)));
    connect(pb_embeddedSql, SIGNAL(clicked()), this, SLOT(pb_Browse_clicked()));
    connect(fd_embeddedSql, SIGNAL(fileSelected(QString)), this, SLOT(fd_embeddedSql_fileSelectet(QString)));
    connect(pb_Ok, SIGNAL(clicked()), this, SLOT(pb_Ok_Clicked()));

    readSetting();
    //writeSetting();
}

bool DialogSetting::checkSetting(QStringList* errorList)
{
    /*Überprüfen ob alle Einstellungen plausiebel sind. Wenn probleme auftreten
    werden sie in der errorList eingetragen und false zurückgegeben*/

    bool settingsOK = true;

    if(cb_embeddedSql->isChecked())
    {
        QDir dir (le_embeddedSql->text());
        if(!dir.exists())
        {
            /*Der Pfad zur Amarok Embedded Datenbank ist nicht vorhanden*/
            errorList->append(QString("Can't found directory ") + le_embeddedSql->text() + QString("\n"));
            settingsOK = false;
        }

        else
        {
            /*Passt! Einstellungen für die Amarok embedded Datenbank in die Struktur globalSetting eintragen*/
            globalSettings->embeddedSql = cb_embeddedSql->isChecked();
            globalSettings->embeddedPath = le_embeddedSql->text();
        }
    }

    if(cb_qmdbSql->isChecked())
    {
        globalSettings->qmdbSQL = cb_qmdbSql->isChecked();
        QString stringIP = le_qmdbServer->text();
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(le_qmdbServer->text());
        db.setDatabaseName("qmdb");
        db.setUserName("qmdbuser");
        db.setPassword("qmdb");
        if(!db.open())
        {
            errorList->append(QString("Can't open qMDB Server\n"));
            settingsOK = false;
        }

        else
            db.close();
    }
    return settingsOK;
}

void DialogSetting::readSetting()
{
    /*Einstellungen einlesen*/
    globalSettings->embeddedSql = settings->value("Embedded_SQL/enable", true).toBool();
    QString defaultPath = QDir::homePath() + "/.kde/share/apps/amarok";
    globalSettings->embeddedPath = settings->value("Embedded_SQL/Path", defaultPath).toString();
    le_embeddedSql->setText(globalSettings->embeddedPath);

    if (globalSettings->embeddedSql)
    {
        cb_embeddedSql->setChecked(true);
    }
    else
    {
        le_embeddedSql->setEnabled(false);
        pb_embeddedSql->setEnabled(false);
    }

    globalSettings->qmdbSQL = settings->value("qMDB_SQL/enable", false).toBool();
    globalSettings->qmdbServerIP = settings->value("qMDB_SQL/Server", "localhost").toString();
    le_qmdbServer->setText(globalSettings->qmdbServerIP);

    if (globalSettings->qmdbSQL)
    {
        cb_qmdbSql->setChecked(true);
    }
}

void DialogSetting::writeSetting()
{
    /*Einstellungen in $HOME/.config/Mike Gareiss/shinyPlayer.conf schreiben
    und in die Struktur globalSettings eintragen*/

    settings->setValue("Embedded_SQL/enable", cb_embeddedSql->isChecked());
    globalSettings->embeddedSql = cb_embeddedSql->isChecked();

    if(cb_embeddedSql->isChecked())
    {
        settings->setValue("Embedded_SQL/Path", le_embeddedSql->text());
        globalSettings->embeddedPath = le_embeddedSql->text();
    }

    settings->setValue("qMDB_SQL/enable", cb_qmdbSql->isChecked());
    globalSettings->qmdbSQL = cb_qmdbSql->isChecked();

    if(cb_qmdbSql->isChecked())
    {
        settings->setValue("qMDB_SQL/Server", le_qmdbServer->text());
        globalSettings->qmdbServerIP = le_qmdbServer->text();
    }
}

//SLOTS
void DialogSetting::cb_embeddedSql_StateChanged(int state)
{
    /*SLOT: Wird ausgeführt wenn sich die CheckBox für Amarok embedded
      geändert hat*/
    if(state == Qt::Checked)
    {
        le_embeddedSql->setEnabled(true);
        pb_embeddedSql->setEnabled(true);
        le_qmdbServer->setEnabled(false);
        if(cb_qmdbSql->isChecked())
            cb_qmdbSql->setChecked(false);
    }

    else
    {
        le_embeddedSql->setEnabled(false);
        pb_embeddedSql->setEnabled(false);
        if(!cb_qmdbSql->isChecked())
            cb_qmdbSql->setChecked(true);
    }


}

void DialogSetting::cb_qmdbSql_StateChanged(int state)
{
    if(state == Qt::Checked)
    {
        le_embeddedSql->setEnabled(false);
        pb_embeddedSql->setEnabled(false);
        le_qmdbServer->setEnabled(true);
        if(cb_embeddedSql->isChecked())
            cb_embeddedSql->setChecked(false);
    }

    else
    {
        le_qmdbServer->setEnabled(false);
        if(!cb_embeddedSql->isChecked())
            cb_embeddedSql->setChecked(true);
    }


}

void DialogSetting::fd_embeddedSql_fileSelectet(QString s)
{
    /*SLOT: Wird ausgeführt wenn über den FileDialog der Pfad zur
      Amarok embedded ausgewält wurde*/
    le_embeddedSql->setText(s);
}

void DialogSetting::pb_Browse_clicked()
{
    /*SLOT: Wird ausgeführt wenn der Button Browse angeklickt wurde
            Öffnet den FileDialog zum auswählen des Pfads der Amarok
            embedded Datenbank.*/
    fd_embeddedSql->show();
}

void DialogSetting::pb_Ok_Clicked()
{
    /*SLOT: Wird ausgeführt wenn der Button Ok angeklickt wurde
            Überprüft die Einstellungen und zeigt Fehler an*/
    QStringList* errorList = new QStringList();
    QString errorString;
    if(!checkSetting(errorList))
    {
        for(int i = 0; i < errorList->size(); i++)
            errorString = errorString + errorList->at(i);

        QMessageBox::warning(this, QString("Error"),
                                          errorString,
                                          "OK",
                                          QString(),
                                          QString(),
                                          0);

    }

    else
    {
        writeSetting();
        readSetting();
        this->accept();
    }
}
