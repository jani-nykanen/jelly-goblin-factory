#!/bin/sh
python3 makeme.py -bin -out:"out" -ldf:"-lSDL2 -lSDL2_mixer -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm" -ccf:"-Wall" src