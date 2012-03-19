#ifndef DB_QMDB_SQL_H
#define DB_QMDB_SQL_H

#include "database.h"
#include <QtSql>
#include <QSqlDatabase>

class DB_QMDB_SQL : public Database
{
    Q_OBJECT
private:
    QSqlDatabase db;

public:
    DB_QMDB_SQL(QObject *parent = 0);
    void openDataBase(QString server);
    QString getCoverPath(QString i, QString a);

    QStringList getAlbenFromInterpret(QString s);
    QPixmap getCover(QString i, QString a);
    QStringList getInterpreten(QString s);
    QStringList getStringListFromQuery(QString queryString);

    QList<MetaPaket> getTracksFromAlbum(QString interpret, QString album);
    QList<MetaPaket> getTracksFromQuick(int y1, int y2, uint t, int p, bool br);

    void setNewPoints(MetaPaket mp);
    void upDateAccess(MetaPaket mp);

signals:

public slots:

};

#endif // DB_QMDB_SQL_H
