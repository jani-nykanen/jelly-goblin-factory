#!/bin/sh
python3 makeme.py -bin -out:"out" -ldf:"-lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm" -ccf:"-Wall" src