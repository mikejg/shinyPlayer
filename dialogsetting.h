/* Ein Dialog zum konvigurieren des Players */

#ifndef DIALOGSETTING_H
#define DIALOGSETTING_H

#include <QDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QFileDialog>
#include "settings.h"

class DialogSetting : public QDialog
{
    Q_OBJECT

private:
    QSettings* settings;
    QVBoxLayout* layoutMaster;
    QHBoxLayout* layoutEmbeddedSql;
    QCheckBox* cb_embeddedSql;
    QCheckBox* cb_qmdbSql;
    QLineEdit* le_embeddedSql;
    QLineEdit* le_qmdbServer;
    QFileDialog* fd_embeddedSql;
    QPushButton* pb_embeddedSql;
    QPushButton* pb_Ok;

    Settings* globalSettings;

    void readSetting();
    void writeSetting();

public:
    DialogSetting(QWidget * parent = 0, Qt::WindowFlags f = 0, Settings* s = 0);

    bool checkSetting(QStringList*);

    Settings* getGlobalSettings() { return globalSettings; }
public slots:

    void cb_embeddedSql_StateChanged(int state);
    void cb_qmdbSql_StateChanged(int state);
    void fd_embeddedSql_fileSelectet(QString);
    void pb_Browse_clicked();
    void pb_Ok_Clicked();
};

#endif // DIALOGSETTING_H
