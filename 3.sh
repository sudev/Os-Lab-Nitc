function add{
	
	echo $"(expr $1 + $2)" 
}

add $1 $2
exit 1

