;	File created by Yohann NICOLAS.
Unicode True

!include "MUI2.nsh"

!define VERSION "v14.01"
!define D2FILES "."
!define NAME "PlugY, The Survival Kit"
!define MOD_DIR "Mod PlugY"
!define REGKEY "SOFTWARE\${NAME}"
!define UNINSTALL_FILE "PlugY Uninstaller.exe"

!define MUI_COMPONENTSPAGE_SMALLDESC
!define MUI_ICON "..\PlugYRun\PlugY.ico"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "PlugYInstallerHeader.bmp"
!define MUI_LANGDLL_REGISTRY_ROOT HKLM
!define MUI_LANGDLL_REGISTRY_KEY "SOFTWARE\${NAME}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "Install Language"
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_UNFINISHPAGE_NOAUTOCLOSE
!define MUI_FINISHPAGE_SHOWREADME "$(README_FILENAME)"
!define MUI_FINISHPAGE_RUN ;"PlugY.exe"
!define MUI_FINISHPAGE_RUN_FUNCTION "LaunchPlugY"
!define MUI_FINISHPAGE_RUN_NOTCHECKED
!define MUI_FINISHPAGE_NOREBOOTSUPPORT
!define MUI_ABORTWARNING
;!define MUI_UNABORTWARNING

Name "${NAME} ${VERSION}"
OutFile "PlugY_The_Survival_Kit_${VERSION}_Installer.exe"
InstallDirRegKey HKLM "${REGKEY}" "InstallPath"

;--------------------------------
; Pages
;!insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
!insertmacro MUI_PAGE_COMPONENTS
;Page Custom OptionsPage
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH


;--------------------------------
; Languages
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "TradChinese"

