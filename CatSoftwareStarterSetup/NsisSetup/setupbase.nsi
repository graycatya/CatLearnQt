Unicode True
!include "LogicLib.nsh"

!define PRODUCT_NAME "CatSoftwareStarter"
!define PRODUCT_VERSION ""
!define PRODUCT_PUBLISHER "CatSoftwareStarter"
!define PRODUCT_DIR_REGKEY ""
!define PRODUCT_UNINST_KEY ""
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"


SetCompressor lzma


!include "MUI.nsh"
!include "x64.nsh"
!include "Winver.nsh"

!define MUI_ABORTWARNING
!define MUI_ICON "Resource\cslogo.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"


!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_DIRECTORY

var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${PRODUCT_NAME}"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN "$INSTDIR\${PRODUCT_NAME}.exe"
!insertmacro MUI_PAGE_FINISH


!insertmacro MUI_UNPAGE_INSTFILES


!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"


!insertmacro MUI_RESERVEFILE_LANGDLL
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS


Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_NAME}Setup.exe"
InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show

Section "${PRODUCT_NAME}" SEC01
    SetOutPath "$INSTDIR"
    SetOverwrite ifnewer
    SectionIn RO
    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME}.exe"
    CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\${PRODUCT_NAME}.exe"

    ; 放置文件
    File /r "${PRODUCT_NAME}\*.*"
  
SectionEnd


Section -AdditionalIcons
  SetOutPath $INSTDIR
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
    WriteUninstaller "$INSTDIR\uninst.exe"
    WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\${PRODUCT_NAME}.exe"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${PRODUCT_NAME}.exe"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
    WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function .onInit
    !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd



Section Uninstall
    !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
    Delete "$INSTDIR\uninst.exe"
    SetOutPath "$INSTDIR"

    Delete "$INSTDIR\*.*"

    SetOutPath "$DESKTOP"

    RMDir /r "$INSTDIR"
    RMDir "$INSTDIR"

    DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
    DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
    SetAutoClose true
SectionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "You do want to remove it completely $(^Name) , And all of its components?" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) It has been successfully removed from your computer."
FunctionEnd