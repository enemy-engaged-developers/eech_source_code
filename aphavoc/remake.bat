@echo off

	cd \aphavoc

	del *.exe

	del *.lnk

	del *.pch

	cd \aphavoc\source

	rec del *.obj

	cd \modules

	rec del *.obj

	cd \aphavoc
