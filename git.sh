#!/bin/sh
make clean # We don't want to add .o files to git repo
git add git.sh
git add src
git add README.md
git add makemake.sh
git add makeme.py
git add app.cfg
