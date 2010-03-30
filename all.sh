#! /bin/bash

IFS='
'
for i in `ls -1 instances/myciel*;ls -1 instances/queen*;ls -1 instances/school*;ls -1 zeroin*`
do
echo ---- $i -----
if ./main < $i
then
	echo --------- Exitosa ---------
else
	echo --------- Fallo ---------
	exit
fi
echo 
done
