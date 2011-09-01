/*GlButton ist ein Button ähnlich dem QButton mit einem
  Signal clicked() */

#ifndef GLBUTTON_H
#define GLBUTTON_H

#include "globject.h"
#include <QColor>
#include <QString>

class GlButton : public GlObject
{
    Q_OBJECT

private:
    int fontSize;
    bool isPressed;

    QColor fontColor;
    QString stringText;
    QPixmap backGroundPixmapPressed;

public:
    GlButton(GlObject* parent = 0);

    void draw(QPainter *p);
    void drawBackGroundPixmapPressed(QPainter* p);
    void drawText(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void setBackGroundPixmapPressed(QPixmap pix) { backGroundPixmapPressed = pix; }
    void setFontColor(QColor fc) { fontColor = fc; }
    void setFontSize(int fs) { fontSize = fs; }
    void setLarge();
    void setText(QString s) { stringText = s; }

signals:
    void clicked();

};

#endif // GLBUTTON_H
