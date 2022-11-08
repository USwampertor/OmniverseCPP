/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	main.cpp
 * @author 	Marco "Swampy" Millan
 * @date 	2022/08/16
 * @brief This only is to make things callable from C++ to javascript
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/


#include "ovFunctions.h"

extern "C"
{
  EXPORTABLE void
  jsSetLiveSync(bool doLiveEdit = true) {
    setLiveSync(doLiveEdit);
  }

  EXPORTABLE bool
  jsGetLiveSync() {
    return getLiveSync();
  }

  EXPORTABLE void
  jsSetLogLevel(int logLevel = 2) {
    setLogLevel(logLevel);
  }

  EXPORTABLE const char*
  jsGetVersion() {
    g_version = getVersionString().c_str();
    return g_version.c_str();
  }

  EXPORTABLE const char*
  jsGetConnectionStatus(int status) {
    g_connection = getConnectionStatus(status).c_str();
    return g_connection.c_str();
  }

  EXPORTABLE const char*
  jsGetGlobalError() {
    return getGlobalError().c_str();
  }

  EXPORTABLE const char*
  jsGetLogString() {
    return g_logString.c_str();
  }

  EXPORTABLE bool 
  jsInitialize(bool doLiveEdit = false, int logLevel = 2) {
   return initialize(doLiveEdit, logLevel);
  }
 
  EXPORTABLE void
  jsShutdown() {
   return shutdown();
  }
 
  EXPORTABLE void
  jsDeleteStage(const char* url, const char* stageName = "Scene.usd") {
    deleteStage(url, stageName);
  }


  EXPORTABLE const char*
  jsCreateStage(const char* path, const char* name = "Scene.usd") {
   g_stageName = createStage(std::string(path), std::string(name)).c_str();
    std::cout << g_stageName << std::endl;
    return g_stageName.c_str();
  }

  EXPORTABLE void
  jsCheckpointFile(const char* url, const char* comment) {
    checkpointFile(url, comment);
  }

  EXPORTABLE const char*
  jsGetUsername(const char* url) {
    g_userName = getUsername(url).c_str();
    std::cout << g_userName << std::endl;
    return g_userName.c_str();
  }

  EXPORTABLE bool
  jsIsValidURL(const char* maybeURL) {
    return isValidOmniURL(maybeURL);
  }

  EXPORTABLE const char*
  jsGetFile(const char* filePath, const char* destinyPath) {
    return getFile(filePath, destinyPath);
  }

  EXPORTABLE void
  jsTransferFile(const char* filePath, const char* destinyPath) {
    transferFile(filePath, destinyPath);
  }

  EXPORTABLE const char*
  jsDownloadMaterial(const char* filePath) {
    return downloadMaterial(filePath);
  }

  EXPORTABLE void
  uploadMaterial(const char* filePath, const char* destinationPath) {
    return uploadMaterial(filePath, destinationPath);
  }

  EXPORTABLE void
  jsgetSessions() {
    return getSessions();
  }

  EXPORTABLE const char*
  jsGetSessionName(int at) {
    return getSessionName(at);
  }

  EXPORTABLE int 
  jsGetSessionListSize() {
    return getSessionListSize();
  }

  EXPORTABLE void
  jsJoinSession(int at) {
    return joinSession(at);
  }


  EXPORTABLE bool
  jsIsSessionNameValid(const char* newSessionName) {
    return isSessionNameValid(newSessionName);
  }

  EXPORTABLE bool
  jsCreateSession(const char* newSessionName) {
    return createSession(newSessionName);
  }

  EXPORTABLE bool
  jsEndAndMergeSession() {
    return endAndMergeSession();
  }

  EXPORTABLE void
  jsInitializeLiveSessionInfo(const char* existingStage) {
    return initializeLiveSessionInfo(existingStage);
  }

  EXPORTABLE void
  jsSetChannelURL() {
    return setChannelURL();
  }

  EXPORTABLE void
  jsSetAppName(const char* appName) {
    return setAppName(appName);
  }

  EXPORTABLE void
  jsRegisterChannelCallback() {
    return registerChannelCallback();
  }

  EXPORTABLE void 
  jsJoinChannel() {
    return joinChannel();
  }

  EXPORTABLE void
  jsLeaveChannel() {
    return leaveChannel();
  }

  EXPORTABLE void 
  jsStartApp(int mseconds) {
    return startApp(mseconds);
  }

  EXPORTABLE void
  jsRunApp() {
    return runApp();
  }

  EXPORTABLE void
  jsStopApp() {
    return stopApp();
  }


  /// <summary>
  /// This is only to check if the system is actually working
  /// </summary>
  /// <returns></returns>
  EXPORTABLE int
  jsPing() {
    return 1;
  }
  
}