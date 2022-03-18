//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_BASE_ARCH_FILE_SYSTEM_H
#define PXR_BASE_ARCH_FILE_SYSTEM_H

/// \file arch/fileSystem.h
/// \ingroup group_arch_SystemFunctions
/// Architecture dependent file system access

#include "pxr/pxr.h"
#include "pxr/base/arch/api.h"
#include "pxr/base/arch/defines.h"
#include "pxr/base/arch/inttypes.h"
#include <memory>
#include <cstdio>
#include <string>
#include <set>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#if defined(ARCH_OS_LINUX)
#include <unistd.h>
#include <sys/statfs.h>
#include <glob.h>
#elif defined(ARCH_OS_DARWIN)
#include <unistd.h>
#include <sys/mount.h>
#include <glob.h>
#elif defined(ARCH_OS_WINDOWS)
#include <io.h>
#endif

PXR_NAMESPACE_OPEN_SCOPE

/// \addtogroup group_arch_SystemFunctions
///@{
#if !defined(ARCH_OS_WINDOWS)
    #ifdef _POSIX_VERSION
        #include <limits.h>                     /* for PATH_MAX */
    #else
        #include <sys/param.h>                  /* for MAXPATHLEN */
    #endif
#else
    // XXX -- Should probably have ARCH_ macro for this.
    #define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)

    // See https://msdn.microsoft.com/en-us/library/1w06ktdy.aspx
    // XXX -- Should probably have Arch enum for these.
    #define F_OK    0       // Test for existence.
    #define X_OK    1       // Test for execute permission.
    #define W_OK    2       // Test for write permission.
    #define R_OK    4       // Test for read permission.
#endif

#if defined(ARCH_OS_WINDOWS)
    #define ARCH_GLOB_NOCHECK   1
    #define ARCH_GLOB_MARK      2
    #define ARCH_GLOB_NOSORT    4
#else
    #define ARCH_GLOB_NOCHECK   GLOB_NOCHECK
    #define ARCH_GLOB_MARK      GLOB_MARK
    #define ARCH_GLOB_NOSORT    GLOB_NOSORT
#endif
#define ARCH_GLOB_DEFAULT   (ARCH_GLOB_NOCHECK | ARCH_GLOB_MARK)

#ifndef ARCH_PATH_MAX
    #ifdef PATH_MAX
        #define ARCH_PATH_MAX PATH_MAX
    #else
        #ifdef MAXPATHLEN
            #define ARCH_PATH_MAX MAXPATHLEN
        #else
            #ifdef _MAX_PATH
                #define ARCH_PATH_MAX _MAX_PATH
            #else
                #define ARCH_PATH_MAX 1024
            #endif
        #endif
    #endif
#endif

#if defined(ARCH_OS_WINDOWS)
    #define ARCH_PATH_SEP       "\\"
    #define ARCH_PATH_LIST_SEP  ";"
    #define ARCH_REL_PATH_IDENT ".\\"
#else
    #define ARCH_PATH_SEP       "/"
    #define ARCH_PATH_LIST_SEP  ":"
    #define ARCH_REL_PATH_IDENT "./"
#endif

#if defined(ARCH_OS_WINDOWS)
typedef struct __stat64 ArchStatType;
#else
typedef struct stat ArchStatType;
#endif

enum ArchFileAdvice {
	ArchFileAdviceNormal,       // Treat range with default behavior.
	ArchFileAdviceWillNeed,     // OS may prefetch this range.
	ArchFileAdviceDontNeed,     // OS may free resources related to this range.
	ArchFileAdviceRandomAccess, // Prefetching may not be beneficial.
};

class ArchMappingImpl
{
protected:
	void* _ptr;
	size_t _length;

	ArchMappingImpl(void* ptr, size_t length) : _ptr(ptr), _length(length) {}

public:
	virtual ~ArchMappingImpl() {}

	inline size_t GetLength() const { return _length; }
	inline void* GetPtr() const { return _ptr; }
};

template <typename T>
class ArchMapping
{
	ArchMappingImpl* _impl;

public:
	ArchMapping() noexcept : _impl(nullptr) {}
	explicit ArchMapping(ArchMappingImpl* impl) noexcept : _impl(impl) {}

	~ArchMapping() noexcept { if (_impl) delete _impl; }

	ArchMapping(const ArchMapping&) = delete;
	ArchMapping& operator=(const ArchMapping&) = delete;

	ArchMapping(ArchMapping&& other) noexcept : _impl(other._impl) { other._impl = nullptr; }
	ArchMapping& operator=(ArchMapping&& other) noexcept
	{
		if (_impl != other._impl)
		{
			if (_impl) delete _impl;
			_impl = other._impl;
			other._impl = nullptr;
		}
		return *this;
	}

