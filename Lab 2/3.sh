
if [ $# -ne 3 ]
	then 
	echo " format <command> <strt-line> <end-line> <file-name>"
	exit 1
fi
head -n $2 < $3 | tail -n +$1 
 
# sed can also be used to attain the same

