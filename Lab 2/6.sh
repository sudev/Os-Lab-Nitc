
echo "give me a path( parent of the directory)"
read $pat
cd $pat
echo "name of the directory"
read fil
if [ -d "$fil" ]
then
	echo "$fil found"
	
else
	if [ -f "$fil" ]	
	then 
	rm $fil
	mkdir $fil 	
	else
	mkdir $fil
	fi
fi
