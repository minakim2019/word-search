#!/bin/bash

#averagetime.sh
#Mina Kim, mk3bnb
#3/2/2020

echo "Enter name of dictionary file:"
read dict
echo "Enter name of grid file:"
read grid
make

time1=`./a.out $dict $grid | tail -1`
time2=`./a.out $dict $grid | tail -1`
time3=`./a.out $dict $grid | tail -1`
time4=`./a.out $dict $grid | tail -1`
time5=`./a.out $dict $grid | tail -1`

echo "Times in milliseconds:"
echo $time1
echo $time2
echo $time3
echo $time4
echo $time5

sum=$(bc <<< "$time1+$time2")
sum=$(bc <<< "$sum+$time3")
sum=$(bc <<< "$sum+$time4")
sum=$(bc <<< "$sum+$time5")

#cast sum to int
#sum=$(printf "%.0f" $sum)
#echo "Sum: "
#echo $sum

echo "Average time in milliseconds: "

num=5.0
average=$(bc <<< "$sum/$num")
echo $average
