;NSIS Modern User Interface
;EECH setup exe script, by gotcha jan 2005

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;General
  
  ;define these variable 
  !define VERSION "162W2"
  
  ;Name and file
  Name "EECH Dev release ${VERSION}"
  OutFile "eechsetup${VERSION}.exe"

  ;Default installation folder
  InstallDir "c:\razorworks\"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKLM "Software\Razorworks\Comanche Hokum\" "INSTALLATION PATH"

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages
		!define MUI_ICON eech.ico
  		!define MUI_WELCOMEFINISHPAGE_BITMAP enemyengagedlogo.bmp
  		!define MUI_WELCOMEFINISHPAGE_BITMAP_NOSTRETCH
		!define MUI_WELCOMEPAGE_TITLE_3LINES
		
  !insertmacro MUI_PAGE_LICENSE licenceeech.txt
		!define MUI_COMPONENTSPAGE_TEXT_TOP "Check/Uncheck the components you want to install. CAREFUL: files will be overwritten!"
  !insertmacro MUI_PAGE_COMPONENTS  	
  		!define MUI_DIRECTORYPAGE_TEXT_TOP "Please select the Razorworks root folder. This installer will place the files in the correct directories."
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
	   !define MUI_FINISHPAGE_NOAUTOCLOSE
  		!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\cohokum\${VERSION}readme.html"
  !insertmacro MUI_PAGE_FINISH
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Create a backup?" SecBackup
	!define TBACKUP1 $INSTDIR\cohokum                                                       
	CreateDirectory "$INSTDIR\cohokum\backup"
	
CopyFiles /FILESONLY ${TBACKUP1}\cohokum.exe           ${TBACKUP1}\backup
CopyFiles /FILESONLY ${TBACKUP1}\GWUT146X.csv          ${TBACKUP1}\backup
CopyFiles /FILESONLY ${TBACKUP1}\GWUT151D.csv          ${TBACKUP1}\backup
CopyFiles /FILESONLY ${TBACKUP1}\GWUT1613H.csv         ${TBACKUP1}\backup
	
SectionEnd

Section "cohokum.exe" SectionExe

  SetOutPath "$INSTDIR\cohokum"
  
  File "..\..\aphavoc\cohokum.exe"
  File ${VERSION}readme.html
  File motd.txt
  File TrackIR.dll	
  File GWUT146X.csv
  File GWUT151D.csv
  File GWUT1613H.csv  

  SetOutPath "$INSTDIR\common\data\language\"
  File ..\common\data\language\tlate6.dat

  SetOutPath "$INSTDIR\cohokum\graphics\ui\cohokum\Map"
  File graphics\ui\cohokum\Map\PayAh6.psd
  File graphics\ui\cohokum\Map\PayBla.psd
  File graphics\ui\cohokum\Map\PayHin.psd
  File graphics\ui\cohokum\Map\PayKa5.psd
 
SectionEnd


;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SectionExe ${LANG_ENGLISH} "Install cohokum.exe, readme.html, additional payload screens, motd.txt and tlate6.dat language file"
;  LangString DESC_SecGWUT ${LANG_ENGLISH} "Weapons and Units Tweaker files"
  LangString DESC_SecBackup ${LANG_ENGLISH} "Backup exe and wut files in a subdirectory 'backup' "

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	 !insertmacro MUI_DESCRIPTION_TEXT ${SecBackup} $(DESC_SecBackup)
    !insertmacro MUI_DESCRIPTION_TEXT ${SectionExe} $(DESC_SectionExe)
 ;   !insertmacro MUI_DESCRIPTION_TEXT ${SecGWUT} $(DESC_SecGWUT)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
;--------------------------------
