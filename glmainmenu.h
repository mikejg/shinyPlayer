/*GlMainMenu ist das Hauptmenü mit den Buttons
  Player, Interpret ... */

#ifndef GLMAINMENU_H
#define GLMAINMENU_H

#include "globject.h"
#include "glbutton.h"

class GlMainMenu : public GlObject
{
    Q_OBJECT
private:
    QPixmap balkenOben;
    QPixmap balkenUnten;
    int yBalkenOben;
    int yBalkenUnten;

public:
    GlButton* buttonPlayer;
    GlButton* buttonGenre;
    GlButton* buttonInterpret;
    GlButton* buttonPlaylist;
    GlButton* buttonSampler;
    GlButton* buttonRadio;
    GlButton* buttonQuick;
    GlButton* buttonSetting;

    GlMainMenu(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    GlButton* newButton(QString text, QRect rect);

    void rollIn(QPainter* p);
    void rollOut(QPainter *p);

    void setLarge();

signals:
    void buttonGenre_clicked();
    void buttonInterpret_clicked();
    void buttonPlayer_clicked();
    void buttonPlaylist_clicked();
    void buttonQuick_clicked();
    void buttonSampler_clicked();
    void buttonRadio_clicked();
};

#endif // GLMAINMENU_H
