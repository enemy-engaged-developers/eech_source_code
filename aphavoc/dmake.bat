@echo off
REM SET EECH_ROOTDIR=c:\watcom\eech-new

echo ################### Make Timings ####################### >> maketime.txt
time < dmake.bat >> maketime.txt

wmake debug=1

time < dmake.bat >> maketime.txt
echo ######################################################## >> maketime.txt
   
type maketime.txt 

del maketime.txt

