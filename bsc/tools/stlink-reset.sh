#!/bin/bash

echo "Tool URL: https://github.com/texane/stlink"
st-flash --reset read /dev/null 0x08000000 32
