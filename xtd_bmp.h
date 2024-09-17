// XTD - Extended Standard Utilities for C/C++
// Single header libraries
// by Marcos Oviedo Rodríguez

// BMP processing module
// #define XTD_BMP_IMPLEMENTATION to include the implementation

#ifndef XTD_BMP_HEADER_H
#define XTD_BMP_HEADER_H

#include "xtd_common.h"

#ifndef XTD_BMP_FUNC
#define XTD_BMP_FUNC 
#endif

#ifndef XTD_BMP_FUNC_DECL
#define XTD_BMP_FUNC_DECL extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////
//
//  BMP Types
//

#pragma pack(push, 1)
typedef struct {
    u16 type;              // Magic identifier: 0x4d42
    u32 size;              // File size in bytes
    u16 reserved1;         // Not used
    u16 reserved2;         // Not used
    u32 offset;            // Offset to image data in bytes from beginning of file
    u32 dib_header_size;   // DIB Header size in bytes
    i32 width_px;          // Width of the image
    i32 height_px;         // Height of image
    u16 num_planes;        // Number of color planes
    u16 bits_per_pixel;    // Bits per pixel
    u32 compression;       // Compression type
    u32 image_size_bytes;  // Image size in bytes
    i32 x_resolution_ppm;  // Pixels per meter
    i32 y_resolution_ppm;  // Pixels per meter
    u32 num_colors;        // Number of colors
    u32 important_colors;  // Important colors
} XTDB_BMPHeader;
#pragma pack(pop)

typedef struct {
    u8 b, g, r, x;
} XTDB_RGBX;

////////////////////////////////////////
//
//  Function Declarations
//

XTD_BMP_FUNC_DECL usize XTD_GetBMPFileSize(i32 width, i32 height, i32 bytes_per_pixel);
XTD_BMP_FUNC_DECL void XTD_WriteBMPToMem(void* out_buffer, i32 width, i32 height, int bytes_per_pixel, u8* pixels);
XTD_BMP_FUNC_DECL int XTD_WriteBMPToFile(void* out_file, i32 width, i32 height, int bytes_per_pixel, u8* pixels);

////////////////////////////////////////
////////////////////////////////////////
//
//  Implementation
//

#ifdef XTD_BMP_IMPLEMENTATION

#include <errno.h>

XTD_BMP_FUNC usize XTD_GetBMPFileSize(i32 width, i32 height, i32 bytes_per_pixel)
{
    return bytes_per_pixel * width * height + sizeof(XTDB_BMPHeader);
}

static void _xtd_FillBMPHeader(XTDB_BMPHeader* header, i32 width, i32 height, i32 bytes_per_pixel)
{
    header->type = 0x4d42;
    header->size = bytes_per_pixel * width * height + sizeof(XTDB_BMPHeader);
    header->offset = sizeof(XTDB_BMPHeader);
    header->dib_header_size = 40;
    header->width_px = width;
    header->height_px = height;
    header->num_planes = 1;
    header->bits_per_pixel = (u16)(bytes_per_pixel * 8);
    header->compression = 0;
    header->image_size_bytes = bytes_per_pixel * width * height;
}

XTD_BMP_FUNC void XTD_WriteBMPToMem(void* out_buffer, i32 width, i32 height, i32 bytes_per_pixel, u8* pixels)
{
    XTD_ASSERT(bytes_per_pixel == 4 && "TODO: implement format");
    
    XTDB_BMPHeader* header = (XTDB_BMPHeader*)out_buffer;
    XTD_ZERO_STRUCT(header);
    _xtd_FillBMPHeader(header, width, height, bytes_per_pixel);

    u8* data = (u8*)(header + 1);
    memcpy(data, pixels, bytes_per_pixel * width * height);
}

XTD_BMP_FUNC int XTD_WriteBMPToFile(void* out_file, i32 width, i32 height, int bytes_per_pixel, u8* pixels)
{
    XTD_ASSERT(bytes_per_pixel == 4 && "TODO: implement format");
    
    XTDB_BMPHeader header = {0};
    _xtd_FillBMPHeader(&header, width, height, bytes_per_pixel);
    
    usize n = fwrite(&header, sizeof(header), 1, (FILE*)out_file);
    if (n != 1)
        return errno;
    n = fwrite(pixels, bytes_per_pixel, width * height, (FILE*)out_file);
    if (n != (usize)width * (usize)height)
        return errno;

    return 0;
}

#endif

////////////////////////////////////////
////////////////////////////////////////
//
//  End of Implementation
//

#ifdef __cplusplus
}
#endif

#endif //XTD_BMP_HEADER_H
