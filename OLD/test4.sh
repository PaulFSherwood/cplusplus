#!/bin/sh
mkdir `date +"%d%m%y_%H%M"` &&
ifconfig > `date +"%d%m%y_%H%M"`/ifconfig`date+"%d%m%y_%H%M"` &&
ps ux > `date +"%d%m%y_%H%M"`/ps_ux`date+"%d%m%y_%H%M"` &&\
netstat > `date +"%d%m%y_%H%M"`/netstat`date +"%d%m%y_%H%M"`
