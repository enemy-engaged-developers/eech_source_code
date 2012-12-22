;NSIS Modern User Interface
;EECH setup exe script, by gotcha jan 2005

SetCompressor /SOLID lzma

;--------------------------------
;Include Modern UI

	!include "MUI.nsh"

;--------------------------------
;General

	;define these variable
	!define VERSION "1.15.0"

	;Name and file
	Name "EECH Dev maps release ${VERSION}"
	OutFile "eech-maps-${VERSION}.exe"

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
	!insertmacro MUI_PAGE_FINISH

	ShowInstDetails show
;--------------------------------
;Languages

	!insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

	!define SRCDIR "D:\GAMES\EE_INST"
	!define EE_BASE_DIR "${SRCDIR}"
	!define EE_MAPS_DIR "${EE_BASE_DIR}"


Section "EECH ${VERSION} maps" SectionMaps

	SetOutPath "$INSTDIR\common\maps"

	File "${EE_MAPS_DIR}\common\maps\maplist.txt"

	SetOutPath "$INSTDIR\common\maps\map1\camp01"

	File "${EE_MAPS_DIR}\common\maps\map1\camp01\THAILAND.BIN"
	File "${EE_MAPS_DIR}\common\maps\map1\camp01\THAILAND.CHC"
	File "${EE_MAPS_DIR}\common\maps\map1\camp01\THAILAND.SCR"
	File "${EE_MAPS_DIR}\common\maps\map1\camp01\THAILAND.SID"

	SetOutPath "$INSTDIR\common\maps\map1\campaign"

	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Briefing.dat"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\CAMPAIGN.POP"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Formcomp.dat"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\FORMS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Mult3.pop"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Mult3.spc"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\PILOT.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\thailand.bin"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Thailand.cmp"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Thailand.dem"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Thailand.fre"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\thailand.sav"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\Thailand.sgl"
	File "${EE_MAPS_DIR}\common\maps\map1\campaign\thailand.sid"

	SetOutPath "$INSTDIR\common\maps\map1\RAFop01"

	File "${EE_MAPS_DIR}\common\maps\map1\RAFop01\Burma.bin"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFop01\Burma.chc"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFop01\Burma.scr"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFop01\Burma.sid"

	SetOutPath "$INSTDIR\common\maps\map1\RAFskirm01"

	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm01\Thailand.bin"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm01\THAILAND.SCR"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm01\Thailand.sid"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm01\Thailand.skr"

	SetOutPath "$INSTDIR\common\maps\map1\RAFskirm02"

	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm02\Thailand.bin"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm02\THAILAND.SCR"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm02\Thailand.sid"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm02\Thailand.skr"

	SetOutPath "$INSTDIR\common\maps\map1\RAFskirm03"

	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm03\Thailand.bin"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm03\THAILAND.SCR"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm03\Thailand.sid"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm03\Thailand.skr"

	SetOutPath "$INSTDIR\common\maps\map1\RAFskirm04"

	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm04\Thailand.bin"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm04\THAILAND.SCR"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm04\Thailand.sid"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm04\Thailand.skr"

	SetOutPath "$INSTDIR\common\maps\map1\RAFskirm05"

	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm05\Thailand.bin"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm05\THAILAND.SCR"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm05\Thailand.sid"
	File "${EE_MAPS_DIR}\common\maps\map1\RAFskirm05\Thailand.skr"

	SetOutPath "$INSTDIR\common\maps\map1\route"

	File "${EE_MAPS_DIR}\common\maps\map1\route\AIRDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\AIRDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map1\route\bridge.dat"
	File "${EE_MAPS_DIR}\common\maps\map1\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map1\route\CITYNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\FIXED_W.LOP"
	File "${EE_MAPS_DIR}\common\maps\map1\route\FIXED_W.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\GROUND.LOP"
	File "${EE_MAPS_DIR}\common\maps\map1\route\GROUND.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\HC_KIEV.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\HC_TARAW.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\HELICOP.LOP"
	File "${EE_MAPS_DIR}\common\maps\map1\route\HELICOP.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\HELICOP2.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\HELL_ST.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\HOVER.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\rivdata.dat"
	File "${EE_MAPS_DIR}\common\maps\map1\route\rivdata.nde"
	File "${EE_MAPS_DIR}\common\maps\map1\route\rivdata.wp"
	File "${EE_MAPS_DIR}\common\maps\map1\route\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map1\route\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map1\route\SEADATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\SEADATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map1\route\SHIP.LOP"
	File "${EE_MAPS_DIR}\common\maps\map1\route\SHIP.RT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\Special.rt"
	File "${EE_MAPS_DIR}\common\maps\map1\route\UTILDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map1\route\utildata.nde"
	File "${EE_MAPS_DIR}\common\maps\map1\route\utildata.wp"

	SetOutPath "$INSTDIR\common\maps\map1\terrain"

	File "${EE_MAPS_DIR}\common\maps\map1\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map1\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map1\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map1\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map1\terrain\terrain.sel"
	File "${EE_MAPS_DIR}\common\maps\map1\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map1\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map1\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map10\camp01"

	File "${EE_MAPS_DIR}\common\maps\map10\camp01\LYBIA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map10\camp01\LYBIA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map10\camp01\LYBIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map10\camp01\LYBIA.SID"

	SetOutPath "$INSTDIR\common\maps\map10\camp02"

	File "${EE_MAPS_DIR}\common\maps\map10\camp02\LYBIA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map10\camp02\LYBIA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map10\camp02\LYBIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map10\camp02\LYBIA.SID"

	SetOutPath "$INSTDIR\common\maps\map10\camp03"

	File "${EE_MAPS_DIR}\common\maps\map10\camp03\LYBIA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map10\camp03\LYBIA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map10\camp03\LYBIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map10\camp03\LYBIA.SID"

	SetOutPath "$INSTDIR\common\maps\map10\route"

	File "${EE_MAPS_DIR}\common\maps\map10\route\BOUNDARY.DAT"
	File "${EE_MAPS_DIR}\common\maps\map10\route\BOUNDARY.NDE"
	File "${EE_MAPS_DIR}\common\maps\map10\route\BOUNDARY.WP"
	File "${EE_MAPS_DIR}\common\maps\map10\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map10\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map10\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map10\route\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map10\route\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map10\route\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map10\terrain"

	File "${EE_MAPS_DIR}\common\maps\map10\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map10\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map10\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map10\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map10\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map10\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map10\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map11\camp01"

	File "${EE_MAPS_DIR}\common\maps\map11\camp01\GRAND.BIN"
	File "${EE_MAPS_DIR}\common\maps\map11\camp01\GRAND.CHC"
	File "${EE_MAPS_DIR}\common\maps\map11\camp01\GRAND.SCR"
	File "${EE_MAPS_DIR}\common\maps\map11\camp01\GRAND.SID"

	SetOutPath "$INSTDIR\common\maps\map11\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map11\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map11\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map11\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map11\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map11\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map11\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map11\TERRAIN"

	File "${EE_MAPS_DIR}\common\maps\map11\TERRAIN\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map11\TERRAIN\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map11\TERRAIN\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map11\TERRAIN\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map11\TERRAIN\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map11\TERRAIN\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map11\TERRAIN\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map12"

	File "${EE_MAPS_DIR}\common\maps\map12\MAPINFO.TXT"

	SetOutPath "$INSTDIR\common\maps\map12\camp01"

	File "${EE_MAPS_DIR}\common\maps\map12\camp01\MARS.BIN"
	File "${EE_MAPS_DIR}\common\maps\map12\camp01\MARS.CHC"
	File "${EE_MAPS_DIR}\common\maps\map12\camp01\MARS.SCR"
	File "${EE_MAPS_DIR}\common\maps\map12\camp01\MARS.SID"

	SetOutPath "$INSTDIR\common\maps\map12\camp02"

	File "${EE_MAPS_DIR}\common\maps\map12\camp02\MARS.BIN"
	File "${EE_MAPS_DIR}\common\maps\map12\camp02\MARS.CHC"
	File "${EE_MAPS_DIR}\common\maps\map12\camp02\MARS.SCR"
	File "${EE_MAPS_DIR}\common\maps\map12\camp02\MARS.SID"

	SetOutPath "$INSTDIR\common\maps\map12\camp03"

	File "${EE_MAPS_DIR}\common\maps\map12\camp03\MARS.BIN"
	File "${EE_MAPS_DIR}\common\maps\map12\camp03\MARS.CHC"
	File "${EE_MAPS_DIR}\common\maps\map12\camp03\MARS.SCR"
	File "${EE_MAPS_DIR}\common\maps\map12\camp03\MARS.SID"

	SetOutPath "$INSTDIR\common\maps\map12\route"

	File "${EE_MAPS_DIR}\common\maps\map12\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map12\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map12\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map12\route\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map12\route\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map12\route\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map12\terrain"

	File "${EE_MAPS_DIR}\common\maps\map12\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map12\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map12\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map12\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map12\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map12\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map12\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map13"

	File "${EE_MAPS_DIR}\common\maps\map13\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map13\camp01"

	File "${EE_MAPS_DIR}\common\maps\map13\camp01\Alexander Archipelago.chc"
	File "${EE_MAPS_DIR}\common\maps\map13\camp01\Alexander.bin"
	File "${EE_MAPS_DIR}\common\maps\map13\camp01\Alexander.scr"
	File "${EE_MAPS_DIR}\common\maps\map13\camp01\Alexander.SID"

	SetOutPath "$INSTDIR\common\maps\map13\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map13\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map13\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map13\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map13\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map13\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map13\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map13\terrain"

	File "${EE_MAPS_DIR}\common\maps\map13\terrain\2DMAPCOL.PSD"
	File "${EE_MAPS_DIR}\common\maps\map13\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map13\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map13\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map13\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map13\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map13\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map14"

	File "${EE_MAPS_DIR}\common\maps\map14\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map14\camp01"

	File "${EE_MAPS_DIR}\common\maps\map14\camp01\skagway.BIN"
	File "${EE_MAPS_DIR}\common\maps\map14\camp01\skagway.CHC"
	File "${EE_MAPS_DIR}\common\maps\map14\camp01\skagway.SCR"
	File "${EE_MAPS_DIR}\common\maps\map14\camp01\skagway.SID"

	SetOutPath "$INSTDIR\common\maps\map14\camp02"

	File "${EE_MAPS_DIR}\common\maps\map14\camp02\skagway.BIN"
	File "${EE_MAPS_DIR}\common\maps\map14\camp02\skagway.CHC"
	File "${EE_MAPS_DIR}\common\maps\map14\camp02\skagway.SCR"
	File "${EE_MAPS_DIR}\common\maps\map14\camp02\skagway.SID"

	SetOutPath "$INSTDIR\common\maps\map14\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map14\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map14\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map14\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map14\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map14\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map14\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map14\terrain"

	File "${EE_MAPS_DIR}\common\maps\map14\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map14\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map14\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map14\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map14\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map14\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map14\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map15"

	File "${EE_MAPS_DIR}\common\maps\map15\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map15\camp01"

	File "${EE_MAPS_DIR}\common\maps\map15\camp01\RedSea.bin"
	File "${EE_MAPS_DIR}\common\maps\map15\camp01\RedSea.scr"
	File "${EE_MAPS_DIR}\common\maps\map15\camp01\RedSea.SID"
	File "${EE_MAPS_DIR}\common\maps\map15\camp01\Saudi Arabia Red Sea.chc"

	SetOutPath "$INSTDIR\common\maps\map15\camp02"

	File "${EE_MAPS_DIR}\common\maps\map15\camp02\RedSea.bin"
	File "${EE_MAPS_DIR}\common\maps\map15\camp02\RedSea.scr"
	File "${EE_MAPS_DIR}\common\maps\map15\camp02\RedSea.SID"
	File "${EE_MAPS_DIR}\common\maps\map15\camp02\Saudi Arabia Red Sea.chc"

	SetOutPath "$INSTDIR\common\maps\map15\camp03"

	File "${EE_MAPS_DIR}\common\maps\map15\camp03\RedSea.bin"
	File "${EE_MAPS_DIR}\common\maps\map15\camp03\RedSea.scr"
	File "${EE_MAPS_DIR}\common\maps\map15\camp03\RedSea.SID"
	File "${EE_MAPS_DIR}\common\maps\map15\camp03\Saudi Arabia Red Sea.chc"

	SetOutPath "$INSTDIR\common\maps\map15\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\BOUNDARY.DAT"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\BOUNDARY.NDE"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\BOUNDARY.WP"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map15\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map15\terrain"

	File "${EE_MAPS_DIR}\common\maps\map15\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map15\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map15\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map15\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map15\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map15\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map15\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map16"

	File "${EE_MAPS_DIR}\common\maps\map16\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map16\camp01"

	File "${EE_MAPS_DIR}\common\maps\map16\camp01\Kenai Peninsula.chc"
	File "${EE_MAPS_DIR}\common\maps\map16\camp01\Kenai_Peninsula.bin"
	File "${EE_MAPS_DIR}\common\maps\map16\camp01\Kenai_Peninsula.BTP"
	File "${EE_MAPS_DIR}\common\maps\map16\camp01\Kenai_Peninsula.scr"
	File "${EE_MAPS_DIR}\common\maps\map16\camp01\Kenai_Peninsula.SID"

	SetOutPath "$INSTDIR\common\maps\map16\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map16\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map16\terrain"

	File "${EE_MAPS_DIR}\common\maps\map16\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map16\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map16\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map16\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map16\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map16\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map16\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map17"

	File "${EE_MAPS_DIR}\common\maps\map17\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map17\camp01"

	File "${EE_MAPS_DIR}\common\maps\map17\camp01\AFOGNAK.bin"
	File "${EE_MAPS_DIR}\common\maps\map17\camp01\AFOGNAK.chc"
	File "${EE_MAPS_DIR}\common\maps\map17\camp01\AFOGNAK.scr"
	File "${EE_MAPS_DIR}\common\maps\map17\camp01\AFOGNAK.SID"

	SetOutPath "$INSTDIR\common\maps\map17\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map17\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map17\terrain"

	File "${EE_MAPS_DIR}\common\maps\map17\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map17\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map17\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map17\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map17\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map17\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map17\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map18"

	File "${EE_MAPS_DIR}\common\maps\map18\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map18\camp01"

	File "${EE_MAPS_DIR}\common\maps\map18\camp01\Puerto Rico.chc"
	File "${EE_MAPS_DIR}\common\maps\map18\camp01\Puerto_Rico.bin"
	File "${EE_MAPS_DIR}\common\maps\map18\camp01\Puerto_Rico.scr"
	File "${EE_MAPS_DIR}\common\maps\map18\camp01\Puerto_Rico.SID"

	SetOutPath "$INSTDIR\common\maps\map18\camp02"

	File "${EE_MAPS_DIR}\common\maps\map18\camp02\Puerto Rico.chc"
	File "${EE_MAPS_DIR}\common\maps\map18\camp02\Puerto_Rico.bin"
	File "${EE_MAPS_DIR}\common\maps\map18\camp02\Puerto_Rico.scr"
	File "${EE_MAPS_DIR}\common\maps\map18\camp02\Puerto_Rico.SID"

	SetOutPath "$INSTDIR\common\maps\map18\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map18\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map18\terrain"

	File "${EE_MAPS_DIR}\common\maps\map18\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map18\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map18\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map18\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map18\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map18\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map18\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map19"

	File "${EE_MAPS_DIR}\common\maps\map19\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map19\camp01"

	File "${EE_MAPS_DIR}\common\maps\map19\camp01\Jordan Dead Sea.chc"
	File "${EE_MAPS_DIR}\common\maps\map19\camp01\jordan.bin"
	File "${EE_MAPS_DIR}\common\maps\map19\camp01\jordan.scr"
	File "${EE_MAPS_DIR}\common\maps\map19\camp01\jordan.SID"

	SetOutPath "$INSTDIR\common\maps\map19\camp02"

	File "${EE_MAPS_DIR}\common\maps\map19\camp02\Jordan Dead Sea.chc"
	File "${EE_MAPS_DIR}\common\maps\map19\camp02\jordan.bin"
	File "${EE_MAPS_DIR}\common\maps\map19\camp02\jordan.scr"
	File "${EE_MAPS_DIR}\common\maps\map19\camp02\jordan.SID"

	SetOutPath "$INSTDIR\common\maps\map19\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map19\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map19\terrain"

	File "${EE_MAPS_DIR}\common\maps\map19\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map19\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map19\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map19\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map19\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map19\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map19\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map2\camp01"

	File "${EE_MAPS_DIR}\common\maps\map2\camp01\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\camp01\CUBA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map2\camp01\CUBA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map2\camp01\CUBA.SID"

	SetOutPath "$INSTDIR\common\maps\map2\camp02"

	File "${EE_MAPS_DIR}\common\maps\map2\camp02\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\camp02\Cuba.chc"
	File "${EE_MAPS_DIR}\common\maps\map2\camp02\Cuba.sid"

	SetOutPath "$INSTDIR\common\maps\map2\camp03"

	File "${EE_MAPS_DIR}\common\maps\map2\camp03\Cuba.bin"
	File "${EE_MAPS_DIR}\common\maps\map2\camp03\CUBA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map2\camp03\CUBA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map2\camp03\Cuba.sid"

	SetOutPath "$INSTDIR\common\maps\map2\campaign"

	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Briefing.dat"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\CAMPAIGN.POP"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\cuba.bin"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Cuba.cmp"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Cuba.dem"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Cuba.fre"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\cuba.sav"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Cuba.sgl"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\cuba.sid"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\cubaair.bin"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Formcomp.dat"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\FORMS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Mult3.pop"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\Mult3.spc"
	File "${EE_MAPS_DIR}\common\maps\map2\campaign\PILOT.DAT"

	SetOutPath "$INSTDIR\common\maps\map2\fidellives"

	File "${EE_MAPS_DIR}\common\maps\map2\fidellives\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\fidellives\CUBA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map2\fidellives\CUBA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map2\fidellives\CUBA.SID"

	SetOutPath "$INSTDIR\common\maps\map2\invasion"

	File "${EE_MAPS_DIR}\common\maps\map2\invasion\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\invasion\CUBA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map2\invasion\CUBA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map2\invasion\CUBA.SID"

	SetOutPath "$INSTDIR\common\maps\map2\RAFop01"

	File "${EE_MAPS_DIR}\common\maps\map2\RAFop01\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFop01\CUBA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFop01\CUBA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFop01\CUBA.SID"

	SetOutPath "$INSTDIR\common\maps\map2\RAFskirm01"

	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm01\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm01\Cuba.sid"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm01\Cuba.skr"

	SetOutPath "$INSTDIR\common\maps\map2\RAFskirm02"

	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm02\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm02\Cuba.sid"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm02\Cuba.skr"

	SetOutPath "$INSTDIR\common\maps\map2\RAFskirm03"

	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm03\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm03\Cuba.sid"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm03\Cuba.skr"

	SetOutPath "$INSTDIR\common\maps\map2\RAFskirm04"

	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm04\CUBA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm04\Cuba.sid"
	File "${EE_MAPS_DIR}\common\maps\map2\RAFskirm04\Cuba.skr"

	SetOutPath "$INSTDIR\common\maps\map2\route"

	File "${EE_MAPS_DIR}\common\maps\map2\route\AIRDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\AIRDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map2\route\AIRPORTS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\AIRTRN1.DAT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\AIRTRN1.NDE"
	File "${EE_MAPS_DIR}\common\maps\map2\route\bridge.dat"
	File "${EE_MAPS_DIR}\common\maps\map2\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map2\route\Cityname.dat"
	File "${EE_MAPS_DIR}\common\maps\map2\route\FIXED_W.LOP"
	File "${EE_MAPS_DIR}\common\maps\map2\route\FIXED_W.RT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\GROUND.LOP"
	File "${EE_MAPS_DIR}\common\maps\map2\route\GROUND.RT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\HC_KIEV.RT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\HC_TARAW.RT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\HELICOP.LOP"
	File "${EE_MAPS_DIR}\common\maps\map2\route\HELICOP.RT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\rivdata.dat"
	File "${EE_MAPS_DIR}\common\maps\map2\route\rivdata.nde"
	File "${EE_MAPS_DIR}\common\maps\map2\route\rivdata.wp"
	File "${EE_MAPS_DIR}\common\maps\map2\route\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map2\route\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map2\route\seadata.dat"
	File "${EE_MAPS_DIR}\common\maps\map2\route\seadata.nde"
	File "${EE_MAPS_DIR}\common\maps\map2\route\SHIP.LOP"
	File "${EE_MAPS_DIR}\common\maps\map2\route\SHIP.RT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\Special.rt"
	File "${EE_MAPS_DIR}\common\maps\map2\route\UTILDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map2\route\utildata.nde"
	File "${EE_MAPS_DIR}\common\maps\map2\route\utildata.wp"

	SetOutPath "$INSTDIR\common\maps\map2\terrain"

	File "${EE_MAPS_DIR}\common\maps\map2\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map2\terrain\DEFAULT.RGB"
	File "${EE_MAPS_DIR}\common\maps\map2\terrain\DEFAULT.SEC"
	File "${EE_MAPS_DIR}\common\maps\map2\terrain\TERRAIN.FFP"
	File "${EE_MAPS_DIR}\common\maps\map2\terrain\terrain.sel"
	File "${EE_MAPS_DIR}\common\maps\map2\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map2\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map2\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map20"

	File "${EE_MAPS_DIR}\common\maps\map20\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map20\camp01"

	File "${EE_MAPS_DIR}\common\maps\map20\camp01\LAKE POWELL.CHC"
	File "${EE_MAPS_DIR}\common\maps\map20\camp01\LAKE_POWELL.BIN"
	File "${EE_MAPS_DIR}\common\maps\map20\camp01\LAKE_POWELL.SCR"
	File "${EE_MAPS_DIR}\common\maps\map20\camp01\LAKE_POWELL.SID"

	SetOutPath "$INSTDIR\common\maps\map20\route"

	File "${EE_MAPS_DIR}\common\maps\map20\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map20\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map20\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map20\route\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map20\route\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map20\route\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map20\terrain"

	File "${EE_MAPS_DIR}\common\maps\map20\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map20\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map20\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map20\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map20\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map20\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map20\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map3\camp01"

	File "${EE_MAPS_DIR}\common\maps\map3\camp01\GEORGIA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map3\camp01\GEORGIA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map3\camp01\GEORGIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map3\camp01\GEORGIA.SID"

	SetOutPath "$INSTDIR\common\maps\map3\camp02"

	File "${EE_MAPS_DIR}\common\maps\map3\camp02\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\camp02\Georgia.chc"
	File "${EE_MAPS_DIR}\common\maps\map3\camp02\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\camp02\Georgia.sid"

	SetOutPath "$INSTDIR\common\maps\map3\camp03"

	File "${EE_MAPS_DIR}\common\maps\map3\camp03\GEORGIA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map3\camp03\GEORGIA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map3\camp03\GEORGIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map3\camp03\Georgia.sid"

	SetOutPath "$INSTDIR\common\maps\map3\campaign"

	File "${EE_MAPS_DIR}\common\maps\map3\campaign\Briefing.dat"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\CAMPAIGN.POP"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\Formcomp.dat"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\FORMS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\Georgia.cmp"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\GEORGIA.DEM"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\Georgia.fre"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\georgia.sav"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\Georgia.sgl"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\Mult3.pop"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\Mult3.spc"
	File "${EE_MAPS_DIR}\common\maps\map3\campaign\PILOT.DAT"

	SetOutPath "$INSTDIR\common\maps\map3\RAFop01"

	File "${EE_MAPS_DIR}\common\maps\map3\RAFop01\GEORGIA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFop01\Georgia.chc"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFop01\GEORGIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFop01\Georgia.sid"

	SetOutPath "$INSTDIR\common\maps\map3\RAFop02"

	File "${EE_MAPS_DIR}\common\maps\map3\RAFop02\GEORGIA.BIN"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFop02\GEORGIA.CHC"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFop02\GEORGIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFop02\Georgia.sid"

	SetOutPath "$INSTDIR\common\maps\map3\RAFskirm01"

	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm01\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm01\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm01\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm01\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\RAFskirm02"

	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm02\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm02\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm02\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm02\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\RAFskirm03"

	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm03\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm03\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm03\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm03\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\RAFskirm04"

	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm04\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm04\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm04\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm04\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\RAFskirm05"

	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm05\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm05\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm05\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\RAFskirm05\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\RedSlice"

	File "${EE_MAPS_DIR}\common\maps\map3\RedSlice\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\RedSlice\Georgia.chc"
	File "${EE_MAPS_DIR}\common\maps\map3\RedSlice\GEORGIA.SCR"
	File "${EE_MAPS_DIR}\common\maps\map3\RedSlice\Georgia.sid"

	SetOutPath "$INSTDIR\common\maps\map3\route"

	File "${EE_MAPS_DIR}\common\maps\map3\route\AIRDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\AIRDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map3\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map3\route\CITYNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\FIXED_W.LOP"
	File "${EE_MAPS_DIR}\common\maps\map3\route\FIXED_W.RT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\GROUND.LOP"
	File "${EE_MAPS_DIR}\common\maps\map3\route\GROUND.RT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\HC_KIEV.RT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\HC_TARAW.RT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\HELICOP.LOP"
	File "${EE_MAPS_DIR}\common\maps\map3\route\HELICOP.RT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\rivdata.dat"
	File "${EE_MAPS_DIR}\common\maps\map3\route\rivdata.nde"
	File "${EE_MAPS_DIR}\common\maps\map3\route\rivdata.wp"
	File "${EE_MAPS_DIR}\common\maps\map3\route\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map3\route\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map3\route\SAM_RUN.RT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\seadata.dat"
	File "${EE_MAPS_DIR}\common\maps\map3\route\seadata.nde"
	File "${EE_MAPS_DIR}\common\maps\map3\route\SHIP.LOP"
	File "${EE_MAPS_DIR}\common\maps\map3\route\SHIP.RT"
	File "${EE_MAPS_DIR}\common\maps\map3\route\Special.rt"
	File "${EE_MAPS_DIR}\common\maps\map3\route\utildata.dat"
	File "${EE_MAPS_DIR}\common\maps\map3\route\utildata.nde"
	File "${EE_MAPS_DIR}\common\maps\map3\route\utildata.wp"
	File "${EE_MAPS_DIR}\common\maps\map3\route\VRCS.BAT"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM1A"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM1A\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM1A\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM1A\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM1A\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM1B"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM1B\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM1B\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM1B\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM2A"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM2A\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM2A\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM2A\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM2A\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM2B"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM2B\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM2B\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM2B\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM3A"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3A\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3A\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3A\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3A\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM3B"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3B\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3B\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3B\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM3B\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM4A"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4A\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4A\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4A\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4A\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\TARAWASkirmGM4B"

	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4B\Georgia.bin"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4B\Georgia.scr"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4B\Georgia.sid"
	File "${EE_MAPS_DIR}\common\maps\map3\TARAWASkirmGM4B\Georgia.skr"

	SetOutPath "$INSTDIR\common\maps\map3\terrain"

	File "${EE_MAPS_DIR}\common\maps\map3\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map3\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map3\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map3\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map3\terrain\terrain.sel"
	File "${EE_MAPS_DIR}\common\maps\map3\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map3\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map3\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map31"

	File "${EE_MAPS_DIR}\common\maps\map31\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map31\camp01"

	File "${EE_MAPS_DIR}\common\maps\map31\camp01\Grand Canyon.CHC"
	File "${EE_MAPS_DIR}\common\maps\map31\camp01\Grand.BIN"
	File "${EE_MAPS_DIR}\common\maps\map31\camp01\Grand.SCR"
	File "${EE_MAPS_DIR}\common\maps\map31\camp01\Grand.SID"

	SetOutPath "$INSTDIR\common\maps\map31\route"

	File "${EE_MAPS_DIR}\common\maps\map31\route\BOUNDARY.DAT"
	File "${EE_MAPS_DIR}\common\maps\map31\route\BOUNDARY.NDE"
	File "${EE_MAPS_DIR}\common\maps\map31\route\BOUNDARY.WP"
	File "${EE_MAPS_DIR}\common\maps\map31\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map31\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map31\route\CITYBASE.PLY"
	File "${EE_MAPS_DIR}\common\maps\map31\route\LAKES.PLY"
	File "${EE_MAPS_DIR}\common\maps\map31\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map31\route\RIVERS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map31\route\RIVERS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map31\route\RIVERS.WP"
	File "${EE_MAPS_DIR}\common\maps\map31\route\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map31\route\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map31\route\ROADS.WP"
	File "${EE_MAPS_DIR}\common\maps\map31\route\utils.nde"
	File "${EE_MAPS_DIR}\common\maps\map31\route\utils.wp"

	SetOutPath "$INSTDIR\common\maps\map31\terrain"

	File "${EE_MAPS_DIR}\common\maps\map31\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map31\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map31\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map31\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map31\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map31\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map31\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map32"

	File "${EE_MAPS_DIR}\common\maps\map32\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map32\camp01"

	File "${EE_MAPS_DIR}\common\maps\map32\camp01\Europe.bin"
	File "${EE_MAPS_DIR}\common\maps\map32\camp01\Europe.chc"
	File "${EE_MAPS_DIR}\common\maps\map32\camp01\Europe.scr"
	File "${EE_MAPS_DIR}\common\maps\map32\camp01\Europe.SID"

	SetOutPath "$INSTDIR\common\maps\map32\camp02"

	File "${EE_MAPS_DIR}\common\maps\map32\camp02\Europe.bin"
	File "${EE_MAPS_DIR}\common\maps\map32\camp02\Europe.chc"
	File "${EE_MAPS_DIR}\common\maps\map32\camp02\Europe.scr"
	File "${EE_MAPS_DIR}\common\maps\map32\camp02\Europe.SID"

	SetOutPath "$INSTDIR\common\maps\map32\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map32\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map32\terrain"

	File "${EE_MAPS_DIR}\common\maps\map32\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map32\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map32\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map32\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map32\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map32\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map32\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map35"

	File "${EE_MAPS_DIR}\common\maps\map35\mapinfo.txt"

	SetOutPath "$INSTDIR\common\maps\map35\camp01"

	File "${EE_MAPS_DIR}\common\maps\map35\camp01\Norway.BIN"
	File "${EE_MAPS_DIR}\common\maps\map35\camp01\Norway.CHC"
	File "${EE_MAPS_DIR}\common\maps\map35\camp01\Norway.SCR"
	File "${EE_MAPS_DIR}\common\maps\map35\camp01\Norway.SID"

	SetOutPath "$INSTDIR\common\maps\map35\ROUTE"

	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\ROADDATA.DAT"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\ROADDATA.NDE"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\ROADDATA.WP"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map35\ROUTE\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map35\terrain"

	File "${EE_MAPS_DIR}\common\maps\map35\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map35\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map35\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map35\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map35\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map35\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map35\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map4\Bluethunder"

	File "${EE_MAPS_DIR}\common\maps\map4\Bluethunder\TAIWAN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map4\Bluethunder\TAIWAN.CHC"
	File "${EE_MAPS_DIR}\common\maps\map4\Bluethunder\TAIWAN.SID"

	SetOutPath "$INSTDIR\common\maps\map4\RAFop01"

	File "${EE_MAPS_DIR}\common\maps\map4\RAFop01\TAIWAN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map4\RAFop01\TAIWAN.CHC"
	File "${EE_MAPS_DIR}\common\maps\map4\RAFop01\TAIWAN.SID"

	SetOutPath "$INSTDIR\common\maps\map5\Camp02"

	File "${EE_MAPS_DIR}\common\maps\map5\Camp02\RAFPRIDE.BIN"
	File "${EE_MAPS_DIR}\common\maps\map5\Camp02\RAFPRIDE.CHC"
	File "${EE_MAPS_DIR}\common\maps\map5\Camp02\RAFPRIDE.SCR"
	File "${EE_MAPS_DIR}\common\maps\map5\Camp02\RAFPRIDE.SID"

	SetOutPath "$INSTDIR\common\maps\map5\RAFop01"

	File "${EE_MAPS_DIR}\common\maps\map5\RAFop01\LEBANON.BIN"
	File "${EE_MAPS_DIR}\common\maps\map5\RAFop01\LEBANON.CHC"
	File "${EE_MAPS_DIR}\common\maps\map5\RAFop01\LEBANON.SID"

	SetOutPath "$INSTDIR\common\maps\map5\RAFop02"

	File "${EE_MAPS_DIR}\common\maps\map5\RAFop02\Israel.bin"
	File "${EE_MAPS_DIR}\common\maps\map5\RAFop02\Israel.chc"
	File "${EE_MAPS_DIR}\common\maps\map5\RAFop02\Israel.sid"

	SetOutPath "$INSTDIR\common\maps\map6\camp02"

	File "${EE_MAPS_DIR}\common\maps\map6\camp02\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\camp02\YEMEN.CHC"
	File "${EE_MAPS_DIR}\common\maps\map6\camp02\YEMEN.SCR"
	File "${EE_MAPS_DIR}\common\maps\map6\camp02\YEMEN.SID"

	SetOutPath "$INSTDIR\common\maps\map6\camp03"

	File "${EE_MAPS_DIR}\common\maps\map6\camp03\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\camp03\YEMEN.CHC"
	File "${EE_MAPS_DIR}\common\maps\map6\camp03\YEMEN.SCR"
	File "${EE_MAPS_DIR}\common\maps\map6\camp03\YEMEN.SID"

	SetOutPath "$INSTDIR\common\maps\map6\kimskirm02"

	File "${EE_MAPS_DIR}\common\maps\map6\kimskirm02\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\kimskirm02\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\kimskirm02\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\kimskirm03"

	File "${EE_MAPS_DIR}\common\maps\map6\kimskirm03\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\kimskirm03\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\kimskirm03\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM1A"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM1A\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM1A\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM1A\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM1B"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM1B\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM1B\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM1B\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM2A"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM2A\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM2A\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM2A\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM2B"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM2B\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM2B\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM2B\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM3A"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM3A\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM3A\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM3A\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM3B"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM3B\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM3B\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM3B\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM4A"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM4A\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM4A\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM4A\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM4B"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM4B\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM4B\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM4B\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM5A"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM5A\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM5A\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM5A\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM5B"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM5B\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM5B\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM5B\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM6A"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM6A\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM6A\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM6A\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM6B"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM6B\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM6B\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM6B\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM7A"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM7A\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM7A\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM7A\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\TARAWASkirmYM7B"

	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM7B\YEMEN.BIN"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM7B\YEMEN.SID"
	File "${EE_MAPS_DIR}\common\maps\map6\TARAWASkirmYM7B\YEMEN.SKR"

	SetOutPath "$INSTDIR\common\maps\map6\terrain"

	File "${EE_MAPS_DIR}\common\maps\map6\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map6\terrain\tree_pos.sec"

	SetOutPath "$INSTDIR\common\maps\map7\camp01"

	File "${EE_MAPS_DIR}\common\maps\map7\camp01\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\camp01\Alaska.chc"
	File "${EE_MAPS_DIR}\common\maps\map7\camp01\Alaska.scr"
	File "${EE_MAPS_DIR}\common\maps\map7\camp01\Alaska.sid"

	SetOutPath "$INSTDIR\common\maps\map7\camp02"

	File "${EE_MAPS_DIR}\common\maps\map7\camp02\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\camp02\Alaska.chc"
	File "${EE_MAPS_DIR}\common\maps\map7\camp02\Alaska.scr"
	File "${EE_MAPS_DIR}\common\maps\map7\camp02\Alaska.sid"

	SetOutPath "$INSTDIR\common\maps\map7\camp03"

	File "${EE_MAPS_DIR}\common\maps\map7\camp03\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\camp03\Alaska.chc"
	File "${EE_MAPS_DIR}\common\maps\map7\camp03\Alaska.scr"
	File "${EE_MAPS_DIR}\common\maps\map7\camp03\Alaska.sid"

	SetOutPath "$INSTDIR\common\maps\map7\route"

	File "${EE_MAPS_DIR}\common\maps\map7\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map7\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map7\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map7\route\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map7\route\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map7\route\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM1A"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM1A\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM1A\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM1A\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM1B"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM1B\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM1B\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM1B\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM2A"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM2A\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM2A\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM2A\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM2B"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM2B\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM2B\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM2B\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM3A"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM3A\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM3A\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM3A\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM3B"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM3B\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM3B\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM3B\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM4A"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM4A\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM4A\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM4A\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM4B"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM4B\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM4B\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM4B\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM5A"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM5A\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM5A\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM5A\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\TARAWASkirmAM5B"

	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM5B\Alaska.bin"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM5B\Alaska.sid"
	File "${EE_MAPS_DIR}\common\maps\map7\TARAWASkirmAM5B\Alaska.skr"

	SetOutPath "$INSTDIR\common\maps\map7\terrain"

	File "${EE_MAPS_DIR}\common\maps\map7\terrain\2DMAPCOL.PSD"
	File "${EE_MAPS_DIR}\common\maps\map7\terrain\DEFAULT.RGB"
	File "${EE_MAPS_DIR}\common\maps\map7\terrain\DEFAULT.SEC"
	File "${EE_MAPS_DIR}\common\maps\map7\terrain\TERRAIN.FFP"
	File "${EE_MAPS_DIR}\common\maps\map7\terrain\TERRAIN.SIM"
	File "${EE_MAPS_DIR}\common\maps\map7\terrain\TREE_POS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map7\terrain\TREE_POS.SEC"

	SetOutPath "$INSTDIR\common\maps\map8\CAMP01"

	File "${EE_MAPS_DIR}\common\maps\map8\CAMP01\Aleut.bin"
	File "${EE_MAPS_DIR}\common\maps\map8\CAMP01\Aleut.chc"
	File "${EE_MAPS_DIR}\common\maps\map8\CAMP01\Aleut.scr"
	File "${EE_MAPS_DIR}\common\maps\map8\CAMP01\Aleut.sid"

	SetOutPath "$INSTDIR\common\maps\map8\route"

	File "${EE_MAPS_DIR}\common\maps\map8\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map8\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map8\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map8\route\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map8\route\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map8\route\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map8\terrain"

	File "${EE_MAPS_DIR}\common\maps\map8\terrain\2DMAPCOL.PSD"
	File "${EE_MAPS_DIR}\common\maps\map8\terrain\DEFAULT.RGB"
	File "${EE_MAPS_DIR}\common\maps\map8\terrain\DEFAULT.SEC"
	File "${EE_MAPS_DIR}\common\maps\map8\terrain\TERRAIN.FFP"
	File "${EE_MAPS_DIR}\common\maps\map8\terrain\TERRAIN.SIM"
	File "${EE_MAPS_DIR}\common\maps\map8\terrain\TREE_POS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map8\terrain\TREE_POS.SEC"

	SetOutPath "$INSTDIR\common\maps\map9\camp01"

	File "${EE_MAPS_DIR}\common\maps\map9\camp01\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\camp01\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\camp01\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\camp01\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\camp02"

	File "${EE_MAPS_DIR}\common\maps\map9\camp02\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\camp02\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\camp02\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\camp02\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\camp03"

	File "${EE_MAPS_DIR}\common\maps\map9\camp03\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\camp03\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\camp03\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\camp03\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\camp04"

	File "${EE_MAPS_DIR}\common\maps\map9\camp04\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\camp04\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\camp04\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\camp04\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\camp05"

	File "${EE_MAPS_DIR}\common\maps\map9\camp05\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\camp05\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\camp05\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\camp05\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\camp06"

	File "${EE_MAPS_DIR}\common\maps\map9\camp06\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\camp06\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\camp06\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\camp06\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\camp07"

	File "${EE_MAPS_DIR}\common\maps\map9\camp07\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\camp07\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\camp07\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\camp07\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\route"

	File "${EE_MAPS_DIR}\common\maps\map9\route\BOUNDARY.DAT"
	File "${EE_MAPS_DIR}\common\maps\map9\route\BOUNDARY.NDE"
	File "${EE_MAPS_DIR}\common\maps\map9\route\BOUNDARY.WP"
	File "${EE_MAPS_DIR}\common\maps\map9\route\BRIDGE.DAT"
	File "${EE_MAPS_DIR}\common\maps\map9\route\BRIDGE.POP"
	File "${EE_MAPS_DIR}\common\maps\map9\route\POPNAME.DAT"
	File "${EE_MAPS_DIR}\common\maps\map9\route\ROADS.DAT"
	File "${EE_MAPS_DIR}\common\maps\map9\route\ROADS.NDE"
	File "${EE_MAPS_DIR}\common\maps\map9\route\ROADS.WP"

	SetOutPath "$INSTDIR\common\maps\map9\Sneakattack"

	File "${EE_MAPS_DIR}\common\maps\map9\Sneakattack\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\Sneakattack\KUWAIT.CHC"
	File "${EE_MAPS_DIR}\common\maps\map9\Sneakattack\KUWAIT.SCR"
	File "${EE_MAPS_DIR}\common\maps\map9\Sneakattack\KUWAIT.SID"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM1A"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM1A\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM1A\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM1A\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM1B"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM1B\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM1B\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM1B\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM2A"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM2A\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM2A\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM2A\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM2B"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM2B\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM2B\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM2B\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM3A"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM3A\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM3A\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM3A\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM3B"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM3B\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM3B\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM3B\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM4A"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM4A\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM4A\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM4A\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\TARAWASkirmKM4B"

	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM4B\KUWAIT.BIN"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM4B\KUWAIT.SID"
	File "${EE_MAPS_DIR}\common\maps\map9\TARAWASkirmKM4B\KUWAIT.SKR"

	SetOutPath "$INSTDIR\common\maps\map9\terrain"

	File "${EE_MAPS_DIR}\common\maps\map9\terrain\2dmapcol.psd"
	File "${EE_MAPS_DIR}\common\maps\map9\terrain\default.rgb"
	File "${EE_MAPS_DIR}\common\maps\map9\terrain\default.sec"
	File "${EE_MAPS_DIR}\common\maps\map9\terrain\terrain.ffp"
	File "${EE_MAPS_DIR}\common\maps\map9\terrain\terrain.sim"
	File "${EE_MAPS_DIR}\common\maps\map9\terrain\tree_pos.dat"
	File "${EE_MAPS_DIR}\common\maps\map9\terrain\tree_pos.sec"

SectionEnd

;--------------------------------
;Descriptions

	;Language strings
	LangString DESC_SectionMaps ${LANG_ENGLISH} "Install EECH ${VERSION} maps"

	;Assign language strings to sections
	!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${SectionMaps} $(DESC_SectionMaps)
	!insertmacro MUI_FUNCTION_DESCRIPTION_END
;--------------------------------
