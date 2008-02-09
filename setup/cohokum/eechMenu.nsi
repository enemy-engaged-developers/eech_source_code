;NSIS Modern User Interface
;EECH setup exe script, by gotcha jan 2005

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;General
  
  ;define these variable 
  !define VERSION "1.10.1"
  
  ;Name and file
  Name "EECH Dev release ${VERSION}"
  OutFile "eechsetup${VERSION}.exe"

  ;Default installation folder
  InstallDir "C:\Program Files\Razorworks\"
  
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

	ShowInstDetails show  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Create a backup?" SecBackup
	!define TBACKUP1 $INSTDIR\cohokum
	!define DATADIR  $INSTDIR\common\data
                                                       
	CreateDirectory "$INSTDIR\cohokum\backup"
	
CopyFiles /FILESONLY ${TBACKUP1}\cohokum.exe           ${TBACKUP1}\backup

CopyFiles /FILESONLY ${DATADIR}\ah64a.dyn         ${TBACKUP1}\backup
CopyFiles /FILESONLY ${DATADIR}\apache.dyn        ${TBACKUP1}\backup
CopyFiles /FILESONLY ${DATADIR}\blckhwk.dyn       ${TBACKUP1}\backup
CopyFiles /FILESONLY ${DATADIR}\comanche.dyn      ${TBACKUP1}\backup
CopyFiles /FILESONLY ${DATADIR}\havoc.dyn         ${TBACKUP1}\backup
CopyFiles /FILESONLY ${DATADIR}\hind.dyn          ${TBACKUP1}\backup
CopyFiles /FILESONLY ${DATADIR}\hokum.dyn         ${TBACKUP1}\backup
CopyFiles /FILESONLY ${DATADIR}\ka50.dyn          ${TBACKUP1}\backup
	
SectionEnd

Section "UI screens" SectionUIScreens

  SetOutPath "$INSTDIR\cohokum\graphics\ui\cohokum"

  File graphics\ui\cohokum\Combat.psd
  File graphics\ui\cohokum\Exit.psd
  File graphics\ui\cohokum\Gunship.psd
  File graphics\ui\cohokum\Main.psd
  File graphics\ui\cohokum\Pilots.psd
  File graphics\ui\cohokum\Setup.psd

SectionEnd

