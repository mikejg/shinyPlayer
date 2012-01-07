#include "ledboom.h"
#include <QTimer>
#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <usb.h>

LedBoom::LedBoom(QObject *parent) :
    QObject(parent)
    , m_scope( MIN_COLUMNS )
    , m_store( 1 << 8, 0 )
    , m_fht(new FHT(9))
{
    uint m_rows    = 10;
    m_yscale.resize( m_rows + 1 );

    const float PRE = 1, PRO = 1; //PRE and PRO allow us to restrict the range somewhat

    for( uint z = 0; z < m_rows; ++z )
           m_yscale[z] = 1 - (log10( PRE+z ) / log10( PRE+m_rows+PRO ));

    m_yscale[m_rows] = 0;

    const double fallTime = 30 * m_rows;
    m_step = double(m_rows * 80) / fallTime;

    counter = 0;
    frameRate = 25;
    listeScope.clear();
    setLeer(true);
  }

void LedBoom::analyze( const QVector<float> &s )
{
    interpolate( s, m_scope );
    uint y;
    uint y_all = 0;

    for(int x = 0; x < m_scope.size(); ++x)
    {
       // determine y
       for( y = 0; m_scope[x] < m_yscale[y]; ++y )
          ;

       // this is opposite to what you'd think, higher than y
       // means the bar is lower than y (physically)
       if( (float)y > m_store[x] )
          y = uint(m_store[x] += m_step);
       else
          m_store[x] = y;

       //REMEMBER: y is a number from 0 to m_rows, 0 means all blocks are glowing, m_rows means none are
       y_all += (10-y);
    }

    y_all = y_all / 20;
    schreibeBuffer(y_all);
}

void LedBoom::clearList()
{
    listeScope.clear();
}

void LedBoom::doit()
{
    if(stopIt) return;

    if(listeScope.isEmpty())
    {
        qDebug("liste leer");
        QTimer::singleShot(100, this, SLOT(doit()));
        return;
    }
    counter++;
    thescope = *listeScope.last();
    static QVector<float> scope( 512 );
    int i = 0;

    for( uint x = 0; (int)x < m_fht->size(); ++x )
    {
       scope[x] = double(thescope[Phonon::AudioDataOutput::LeftChannel][x]
                        + thescope[Phonon::AudioDataOutput::RightChannel][x])
                        / (2*(1<<15)); // Average between the channels
       i += 2;
    }

    transform(scope);
    analyze(scope);

    scope.resize( m_fht->size() );

    QTimer::singleShot(frameRate, this, SLOT(doit()));
}

void LedBoom::insertScope(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &s)
{
    QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >* sPointer =
            new QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >;
    *sPointer = s;
    if(listeScope.size() > 3)
    {
        listeScope.pop_front();
    }
    listeScope.append(sPointer);
}

void LedBoom::interpolate( const QVector<float> &inVec, QVector<float> &outVec )
{
    double pos = 0.0;
    const double step = (double)inVec.size() / outVec.size();

    for (int i = 0; i < outVec.size(); ++i, pos += step)
    {
        const double error = pos - std::floor( pos );
        const unsigned long offset = (unsigned long)pos;

        long indexLeft = offset + 0;

        if (indexLeft >= inVec.size())
            indexLeft = inVec.size() - 1;

        long indexRight = offset + 1;

        if (indexRight >= inVec.size())
            indexRight = inVec.size() - 1;

        outVec[i] = inVec[indexLeft ] * ( 1.0 - error ) +
                    inVec[indexRight] * error;
    }
}

void LedBoom::schreibeBuffer(int r)
{
    static int oldRing = 0;
    static int falldownRing = 0;
    static int ringCount = 0;
    static int updown = -1;

    bzero(buffer, sizeof(buffer));
    buffer[1] = 5;
    if(leer)
        buffer[2] = 21;
    else
        buffer[2] = 20;

    //(full) ? buffer[2] = 20 : buffer[2]=21;

    if(oldRing == r)
    {
        falldownRing = falldownRing + updown;
        if (falldownRing == 0 || falldownRing == r)
            updown *= (-1);
        buffer[3] = falldownRing;
    }
    else
    {
        oldRing = r;
        falldownRing = r;
        updown = -1;
        ringCount = 0;
        buffer[3] = r;
    }

    fehler = usbhidSetReport(dev, buffer, 8);

    if(fehler == 2)
    {
        frameRate = frameRate + 50;
        fehlerString = usb_strerror();
        if(fehlerString == QString("error sending control message: Kein passendes Gerät gefunden"))
        {
            setStopIt(true);
            QTimer::singleShot(500, this, SLOT(restart()));
        }
        qDebug() << QString("fehler beim schreiben %1").arg(frameRate);
    }

    if(fehler == 0 && frameRate > 35)
        frameRate = frameRate - 5;
}

void LedBoom::clearLed()
{
    bzero(buffer, sizeof(buffer));
    buffer[1] = 5;
    buffer[2] = 1;

    if( usbhidSetReport(dev, buffer, 4) != 0 )
      {
        qDebug("fehler beim schreiben");
      }
}

void LedBoom::transform(QVector<float> &s )
{

    for(int x = 0; x < s.size(); ++x)
        s[x] *= 2;

    float *front = static_cast<float*>( &s.front() );

    m_fht->spectrum( front );
    m_fht->scale( front, 1.0 / 20 );

    //the second half is pretty dull, so only show it if the user has a large analyzer
    //by setting to m_scope.size() if large we prevent interpolation of large analyzers, this is good!
    s.resize( m_scope.size() <= MAX_COLUMNS/2 ? MAX_COLUMNS/2 : m_scope.size() );
}

void LedBoom::restart()
{
    qDebug() << Q_FUNC_INFO;
    newUsbDevice();
    //setStopIt(false);
    //QTimer::singleShot(1500, this, SLOT(doit()));
}
