#I've written script to display top two tweets when invoked . Checking if the file have modified is yet to be implemented.
#!/bin/bash
while true;
do

wget "http://athena.nitc.ac.in/~sudev_bcs10/tuxofwar" -b -O tweets > /dev/null
cat tweets | sed -e 's/[{}]/''/g' | awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | grep '"text"' > text
cat tweets | sed -e 's/[{}]/''/g' | awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]}' | grep '"from_user"' > user
user1=`cat user | head -n 1 | awk 'BEGIN{FS=":"}{print $2}'`
##echo $user1
user2=`cat user | head -n 2 | tail -n 1 | awk 'BEGIN{FS=":"}{print $2}'`
##echo $user2 
text1=`cat text | head -n 1 | awk 'BEGIN{FS="\":"}{print $2}'`
#echo $text1
text2=`cat text | head -n 2 | tail -n 1 | awk 'BEGIN{FS=":"}{print $2}'`
#echo $text2
echo "$user1 : $text1"
echo "$user2 : $text2"
sleep 15
done 
