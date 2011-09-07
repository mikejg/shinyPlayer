/* Database ist eine Abstrakte Klasse von der die Klassen
   für verschiedene Datenbanken abgeleitet werden. */

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include <QDebug>

class Database : public QObject
{
    Q_OBJECT

private:
    QString embeddedPath;

public:
    Database(QObject* parent);

    QString getEmbeddedPath() { return embeddedPath; }
    virtual QStringList getAlbenFromInterpret(QString s) { return getStringListFromQuery(s); }
    virtual QStringList getInterpreten(QString s) { return getStringListFromQuery(s); }
    virtual QPixmap getCover(QString i, QString a);
    virtual QString getStringFromQuery(QString queryString);
    virtual QStringList getStringListFromQuery(QString queryString);
    virtual void openDataBase() {}

    void setEmbeddedPath(QString ep) { embeddedPath = ep; }
};

#endif // DATABASE_H
