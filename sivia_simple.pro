#-------------------------------------------------
#
# Project created by QtCreator 2011-07-01T09:24:59
#
#-------------------------------------------------

QT       += core gui script

TARGET = sivia_simple
TEMPLATE = app

SOURCES += main.cpp\
 mainwindow.cpp \
 sivia.cpp \
 repere.cpp \
    simulation.cpp \
    scenar.cpp \
    drawPaving.cpp \
    drawf.cpp

HEADERS += mainwindow.h \
 sivia.h \
 repere.h \
 simulation.h \
    scenar.h \
    drawPaving.h \
    drawf.h

FORMS += mainwindow.ui

IBEXHOME = /home21/benefije/Documents/57_ROMO/IBEX/IBEX_INSTALL/INSTALL
#IBEXHOME = /home/biop/programmation/5.6_interval/TD_Ibex
INCLUDEPATH += $$IBEXHOME/IBEX/include/ibex $$IBEXHOME/IBEX/include $$IBEXHOME/soplex-1.7.2/src -frounding-math -msse2 -mfpmath=sse

LIBS += -L$$IBEXHOME/IBEX/lib -L$$IBEXHOME/soplex-1.7.2/lib -libex -lsoplex -lprim

OTHER_FILES += \
    g.txt \
    f.txt

