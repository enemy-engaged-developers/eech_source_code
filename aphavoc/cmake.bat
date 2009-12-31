@echo off
SET EECH_ROOTDIR=c:\eech-dev
del project.exe
wmake optimise=1 commercial=1
