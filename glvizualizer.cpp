#include "glvizualizer.h"
#include <QTimer>

GlVizualizer::GlVizualizer(GlObject *parent) : GlObject(parent)
  , m_scope( MIN_COLUMNS )
  , m_store( 1 << 8, 0 )
  , m_fht(new FHT(9))

{
    borderColor = QColor(66, 74, 90);
    gradientColorAt0 = QColor(40,40,40);
    gradientColorAt1 = QColor(96,112,144);
    border = 1;
    borderRadius = 10;


    uint m_rows    = 16;
    m_yscale.resize( m_rows + 1 );

    const float PRE = 1, PRO = 1; //PRE and PRO allow us to restrict the range somewhat

    for( uint z = 0; z < m_rows; ++z )
        m_yscale[z] = 1 - (log10( PRE+z ) / log10( PRE+m_rows+PRO ));

    m_yscale[m_rows] = 0;

    const double fallTime = 30 * m_rows;
    m_step = double(m_rows * 80) / fallTime;

    counter = 0;
    listeScope.clear();
}

void GlVizualizer::analyze( const QVector<float> &s )
{
    interpolate( s, m_scope );

     uint y;
     //qDebug() << QString("m_scope.size %1").arg(m_scope.size());
     bzero(blockValue, sizeof(blockValue));

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
       blockValue[x+1] = 16 - y;
    }
    uint tmpValue;
    tmpValue = (uint)((blockValue[1] + blockValue[2] + blockValue[3]) / 3);

    blockValue[2] = tmpValue;

    tmpValue = (uint)((blockValue[4] + blockValue[5] + blockValue[6]) / 3);
    blockValue[3] = tmpValue;

       tmpValue = (uint)((blockValue[7] + blockValue[8] + blockValue[9]) / 3);
       blockValue[4] = tmpValue;

       tmpValue = (uint)((blockValue[10] + blockValue[11] + blockValue[12]) / 3);
       blockValue[5] = tmpValue;

       tmpValue = (uint)((blockValue[13] + blockValue[14] + blockValue[15]) / 3);
       blockValue[6] = tmpValue;

       tmpValue = (uint)((blockValue[16] + blockValue[17] + blockValue[18]) / 3);
       blockValue[7] = tmpValue;

       tmpValue = (uint)((blockValue[19] + blockValue[20]) / 2);
       blockValue[8] = tmpValue;

       newChildToDraw(this);
       //qDebug() << QString("%1").arg((int)(blockValue[2]));
       //schreibeBlockValue();
   }

void GlVizualizer::clearList()
{
    listeScope.clear();
}

void GlVizualizer::doit()
{
    if(stopIt) return;

    if(listeScope.isEmpty())
    {
        //qDebug("liste leer");
        QTimer::singleShot(100, this, SLOT(doit()));
        return;
    }

    if(!this->getParent()->isVisible() || !this->isVisible())
    {
        QTimer::singleShot(200, this, SLOT(doit()));
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
       //qDebug() << QString("%1").arg(scope[x]);
    }

    transform(scope);
    analyze(scope);

    scope.resize( m_fht->size() );

    QTimer::singleShot(50, this, SLOT(doit()));
}

void GlVizualizer::draw(QPainter *p)
{
    p->fillRect(geometry(), Qt::black);
    QLinearGradient gradient( getWidth()/2, getY(),
                              getWidth()/2, getY() + getHeight());

    gradient.setColorAt(0, gradientColorAt0);
    gradient.setColorAt(1, gradientColorAt1);
    p->setBrush(QBrush(gradient));
    QPainterPath pa;
    QRect rect = geometry();
    pa.addRoundedRect(rect, borderRadius, borderRadius);
    pen.setWidth(border); //Strichbreite
    pen.setColor(borderColor); //Strichfarbe
    p->setPen(pen);
    p->drawPath(pa);

    for(int j = (int)(blockValue[8]); j > 0; j--)
        drawRect(p, 10, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[7]); j > 0; j--)
        drawRect(p, 70, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[6]); j > 0; j--)
        drawRect(p, 130, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[5]); j > 0; j--)
        drawRect(p, 190, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[4]); j > 0; j--)
        drawRect(p, 250, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[3]); j > 0; j--)
        drawRect(p, 310, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[2]); j > 0; j--)
        drawRect(p, 370, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[3]); j > 0; j--)
        drawRect(p, 430, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[4]); j > 0; j--)
        drawRect(p, 490, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[5]); j > 0; j--)
        drawRect(p, 550, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[6]); j > 0; j--)
        drawRect(p, 610, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[7]); j > 0; j--)
        drawRect(p, 670, getY() + getHeight() - (j*25));

    for(int j = (int)(blockValue[8]); j > 0; j--)
        drawRect(p, 730, getY() + getHeight() - (j*25));
}

void GlVizualizer::drawRect(QPainter *p, int posx, int posy)
{
    QPainterPath rectpath;
    QRect re = QRect(posx, posy, 40, 20);
    pen.setColor(QColor(Qt::white));
    pen.setWidth(3);
    p->setBrush(QBrush(QColor(Qt::blue)));
    rectpath.addRect(re);
    p->drawPath(rectpath);
}

void GlVizualizer::insertScope(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > &s)
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

void GlVizualizer::interpolate( const QVector<float> &inVec, QVector<float> &outVec )
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

void GlVizualizer::transform(QVector<float> &s )
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
