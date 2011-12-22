#ifndef GLINFOVIEW_H
#define GLINFOVIEW_H

#include "globject.h"
#include "glcombobox.h"
#include "metapaket.h"

class GlInfoView : public GlObject
{
    Q_OBJECT
private:
private:
    QColor borderColor;
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QPen pen;

    int border;
    int borderRadius;
    MetaPaket mp;
    QImage coverImg;
    QColor fontColor;
    int fontSize;

    GlComboBox* cbPoints;

public:
    GlInfoView(GlObject *parent = 0);
    void setMetaPaket(MetaPaket m) { mp = m; cbPoints->setFirstText(QString("%1 Points").arg(m.points)); }

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );
signals:
    void setNewPoints(MetaPaket);

public slots:
    void comboBoxOpen(GlComboBox* cb);
    void comboBoxClosed(GlComboBox* cb);
};

#endif // GLINFOVIEW_H
