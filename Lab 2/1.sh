#to find a no is even or odd 
if [ $# -ne 1 ]
	then
	echo "pass one argument  "
	exit 1
fi
#remember to use two square brackets ow this wont work 
if [[ `expr $1 % 2` -ne 0 ]]
	then 
	echo "The given number is odd"
	else
	echo "The given number is even"
fi
	
