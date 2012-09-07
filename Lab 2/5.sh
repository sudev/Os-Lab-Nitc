#to find all hidden files find /home/sudev/ -iname ".*" -maxdepth 1
#
if [ $# -ne 0 ]
	then
	echo "No argument  "
	exit 1
fi
touch listhid
echo "Path from which you wish to copy stuff"
read pathe
#check file exits 
find $pathe -iname ".*" -maxdepth 1 | cat >> listhid
echo "Name your folder"
read fold
#folder exits 
mkdir $fold
mv -R `cat < listhid ` $fold/ 
exit 1
#ahkjhakljl
