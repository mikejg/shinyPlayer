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
    QImage img_btn_Player;
    QImage img_btn_Genre;

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

    void rollOut(QPainter *p);

    void setLarge();

signals:
    void buttonGenre_clicked();
    void buttonInterpret_clicked();
};

#endif // GLMAINMENU_H
