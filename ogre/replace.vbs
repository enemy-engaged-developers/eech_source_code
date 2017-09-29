Set regObj = GetObject( _
	"winmgmts:{impersonationLevel=impersonate}!\\" & _
	".\root\default:StdRegProv")
 
regObj.GetStringValue &H80000002, "Software\\Razorworks\\Comanche Hokum", "Installation Path", dir
dir = dir & "\cohokum\"

Set objFSO = CreateObject("Scripting.FileSystemObject")

Set objFile = objFSO.OpenTextFile(Wscript.Arguments(0) & "\" & Wscript.Arguments(1), 1)
strText = objFile.ReadAll
objFile.Close

strNewText = Replace(strText, Wscript.Arguments(2), Wscript.Arguments(3))

file = dir & Wscript.Arguments(1)
Set objFile = objFSO.CreateTextFile(dir & Wscript.Arguments(1))
objFile.Write strNewText
objFile.Close
