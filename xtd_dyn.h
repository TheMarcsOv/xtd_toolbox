// XTD - Extended Standard Utilities for C/C++
// Single header libraries
// by Marcos Oviedo Rodríguez

// Dynamic structures module
// #define XTD_DYN_IMPLEMENTATION to include the implementation

#ifndef XTD_DYN_HEADER_H
#define XTD_DYN_HEADER_H

#ifndef XTD_DYN_FUNC
#define XTD_DYN_FUNC 
#endif

#ifndef XTD_DYN_FUNC_DECL
#define XTD_DYN_FUNC_DECL extern
#endif

#ifndef XTD_DYN_MALLOC
#define XTD_DYN_MALLOC(size) malloc(size)
#endif

#ifndef XTD_DYN_REALLOC
#define XTD_DYN_REALLOC(ptr, new_size) realloc(ptr, new_size)
#endif

#ifndef XTD_DYN_FREE
#define XTD_DYN_FREE(ptr) free(ptr)
#endif

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

#include "xtd_common.h"

////////////////////////////////////////
//
//  Dynamic Array Macros
//

// Works with any struct with the following fields
//   T* items;
//   usize capacity;
//   usize count;
// where T can be any type

#define XTD_DA_MIN_CAPACITY 16

#define __XTD_DA_SHOULD_GROW(da, new_len) ((da).items == ((void*)0) || (new_len) > (da).capacity)
#define XTD_DA_RESERVE(da, new_cap) if ((da).items == (void*)0 || (da).capacity < (new_cap)) { \
        if ((da).items == (void*)0) (da).count = 0; \
        usize cap = XTD_MAX(new_cap, XTD_DA_MIN_CAPACITY); \
        (da).items = _XTD_GrowBuffer((da).items, cap, sizeof((da).items[0])); \
        (da).capacity = cap; \
    }
#define XTD_DA_PUSH(da, ...) do { \
    if (__XTD_DA_SHOULD_GROW(da, (da).count + 1)) \
        {XTD_DA_RESERVE(da, (da).capacity * 2)} \
    (da).items[((da).count)++] = __VA_ARGS__; \
    } while(0);

#define XTD_DA_POP(da) ((da).count--, (da).items[(da).count])
#define XTD_DA_CLEAR(da) do {(da).count = 0;} while(0)
#define XTD_DA_FREE(da) do {XTD_DYN_FREE((da).items); (da).items = NULL; (da).capacity = 0; (da).count = 0;} while(0)

////////////////////////////////////////
//
//  Function Declarations
//

XTD_DYN_FUNC_DECL void* _XTD_GrowBuffer(void* buffer, usize new_capacity, usize elem_size);


////////////////////////////////////////
////////////////////////////////////////
//
//  Implementation
//

#ifdef XTD_DYN_IMPLEMENTATION

XTD_DYN_FUNC void* _XTD_GrowBuffer(void* buffer, usize new_capacity, usize elem_size)
{
    usize new_size = new_capacity * elem_size;
    if(buffer == NULL)
    {
        return XTD_DYN_MALLOC(new_size);
    } else
    {
        return XTD_DYN_REALLOC(buffer, new_size);
    }

    return buffer;
}

#endif

////////////////////////////////////////
////////////////////////////////////////
//
//  End of Implementation
//

#ifdef __cplusplus //End extern "C"
}
#endif

#endif // XTD_HEADER_H
