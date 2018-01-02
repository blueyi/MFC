; Inno Setup script for CD-DA X-Tractor: minimum install
; 

[Setup]
;Bits=32
Compression=bzip/9
;AlwaysCreateUninstallIcon=1
AppCopyright=Copyright © 1999-2003, Jay A. Key
AppName=CD-DA X-Tractor
AppVerName=CD-DA X-Tractor v0.24
AppVersion=0.24
AppPublisherURL=http://xtractor.sourceforge.net/
CreateAppDir=1
DefaultDirName={pf}\CD-DA X-Tractor
DefaultGroupName=CD-DA X-Tractor
;DisableDirExistsWarning=1
LicenseFile=copying-2.0
MinVersion=4,4
;OverwriteUninstRegEntries=0
WizardImageFile=about.bmp

[Dirs]
Name: "{app}\htmlhelp"
Name: "{app}\output"

[Files]
Source: "akrip32.dll"; DestDir: "{app}"
Source: "vorb_enc.dll"; DestDir: "{app}"
Source: "xtenc.dll"; DestDir: "{app}"
Source: "Copying-2.0"; DestDir: "{app}"
Source: "xtractor.exe"; DestDir: "{app}"
Source: "altrip3.ico"; DestDir: "{app}"
Source: "lame_enc.dll"; DestDir: "{app}"
Source: "cdcache.dll"; DestDir: "{app}"
Source: "xtrctl32.dll"; DestDir: "{app}"
Source: "readme.txt"; DestDir: "{app}"; Flags: isreadme
Source: "xtractor.chm"; DestDir: "{app}\htmlhelp"

[InstallDelete]
Type: files; Name: "{app}\help\cdoptions.html"
Type: files; Name: "{app}\help\cddboptions.html"
Type: files; Name: "{app}\help\faq.html"
Type: files; Name: "{app}\help\features.html"
Type: files; Name: "{app}\help\id3.html"
Type: files; Name: "{app}\help\index.html"
Type: files; Name: "{app}\help\intro.html"
Type: files; Name: "{app}\help\license.html"
Type: files; Name: "{app}\help\menuitems.html"
Type: files; Name: "{app}\help\mp3options.html"
Type: files; Name: "{app}\help\outputoptions.html"
Type: files; Name: "{app}\help\quickstart.html"
Type: files; Name: "{app}\help\toc.html"
Type: files; Name: "{app}\help\toolbar.html"
Type: files; Name: "{app}\help\ripsegment.html"
Type: files; Name: "{app}\help\credits.html"
Type: files; Name: "{app}\help\fullscreen.png"
Type: files; Name: "{app}\help\cddb-options.png"
Type: files; Name: "{app}\help\cd-options.png"
Type: files; Name: "{app}\help\id3.png"
Type: files; Name: "{app}\help\mp3-options.png"
Type: files; Name: "{app}\help\output-options.png"
Type: files; Name: "{app}\help\ripsegment.png"
Type: files; Name: "{app}\help\ripsegment2.png"
Type: files; Name: "{app}\help\toolbar.png"
Type: files; Name: "{app}\help\refresh.png"
Type: files; Name: "{app}\help\rip.png"
Type: files; Name: "{app}\help\options.png"
Type: files; Name: "{app}\help\id3button.png"
Type: files; Name: "{app}\help\copying-vorbis"
Type: dirifempty; Name: "{app}\help"


[Icons]
Name: "{group}\CD-DA X-Tractor"; Filename: "{app}\xtractor.exe"; WorkingDir: "{app}"; IconFilename: "{app}\altrip3.ico"
Name: "{group}\Help"; Filename: "{app}\htmlhelp\xtractor.chm"; WorkingDir: "{app}\htmlhelp"
Name: "{group}\Browse Output Folder"; Filename: "{app}\Output"; WorkingDir: "{app}\Output"

[UninstallDelete]
Type: files; Name: "{app}\toc.dat"
Type: files; Name: "{app}\cdparms.dat"
Type: files; Name: "{app}\inquiry.dat"
Type: files; Name: "{app}\retbuf.txt"

[Registry]
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; Flags: uninsdeletekey
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: string; ValueName: "mp3OutputDir"; ValueData: "{app}\output";
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: string; ValueName: "wavOutputDir"; ValueData: "{app}\output";
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "autoCheck"; ValueData: 1; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "autoTOC"; ValueData: 0; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "bitrate"; ValueData: 192; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "id3level"; ValueData: 1; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "jitterCheck"; ValueData: 1; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "numRip"; ValueData: 26; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "overlap"; ValueData: 3; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: dword; ValueName: "readMode"; ValueData: 2; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: string; ValueName: "cddbaddr"; ValueData: "cddb.cddb.com"; Flags: createvalueifdoesntexist
Root: HKLM; Subkey: "SOFTWARE\AKSoft\X-Tractor"; ValueType: string; ValueName: "cddbcgi"; ValueData: "/~cddb/cddb.cgi"; Flags: createvalueifdoesntexist

