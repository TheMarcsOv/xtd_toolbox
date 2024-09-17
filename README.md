# XTD Toolbox (WIP)
C/C++ utility headers heavily inspired by [stb](https://github.com/nothings/stb) and [gb](https://github.com/gingerBill/gb) single-header libraries.
Mainly used for my own personal projects and for reference.

Can be used as drop-in modules that are easily integrated into existing projects since no build system is required.

## Modules
* xtd_common.h: Lightweight core module including useful types, macros, functions...
* xtd_math.h: Math library with vector types, useful for game development and graphics
* xtd_bmp.h: BMP image file writing module. (BMP reading not implemented yet)
* xtd_colors.h: RGBA color struct for easy manipulation.
* xtd_dyn.h: Simple generic dynamic array data structure using macros.

# Usage

To use one of the modules, just place it on your include path and include it. All of the modules depend on
xtd_common.h so you must place it on your include path as well.
All modules are header files, but they contain function implementations that can be enabled with a macro.
For instance, if you want to use xtd_math.h, define XTD_MATH_IMPLEMENTATION before including it:
```c
#include <stdio.h>

#define XTD_MATH_IMPLEMENTATION
#include "xtd_math.h"

int main(int argc, char** argv) {
    XTD_fprint4f(stdout, add4f(V4f {1,2,3,4} + V4f {1,1,1,1}));
    return 0;
}
```

XTD_MATH_IMPLEMENTATION should only be defined on one `.c` file to avoid conflicts. 

## xtd_common.h
xtd_common.h is a simple header. To use it just place it on your include path and include it.
```c
#include "xtd_common.h"

int main(int argc, char** argv) {
    return 0;
}
```