// Copyright (c) 2020-2022, NVIDIA CORPORATION. All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.
//
// clang-format off
#pragma once

//! @file OmniClient.h
//! @brief The main include file for the Omniverse Client Library.

#include "OmniClientAbi.h"
#include "OmniClientVersion.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//! The version of this library. You can pass it to @ref omniClientInitialize to verify
//! that the dll which is loaded matches the header file you compiled against.
const uint64_t kOmniClientVersion = (uint64_t)OMNICLIENT_VERSION_MAJOR << 48 |
                                    (uint64_t)OMNICLIENT_VERSION_MINOR << 32 |
                                    (uint64_t)OMNICLIENT_VERSION_PATCH;

//! @defgroup logging Logging
//! @{

//! Log Level
typedef enum
{
    eOmniClientLogLevel_Debug, ///< Extra chatty
    eOmniClientLogLevel_Verbose, ///< Chatty
    eOmniClientLogLevel_Info, ///< Not a problem
    eOmniClientLogLevel_Warning, ///< Potential problem
    eOmniClientLogLevel_Error, ///< Definite problem

    Count_eOmniClientLogLevel
} OmniClientLogLevel;

//! This is called from a background thread any time the library wants to print a message to the log.
typedef void(OMNICLIENT_ABI* OmniClientLogCallback)
    (char const* threadName, char const* component, OmniClientLogLevel level, char const* message)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Set a log callback function.
