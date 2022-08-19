#include <photoshopapi/pica_sp/SPBasic.h>
#include <photoshopapi/pica_sp/SPInterf.h>

#include <photoshopapi/photoshop/PIActionsPlugin.h>
#include <photoshopapi/photoshop/PIActions.h>
#include <samplecode/common/includes/PIUtilities.h>

#include <Windows.h>
#include <string.h>
#include <assert.h>

#include <samplecode/common/sources/DialogUtilitiesWin.cpp>
#include <samplecode/common/sources/PIDLLInstance.cpp>
#include <samplecode/common/sources/PIUSuites.cpp>
#include <samplecode/common/sources/PIUtilities.cpp>
#include <samplecode/common/sources/PIUtilitiesWin.cpp>
#include <samplecode/common/sources/PIWinUI.cpp>

#include "PIUXPSuite.h"

#define WIN32_MAX_CLASS_NAME_LENGTH 256

SPBasicSuite* g_basicSuite = nullptr;
HWND globalPSMainWindowHwnd = nullptr;

// Access the Photoshop window
BOOL CALLBACK getPSMainWindowCB(HWND hwnd, LPARAM lParam)
{
  char windowClassName[WIN32_MAX_CLASS_NAME_LENGTH];
  GetClassNameA(hwnd, (LPSTR)windowClassName, WIN32_MAX_CLASS_NAME_LENGTH);

  if (strncmp(windowClassName, "Photoshop", WIN32_MAX_CLASS_NAME_LENGTH) == 0) {
    globalPSMainWindowHwnd = hwnd;
  }

  return true;
}

// When the plugin uninitializes
SPErr UninitializePlugin() {
  PIUSuitesRelease();
  return kSPNoError;
}

// The main entry for the plugin
DLLExport SPAPI SPErr AutoPluginMain(const char* caller,
  const char* selector,
  void* message)
{
  SPErr status = kSPNoError;

  SPMessageData* basicMessage = (SPMessageData*)message;

  sSPBasic = basicMessage->basic;

  if (sSPBasic->IsEqual(caller, kSPInterfaceCaller)) {
    if (sSPBasic->IsEqual(selector, kSPInterfaceAboutSelector)) {
      DoAbout(basicMessage->self, AboutID);
    }

    if (sSPBasic->IsEqual(selector, kSPInterfaceStartupSelector)) {
      return kSPNoError;
    }

    if (sSPBasic->IsEqual(selector, kSPInterfaceShutdownSelector)) {
      status = UninitializePlugin();
    }
  }

  if (sSPBasic->IsEqual(caller, kPSPhotoshopCaller)) {
    if (sSPBasic->IsEqual(selector, kPSDoIt)) {
      PSActionsPlugInMessage* tmpMsg = (PSActionsPlugInMessage*)message;
      BOOL status = EnumWindows(getPSMainWindowCB, (LPARAM)NULL);
      assert(status != 0);
      MessageBoxA(globalPSMainWindowHwnd, "Hello World!", "Tutorial Dialog", MB_OK | MB_ICONINFORMATION);
    }
  }

  return status;
}
