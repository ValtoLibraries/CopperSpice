/***********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (c) 2012-2018 Ansel Sermersheim
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

// Get Qt defines/settings

#include "qglobal.h"

// Set any POSIX/XOPEN defines at the top of this file to turn on specific APIs

#include <unistd.h>

// We are hot - unistd.h should have turned on the specific APIs we requested

#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <dlfcn.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#ifndef QT_NO_IPV6IFNAME
#include <net/if.h>
#endif

#ifdef QT_LARGEFILE_SUPPORT
#define QT_STATBUF              struct stat64
#define QT_STATBUF4TSTAT        struct stat64
#define QT_STAT                 ::stat64
#define QT_FSTAT                ::fstat64
#define QT_LSTAT                ::lstat64
#define QT_OPEN                 ::open64
#define QT_TRUNCATE             ::truncate64
#define QT_FTRUNCATE            ::ftruncate64
#define QT_LSEEK                ::lseek64
#else
#define QT_STATBUF              struct stat
#define QT_STATBUF4TSTAT        struct stat
#define QT_STAT                 ::stat
#define QT_FSTAT                ::fstat
#define QT_LSTAT                ::lstat
#define QT_OPEN                 ::open
#define QT_TRUNCATE             ::truncate
#define QT_FTRUNCATE            ::ftruncate
#define QT_LSEEK                ::lseek
#define QT_OPEN_LARGEFILE       0
#endif

#ifdef QT_LARGEFILE_SUPPORT
#define QT_FOPEN                ::fopen64
#define QT_FSEEK                ::fseeko64
#define QT_FTELL                ::ftello64
#define QT_FGETPOS              ::fgetpos64
#define QT_FSETPOS              ::fsetpos64
#define QT_FPOS_T               fpos64_t
#define QT_OFF_T                off64_t
#else
#define QT_FOPEN                ::fopen
#define QT_FSEEK                ::fseek
#define QT_FTELL                ::ftell
#define QT_FGETPOS              ::fgetpos
#define QT_FSETPOS              ::fsetpos
#define QT_FPOS_T               fpos_t
#define QT_OFF_T                long
#endif

#define QT_STAT_REG             S_IFREG
#define QT_STAT_DIR             S_IFDIR
#define QT_STAT_MASK            S_IFMT
#define QT_STAT_LNK             S_IFLNK
#define QT_SOCKET_CONNECT       ::connect
#define QT_SOCKET_BIND          ::bind
#define QT_FILENO               fileno
#ifndef QT_CLOSE
#define QT_CLOSE                ::close
#endif
#ifndef QT_READ
#define QT_READ                 ::read
#endif
#ifndef QT_WRITE
#define QT_WRITE                ::write
#endif
#define QT_ACCESS               ::access
#define QT_GETCWD               ::getcwd
#define QT_CHDIR                ::chdir
#define QT_MKDIR                ::mkdir
#define QT_RMDIR                ::rmdir
#define QT_OPEN_RDONLY          O_RDONLY
#define QT_OPEN_WRONLY          O_WRONLY
#define QT_OPEN_RDWR            O_RDWR
#define QT_OPEN_CREAT           O_CREAT
#define QT_OPEN_TRUNC           O_TRUNC
#define QT_OPEN_APPEND          O_APPEND

#define QT_SIGNAL_RETTYPE       void
#define QT_SIGNAL_ARGS          int
#define QT_SIGNAL_IGNORE        SIG_IGN

#define QT_MMAP                 ::mmap

// Directory iteration
#define QT_DIR                  DIR

#define QT_OPENDIR              ::opendir
#define QT_CLOSEDIR             ::closedir


#if defined(QT_LARGEFILE_SUPPORT) \
        && defined(QT_USE_XOPEN_LFS_EXTENSIONS) \
        && !defined(QT_NO_READDIR64)
# define QT_DIRENT               struct dirent64
# define QT_READDIR              ::readdir64
# define QT_READDIR_R            ::readdir64_r
#else
# define QT_DIRENT               struct dirent
# define QT_READDIR              ::readdir
# define QT_READDIR_R            ::readdir_r
#endif

#define QT_SOCKLEN_T           socklen_t

#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE >= 500)
#define QT_SNPRINTF             ::snprintf
#define QT_VSNPRINTF            ::vsnprintf
#endif

#ifndef MAXNAMLEN
#  define MAXNAMLEN NAME_MAX
#endif

#ifndef PATH_MAX
#  define PATH_MAX MAXPATHLEN
#endif

#ifndef NSIG
#  define NSIG _SIGMAX
#endif

#ifndef MAP_ANON
#  define MAP_ANON 0
#endif

typedef void (*sighandler_t)(int);

#ifndef QT_NO_MMAP
#  define QT_NO_MMAP
#endif

#ifndef QT_NO_SHAREDMEMORY
#  define QT_NO_SHAREDMEMORY
#endif

#ifndef QT_NO_SYSTEMSEMAPHORE
#  define QT_NO_SYSTEMSEMAPHORE
#endif
