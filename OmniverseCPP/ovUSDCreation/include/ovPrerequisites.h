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


// Making things easier to work with, will rename a few classes and define we are
// using a few variables

using String = std::string;
using int32 = int32_t;
using Exception = std::exception;
using Mutex = std::mutex;

template<typename T>
using UniqueLock = std::unique_lock<T>;

using std::cout;
using std::endl;
