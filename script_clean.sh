#! /bin/bash

IFS='
'
for i in `grep -v '^NC' checklist` 
do
i=${i// C /}
echo ---- $i -----
if ./main < instances/$i > /dev/null
then
	echo Exitosa
else
	echo Fallo
fi
echo 
done
