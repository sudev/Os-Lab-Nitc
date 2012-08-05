#! /bin/bash

#this snipnet will check the numbher of parameter passed into the command by the user 

if [ $# -ne 3 ]
  then
    echo "Required no of arguments is three !"
fi
