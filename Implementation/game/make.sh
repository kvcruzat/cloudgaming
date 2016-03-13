#!/usr/bin/env bash

qmake -project QT+=opengl QT+=network LIBS+=-lGLU\ -lglut
qmake
make
