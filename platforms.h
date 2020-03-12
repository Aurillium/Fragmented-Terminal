#ifndef OS_TYPE
    #include "includes/req_types.c"
    #ifdef ANDROID
        #define OS_TYPE 0
        #include "platforms/android.c"
        #include "platforms/posix.c"
        #define MESSAGE L"Hello Android user!"
    #elif defined(__MACH__)
        #define OS_TYPE 1
        #include "platforms/osx.c"
        #include "platforms/posix.c"
        #define MESSAGE L"Hello Mac user!"
    #elif defined(__FreeBSD__)
        #define OS_TYPE 2
        #include "platforms/freebsd.c"
        #include "platforms/posix.c"
        #define MESSAGE L"Hello FreeBSD user!"
    #elif defined(linux) || defined(__linux)
        #define OS_TYPE 3
        #include "platforms/linux.c"
        #include "platforms/posix.c"
        #define MESSAGE L"Hello Linux user!"
    #elif defined(__linux__)
        #define OS_TYPE 4
        #include "platforms/old_linux.c"
        #define MESSAGE L"Hello Old Linux user!"
    #elif defined(unix) || defined(__unix) || defined(__unix__)
        #define OS_TYPE 5
        #include "platforms/unix.c"
        #include "platforms/posix.c"
        #define MESSAGE L"Hello UNIX user!"
    #elif defined(_WIN64) || defined(WIN64)
        #define OS_TYPE 6
        #include "platforms/win64.c"
        #include "platforms/windows_all.c"
        #define MESSAGE L"Hello Windows 64-bit user!"
    #elif defined(_WIN32) || defined(WIN32)
        #define OS_TYPE 7
        #include "platforms/win32.c"
        #include "platforms/windows_all.c"
        #define MESSAGE L"Hello Windows 32-bit user!"
    #else
        #error OS not supported.
        #include <stophere>
    #endif
    #include "includes/types.c"
    #include "includes/dialogs.c"
#endif