#!/bin/bash

echo "Tool URL: https://github.com/texane/stlink"

echo "flash:   " `st-info --flash`
echo "sram:    " `st-info --sram`
echo "descr:   " `st-info --descr`
echo "pagesize:" `st-info --pagesize`
echo "chipid:  " `st-info --chipid`

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
