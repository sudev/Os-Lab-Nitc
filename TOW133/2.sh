#!/bin/bash
wget  -O $1 "https://graph.facebook.com/$1"
line=`cat $1 | tr ':' '\n' | grep -n 'likes'`
#echo $line
l=`echo $line | cut -f 1 -d ':'`
#echo $l
let l++
#echo $l
l2=`cat $1 | tr ':' '\n' | head -n $l | tail -n 1`

#echo $l2
echo -n "Likes:"
echo $l2 | cut -f 1 -d ','
