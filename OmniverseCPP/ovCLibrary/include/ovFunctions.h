#pragma once
// This library allows us to connect to Nucleus
#include <OmniClient.h>
#include <OmniUsdResolver.h>

// This libraries help us create USD objects and components

#include "LiveSessionInfo.h"
#include "LiveSessionConfigFile.h"
#include "OmniChannel.h"
#include "primUtils.h"
#include "xformUtils.h"

#include <pxr/base/gf/matrix4f.h>
#include <pxr/base/gf/vec2f.h>
#include <pxr/base/plug/registry.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/modelAPI.h>
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/domeLight.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/cube.h>
#include <pxr/usd/usdGeom/primvar.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/usd/usdUtils/pipeline.h>
#include <pxr/usd/usdUtils/sparseValueWriter.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usdShade/material.h>
#include <pxr/usd/usdShade/input.h>
#include <pxr/usd/usdShade/output.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>

// Standard libraries
#include <cstdio>
#include <string>
#include <iostream>
#include <mutex>
#include <exception>
#include <fstream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <limits.h>
#include <unistd.h>     //readlink
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

PXR_NAMESPACE_USING_DIRECTIVE

#define EXPORTABLE __declspec(dllexport)

static bool           g_doLiveEdit = true;
static bool           g_omniverseLogEnabled = false;
static std::string    g_error;
static std::string    g_logString;
static std::string    g_userName;
static std::string    g_stageName;
static std::string    g_version;
static std::string    g_connection;
std::mutex            g_LogMutex;
static bool           g_isLive;
static bool           g_stageMerged;

static UsdStageRefPtr   g_stage;
static LiveSessionInfo  g_liveSessionInfo;
static OmniChannel      g_omniChannel;
static std::vector<std::string> g_sessions;
static std::thread              g_channelUpdateThread;

EXPORTABLE class AppUpdate
{
public:
  AppUpdate(int updatePeriodMs)
    : mUpdatePeriodMs(updatePeriodMs), 
      mStopped(false) {}

  void run() {
    while (!mStopped) {
      std::this_thread::sleep_for(std::chrono::milliseconds(mUpdatePeriodMs));
      for (OmniChannel* channel : mChannels) {
        channel->Update();
      }
    }
  }

  int mUpdatePeriodMs;
  bool mStopped;
  std::vector<OmniChannel*> mChannels;
};

static AppUpdate*        g_appUpdate = nullptr;

// Get the Absolute path of the current executable
// Borrowed from https://stackoverflow.com/questions/1528298/get-path-of-executable
static fs::path getExePath()
{
#ifdef _WIN32
  wchar_t path[MAX_PATH] = { 0 };
  GetModuleFileNameW(NULL, path, MAX_PATH);
  return path;
#else
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::string(result, (count > 0) ? count : 0);
#endif
}

