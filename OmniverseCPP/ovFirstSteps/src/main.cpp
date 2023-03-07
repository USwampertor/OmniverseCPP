/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	main.cpp
 * @author 	Marco "Swampy" Millan
 * @date 	2022/10/14
 * @brief Hi and welcome to the Omniverse First Steps!
          I hope this tutorial can show you how Omniverse works
          and how to use it to increase the functionality of
          your production pipeline!

          This Tutorial is aimed at the biggest basic thing: to
          connect to the Omniverse Client (Lets you connect to
          the Omniverse Nucleus server)
          
          This is a complementary work, for the theory part look
          for the documentation at 
          https://github.com/USwampertor/OmniverseCPP
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <map>
#include <condition_variable>

#include <OmniClient.h>

static bool gOmniverseLoggingEnabled = false;
static std::mutex gLogMutex;

static void OmniClientConnectionStatusCallbackImpl(void* userData, const char* url, OmniClientConnectionStatus status) noexcept
{
  // Let's just print this regardless
  {
    std::unique_lock<std::mutex> lk(gLogMutex);
    std::cout <<  "Connection Status: " << 
                  omniClientGetConnectionStatusString(status) <<
                  " [" << 
                  url <<
                  "]" << std::endl;
  }
  if (status == eOmniClientConnectionStatus_ConnectError)
  {
    // We shouldn't just exit here - we should clean up a bit, but we're going to do it anyway
    std::cout << "[ERROR] Failed connection, exiting." << std::endl;
    exit(-1);
  }
}


static void failNotify(const char* msg, const char* detail = nullptr, ...)
{
  std::unique_lock<std::mutex> lk(gLogMutex);

  fprintf(stderr, "%s\n", msg);
  if (detail != nullptr)
  {
    fprintf(stderr, "%s\n", detail);
  }
}

// Shut down Omniverse connection
static void shutdownOmniverse()
{
  // Calling this prior to shutdown ensures that all pending live updates complete.
  omniClientLiveWaitForPendingUpdates();

  //omniClientTick(1000);
  omniClientShutdown();
}

// Omniverse Log callback
static void omniLogCallback(const char* threadName, const char* component, OmniClientLogLevel level, const char* message) noexcept
{
  std::unique_lock<std::mutex> lk(gLogMutex);
  if (gOmniverseLoggingEnabled)
  {
    puts(message);
  }
}

// Startup Omniverse 
static bool startOmniverse()
{
  // Register a function to be called whenever the library wants to print something to a log
  omniClientSetLogCallback(omniLogCallback);

  // The default log level is "Info", set it to "Debug" to see all messages
  omniClientSetLogLevel(eOmniClientLogLevel_Debug);

  // Initialize the library and pass it the version constant defined in OmniClient.h
  // This allows the library to verify it was built with a compatible version. It will
  // return false if there is a version mismatch.
  if (!omniClientInitialize(kOmniClientVersion))
  {
    return false;
  }

  omniClientRegisterConnectionStatusCallback(nullptr, OmniClientConnectionStatusCallbackImpl);

  return true;
}

static std::string getConnectedUsername(const char* stageUrl)
{
  // Get the username for the connection
  std::string userName("_none_");
  omniClientWait(omniClientGetServerInfo(stageUrl, &userName, [](void* userData, OmniClientResult result, struct OmniClientServerInfo const* info) noexcept
    {
      std::string* userName = static_cast<std::string*>(userData);
      if (userData && userName && info && info->username)
      {
        userName->assign(info->username);
      }
    }));

  return userName;
}

// Stage URL really only needs to contain the server in the URL.  eg. omniverse://ov-prod
static void printConnectedUsername(const std::string& stageUrl)
{
  // Get the username for the connection
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
    std::unique_lock<std::mutex> lk(gLogMutex);
    std::cout << "Connected username: " << userName << std::endl;
  }
}

// Returns true if the provided maybeURL contains a host and path
static bool isValidOmniURL(const std::string& maybeURL)
{
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

int main() {

  if (!startOmniverse()) { return -1; }
  std::string userFolder = "omniverse://localhost/Users";
  std::string username = getConnectedUsername(userFolder.c_str());

  std::cout << userFolder << std::endl;
  std::cout << username << std::endl;

  shutdownOmniverse();
  return 0;
}