	T* get() const noexcept { return _impl ? static_cast<T*>(_impl->GetPtr()) : nullptr; }

	size_t length() const noexcept { return _impl ? _impl->GetLength() : 0; }

	explicit operator bool() const noexcept { return _impl != nullptr; }
};


/// ArchConstFileMapping and ArchMutableFileMapping are std::unique_ptr<char
/// const *, ...> and std::unique_ptr<char *, ...> respectively.  The functions
/// ArchMapFileReadOnly() and ArchMapFileReadWrite() return them and provide
/// access to memory-mapped file contents.
using ArchConstFileMapping = ArchMapping<char const>;
using ArchMutableFileMapping = ArchMapping<char>;

// ArchFile abstract class
class ArchFile
{
protected:
	ArchFile() {}

public:
	virtual ~ArchFile() {}

	virtual int64_t GetFileLength() = 0;
	virtual std::string GetFileName() = 0;

	virtual ArchConstFileMapping MapFileReadOnly(std::string *errMsg) = 0;
	virtual ArchMutableFileMapping MapFileReadWrite(std::string *errMsg) = 0;

	virtual int64_t PRead(void *buffer, size_t count, int64_t offset) = 0;
	virtual int64_t PWrite(void const *bytes, size_t count, int64_t offset) = 0;

	virtual void FileAdvise(int64_t offset, size_t count, ArchFileAdvice adv) = 0;
};


/// \file fileSystem.h
/// Architecture dependent file system access
/// \ingroup group_arch_SystemFunctions
///

/// Opens a file.
///
/// Opens the file that is specified by filename.
/// Returning true if the file was opened successfully; false otherwise.
///
ARCH_API ArchFile*
ArchOpenFile(char const* fileName, char const* mode);

ARCH_API ArchFile*
ArchOpenFile(int fd, char const* mode);

ARCH_API void ArchReleaseFile(ArchFile* file);

#if defined(ARCH_OS_WINDOWS)
#   define ArchChmod(path, mode)        _chmod(path, mode)
#else
#   define ArchChmod(path, mode)        chmod(path, mode)
#endif

#if defined(ARCH_OS_WINDOWS)
#   define ArchCloseFile(fd)            _close(fd)
#else
#   define ArchCloseFile(fd)            close(fd)
#endif

#if defined(ARCH_OS_WINDOWS)
#   define ArchUnlinkFile(path)         _unlink(path)
#else
#   define ArchUnlinkFile(path)         unlink(path)
#endif

#if defined(ARCH_OS_WINDOWS)
    ARCH_API int ArchFileAccess(const char* path, int mode);
#else
#   define ArchFileAccess(path, mode)   access(path, mode)
#endif

#if defined(ARCH_OS_WINDOWS)
#   define ArchFdOpen(fd, mode)         _fdopen(fd, mode)
#else
#   define ArchFdOpen(fd, mode)         fdopen(fd, mode)
#endif

#if defined(ARCH_OS_WINDOWS)
#   define ArchFileNo(stream)           _fileno(stream)
#else
#   define ArchFileNo(stream)           fileno(stream)
#endif

#if defined(ARCH_OS_WINDOWS)
#   define ArchFileIsaTTY(stream)       _isatty(stream)
#else
#   define ArchFileIsaTTY(stream)       isatty(stream)
#endif

#if defined(ARCH_OS_WINDOWS)
    ARCH_API int ArchRmDir(const char* path);
#else
#   define ArchRmDir(path)   rmdir(path)
#endif

/// Return the length of a file in bytes.
///
/// Returns -1 if the file cannot be opened/read.
ARCH_API int64_t ArchGetFileLength(const char* fileName);
ARCH_API int64_t ArchGetFileLength(FILE* fileName);
ARCH_API inline int64_t ArchGetFileLength(ArchFile *file) { return file->GetFileLength(); }

/// Return a filename for this file, if one can be obtained.
ARCH_API inline std::string ArchGetFileName(ArchFile *file) { return file->GetFileName(); }

/// Returns true if the data in \c stat struct \p st indicates that the target
/// file or directory is writable.
///
/// This returns true if the struct pointer is valid, and the stat indicates
/// the target is writable by the effective user, effective group, or all
/// users.
ARCH_API bool ArchStatIsWritable(const ArchStatType *st);

/// Returns the modification time (mtime) in seconds for a file.
///
/// This function stores the modification time with as much precision as is
/// available in the stat structure for the current platform in \p time and
/// returns \c true on success, otherwise just returns \c false.
ARCH_API bool ArchGetModificationTime(const char* pathname, double* time);

