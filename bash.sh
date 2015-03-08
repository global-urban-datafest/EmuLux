#!/bin/bash
A= grep 404 httpdata.txt   #  The "-q" option
                          #+ causes nothing to echo to stdout.

if [ $A -eq $SUCCESS ]
  then
    echo "ERROR"
else
echo "af"
fi
rm parsed.txt
grep { httpdata.txt >> parsed.txt
rm led.txt
awk -F"d" '{ print $2 }' parsed.txt >> led.txt
rm ledx.txt
awk -F"\"" '{ print $1 }' led.txt >> ledx.txt
rm tmp1.txt
awk -F":" '{ print $2 }' led.txt >> tmp1.txt
rm val1.txt
awk -F"\"" '{ print $2 }' tmp1.txt >> val1.txt
#rm ledx.txt
#awk -F"\"" '{ print $1 }' led.txt >> ledx.txt



var="$(cat ledx.txt)" 

aa="$(cat val1.txt)" 

rm led$var


echo $aa > led$var

exit