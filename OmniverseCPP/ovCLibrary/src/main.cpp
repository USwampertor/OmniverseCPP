/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	main.cpp
 * @author 	Marco "Swampy" Millan
 * @date 	2022/08/16
 * @brief This is a C version of the Omniverse library, this to be
 *        exportable to as External Objects for Python or JS
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/

#include "ovFunctions.h"


extern "C"
{
  /*
   *	@brief	This sets the live syncing between the file and omniverse
   *	@param  bool doLiveEdit sets if the file is live syncing or not	
   *	@return -
   */
  EXPORTABLE void
  cSetLiveSync(bool doLiveEdit = true) {
    setLiveSync(doLiveEdit);
  }

  EXPORTABLE bool
  cGetLiveSync() {
    return getLiveSync();
  }

  EXPORTABLE void
  cSetLogLevel(int logLevel = 2) {
    setLogLevel(logLevel);
  }

  EXPORTABLE const char*
  cGetVersion() {
    g_version = getVersionString().c_str();
    return g_version.c_str();
  }

  EXPORTABLE const char*
  cGetConnectionStatus(int status) {
    g_connection = getConnectionStatus(status).c_str();
    return g_connection.c_str();
  }

  EXPORTABLE const char*
  cGetGlobalError() {
    return g_error.c_str();
  }

  EXPORTABLE const char*
  cGetLogString() {
    return g_logString.c_str();
  }

  EXPORTABLE bool 
  cInitialize(bool doLiveEdit = false, int logLevel = 2) {
   return initialize(doLiveEdit, logLevel);
  }
  
  EXPORTABLE void
  cShutdown() {
   return shutdown();
  }
 
  EXPORTABLE void
  cDeleteStage(const char* url, const char* stageName = "Scene.usd") {
    deleteStage(url, stageName);
  }

  EXPORTABLE const char*
  cCreateStage(const char* path, const char* name = "Scene.usd") {
   g_stageName = createStage(std::string(path), std::string(name)).c_str();
    std::cout << g_stageName << std::endl;
    return g_stageName.c_str();
  }

  EXPORTABLE void
  cCheckpointFile(const char* url, const char* comment) {
    checkpointFile(url, comment);
  }

  EXPORTABLE void
  cForceConnect(const char* url) {
    forceConnect(url);
  }

  EXPORTABLE const char*
  cGetUsername(const char* url) {
    g_userName = getUsername(url).c_str();
    std::cout << g_userName << std::endl;
    return g_userName.c_str();
  }

  EXPORTABLE bool
  cURLObjectExists(const char* maybeFile) {
    return urlObjectExists(maybeFile);
  }

  EXPORTABLE bool
  cIsValidURL(const char* maybeURL) {
    return isValidOmniURL(maybeURL);
  }

  EXPORTABLE const char*
  cGetFile(const char* filePath, const char* destinyPath) {
    return getFile(filePath, destinyPath);
  }

  EXPORTABLE const char*
  cGetLocalFile(const char* filePath) {
    return getLocalFile(filePath).c_str();
  }

  EXPORTABLE int
  cGetFolderCount() {
    return getFolderCount();
  }

  EXPORTABLE bool
  cIsEntryFolder(int position) {
    return isEntryFolder(position);
  }

  EXPORTABLE OmniFolderEntry*
  cFetchFileEntry (int position) {
    return fetchFileEntry(position);
  }

  EXPORTABLE void
  cFetchFolderEntries(const char* folderPath) {
    return fetchFolderEntries(folderPath);
  }

  EXPORTABLE void
  cTransferFile(const char* filePath, const char* destinyPath) {
    transferFile(filePath, destinyPath);
  }

  EXPORTABLE void
  cDeleteFile(const char* filePath) {
    deleteFile(filePath);
  }

  EXPORTABLE const char*
  cDownloadMaterial(const char* filePath) {
    return downloadMaterial(filePath);
  }

  EXPORTABLE void
  cUploadMaterial(const char* filePath, const char* destinationPath) {
    return uploadMaterial(filePath, destinationPath);
  }

  EXPORTABLE void
  cGetSessions() {
    return getSessions();
  }

  EXPORTABLE const char*
  cGetSessionName(int at) {
    return getSessionName(at);
  }

  EXPORTABLE int 
  cGetSessionListSize() {
    return getSessionListSize();
  }

  EXPORTABLE void
  cJoinSession(int at) {
    return joinSession(at);
  }


  EXPORTABLE bool
  cIsSessionNameValid(const char* newSessionName) {
    return isSessionNameValid(newSessionName);
  }

  EXPORTABLE bool
  cCreateSession(const char* newSessionName) {
    return createSession(newSessionName);
  }

  EXPORTABLE bool
  cEndAndMergeSession() {
    return endAndMergeSession();
  }

  EXPORTABLE void
  cInitializeLiveSessionInfo(const char* existingStage) {
    return initializeLiveSessionInfo(existingStage);
  }

  EXPORTABLE void
  cSetChannelURL() {
    return setChannelURL();
  }

  EXPORTABLE void
  cSetAppName(const char* appName) {
    return setAppName(appName);
  }

  EXPORTABLE void
  cRegisterChannelCallback() {
    return registerChannelCallback();
  }

  EXPORTABLE void 
  cJoinChannel() {
    return joinChannel();
  }

  EXPORTABLE void
  cLeaveChannel() {
    return leaveChannel();
  }

  EXPORTABLE void 
  cStartApp(int mseconds) {
    return startApp(mseconds);
  }

  EXPORTABLE void
  cRunApp() {
    return runApp();
  }

  EXPORTABLE void
  cStopApp() {
    return stopApp();
  }

  /// <summary>
  /// This is only to check if the system is actually working
  /// </summary>
  /// <returns></returns>
  EXPORTABLE int
  cPing() {
    return 1;
  }
}

#define ASDLL 1
#if ASDLL == 0

int main()
{

  std::string destinationPath = "omniverse://localhost/Projects/";

  try
  {
    if (!cInitialize(true)) {
      throw std::exception("Error initializing");
    }
    // const std::string stageURL = cCreateStage(destinationPath.c_str());
    // std::cout << "Connected user:" << cGetUsername(stageURL.c_str()) << std::endl;

    // const std::string localFile = cGetLocalFile(stageURL.c_str());
    // std::cout << localFile << std::endl;
    cFetchFolderEntries(destinationPath.c_str());
    if (cGetFolderCount() > 0) {
      std::cout << "File fetched is: " << std::string(cFetchFileEntry(0)->relativePath) << std::endl;
    }

    std::cout << "Finishing..." << std::endl;

    std::cout << cURLObjectExists("omniverse://localhost/Projects/") << " : " 
              << cURLObjectExists("omniverse://localhost/asdfasdf/") << std::endl;
  }
  catch (const std::exception& e) 
  {
    std::cout << std::string("There was a problem with Omniverse \n") << e.what() << std::endl;
    return -1;
  }
  return 0;
}

#endif
