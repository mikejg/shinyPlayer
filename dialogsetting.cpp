#include "dialogsetting.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>


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

    pb_Ok = new QPushButton("OK", this);

    layoutMaster = new QVBoxLayout(this);
    layoutMaster->addWidget(cb_embeddedSql);
    layoutEmbeddedSql = new QHBoxLayout();
    layoutMaster->addLayout(layoutEmbeddedSql);
    layoutEmbeddedSql->addWidget(le_embeddedSql);
    layoutEmbeddedSql->addWidget(pb_embeddedSql);
    layoutMaster->addWidget(pb_Ok);

    connect(cb_embeddedSql, SIGNAL(stateChanged(int)), this, SLOT(cb_embeddedSql_StateChanged(int)));
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
    }

    /*Passt! Einstellungen für die Amarok embedded Datenbank in die Struktur globalSetting eintragen*/
    globalSettings->embeddedSql = cb_embeddedSql->isChecked();
    globalSettings->embeddedPath = le_embeddedSql->text();
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
    }

    else
    {
        le_embeddedSql->setEnabled(false);
        pb_embeddedSql->setEnabled(false);
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
