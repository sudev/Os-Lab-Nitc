if [$# -ne 1]
then 
echo "<Command> <path>"
exit 1
fi

find $1/* -empty -delete
