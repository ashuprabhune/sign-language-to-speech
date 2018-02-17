#!/bin/sh
# A simple script with a function...

add_a_user()
{
	sum=0
	sum=`expr $1 + $2`
	echo $sum
}

###
# Main body of script starts here
###
echo "Start of script..."
$fnum=$1
$snum=$2
add_a_user $1 $2
echo "End of script..."