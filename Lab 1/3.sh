if [ $# -ne 2 ]
  then
    echo "Required no of arguments is two Format : add <no1> <no2> !"
fi
function add
{
echo `expr $1 + $2`
}

add $1 $2
