// Copyright (c) 2020-2021, NVIDIA CORPORATION. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.
//
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum
{
    eOmniClientLogLevel_Debug, // Extra chatty
    eOmniClientLogLevel_Verbose, // Chatty
    eOmniClientLogLevel_Info, // Not a problem
    eOmniClientLogLevel_Warning, // Potential problem
    eOmniClientLogLevel_Error, // Definite problem

    Count_eOmniClientLogLevel
} OmniClientLogLevel;

typedef uint64_t OmniClientRequestId;
static const OmniClientRequestId kInvalidRequestId = UINT64_MAX;

typedef enum
{
    eOmniClientResult_Ok,
    eOmniClientResult_OkLatest,
    // This is returned only by the Stat and Resolve Subscribe functions to indicate that the file wasn't found, but it
    // is being monitored, as opposed to an error e.g. eOmniClientResult_ErrorNotFound which would indicate that Stat
    // didn't find the file, but it is also no longer monitoring the file.
    eOmniClientResult_OkNotYetFound,
    eOmniClientResult_Error,
    eOmniClientResult_ErrorConnection,
    eOmniClientResult_ErrorNotSupported,
    eOmniClientResult_ErrorAccessDenied,
    eOmniClientResult_ErrorNotFound,
    eOmniClientResult_ErrorBadVersion,
    eOmniClientResult_ErrorAlreadyExists,
    eOmniClientResult_ErrorAccessLost,

    Count_eOmniClientResult
} OmniClientResult;

typedef enum
{
    eOmniClientConnectionStatus_Connecting, // Attempting to connect
    eOmniClientConnectionStatus_Connected, // Successfully connected
    eOmniClientConnectionStatus_ConnectError, // Error trying to connect
    eOmniClientConnectionStatus_Disconnected, // Disconnected

    Count_eOmniClientConnectionStatus
} OmniClientConnectionStatus;

typedef enum OmniClientFileStatus
{
    eOmniClientFileStatus_Reading,
    eOmniClientFileStatus_Writing,
    eOmniClientFileStatus_Copying,
    eOmniClientFileStatus_Deleting,

    eOmniClientFileStatus_LiveUpdateSending,
    eOmniClientFileStatus_LiveUpdateReceived,

    Count_eOmniClientFileStatus
} OmniClientFileStatus;

#define BIT(x) (1 << (x - 1))

typedef enum
{
    // Can read this thing
    fOmniClientAccess_Read = BIT(1),

    // Can write to this thing
    fOmniClientAccess_Write = BIT(2),

    // Can change ACLs for this thing
    fOmniClientAccess_Admin = BIT(3),

    fOmniClientAccess_Full = fOmniClientAccess_Admin | fOmniClientAccess_Write | fOmniClientAccess_Read

} OmniClientAccessFlags;

typedef enum
{
    // You can call omniClientReadFile on this
    // note: ACLs may still prevent you from reading it
    fOmniClientItem_ReadableFile = BIT(1),

    // You can call omniClientWriteFile on this
    // note ACLs may still prevent you from writing it
    fOmniClientItem_WriteableFile = BIT(2),

    // This thing can contain other things (a folder-like thing)
    fOmniClientItem_CanHaveChildren = BIT(3),

    // This thing does not have any children.
    // The lack of this flag does not mean it does have children!
    // Sometimes we are not sure if it has children until you attempt to list the children.
    // This is only intended to be used for UI elements to hide the "expand" button if we
    // are sure it does not have any children.
    fOmniClientItem_DoesNotHaveChildren = BIT(4),

    // This thing is the root of a mount point
    fOmniClientItem_IsMount = BIT(5),

    // This thing is located inside a mounted folder
    fOmniClientItem_IsInsideMount = BIT(6),

    // This thing supports live updates
    fOmniClientItem_CanLiveUpdate = BIT(7),

    // This thing is in omni-object format
    // You must use a special API to read/write it
    fOmniClientItem_IsOmniObject = BIT(8),

    // You can call omniClientJoinChannel on this
    fOmniClientItem_IsChannel = BIT(9),

    // This item is checkpointed (meaning you can revert to it)
    fOmniClientItem_IsCheckpointed = BIT(10)
} OmniClientItemFlags;

