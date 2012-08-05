#! /bin/bash

#the format used here is <script-name> <text> <replace-text> <filename>
#parameter 1 is old text , $2 is new replacement, and $3 inputs the filename 

sed -i "s/$1/$2/g" "$3"