//! 
//! This sets a function that will be called when the library wants to write anything to a log.
//! This is the only function that's safe to call before @ref omniClientInitialize.
OMNICLIENT_EXPORT(void)
    omniClientSetLogCallback(OmniClientLogCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Set the log level.
//! 
//! Any messages below this level will not be logged.
OMNICLIENT_EXPORT(void)
    omniClientSetLogLevel(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

//! Retrieve a human readable string for a log level.
//! 
//! For example `omniClientGetLogLevelString(eOmniClientLogLevel_Verbose)` returns `Verbose`
OMNICLIENT_EXPORT(char const*)
    omniClientGetLogLevelString(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

//! Retrieve a single character to represent a log level.
//!
//! For example `omniClientGetLogLevelChar(eOmniClientLogLevel_Verbose)` returns `V`
OMNICLIENT_EXPORT(char)
    omniClientGetLogLevelChar(OmniClientLogLevel level)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup startup Startup & Shutdown
//! @{

//! Perform some one-time initialization.
//!
//! @note It's not strictly necessary to call this, because it will be automatically called
//! the first time any of the other functions are called (except the logging functions). The
//! reason you may want to manually call it are to verify the version in the header and dll
//! match, and also so you have a consistent place where the library is initialized. This can
//! sometimes be important for logging (so you get the initialization messages at the same
//! place in the log every time).
//!
//! @param version Pass @ref kOmniClientVersion to ensure the header matches the dll.
//! @returns false if there was a version mismatch.
OMNICLIENT_EXPORT(bool)
    omniClientInitialize(uint64_t version)
    OMNICLIENT_NOEXCEPT;

//! Terminate all connections and free everything.
//! 
//! Only call this once, when the entire program is terminating.
//!
//! @warning It's not safe to call any functions (not even @ref omniClientInitialize!) after calling this.
OMNICLIENT_EXPORT(void)
    omniClientShutdown()
    OMNICLIENT_NOEXCEPT;

//! Returns a human-readable version string.
//!
//! The format is not guaranteed to remain consistent from one version to another, so please
//! don't try to parse it. Instead, use @ref OMNICLIENT_VERSION_MAJOR @ref OMNICLIENT_VERSION_MINOR
//! and @ref OMNICLIENT_VERSION_PATCH if you are trying to conditionally perform an operation
//! depending on which version of the library is being used.
OMNICLIENT_EXPORT(char const*)
    omniClientGetVersionString()
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup content Content
//! @{

//! Content
struct OmniClientContent
{
    void* buffer; ///< Buffer data
    size_t size; ///< Size of the buffer
    void (*free)(void* buffer); ///< Function to call to free the buffer. Null if this is a refrence.
};

//! Allocate a content buffer with the specified size
//!
//! You can fill in the returned buffer then pass it to the various client library functions such as
//! @ref omniClientWriteFile and @ref omniClientSendMessage which will then take ownership of the buffer
//! and free it when they are finished with it.
OMNICLIENT_EXPORT(struct OmniClientContent) omniClientAllocContent(size_t size) OMNICLIENT_NOEXCEPT;

//! Reference an existing content buffer
//!
//! The difference between calling @ref omniClientAllocContent and this function is referencing a buffer
//! prevents the library from taking ownership of the buffer. Therefore you must ensure the buffer exists
//! at least until the library is finished using it.
OMNICLIENT_EXPORT(struct OmniClientContent) omniClientReferenceContent(void* buffer, size_t size) OMNICLIENT_NOEXCEPT;

//! Attempt to take ownership of a content buffer
//!
//! When you receive a buffer through a callback, such as @ref OmniClientReadFileCallback, you can take ownership
//! of the buffer by calling this function. The library will not free the buffer, so you are required to call
//! @ref omniClientFreeContent when you are finished with it.
//!
//! If it's not posible to take ownership of the buffer (because it was referenced rather than allocated) then
//! this will fall back to calling @ref omniClientCopyContent
OMNICLIENT_EXPORT(struct OmniClientContent) omniClientMoveContent(struct OmniClientContent* content) OMNICLIENT_NOEXCEPT;

//! Copy a content buffer
//!
//! You are required to call @ref omniClientFreeContent when you are finished with it.
OMNICLIENT_EXPORT(struct OmniClientContent) omniClientCopyContent(struct OmniClientContent const* content) OMNICLIENT_NOEXCEPT;

//! Free an allocated content buffer
//!
//! It's safe to call this with a content buffer that was refrenced with @ref omniClientReferenceContent (though the content will
//! obviously not actually be freed). This function also clears the structure (setting size to 0, buffer to nullptr, etc)
OMNICLIENT_EXPORT(void) omniClientFreeContent(struct OmniClientContent* content) OMNICLIENT_NOEXCEPT;

#ifdef __cplusplus
inline OmniClientContent omniClientMoveContent(OmniClientContent& content) noexcept
{
    return omniClientMoveContent(&content);
}
inline OmniClientContent omniClientCopyContent(OmniClientContent const& content) noexcept
{
    return omniClientCopyContent(&content);
}
inline void omniClientFreeContent(OmniClientContent& content) noexcept
{
    omniClientFreeContent(&content);
}
#endif

//! @}

//! @defgroup status Status Callbacks
//! @{

//! Connection Status
typedef enum
{
    eOmniClientConnectionStatus_Connecting, ///< Attempting to connect
    eOmniClientConnectionStatus_Connected, ///< Successfully connected
    eOmniClientConnectionStatus_ConnectError, ///< Error trying to connect
    eOmniClientConnectionStatus_Disconnected, ///< Disconnected

    Count_eOmniClientConnectionStatus
} OmniClientConnectionStatus;

//! This is called any time any connection status changes
//!
//! url does not include path components, for example it could be
//! "omniverse://sandbox.ov.nvidia.com" or "http://nvidia.com"
typedef void
    (OMNICLIENT_ABI* OmniClientConnectionStatusCallback)(void* userData, char const* url, OmniClientConnectionStatus status)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Register a callback to receive connection status updates.
//! 
//! If you are already connected to a server when you call this function,
//! you will receive a connection status callback for that connection.
//! @returns a handle that you can use with @ref omniClientUnregisterCallback
OMNICLIENT_EXPORT(uint32_t)
    omniClientRegisterConnectionStatusCallback(void* userData, OmniClientConnectionStatusCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Retrieve a human readable string for a connection status.
OMNICLIENT_EXPORT(char const*)
    omniClientGetConnectionStatusString(OmniClientConnectionStatus connectionStatus)
    OMNICLIENT_NOEXCEPT;

//! File Status
typedef enum
{
    //! Reading a file
    eOmniClientFileStatus_Reading,

    //! Writing a file
    eOmniClientFileStatus_Writing,

    //! Copying a file. The url is the source url.
    eOmniClientFileStatus_Copying,

    //! Moving a file. The url is the source url.
    eOmniClientFileStatus_Moving,

    //! Deleting a file
    eOmniClientFileStatus_Deleting,

    //! Sending a live update
    eOmniClientFileStatus_LiveUpdateSending,

    //! Received a live update
    eOmniClientFileStatus_LiveUpdateReceived,

    Count_eOmniClientFileStatus
} OmniClientFileStatus;

//! This is called any time any file status changes
typedef void
    (OMNICLIENT_ABI* OmniClientFileStatusCallback)(void* userData, char const* url, OmniClientFileStatus status, int percentage)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Register a callback to receive file transfer updates.
//! 
//! You will receive a callback each time a file transfer starts or stops.
//! This is intended to be used to display loading progress bars and such.
//! @returns a handle that you can use with @ref omniClientUnregisterCallback
OMNICLIENT_EXPORT(uint32_t)
    omniClientRegisterFileStatusCallback(void* userData, OmniClientFileStatusCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Retrieve a human readable string for a file status.
OMNICLIENT_EXPORT(char const*)
    omniClientGetFileStatusString(OmniClientFileStatus fileStatus)
    OMNICLIENT_NOEXCEPT;

//! Unregister a callback.
//!
//! After this function returns, your callback is guaranteed to never be called again.
//! @param handle The handle that was returned from either @ref omniClientRegisterConnectionStatusCallback
//! or @ref omniClientRegisterFileStatusCallback
OMNICLIENT_EXPORT(void)
    omniClientUnregisterCallback(uint32_t handle)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup misc Misc
//! @{

//! Request Id returned from all the asynchronous functions
typedef uint64_t OmniClientRequestId;

//! This is returned if you call an asynchronous function after calling @ref omniClientShutdown
static const OmniClientRequestId kInvalidRequestId = 0;

//! The primary result code returned by the asynchronous functions
typedef enum
{
    //! The operation was successful
    eOmniClientResult_Ok,

    //! Returned only by @ref omniClientLiveRead and indicates that you have the latest version
    eOmniClientResult_OkLatest,

    //! Returned only by @ref omniClientStatSubscribe and @ref omniClientResolveSubscribe functions to indicate that the file wasn't found, but it is being monitored
    //!
    //! A different error (for example @ref eOmniClientResult_ErrorNotFound) indicates that Subscribe could not monitor the file.
    eOmniClientResult_OkNotYetFound,

    //! An unknown error occured while processing the reuest
    eOmniClientResult_Error,

    //! The request failed because the connection to the server was lost (or could not be established in the first place)
    eOmniClientResult_ErrorConnection,

    //! The requested operation is not supported by the server or provider
    eOmniClientResult_ErrorNotSupported,

    //! You don't have access to perform the requested operation
    eOmniClientResult_ErrorAccessDenied,

    //! The operation failed because the specified thing does not exist
    eOmniClientResult_ErrorNotFound,

    //! This is no longer used
    eOmniClientResult_ErrorBadVersion,

    //! You tried to copy or move over a thing that already exists and `behavior` was not OVERWRITE
    eOmniClientResult_ErrorAlreadyExists,

    //! Tried to @ref omniClientCopy or @ref omniClientMove a thing to itself or a child of itself
    eOmniClientResult_ErrorSourceIsDest,

    //! Returned by @ref omniClientListSubscribe and @ref omniClientLiveRead when the thing you were
    //! subscribed to was either deleted or the ACLs were changed so you no longer have access to it.
    eOmniClientResult_ErrorAccessLost,

    //! Returned by @ref omniClientWriteFile when the file you are trying to write is locked by another client
    eOmniClientResult_ErrorLocked,

    //! Returned by HTTP providers when server receives a malformed HTTP request
    eOmniClientResult_ErrorBadRequest,

    Count_eOmniClientResult
} OmniClientResult;

//! Retrieve a human readable string from a result
OMNICLIENT_EXPORT(char const*)
    omniClientGetResultString(OmniClientResult result)
    OMNICLIENT_NOEXCEPT;

//! Stop an active request.
//! 
//! Your callback will not be called after this function returns.
//! If a callback is in process @ref omniClientStop will wait to return until the callback completes.
//! 
//! @warning Don't hold mutexes that may also be used by any functions called by callbacks of *requestId*
//! as this can lead to deadlocks.
OMNICLIENT_EXPORT(void)
    omniClientStop(OmniClientRequestId requestId)
    OMNICLIENT_NOEXCEPT;

//! Wait for a request to complete.
//! 
//! For subscription requests (like @ref omniClientListSubscribe or @ref omniClientJoinChannel) this
//! will return after the initial message is received
OMNICLIENT_EXPORT(void)
    omniClientWait(OmniClientRequestId requestId)
    OMNICLIENT_NOEXCEPT;

//! Wait for a request to complete, but with a timeout.
//! 
//! Same as @ref omniClientWait, but with a timeout in milliseconds
//! 
//! @returns false if the wait timed out before the request finished
OMNICLIENT_EXPORT(bool)
    omniClientWaitFor(OmniClientRequestId requestId, uint64_t milliseconds)
    OMNICLIENT_NOEXCEPT;

//! Redirect a URL to a different location
//!
//! For example alias("home:", "C:\Users\brianh\")
//! Call it with dst=null to remove an alias
OMNICLIENT_EXPORT(void)
    omniClientSetAlias(char const* src, char const* dst)
    OMNICLIENT_NOEXCEPT;

//! Get access to the reactor.
//!
//! Use idl.cpp reactor.h and reactor.hh for the types definitions.
OMNICLIENT_EXPORT(struct OmniIDLCPPInitializerReactor*)
    omniClientGetReactor()
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup bookmarks Bookmarks
//! @{

//! Add a URL to the list of bookmarks
OMNICLIENT_EXPORT(void)
    omniClientAddBookmark(char const* name, char const* url)
    OMNICLIENT_NOEXCEPT;

//! Remove a URL from the list of bookmarks
OMNICLIENT_EXPORT(void)
    omniClientRemoveBookmark(char const* name)
    OMNICLIENT_NOEXCEPT;

//! A bookmark
struct OmniClientBookmark
{
    char const* name;     //!< The name of the bookmark
    char const* url;      //!< The bookmark URL
};

//! This is called with the list of bookmarks
typedef void
    (OMNICLIENT_ABI* OmniClientBookmarkCallback)(void* userData, struct OmniClientBookmark const* bookmarks, size_t numBookmarks)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Register a callback to receive the list of bookmarks
//! 
//! The callback is called once with the current list of bookmarks, and
//! again any time the bookmark list is changed (by any application, including this one)
//!
//! Call @ref omniClientStop with the returned handle to stop receiving updated bookmark lists
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientListBookmarks(void* userData, OmniClientBookmarkCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup url URL Parsing and Manipulation
//! @{

//! A URL broken into the component pieces
//!
//! A fully composed URL takes the format `scheme://user@host:port/path?query#fragment`
//! Note that "null" is different from blank. Null means the component is missing, blank
//! means it exists but has no value.
//! 
//!  See also https://en.wikipedia.org/wiki/Uniform_Resource_Identifier#Generic_syntax
//!
//!  @note omniverse: urls IGNORE the "user" component!
struct OmniClientUrl
{
    char const* scheme;     //!< The part of the URL before the first colon.
    char const* user;       //!< The part of the URL to indicate the user to sign in as.
    char const* host;       //!< The part of the URL indicating the host name or IP address to connect to.
    char const* port;       //!< The part of the URL indicating the port to connect to.
    char const* path;       //!< The part of the URL indicating the path of the item on the server. This is percent-decoded.
    char const* query;      //!< The part of the URL containing the query parameter. This is percent-decoded.
    char const* fragment;   //!< The part of the URL containing the fragment parameter. This is percent-decoded.
    bool isRaw;             //!< True if this is a "raw" URL such as "C:\\file". Setting this to true prevents @ref omniClientMakeUrl from percent-encoding the path.
};

//! Parse a URL into the components pieces
//! 
//! The full rules are mostly defined by https://tools.ietf.org/html/rfc3986
//! Although the Omniverse client library has some special magic for dealing with:
//! * malformed URLs
//! * raw file paths
//! * ov-web URLs
//! The returned structure should be freed by @ref omniClientFreeUrl
OMNICLIENT_EXPORT(struct OmniClientUrl*)
    omniClientBreakUrl(char const* url)
    OMNICLIENT_NOEXCEPT;

//! This version of @ref omniClientBreakUrl behaves slightly differently for raw file paths
//! 
//! This assumes the URL is either a full URL (starting with a scheme such as "http:") or a raw
//! local file path such as "C:\path" (Windows) or "/path" (Linux).
//! 
//! This affects percent-encoding for relative paths such as "test%20test", which will
//! be decoded to "test test" by @ref omniClientBreakUrl, but left as-is by omniClientBreakUrlAbsolute
OMNICLIENT_EXPORT(struct OmniClientUrl*)
    omniClientBreakUrlAbsolute(char const* url)
    OMNICLIENT_NOEXCEPT;

//! Free the URL structure allocated by @ref omniClientBreakUrl or @ref omniClientBreakUrlAbsolute
OMNICLIENT_EXPORT(void)
    omniClientFreeUrl(struct OmniClientUrl* url)
    OMNICLIENT_NOEXCEPT;

//! This creates a URL from the pieces provided.
//! 
//! "bufferSize" is an in-out parameter; set it to the size of the buffer before calling this function
//! and it will be set to the actual size when the function returns.
//! 
//! If the size required is more than the size provided, this function returns null, otherwise it returns 'buffer'.
OMNICLIENT_EXPORT(char*)
    omniClientMakeUrl(struct OmniClientUrl const* url, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! This creates a "file:" URL from a path
//!
//! This uses the rules defined by: https://en.wikipedia.org/wiki/File_URI_scheme
//! 
//! This is equivalent to calling:
//! @code{.c}
//! OmniClientUrl fileUrl{};
//! fileUrl.scheme = "file";
//! fileUrl.path = path;
//! omniClientMakeUrl(&fileUrl, buffer, bufferSize);
//! @endcode
//!
//! buffer rules are the same as @ref omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientMakeFileUrl(char const* path, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! This normalizes a URL by parsing it then recomposing it
//! 
//! This is equivalent to calling @ref omniClientBreakUrl then @ref omniClientMakeUrl;
//!
//! buffer rules are the same as @ref omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientNormalizeUrl(char const* url, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! This combines a URL with an explicit base URL
//! 
//! The full rules are mostly defined by https://tools.ietf.org/html/rfc3986#section-5
//! Although we do some special magic for raw file paths
//! Note that trailing slashes matter here!
//! ("/a/b/c", "d") = "/a/b/d"
//! ("/a/b/c/", "d") = "/a/b/c/d"
//! The trailing slash rule makes more sense with real files:
//! ("/path/file1.usd", "file2.usd") = "/path/file2.usd"
//! ("/path/subdir/", "file.usd") = "/path/subdir/file.usd"
//! buffer rules are the same as @ref omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientCombineUrls(char const* baseUrl, char const* otherUrl, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! This calls @ref omniClientCombineUrls with the URL on the top of the stack
//!
//! @see omniClientPushBaseUrl
OMNICLIENT_EXPORT(char*)
    omniClientCombineWithBaseUrl(char const* otherUrl, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! This calls @ref omniClientCombineUrls with the URL on the top of the stack
//!
//! It differs from @ref omniClientCombineWithBaseUrl only in the return value.
//! Call @ref omniClientFreeUrl to free the returned structure.
//!
//! @see omniClientPushBaseUrl
OMNICLIENT_EXPORT(struct OmniClientUrl*)
    omniClientCombineWithBaseUrl2(char const* otherUrl)
    OMNICLIENT_NOEXCEPT;

//! This makes "otherUrl" relative to "baseUrl"
//! 
//! It attempts to make the shortest URL possible while guaranteeing that you can pass the returned relative URL and
//! baseUrl to @ref omniClientCombineUrls and get back the original otherUrl (except that the returned URL is normalized)
//! buffer rules are the same as @ref omniClientMakeUrl
//! Note that trailing slashes matter here!
//! ("/a/b/c", "/a/d") = "../d"
//! ("/a/b/c/", "/a/d") = "../../d"
//! The reason is because trailing slashes also matter in the baseUrl for @ref omniClientCombineUrls
OMNICLIENT_EXPORT(char*)
    omniClientMakeRelativeUrl(char const* baseUrl, char const* otherUrl, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! This makes a URL safe for printing in a UI or to a console window
//!
//! The input is expected to be a full, potentially with percent-encoded, URL.
//! 
//! It percent-encodes any ASCII control characters or invalid UTF-8 characters.
//! It percent-decodes any valid UTF-8 characters, and ASCII characters that are not reserved by the URL specification.
//! 
//! buffer rules are the same as @ref omniClientMakeUrl
OMNICLIENT_EXPORT(char*)
    omniClientMakePrintable(char const* string, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup auth Authentication
//! @{

//! Credentials to sign in with
//!
//! Set either "abort", "token", or "username" & "password" if you return true from your callback
struct OmniClientCredentials
{
    bool abort;                         //!< Set to true to abort this connection request
    struct OmniClientContent token;     //!< Set to an access token retrieved from the authentication service
    struct OmniClientContent username;  //!< Set to an explicit username to sign in
    struct OmniClientContent password;  //!< Specify a password to use with username
};

//! This allows you to provide credentials used to sign in to a server.
typedef bool
    (OMNICLIENT_ABI* OmniClientAuthCallback)(void* userData, char const* prefix, struct OmniClientCredentials * credentials)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Register a callback to provide authentication credentials
//! 
//! More than one callback can be registered at the same time, they will be called
//! newest-to-oldest until one of them returns 'true' indicating that it wants to handle the request
//! Returns a handle that you provide to @ref omniClientUnregisterCallback
//! 
//! The authentication callback receives the "prefix" of the server it's trying to connect to, which could be of the
//! form "omniverse://server:port" "http://server" "file://server" etc.. You can use @ref omniClientBreakUrl to
//! Parse the prefix into scheme, host, and port.
//! Return false to fall back to the default credentials (for example because this is not a server you care about)
//! Return true if you have filled in the credentials
//! Either:
//! Set credentials->abort to true to stop the sign-in process
//! OR set credentials->token
//! OR set credentials->username and credentials->password
OMNICLIENT_EXPORT(uint32_t)
    omniClientRegisterAuthCallback(void* userData, OmniClientAuthCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called when the library needs to continue authentication in a web browser
typedef void
    (OMNICLIENT_ABI* OmniClientAuthenticationMessageBoxCallback)(void* userData, bool show, const char* server, uint32_t authHandle)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Set a callback which is called instead of showing the "Please sign in using your browser" dialog
OMNICLIENT_EXPORT(void)
    omniClientSetAuthenticationMessageBoxCallback(void* userData, OmniClientAuthenticationMessageBoxCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Call this to cancel the current authentication process
//! 
//! This should only be used in conjection with @ref omniClientSetAuthenticationMessageBoxCallback if the user clicks "Cancel"
//! authHandle is the same value passed to @ref OmniClientAuthenticationMessageBoxCallback
OMNICLIENT_EXPORT(void)
    omniClientAuthenticationCancel(uint32_t authHandle)
    OMNICLIENT_NOEXCEPT;

//! Immediately disconnect from the server specified by this URL
//! 
//! Any outstanding requests will call their callbacks with `eOmniClientResult_ErrorConnection`
//! Additionally, clear the saved authentication token so future requests to this server will trigger re-authentication
OMNICLIENT_EXPORT(void)
    omniClientSignOut(char const* url)
    OMNICLIENT_NOEXCEPT;

//! Attempt to reconnect, even if the previous connection attempt failed
//! 
//! Automatic connection does not normally try again after failure
//! you can call this function to force a retry
OMNICLIENT_EXPORT(void)
    omniClientReconnect(const char* url)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup query Server Querying
//! @{

//! Server Info
struct OmniClientServerInfo
{
    char const* version;        //!< The version of software the server is running
    char const* username;       //!< The username you are signed in as
    char const* authToken;      //!< The authentication token you are using (this should no longer be used)
    bool cacheEnabled;          //!< True if the local nucleus cache is enabled for this server
    bool omniObjectsEnabled;    //!< True if omni-objects are enabled on this server
    bool checkpointsEnabled;    //!< True if checkpoints are enabled on this server
};

//! This is called with the results of @ref omniClientGetServerInfo
typedef void
    (OMNICLIENT_ABI* OmniClientGetServerInfoCallback)(void* userData, OmniClientResult result, struct OmniClientServerInfo const * info)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Retrieve information about the server for a specified URL
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetServerInfo(char const* url, void* userData, OmniClientGetServerInfoCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup stat Stat
//! @{

//! @private Macro to help define bit fields
#define BIT(x) (1 << (x - 1))

//! Access flags
typedef enum
{
    //! Can read this thing
    fOmniClientAccess_Read = BIT(1),

    //! Can write to this thing
    fOmniClientAccess_Write = BIT(2),

    //! Can change ACLs for this thing
    fOmniClientAccess_Admin = BIT(3),

    //! read + write + admin
    fOmniClientAccess_Full = fOmniClientAccess_Admin | fOmniClientAccess_Write | fOmniClientAccess_Read

} OmniClientAccessFlags;

//! Item flags
typedef enum
{
    //! You can call omniClientReadFile on this
    //!
    //! @note: ACLs may still prevent you from reading it
    fOmniClientItem_ReadableFile = BIT(1),

    //!You can call omniClientWriteFile on this
    //!
    //! @note ACLs may still prevent you from writing it
    fOmniClientItem_WriteableFile = BIT(2),

    //! This thing can contain other things (a folder-like thing)
    fOmniClientItem_CanHaveChildren = BIT(3),

    //! This thing does not have any children.
    //! 
    //! The lack of this flag does not mean it does have children!
    //! Sometimes we are not sure if it has children until you attempt to list the children.
    //! This is only intended to be used for UI elements to hide the "expand" button if we
    //! are sure it does not have any children.
    fOmniClientItem_DoesNotHaveChildren = BIT(4),

    //! This thing is the root of a mount point
    fOmniClientItem_IsMount = BIT(5),

    //! This thing is located inside a mounted folder
    fOmniClientItem_IsInsideMount = BIT(6),

    //! This thing supports live updates
    fOmniClientItem_CanLiveUpdate = BIT(7),

    //! This thing is in omni-object format
    //! 
    //! You must use @ref omniClientLiveRead to read it and @ref omniClientLiveUpdate to update it
    fOmniClientItem_IsOmniObject = BIT(8),

    //! You can call omniClientJoinChannel on this
    fOmniClientItem_IsChannel = BIT(9),

    //! This item is a checkpoint
    fOmniClientItem_IsCheckpointed = BIT(10)
} OmniClientItemFlags;

#undef BIT

//! List Entry
struct OmniClientListEntry
{
    //! The relative path for this item
    //! 
    //! The exact meaning depends on the function being called
    //! for @ref omniClientList, it's the name of the item
    //! for @ref omniClientListCheckpoints, it's the "query" part of the URL
    const char* relativePath;

    //! YOUR access level
    //! Some combination of @ref OmniClientAccessFlags
    uint32_t access;

    //! Information about this item
    //!
    //! Some combination of @ref OmniClientItemFlags
    uint32_t flags;

    //! For files, the size in bytes. Undefined for other types.
    uint64_t size;

    //! Nanoseconds since the Unix epoch (1 January 1970) of the last time the file was modified
    uint64_t modifiedTimeNs;

    //! Nanoseconds since the Unix epoch (1 January 1970) of when the file was created
    uint64_t createdTimeNs;

    //! User name of the last person to modify it
    //! @note Not all providers support this, so it may be null
    const char* modifiedBy;
    //! User name of the person that created it
    //! @note Not all providers support this, so it may be null
    const char* createdBy;
    //! Provider-specific version
    //! @details Might not be an always incrementing number (could be a hash, for example)
    //! @note Not all providers support this, so it may be null
    const char* version;
    //! Provider specific file hash
    //! @note Not all providers support this, so it may be null
    const char* hash;
    //! Provider specific comment
    //! @details This will only be set for @ref omniClientListCheckpoints
    //! @note Not all providers support this, so it may be null
    const char* comment;
};

//! This is called with the results of @ref omniClientStat or @ref omniClientStatSubscribe
typedef void
    (OMNICLIENT_ABI* OmniClientStatCallback)(void* userData, OmniClientResult result, struct OmniClientListEntry const* entry)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Retrieve information about a single item
//! 
//! This works on both files and folders
//! The "relativePath" in the entry is blank
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientStat(char const* url, void* userData, OmniClientStatCallback callback)
    OMNICLIENT_NOEXCEPT;

//! List Subscribe Event
typedef enum
{
    eOmniClientListEvent_Unknown,   //!< Unknown event
    eOmniClientListEvent_Created,   //!< An item was created
    eOmniClientListEvent_Updated,   //!< An item (contents) were updated
    eOmniClientListEvent_Deleted,   //!< An item was deleted
    eOmniClientListEvent_Metadata,  //!< An item's metadata was changed
    eOmniClientListEvent_Locked,    //!< A file was locked
    eOmniClientListEvent_Unlocked,  //!< A file was unlocked

    Count_eOmniClientListEvent
} OmniClientListEvent;

//! This is called any time an item you've subscribed to with @ref omniClientStatSubscribe changes.
typedef void
    (OMNICLIENT_ABI* OmniClientStatSubscribeCallback)(void* userData, OmniClientResult result, OmniClientListEvent listEvent, struct OmniClientListEntry const* entry)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Retrieve information about a single item, and subscribe to future changes.
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientStatSubscribe(char const* url, void* userData, OmniClientStatCallback callback, OmniClientStatSubscribeCallback subscribeCallback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup resolve Resolve
//! @{

//! This is called with the result of @ref omniClientResolve or @ref omniClientResolveSubscribe
typedef void
    (OMNICLIENT_ABI* OmniClientResolveCallback)(void* userData, OmniClientResult result, struct OmniClientListEntry const* entry, char const* url)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Resolve operates similarly to stat with one major difference.
//!
//! You may pass an (ordered) list of paths that are searched if the item is not found.
//! The search paths may be a full URL, or a partial URL. If it's a partial URL,
//! it will be combined with the base URL (set with omniClientPushBaseUrl)
//! 
//! For example, given:
//!   * Base URL: omniverse://sandbox.ov.nvidia.com/project/stage.usd
//!   * Search Paths:
//!      1. materials/
//!      2. /materials/
//!      3. omniverse://ov-materials/
//!      4. file:/c:/materials/
//!   * Relative Path: wood/oak.mdl
//! 
//! This function will search in the following places:
//!      1. omniverse://sandbox.ov.nvidia.com/project/wood/oak.mdl
//!      2. omniverse://sandbox.ov.nvidia.com/project/materials/wood/oak.mdl
//!      3. omniverse://sandbox.ov.nvidia.com/materials/wood/oak.mdl
//!      4. omniverse://ov-materials/wood/oak.mdl
//!      5. file:/c:/materials/wood/oak.mdl
//! 
//!  And given the same search paths and URL, but with a base URL of:
//!      file:/c:/projects/a/stage.usd
//! 
//!  This function will search in the following places:
//!      1. file:/c:/projects/a/wood/oak.mdl
//!      2. file:/c:/projects/a/materials/wood/oak.mdl
//!      3. file:/c:/materials/wood/oak.mdl
//!      4. omniverse://ov-materials/wood/oak.mdl
//!      5. file:/c:/materials/wood/oak.mdl
//! 
//! If found, "url" will be the FULL URL of the item that was found
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientResolve(char const* relativePath, char const* const* searchPaths, uint32_t numSearchPaths, void* userData, OmniClientResolveCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called any time an item you've subscribed to with @ref omniClientResolveSubscribe changes.
typedef void
    (OMNICLIENT_ABI* OmniClientResolveSubscribeCallback)(void* userData, OmniClientResult result, OmniClientListEvent listEvent, struct OmniClientListEntry const* entry, char const* url)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Resolve an item, and subscribe to future changes.
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientResolveSubscribe(char const* relativePath, char const* const* searchPaths, uint32_t numSearchPaths, void* userData, OmniClientResolveCallback callback, OmniClientResolveSubscribeCallback subscribeCallback)
    OMNICLIENT_NOEXCEPT;

//! Add a default search path to the list of search paths used by resolve
//! 
//! New default search paths are added to the top of the stack (meaning they
//! will match before older default search paths), but all default search paths
//! are underneath the searchPaths explicitly provided to resolve.
//! 
//! If this searchPath is already in the list, it is moved to the top
OMNICLIENT_EXPORT(void)
    omniClientAddDefaultSearchPath(char const* searchPath)
    OMNICLIENT_NOEXCEPT;

//! Remove a default search path from the list of search paths used by resolve
OMNICLIENT_EXPORT(void)
    omniClientRemoveDefaultSearchPath(char const* searchPath)
    OMNICLIENT_NOEXCEPT;

//! Retrieve the current list of default search paths
//! 
//! The 'searchPaths' buffer will be filled with pointers to the default search path strings
//! up to 'maxSearchPaths' and this will return the number of default search paths. If the return
//! value is > maxSearchPaths then you should call it again with a larger buffer.
//! The returned pointers are stable unless/until you add or remove a default search path
OMNICLIENT_EXPORT(uint32_t)
    omniClientGetDefaultSearchPaths(char const** searchPaths, uint32_t maxSearchPaths)
    OMNICLIENT_NOEXCEPT;

//! Push a base URL for relative URLs to resolve against
//! 
//! For example if you push "omniverse://sandbox.ov.nvidia.com/path/" then calling omniList("subpath") will
//! return the results of "omniverse://sandbox.ov.nvidia.com/path/subpath". The rules for combining a relative
//! URL with a base URLs is defined by https://tools.ietf.org/html/rfc3986 and is the same
//! as a web browser would resolve links inside an HTML document.
//! ** Note that the context is per-thread! **
//! This is so you can load resources on different threads with different base URLs
OMNICLIENT_EXPORT(void)
    omniClientPushBaseUrl(char const* baseUrl)
    OMNICLIENT_NOEXCEPT;

//! Pop a base URL from the context stack
//! 
//! If the provided base URL is not on the top of the stack,
//! a warning will be printed to the log and this will return false
OMNICLIENT_EXPORT(bool)
    omniClientPopBaseUrl(char const* baseUrl)
    OMNICLIENT_NOEXCEPT;

//! Returns the top of the base URL stack
//! 
//! Returns nullptr if the stack is empty
OMNICLIENT_EXPORT(char const*)
    omniClientGetBaseUrl()
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup list List
//! @{

//! This is called with the results of @ref omniClientList and @ref omniClientListSubscribe
typedef void
    (OMNICLIENT_ABI* OmniClientListCallback)(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientListEntry const* entries)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Retrieve contents of a folder
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientList(char const* url, void* userData, OmniClientListCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called any time an item you've subscribed to with @ref omniClientListSubscribe changes.
typedef void
    (OMNICLIENT_ABI* OmniClientListSubscribeCallback)(void* userData, OmniClientResult result, OmniClientListEvent listEvent, struct OmniClientListEntry const* entry)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Subscribe to change notifications for a url
//! 
//! 'callback' is called once with the initial list
//! then 'subscribeCallback' may be called multiple times after that as items change
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientListSubscribe(char const* url, void* userData, OmniClientListCallback callback, OmniClientListSubscribeCallback subscribeCallback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup delete Delete
//! @{

//! This is called with the result of @ref omniClientDelete
typedef void
    (OMNICLIENT_ABI* OmniClientDeleteCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Delete something (file, folder, mount, live object, channel etc..)
//! 
//! Deleting a folder performs a recursive delete
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientDelete(char const* url, void* userData, OmniClientDeleteCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup copy Copy
//! @{

//! This is called with the result of @ref omniClientCopy
typedef void
    (OMNICLIENT_ABI* OmniClientCopyCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Copy Behavior
typedef enum
{
    eOmniClientCopy_ErrorIfExists, ///< Stops copying and issues an error if a file exists.
    eOmniClientCopy_Overwrite, ///< Overwrites any destination file(s) with the source file.
} OmniClientCopyBehavior;

//! Copy a thing from 'srcUrl' to 'dstUrl'
//! 
//! The thing can be anything that supports copying (files, folders, etc..)
//! 
//! If both src and dst are on the same server, this is done on the server
//! Otherwise the file is first downloaded from 'src' then uploaded to 'dst'
//! 
//! Destination folders will be created as needed.
//! 
//! Returns `eOmniClientResult_ErrorAlreadyExists` if "dstUrl" already exists
//! unless you specify 'behavior' as eOmniClientCopy_Overwrite
//! 
//! Trailing slashes are ignored!
//! 
//! The message parameter is applied to the atomic checkpoint created of dstUrl after the copy is complete.
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientCopy(char const* srcUrl, char const* dstUrl, void* userData, OmniClientCopyCallback callback, OmniClientCopyBehavior behavior OMNICLIENT_DEFAULT(eOmniClientCopy_ErrorIfExists), const char* message OMNICLIENT_DEFAULT(nullptr))
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup move Move
//! @{

//! This is called with the result of @ref omniClientMove
typedef void
    (OMNICLIENT_ABI* OmniClientMoveCallback)(void* userData, OmniClientResult result, bool copied)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Move a thing from 'srcUrl' to 'dstUrl'
//! 
//! The thing can be anything that supports moving (files, folders, etc..)
//! 
//! If both src and dst are on the same server, this is done on the server.
//! Otherwise, it is first copied from srcUrl to dstUrl, then deleted from srcUrl
//! Note it is possible for the copy to succeed and the delete to fail. In this case
//! the result will be the error code from the delete but 'copied' will be true.
//! 
//! If the result is 'Ok' but 'copied' is false, that means the move was done entirely
//! on the server, so no local copy had to be made.
//! 
//! Destination folders will be created as needed.
//! Returns `eOmniClientResult_ErrorAlreadyExists` if 'dstUrl' already exists
//! unless you specify 'behavior' as `eOmniClientCopy_Overwrite`
//! 
//! Trailing slashes are ignored!
//! 
//! The message parameter is applied to the atomic checkpoint created of dstUrl after the move is complete.
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientMove(char const* srcUrl, char const* dstUrl, void* userData, OmniClientMoveCallback callback, OmniClientCopyBehavior behavior OMNICLIENT_DEFAULT(eOmniClientCopy_ErrorIfExists), const char* message OMNICLIENT_DEFAULT(nullptr))
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup folder Folders
//! @{

//! This is called with the result of @ref omniClientCreateFolder
typedef void
    (OMNICLIENT_ABI* OmniClientCreateFolderCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Create a folder
//! 
//! Returns `eOmniClientResult_ErrorAlreadyExists` if the URL already exists (note that it may not actually be a folder!)
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientCreateFolder(char const* url, void* userData, OmniClientCreateFolderCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup file Files
//! @{

//! This is called with the result of @ref omniClientWriteFile
typedef void
    (OMNICLIENT_ABI* OmniClientWriteFileCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Create a new file, overwriting if it already exists
//! 
//! This function takes ownership of the content buffer, and frees it when it's finished with it
//! (which may be some time in the future)
//! 
//! The message parameter is applied to the atomic checkpoint created after writing the file.
//! 
//! FIXME: Support streaming writes
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientWriteFile(char const* url, struct OmniClientContent* content, void* userData, OmniClientWriteFileCallback callback, const char* message OMNICLIENT_DEFAULT(nullptr))
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientReadFile
typedef void
    (OMNICLIENT_ABI* OmniClientReadFileCallback)(void* userData, OmniClientResult result, char const* version, struct OmniClientContent* content)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Read the entire file
//! 
//! The content buffer is normally freed after the callback returns. To prevent this, take ownership of the content
//! buffer by calling omniClientMoveContent. You are then responsible for calling @ref omniClientFreeContent when you're finished
//! with it. For example:
//! @code{c}
//! OmniClientContent myContent = omniClientMoveContent(*content);
//! omniClientFreeContent(myContent);
//! @endcode
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientReadFile(char const* url, void* userData, OmniClientReadFileCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientGetLocalFile
typedef void
    (OMNICLIENT_ABI* OmniClientGetLocalFileCallback)(void* userData, OmniClientResult result, char const* localFilePath)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Get a local file name for the URL
//! 
//! If the URL already points to a local file, it is returned directly
//! Otherwise, this downloads the file to a local location and return that location
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetLocalFile(char const* url, void* userData, OmniClientGetLocalFileCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup channels Channels
//! @{

//! Channel Event
typedef enum
{
    eOmniClientChannelEvent_Error, //< An unknown error occured
    eOmniClientChannelEvent_Message, //< Someone sent a message
    eOmniClientChannelEvent_Hello, //< You joined a channel that someone else was already in, and they said hello.
    eOmniClientChannelEvent_Join, //< Someone joined the channel
    eOmniClientChannelEvent_Left, //< Someone left the channel (as of Nucleus 114, the server does not appear to send these)
    eOmniClientChannelEvent_Deleted, //< Someone deleted the channel or changed ACLs so you no longer have access.

    Count_eOmniClientChannelEvent
} OmniClientChannelEvent;

//! This is called with the result of @ref omniClientJoinChannel
typedef void
    (OMNICLIENT_ABI* OmniClientJoinChannelCallback)(void* userData, OmniClientResult result, OmniClientChannelEvent eventType, char const* from, struct OmniClientContent* content)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Start listening to a channel
//! 
//! This also creates the channel, if it doesn't already exist.
//! The callback might be called more than once.
//! The content buffer is normally freed after the callback returns. To prevent this, "take" the content
//! buffer by clearing it to 0 inside the callback (after copying it somewhere else, of course). You are then
//! responsible for calling content->free(content->buffer) when you're finished with it
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientJoinChannel(char const* url, void* userData, OmniClientJoinChannelCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientSendMessage
typedef void
    (OMNICLIENT_ABI* OmniClientSendMessageCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Send a message to a channel
//! 
//! joinRequestId is the return value from @ref omniClientJoinChannel
//! Sending a message before receiving an event does nothing because nobody will hear the message.
//! Returns 0 in that case
//! This function takes ownership of the content
//! it calls content->free(content->buffer) when it's finished with it (which may be some time in the future)
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientSendMessage(OmniClientRequestId joinRequestId, struct OmniClientContent* content, void* userData, OmniClientSendMessageCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup acls ACLs
//! @{

//! ACL Entry
struct OmniClientAclEntry
{
    //! The name of the user or group
    const char* name;
    //! Some combination of @ref OmniClientAccessFlags that apply to this user or group
    uint32_t access;
};

//! This is called with the result of @ref omniClientGetAcls
typedef void
    (OMNICLIENT_ABI* OmniClientGetAclsCallback)(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientAclEntry* entries)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Retrieve the ACLs for an item
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetAcls(char const* url, void* userData, OmniClientGetAclsCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientSetAcls
typedef void
    (OMNICLIENT_ABI* OmniClientSetAclsCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Set ACLs for an item
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientSetAcls(char const* url, uint32_t numEntries, struct OmniClientAclEntry* entries, void* userData, OmniClientSetAclsCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup lock Locking
//! @{

//! This is called with the result of @ref omniClientLock
typedef void
    (OMNICLIENT_ABI* OmniClientLockCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Lock a file so no other clients can modify it
//! 
//! The file is automatically unlocked when you disconnect
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientLock(char const* url, void* userData, OmniClientLockCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientUnlock
typedef void
    (OMNICLIENT_ABI* OmniClientUnlockCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Unlock a file so other clients can modify it
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientUnlock(char const* url, void* userData, OmniClientUnlockCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup version Versioning
//! @{

//! This is called with the result of @ref omniClientCreateCheckpoint
typedef void
    (OMNICLIENT_ABI* OmniClientCreateCheckpointCallback)(void* userData, OmniClientResult result, char const * checkpointQuery)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Create a checkpoint for a given URL (which can include a branch, otherwise assume the default branch)
//! 
//! Returns a query you can combine this with the source url to retrieve this specific checkpoint
//! 'force=true' will create a checkpoint even if there are no changes
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientCreateCheckpoint(char const* url, char const* comment, bool force, void* userData, OmniClientCreateCheckpointCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientListCheckpoints
typedef void
    (OMNICLIENT_ABI* OmniClientListCheckpointsCallback)(void* userData, OmniClientResult result, uint32_t numEntries, struct OmniClientListEntry const* entries)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Returns a list of checkpoints for a URL
//! 
//! The "relativePath" in the entries list is a query that you can use with the original URL to access this checkpoint. You can pass
//! relativePath to @ref omniClientGetBranchAndCheckpointFromQuery in order to parse it into the branch and checkpoint.
//! 
//! @note If this function is called after @ref omniClientShutdown, kInvalidRequestId will be returned, and the callback will not be called.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientListCheckpoints(char const* url, void* userData, OmniClientListCheckpointsCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Branch & Checkpoint
struct OmniClientBranchAndCheckpoint
{
    char const* branch;     //!< Branch
    uint64_t checkpoint;    //!< Checkpoint
};

//! Breaks a query string into the branch/checkpoint parameters
//!
//! Query could be either the expanded "branch=my_branch&checkpoint=30" or shortened "my_branch&30"
OMNICLIENT_EXPORT(struct OmniClientBranchAndCheckpoint *)
    omniClientGetBranchAndCheckpointFromQuery(const char* query)
    OMNICLIENT_NOEXCEPT;

//! Free the structure returned from @ref omniClientGetBranchAndCheckpointFromQuery
OMNICLIENT_EXPORT(void)
    omniClientFreeBranchAndCheckpoint(struct OmniClientBranchAndCheckpoint *)
    OMNICLIENT_NOEXCEPT;

//! This creates a query string from the parameters provided
//! 
//! "bufferSize" is an in-out parameter; set it to the size of the buffer before calling this function
//! and it will be set to the actual size when the function returns.
//! If the size required is more than the size provided, this function returns null, otherwise it returns 'buffer'.
OMNICLIENT_EXPORT(char*)
    omniClientMakeQueryFromBranchAndCheckpoint(char const* branch, uint64_t checkpoint, char* buffer, size_t* bufferSize)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup user User/Group
//! @{

//! This is called with the result of @ref omniClientGetGroups
typedef void
    (OMNICLIENT_ABI* OmniClientGetGroupsCallback)(void* userData, OmniClientResult result, uint64_t count, const char** groups)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Returns a list of all groups registered with the server.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetGroups(char const* url, void* userData, OmniClientGetGroupsCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientGetGroupUsers
typedef void
    (OMNICLIENT_ABI* OmniClientGetGroupUsersCallback)(void* userData, OmniClientResult result, uint64_t count, const char** users)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Returns a list of users associated with a group.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetGroupUsers(char const* url, const char* group, void* userData, OmniClientGetGroupUsersCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientCreateGroup
typedef void
    (OMNICLIENT_ABI* OmniClientCreateGroupCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Create a group on server.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientCreateGroup(char const* url, const char* group, void* userData, OmniClientCreateGroupCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientRenameGroup
typedef void
    (OMNICLIENT_ABI* OmniClientRenameGroupCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Rename group on server.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientRenameGroup(char const* url, const char* group, const char* newGroup, void* userData, OmniClientRenameGroupCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientRemoveGroup
typedef void
    (OMNICLIENT_ABI* OmniClientRemoveGroupCallback)(void* userData, OmniClientResult result, uint64_t changeCount)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Remove group from server.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientRemoveGroup(char const* url, const char* group, void* userData, OmniClientRemoveGroupCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientGetUsers
typedef void
    (OMNICLIENT_ABI* OmniClientGetUsersCallback)(void* userData, OmniClientResult result, uint64_t count, const char** users)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Returns all users registered with the server.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetUsers(char const* url, void* userData, OmniClientGetUsersCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientGetUserGroups
typedef void
    (OMNICLIENT_ABI* OmniClientGetUserGroupsCallback)(void* userData, OmniClientResult result, uint64_t count, const char** groups)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Returns all groups a user belongs to.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientGetUserGroups(char const* url, const char *user, void* userData, OmniClientGetUserGroupsCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientAddUserToGroup
typedef void
    (OMNICLIENT_ABI* OmniClientAddUserToGroupCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Add user to a group.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientAddUserToGroup(char const* url, const char* user, const char* group, void* userData, OmniClientAddUserToGroupCallback callback)
    OMNICLIENT_NOEXCEPT;

//! This is called with the result of @ref omniClientRemoveUserFromGroup
typedef void
    (OMNICLIENT_ABI* OmniClientRemoveUserFromGroupCallback)(void* userData, OmniClientResult result)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Remove user from a group.
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientRemoveUserFromGroup(char const* url, const char* user, const char* group, void* userData, OmniClientRemoveUserFromGroupCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup live Live Updates
//! @{

//! This is called any time we receive a live update from the network
typedef void
    (OMNICLIENT_ABI* OmniClientLiveQueuedCallback)()
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Set a function to be called any time there's an update in the queue that needs to be processed
//! 
//! When this function is called, you should call omniClientLiveProcess(false) FROM THE MAIN THREAD.
//! DO NOT CALL omniClientLiveProcess(false) FROM THIS CALLBACK!
//! DO NOT CALL omniClientLiveProcess(false) WHEN SOME OTHER THREAD IS USING THE USD LIBRARY!
OMNICLIENT_EXPORT(void)
    omniClientLiveSetQueuedCallback(OmniClientLiveQueuedCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Call this to send live updates to the server and process live updates received from the server.
//! 
//! Make sure that no other threads are accessing the USD library at the time this is called.
OMNICLIENT_EXPORT(void)
    omniClientLiveProcess()
    OMNICLIENT_NOEXCEPT;

//! Same as @ref omniClientLiveProcess() but you can specify a server time to stop processing updates.
//! 
//! These can be used to syncronize machines in multi-node rendering. One machine calls @ref omniClientLiveGetLatestServerTime
//! then all machines call @ref omniClientLiveProcessUpTo to process updates received up to that time. This ensures that all machines
//! have the same set of updates, and are therefore rendering the same version scene.
//! 
//! @see omniClientLiveGetLatestServerTime
OMNICLIENT_EXPORT(void)
    omniClientLiveProcessUpTo(const char* url, uint64_t serverTime)
    OMNICLIENT_NOEXCEPT;

//! Returns the server timestamp of the most recently received message (0 if no messages have been received)
OMNICLIENT_EXPORT(uint64_t)
    omniClientLiveGetLatestServerTime(const char* url)
    OMNICLIENT_NOEXCEPT;

//! Call this to wait for all pending live updates to complete.
//! 
//! You should only have to call this at shutdown.
OMNICLIENT_EXPORT(void)
    omniClientLiveWaitForPendingUpdates()
    OMNICLIENT_NOEXCEPT;

//! Set parameters that control jitter reduction
//! 
//! Jitter is a variance in latency. For example if your ping times are variable from 100ms up to 250ms, then your received updates will not be smooth.
//! 
//! Jitter reduction attempts to reduce jitter by holding incoming updates in a queue and releasing them at a consistent rate. The amount of delay is a multiple of your average ping time, plus some constant, up to a maximum amount.
//! 
//! The formula is: `delay = sentTime + min(delayMaximum, delayConstant + delayMultiple * averageLatency) - receivedTime`
//! 
//! * `sentTime` is the (actual) server time when the update was sent
//! * `receivedTime` is the (estimated) server time when the update was received
//! * `averageLatency` is the average amount of latency measured from periodic pings
//! * `delay` is the amount of time to wait before processing the update
//! 
//! The default values are 10ms of constant delay, 2x average ping time, and 1 second maximum.
//!
//! Pass (0,0,0) to completely disable jitter reduction.
//!
//! See also http://omniverse-docs.s3-website-us-east-1.amazonaws.com/usd_resolver/1.4.0/docs/omni-client-live.html#jitter-reduction
OMNICLIENT_EXPORT(void)
    omniClientLiveConfigureJitterReduction(uint32_t delayConstantMilliseconds, uint32_t delayMultiple, uint32_t delayMaximumMilliseconds)
    OMNICLIENT_NOEXCEPT;

//! This is called any time @ref omniClientLiveProcess, @ref omniClientLiveProcessUpTo or @ref omniClientLiveWaitForPendingUpdates is called.
//! 
//! @see omniClientLiveRegisterProcessUpdatesCallback
typedef void
    (OMNICLIENT_ABI* OmniClientLiveProcessUpdatesCallback)(void* userData)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Register a callback to be notified that we are about to begin processing live updates
//! 
//! Used by omni-usd-resolver.
//!
//! See also http://omniverse-docs.s3-website-us-east-1.amazonaws.com/usd_resolver/1.4.0/docs/omni-client-live.html#updating-a-live-layer
OMNICLIENT_EXPORT(uint32_t)
    omniClientLiveRegisterProcessUpdatesCallback(void* userData, OmniClientLiveProcessUpdatesCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Called with the result of @ref omniClientLiveRead
typedef void
    (OMNICLIENT_ABI* OmniClientLiveReadCallback)(void* userData, OmniClientResult result, uint64_t objectId, uint64_t sequenceNum, struct OmniClientContent* content)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Read a live object and set up a subscription to be notified of new updates to that object
//!
//! @p haveObjectId & @p haveSequenceNum: If you already have some version of this live object, you can provide the object id
//! and sequence number that you already have. The server will attempt to build a delta that brings you up to date. If you do
//! not have any version of this live layer, you set both to 0.
//! 
//! The callback will be called with the exact @p objectId and @p sequenceNum that you have read. Both @p objectId and @p sequenceNum
//! may be different from @p haveObjectId and @p haveSequenceNum. For example, if the object was deleted and recreated, then
//! @p objectId will be different from @p haveObjectId. If additional changes were made to the object, @p sequenceNum will be
//! different from @p haveSequenceNum.
//! 
//! Once you've received a callback with one @p objectId, all further callbacks will provide the same @p objectId, because if
//! the object is deleted while you are reading it, you will receive a result of `eOmniClientResult_ErrorAccessLost`
//!
//! The callback will be called with zero or more `eOmniClientResult_Ok` results, followed by `eOmniClientResult_OkLatest`,
//! followed by zero or more `eOmniClientResult_Ok` results. Unless there is an error result (which could come at any time).
//!
//! The callback will not be called again after an error result.
//! 
//! Used by omni-usd-resolver.
//! 
//! See also http://omniverse-docs.s3-website-us-east-1.amazonaws.com/usd_resolver/1.4.0/docs/omni-client-live.html#reading-a-live-layer
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientLiveRead(char const* url, uint64_t haveObjectId, uint64_t haveSequenceNum, void* userData, OmniClientLiveReadCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Called with the result of @ref omniClientLiveCreate
typedef void
    (OMNICLIENT_ABI* OmniClientLiveCreateCallback)(void * userData, OmniClientResult result, uint64_t objectId, uint64_t sequenceNum)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Create a live object
//! 
//! Used by omni-usd-resolver.
//! 
//! See also http://omniverse-docs.s3-website-us-east-1.amazonaws.com/usd_resolver/1.4.0/docs/omni-client-live.html#creating-a-live-layer
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientLiveCreate(char const* url, struct OmniClientContent* content, void* userData, OmniClientLiveCreateCallback callback)
    OMNICLIENT_NOEXCEPT;

//! Called with the result of @ref omniClientLiveUpdate
typedef void
    (OMNICLIENT_ABI* OmniClientLiveUpdateCallback)(void* userData, OmniClientResult result, uint64_t sequenceNum, uint64_t requestId)
    OMNICLIENT_CALLBACK_NOEXCEPT;

//! Update a live object
//! 
//! Used by omni-usd-resolver.
//! 
//! See also http://omniverse-docs.s3-website-us-east-1.amazonaws.com/usd_resolver/1.4.0/docs/omni-client-live.html#updating-a-live-layer
OMNICLIENT_EXPORT(OmniClientRequestId)
    omniClientLiveUpdate(char const* url, uint64_t objectId, struct OmniClientContent* content, void* userData, OmniClientLiveUpdateCallback callback)
    OMNICLIENT_NOEXCEPT;

//! @}

//! @defgroup S3 S3
//! @{

//! Set S3 configuration info for a given URL
//!
//! @param url S3 url to configure. Can be any URL even a custom S3 domain. required.
//! @param bucket S3 bucket name. required.
//! @param region S3 region. required.
//! @param accessKeyId S3 access key. optional.
//! @param secretAccessKey S3 secret access key. optional.
//! @param cloudfrontUrl CloudFront URL. optional. if set, any URLs using \p url will automatically be rewritten to use this URL.
//! @param cloudfrontForList Send all list and stat requests through the CloudFront URLs instead of directly to the S3 endpoint.
//! @param writeConfig true to write omniverse.toml file back to disk, false to only have changes in memory
OMNICLIENT_EXPORT(OmniClientResult)
    omniClientSetS3Configuration(char const* url, char const* bucket, char const* region,
        char const* accessKeyId, char const* secretAccessKey, char const* cloudfrontUrl, bool cloudfrontForList, bool writeConfig)
    OMNICLIENT_NOEXCEPT;

//! @}
