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

typedef void(OMNICLIENT_ABI* OmniClientLogCallback)
    (char const* threadName, char const* component, OmniClientLogLevel level, char const* message)
    OMNICLIENT_CALLBACK_NOEXCEPT;

// This function is called any time any connection status changes
// url does not include path components, for example it could be
// "omniverse://sandbox.ov.nvidia.com" or "http://nvidia.com"
typedef void
    (OMNICLIENT_ABI* OmniClientConnectionStatusCallback)(void* userData, char const* url, OmniClientConnectionStatus status)
    OMNICLIENT_CALLBACK_NOEXCEPT;

// This function is called any time any file status changes
typedef void
    (OMNICLIENT_ABI* OmniClientFileStatusCallback)(void* userData, char const* url, OmniClientFileStatus status, int percentage)
    OMNICLIENT_CALLBACK_NOEXCEPT;

// The authentication callback receives the "prefix" of the server it's trying to connect to, which could be of the
// form "omniverse://server:port" "http://server" "file://server" etc.. You can use the various omniClientUrl functions to
// Parse the prefix into scheme, host, and port.
// Return false to fall back to the default credentials (for example because this is not a server you care about)
// Return true if you have filled in the credentials
// Either:
// Set credentials->abort to true to stop the sign-in process
// OR set credentials->token
// OR set credentials->username and credentials->password
typedef bool
    (OMNICLIENT_ABI* OmniClientAuthCallback)(void* userData, char const* prefix, struct OmniClientCredentials * credentials)
    OMNICLIENT_CALLBACK_NOEXCEPT;

// Through this callback the application may receive the authentication status.
// This is useful for showing a modal dialog preventing interaction with the client UI
// until authentication (possibly involving other applications, like a system browser or
// Omniverse System Monitor) finished or cancelled.
typedef void
    (OMNICLIENT_ABI* OmniClientSetAuthenticationMessageBoxCallback)(void* userData, bool show, const char* server)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientGetServerInfoCallback)(void* userData, OmniClientResult result, struct OmniClientServerInfo const * info)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientStatCallback)(void* userData, OmniClientResult result, struct OmniClientListEntry const* entry)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientStatSubscribeCallback)(void* userData, OmniClientResult result, OmniClientListEvent listEvent, struct OmniClientListEntry const* entry)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientResolveCallback)(void* userData, OmniClientResult result, struct OmniClientListEntry const* entry, char const* url)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientResolveSubscribeCallback)(void* userData, OmniClientResult result, OmniClientListEvent listEvent, struct OmniClientListEntry const* entry, char const* url)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientListCallback)(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientListEntry const* entries)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientListSubscribeCallback)(void* userData, OmniClientResult result, OmniClientListEvent listEvent, struct OmniClientListEntry const* entry)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientDeleteCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientCopyCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

// Create a folder
// Returns eOmniClientResult_ErrorAlreadyExists if the URL already exists (note that it may not actually be a folder!)
typedef void
    (OMNICLIENT_ABI* OmniClientCreateFolderCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientWriteFileCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientReadFileCallback)(void* userData, OmniClientResult result, char const* version, struct OmniClientContent* content)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientGetLocalFileCallback)(void* userData, OmniClientResult result, char const* localFilePath)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientJoinChannelCallback)(void* userData, OmniClientResult result, OmniClientChannelEvent eventType, char const* from, struct OmniClientContent* content)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientSendMessageCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientGetAclsCallback)(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientAclEntry* entries)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientSetAclsCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientLockCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientUnlockCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientCreateCheckpointCallback)(void* userData, OmniClientResult result, char const * checkpointQuery)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientListCheckpointsCallback)(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientListEntry const* entries)
    OMNICLIENT_CALLBACK_NOEXCEPT;

#if 0 // Coming soon in MVp2!

typedef void
    (OMNICLIENT_ABI* OmniClientUpdateBranchCallback)(void* userData, OmniClientResult result, char const * checkpointQuery)
    OMNICLIENT_CALLBACK_NOEXCEPT;

typedef void
    (OMNICLIENT_ABI* OmniClientListBranchesCallback)(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientListEntry const* entries)
    OMNICLIENT_CALLBACK_NOEXCEPT;

#endif
