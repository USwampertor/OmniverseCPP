#pragma once
// This library allows us to connect to Nucleus
#include <OmniClient.h>

// This libraries help us create USD objects and components

#include <OmniUsdResolver.h>
#include "OmniChannel.h"
#include "LiveSessionInfo.h"
#include "LiveSessionConfigFile.h"

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

// Making things easier to work with, will rename a few classes and define we are
// using a few variables

// using String = std::string;
// using int32 = int32_t;
// using Exception = std::exception;
// using Mutex = std::mutex;
// 
// template<typename T>
// using UniqueLock = std::unique_lock<T>;
// 
// using std::cout;
// using std::endl;
