#!/bin/sh
cd "$(dirname "$0")"

# Convert bitmaps
../tools/png2bin bitmaps/parrot.png ../parrot.bin -dither
../tools/png2bin bitmaps/font.png ../font.bin
