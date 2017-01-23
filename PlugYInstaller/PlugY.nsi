;	File created by Yohann NICOLAS.
;	Modified by L'Autour.
!include "MUI2.nsh"

!define VERSION "11.01"
!define D2FILES "."
!define NAME "PlugY, The Survival Kit"
!define MOD_DIR "Mod PlugY"
!define REGKEY "SOFTWARE\${NAME}"
!define UNINSTALL_FILE "PlugY Uninstaller.exe"

!define MUI_COMPONENTSPAGE_SMALLDESC
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

Name "${NAME} v${VERSION}"
OutFile "PlugY_The_Survival_Kit_v${VERSION}.exe"
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
!insertmacro MUI_LANGUAGE "Russian"

LangString DESC_CORE ${LANG_ENGLISH} "Core files.$\nPlugY.dll will be installed in Diablo II directory."
LangString DESC_CORE ${LANG_FRENCH} "Fichiers nйcessaires.$\nPlugY.dll sera installй dans le rйpertoire de Diablo II."
LangString DESC_CORE ${LANG_RUSSIAN} "Основные файлы.$\nPlugY.dll должен быть установлен в каталог Diablo II."
LangString DESC_DESKTOP_SHORTCUTS ${LANG_ENGLISH} "Add shortcut on Desktop to launch Diablo II with ${NAME}."
LangString DESC_DESKTOP_SHORTCUTS ${LANG_FRENCH} "Ajoute un raccourci pour dйmarrer Diablo II avec ${NAME}."
LangString DESC_DESKTOP_SHORTCUTS ${LANG_RUSSIAN} "Добавить ярлык на рабочий стол для запуска Diablo II с ${NAME}."
LangString DESC_MENU_SHORTCUTS ${LANG_ENGLISH} "Add shortcuts in start menu."
LangString DESC_MENU_SHORTCUTS ${LANG_FRENCH} "Ajoute des raccourcis dans le menu dйmarrer."
LangString DESC_MENU_SHORTCUTS ${LANG_RUSSIAN} "Добавить ярлыки в главное меню."
LangString DESC_UNINSTALLER ${LANG_ENGLISH} "Create a Windows uninstall program.$\nAdding registry keys in Windows."
LangString DESC_UNINSTALLER ${LANG_FRENCH} "Crйe un programme Windows de dйsinstallation.$\nAjoute des clйs de registres dans Windows."
LangString DESC_UNINSTALLER ${LANG_RUSSIAN} "Создать в Windows деинстллятор программы.$\nДобавляет ключи реестра в Windows."
LangString DESC_PATCH_D2GFX ${LANG_ENGLISH} "D2gfx.dll patcher to run PlugY without PlugY.exe. Before use it, you MUST read the readme."
LangString DESC_PATCH_D2GFX ${LANG_FRENCH} "D2gfx.dll patcheur pour lancer PlugY sans PlugY.exe. Avant de l'utiliser, vous DEVEZ lire le LISEZ-MOI."
LangString DESC_PATCH_D2GFX ${LANG_RUSSIAN} "Применить патч к D2gfx.dll для запуска PlugY без PlugY.exe. Подробнее смотреть в файле Readme."
LangString SECTION_NAME_CORE ${LANG_ENGLISH} "${NAME} (required)"
LangString SECTION_NAME_CORE ${LANG_FRENCH} "${NAME} (nйcessaire)"
LangString SECTION_NAME_CORE ${LANG_RUSSIAN} "${NAME} (требуется)"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_ENGLISH} "Desktop Shortcut"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_FRENCH} "Raccourci sur le bureau"
LangString SECTION_NAME_DESKTOP_SHORTCUT ${LANG_RUSSIAN} "Ярлык на рабочем столе"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_ENGLISH} "Start menu Shortcuts"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_FRENCH} "Raccourcis dans le Menu dйmarrer"
LangString SECTION_NAME_STARTMENU_SHORTCUTS ${LANG_RUSSIAN} "Ярлыки в в главном меню"
LangString SECTION_NAME_UNINSTALLER ${LANG_ENGLISH} "Uninstaller (add keys registers)"
LangString SECTION_NAME_UNINSTALLER ${LANG_FRENCH} "Dй-installeur (ajoute clйs de registre)"
LangString SECTION_NAME_UNINSTALLER ${LANG_RUSSIAN} "Деинсталлятор (добавляет ключи реестра)"
LangString SECTION_PATCH_D2GFX ${LANG_ENGLISH} "D2gfx.dll Patcher (advanced user only)"
LangString SECTION_PATCH_D2GFX ${LANG_FRENCH} "Patcheur de D2gfx.dll (utilisateur avancй uniquement)"
LangString SECTION_PATCH_D2GFX ${LANG_RUSSIAN} "Патч для D2gfx.dll Patcher (для опытных пользователей)"