/// Returns the modification time (mtime) in seconds from the stat struct.
///
/// This function returns the modification time with as much precision as is
/// available in the stat structure for the current platform.
ARCH_API double ArchGetModificationTime(const ArchStatType& st);

/// Normalizes the specified path, eliminating double slashes, etc.
///
/// This canonicalizes paths, removing any double slashes, and eliminiating
/// '.', and '..' components of the path.  This emulates the behavior of
/// os.path.normpath in Python.
///
/// On Windows, all backslashes are converted to forward slashes and drive
/// specifiers (e.g., "C:") are lower-cased. If \p stripDriveSpecifier
/// is \c true, these drive specifiers are removed from the path.
ARCH_API std::string ArchNormPath(const std::string& path,
                                  bool stripDriveSpecifier = false);

/// Returns the canonical absolute path of the specified filename.
///
/// This makes the specified path absolute, by prepending the current working
/// directory.  If the path is already absolute, it is returned unmodified.
ARCH_API std::string ArchAbsPath(const std::string& path);

/// Returns the permissions mode (mode_t) for the given pathname.
///
/// This function stats the given pathname and returns the permissions flags
/// for it and returns true.  If the stat fails, returns false.
///
ARCH_API bool ArchGetStatMode(const char *pathname, int *mode);

/// Return the path to a temporary directory for this platform.
///
/// The returned temporary directory will be a location that will normally
/// be cleaned out on a reboot. This is /var/tmp on Linux machines (for
/// legacy reasons), but /tmp on Darwin machines (/var/tmp on Darwin is
/// specified as a location where files are kept between system reboots -
/// see "man hier"). The returned string will not have a trailing slash.
///
/// This routine is threadsafe and will not perform any memory allocations.
ARCH_API const char *ArchGetTmpDir();

/// Make a temporary file name, in a system-determined temporary directory.
///
/// The result returned has the form TMPDIR/prefix.pid[.n]suffix where TMPDIR
/// is a system-determined temporary directory (typically /tmp or /usr/tmp),
/// pid is the process id of the process, and the optional .n records the
/// number of times this function has been called by a process (and is ommited
/// the first time this function is called).
///
/// The call is threadsafe.
///
/// \warning This call opens a security hole because of the race between
/// choosing the name and opening the file.  This call should be avoided in
/// favor of \c ArchMakeTmpFile().
ARCH_API
std::string ArchMakeTmpFileName(const std::string& prefix,
                                const std::string& suffix = std::string());

/// Create a temporary file, in a system-determined temporary directory.
///
/// The result returned has the form TMPDIR/prefix.XXXXXX where TMPDIR is a
/// system-determined temporary directory (typically /tmp or /usr/tmp) and
/// XXXXXX is a unique suffix.  Returns the file descriptor of the new file
/// and, if pathname isn't NULL, returns the full path to the file in
/// pathname.  Returns -1 on failure and errno is set.
///
/// The call is threadsafe.
ARCH_API
int ArchMakeTmpFile(const std::string& prefix, std::string* pathname = 0);

/// Create a temporary file, in a given temporary directory.
///
/// The result returned has the form TMPDIR/prefix.XXXXXX where TMPDIR is the
/// given temporary directory and XXXXXX is a unique suffix.  Returns the file
/// descriptor of the new file and, if pathname isn't NULL, returns the full
/// path to the file in pathname.  Returns -1 on failure and errno is set.
///
/// The call is threadsafe.
ARCH_API
int ArchMakeTmpFile(const std::string& tmpdir,
                    const std::string& prefix, std::string* pathname = 0);

/// Create a temporary sub-direcrory, in a given temporary directory.
///
/// The result returned has the form TMPDIR/prefix.XXXXXX/ where TMPDIR is the
/// given temporary directory and XXXXXX is a unique suffix.  Returns the the
/// full path to the subdir in pathname.  Returns empty string on failure and
/// errno is set.
///
/// The call is threadsafe.
ARCH_API
std::string ArchMakeTmpSubdir(const std::string& tmpdir,
                              const std::string& prefix);


/// Return the length of an ArchConstFileMapping.
inline size_t
ArchGetFileMappingLength(ArchConstFileMapping const &m) {
    return m.length();
}

/// Return the length of an ArchMutableFileMapping.
inline size_t
ArchGetFileMappingLength(ArchMutableFileMapping const &m) {
    return m.length();
}

/// Privately map the passed \p file into memory and return a unique_ptr to the
/// read-only mapped contents.  The contents may not be modified.  If mapping
/// fails, return a null unique_ptr and if errMsg is not null fill it with
/// information about the failure.
ARCH_API
ArchConstFileMapping
inline ArchMapFileReadOnly(ArchFile *file, std::string *errMsg = nullptr) { return file->MapFileReadOnly(errMsg); }

