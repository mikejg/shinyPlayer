#ifndef GLVIZUALIZER_H
#define GLVIZUALIZER_H

#include "globject.h"
#include <phonon/audiodataoutput.h>
#include <QMap>
#include "fht.h"
#include <vector>
#include <cmath>
#include <inttypes.h>

class GlVizualizer : public GlObject
{
    Q_OBJECT
private:
    QColor borderColor;
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QPen pen;

    int border;
    int borderRadius;

public:
    int counter;
    bool stopIt;
    bool balken;
    char        blockValue[25];

    /*int oldValue1(int);
    int oldValue2(int);
    int oldValue3(int);
    int oldValue4(int);
    int oldValue5(int);
    int oldValue6(int);
    int oldValue7(int);*/

    static const int HEIGHT      = 2;
    static const int WIDTH       = 4;
    static const int MIN_ROWS    = 3;   //arbituary
    static const int MIN_COLUMNS = 20;  //arbituary
    static const int MAX_COLUMNS = 20; //must be 2**n

    QVector<float> m_scope; //so we don't create a vector every frame
    float m_step; //rows to fall per frame
    QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > thescope;
    QList<QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >* > listeScope;
    std::vector<float> m_store;  //current bar heights
    std::vector<float> m_yscale;
    FHT    *m_fht;

    GlVizualizer(GlObject *parent = 0);
    void analyze(const QVector<float>&);
    void draw(QPainter *p);
    void drawRect(QPainter *p, int posx, int posy);
    void interpolate( const QVector<float> &inVec, QVector<float> &outVec );
    //void schreibeBlockValue();
    void transform(QVector<float>&);
    void setStopIt(bool b) {stopIt = b;}
    void setBalken(bool b) {balken = b;}

signals:

public slots:
    void clearList();
    void doit();
    void insertScope(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &);
};

#endif // GLVIZUALIZER_H
