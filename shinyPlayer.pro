# -------------------------------------------------
# Project created by QtCreator 2011-08-21T11:47:45
# -------------------------------------------------
QT += opengl \
    sql \
    phonon
TARGET = shinyPlayer
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    dialogsetting.cpp \
    globject.cpp \
    glbutton.cpp \
    gllistwidget.cpp \
    glmainmenu.cpp \
    glmenuinterpret.cpp \
    glmenugenre.cpp \
    glanimation.cpp \
    glbuttonlist.cpp \
    database.cpp \
    db_amarok_embedded.cpp \
    glmenualben.cpp \
    glpictureflow.cpp \
    glmenuplayer.cpp \
    gltracklist.cpp \
    play_engine.cpp \
    gltracklistwidget.cpp \
    glmenuplaylist.cpp \
    glmenusampler.cpp \
    glmenuradio.cpp \
    glradiolist.cpp \
    glcombobox.cpp \
    glmenuquick.cpp \
    glrulewidget.cpp \
    gltextlabel.cpp \
    glcoverview.cpp \
    glinfoview.cpp \
    fht.cpp \
    glvizualizer.cpp
HEADERS += mainwindow.h \
    dialogsetting.h \
    settings.h \
    globject.h \
    glbutton.h \
    gllistwidget.h \
    glmainmenu.h \
    glmenuinterpret.h \
    glmenugenre.h \
    glanimation.h \
    glbuttonlist.h \
    database.h \
    db_amarok_embedded.h \
    glmenualben.h \
    glpictureflow.h \
    glmenuplayer.h \
    gltracklist.h \
    metapaket.h \
    play_engine.h \
    gltracklistwidget.h \
    glmenuplaylist.h \
    glmenusampler.h \
    glmenuradio.h \
    glradiolist.h \
    glcombobox.h \
    glmenuquick.h \
    glrulewidget.h \
    gltextlabel.h \
    glcoverview.h \
    glinfoview.h \
    fht.h \
    glvizualizer.h
FORMS += mainwindow.ui
RESOURCES += pixmaps.qrc
INCLUDEPATH += /usr/include/mysql
LIBS += -L/usr/lib/mysql \
    -lmysqld \
    -lcrypt

INCLUDEPATH += /usr/include/taglib

LIBS += -L/usr/lib \
    -ltag

LIBS += -L/usr/lib \
    -lz
