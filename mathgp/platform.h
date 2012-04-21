//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright

// platform.h - some platform dependent checks and defines
#pragma once

////////////////////////////////////////////////////////
// compiler specific stuff

#if defined(_MSC_VER)
#   if _MSC_VER < 1600
#       error "A minimum cl version of 16 is required to compile MathGP"
#   endif
#elif defined(__GNUC__)
    #define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
    #if GCC_VERSION < 40502
        #error "A minimum gcc version of 4.5.2 is required to compile MathGP"
    #elif GCC_VERSION < 40600
        // can be emulated through
        // http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/nullptr#Solution_and_Sample_Code
        // but no need to maintain a global variable.
        // the define is fine for now
        #define nullptr NULL
    #endif
#endif
