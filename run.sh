#!/usr/bin/env bash

#set -o xtrace
set -o errexit -o nounset -o pipefail -o errtrace
IFS=$'\n\t'

disp_num=1
disp=:$disp_num
unset XDG_SEAT
Xephyr -screen 1024x768 $disp -ac -br -sw-cursor &
pid=$!

sleep 0.2

export DISPLAY=$disp
./dwm &

exit 0
