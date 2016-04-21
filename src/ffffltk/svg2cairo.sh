#!/bin/bash

##
##  This script is included because its so stinking useful for ffffltk
##  to really use it compile svg2cairo and copy this script into the folder
##  with the binaries. Put all your .svg drawings into a subdirectory called
##  svgfiles and this will generate a C header for each file.
##

export LD_LIBRARY_PATH=/usr/local/lib

if [[ -z $1 ]]
then

	cd svgfiles
	mkdir formats
	cp ../formats/* formats/
	for file in *.svg;
	do
	 echo "converting $file"
	 ./../svg2cairoxml $file ${file}.xml
	 lua ../cairoxml2cairo.lua -f c ${file}.xml draw_${file/.svg/}.h
	 file=draw_${file/.svg/}.h
	 size=$(file $file | grep "empty")
	 if [[ -z "$size" ]];
	 then
	  echo success
	  sed -i s/CAIRO_DEFAULT/CAIRO_ANTIALIAS_DEFAULT/ $file
	  sed -i "1s,^,inline ," $file
	  sed -i "2s,^,inline ," $file
	  sed -i "3s,^,inline ," $file
	  caps=`echo ${file^^}`
	  caps=`echo $caps | sed s/[.]/_/`
	  sed -i "1s,^,#ifndef $caps\n#define $caps\n," $file
	  sed -i -e "\$a#endif" $file
	 else
	  rm draw_${file/.svg/}.c
	fi
	done

	rm -rf formats/
	rm *.xml
	cd ..

else

	echo "converting $file"
	./svg2cairoxml $1 ${1}.xml
	lua cairoxml2cairo.lua -f c ${1}.xml draw.c
	sed -i s/CAIRO_DEFAULT/CAIRO_ANTIALIAS_DEFAULT/ draw.c
fi

export LD_LIBRARY_PATH=/usr/lib
