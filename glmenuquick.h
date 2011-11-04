#ifndef GLMENUQUICK_H
#define GLMENUQUICK_H

#include "globject.h"
#include "glcombobox.h"
#include "gltextlabel.h"
#include "glbutton.h"
#include "settings.h"

class GlMenuQuick : public GlObject
{
    Q_OBJECT

private:
     GlTextLabel* labelYear;
     GlComboBox* comboBoxYear;

     GlTextLabel* labelRandom;
     GlComboBox* comboBoxRandom;

     GlTextLabel* labelPoints;
     GlComboBox* comboBoxPoints;

     GlTextLabel* labelAdded;
     GlComboBox* comboBoxAdded;

     GlButton* buttonMain;
     GlButton* buttonClear;
     GlButton* buttonOK;

     Database* db;

     QPixmap balkenOben;
     QPixmap balkenUnten;
     int yBalkenOben;
     int yBalkenUnten;
public:
    GlMenuQuick(GlObject* parent = 0);

    void draw(QPainter *p);

    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent ( QMouseEvent * event );

    void rollIn(QPainter* p);
    void rollOut(QPainter* p);

    void setDatabase(Database* d) { db = d; }

signals:
    void buttonMain_clicked();

public slots:
    void comboBoxOpen(GlComboBox*);
    void comboBoxClosed(GlComboBox*);
    void buttonClear_clicked();
    void buttonOK_clicked();
};

#endif // GLMENUQUICK_H
