@echo off

	cd %EECH_ROOTDIR%\aphavoc

	del *.exe

	del *.lnk

	del *.pch

	cd %EECH_ROOTDIR%\aphavoc\source

	del /s *.obj

	cd %EECH_ROOTDIR%\modules

	del /s *.obj

	cd %EECH_ROOTDIR%\aphavoc
