#to check if given two files are different 
if [ $# -ne 2 ]
	then
	echo "<cmd> file1 file2 "
	exit 1
fi
cmp $1 $2 > /dev/null
#  wi th operator > /dev/nul is to redirect the output to null area which helps in not displaying the error mesage

if [[ $? -ne 0 ]]
	then 
	echo "The given files are different"
	else
	echo "The given files are same"
fi
