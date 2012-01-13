#ifndef GLMENUPLAYER_H
#define GLMENUPLAYER_H

#include "globject.h"
#include "gltracklist.h"
#include "glcoverview.h"
#include "glinfoview.h"
#include "glbutton.h"
#include "glanimation.h"
#include "glcombobox.h"
#include "glvizualizer.h"
#include "settings.h"
#include "metapaket.h"
#include "play_engine.h"
#include "usbconfig.h"
#include "ledboom.h"
#include <QTimer>

extern "C"
{
#include "hiddata.h"
}

class GlMenuPlayer : public GlObject
{
    Q_OBJECT
private:
    GlAnimation* animation;
    GlTrackList* trackList;
    GlCoverView* coverView;
    GlInfoView* infoView;
    GlVizualizer* vizualizer;
    GlButton* buttonMain;
    GlButton* buttonDown;
    GlButton* buttonUp;
    GlButton* buttonFor;
    GlButton* buttonBack;
    GlButton* buttonPause;
    GlButton* buttonClear;
    GlComboBox* comboBoxView;
    GlComboBox* comboBoxLed;
    QString cbViewString;
    GlObject* viewObject;
    Database* db;
    Play_Engine* playEngine;
    LedBoom* ledBoom;
    QString infoString;
    QTimer* timer_ledAnimation;
    //QTimer* timer_ledTime;

    QColor fontColor;
    int fontSize;

    usbDevice_t *dev;
    char        buffer[65];    /* room for dummy report ID */
    int         err;
    int         fehler;
    QString     fehlerString;

    bool ledArtist;
    bool ledAnimation;
    bool ledTime;
    bool ledAnalyzer;

public:
    GlMenuPlayer(GlObject* parent = 0);

    char convertASCII_to_FlashTable(char c);

    void draw(QPainter *p);

    void insertNewAlbum(QString interpret, QString album);
    void insertNewPlaylist(QString pl);
    void insertNewQuick(int y1, int y2, uint pastTime, int point, bool boolRandom);
    void insertNewSampler(QString sampler);
    void insertNewTitle(MetaPaket mp);

    void ledLaufschrift(QString lt);
    void ledStartTime();
    void ledPlayAnimation();

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    usbDevice_t* openDevice(void);

    void setPlayEngine(Play_Engine* pe);

    void rollIn(QPainter* p);
    void rollOut(QPainter* p);

    void setDatabase(Database* d) { db = d; }
    void setUsbDevice(usbDevice_t* d);

public slots:
    void buttonDown_clicked();
    void buttonUp_clicked();
    void comboBoxOpen(GlComboBox* cb);
    void comboBoxClosed(GlComboBox* cb);
    void comboBoxLedOpen(GlComboBox* cb);
    void comboBoxLedClosed(GlComboBox* cb);
    //void ledTimer_Time_timeout();
    void ledTimer_Animation_timeout();
    void nextSong();
    void playTrackListItem(MetaPaket);
    void prevSong();
    void setNewPoints(MetaPaket);
    void newUsbDevice();
    void openUsbDevice();
signals:
    void buttonMain_clicked();
};

#endif // GLMENUPLAYER_H
