#!/bin/bash
#Outputs if word is found in dictionary. Spell check to be implemented
echo "Input : $1"
grep "^$1$" /usr/share/dict/words > /dev/null
if [ $? == 0 ]; then
echo "Output: It is a dictionary word"
fi

