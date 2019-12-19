#ifndef HEAVENLY_API
    #ifdef _WIN32 || __CYGWIN__
        // WINDOWS API DEFINITIONS
        #ifdef _MSC_VER
            #ifdef HEAVENLY_DLL_BUILD
                #define HEAVENLY_API __declspec(dllexport)
            #else
                #define HEAVENLY_API __declspec(dllimport)
            #endif
        #elif defined(__GNUC__)
            #ifdef HEAVENLY_DLL_BUILD
                #define HEAVENLY_API __attribute__ ((dllexport))
            #else
                #define HEAVENLY_API __attribute__ ((dllimport))
            #endif
        #else
            #error Heavenly Engine must be compiled using Visual Studio or GCC.
        #endif
    #elif defined(__linux__)
        // LINUX API DEFINITIONS
        #if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
            #ifdef HEAVENLY_DLL_BUILD
                #define HEAVENLY_API __attribute__(visibility("default"))
            #else
                #define HEAVENLY_API
            #endif
        #else
            #error Heavenly Engine must be compiled using GCC (v4 or higher) or Clang.
        #endif
    #else
        #error Heavenly Engine only supports Windows and Linux systems.
    #endif
#endif // HEAVENLY_API