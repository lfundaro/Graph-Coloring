#! /bin/bash
#! /bin/bash

IFS='
'
for i in `ls -1 instances`
do
echo ---- $i -----
if ./main < instances/$i
then
	echo --------- Exitosa ---------
else
	echo --------- Fallo ---------
	exit
fi
echo 
done
