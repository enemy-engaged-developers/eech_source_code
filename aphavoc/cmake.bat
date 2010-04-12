@echo off
SET EECH_ROOTDIR=c:\eech-dev
del project.exe

echo ################### Make Timings ####################### >> maketime.txt
echo. | time < dmake.bat >> maketime.txt

wmake optimise=1 commercial=1

echo. | time < dmake.bat >> maketime.txt
echo ######################################################## >> maketime.txt
   
type maketime.txt 

del maketime.txt