/// \overload
ARCH_API
ArchConstFileMapping
ArchMapFileReadOnly(std::string const& path, std::string *errMsg=nullptr);

/// Privately map the passed \p file into memory and return a unique_ptr to the
/// copy-on-write mapped contents.  If modified, the affected pages are
/// dissociated from the underlying file and become backed by the system's swap
/// or page-file storage.  Edits are not carried through to the underlying file.
/// If mapping fails, return a null unique_ptr and if errMsg is not null fill it
/// with information about the failure.
ARCH_API
ArchMutableFileMapping
inline ArchMapFileReadWrite(ArchFile *file, std::string *errMsg=nullptr) { return file->MapFileReadWrite(errMsg); }

/// \overload
ARCH_API
ArchMutableFileMapping
ArchMapFileReadWrite(std::string const& path, std::string *errMsg=nullptr);

enum ArchMemAdvice {
    ArchMemAdviceNormal,       // Treat range with default behavior.
    ArchMemAdviceWillNeed,     // OS may prefetch this range.
    ArchMemAdviceDontNeed,     // OS may free resources related to this range.
    ArchMemAdviceRandomAccess, // Prefetching may not be beneficial.
};

/// Advise the OS regarding how the application intends to access a range of
/// memory.  See ArchMemAdvice.  This is primarily useful for mapped file
/// regions.  This call does not change program semantics.  It is only an
/// optimization hint to the OS, and may be a no-op on some systems.
ARCH_API
void ArchMemAdvise(void const *addr, size_t len, ArchMemAdvice adv);

/// Report whether or not the mapped virtual memory pages starting at \p addr
/// for \p len bytes are resident in RAM.  Pages that are resident will not,
/// when accessed, cause a page fault while those that are not will.  Return
/// true on success and false in case of an error.  The \p addr argument must be
/// a multiple of ArchGetPageSize().  The \p len argument need not be a multiple
/// of the page size; it will be rounded up to the next page boundary.  Fill
/// \p pageMap with 0s for pages not resident in memory and 1s for pages that
/// are. The \p pageMap argument must therefore point to at least (\p len +
/// ArchGetPageSize()-1)/ArchGetPageSize() bytes.
///
/// Note that currently this function is only implemented on Linux and Darwin.
/// On Windows it currently always returns false.
ARCH_API
bool
ArchQueryMappedMemoryResidency(
    void const *addr, size_t len, unsigned char *pageMap);

/// Read up to \p count bytes from \p offset in \p file into \p buffer.  The
/// file position indicator for \p file is not changed.  Return the number of
/// bytes read, or zero if at end of file.  Return -1 in case of an error, with
/// errno set appropriately.
ARCH_API
inline int64_t ArchPRead(ArchFile *file, void *buffer, size_t count, int64_t offset) { return file->PRead(buffer, count, offset); }

/// Write up to \p count bytes from \p buffer to \p file at \p offset.  The file
/// position indicator for \p file is not changed.  Return the number of bytes
/// written, possibly zero if none written.  Return -1 in case of an error, with
/// errno set appropriately.
ARCH_API
inline int64_t ArchPWrite(ArchFile *file, void const *bytes, size_t count, int64_t offset) { return file->PWrite(bytes, count, offset); }

/// Returns the value of the symbolic link at \p path.  Returns the empty
/// string on error or if \p path does not refer to a symbolic link.
ARCH_API
std::string ArchReadLink(const char* path);

/// Advise the OS regarding how the application intends to access a range of
/// bytes in a file.  See ArchFileAdvice.  This call does not change program
/// semantics.  It is only an optimization hint to the OS, and may be a no-op on
/// some systems.
ARCH_API
inline void ArchFileAdvise(ArchFile *file, int64_t offset, size_t count, ArchFileAdvice adv) { file->FileAdvise(offset, count, adv); }


class ArchFileSysImpl
{
protected:
	ArchFileSysImpl() {}

public:
	virtual ~ArchFileSysImpl() {}

	virtual ArchFile* OpenFile(char const* fileName, char const* mode) = 0;

	virtual std::string AbsPath(const std::string& path) = 0;
	virtual bool IsDir(const std::string& path) = 0;
};

ARCH_API
void ArchRegisterFileSysImpl(const char* prefix, ArchFileSysImpl* fileSysImpl);

ARCH_API 
void ArchUnRegisterFileSysImpl(const char* prefix, ArchFileSysImpl* fileSysImpl);

ARCH_API
bool ArchCanMakeTmpFile(const char* fileName);

ARCH_API
bool ArchTryAbsPath(const std::string& pathIn, std::string& pathOut);

ARCH_API
bool ArchTryIsDir(const std::string& path, bool& result);

///@}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_BASE_ARCH_FILE_SYSTEM_H