static void
omniClientCallback(void* userData,
                   const char* url,
                   OmniClientConnectionStatus status) noexcept {
  // Let's just print this regardless
  {
    std::unique_lock<std::mutex> lk(g_LogMutex);
    std::string message = std::string("Connection Status: ") + 
                          omniClientGetConnectionStatusString(status) + 
                          std::string(" [") + 
                          url + 
                          std::string("]\n");
    std::cout << message;
    g_logString = message;

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
omniMergeCallback(OmniChannelMessage::MessageType messageType, 
                  void* userData, 
                  const char* userName, 
                  const char* appName) {
  // Just a note that userData is available for context
  std::string* existingStage = static_cast<std::string*>(userData);

  std::cout << "Channel Callback: " << OmniChannelMessage::MessageTypeToStringType(messageType) << " " << userName << " - " << appName << std::endl;
  if (messageType == OmniChannelMessage::MessageType::MergeStarted ||
    messageType == OmniChannelMessage::MessageType::MergeFinished)
  {
    std::cout << "Exiting since a merge is happening in another client" << std::endl;
    g_stageMerged = true;
  }
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
  g_isLive = doLiveEdit;
}

// EXPORTABLE void
// setModeForURL(const std::string& url, int mode) {
//   omniUsdLiveSetModeForUrl(url.c_str(), static_cast<OmniUsdLiveMode>(mode));
// }

EXPORTABLE bool
getLiveSync() {
  return g_isLive;
}

// EXPORTABLE int
// getModeForURL(const std::string& url) {
//   return static_cast<int>(omniUsdLiveGetModeForUrl(url.c_str()));
// }

EXPORTABLE void
waitForUpdates() {
  // Version 104
  // omniUsdLiveWaitForPendingUpdates();
  // Version 200
  omniClientLiveWaitForPendingUpdates();
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
  g_logString = "";
  // Find absolute path of the resolver plugins `resources` folder
  std::string pluginResourcesFolder = getExePath().parent_path().string() + "/usd/omniverse/resources";
  PlugRegistry::GetInstance().RegisterPlugins(pluginResourcesFolder);
  std::string PluginName = "OmniUsdResolver";
  if (TfType::FindByName(PluginName).IsUnknown()) {
    failNotify("Could not find the Omniverse USD Resolver plugin");
    return false;
  }

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
  waitForUpdates();

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
checkpointFile(const std::string& url, const std::string& comment, bool force = true) {
  // Version 104 OBSOLETE
  // if (omniUsdLiveGetDefaultEnabled()) {
  //   return;
  // }

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
    omniClientWait(omniClientCreateCheckpoint(url.c_str(), comment.c_str(), force, nullptr,
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
  // {
  //   std::unique_lock<std::mutex> lk(g_LogMutex);
  //   std::cout << "Connected username: " << userName << std::endl;
  // }
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
getFile(const std::string& filePath, const std::string& destinyPath) {
  omniClientWait(omniClientCopy(filePath.c_str(), destinyPath.c_str(), copyCallback, nullptr));

  std::fstream f;
  f.open(destinyPath, std::ios::out | std::ios::app | std::ios::binary);
  std::ostringstream sstream;
  std::ifstream fs("test.txt");
  sstream << fs.rdbuf();
  const std::string str(sstream.str());
  return str.c_str();
}

EXPORTABLE void
transferFile(const std::string& filePath, const std::string& destinyPath) {
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

EXPORTABLE void getSessions() {
  std::string sessionFolderForStage = g_liveSessionInfo.GetSessionFolderPathForStage();
  g_sessions = g_liveSessionInfo.GetLiveSessionList();

  // Get the live layer from the live stage
  SdfLayerHandle liveLayer = g_stage->GetRootLayer();

  // Construct the layers so that we can join the session
  g_stage->GetSessionLayer()->InsertSubLayerPath(liveLayer->GetIdentifier());
  g_stage->SetEditTarget(UsdEditTarget(liveLayer));
}

EXPORTABLE const char* getSessionName(int at) {
  return g_sessions[at].c_str();
}

EXPORTABLE int getSessionListSize() {
  return g_sessions.size();
}

EXPORTABLE void joinSession(int at) {
  g_liveSessionInfo.SetSessionName(g_sessions[at].c_str());


  LiveSessionConfigFile sessionConfig;
  std::string tomlUrl = g_liveSessionInfo.GetLiveSessionTomlUrl();
  if (!sessionConfig.IsVersionCompatible(tomlUrl.c_str()))
  {
    std::string actualVersion = sessionConfig.GetSessionConfigValue(tomlUrl.c_str(), LiveSessionConfigFile::Key::Version);
    std::cout << "The session config TOML file version is not compatible, exiting." << std::endl;
    std::cout << "Expected: " << LiveSessionConfigFile::kCurrentVersion << " Actual: " << actualVersion << std::endl;
    exit(1);
  }

  std::string liveSessionUrl = g_liveSessionInfo.GetLiveSessionUrl();
  g_stage = UsdStage::Open(liveSessionUrl);

  // Get the live layer from the live stage
  SdfLayerHandle liveLayer = g_stage->GetRootLayer();

  // Construct the layers so that we can join the session
  g_stage->GetSessionLayer()->InsertSubLayerPath(liveLayer->GetIdentifier());
  g_stage->SetEditTarget(UsdEditTarget(liveLayer));
}

EXPORTABLE bool isSessionNameValid(const std::string& newSessionName) {
  return g_liveSessionInfo.SetSessionName(newSessionName.c_str());
}

EXPORTABLE bool createSession(const std::string& newSessionName) {

  if (!isSessionNameValid(newSessionName)) {
    std::cout << "Session name " << newSessionName <<
      "Session names must start with an alphabetical character" <<
      " but may contain alphanumeric, hyphen, or underscore characters." << std::endl;
  }

  // Make sure that this session doesn't already exist (don't overwrite/stomp it)
  if (g_liveSessionInfo.DoesSessionExist())
  {
    std::cout << "Session config file already exists at: " << g_liveSessionInfo.GetLiveSessionTomlUrl() << std::endl;
    return false;
  }

  // Create the session config file 
  LiveSessionConfigFile::KeyMap keyMap;
  std::string stageUrl = g_liveSessionInfo.GetStageUrl();
  std::string connectedUserName = getUsername(stageUrl.c_str());
  keyMap[LiveSessionConfigFile::Key::Admin] = connectedUserName.c_str();
  keyMap[LiveSessionConfigFile::Key::StageUrl] = stageUrl.c_str();
  keyMap[LiveSessionConfigFile::Key::Mode] = "default";
  LiveSessionConfigFile sessionConfig;
  if (!sessionConfig.CreateSessionConfigFile(g_liveSessionInfo.GetLiveSessionTomlUrl().c_str(), keyMap))
  {
    std::cout << "Unable to create session config file: " << g_liveSessionInfo.GetLiveSessionTomlUrl() << std::endl;
    exit(1);
  }

  // Create the new root.live file to be the stage's edit target
  std::string liveSessionUrl = g_liveSessionInfo.GetLiveSessionUrl();
  g_stage = UsdStage::CreateNew(liveSessionUrl);

  // Get the live layer from the live stage
  SdfLayerHandle liveLayer = g_stage->GetRootLayer();

  // Construct the layers so that we can join the session
  g_stage->GetSessionLayer()->InsertSubLayerPath(liveLayer->GetIdentifier());
  g_stage->SetEditTarget(UsdEditTarget(liveLayer));
}

EXPORTABLE bool endAndMergeSession() {

  LiveSessionConfigFile sessionConfig;
  std::string sessionAdmin = sessionConfig.GetSessionAdmin(g_liveSessionInfo.GetLiveSessionTomlUrl().c_str());
  std::string currentUser = getUsername(g_liveSessionInfo.GetStageUrl().c_str());
  if (sessionAdmin != currentUser)
  {
    std::cout << "You [" << currentUser << "] are not the session admin [" << sessionAdmin << "].  Stopping merge.";
    return false;
  }

  // Gather the latest changes from the live stage
  omniClientLiveProcess();

  // Send a MERGE_STARTED channel message
  g_omniChannel.SendChannelMessage(OmniChannelMessage::MessageType::MergeStarted);

  // Create a checkpoint on the live layer (don't force if no changes)
  // Create a checkpoint on the root layer (don't force if no changes)
  std::string comment("Pre-merge for " + g_liveSessionInfo.GetSessionName() + " session");
  checkpointFile(g_liveSessionInfo.GetLiveSessionUrl(), comment.c_str(), false);
  checkpointFile(g_liveSessionInfo.GetStageUrl(), comment.c_str(), false);

  std::string mergeOption("_");
  while (mergeOption != "n" && mergeOption != "r" && mergeOption != "c")
  {
    std::cout << "Merge to new layer [n], root layer [r], or cancel [c]: ";
    std::cin >> mergeOption;
  }
  if (mergeOption == "n")
  {
    // Inject a new layer in the same folder as the root with the session name into the root stage (rootStageName_sessionName_edits.usd)
    std::string stageName   = g_liveSessionInfo.GetStageFileName();
    std::string stageFolder = g_liveSessionInfo.GetStageFolderUrl();
    std::string sessionName = g_liveSessionInfo.GetSessionName();
    std::string newLayerUrl = stageFolder + "/" + stageName + "_" + sessionName + ".usd";
    std::cout << "Merging session changes to " << newLayerUrl << " and inserting as a sublayer in the root layer." << std::endl;
    primUtils::MergeLiveLayerToNewLayer(g_stage->GetEditTarget().GetLayer(), g_stage->GetRootLayer(), newLayerUrl.c_str());
  }
  else if (mergeOption == "r")
  {
    // Merge the live deltas to the root layer
    // This does not clear the source layer --- we'll do that after checkpointing it
    primUtils::MergeLiveLayerToRoot(g_stage->GetEditTarget().GetLayer(), g_stage->GetRootLayer());
  }
  else // the merge was canceled
  {
    return false;
  }

  // Create a checkpoint on the root layer while saving it
  std::string postComment("Post-merge for " + g_liveSessionInfo.GetSessionName() + " session");
  omniUsdResolverSetCheckpointMessage(postComment.c_str());
  g_stage->GetRootLayer()->Save();
  omniUsdResolverSetCheckpointMessage("");

  // Clear and save the live layer
  // We shouldn't need to save this live layer, there's a bug somewhere between the 
  // USD resolver, client library, or Nucleus server.  If we don't the contents won't
  // be cleared.
  g_stage->GetEditTarget().GetLayer()->Clear();
  g_stage->GetEditTarget().GetLayer()->Save();

  // Remove the .live layer from the session layer
  g_stage->GetSessionLayer()->GetSubLayerPaths().clear();

  // Send a MERGE_FINISHED channel message
  g_omniChannel.SendChannelMessage(OmniChannelMessage::MessageType::MergeFinished);

  return true;
}


EXPORTABLE void initializeLiveSessionInfo(std::string existingStage) {
  g_liveSessionInfo.Initialize(existingStage.c_str());
}

EXPORTABLE void setChannelURL() {
  g_omniChannel.SetChannelUrl(g_liveSessionInfo.GetMessageChannelUrl().c_str());
}

EXPORTABLE void setAppName(std::string appName) {
  g_omniChannel.SetAppName(appName.c_str());
}

EXPORTABLE void registerChannelCallback() {
  g_omniChannel.RegisterNotifyCallback(omniMergeCallback, &g_stage);
}

EXPORTABLE void joinChannel() {
  g_omniChannel.JoinChannel();
}

EXPORTABLE void leaveChannel() {
  g_omniChannel.LeaveChannel();
}

EXPORTABLE void startApp(int mseconds) {
  if (g_appUpdate != nullptr) { return; }
  g_appUpdate = new AppUpdate(mseconds);
}

EXPORTABLE void runApp() {
  g_channelUpdateThread = std::thread(&AppUpdate::run, g_appUpdate);
}

EXPORTABLE void stopApp() {
  g_appUpdate->mStopped = true;
  g_channelUpdateThread.join();
}