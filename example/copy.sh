 echo 'Command copies A at cade machine to B locally'
 echo -n ' 
Making a copy of '
echo -n ${1}
echo -n ' in '
echo -n ${2}
echo

scp u1318856@lab1-13.eng.utah.edu:${1} ${2}

echo "Complete"
