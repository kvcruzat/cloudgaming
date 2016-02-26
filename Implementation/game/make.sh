#!/usr/bin/env bash

qmake -project QT+=opengl LIBS+=-lGLU
qmake
make
