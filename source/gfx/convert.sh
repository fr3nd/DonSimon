#!/bin/bash

rm -f *.c *.pcx
#./gfx2gba -align -fsrc -m -psimon1.pal -t8 simon1.bmp
./gfx2gba -align -fsrc -m -psimon3.pal -t8 simon3.bmp
convert +compress simon2_anim.gif "simon2_anim_%03d.pcx"
convert -crop 256x256+0+0 +compress simon_zoom.gif "simon_zoom_%03d.pcx"
./gfx2gba -align -fsrc -m -psimon_zoom.pal -t8 simon_zoom*.pcx
./gfx2gba -align -fsrc -m -psimon_2.pal -t8 simon2_anim_*.pcx


./gfx2gba -align -fsrc -m -psplash1.pal -t8 splash1.bmp
./gfx2gba -align -fsrc -m -psplash2.pal -t8 splash2.bmp

./gfx2gba -align -D -fsrc -pleds.pal -t8 leds.bmp

./gfx2gba -align -fsrc -m -pmenu.pal -t8 menu.bmp credits.bmp thanks.bmp help1.bmp help2.bmp scores1.bmp scores2.bmp newscore.bmp
./gfx2gba -align -D -fsrc -poptions.pal -T64 -t8 options.bmp

./gfx2gba -align -D -fsrc -ptextgran.pal -T64 -t8 textgran.bmp

# no se perque pero no converteix be de png a pcx directament
#convert text3.png text3.gif
#convert text3.gif text3.pcx
#rm text3.gif
#./gfx2gba -align -m -fsrc -ptext3.pal -t8 text3.pcx
#cat text3.raw.c |sed s/0x00/0xff/g > tmp
#mv tmp text3.raw.c
rm *.pcx