LangString DESC_CORE ${LANG_ENGLISH} "Core files.$\nPlugY.dll will be installed in Diablo II directory."
LangString DESC_CORE ${LANG_FRENCH} "Fichiers nécessaires.$\nPlugY.dll sera installé dans le répertoire de Diablo II."
LangString DESC_CORE ${LANG_GERMAN} "Hauptdateien.$\nPlugY.dll wird in das Installationsverzeichnis von Diablo II installiert."
LangString DESC_CORE ${LANG_RUSSIAN} "Основные файлы.$\nPlugY.dll должен быть установлен в каталог Diablo II."
LangString DESC_CORE ${LANG_TRADCHINESE} "核心檔案。$\nPlugY.dll 將被安裝於 Diablo II 目錄。"
LangString DESC_DESKTOP_SHORTCUTS ${LANG_ENGLISH} "Add shortcut on Desktop to launch Diablo II with ${NAME}."
LangString DESC_DESKTOP_SHORTCUTS ${LANG_FRENCH} "Ajoute un raccourci pour démarrer Diablo II avec ${NAME}."
LangString DESC_DESKTOP_SHORTCUTS ${LANG_GERMAN} "Fügt eine Verknüpfung auf dem Desktop mit dem Namen ${NAME} hinzu mit der Diablo II gestartet werden kann."
LangString DESC_DESKTOP_SHORTCUTS ${LANG_RUSSIAN} "Добавить ярлык на рабочий стол для запуска Diablo II с ${NAME}."
LangString DESC_DESKTOP_SHORTCUTS ${LANG_TRADCHINESE} "在桌面新增捷徑以藉由 ${NAME} 執行 Diablo II。"
LangString DESC_MENU_SHORTCUTS ${LANG_ENGLISH} "Add shortcuts in start menu."
LangString DESC_MENU_SHORTCUTS ${LANG_FRENCH} "Ajoute des raccourcis dans le menu démarrer."
LangString DESC_MENU_SHORTCUTS ${LANG_GERMAN} "Fügt Verknüpfungen im Startmenü hinzu."
LangString DESC_MENU_SHORTCUTS ${LANG_RUSSIAN} "Добавить ярлыки в главное меню."
LangString DESC_MENU_SHORTCUTS ${LANG_TRADCHINESE} "新增「開始」功能表捷徑"
LangString DESC_UNINSTALLER ${LANG_ENGLISH} "Create a Windows uninstall program.$\nAdding registry keys in Windows."
LangString DESC_UNINSTALLER ${LANG_FRENCH} "Crée un programme Windows de désinstallation.$\nAjoute des clés de registres dans Windows."
LangString DESC_UNINSTALLER ${LANG_GERMAN} "Erzeugt ein Deinstallationsprogramm.$\nWindows Registrierungseinträge werden erstellt."
LangString DESC_UNINSTALLER ${LANG_RUSSIAN} "Создать в Windows деинстллятор программы.$\nДобавляет ключи реестра в Windows."
LangString DESC_UNINSTALLER ${LANG_TRADCHINESE} "建立 Windows 解除安裝程式。$\n加入 Windows 登錄訊息。"
LangString DESC_PATCH_FILE ${LANG_ENGLISH} "Patcher to run PlugY without PlugY.exe. Before use it, you MUST read the readme."
LangString DESC_PATCH_FILE ${LANG_FRENCH} "Patcheur pour lancer PlugY sans PlugY.exe. Avant de l'utiliser, vous DEVEZ lire le LISEZ-MOI."
LangString DESC_PATCH_FILE ${LANG_GERMAN} "Patcher um PlugY ohne PlugY.exe zu starten.$\nDie LiesMich-Datei MUSS vor Benutzung gelesen werden."
LangString DESC_PATCH_FILE ${LANG_RUSSIAN} "Применить патч для запуска PlugY без PlugY.exe. Подробнее смотреть в файле Readme."
LangString DESC_PATCH_FILE ${LANG_TRADCHINESE} "更改遊戲檔案以不藉由 PlugY.exe 而執行 PlugY。使用前，您「必須」閱讀「讀我檔案」。"
LangString SECTION_NAME_CORE ${LANG_ENGLISH} "${NAME} (required)"
LangString SECTION_NAME_CORE ${LANG_FRENCH} "${NAME} (nécessaire)"
LangString SECTION_NAME_CORE ${LANG_GERMAN} "${NAME} (benötigt)"
LangString SECTION_NAME_CORE ${LANG_RUSSIAN} "${NAME} (требуется)"
LangString SECTION_NAME_CORE ${LANG_TRADCHINESE} "${NAME} (必要)"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_ENGLISH} "Desktop Shortcut"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_FRENCH} "Raccourci sur le bureau"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_GERMAN} "Desktopverknüpfung"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_RUSSIAN} "Ярлык на рабочем столе"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_TRADCHINESE} "桌面捷徑"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_ENGLISH} "Start menu Shortcuts"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_FRENCH} "Raccourcis dans le Menu démarrer"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_GERMAN} "Startmenüverknüpfungen"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_RUSSIAN} "Ярлыки в в главном меню"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_TRADCHINESE} "「開始」功能表捷徑"
LangString SECTION_NAME_UNINSTALLER ${LANG_ENGLISH} "Uninstaller (add keys registers)"
LangString SECTION_NAME_UNINSTALLER ${LANG_FRENCH} "Dé-installeur (ajoute clés de registre)"
LangString SECTION_NAME_UNINSTALLER ${LANG_GERMAN} "Deinstallationsprogramm (Fügt Windows Registrierungseinträge hinzu)"
LangString SECTION_NAME_UNINSTALLER ${LANG_RUSSIAN}  "Деинсталлятор (добавляет ключи реестра)"
LangString SECTION_NAME_UNINSTALLER ${LANG_TRADCHINESE} "移除工具 (加入登錄訊息)"
LangString SECTION_PATCH_FILE ${LANG_ENGLISH} "File Patcher (advanced user only)"
LangString SECTION_PATCH_FILE ${LANG_FRENCH} "Patcheur de fichier (utilisateur avancé uniquement)"
LangString SECTION_PATCH_FILE ${LANG_GERMAN} "Datei Patcher (Für erfahrene Nutzer)"
LangString SECTION_PATCH_FILE ${LANG_RUSSIAN} "Патч для Patcher (для опытных пользователей)"
LangString SECTION_PATCH_FILE ${LANG_TRADCHINESE} "檔案級補釘 (限高級用戶)"

LangString README_FILENAME ${LANG_ENGLISH} "PlugY_The_Survival_Kit_-_Readme.txt"
LangString README_FILENAME ${LANG_FRENCH} "PlugY_The_Survival_Kit_-_LisezMoi.txt"
LangString README_FILENAME ${LANG_GERMAN} "PlugY_The_Survival_Kit_-_Liesmich.txt"
LangString README_FILENAME ${LANG_RUSSIAN} "PlugY_The_Survival_Kit_-_Readme.txt"
LangString README_FILENAME ${LANG_TRADCHINESE} "PlugY_The_Survival_Kit_-_讀我檔案"

LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_ENGLISH} "Error : Diablo II install directory not found.$\nPlease re-install your copy of Diablo II - Lord of Destruction."
LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_FRENCH} "Erreur : Le répertoire d'installation de Diablo II n'a pas été trouvé.$\nVeuillez ré-installer votre copie de Diablo II - Lord of Destruction."
LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_GERMAN} "Fehler : Diablo II Installationsverzeichnis nicht gefunden.$\nBitte installiere Diablo II - Lord of Destruction neu."
LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_RUSSIAN} "Ошибка : каталог с установленной игрой Diablo II не найден.$\nПожалуйста переустановите вашу копию Diablo II - Lord of Destruction."
LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_TRADCHINESE} "錯誤: 找不到 Diablo II 安裝目錄$\n請重新安裝「暗黑破壞神II：毀滅之王」"

Var D2Path
;--------------------------------
; Initialisation
Function .onInit
  !define MUI_LANGDLL_WINDOWTITLE "${NAME} ${VERSION}"
  !define MUI_LANGDLL_INFO "Select your language:"
  !insertmacro MUI_LANGDLL_DISPLAY
  !undef MUI_LANGDLL_WINDOWTITLE
  !undef MUI_LANGDLL_INFO
  ReadRegStr $D2Path HKLM "SOFTWARE\Blizzard Entertainment\Diablo II" "InstallPath"
  ${If} $D2Path == ""
    ReadRegStr $D2Path HKCU "SOFTWARE\Blizzard Entertainment\Diablo II" "InstallPath"
    ${If} $D2Path == ""
      MessageBox MB_OK $(ERROR_NO_D2_DIRECTORY_FOUND)
      Abort
    ${EndIf}
  ${EndIf}

  ${If} $INSTDIR == ""
    StrLen $0 $D2Path
    IntOp $0 $0 - 1
    StrCpy $0 $D2Path 1 $0
    ${if} $0 == "\"
      StrCpy $INSTDIR "$D2Path${MOD_DIR}\"
    ${else}
      StrCpy $INSTDIR "$D2Path\${MOD_DIR}\"
    ${endif}
  ${EndIf}
FunctionEnd

Function Un.onInit
  !insertmacro MUI_UNGETLANGUAGE
  ReadRegStr $D2Path HKLM "${REGKEY}" "PlugYDllPath"
FunctionEnd

Function LaunchPlugY
	SetOutPath "$INSTDIR"
	ExecShell "" "$INSTDIR\PlugY.exe"
FunctionEnd

InstType "Standard"
InstType "Minimal"

Section "!$(SECTION_NAME_CORE)" Core
  SectionIn 1 2 RO
  SetOutPath $D2Path
  File "${D2FILES}\PlugY.dll"
  SetOutPath $INSTDIR
  File "${D2FILES}\PlugY.exe"
  File "${D2FILES}\PlugY.ini"
  File "${D2FILES}\PlugY_The_Survival_Kit_-_Readme.txt"
  File "${D2FILES}\PlugY_The_Survival_Kit_-_LisezMoi.txt"
  File "${D2FILES}\PlugY_The_Survival_Kit_-_Liesmich.txt"
  File "${D2FILES}\PlugY_The_Survival_Kit_-_讀我檔案.txt"
  setOutPath "$INSTDIR\PlugY"
  File "${D2FILES}\PlugY\EmptyPage.dc6"
  File "${D2FILES}\PlugY\PlugYDefault.ini"
  File "${D2FILES}\PlugY\PlugYFixed.ini"
  File "${D2FILES}\PlugY\LocalizedStrings.ini"
  File "${D2FILES}\PlugY\SharedGoldBtns.dc6"
  File "${D2FILES}\PlugY\StashBtns.dc6"
  File "${D2FILES}\PlugY\StatsBackground.dc6"
  File "${D2FILES}\PlugY\statsinterface.txt"
  File "${D2FILES}\PlugY\TradeStash.dc6"
  File "${D2FILES}\PlugY\UnassignSkillsBtns.dc6"
  File "${D2FILES}\PlugY\UnassignStatsBtns.dc6"
SectionEnd

Section "$(SECTION_NAME_DESKTOP_SHORTCUT)" DesktopShortcuts
  SectionIn 1
  SetOutPath $INSTDIR
  CreateShortCut "$DESKTOP\${NAME}.lnk" "$INSTDIR\PlugY.exe" "" "$INSTDIR\PlugY.exe" 0
