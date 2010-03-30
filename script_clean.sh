#! /bin/bash

if test -z $1
then
   echo provea un archivo con la lista de instancias
fi

file_instances=$1

IFS='
'
for i in `grep -v '^NC' $file_instances` 
do
i=${i// C /}
echo ---- $i -----
if ./main < instances/$i > /dev/null
then
	echo Exitosa
else
	echo Fallo
	exit
fi
echo 
done
