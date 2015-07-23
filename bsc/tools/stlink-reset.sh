#!/bin/bash

echo "Tool URL: https://github.com/texane/stlink"

echo "flash:   " `st-info --flash`
echo "sram:    " `st-info --sram`
echo "descr:   " `st-info --descr`
echo "pagesize:" `st-info --pagesize`
echo "chipid:  " `st-info --chipid`
st-flash --reset read /dev/null 0x08000000 32
