#ifndef GLTRACKLISTWIDGET_H
#define GLTRACKLISTWIDGET_H

#include "globject.h"
#include "glanimation.h"
#include "metapaket.h"

class GlTrackListWidgetItem : public GlObject
{
    Q_OBJECT

private:
    QString text;
    MetaPaket mp;

public:
    GlTrackListWidgetItem(GlObject* parent = 0);

    MetaPaket getMetaPaket() { return mp; }
    QString getText() { return mp.title; }

    void setMetaPaket(MetaPaket m) { mp = m; }
};

class GlTrackListWidget : public GlObject
{
    Q_OBJECT

private:
    QColor borderColor;
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QColor fontColor;
    QPen pen;

    int border;
    int borderRadius;
    int fontSize;
    int itemHeight;

    QList<GlTrackListWidgetItem* > itemList;
    GlAnimation* animation;

public:
    GlTrackListWidget(GlObject* parent = 0);

    void draw(QPainter *p);

    void mouseReleaseEvent ( QMouseEvent * event );

    void startZoomIn();
    void startZoomOut();
    void setLarge();
    void setTracks(QList<MetaPaket>);

signals:
    void newTitleSelected(MetaPaket);
    void animationDone();
};

#endif // GLTRACKLISTWIDGET_H
