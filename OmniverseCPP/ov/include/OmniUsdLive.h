// Copyright (c) 2020-2021, NVIDIA CORPORATION. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.
//
// clang-format off
#pragma once

#include "OmniClientAbi.h"
#include "OmniClientTypes.h"

/*
Live mode means updates from other users are applied to your scene.

When live mode is disabled:
* You will not receive updates from other users.
* Saving a layer will OVERWRITE it on the server.
* Saving a layer will BLOCK until the layer has been saved.
* This is functionally equivalent to using Omniverse like a filesystem.

When live mode is enabled:
* You will receive updates from other users.
* Saving a layer will send a delta to the server, to merge your changes with others
* Saving a layer will return immediately (not block).
* You must call omniUsdLiveProcess (or omniUsdLiveProcessUpTo) to apply remote updates
    to your scene and to process any responses the server may have sent about delta updates
    that you have sent (from calling Save).
* You may call omniUsdLiveWaitForPendingUpdates to block until the server has acknowledged
    all the updates that you have sent to it.

Live mode can be set per-layer with a global default.
*/
typedef enum
{
    eOmniUsdLiveModeDefault,
    eOmniUsdLiveModeDisabled,
    eOmniUsdLiveModeEnabled,
} OmniUsdLiveMode;

OMNICLIENT_EXPORT(void)
    omniUsdLiveSetDefaultEnabled(bool enabled)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(void)
    omniUsdLiveSetModeForUrl(const char* url, OmniUsdLiveMode mode)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(bool)
    omniUsdLiveGetDefaultEnabled()
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(OmniUsdLiveMode)
    omniUsdLiveGetModeForUrl(const char* url)
    OMNICLIENT_NOEXCEPT;

// Set a function to be called any time there's an update in the queue that needs to be processed
// When this function is called, you should call omniUsdLiveProcess(false) FROM THE MAIN THREAD.
// DO NOT CALL omniUsdLiveProcess(false) FROM THIS CALLBACK!
// DO NOT CALL omniUsdLiveProcess(false) WHEN SOME OTHER THREAD IS USING THE USD LIBRARY!
typedef void
    (OMNICLIENT_ABI* OmniUsdLiveQueuedCallback)()
    OMNICLIENT_CALLBACK_NOEXCEPT;

OMNICLIENT_EXPORT(void)
    omniUsdLiveSetQueuedCallback(OmniUsdLiveQueuedCallback callback)
    OMNICLIENT_NOEXCEPT;

typedef enum
{
    eOmniUsdLiveResolveMethodUsingClient,
    eOmniUsdLiveResolveMethodUsingServer,
} OmniUsdLiveResolveMethod;

OMNICLIENT_EXPORT(void)
    omniUsdLiveSetResolveMethod(OmniUsdLiveResolveMethod resolveMethod)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(OmniUsdLiveResolveMethod)
    omniUsdLiveGetResolveMethod()
    OMNICLIENT_NOEXCEPT;

// Call this to process live updates received from the server.
OMNICLIENT_EXPORT(void)
    omniUsdLiveProcess()
    OMNICLIENT_NOEXCEPT;

// Same as omniUsdLiveProcess(false) but you can specify a server time to stop processing updates.
OMNICLIENT_EXPORT(void)
    omniUsdLiveProcessUpTo(const char* url, uint64_t serverTime)
    OMNICLIENT_NOEXCEPT;

// Returns the server timestamp of the most recently received message (0 if no messages have been received)
OMNICLIENT_EXPORT(uint64_t)
    omniUsdLiveGetLatestServerTime(const char* url)
    OMNICLIENT_NOEXCEPT;

// Call this to wait for all pending live updates to complete.
// You should only have to call this at shutdown.
OMNICLIENT_EXPORT(void)
    omniUsdLiveWaitForPendingUpdates()
    OMNICLIENT_NOEXCEPT;

// Set parameters that control jitter reduction
// Jitter reduction adds delay to packets received to compensate for latency variance
// The formula is: delay = sentTime + min(delayMaximum, delayConstant + delayMultiple * averageLatency) - receivedTime
// Where:
//     sentTime is the (actual) server time when the packet was sent
//     receivedTime is the (estimated) server time when the packet was received
//     averageLatency is the average amount of latency measured from periodic pings
//     delay is the amount of time to wait before processing the packet
// Pass (0,0,0) to completely disable jitter reduction
// Pass (100,2,1000) to enable 100 milliseconds of delay plus 2x the measured latency, up to 1 second
OMNICLIENT_EXPORT(void)
    omniUsdLiveConfigureJitterReduction(uint32_t delayConstantMilliseconds, uint32_t delayMultiple, uint32_t delayMaximumMilliseconds)
    OMNICLIENT_NOEXCEPT;
