@echo off
SET EECH_ROOTDIR=c:\eech-dev\

del project.exe

echo ################### Make Timings ####################### >> maketime.txt
echo. | time < dmake.bat >> maketime.txt

wmake debug=1

echo. | time < dmake.bat >> maketime.txt
echo ######################################################## >> maketime.txt
   
type maketime.txt 

del maketime.txt

xcopy /y project.* "C:\Program Files\Razorworks\cohokum"
