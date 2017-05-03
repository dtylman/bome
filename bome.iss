; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "bome"
#define MyAppVersion "0.2"
#define MyAppExeName "nw.exe"
#define GOPATH GetEnv('GOPATH')

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{ED800776-990D-4121-A747-AEC8716D5098}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
DefaultDirName={pf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile=LICENSE
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\bootstrap\*"; DestDir: "{app}\bootstrap"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\css\*"; DestDir: "{app}\css"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\font-awesome\*"; DestDir: "{app}\font-awesome"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\js\*"; DestDir: "{app}\js"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\locales\*"; DestDir: "{app}\locales"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\app.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\package.json"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\main.js"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#GOPATH}\src\github.com\dtylman\pictures\cmd\app\index.html"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "nwjs-v0.21.5-win-x64\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "bin\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
