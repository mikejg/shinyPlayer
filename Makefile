#############################################################################
# Makefile for building: shinyPlayer
# Generated by qmake (2.01a) (Qt 4.6.3) on: Do. Aug 25 21:27:03 2011
# Project:  shinyPlayer.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile shinyPlayer.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_PHONON_LIB -DQT_SQL_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtSql -I/usr/include/phonon -I/usr/include/qt4 -I/usr/include/qt4/phonon_compat -I/usr/X11R6/include -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -L/usr/X11R6/lib -lphonon -lQtSql -lQtOpenGL -lQtGui -lQtCore -lGLU -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		dialogsetting.cpp \
		globject.cpp \
		glbutton.cpp \
		gllistwidget.cpp \
		glmainmenu.cpp \
		glmenuinterpret.cpp \
		glmenugenre.cpp moc_mainwindow.cpp \
		moc_dialogsetting.cpp \
		moc_globject.cpp \
		moc_glbutton.cpp \
		moc_gllistwidget.cpp \
		moc_glmainmenu.cpp \
		moc_glmenuinterpret.cpp \
		moc_glmenugenre.cpp \
		qrc_pixmaps.cpp
OBJECTS       = main.o \
		mainwindow.o \
		dialogsetting.o \
		globject.o \
		glbutton.o \
		gllistwidget.o \
		glmainmenu.o \
		glmenuinterpret.o \
		glmenugenre.o \
		moc_mainwindow.o \
		moc_dialogsetting.o \
		moc_globject.o \
		moc_glbutton.o \
		moc_gllistwidget.o \
		moc_glmainmenu.o \
		moc_glmenuinterpret.o \
		moc_glmenugenre.o \
		qrc_pixmaps.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		shinyPlayer.pro
QMAKE_TARGET  = shinyPlayer
DESTDIR       = 
TARGET        = shinyPlayer

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: shinyPlayer.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtSql.prl \
		/usr/lib/libQtOpenGL.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile shinyPlayer.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtSql.prl:
/usr/lib/libQtOpenGL.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile shinyPlayer.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/shinyPlayer1.0.0 || $(MKDIR) .tmp/shinyPlayer1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/shinyPlayer1.0.0/ && $(COPY_FILE) --parents mainwindow.h dialogsetting.h settings.h globject.h glbutton.h gllistwidget.h glmainmenu.h glmenuinterpret.h glmenugenre.h .tmp/shinyPlayer1.0.0/ && $(COPY_FILE) --parents pixmaps.qrc .tmp/shinyPlayer1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp dialogsetting.cpp globject.cpp glbutton.cpp gllistwidget.cpp glmainmenu.cpp glmenuinterpret.cpp glmenugenre.cpp .tmp/shinyPlayer1.0.0/ && $(COPY_FILE) --parents mainwindow.ui .tmp/shinyPlayer1.0.0/ && (cd `dirname .tmp/shinyPlayer1.0.0` && $(TAR) shinyPlayer1.0.0.tar shinyPlayer1.0.0 && $(COMPRESS) shinyPlayer1.0.0.tar) && $(MOVE) `dirname .tmp/shinyPlayer1.0.0`/shinyPlayer1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/shinyPlayer1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_dialogsetting.cpp moc_globject.cpp moc_glbutton.cpp moc_gllistwidget.cpp moc_glmainmenu.cpp moc_glmenuinterpret.cpp moc_glmenugenre.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_dialogsetting.cpp moc_globject.cpp moc_glbutton.cpp moc_gllistwidget.cpp moc_glmainmenu.cpp moc_glmenuinterpret.cpp moc_glmenugenre.cpp
moc_mainwindow.cpp: dialogsetting.h \
		settings.h \
		glmainmenu.h \
		globject.h \
		glbutton.h \
		glmenuinterpret.h \
		gllistwidget.h \
		glmenugenre.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_dialogsetting.cpp: settings.h \
		dialogsetting.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) dialogsetting.h -o moc_dialogsetting.cpp

moc_globject.cpp: globject.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) globject.h -o moc_globject.cpp

moc_glbutton.cpp: globject.h \
		glbutton.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) glbutton.h -o moc_glbutton.cpp

moc_gllistwidget.cpp: globject.h \
		glbutton.h \
		gllistwidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) gllistwidget.h -o moc_gllistwidget.cpp

moc_glmainmenu.cpp: globject.h \
		glbutton.h \
		glmainmenu.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) glmainmenu.h -o moc_glmainmenu.cpp

moc_glmenuinterpret.cpp: globject.h \
		gllistwidget.h \
		glbutton.h \
		glmenuinterpret.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) glmenuinterpret.h -o moc_glmenuinterpret.cpp

moc_glmenugenre.cpp: globject.h \
		gllistwidget.h \
		glbutton.h \
		glmenugenre.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) glmenugenre.h -o moc_glmenugenre.cpp

compiler_rcc_make_all: qrc_pixmaps.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_pixmaps.cpp
qrc_pixmaps.cpp: pixmaps.qrc \
		images/button400.png \
		images/main.png \
		images/button400_pressed.png \
		images/BackgroundBlack.png \
		images/button_pressed.png \
		images/button.png
	/usr/bin/rcc -name pixmaps pixmaps.qrc -o qrc_pixmaps.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		dialogsetting.h \
		settings.h \
		glmainmenu.h \
		globject.h \
		glbutton.h \
		glmenuinterpret.h \
		gllistwidget.h \
		glmenugenre.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		dialogsetting.h \
		settings.h \
		glmainmenu.h \
		globject.h \
		glbutton.h \
		glmenuinterpret.h \
		gllistwidget.h \
		glmenugenre.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

dialogsetting.o: dialogsetting.cpp dialogsetting.h \
		settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogsetting.o dialogsetting.cpp

globject.o: globject.cpp globject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o globject.o globject.cpp

glbutton.o: glbutton.cpp glbutton.h \
		globject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glbutton.o glbutton.cpp

gllistwidget.o: gllistwidget.cpp gllistwidget.h \
		globject.h \
		glbutton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gllistwidget.o gllistwidget.cpp

glmainmenu.o: glmainmenu.cpp glmainmenu.h \
		globject.h \
		glbutton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glmainmenu.o glmainmenu.cpp

glmenuinterpret.o: glmenuinterpret.cpp glmenuinterpret.h \
		globject.h \
		gllistwidget.h \
		glbutton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glmenuinterpret.o glmenuinterpret.cpp

glmenugenre.o: glmenugenre.cpp glmenugenre.h \
		globject.h \
		gllistwidget.h \
		glbutton.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glmenugenre.o glmenugenre.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_dialogsetting.o: moc_dialogsetting.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogsetting.o moc_dialogsetting.cpp

moc_globject.o: moc_globject.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_globject.o moc_globject.cpp

moc_glbutton.o: moc_glbutton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glbutton.o moc_glbutton.cpp

moc_gllistwidget.o: moc_gllistwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gllistwidget.o moc_gllistwidget.cpp

moc_glmainmenu.o: moc_glmainmenu.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glmainmenu.o moc_glmainmenu.cpp

moc_glmenuinterpret.o: moc_glmenuinterpret.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glmenuinterpret.o moc_glmenuinterpret.cpp

moc_glmenugenre.o: moc_glmenugenre.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glmenugenre.o moc_glmenugenre.cpp

qrc_pixmaps.o: qrc_pixmaps.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_pixmaps.o qrc_pixmaps.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

