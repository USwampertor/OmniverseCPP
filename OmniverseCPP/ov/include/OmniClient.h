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
#include "OmniClientCallbacks.h"

#include "OmniClientVersion.h"

const uint64_t kOmniClientVersion = (uint64_t)OMNICLIENT_VERSION_MAJOR << 48 |
                                    (uint64_t)OMNICLIENT_VERSION_MINOR << 32 |
                                    (uint64_t)OMNICLIENT_VERSION_PATCH;

// =======
// General
// =======

// Register a function that will be called when the plugin wants to write anything to a log
// This is the only function that's safe to call before Initialize
OMNICLIENT_EXPORT(void)
    omniClientSetLogCallback(OmniClientLogCallback callback)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(void)
    omniClientSetLogLevel(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(char const*)
    omniClientGetLogLevelString(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(char)
    omniClientGetLogLevelChar(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

// Perform some one-time initialization prior to calling anything else (except SetLog)
// Pass kOmniClientVersion as the parameter to ensure the header matches the dll
// Returns false if initialization failed for any reason (most likely a version mismatch)
OMNICLIENT_EXPORT(bool)
    omniClientInitialize(uint64_t version)
    OMNICLIENT_NOEXCEPT;

// Terminate all connections and free everything
// It's not safe to call any functions (not even Initialize!) after calling this
OMNICLIENT_EXPORT(void)
    omniClientShutdown()
    OMNICLIENT_NOEXCEPT;

// Returns a human-readable version string, the format is not guaranteed to remain consistent, so don't try to parse it
OMNICLIENT_EXPORT(char const*)
    omniClientGetVersionString()
    OMNICLIENT_NOEXCEPT;

// Register a callback to receive connection status updates
// Returns a handle that you can use with omniClientUnregisterCallback
OMNICLIENT_EXPORT(uint32_t)
    omniClientRegisterConnectionStatusCallback(void* userData, OmniClientConnectionStatusCallback callback)
    OMNICLIENT_NOEXCEPT;

// Retrieve a human readable string from a connection status
OMNICLIENT_EXPORT(char const*)
    omniClientGetConnectionStatusString(OmniClientConnectionStatus connectionStatus)
    OMNICLIENT_NOEXCEPT;

// Register a callback to receive file transfer updates
// Returns a handle that you can use with omniClientUnregisterCallback
OMNICLIENT_EXPORT(uint32_t)
    omniClientRegisterFileStatusCallback(void* userData, OmniClientFileStatusCallback callback)
    OMNICLIENT_NOEXCEPT;

// Retrieve a human readable string from a file status
OMNICLIENT_EXPORT(char const*)
    omniClientGetFileStatusString(OmniClientFileStatus fileStatus)
    OMNICLIENT_NOEXCEPT;

// Retrieve a human readable string from a result
OMNICLIENT_EXPORT(char const*)
    omniClientGetResultString(OmniClientResult result)
    OMNICLIENT_NOEXCEPT;

// Stop an active request. Your callback will not be called after this function returns.
// If a callback is in process omniClientStop() will wait to return until the callback completes.
// NOTE: Don't hold mutexes that may also be used by any functions called by callbacks of *requestId*
// as this can lead to deadlocks.
OMNICLIENT_EXPORT(void)
    omniClientStop(OmniClientRequestId requestId)
    OMNICLIENT_NOEXCEPT;

// Wait for a request, your callback will be called before this returns.
// For subscription requests (like omnClientListSubscribe or omniClientJoinChannel) this
// will return after the initial message is received
OMNICLIENT_EXPORT(void)
    omniClientWait(OmniClientRequestId requestId)
    OMNICLIENT_NOEXCEPT;

// Same as omniClientWait, but with a timeout in milliseconds
// Returns false if the wait timed out before the request finished
OMNICLIENT_EXPORT(bool)
    omniClientWaitFor(OmniClientRequestId requestId, uint64_t milliseconds)
    OMNICLIENT_NOEXCEPT;

// Redirect a URL to a different location
// For example alias("home:", "C:\Users\brianh\")
// Call it with dst=null to remove an alias
OMNICLIENT_EXPORT(void)
    omniClientSetAlias(char const* src, char const* dst)
    OMNICLIENT_NOEXCEPT;

// Get access to the reactor.
// Use idl.cpp reactor.h and reactor.hh for the types definitions.
struct OmniIDLCPPInitializerReactor;
OMNICLIENT_EXPORT(struct OmniIDLCPPInitializerReactor*)
    omniClientGetReactor()
    OMNICLIENT_NOEXCEPT;

// Unregister a callback
OMNICLIENT_EXPORT(void)
    omniClientUnregisterCallback(uint32_t handle)
    OMNICLIENT_NOEXCEPT;

// ============================
// URL Parsing and Manipulation
// ============================

// Parse a URL into the components pieces
// The full rules are mostly defined by https://tools.ietf.org/html/rfc3986
// Although the Omniverse client library has some special magic for dealing with:
// * malformed URLs
// * raw file paths
// * ov-web URLs
// The returned structure should be freed by omniClientFreeUrl
OMNICLIENT_EXPORT(struct OmniClientUrl*)
    omniClientBreakUrl(char const* url)
    OMNICLIENT_NOEXCEPT;

// Free the URL structure allocated by omniClientBreakUrl
OMNICLIENT_EXPORT(void)
    omniClientFreeUrl(struct OmniClientUrl* url)
    OMNICLIENT_NOEXCEPT;

// This creates a URL from the pieces provided.
// "bufferSize" is an in-out parameter; set it to the size of the buffer before calling this function
// and it will be set to the actual size when the function returns.
// If the size required is more than the size provided, this function returns null, otherwise it returns 'buffer'.
OMNICLIENT_EXPORT(char*)
    omniClientMakeUrl(struct OmniClientUrl const* url, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

// This creates a "file:" URL from a path using the rules defined by: https://en.wikipedia.org/wiki/File_URI_scheme
// This is equivalent to calling:
// OmniClientUrl fileUrl{};
// fileUrl.scheme = "file";
// fileUrl.path = path;
// omniClientMakeUrl(&fileUrl, buffer, bufferSize);
// buffer rules are the same as omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientMakeFileUrl(char const* path, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

// This normalizes a URL by parsing it then recomposing it
// This is equivalent to calling omniClientMakeUrl(omniClientBreakUrl(url));
// buffer rules are the same as omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientNormalizeUrl(char const* url, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

// This combines a URL with an explicit base URL
// The full rules are mostly defined by https://tools.ietf.org/html/rfc3986#section-5
// Although we do some special magic for raw file paths
// Note that trailing slashes matter here!
// ("/a/b/c", "d") = "/a/b/d"
// ("/a/b/c/", "d") = "/a/b/c/d"
// The trailing slash rule makes more sense with real files:
// ("/path/file1.usd", "file2.usd") = "/path/file2.usd"
// ("/path/subdir/", "file.usd") = "/path/subdir/file.usd"
// buffer rules are the same as omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientCombineUrls(char const* baseUrl, char const* otherUrl, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

// This calls omniClientCombineUrls with the URL on the top of the stack (see omniClientPushBaseUrl)
OMNICLIENT_EXPORT(char*)
    omniClientCombineWithBaseUrl(char const* otherUrl, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

// This makes "otherUrl" relative to "baseUrl"
// It attempts to make the shortest URL possible while guaranteeing that you can pass the returned relative URL and
// baseUrl to omniClientComibneUrls and get back the original otherUrl (except that the returned URL is normalized)
// buffer rules are the same as omniClientMakeUrl
// Note that trailing slashes matter here!
// ("/a/b/c", "/a/d") = "../d"
// ("/a/b/c/", "/a/d") = "../../d"
// The reason is because trailing slashes also matter in the baseUrl for omniClientCombineUrls
OMNICLIENT_EXPORT(char*)
    omniClientMakeRelativeUrl(char const* baseUrl, char const* otherUrl, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

// This escapes any control codes (like newline and backspace) and any invalid UTF8 characters
// buffer rules are the same as omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientMakePrintable(char const* string, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

// ==============
// Authentication
// ==============

// Register a callback to provide authentication credentials
// More than one callback can be registered at the same time, they will be called
// newest-to-oldest until one of them returns 'true' indicating that it wants to handle the request
// Returns a handle that you provide to omniClientUnregisterCallback
OMNICLIENT_EXPORT(uint32_t)
    omniClientRegisterAuthCallback(void* userData, OmniClientAuthCallback callback)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(void)
    omniClientSetAuthenticationMessageBoxCallback(void* userData, OmniClientSetAuthenticationMessageBoxCallback callback)
    OMNICLIENT_NOEXCEPT;

// Call this to cancel the current authentication process
// This should only be used in conjection with omniClientSetAuthenticationMessageBoxCallback if the user clicks "Cancel"
OMNICLIENT_EXPORT(void)
    omniClientAuthenticationCancel()
    OMNICLIENT_NOEXCEPT;

// Immediately disconnect from the server specified by this URL
// Any outstanding requests will call their callbacks with eOmniClientResult_ErrorConnection
// Additionally, clear the saved authentication token so future requests to this server will trigger re-authentication
OMNICLIENT_EXPORT(void)
    omniClientSignOut(char const* url)
    OMNICLIENT_NOEXCEPT;

// Attempt to reconnect, even if the previous connection attempt failed
// Automatic connection does not normally try again after failure
// you can call this function to force a retry
OMNICLIENT_EXPORT(void)
    omniClientReconnect(const char* url)
    OMNICLIENT_NOEXCEPT;

// ===============
// Server Querying
// ===============

// Retrieve information about the server for a specified URL
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetServerInfo(char const* url, void* userData, OmniClientGetServerInfoCallback callback)
    OMNICLIENT_NOEXCEPT;

// ====
// Stat
// ====

// Retrieve information about a single item
// This works on both files and folders
// The "relativePath" in the entry is blank
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientStat(char const* url, void* userData, OmniClientStatCallback callback)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientStatSubscribe(char const* url, void* userData, OmniClientStatCallback callback, OmniClientStatSubscribeCallback subscribeCallback)
    OMNICLIENT_NOEXCEPT;

// =======
// Resolve
// =======

// Resolve operates similarly to stat with one major difference:
// You may pass an (ordered) list of paths that are searched if the item is not found.
// The search paths may be a full URL, or a partial URL. If it's a partial URL,
// it will be combined with the base URL (set with omniClientPushBaseUrl)
// For example, given:
//      Base URL: omniverse://sandbox.ov.nvidia.com/project/stage.usd
//      Search Paths:
//          1. materials/
//          2. /materials/
//          3. omniverse://ov-materials/
//          4. file:/c:/materials/
//      Relative Path: wood/oak.mdl
//  This function will search in the following places:
//      1. omniverse://sandbox.ov.nvidia.com/project/wood/oak.mdl
//      2. omniverse://sandbox.ov.nvidia.com/project/materials/wood/oak.mdl
//      3. omniverse://sandbox.ov.nvidia.com/materials/wood/oak.mdl
//      4. omniverse://ov-materials/wood/oak.mdl
//      5. file:/c:/materials/wood/oak.mdl
//  And given the same search paths and URL, but with a base URL of:
//      file:/c:/projects/a/stage.usd
//  This function will search in the following places:
//      1. file:/c:/projects/a/wood/oak.mdl
//      2. file:/c:/projects/a/materials/wood/oak.mdl
//      3. file:/c:/materials/wood/oak.mdl
//      4. omniverse://ov-materials/wood/oak.mdl
//      5. file:/c:/materials/wood/oak.mdl
// If found, "url" will be the FULL URL of the item that was found
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientResolve(char const* relativePath, char const* const* searchPaths, uint32_t numSearchPaths, void* userData, OmniClientResolveCallback callback)
    OMNICLIENT_NOEXCEPT;

OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientResolveSubscribe(char const* relativePath, char const* const* searchPaths, uint32_t numSearchPaths, void* userData, OmniClientResolveCallback callback, OmniClientResolveSubscribeCallback subscribeCallback)
    OMNICLIENT_NOEXCEPT;
// Add a default search path to the list of search paths used by resolve
// New default search paths are added to the top of the stack (meaning they
// will match before older default search paths), but all default search paths
// are underneath the searchPaths explicitly provided to resolve.
// If this searchPath is already in the list, it is moved to the top
OMNICLIENT_EXPORT(void)
    omniClientAddDefaultSearchPath(char const* searchPath)
    OMNICLIENT_NOEXCEPT;

// Remove a default search path from the list of search paths used by resolve
OMNICLIENT_EXPORT(void)
    omniClientRemoveDefaultSearchPath(char const* searchPath)
    OMNICLIENT_NOEXCEPT;

// Retrieve the current list of default search paths
// The 'searchPaths' buffer will be filled with pointers to the default search path strings
// up to 'maxSearchPaths' and this will return the number of default search paths. If the return
// value is > maxSearchPaths then you should call it again with a larger buffer.
// The returned pointers are stable unless/until you add or remove a default search path
OMNICLIENT_EXPORT(uint32_t)
    omniClientGetDefaultSearchPaths(char const** searchPaths, uint32_t maxSearchPaths)
    OMNICLIENT_NOEXCEPT;

// Push a base URL for relative URLs to resolve against
// For example if you push "omniverse://sandbox.ov.nvidia.com/path/" then calling omniList("subpath") will
// return the results of "omniverse://sandbox.ov.nvidia.com/path/subpath". The rules for combining a relative
// URL with a base URLs is defined by https://tools.ietf.org/html/rfc3986 and is the same
// as a web browser would resolve links inside an HTML document.
// ** Note that the context is per-thread! **
// This is so you can load resources on different threads with different base URLs
OMNICLIENT_EXPORT(void)
    omniClientPushBaseUrl(char const* baseUrl)
    OMNICLIENT_NOEXCEPT;

// Pop a base URL from the context stack. If the provided base URL is not on the top of the stack,
// a warning will be printed to the log and this will return false
OMNICLIENT_EXPORT(bool)
    omniClientPopBaseUrl(char const* baseUrl)
    OMNICLIENT_NOEXCEPT;

// ====
// List
// ====

// Retrieve contents of a folder
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientList(char const* url, void* userData, OmniClientListCallback callback)
    OMNICLIENT_NOEXCEPT;

// Subscribe to change notifications for a url
// 'callback' is called once with the initial list
// then 'subscribeCallback' may be called multiple times after that as items change
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientListSubscribe(char const* url, void* userData, OmniClientListCallback callback, OmniClientListSubscribeCallback subscribeCallback)
    OMNICLIENT_NOEXCEPT;

// ======
// Delete
// ======

// Delete something (file, folder, mount, liveFile, channel etc..)
// wildcards are not supported
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientDelete(char const* url, void* userData, OmniClientDeleteCallback callback)
    OMNICLIENT_NOEXCEPT;

// ====
// Copy
// ====

// Copy a thing from 'srcUrl' to 'dstUrl'
// The thing can be anything that supports copying (files, folders, etc..)
// If both src and dst are on the same server, this is done on the server
// Otherwise the file is first downloaded from 'src' then uploaded to 'dst'
// Destination folders will be created as needed.
// Returns eOmniClientResult_ErrorAlreadyExists if "dstUrl" already exists
// Trailing slashes are ignored!
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientCopy(char const* srcUrl, char const* dstUrl, void* userData, OmniClientCopyCallback callback, OmniClientCopyBehavior behavior OMNICLIENT_DEFAULT(eOmniClientCopy_ErrorIfExists))
    OMNICLIENT_NOEXCEPT;

// ======
// Folder
// ======

// Create a folder
// Returns eOmniClientResult_ErrorAlreadyExists if the URL already exists (note that it may not actually be a folder!)
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientCreateFolder(char const* url, void* userData, OmniClientCreateFolderCallback callback)
    OMNICLIENT_NOEXCEPT;

// ====
// File
// ====

// Create a new file, overwriting if it already exists
// This function "takes" the content buffer, by clearing it to 0
// it calls content->free(content->buffer) when it's finished with it (which may be some time in the future)
// FIXME: Support streaming writes
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientWriteFile(char const* url, struct OmniClientContent* content, void* userData, OmniClientWriteFileCallback callback)
    OMNICLIENT_NOEXCEPT;

// Read the entire file
// The content buffer is normally freed after the callback returns. To prevent this, "take" the content
// buffer by clearing it to 0 inside the callback (after copying it somewhere else, of course). You are then
// responsible for calling content->free(content->buffer) when you're finished with it
// FIXME: Support streaming reads
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientReadFile(char const* url, void* userData, OmniClientReadFileCallback callback)
    OMNICLIENT_NOEXCEPT;

// Get a local file name for the URL
// If the URL already points to a local file, it is returned directly
// Otherwise, this downloads the file to a local location and return that location
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetLocalFile(char const* url, void* userData, OmniClientGetLocalFileCallback callback)
    OMNICLIENT_NOEXCEPT;

// =======
// Channel
// =======

// Start listening to a channel
// This also creates the channel, if it doesn't already exist.
// The callback might be called more than once.
// The content buffer is normally freed after the callback returns. To prevent this, "take" the content
// buffer by clearing it to 0 inside the callback (after copying it somewhere else, of course). You are then
// responsible for calling content->free(content->buffer) when you're finished with it
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientJoinChannel(char const* url, void* userData, OmniClientJoinChannelCallback callback)
    OMNICLIENT_NOEXCEPT;

// Send a message to a channel
// joinRequestId is the return value from omniClientJoinChannel
// Sending a message before receiving an event does nothing because nobody will hear the message.
// Returns 0 in that case
// This function takes ownership of the content
// it calls content->free(content->buffer) when it's finished with it (which may be some time in the future)
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientSendMessage(OmniClientRequestId joinRequestId, struct OmniClientContent* content, void* userData, OmniClientSendMessageCallback callback)
    OMNICLIENT_NOEXCEPT;

// ====
// ACLs
// ====

// Retrieve the ACLs for an item
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetAcls(char const* url, void* userData, OmniClientGetAclsCallback callback)
    OMNICLIENT_NOEXCEPT;

// Set ACLs for an item
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientSetAcls(char const* url, uint32_t numEntries, struct OmniClientAclEntry* entries, void* userData, OmniClientSetAclsCallback callback)
    OMNICLIENT_NOEXCEPT;

// =======
// Locking
// =======

// Lock a file so no other clients can modify it
// The file is automatically unlocked when you disconnect
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientLock(char const* url, void* userData, OmniClientLockCallback callback)
    OMNICLIENT_NOEXCEPT;

// Unlock a file so other clients can modify it
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientUnlock(char const* url, void* userData, OmniClientUnlockCallback callback)
    OMNICLIENT_NOEXCEPT;

// ==========
// Versioning
// ==========

// Create a checkpoint for a given URL (which can include a branch, otherwise assume the default branch)
// Returns a query you can combine this with the source url to retrieve this specific checkpoint
// 'force=true' will create a checkpoint even if there are no changes
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientCreateCheckpoint(char const* url, char const* comment, bool force, void* userData, OmniClientCreateCheckpointCallback callback)
    OMNICLIENT_NOEXCEPT;

// Returns a list of checkpoints for a URL
// The "relativePath" in the entries list is a query that you can use with the original URL to access this checkpoint
//
// NOTE: If this function is called after omniClientShutdown, kInvalidRequestId will be returned, and the callback will
// not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientListCheckpoints(char const* url, void* userData, OmniClientListCheckpointsCallback callback)
    OMNICLIENT_NOEXCEPT;

// Breaks a query string into the branch/checkpoint parameters
OMNICLIENT_EXPORT(struct OmniClientBranchAndCheckpoint *)
    omniClientGetBranchAndCheckpointFromQuery(const char* query)
    OMNICLIENT_NOEXCEPT;

// Free the structure returned from omniClientGetBranchAndCheckpointFromQuery
OMNICLIENT_EXPORT(void)
    omniClientFreeBranchAndCheckpoint(struct OmniClientBranchAndCheckpoint *)
    OMNICLIENT_NOEXCEPT;

// This creates a query string from the parameters provided
// "bufferSize" is an in-out parameter; set it to the size of the buffer before calling this function
// and it will be set to the actual size when the function returns.
// If the size required is more than the size provided, this function returns null, otherwise it returns 'buffer'.
OMNICLIENT_EXPORT(char*)
    omniClientMakeQueryFromBranchAndCheckpoint(char const* branch, uint64_t checkpoint, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

#if 0 // Coming soon in MVp2!

// Update a branch to point to a different version
// The source must be a file, not a folder!
// The source could be:
//   - A specific checkpoint in the destination branch or another
//   - The head of another branch, in which case a checkpoint will be automatically created
// The destination branch does not have to exist yet, but if it does exist, a checkpoint will be created for it
//    prior to being updated (so you can restore afterwards)
// In all cases, a new checkpoint will be created in the destination branch after it has been updated with the
//    contents of the source url. This final checkpoint will have the comment provided. The callback will receive
//    a query that can be used to access this final checkpoint.
// Examples:
// omniClientUpdateBranch("omniverse://server/path?BranchA&3", "omniverse://server/path?BranchB", "Updating from BranchA");
// omniClientUpdateBranch("omniverse://server1/path?Branch", "omniverse://server2/path?Branch", "Updating from server1");
// omniClientUpdateBranch("file:/C:/path", "omniverse://server/path?Branch", "Updating from local file");
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientUpdateBranch(char const* srcUrl, char const* dstUrl, char const* comment, void* userData, OmniClientUpdateBranchCallback callback)
    OMNICLIENT_NOEXCEPT;

// Returns a list of branches for a URL
// The "relativePath" in the entries list is a query that you can use with the original URL to access this checkpoint
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientListBranches(char const* url, void* userData, OmniClientListBranchesCallback callback)
    OMNICLIENT_NOEXCEPT;

#endif

// ===================
// Mount Configuration
// ===================

// Todo

// ==========
// User/Group
// ==========

// Todo
