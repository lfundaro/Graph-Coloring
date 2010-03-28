#! /bin/bash

IFS='
'
for i in `grep -v '^NC' checklist` 
do
i=${i// C /}
echo ---- $i -----
./main < instances/$i
echo 
done
