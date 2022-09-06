#pragma once
// This library allows us to connect to Nucleus
#include <OmniClient.h>

// This library gives us the ability for live synchronization and USD updates
#include <OmniUsdLive.h>

// This libraries help us create USD objects and components
#include <pxr/usd/usd/common.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>

// Standard libraries
#include <cstdio>
#include <string>
#include <iostream>
#include <mutex>
#include <exception>

PXR_NAMESPACE_USING_DIRECTIVE

#define EXPORTABLE __declspec(dllexport)

static bool           g_doLiveEdit = true;
static bool           g_omniverseLogEnabled = false;
static std::string    g_error;
static UsdStageRefPtr g_stage;
std::mutex            g_LogMutex;

static void
omniClientCallback(void* userData,
                   const char* url,
                   OmniClientConnectionStatus status) noexcept {
  // Let's just print this regardless
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);

    std::cout << std::string("Connection Status: ")
              << omniClientGetConnectionStatusString(status)
              << " [" << url << "]" << std::endl;
  }
  if (status == eOmniClientConnectionStatus_ConnectError) {
    std::string error("[ERROR] Failed connection, exiting.");

    std::cout << error << std::endl;
  }
}

static void
copyCallback() {

}

static void
failNotify(const char* msg, const char* detail = nullptr, ...) {
  std::unique_lock<std::mutex> lk(g_LogMutex);

  fprintf(stderr, "%s\n", msg);
  if (detail != nullptr) {
    fprintf(stderr, "%s\n", detail);
  }
}

// Omniverse Log callback
static void 
logCallback(const char* threadName,
            const char* component,
            OmniClientLogLevel level,
            const char* message) noexcept {
  std::unique_lock<std::mutex> lk(g_LogMutex);
  if (g_omniverseLogEnabled) {
    printf(message);
    g_error = message;
  }
}

EXPORTABLE void
setLiveSync(bool doLiveEdit = false) {
  omniUsdLiveSetDefaultEnabled(doLiveEdit);
}

EXPORTABLE void
setModeForURL(const std::string& url, int mode) {
  omniUsdLiveSetModeForUrl(url.c_str(), static_cast<OmniUsdLiveMode>(mode));
}

EXPORTABLE bool
getLiveSync() {
  return omniUsdLiveGetDefaultEnabled();
}

EXPORTABLE int
getModeForURL(const std::string& url) {
  return static_cast<int>(omniUsdLiveGetModeForUrl(url.c_str()));
}

EXPORTABLE void
waitForUpdates() {
  omniUsdLiveWaitForPendingUpdates();
}

EXPORTABLE void
setLogLevel(int logLevel = 2) {
  omniClientSetLogLevel(static_cast<OmniClientLogLevel>(logLevel));
}

EXPORTABLE std::string
getVersionString() {
  return omniClientGetVersionString();
}

EXPORTABLE std::string
getConnectionStatus(int status) {
  return omniClientGetConnectionStatusString(static_cast<OmniClientConnectionStatus>(status));
}

EXPORTABLE std::string
getGlobalError() {
  return g_error;
}

EXPORTABLE bool
initialize(bool doLiveEdit = false, int logLevel = 2) {

  // Register a function to be called whenever the library wants to print something to a log
  omniClientSetLogCallback(logCallback);

  // The default log level is "Info", set it to "Debug" to see all messages
  setLogLevel(logLevel);

  // Initialize the library and pass it the version constant defined in OmniClient.h
  // This allows the library to verify it was built with a compatible version. It will
  // return false if there is a version mismatch.
  if (!omniClientInitialize(kOmniClientVersion)) {
    return false;
  }

  omniClientRegisterConnectionStatusCallback(nullptr, omniClientCallback);

  // Enable live updates
  setLiveSync(doLiveEdit);

  return true;
}

EXPORTABLE void
shutdown() {
  // Calling this prior to shutdown ensures that all pending live updates complete.
  omniUsdLiveWaitForPendingUpdates();

  // The stage is a sophisticated object that needs to be destroyed properly.  
  // Since gStage is a smart pointer we can just reset it
  g_stage.Reset();

  //omniClientTick(1000);
  omniClientShutdown();
}

EXPORTABLE void
deleteStage(const std::string& url, const std::string& stageName = "Scene.usd") {
  std::string stageUrl = url + stageName;

  // Delete the old version of this file on Omniverse and wait for the operation to complete
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "Waiting for " << stageUrl << " to delete... " << std::endl;
  }
  omniClientWait(omniClientDelete(stageUrl.c_str(), nullptr, nullptr));
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "finished" << std::endl;
  }
}

EXPORTABLE std::string
createStage(const std::string& url, const std::string& stageName = "Scene.usd") {
  deleteStage(url, stageName);
  std::string stageUrl = url + stageName;

  // Create this file in Omniverse cleanly
  g_stage = UsdStage::CreateNew(stageUrl);
  if (!g_stage)
  {
    failNotify("Failure to create model in Omniverse", stageUrl.c_str());
    return std::string();
  }

  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "New stage created: " << stageUrl << std::endl;
  }

  // Always a good idea to declare your up-ness
  UsdGeomSetStageUpAxis(g_stage, UsdGeomTokens->y);

  return stageUrl;
}

EXPORTABLE void
checkpointFile(const std::string& url, const std::string& comment) {
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

    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "Adding checkpoint comment <" << comment << "> to stage <" << url << ">" << std::endl;
  }
}

EXPORTABLE std::string
getUsername(const std::string& stageUrl) {
  std::string userName("_none_");
  omniClientWait(omniClientGetServerInfo(stageUrl.c_str(), &userName, [](void* userData, OmniClientResult result, struct OmniClientServerInfo const* info) noexcept
    {
      std::string* userName = static_cast<std::string*>(userData);
      if (userData && userName && info && info->username)
      {
        userName->assign(info->username);
      }
    }));
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "Connected username: " << userName << std::endl;
  }
  return userName;
}

EXPORTABLE bool
isValidOmniURL(const std::string& maybeURL) {
  bool isValidURL = false;
  OmniClientUrl* url = omniClientBreakUrl(maybeURL.c_str());
  if (url->host && url->path &&
    (std::string(url->scheme) == std::string("omniverse") ||
      std::string(url->scheme) == std::string("omni")))
  {
    isValidURL = true;
  }
  omniClientFreeUrl(url);
  return isValidURL;
}

EXPORTABLE const char*
downloadFile(const std::string& fileName) {
  return nullptr;
}

EXPORTABLE void
uploadFile(const std::string& filePath, const std::string& destinyPath) {
  omniClientWait(omniClientCopy(filePath.c_str(), destinyPath.c_str(), copyCallback, nullptr ));
}

EXPORTABLE const char*
downloadMaterial(const std::string& filePath) {
  return nullptr;
}

EXPORTABLE void
uploadMaterial(const std::string& filePath, const std::string& destinationPath) {
  std::string uriPath = destinationPath;

  // Delete the old version of this folder on Omniverse and wait for the operation to complete
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "Waiting for " << uriPath << " to delete... ";
  }
  omniClientWait(omniClientDelete(uriPath.c_str(), nullptr, nullptr));
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "finished" << std::endl;
  }

  // Upload the material folder (MDL and textures)
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "Waiting for the resources/Materials folder to upload to " << uriPath << " ... ";
  }
  omniClientWait(omniClientCopy(filePath.c_str(), uriPath.c_str(), nullptr, nullptr));
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::cout << "finished" << std::endl;
  }
}