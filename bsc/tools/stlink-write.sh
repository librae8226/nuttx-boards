#!/bin/bash

echo "Tool URL: https://github.com/texane/stlink"

if [ $1null = 'null' ]; then
	file=nuttx.bin
else
	file=$1
fi

if [ ! -f "$file" ]; then
	echo $file "doesn't exist, exit."
	exit -1
fi

st-flash write $file 0x08000000
