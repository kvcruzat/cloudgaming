######################################################################
# Automatically generated by qmake (3.0) Wed Mar 2 12:45:31 2016
######################################################################

QT+=opengl
LIBS+=-lGLU -lglut
TEMPLATE = app
TARGET = game
INCLUDEPATH += . lib

# Input
HEADERS += GLPolygonWidget.h GLWindow.h lib/Matrix.h lib/Point.h lib/Vector.h
SOURCES += GLPolygonMain.cpp \
           GLPolygonWidget.cpp \
           GLWindow.cpp \
           lib/Matrix.cpp \
           lib/Point.cpp \
           lib/Vector.cpp
