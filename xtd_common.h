// XTD - eXtended Standard Utilities for C/C++
// Single header library
// by Marcos Oviedo Rodríguez

// Common header
// Does not need an implementation macro (XTD_COMMON_IMPL) yet.

// Assumes existence of libc, __STDC_HOSTED__ == 1

#ifndef XTD_COMMON_HEADER_H
#define XTD_COMMON_HEADER_H

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////
//
//  Compiler Helpers
//

#define XTD_IS_COMPILER_MSVC 0
#define XTD_IS_COMPILER_CLANG 0
#define XTD_IS_COMPILER_GCC 0

#ifdef _MSC_VER
    #undef XTD_IS_COMPILER_MSVC
    #define XTD_IS_COMPILER_MSVC 1
#endif

#ifdef __clang__
    #undef XTD_IS_COMPILER_CLANG
    #define XTD_IS_COMPILER_CLANG 1
#elif defined(__GNUC__)
    #undef XTD_IS_COMPILER_GCC
    #define XTD_IS_COMPILER_GCC 1
#endif

#if XTD_IS_COMPILER_MSVC
    #define XTD_THREAD_LOCAL __declspec(thread)
#elif XTD_IS_COMPILER_CLANG || XTD_IS_COMPILER_GCC
    #define XTD_THREAD_LOCAL __thread
#else
    #warning XTD_THREAD_LOCAL not defined for this compiler
#endif

#if XTD_IS_COMPILER_MSVC || XTD_IS_COMPILER_CLANG
    #define XTD_DLL_EXPORT __declspec(dllexport)
#elif XTD_IS_COMPILER_GCC
    #define XTD_DLL_EXPORT
#else
    #warning XTD_DLL_EXPORT not defined for this compiler
#endif

#define XTD_DLL_EXPORT_FUNC extern "C" XTD_DLL_EXPORT

#ifdef __cplusplus
    #define XTD_INLINE inline
#else
    #define XTD_INLINE static inline
#endif

#if XTD_IS_COMPILER_MSVC
    #define XTD_FORCE_INLINE XTD_INLINE __forceinline 
#elif XTD_IS_COMPILER_CLANG || XTD_IS_COMPILER_GCC
    #define XTD_FORCE_INLINE __attribute__((always_inline)) XTD_INLINE
#else
    #warning XTD_FORCE_INLINE not defined for this compiler
#endif

#if XTD_IS_COMPILER_CLANG
    #define XTD_COMPILER_DESCRIPTION "Clang " __clang_version__
#elif XTD_IS_COMPILER_GCC
    #define XTD_COMPILER_DESCRIPTION "GCC " XTD_MACROSTR(__GNUC__) "." XTD_MACROSTR(__GNUC_MINOR__) "." XTD_MACROSTR(__GNUC_PATCHLEVEL__)
#elif XTD_IS_COMPILER_MSVC
    #define XTD_COMPILER_DESCRIPTION "MSVC " _MSC_FULL_VER
#else 
    #define XTD_COMPILER_DESCRIPTION "Unknown"
#endif

#if __STDC_VERSION__ >= 202301L
    #define XTD_TYPEOF(X) typeof(X)
#elif XTD_IS_COMPILER_MSVC && defined(__cplusplus)
    #define XTD_TYPEOF(X) decltype(X)
#elif XTD_IS_COMPILER_CLANG || XTD_IS_COMPILER_GCC
    #define XTD_TYPEOF(X) __typeof__(X)
#else
    #define XTD_TYPEOF(X)
#endif

////////////////////////////////////////
//
//  Utility Macros
//

#define __XTD_GLUE2(A, B) A ## B
#define __XTD_GLUE(A, B) __XTD_GLUE2(A, B)
#define XTD_GLUE(A, B) __XTD_GLUE(A, B)

#define XTD_MACROSTR_(X) #X
#define XTD_MACROSTR(X) XTD_MACROSTR_(X)

#define __XTD_MEMBER(T, M) (((T*)0)->M)
#define XTD_OFFSETOF(T, M) ((usize)&__XTD_MEMBER(T, M))

#if defined(__cplusplus)
    #define XTD_COMPOUND(Type) Type
#elif __STDC_VERSION__ >= 199901L
    #define XTD_COMPOUND(Type) (Type)
#else
    #define XTD_COMPOUND(Type)
#endif

#define XTD_STATIC_ASSERT(c) typedef u8 XTD_GLUE(__xtd__sa__,__LINE__) [(c)?1:-1]

////////////////////////////////////////
//
//  Common Types
//

#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t usize;
typedef intptr_t isize;

typedef float f32;
typedef double f64;

////////////////////////////////////////
//
//  Common Constants
//

#ifndef U64_MAX
#define U64_MAX ((u64)0xFFFFFFFFFFFFFFFF)
#endif

#ifndef U32_MAX
#define U32_MAX ((u32)0xFFFFFFFF)
#endif

#define U64_MIN ((u64)0)
#define I64_MAX ((i64)0x7FFFFFFFFFFFFFFF)
#define I64_MIN ((i64)0x8FFFFFFFFFFFFFFF)

