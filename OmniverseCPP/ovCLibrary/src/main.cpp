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
// #define EXPORTABLE __declspec(dllexport)

extern "C"
{
  EXPORTABLE void
  jsSetLiveSync(bool doLiveEdit = false) {
    setLiveSync(doLiveEdit);
  }

  EXPORTABLE void
  jsSetLogLevel(int logLevel = 2) {
    setLogLevel(logLevel);
  }

  EXPORTABLE const char*
  jsGetGlobalError() {
    std::string error = getGlobalError().c_str();
    return error.c_str();
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
  jsDeleteStage(const std::string& url, const std::string& stageName = "Scene.usd") {
    deleteStage(url, stageName);
  }


  EXPORTABLE const char*
  jsCreateStage(const char* path, const char* name = "Scene.usd") {
    std::string stage = createStage(std::string(path), std::string(name)).c_str();
    return stage.c_str();
  }

  EXPORTABLE void
  jsCheckpointFile(const std::string& url, const std::string& comment) {
    checkpointFile(url, comment);
  }

  EXPORTABLE const char*
  jsGetUsername(const char* url) {
    std::string userName = getUsername(url).c_str();
    return userName.c_str();
  }

  EXPORTABLE bool
  jsIsValidURL(const char* maybeURL) {
    return isValidOmniURL(maybeURL);
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