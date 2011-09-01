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
    db_amarok_embedded.cpp
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
    db_amarok_embedded.h
FORMS += mainwindow.ui
RESOURCES += pixmaps.qrc
INCLUDEPATH += /usr/include/mysql
LIBS += -L/usr/lib/mysql \
    -lmysqld \
    -lcrypt
