#! /bin/bash

#the format used here is <script-name> <text> <replace-text> <filename>
#parameter 1 is old text , $2 is new replacement, and $3 inputs the filename 
#3checking for three parameters 
if [ $# -ne 3 ]
  then
    echo "Required no of arguments is three !"
fi
#replacement using sed 
sed -i "s/$1/$2/g" "$3"

