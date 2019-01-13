#!/bin/sh
make clean # We don't want to add .o files to git repo
git add git.sh
git add src
git add README.md
git add makemake.sh
git add makeme.py
git add app.cfg
git add dev
git add Assets
git add controls.cfg
git add buildwin32.txt
