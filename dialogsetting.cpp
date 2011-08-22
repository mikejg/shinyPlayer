#include "dialogsetting.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>


DialogSetting::DialogSetting(QWidget * parent = 0, Qt::WindowFlags f = 0, Settings* s = 0) : QDialog(parent,f)
{
    globalSettings = s;

    settings = new QSettings("Mike Gareiss", "shinyPlayer");
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
    bool settingsOK = true;

    if(cb_embeddedSql->isChecked())
    {
        QDir dir (le_embeddedSql->text());
        if(!dir.exists())
        {
            errorList->append(QString("Can't found directory ") + le_embeddedSql->text() + QString("\n"));
            settingsOK = false;
        }
    }
    return settingsOK;
}

void DialogSetting::readSetting()
{
    //embedded sql
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
    settings->setValue("Embedded_SQL/enable", cb_embeddedSql->isChecked());
    if(cb_embeddedSql->isChecked())
        settings->setValue("Embedded_SQL/Path", le_embeddedSql->text());
}

//SLOTS
void DialogSetting::cb_embeddedSql_StateChanged(int state)
{
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
    le_embeddedSql->setText(s);
}

void DialogSetting::pb_Browse_clicked()
{
    fd_embeddedSql->show();
}

void DialogSetting::pb_Ok_Clicked()
{
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
