#ifndef LEDBOOM_H
#define LEDBOOM_H

#include <QObject>
#include <phonon/audiodataoutput.h>
#include <QMap>
#include "fht.h"
#include <vector>
#include <cmath>
#include <inttypes.h>
#include "usbconfig.h"

extern "C"
{
#include "hiddata.h"
}

class LedBoom : public QObject
{
    Q_OBJECT
private:
    usbDevice_t *dev;
    char        buffer[65];    /* room for dummy report ID */
    int         err;
    int fehler;
    int counter;
    int frameRate;
    bool stopIt;
    bool leer;
    QString fehlerString;

public:
    static const int HEIGHT      = 2;
    static const int WIDTH       = 4;
    static const int MIN_ROWS    = 3;   //arbituary
    static const int MIN_COLUMNS = 21;  //arbituary
    static const int MAX_COLUMNS = 21; //must be 2**n

    QVector<float> m_scope; //so we don't create a vector every frame

    float m_step; //rows to fall per frame
    QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > thescope;
    QList<QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >* > listeScope;
    std::vector<float> m_store;  //current bar heights
    std::vector<float> m_yscale;
    FHT    *m_fht;

    LedBoom(QObject *parent = 0);
    void setUsbDevice(usbDevice_t* d) { dev = d; }
    void analyze(const QVector<float>&);
    void interpolate( const QVector<float> &inVec, QVector<float> &outVec );
    void schreibeBuffer(int r);
    void transform(QVector<float>&);
    void setStopIt(bool b) {stopIt = b;}
    void setLeer(bool b) {leer = b;}
    void clearLed();

signals:
    void newUsbDevice();

public slots:
    void clearList();
    void doit();
    void insertScope(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &);
    void restart();
};

#endif // LEDBOOM_H