#undef BIT

struct OmniClientListEntry
{
    // The path for this item relative to the url provided to "List"
    const char* relativePath;
    // YOUR access level
    // Some combination of OmniClientAccessFlags
    uint32_t access;
    // Information about this item
    // Some combination of OmniClientItemFlags
    uint32_t flags;
    // For files, the size in bytes
    uint64_t size;
    // Nanoseconds since the Unix epoch (1 January 1970)
    uint64_t modifiedTimeNs;
    // Nanoseconds since the Unix epoch (1 January 1970)
    uint64_t createdTimeNs;
    // User name of the last person to modify it
    // Not all providers support this, so it may be null
    const char* modifiedBy;
    // User name of the person that created it
    // Not all providers support this, so it may be null
    const char* createdBy;
    // Provider-specific version
    // May not be an always incrementing number (could be a hash, for example)
    // Not all providers support this, so it may be null
    const char* version;
    // Provider specific file hash
    // Not all providers support this, so it may be null
    const char* hash;
    // Provider specific comment
    // Not all providers support this, so it may be null
    const char* comment;
};

typedef enum
{
    eOmniClientListEvent_Unknown,
    eOmniClientListEvent_Created,
    eOmniClientListEvent_Updated,
    eOmniClientListEvent_Deleted,
    eOmniClientListEvent_Metadata,
    eOmniClientListEvent_Locked,
    eOmniClientListEvent_Unlocked,

    Count_eOmniClientListEvent
} OmniClientListEvent;

struct OmniClientContent
{
    void* buffer;
    size_t size;
    void (*free)(void* buffer); // Function to call to free the buffer
};

typedef enum
{
    eOmniClientChannelEvent_Error, // Error
    eOmniClientChannelEvent_Message, // Someone sent a message
    eOmniClientChannelEvent_Hello, // You joined a channel that someone else was already in, and they said hello.
    eOmniClientChannelEvent_Join, // Someone joined
    eOmniClientChannelEvent_Left, // Someone left
    eOmniClientChannelEvent_Deleted, // Someone deleted the channel or changed ACLs so you no longer have access.

    Count_eOmniClientChannelEvent
} OmniClientChannelEvent;

struct OmniClientAclEntry
{
    const char* name;
    // Some combination of OmniClientAccessFlags
    uint32_t access;
};

// A URL broken into the component pieces
// A fully composed URL takes the format "scheme://user@host:port/path?query#fragment"
// Note that "null" is different from blank. Null means the component is missing, blank
// means it exists but has no value.
// See also https://en.wikipedia.org/wiki/Uniform_Resource_Identifier#Generic_syntax
// Also note that omniverse: urls IGNORE the "user" component!
struct OmniClientUrl
{
    char const* scheme;
    char const* user;
    char const* host;
    char const* port;
    char const* path;
    char const* query;
    char const* fragment;
    bool isRaw;
};

struct OmniClientBranchAndCheckpoint
{
    char const* branch;
    uint64_t checkpoint;
};

struct OmniClientServerInfo
{
    char const* version;
    char const* username;
    char const* authToken;
    bool cacheEnabled;
    bool omniObjectsEnabled;
    bool checkpointsEnabled;
};

struct OmniClientCredentials
{
    bool abort;
    struct OmniClientContent token;
    struct OmniClientContent username;
    struct OmniClientContent password;
};

typedef enum
{
    eOmniClientCopy_ErrorIfExists, ///< Stops copying and issues an error if a file exists.
    eOmniClientCopy_Overwrite, ///< Overwrites any destination file(s) with the source file.
} OmniClientCopyBehavior;
