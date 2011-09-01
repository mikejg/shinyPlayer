/* Database ist eine Abstrakte Klasse von der die Klassen
   für verschiedene Datenbanken abgeleitet werden. */

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QStringList>

class Database : public QObject
{
    Q_OBJECT

private:
    QString embeddedPath;

public:
    Database(QObject* parent);

    QString getEmbeddedPath() { return embeddedPath; }
    virtual QStringList getInterpreten(QString s);
    virtual void openDataBase() {}

    void setEmbeddedPath(QString ep) { embeddedPath = ep; }
};

#endif // DATABASE_H