LangString README_FILENAME ${LANG_ENGLISH} "PlugY_The_Survival_Kit_-_Readme.txt"
LangString README_FILENAME ${LANG_FRENCH} "PlugY_The_Survival_Kit_-_LisezMoi.txt"
LangString README_FILENAME ${LANG_RUSSIAN} "PlugY_The_Survival_Kit_-_Readme.txt"

LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_ENGLISH} "Error : Diablo II install directory not found.$\nPlease re-install your copy of Diablo II - Lord of Destruction."
LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_FRENCH} "Erreur : Le rйpertoire d'installation de Diablo II n'a pas йtй trouvй.$\nVeuillez rй-installer votre copie de Diablo II - Lord of Destruction."
LangString ERROR_NO_D2_DIRECTORY_FOUND ${LANG_RUSSIAN} "Ошибка : каталог с установленной игрой Diablo II не найден.$\nПожалуйста переустановите вашу копию Diablo II - Lord of Destruction."

Var D2Path
;--------------------------------
; Initialisation
Function .onInit
  !define MUI_LANGDLL_WINDOWTITLE "${NAME} v${VERSION}"
  !define MUI_LANGDLL_INFO "Select your language:$\nChoisissez votre langue:"
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

;--------------------------------
; Custom Page
;Function OptionsPage
  ;StrCpy $INSTDIR "C:\temp\${NAME}"
;	nsDialogs::Create /NOUNLOAD 1018
	;Pop $D2Path

	;GetFunctionAddress $D2Path OnBack
	;nsDialogs::OnBack /NOUNLOAD $D2Path

	;${NSD_CreateButton} 0 0 100% 12u Test
	;Pop $BUTTON
	;GetFunctionAddress $D2Path OnClick
	;nsDialogs::OnClick /NOUNLOAD $BUTTON $D2Path

	;${NSD_CreateText} 0 35 100% 12u hello
	;Pop $EDIT
	;GetFunctionAddress $D2Path OnChange
	;nsDialogs::OnChange /NOUNLOAD $EDIT $D2Path

	;${NSD_CreateCheckbox} 0 -50 100% 8u Test
	;Pop $CHECKBOX
	;GetFunctionAddress $D2Path OnCheckbox
	;nsDialogs::OnClick /NOUNLOAD $CHECKBOX $D2Path

	;${NSD_CreateLabel} 0 40u 75% 40u "* Type `hello there` above.$\n* Click the button.$\n* Check the checkbox.$\n* Hit the Back button."
	;Pop $D2Path

;	nsDialogs::Show
;FunctionEnd


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
  setOutPath "$D2Path\PlugY"
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

Section $(SECTION_PATCH_D2GFX) PatchD2gfx
  SetOutPath $D2Path
  File "${D2FILES}\PatchD2gfxDll.exe"
  File "${D2FILES}\RestoreD2gfxDll.exe"
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
  Delete "$D2Path\PatchD2gfxDll.exe"
  Delete "$D2Path\RestoreD2gfxDll.exe"
  Delete "$INSTDIR\PlugY.exe"
  Delete "$INSTDIR\PlugY.log"
  Delete "$INSTDIR\BnetLog.txt"
  Delete "$INSTDIR\PlugY.ini"
  Delete "$INSTDIR\PlugY_The_Survival_Kit_-_Readme.txt"
  Delete "$INSTDIR\PlugY_The_Survival_Kit_-_LisezMoi.txt"
  Delete "$INSTDIR\PlugY_The_Survival_Kit_-_Liesmich.txt"
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
  !insertmacro MUI_DESCRIPTION_TEXT "${PatchD2gfx}" $(DESC_PATCH_D2GFX)
  !insertmacro MUI_DESCRIPTION_TEXT "${Uninstaller}" $(DESC_UNINSTALLER)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

###########################################################################################################
