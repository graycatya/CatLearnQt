#!/bin/bash

sudo cp *.ttf /usr/share/fonts
sudo mkfontscale
sudo mkfontdir
sudo fc-cache -fv