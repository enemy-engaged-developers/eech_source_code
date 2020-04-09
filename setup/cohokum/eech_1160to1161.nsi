;NSIS Modern User Interface
;EECH setup exe script, by gotcha jan 2005

SetCompressor /SOLID lzma

;--------------------------------
;Include Modern UI

	!include "MUI.nsh"

;--------------------------------
;General

	;define these variable
	!define VERSION "1.16.1RC1"

	;Name and file
	Name "EECH Dev release ${VERSION}"
	OutFile "eech-allmods-${VERSION}.exe"

	;Default installation folder
	InstallDir "C:\Program Files\Razorworks"

	;Get installation folder from registry if available
	InstallDirRegKey HKLM "Software\Razorworks\Comanche Hokum" "INSTALLATION PATH"

;--------------------------------
;Interface Settings

	!define MUI_ABORTWARNING

;--------------------------------
;Pages
	!define MUI_ICON eech.ico
	!define MUI_WELCOMEFINISHPAGE_BITMAP enemyengagedlogo.bmp
	!define MUI_WELCOMEFINISHPAGE_BITMAP_NOSTRETCH
	!define MUI_WELCOMEPAGE_TITLE_3LINES

		!define MUI_COMPONENTSPAGE_TEXT_TOP "You should have EECH 1.16.0 with all components installed (allmods, maps, terrain, smoke). Check/Uncheck what 1.16.1 components you want to install."
	!insertmacro MUI_PAGE_COMPONENTS
		!define MUI_DIRECTORYPAGE_TEXT_TOP "Please select the Razorworks root folder. This installer will place the files in the correct directories."
	!insertmacro MUI_PAGE_DIRECTORY
	!insertmacro MUI_PAGE_INSTFILES
		!define MUI_FINISHPAGE_NOAUTOCLOSE
	!insertmacro MUI_PAGE_FINISH

	ShowInstDetails show
;--------------------------------
;Languages

	!insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

	!define SRCDIR "\"
	!define EE_BASE_DIR "${SRCDIR}"



Section "Core files" SectionSystem

	SetOutPath "$INSTDIR\cohokum"

	Delete "$INSTDIR\cohokum\eech_keyguide_2.pdf"
	Delete "$INSTDIR\cohokum\eech_keyguide_190_2.9.pdf"
	Delete "$INSTDIR\keyguide.pdf"
	Delete "$INSTDIR\keyguide2.pdf"
	Delete "$INSTDIR\cohokum\COHOKUM1161.exe"
	Delete "$INSTDIR\cohokum\DEBUG1161.exe"

	SetOutPath "$INSTDIR"

	File /r "core\"

SectionEnd

Section "1.16.1 dynamics files" Section1161Dyn

	SetOutPath "$INSTDIR"

	File /r "DYN1161\"

SectionEnd

Section /o "1.16.0 dynamics files" Section1160Dyn

	SetOutPath "$INSTDIR"

	File /r "DYN1160\"

SectionEnd

Section /o "EECH/EEAH music" originalMusic

	SetOutPath "$INSTDIR"

	File /r "music eech eeah\"

SectionEnd

Section /o "Aero Elite music" aeroEliteMusic

	SetOutPath "$INSTDIR"

	File /r "music aero elite\"

SectionEnd

Section /o "Clear EECH.INI" SectionINI

	SetOutPath "$INSTDIR"
	Delete "$INSTDIR\cohokum\EECH.INI"

SectionEnd

Function .onSelChange
; This is not like radio buttons, both can be unselected:
${If} $0 = ${Section1161Dyn}
${AndIf} ${SectionIsSelected} ${Section1161Dyn}
    !insertmacro UnselectSection "${Section1161Dyn}"
${ElseIf} ${SectionIsSelected} ${Section1160Dyn}
    !insertmacro UnselectSection "${Section1161Dyn}"
${EndIf} 

${If} $0 = ${originalMusic}
${AndIf} ${SectionIsSelected} ${originalMusic}
    !insertmacro UnselectSection "${originalMusic}"
${ElseIf} ${SectionIsSelected} ${aeroEliteMusic}
    !insertmacro UnselectSection "${originalMusic}"
${EndIf} 
FunctionEnd

;--------------------------------
;Descriptions

	;Language strings
	LangString DESC_SectionSystem ${LANG_ENGLISH} "Install EECH ${VERSION} EXE, GWUT and core files"
	LangString DESC_Section1161Dyn ${LANG_ENGLISH} "Dynamics files by Javelin (flight model #2 only)"
	LangString DESC_Section1160Dyn ${LANG_ENGLISH} "Dynamics files from 1.16.0 (flight model #2 only)"
	LangString DESC_originalMusic ${LANG_ENGLISH} "Original music pack (cut and compressed)"
	LangString DESC_aeroEliteMusic ${LANG_ENGLISH} "Custom music pack from Aero Elite PS2 game"
	LangString DESC_SectionINI ${LANG_ENGLISH} "Necessary for first installation"

	;Assign language strings to sections
	!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${SectionSystem} $(DESC_SectionSystem)
	!insertmacro MUI_DESCRIPTION_TEXT ${Section1161Dyn} $(DESC_Section1161Dyn)
	!insertmacro MUI_DESCRIPTION_TEXT ${Section1160Dyn} $(DESC_Section1160Dyn)
	!insertmacro MUI_DESCRIPTION_TEXT ${originalMusic} $(DESC_originalMusic)
	!insertmacro MUI_DESCRIPTION_TEXT ${aeroEliteMusic} $(DESC_aeroEliteMusic)
	!insertmacro MUI_DESCRIPTION_TEXT ${SectionINI} $(DESC_SectionINI)
	!insertmacro MUI_FUNCTION_DESCRIPTION_END
;--------------------------------
