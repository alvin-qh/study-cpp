#pragma once;

#ifndef __COMMON__CXXVER_H
#define __COMMON__CXXVER_H

#ifndef __ge_cxx17
#define __ge_cxx17 (__cplusplus >= 201703L)
#endif

#ifndef __ge_cxx20
#define __ge_cxx20 (__cplusplus >= 202002L)
#endif

#ifndef __ge_cxx23
#define __ge_cxx23 (__cplusplus >= 202302L)
#endif

#if __ge_cxx17
#define nullopt_or(val) nullopt
#else
#define nullopt_or(val) (val)
#endif

#endif // __COMMON__CXXVER_H
