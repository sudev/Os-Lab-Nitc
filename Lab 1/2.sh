#! /bin/bash
temp=`date +%k`
echo $temp."Hours now"
if [ $temp -gt 12 ]; then
	echo "Good Afternoon"
else
	echo "Good Morning"  
  exit 1
fi
#echo "temp=`date +%k`
#echo $temp."Hours now"
#if [ $temp -gt 12 ]; then
#	echo "Good Afternoon"
#else
	#echo "Good Morning"  
#  exit 1
#fi" >> .profile
#
