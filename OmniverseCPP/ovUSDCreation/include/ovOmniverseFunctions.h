/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/
/**
 * @file 	ovOmniverseFunctions.h
 * @author 	Marco "Swampy" Millan
 * @date 	2022/03/02
 * @brief 	This file contains the code in a way so it is not cluttered on main
 * 
 */
/*0***0***0***0***0***0***0***0***0***0***0***0***0***0***0***0*/

#pragma once

#include <OmniClient.h>
#include <OmniUsdLive.h>
#include <pxr/usd/usd/common.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>

#include <string>
#include <iostream>
#include <mutex>

PXR_NAMESPACE_USING_DIRECTIVE


// Making things easier to work with, will rename a few classes and define we are
// using a few variables

using String = std::string;
using int32 = int32_t;
using Exception = std::exception;
using std::cout;
using std::endl;
using Mutex = std::mutex;
template<typename T>
using UniqueLock = std::unique_lock<T>

// While I do not personally like global variables, we will create ones for the example
static bool g_doLiveEdit = false;
static bool g_omniverseLogEnabled = false;
Mutex g_LogMutex;

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
    std::unique_lock<std::mutex> lk(g_LogMutex);

    std::cout << String("Connection Status: ") 
              << omniClientGetConnectionStatusString(status) 
              << " [" << url << "]" << std::endl;
  }
  if (status == eOmniClientConnectionStatus_ConnectError) {
    // We shouldn't just exit here - we should clean up a bit, but we're going to do it anyway
    std::cout << String("[ERROR] Failed connection, exiting.") << std::endl;
    throw Exception("[ERROR] Failed connection to Omniverse");
    // exit(-1);
  }
}

static void
failNotify(const char* msg, const char* detail = nullptr, ...) {
  std::unique_lock<std::mutex> lk(g_LogMutex);

  fprintf(stderr, "%s\n", msg);
  if (detail != nullptr)
  {
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
  }
}

bool
initialize(bool doLiveEdit) {


  return true;
}

