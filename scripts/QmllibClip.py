#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import platform
import os
import glob

print(platform.system())

def clipqmllib(path, types):
    for root,dirs,files in os.walk(path):
        #print(root)
        for type in types:
            for infile in glob.glob( os.path.join(root, type) ):
                print("remove: " + infile)
                os.remove(infile)


def WindowsClipQmlLib(path):
    print(path)
    if os.path.exists(path):
        clipqmllib(path, ['*d.dll', '*.pdb']);
    else:
        print("The directory is invalid")

    return;

def LinuxClipQmlLib(path):
    print(path)
    if os.path.exists(path):
        clipqmllib(path, ['*.debug']);
    else:
        print("The directory is invalid")
    return;


if __name__ == "__main__":

    if len(sys.argv) > 1:
        if(platform.system()=='Windows'):
            WindowsClipQmlLib(sys.argv[1])
        elif(platform.system()=='Linux'):
            LinuxClipQmlLib(sys.argv[1])
        else:
            print("The system is not supported")
