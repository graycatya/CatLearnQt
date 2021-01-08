#!/bin/bash
a=`uname  -a`

b="Darwin"
c="centos"
d="ubuntu"

if [[ $a =~ $b ]];then
    echo "mac"
elif [[ $a =~ $d ]];then
    echo "ubuntu"
else
    echo $a
    sudo mkdir /usr/share/fonts/ubuntu
    sudo cp *.ttf /usr/share/fonts
    sudo mkfontscale
    sudo mkfontdir
    sudo fc-cache -fv
fi

