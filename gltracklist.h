#ifndef GLTRACKLIST_H
#define GLTRACKLIST_H

#include "globject.h"
#include "metapaket.h"
#include <QList>

class GlTrackListItem : public GlObject
{
    Q_OBJECT
private:
    MetaPaket metapaket;

public:
    GlTrackListItem(GlObject* parent = 0);
    MetaPaket getMetaPaket() { return metapaket; }
    void setMetaPaket(MetaPaket mp) { metapaket = mp; }
    QString title() { return metapaket.title; }
    QString interpret() { return metapaket.interpret; }
};

class GlTrackList : public GlObject
{
    Q_OBJECT

private:
    QList<GlTrackListItem*> listItem;
    QColor borderColor;
    QColor gradientColorAt0;
    QColor gradientColorAt1;
    QColor fontColor;
    QPen pen;

    int border;
    int borderRadius;
    int fontSize;
    int startPos;
    int itemHeight;
    int currentItem;

public:
    GlTrackList(GlObject* parent = 0);

    void draw(QPainter *p);
    void drawTextLeft(QPainter *p, QRect rect, QString text);
    void drawTextRight(QPainter *p, QRect rect, QString text);

    int getListSize() { return listItem.size(); }
    int getStartPos() { return startPos; }

    int indexOf(MetaPaket mp);
    void mouseReleaseEvent(QMouseEvent *event);

    MetaPaket nextItem();
    void newTracks(QList<MetaPaket> list);
    void newTrack(MetaPaket mp);

    MetaPaket prevItem();

    void setCurrentItem(int ci) { currentItem = ci; }
    void setStartPos(int p) { startPos = p; }

public slots:
    void clear();

signals:
    void itemClicked(MetaPaket);
};

#endif // GLTRACKLIST_H
