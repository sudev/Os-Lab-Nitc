#! /bin/bash
temp=`date | cut -c12-13`
echo $temp."Hours now"
if [ $temp -gt 12 ]; then
	echo "Good Afternoon"
else
	echo "Good Morning"  
  exit 1
fi