SectionEnd

Section $(SECTION_NAME_STARTMENU_SHORTCUTS) MenuShortcuts
  SectionIn 1
  CreateDirectory "$SMPROGRAMS\${NAME}"
  SetOutPath $INSTDIR
  CreateShortCut "$SMPROGRAMS\${NAME}\Uninstall.lnk" "$INSTDIR\${UNINSTALL_FILE}" "" "$INSTDIR\${UNINSTALL_FILE}" 0
  CreateShortCut "$SMPROGRAMS\${NAME}\${NAME}.lnk" "$INSTDIR\PlugY.exe" "" "$INSTDIR\PlugY.exe" 0
SectionEnd

Section $(SECTION_NAME_UNINSTALLER) Uninstaller
  SectionIn 1

  ; Create uninstaller
  setOutPath "$INSTDIR"
  WriteUninstaller "${UNINSTALL_FILE}"

  ; Write the installation path into the registry
  WriteRegStr HKLM "${REGKEY}" "InstallPath" $INSTDIR
  WriteRegStr HKLM "${REGKEY}" "PlugYDllPath" "$D2Path"

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "InstallLocation" "$$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "DisplayName" "${NAME}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "HelpLink" "http://plugy.free.fr"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "DisplayVersion" "${VERSION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "UninstallString" '"$INSTDIR\${UNINSTALL_FILE}"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "NoRepair" 1
SectionEnd

Section $(SECTION_PATCH_FILE) PatchFile
  SetOutPath $D2Path
  File "${D2FILES}\PatchD2File.exe"
  File "${D2FILES}\RestoreD2File.exe"
SectionEnd

;--------------------------------
; Uninstall
Section "Uninstall" Uninstall
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}"
  DeleteRegKey HKLM "${REGKEY}"

  ; Remove shortcuts, if any
  Delete "$DESKTOP\${NAME}.lnk"
  Delete "$SMPROGRAMS\${NAME}\*.*"
  RMDir "$SMPROGRAMS\${NAME}"

  ; Remove files and uninstaller
  Delete "$D2Path\PlugY.dll"
  Delete "$D2Path\PatchD2File.exe"
  Delete "$D2Path\RestoreD2File.exe"
  Delete "$INSTDIR\PlugY.exe"
  Delete "$INSTDIR\PlugY.log"
  Delete "$INSTDIR\BnetLog.txt"
  Delete "$INSTDIR\PlugY.ini"
  Delete "$INSTDIR\PlugY_The_Survival_Kit_-_Readme.txt"
  Delete "$INSTDIR\PlugY_The_Survival_Kit_-_LisezMoi.txt"
  Delete "$INSTDIR\PlugY_The_Survival_Kit_-_Liesmich.txt"
  Delete "$INSTDIR\PlugY_The_Survival_Kit_-_讀我檔案.txt"
  Delete "$D2Path\PlugY\EmptyPage.dc6"
  Delete "$D2Path\PlugY\PlugYDefault.ini"
  Delete "$D2Path\PlugY\PlugYFixed.ini"
  Delete "$D2Path\PlugY\LocalizedStrings.ini"
  Delete "$D2Path\PlugY\SharedGoldBtns.dc6"
  Delete "$D2Path\PlugY\StashBtns.dc6"
  Delete "$D2Path\PlugY\StatsBackground.dc6"
  Delete "$D2Path\PlugY\statsinterface.txt"
  Delete "$D2Path\PlugY\TradeStash.dc6"
  Delete "$D2Path\PlugY\UnassignSkillsBtns.dc6"
  Delete "$D2Path\PlugY\UnassignStatsBtns.dc6"
  RMDir "$D2Path\PlugY"
  Delete "$INSTDIR\${UNINSTALL_FILE}"
  RMDir "$INSTDIR"
SectionEnd

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT "${Core}" $(DESC_CORE)
  !insertmacro MUI_DESCRIPTION_TEXT "${DesktopShortcuts}" $(DESC_DESKTOP_SHORTCUTS)
  !insertmacro MUI_DESCRIPTION_TEXT "${MenuShortcuts}" $(DESC_MENU_SHORTCUTS)
  !insertmacro MUI_DESCRIPTION_TEXT "${PatchFile}" $(DESC_PATCH_FILE)
  !insertmacro MUI_DESCRIPTION_TEXT "${Uninstaller}" $(DESC_UNINSTALLER)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

###########################################################################################################
