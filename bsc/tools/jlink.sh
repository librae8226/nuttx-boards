#!/bin/bash

if [ is$1 = 'isdfu' ]; then
	JLinkExe -CommanderScript configs/bsc/tools/jlink.dfu.cmd
else
	JLinkExe -CommanderScript configs/bsc/tools/jlink.cmd
fi
