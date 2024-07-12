 /**
  * Platform determination:
  *     https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive
  *
  * Apple syslimits. Contains MAX_PATH:
  *     https://opensource.apple.com/source/xnu/xnu-201.5/bsd/sys/syslimits.h.auto.html
  * */

#ifndef SYS_CHECK_H_
#define SYS_CHECK_H_

#include <stdio.h>

/**
 * TODO:
 * Source the correct limits.h or syslimits.h or sys/syslimits.h and set
 * NSH_MAX_PATH to the correct value.
 * */

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 */

#if defined(_WIN32)
    #define PLATFORM_NAME "windows" /* Windows */
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" /* Windows */
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" /* Windows (Cygwin POSIX under Microsoft Window) */
#elif defined(__ANDROID__)
    #define PLATFORM_NAME "android" /* Android (implies Linux, so it must come first) */
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" /* Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other */
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM_NAME "bsd" /* FreeBSD, NetBSD, OpenBSD, DragonFly BSD */
    #endif
#elif defined(__hpux)
    #define PLATFORM_NAME "hp-ux" /* HP-UX */
#elif defined(_AIX)
    #define PLATFORM_NAME "aix" /* IBM AIX */
#elif defined(__APPLE__) && defined(__MACH__) /* Apple OSX and iOS (Darwin) */
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "ios" /* Apple iOS */
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "ios" /* Apple iOS */
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" /* Apple OSX */
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define PLATFORM_NAME "solaris" /* Oracle Solaris, Open Indiana */
#else
    #define PLATFORM_NAME NULL
#endif

/* Return a name of platform, if determined, otherwise - an empty string */
const char *get_platform_name(void) {
    return (PLATFORM_NAME == NULL) ? "" : PLATFORM_NAME;
}

/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char *argv[]) {
    puts(get_platform_name());
    return 0;
}
#pragma GCC diagnostic pop
*/

#endif