Section "cohokum.exe" SectionExe

  SetOutPath "$INSTDIR\cohokum"
  
  File "..\..\aphavoc\cohokum.exe"
  File ${VERSION}-readme.html
  File motd.txt
  File TrackIR.dll	
  File gwut190.csv
  File eech_keyguide_2.pdf

  SetOutPath "$INSTDIR\common\data\"
  File ..\common\data\FORMS.DAT
  File ..\common\data\ah64a.dyn
  File ..\common\data\apache.dyn
  File ..\common\data\blckhwk.dyn
  File ..\common\data\comanche.dyn
  File ..\common\data\havoc.dyn
  File ..\common\data\hind.dyn
  File ..\common\data\hokum.dyn
  File ..\common\data\ka50.dyn
  
  SetOutPath "$INSTDIR\common\data\language"
  File ..\common\data\language\tlate6.dat

  SetOutPath "$INSTDIR\cohokum\graphics\ui\cohokum\Map"
  File graphics\ui\cohokum\Map\PayAh6.psd
  File graphics\ui\cohokum\Map\PayBla.psd
  File graphics\ui\cohokum\Map\PayHin.psd
  File graphics\ui\cohokum\Map\PayKa5.psd

  SetOutPath "$INSTDIR\cohokum\audio"

  File audio\a10.pcm
  File audio\ac_crash.pcm
  File audio\ac_shotd.pcm
  File audio\ah1.pcm
  File audio\ah1t_seacobra_a2a.pcm
  File audio\ah1t_seacobra_mca.pcm
  File audio\ah1t_seacobra_rotor_ext.pcm
  File audio\ah1t_seacobra_rotor_int.pcm
  File audio\ah1t_seacobra_slap_ext.pcm
  File audio\ah1t_seacobra_slap_int.pcm
  File audio\ah1t_seacobra_turbine_ext.pcm
  File audio\ah1t_seacobra_turbine_int.pcm
  File audio\ah1t_seacobra_winddown_ext.pcm
  File audio\ah1t_seacobra_winddown_int.pcm
  File audio\ah1t_seacobra_windup_ext.pcm
  File audio\ah1t_seacobra_windup_int.pcm
  File audio\amb1.pcm
  File audio\amb2.pcm
  File audio\amb3.pcm
  File audio\amb4.pcm
  File audio\amb5.pcm
  File audio\an12b.pcm
  File audio\ap_a2a.pcm
  File audio\ap_mca.pcm
  File audio\aprotdne.pcm
  File audio\aprotdni.pcm
  File audio\aprotore.pcm
  File audio\aprotores.pcm
  File audio\aprotoret.pcm
  File audio\aprotori.pcm
  File audio\aprotoris.pcm
  File audio\aprotorit.pcm
  File audio\aprotupe.pcm
  File audio\aprotupi.pcm
  File audio\ataka_e.pcm
  File audio\ataka_i.pcm
  File audio\blackhawk_a2a.pcm
  File audio\blackhawk_mca.pcm
  File audio\blackhawk_rotor_ext.pcm
  File audio\blackhawk_rotor_int.pcm
  File audio\blackhawk_slap_ext.pcm
  File audio\blackhawk_slap_int.pcm
  File audio\blackhawk_turbine_ext.pcm
  File audio\blackhawk_turbine_int.pcm
  File audio\blackhawk_winddown_ext.pcm
  File audio\blackhawk_winddown_int.pcm
  File audio\blackhawk_windup_ext.pcm
  File audio\blackhawk_windup_int.pcm
  File audio\c-130.pcm
  File audio\c17.pcm
  File audio\ch3_a2a.pcm
  File audio\ch3_mca.pcm
  File audio\ch3.pcm
  File audio\ch3_rotor_ext.pcm
  File audio\ch3_rotor_int.pcm
  File audio\ch3_slap_ext.pcm
  File audio\ch3_slap_int.pcm
  File audio\ch3_turbine_ext.pcm
  File audio\ch3_turbine_int.pcm
  File audio\ch3_winddown_ext.pcm
  File audio\ch3_winddown_int.pcm
  File audio\ch3_windup_ext.pcm
  File audio\ch3_windup_int.pcm
  File audio\ch46e_a2a.pcm
  File audio\ch46e_mca.pcm
  File audio\ch46e_rotor_ext.pcm
  File audio\ch46e_rotor_int.pcm
  File audio\ch46e_slap_ext.pcm
  File audio\ch46e_slap_int.pcm
  File audio\ch46e_turbine_ext.pcm
  File audio\ch46e_turbine_int.pcm
  File audio\ch46e_winddown_ext.pcm
  File audio\ch46e_winddown_int.pcm
  File audio\ch46e_windup_ext.pcm
  File audio\ch46e_windup_int.pcm
  File audio\ch47.pcm
  File audio\ch53e.pcm
  File audio\chaffe.pcm
  File audio\chaffi.pcm
  File audio\chaparral.pcm
  File audio\chgune.pcm
  File audio\chguni.pcm
  File audio\comanche_a2a.pcm
  File audio\comanche_mca.pcm
  File audio\comanche_rotor_ext.pcm
  File audio\comanche_rotor_int.pcm
  File audio\comanche_slap_ext.pcm
  File audio\comanche_slap_int.pcm
  File audio\comanche_turbine_ext.pcm
  File audio\comanche_turbine_int.pcm
  File audio\comanche_winddown_ext.pcm
  File audio\comanche_winddown_int.pcm
  File audio\comanche_windup_ext.pcm
  File audio\comanche_windup_int.pcm
  File audio\explosion_distant1.pcm
  File audio\explosion_distant2.pcm
  File audio\explosion_distant3.pcm
  File audio\explosion_distant4.pcm
  File audio\explosion_distant5.pcm
  File audio\explosion_distant6.pcm
  File audio\explosion_distant7.pcm
  File audio\explosions_door_ka52_1.pcm
  File audio\explosions_door_ka52_2.pcm
  File audio\explosions_door_ka52_e.pcm
  File audio\explosions_door_ka52_i.pcm
  File audio\explosions_door_ka52.pcm
  File audio\flaree.pcm
  File audio\flarei.pcm
  File audio\grstrafe.pcm
  File audio\ha_a2a.pcm
  File audio\ha_mca.pcm
  File audio\harotdne.pcm
  File audio\harotdni.pcm
  File audio\harotore.pcm
  File audio\harotores.pcm
  File audio\harotoret.pcm
  File audio\harotori.pcm
  File audio\harotoris.pcm
  File audio\harotorit.pcm
  File audio\harotupe.pcm
  File audio\harotupi.pcm
  File audio\h_artill.pcm
  File audio\hc_crash.pcm
  File audio\hc_doors.pcm
  File audio\hc_shotd.pcm
  File audio\hind_a2a.pcm
  File audio\hind_mca.pcm
  File audio\hind_rotor_ext.pcm
  File audio\hind_rotor_int.pcm
  File audio\hind_slap_ext.pcm
  File audio\hind_slap_int.pcm
  File audio\hind_turbine_ext.pcm
  File audio\hind_turbine_int.pcm
  File audio\hind_winddown_ext.pcm
  File audio\hind_winddown_int.pcm
  File audio\hind_windup_ext.pcm
  File audio\hind_windup_int.pcm
  File audio\hokum_a2a.pcm
  File audio\hokum_mca.pcm
  File audio\hokum_rotor_ext.pcm
  File audio\hokum_rotor_int.pcm
  File audio\hokum_slap_ext.pcm
  File audio\hokum_slap_int.pcm
  File audio\hokum_turbine_ext.pcm
  File audio\hokum_turbine_int.pcm
  File audio\hokum_winddown_ext.pcm
  File audio\hokum_winddown_int.pcm
  File audio\hokum_windup_ext.pcm
  File audio\hokum_windup_int.pcm
  File audio\hov_move.pcm
  File audio\hov_tick.pcm
  File audio\hv_dmg1e.pcm
  File audio\hv_dmg1i.pcm
  File audio\hv_dmg2e.pcm
  File audio\hv_dmg2i.pcm
  File audio\hv_mgun.pcm
  File audio\hv_rain.pcm
  File audio\hv_wind.pcm
  File audio\IL76.pcm
  File audio\incoming.pcm
  File audio\jeepmove.pcm
  File audio\jeeptick.pcm
  File audio\jet_aft.pcm
  File audio\jet_high.pcm
  File audio\jet_low.pcm
  File audio\jet_med.pcm
  File audio\jungle.pcm
  File audio\ka29_a2a.pcm
  File audio\ka29_mca.pcm
  File audio\ka29_rotor_ext.pcm
  File audio\ka29_rotor_int.pcm
  File audio\ka29_slap_ext.pcm
  File audio\ka29_slap_int.pcm
  File audio\ka29_turbine_ext.pcm
  File audio\ka29_turbine_int.pcm
  File audio\ka29_winddown_ext.pcm
  File audio\ka29_winddown_int.pcm
  File audio\ka29_windup_ext.pcm
  File audio\ka29_windup_int.pcm
  File audio\ka50_a2a.pcm
  File audio\ka50_mca.pcm
  File audio\ka50_rotor_ext.pcm
  File audio\ka50_rotor_int.pcm
  File audio\ka50_slap_ext.pcm
  File audio\ka50_slap_int.pcm
  File audio\ka50_turbine_ext.pcm
  File audio\ka50_turbine_int.pcm
  File audio\ka50_winddown_ext.pcm
  File audio\ka50_winddown_int.pcm
  File audio\ka50_windup_ext.pcm
  File audio\ka50_windup_int.pcm
  File audio\kiowa_a2a.pcm
  File audio\kiowa_mca.pcm
  File audio\kiowa_rotor_ext.pcm
  File audio\kiowa_rotor_int.pcm
  File audio\kiowa_slap_ext.pcm
  File audio\kiowa_slap_int.pcm
  File audio\kiowa_turbine_ext.pcm
  File audio\kiowa_turbine_int.pcm
  File audio\kiowa_winddown_ext.pcm
  File audio\kiowa_winddown_int.pcm
  File audio\kiowa_windup_ext.pcm
  File audio\kiowa_windup_int.pcm
  File audio\l_explsn.pcm
  File audio\lg_rotdn.pcm
  File audio\lg_rotor.pcm
  File audio\lg_rotup.pcm
  File audio\lg_water.pcm
  File audio\lock1.pcm
  File audio\lock_on2.pcm
  File audio\lrlaunch.pcm
  File audio\lstrike.pcm
  File audio\lt_dmg1e.pcm
  File audio\lt_dmg1i.pcm
  File audio\lt_dmg2e.pcm
  File audio\lt_dmg2i.pcm
  File audio\lt_mgun.pcm
  File audio\lt_rain.pcm
  File audio\lt_wind.pcm
  File audio\m_artill.pcm
  File audio\md_rotdn.pcm
  File audio\md_rotor.pcm
  File audio\md_rotup.pcm
  File audio\m_explsn.pcm
  File audio\mi16.pcm
  File audio\missilee.pcm
  File audio\missilei.pcm
  File audio\rockete.pcm
  File audio\rocketi.pcm
  File audio\rubble.pcm
  File audio\screech.pcm
  File audio\sea.pcm
  File audio\s_explsn.pcm
  File audio\sh_doors.pcm
  File audio\shipmove.pcm
  File audio\smokeGrenade.pcm
  File audio\sm_rotdn.pcm
  File audio\sm_rotor.pcm
  File audio\sm_rotup.pcm
  File audio\sm_water.pcm
  File audio\srlaunch.pcm
  File audio\stinger_e.pcm
  File audio\stinger_i.pcm
  File audio\sweep1.pcm
  File audio\tankmove.pcm
  File audio\tanktick.pcm
  File audio\thunder.pcm
  File audio\trckmove.pcm
  File audio\trcktick.pcm
  File audio\undercar.pcm
  File audio\v22.pcm

SectionEnd


;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SectionExe ${LANG_ENGLISH} "Install cohokum.exe, readme.html, additional payload screens, motd.txt and tlate6.dat language file"
;  LangString DESC_SecGWUT ${LANG_ENGLISH} "Weapons and Units Tweaker files"
  LangString DESC_SecBackup ${LANG_ENGLISH} "Backup exe and wut files in a subdirectory 'backup' "
  LangString DESC_SecUIScreens ${LANG_ENGLISH} "Install new more immersive UI screens"

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	 !insertmacro MUI_DESCRIPTION_TEXT ${SecBackup} $(DESC_SecBackup)
    !insertmacro MUI_DESCRIPTION_TEXT ${SectionExe} $(DESC_SectionExe)
    !insertmacro MUI_DESCRIPTION_TEXT ${SectionUIScreens} $(DESC_SecUIScreens)
 ;   !insertmacro MUI_DESCRIPTION_TEXT ${SecGWUT} $(DESC_SecGWUT)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
;--------------------------------
