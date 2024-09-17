// XTD - Extended Standard Utilities for C/C++
// Single header libraries
// by Marcos Oviedo Rodríguez

// Color utility module
// #define XTD_COLORS_IMPLEMENTATION to include the implementation

#ifndef XTD_COLORS_HEADER_H
#define XTD_COLORS_HEADER_H

// C++ compatibility
#ifdef __cplusplus
extern "C" {
#endif

#include "xtd_common.h"

////////////////////////////////////////
//
//  Color Types
//

// Memory order is R,G,B,A (from low to high address)
typedef union ColorRGBA_
{
    u32 hex; // 0xAABBGGRR
    u8 components[4];
    struct {
        u8 r, g, b, a;
    };
} ColorRGBA;
#define XTD_MAKE_RGBA(r, g, b, a) XTD_COMPOUND(ColorRGBA) { (u32) (((a) << 24) | ((b) << 16) | ((g) << 8) | (r)) }

// Memory order is B,G,R,A (from low to high address)
typedef union ColorBGRA_
{
    u32 hex; // 0xAARRGGBB
    u8 components[4];
    struct {
        u8 b, g, r, a;
    };
} ColorBGRA;
#define XTD_MAKE_BGRA(r, g, b, a) XTD_COMPOUND(ColorBGRA) { (u32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)) }

#ifdef __cplusplus //End extern "C"
}
#endif

#endif // XTD_HEADER_H
