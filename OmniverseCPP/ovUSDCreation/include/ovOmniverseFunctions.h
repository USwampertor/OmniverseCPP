/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	ovOmniverseFunctions.h
 * @author 	Marco "Swampy" Millan
 * @date 	2022/03/02
 * @brief 	This file contains the code in a way so it is not cluttered on main
 *          Functions will have their description and what they do on
 *          the inside
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/

#pragma once

#include "ovPrerequisites.h"


// While I do not personally like global variables, we will create ones for the example
// So things can be easy to understand
static bool           g_doLiveEdit = true;
static bool           g_omniverseLogEnabled = true;
static String         g_error;
static UsdStageRefPtr g_stage;
Mutex                 g_LogMutex;

/*
 *	@brief  The callback called by Omniverse when creating a connection with
 *          Nucleus
 *	@param  void* userData the information as a raw pointer
 *	@param  const char* url the URL of omniverse to create the stage
 *	@param  OmniClientConnectionStatus status the status of the callback
 *	@return -
 */
static void
omniClientCallback(void* userData, 
                   const char* url, 
                   OmniClientConnectionStatus status) noexcept {
  // Let's just print this regardless
  {
    UniqueLock<Mutex> lk(g_LogMutex);

    cout << String("Connection Status: ") 
         << omniClientGetConnectionStatusString(status) 
         << " [" << url << "]" << endl;
  }
  if (status == eOmniClientConnectionStatus_ConnectError) {
    // We shouldn't just exit here - we should clean up a bit, but we're going to do it anyway
    String error("[ERROR] Failed connection, exiting.");
    
    cout << error << endl;
    // throw Exception(error.c_str());
  }
}

static void
failNotify(const char* msg, const char* detail = nullptr, ...) {
  UniqueLock<Mutex> lk(g_LogMutex);

  fprintf(stderr, "%s\n", msg);
  if (detail != nullptr) {
    fprintf(stderr, "%s\n", detail);
  }
}

// Omniverse Log callback
static void logCallback(const char* threadName, 
                        const char* component, 
                        OmniClientLogLevel level, 
                        const char* message) noexcept {
  UniqueLock<Mutex> lk(g_LogMutex);
  if (g_omniverseLogEnabled) {
    puts(message);
    g_error = message;
  }
}

bool
initialize(bool doLiveEdit) {

  // Register a function to be called whenever the library wants to print something to a log
  omniClientSetLogCallback(logCallback);

  // The default log level is "Info", set it to "Debug" to see all messages
  omniClientSetLogLevel(eOmniClientLogLevel_Debug);

  // Initialize the library and pass it the version constant defined in OmniClient.h
  // This allows the library to verify it was built with a compatible version. It will
  // return false if there is a version mismatch.
  if (!omniClientInitialize(kOmniClientVersion)) {
    return false;
  }

  omniClientRegisterConnectionStatusCallback(nullptr, omniClientCallback);

  // Enable live updates
  omniUsdLiveSetDefaultEnabled(doLiveEdit);

  return true;
}

void
shutdown() {
  // Calling this prior to shutdown ensures that all pending live updates complete.
  omniUsdLiveWaitForPendingUpdates();

  // The stage is a sophisticated object that needs to be destroyed properly.  
  // Since gStage is a smart pointer we can just reset it
  g_stage.Reset();

  //omniClientTick(1000);
  omniClientShutdown();
}

bool
startConnection() {
  return true;
}

bool
endConnection() {
  return true;
}

String
createStage(const String& url, const String& stageName = "Sample.usd") {
  String stageUrl = url + stageName;

  // Delete the old version of this file on Omniverse and wait for the operation to complete
  {
    UniqueLock<Mutex> lk(g_LogMutex);
    cout << "Waiting for " << stageUrl << " to delete... " << endl;
  }
  omniClientWait(omniClientDelete(stageUrl.c_str(), nullptr, nullptr));
  {
    UniqueLock<Mutex> lk(g_LogMutex);
    cout << "finished" << endl;
  }

  // Create this file in Omniverse cleanly
  g_stage = UsdStage::CreateNew(stageUrl);
  if (!g_stage)
  {
    failNotify("Failure to create model in Omniverse", stageUrl.c_str());
    return String();
  }

  {
    UniqueLock<Mutex> lk(g_LogMutex);
    cout << "New stage created: " << stageUrl << endl;
  }

  // Always a good idea to declare your up-ness
  UsdGeomSetStageUpAxis(g_stage, UsdGeomTokens->y);

  return stageUrl;
}

void
checkpointFile(const String& url, const String& comment) {
  if (omniUsdLiveGetDefaultEnabled()) {
    return;
  }

  bool bCheckpointsSupported = false;
  omniClientWait(omniClientGetServerInfo(url.c_str(), &bCheckpointsSupported,
    [](void* UserData, OmniClientResult Result, OmniClientServerInfo const* Info) noexcept
    {
      if (Result == eOmniClientResult_Ok && Info && UserData)
      {
        bool* bCheckpointsSupported = static_cast<bool*>(UserData);
        *bCheckpointsSupported = Info->checkpointsEnabled;
      }
    }));

  if (bCheckpointsSupported)
  {
    const bool bForceCheckpoint = true;
    omniClientWait(omniClientCreateCheckpoint(url.c_str(), comment.c_str(), bForceCheckpoint, nullptr,
      [](void* userData, OmniClientResult result, char const* checkpointQuery) noexcept
      {}));

    UniqueLock<Mutex> lk(g_LogMutex);
    cout << "Adding checkpoint comment <" << comment << "> to stage <" << url << ">" << endl;
  }
}

String
getUserName(const String& url) {
  // Get the username for the connection
  String userName("_none_");
  omniClientWait(omniClientGetServerInfo(url.c_str(), &userName, [](void* userData, OmniClientResult result, struct OmniClientServerInfo const* info) noexcept
    {
      String* userName = static_cast<String*>(userData);
      if (userData && userName && info && info->username)
      {
        userName->assign(info->username);
      }
    }));
  {
    // std::unique_lock<std::mutex> lk(gLogMutex);
    // std::cout << "Connected username: " << userName << std::endl;
  }
  return userName;
}

bool
isValidOmniURL(const String& maybeURL) {
  bool isValidURL = false;
  OmniClientUrl* url = omniClientBreakUrl(maybeURL.c_str());
  if (url->host && url->path &&
    (String(url->scheme) == String("omniverse") ||
      String(url->scheme) == String("omni")))
  {
    isValidURL = true;
  }
  omniClientFreeUrl(url);
  return isValidURL;
}