#define U32_MIN ((u32)0)
#define I32_MAX ((i32)0x7FFFFFFF)
#define I32_MIN ((i32)0x80000000)

#define F32_EPSILON ((f32)1.19209290e-7F)
#define F64_EPSILON ((f64)2.2204460492503131e-16)

#define PI_HALF     (1.57079632679489661923)
#define PI          (3.14159265358979323846)
#define TAU         (6.28318530717958647692)
#define TWO_PI TAU
#define E           (2.71828182845904523536)
#define SQRT2       (1.41421356237309504880)
#define XTD_DEG2RAD (TAU/360.0)
#define XTD_RAD2DEG (360.0/TAU)

////////////////////////////////////////
//
//  Math
//

#define XTD_INRANGE(x, min, max) ((x) >= (min) && (x) < (max))
#define XTD_ABS(x) ((x) < 0 ? -(x) : (x))

#define XTD_MAX(a, b) ((a) > (b) ? (a) : (b))
#define XTD_MAX3(a, b, c) XTD_MAX(XTD_MAX(a, b), c)
#define XTD_LIMITBOTTOM(x, minimum) XTD_MAX(x, minimum)
#define XTD_MIN(a, b) ((a) < (b) ? (a) : (b))
#define XTD_MIN3(a, b, c) XTD_MIN(XTD_MIN(a, b), c)
#define XTD_LIMITTOP(x, maximum) XTD_MIN(x, maximum)
#define XTD_CLAMP(x, lower, upper) XTD_MIN(XTD_MAX(x, lower), upper)

#define XTD_DIVFLOOR(a, b) ((a)/(b))
#define XTD_DIVCEIL(a, b)  (((a) + (b) - 1)/(b))
#define XTD_ALIGNDOWN(x, align) (XTD_DIVFLOOR((x), (align)) * (align))
#define XTD_ALIGNUP(x, align) (XTD_DIVCEIL((x), (align)) * (align))

#define XTD_ARRAYCOUNT(A) (sizeof(A)/sizeof(A[0]))
#define XTD_ARRAYCOUNTI32(A) ((i32)XTD_ARRAYCOUNT(A))

#define XTD_ISPOW2(x) (((x) != 0) && (((x) & ((x)-1)) == 0))

#define XTD_KB(kb) ((kb)*1024)
#define XTD_MB(mb) (XTD_KB(mb)*1024)
#define XTD_GB(gb) (XTD_MB(gb)*1024)
#define XTD_TB(tb) (XTD_GB(tb)*1024)

// Bit Manipulation 
//

#define XTD_BIT(position) (1ULL << (position))
#define XTD_SETBIT(var, position) ((var) |= XTD_BIT(position))
#define XTD_SETBITMASK(var, mask) ((var) |= (mask) )
#define XTD_CLEARBIT(var, position) ((var) &= ~XTD_BIT(position))
#define XTD_CLEARBITMASK(var, mask) ((var) &= ~(mask))
#define XTD_MODIFYBITS(var, clearBits, setBits) ((var) = (((var) & ~(clearBits)) | (setBits)))
#define XTD_TOGGLEBIT(var, position) ((var) ^= XTD_BIT(position) )
#define XTD_TOGGLEBITMASK(var, mask) ((var) ^= (mask))
#define XTD_BITBLOCK(size) ((1ULL << (size)) - 1ULL)

////////////////////////////////////////
//
//  Defineable Functions
//

#ifndef XTD_ASSERT
    #include <assert.h>
    #define XTD_ASSERT(x) assert(x)
#endif

#ifndef XTD_FPRINTF
    #include <stdio.h>
    #if XTD_IS_COMPILER_GCC
        #define XTD_FPRINTF(file, fmt, ...) fprintf((FILE*)(file), (fmt), ##__VA_ARGS__)
    #else
        #define XTD_FPRINTF(file, fmt, ...) fprintf((FILE*)(file), (fmt), __VA_ARGS__)
    #endif
#endif

#ifndef XTD_PANIC
    #if XTD_IS_COMPILER_GCC | XTD_IS_COMPILER_CLANG
        #define XTD_PANIC(fmt, ...) do { XTD_FPRINTF(stderr, fmt, ##__VA_ARGS__); XTD_ASSERT(0); } while(0);
    # else
        #define XTD_PANIC(fmt, ...) do { XTD_FPRINTF(stderr, fmt,   __VA_ARGS__); XTD_ASSERT(0); } while(0);
    #endif
#endif

#ifndef XTD_MEMSET
    #include <string.h>
    #define XTD_MEMSET(pointer, val, size) memset((pointer), (val), (size))
#endif

////////////////////////////////////////
//
//  Memory Utilities
//

#define XTD_ZERO_MEM(pointer, size) XTD_MEMSET((pointer), 0, (size))
#define XTD_ZERO_STRUCT(struct_ptr) XTD_ZERO_MEM((struct_ptr), sizeof(*(struct_ptr)))
#define XTD_ZERO_FIXEDARRAY(fixed_array) XTD_ZERO_MEM((fixed_array), sizeof(fixed_array))

#ifdef __cplusplus //End extern "C"
}
#endif

#endif // XTD_HEADER_H
