@ECHO OFF

IF NOT DEFINED OGRE_SDK (
	ECHO OGRE_SDK is not defined
	pause
	exit
)

set r=%OGRE_SDK%\bin\Release
set d=%OGRE_SDK%\bin\Debug
set t=%OGRE_SDK%\bin\ogreee
IF NOT EXIST %t% (
	mkdir %t%
	copy %OGRE_SDK%\bin\Release\cg.dll %t%
	FOR %%f IN (OgreMain,OgreOverlay,OIS,Plugin_BSPSceneManager,Plugin_CgProgramManager,Plugin_OctreeSceneManager,Plugin_OctreeZone,Plugin_ParticleFX,Plugin_PCZSceneManager,RenderSystem_Direct3D9,RenderSystem_Direct3D11,RenderSystem_GL) DO for %%g IN ("%r%\%%f.dll" "%d%\%%f_d.dll") DO copy %%g %t% >nul
)

FOR %%f IN (lib\Release\ogreee.dll lib\Release\ogreee.pdb lib\Debug\ogreee_d.dll lib\Debug\ogreee_d.pdb) DO copy /y %%f %t% >nul
FOR %%f IN (..\aphavoc\project.exe ..\aphavoc\project.sym) DO copy %%f %t% >nul

cscript replace.vbs %r% plugins.cfg . %t% >nul
cscript replace.vbs %r% resources.cfg ../.. %OGRE_SDK% >nul
cscript replace.vbs %d% plugins_d.cfg . %t% >nul
cscript replace.vbs %d% resources_d.cfg ../.. %OGRE_SDK% >nul

cd %t%
%1 project.exe
