#!/bin/bash

if [ $# -ne 0 ]; then
        if [ -d $1 ]; then
            find $1 -type f -name "*.debug" | xargs rm -rf
        else
            echo "Invalid path"
        fi
else
        echo "Invalid path"
fi
