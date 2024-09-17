// XTD - Extended Standard Utilities for C/C++
// Single header library
// by Marcos Oviedo Rodríguez

// Vector math module
// #define XTD_MATH_IMPLEMENTATION to include the implementation

#ifndef XTD_MATH_HEADER_H
#define XTD_MATH_HEADER_H

#ifndef XTD_MATH_FUNC
#define XTD_MATH_FUNC 
#endif

#ifndef XTD_MATH_FUNC_DECL
#define XTD_MATH_FUNC_DECL extern
#endif

#ifndef XTD_MATH_FORCE_INLINE
#define XTD_MATH_FORCE_INLINE XTD_FORCE_INLINE
#endif

#include "xtd_common.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////
//
//  Scalar functions
//

XTD_MATH_FORCE_INLINE f32 absF32(f32 x) {
    union {
        u32 u;
        f32 f;
    } r;
    r.f = x;
    r.u &= 0x7fffffff;
    return r.f;
}

XTD_MATH_FORCE_INLINE f32 lerpF32(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

////////////////////////////////////////
//
//  Random functions
//

XTD_MATH_FORCE_INLINE f32 rand01() {
    return rand() / (RAND_MAX + 1.0);
}

XTD_MATH_FORCE_INLINE f32 randUniform(f32 min, f32 max) {
    return lerpF32(min, max, rand01());
}

////////////////////////////////////////
//
//  Vector Types
//

typedef union V2f_ {
    struct
    {
        f32 x, y;
    };
    struct
    {
        f32 u, v;
    };
    f32 e[2];
} V2f; 

typedef union V3f_ {
    struct
    {
        f32 x, y, z;
    };
    struct
    {
        f32 r, g, b;
    };
    struct
    {
        V2f xy;
        f32 _z;
    };
    f32 e[3];
} V3f; 


typedef union V4f_ {
    struct
    {
        f32 x, y, z, w;
    };
    struct
    {
        f32 r, g, b, a;
    };
    struct
    {
        V3f xyz;
        f32 _w;
    };
    struct
    {
        V2f xy;
        V2f zw;
    };
    f32 e[4];
} V4f; 


////////////////////////////////////////
//
//  Basic math operators
//

#if XTD_IS_COMPILER_GCC
#pragma GCC diagnostic push
#ifndef __cplusplus
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#endif
#endif

//
// Vector 4
//

XTD_MATH_FORCE_INLINE V4f add4f(V4f a, V4f b) {
    V4f res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    res.w = a.w + b.w;
    return res;
}
XTD_MATH_FORCE_INLINE V4f addsc4f(V4f a, f32 b) {
    V4f res;
    res.x = a.x + b;
    res.y = a.y + b;
    res.z = a.z + b;
    res.w = a.w + b;
    return res;
}
XTD_MATH_FORCE_INLINE V4f sub4f(V4f a, V4f b) {
    V4f res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    res.w = a.w - b.w;
    return res;
}
XTD_MATH_FORCE_INLINE V4f neg4f(V4f a) {
    V4f res;
    res.x = -a.x;
    res.y = -a.y;
    res.z = -a.z;
    res.w = -a.w;
    return res;
}
XTD_MATH_FORCE_INLINE V4f subsc4f(V4f a, f32 b) {
    V4f res;
    res.x = a.x - b;
    res.y = a.y - b;
    res.z = a.z - b;
    res.w = a.w - b;
    return res;
}
XTD_MATH_FORCE_INLINE V4f mul4f(V4f a, V4f b) {
    V4f res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;
    res.w = a.w * b.w;
    return res;
}

XTD_MATH_FORCE_INLINE V4f sc4f(V4f a, f32 b) {
    V4f res;
    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    res.w = a.w * b;
    return res;
}

XTD_MATH_FORCE_INLINE V4f div4f(V4f a, V4f b) {
    V4f res;
    res.x = a.x / b.x;
    res.y = a.y / b.y;
    res.z = a.z / b.z;
    res.w = a.w / b.w;
    return res;
}

XTD_MATH_FORCE_INLINE V4f divsc4f(V4f a, f32 b) {
    V4f res;
    f32 inv = 1.0f / b;
    res.x = a.x * inv;
    res.y = a.y * inv;
    res.z = a.z * inv;
    res.w = a.w * inv;
    return res;
}

XTD_MATH_FORCE_INLINE f32 dot4f(V4f a, V4f b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

XTD_MATH_FORCE_INLINE f32 lengthSq4f(V4f a) {
    return dot4f(a, a);
}

XTD_MATH_FORCE_INLINE f32 length4f(V4f a) {
    return sqrtf(lengthSq4f(a));
}
XTD_MATH_FORCE_INLINE V4f normalized4f(V4f a) {
    f32 len = length4f(a);
	f32 invlen = 1.0f / len;
    return sc4f(a, invlen);
}

XTD_MATH_FORCE_INLINE V4f noz4f(V4f a) {
    f32 len = length4f(a);
	if (len == 0.0f)
		return a;
	f32 invlen = 1.0f / len;
    return sc4f(a, invlen);
}

XTD_MATH_FORCE_INLINE V4f abs4f(V4f a) {
    V4f res = {{absF32(a.x), absF32(a.y), absF32(a.z), absF32(a.w)}};
    return res;
}

XTD_MATH_FORCE_INLINE bool approxEqual4f(V4f a, V4f b, f32 epsilon) {
    V4f err = abs4f(sub4f(a, b));
    return (err.x < epsilon) && (err.y < epsilon) && (err.z < epsilon) && (err.w < epsilon);
}

XTD_MATH_FORCE_INLINE V4f lerp4f(V4f a, V4f b, f32 t) {
    return add4f(a, sc4f(sub4f(b, a), t));
}

//
// Vector 3
//

XTD_MATH_FORCE_INLINE V3f add3f(V3f a, V3f b) {
    V3f res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return res;
}
XTD_MATH_FORCE_INLINE V3f addsc3f(V3f a, f32 b) {
    V3f res;
    res.x = a.x + b;
    res.y = a.y + b;
    res.z = a.z + b;
    return res;
}
XTD_MATH_FORCE_INLINE V3f sub3f(V3f a, V3f b) {
    V3f res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return res;
}
XTD_MATH_FORCE_INLINE V3f neg3f(V3f a) {
    V3f res;
    res.x = -a.x;
    res.y = -a.y;
    res.z = -a.z;
    return res;
}
XTD_MATH_FORCE_INLINE V3f subsc3f(V3f a, f32 b) {
    V3f res;
    res.x = a.x - b;
    res.y = a.y - b;
    res.z = a.z - b;
    return res;
}
XTD_MATH_FORCE_INLINE V3f mul3f(V3f a, V3f b) {
    V3f res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;
    return res;
}
XTD_MATH_FORCE_INLINE V3f sc3f(V3f a, f32 b) {
    V3f res;
    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    return res;
}
XTD_MATH_FORCE_INLINE V3f div3f(V3f a, V3f b) {
    V3f res;
    res.x = a.x / b.x;
    res.y = a.y / b.y;
    res.z = a.z / b.z;
    return res;
}
XTD_MATH_FORCE_INLINE V3f divsc3f(V3f a, f32 b) {
    V3f res;
    f32 inv = 1.0f / b;
    res.x = a.x * inv;
    res.y = a.y * inv;
    res.z = a.z * inv;
    return res;
}

XTD_MATH_FORCE_INLINE f32 dot3f(V3f a, V3f b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

XTD_MATH_FORCE_INLINE f32 lengthSq3f(V3f a) {
    return dot3f(a, a);
}

XTD_MATH_FORCE_INLINE f32 length3f(V3f a) {
    return sqrtf(lengthSq3f(a));
}
XTD_MATH_FORCE_INLINE V3f normalized3f(V3f a) {
    f32 len = length3f(a);
	f32 invlen = 1.0f / len;
    return sc3f(a, invlen);
}

XTD_MATH_FORCE_INLINE V3f noz3f(V3f a) {
    f32 len = length3f(a);
	if (len == 0.0f)
		return a;
	f32 invlen = 1.0f / len;
    return sc3f(a, invlen);
}

XTD_MATH_FORCE_INLINE V3f abs3f(V3f a) {
    V3f res = {absF32(a.x), absF32(a.y), absF32(a.z)};
    return res;
}

XTD_MATH_FORCE_INLINE bool approxEqual3f(V3f a, V3f b, f32 epsilon) {
    V3f err = abs3f(sub3f(a, b));
    return (err.x < epsilon) && (err.y < epsilon) && (err.z < epsilon);
}

XTD_MATH_FORCE_INLINE V3f lerp3f(V3f a, V3f b, f32 t) {
    return add3f(a, sc3f(sub3f(b, a), t));
}

XTD_MATH_FORCE_INLINE V3f rand3fUniform3(V3f min, V3f max) {
    V3f v;
    v.x = randUniform(min.x, max.x);
    v.y = randUniform(min.y, max.y);
    v.z = randUniform(min.z, max.z);
    return v;
}

XTD_MATH_FORCE_INLINE V3f rand3fUniform(f32 min, f32 max) {
    V3f v;
    v.x = randUniform(min, max);
    v.y = randUniform(min, max);
    v.z = randUniform(min, max);
    return v;
}


XTD_MATH_FORCE_INLINE V3f rand3fUnitSphere() {
    // TODO: remove loop
    while (1)
    {
        V3f p = rand3fUniform(-1, 1);
        if (lengthSq3f(p) <= 1.f)
            return p;
    }
}

XTD_MATH_FORCE_INLINE V3f rand3fUnitLength() {
    return noz3f(rand3fUnitSphere());
}


XTD_MATH_FORCE_INLINE V3f cross3f(V3f a, V3f b) {
    V3f res;
    res.x = a.y * b.z - a.z * b.y; 
    res.y = a.z * b.x - a.x * b.z; 
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

//
// Vector 2
//

XTD_MATH_FORCE_INLINE V2f add2f(V2f a, V2f b) {
    V2f res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}
XTD_MATH_FORCE_INLINE V2f addsc2f(V2f a, f32 b) {
    V2f res;
    res.x = a.x + b;
    res.y = a.y + b;
    return res;
}
XTD_MATH_FORCE_INLINE V2f sub2f(V2f a, V2f b) {
    V2f res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}
XTD_MATH_FORCE_INLINE V2f neg2f(V2f a) {
    V2f res;
    res.x = -a.x;
    res.y = -a.y;
    return res;
}
XTD_MATH_FORCE_INLINE V2f subsc2f(V2f a, f32 b) {
    V2f res;
    res.x = a.x - b;
    res.y = a.y - b;
    return res;
}
XTD_MATH_FORCE_INLINE V2f mul2f(V2f a, V2f b) {
    V2f res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    return res;
}
XTD_MATH_FORCE_INLINE V2f sc2f(V2f a, f32 b) {
    V2f res;
    res.x = a.x * b;
    res.y = a.y * b;
    return res;
}
XTD_MATH_FORCE_INLINE V2f div2f(V2f a, V2f b) {
    V2f res;
    res.x = a.x / b.x;
    res.y = a.y / b.y;
    return res;
}
XTD_MATH_FORCE_INLINE V2f divsc2f(V2f a, f32 b) {
    V2f res;
    f32 inv = 1.0f / b;
    res.x = a.x * inv;
    res.y = a.y * inv;
    return res;
}

XTD_MATH_FORCE_INLINE f32 dot2f(V2f a, V2f b) {
    return a.x * b.x + a.y * b.y;
}

XTD_MATH_FORCE_INLINE f32 lengthSq2f(V2f a) {
    return dot2f(a, a);
}

XTD_MATH_FORCE_INLINE f32 length2f(V2f a) {
    return sqrtf(lengthSq2f(a));
}
XTD_MATH_FORCE_INLINE V2f normalized2f(V2f a) {
    f32 len = length2f(a);
	f32 invlen = 1.0f / len;
    return sc2f(a, invlen);
}

XTD_MATH_FORCE_INLINE V2f noz2f(V2f a) {
    f32 len = length2f(a);
	if (len == 0.0f)
		return a;
	f32 invlen = 1.0f / len;
    return sc2f(a, invlen);
}

XTD_MATH_FORCE_INLINE V2f abs2f(V2f a) {
    V2f res = {absF32(a.x), absF32(a.y)};
    return res;
}

XTD_MATH_FORCE_INLINE bool approxEqual2f(V2f a, V2f b, f32 epsilon) {
    V2f err = abs2f(sub2f(a, b));
    return (err.x < epsilon) && (err.y < epsilon);
}

XTD_MATH_FORCE_INLINE V2f lerp2f(V2f a, V2f b, f32 t) {
    return add2f(a, sc2f(sub2f(b, a), t));
}

XTD_MATH_FORCE_INLINE V2f rand2fUniform3(V2f min, V2f max) {
    V2f v;
    v.x = randUniform(min.x, max.x);
    v.y = randUniform(min.y, max.y);
    return v;
}

XTD_MATH_FORCE_INLINE V2f rand2fUniform(f32 min, f32 max) {
    V2f v;
    v.x = randUniform(min, max);
    v.y = randUniform(min, max);
    return v;
}


XTD_MATH_FORCE_INLINE V2f rand2fUnitCircle() {
    // TODO: remove loop
    while (1)
    {
        V2f p = rand2fUniform(-1, 1);
        if (lengthSq2f(p) <= 1.f)
            return p;
    }
}

XTD_MATH_FORCE_INLINE V2f rand2fUnitLength() {
    return noz2f(rand2fUnitCircle());
}

#ifdef __cplusplus
extern "C++" {

//
// Vector 4
//

XTD_MATH_FORCE_INLINE V4f operator+(V4f a, V4f b) {
    return add4f(a, b);
}
XTD_MATH_FORCE_INLINE V4f operator+(V4f a, f32 b) {
    return addsc4f(a, b);
}
XTD_MATH_FORCE_INLINE V4f operator+(f32 a, V4f b) {
    return addsc4f(b, a);
}
XTD_MATH_FORCE_INLINE V4f& operator+=(V4f& a, const V4f& b)
{
	a = add4f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V4f& operator+=(V4f& a, const f32& b)
{
	a = addsc4f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V4f operator-(V4f a, V4f b) {
    return sub4f(a, b);
}
XTD_MATH_FORCE_INLINE V4f operator-(V4f a) {
    return neg4f(a);
}
XTD_MATH_FORCE_INLINE V4f& operator-=(V4f& a, const V4f& b)
{
	a = sub4f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V4f& operator-=(V4f& a, const f32& b)
{
	a = subsc4f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V4f operator*(V4f a, V4f b) {
    return mul4f(a, b);
}
XTD_MATH_FORCE_INLINE V4f& operator*=(V4f& a, const V4f& b) {
    a = mul4f(a, b);
    return a;
}
XTD_MATH_FORCE_INLINE V4f operator*(V4f a, f32 b) {
    return sc4f(a, b);
}
XTD_MATH_FORCE_INLINE V4f operator*(f32 a, V4f b) {
    return sc4f(b, a);
}
XTD_MATH_FORCE_INLINE V4f& operator*=(V4f& a, f32 b) {
    a = sc4f(a, b);
    return a;
}
XTD_MATH_FORCE_INLINE V4f operator/(V4f a, V4f b) {
    return div4f(a, b);
}
XTD_MATH_FORCE_INLINE V4f operator/(V4f a, f32 b) {
    return divsc4f(a, b);
}

//
// Vector 3
//

XTD_MATH_FORCE_INLINE V3f operator+(V3f a, V3f b) {
    return add3f(a, b);
}
XTD_MATH_FORCE_INLINE V3f operator+(V3f a, f32 b) {
    return addsc3f(a, b);
}
XTD_MATH_FORCE_INLINE V3f operator+(f32 a, V3f b) {
    return addsc3f(b, a);
}
XTD_MATH_FORCE_INLINE V3f& operator+=(V3f& a, const V3f& b)
{
	a = add3f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V3f& operator+=(V3f& a, const f32& b)
{
	a = addsc3f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V3f operator-(V3f a, V3f b) {
    return sub3f(a, b);
}
XTD_MATH_FORCE_INLINE V3f operator-(V3f a) {
    return neg3f(a);
}
XTD_MATH_FORCE_INLINE V3f& operator-=(V3f& a, const V3f& b)
{
	a = sub3f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V3f& operator-=(V3f& a, const f32& b)
{
	a = subsc3f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V3f operator*(V3f a, V3f b) {
    return mul3f(a, b);
}
XTD_MATH_FORCE_INLINE V3f& operator*=(V3f& a, const V3f& b) {
    a = mul3f(a, b);
    return a;
}
XTD_MATH_FORCE_INLINE V3f operator*(V3f a, f32 b) {
    return sc3f(a, b);
}
XTD_MATH_FORCE_INLINE V3f operator*(f32 a, V3f b) {
    return sc3f(b, a);
}
XTD_MATH_FORCE_INLINE V3f& operator*=(V3f& a, f32 b) {
    a = sc3f(a, b);
    return a;
}
XTD_MATH_FORCE_INLINE V3f operator/(V3f a, V3f b) {
    return div3f(a, b);
}
XTD_MATH_FORCE_INLINE V3f operator/(V3f a, f32 b) {
    return divsc3f(a, b);
}

//
// Vector 2
//

XTD_MATH_FORCE_INLINE V2f operator+(V2f a, V2f b) {
    return add2f(a, b);
}
XTD_MATH_FORCE_INLINE V2f operator+(V2f a, f32 b) {
    return addsc2f(a, b);
}
XTD_MATH_FORCE_INLINE V2f operator+(f32 a, V2f b) {
    return addsc2f(b, a);
}
XTD_MATH_FORCE_INLINE V2f& operator+=(V2f& a, const V2f& b)
{
	a = add2f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V2f& operator+=(V2f& a, const f32& b)
{
	a = addsc2f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V2f operator-(V2f a, V2f b) {
    return sub2f(a, b);
}
XTD_MATH_FORCE_INLINE V2f operator-(V2f a) {
    return neg2f(a);
}
XTD_MATH_FORCE_INLINE V2f& operator-=(V2f& a, const V2f& b)
{
	a = sub2f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V2f& operator-=(V2f& a, const f32& b)
{
	a = subsc2f(a, b);
	return a;
}
XTD_MATH_FORCE_INLINE V2f operator*(V2f a, V2f b) {
    return mul2f(a, b);
}
XTD_MATH_FORCE_INLINE V2f& operator*=(V2f& a, const V2f& b) {
    a = mul2f(a, b);
    return a;
}
XTD_MATH_FORCE_INLINE V2f operator*(V2f a, f32 b) {
    return sc2f(a, b);
}
XTD_MATH_FORCE_INLINE V2f operator*(f32 a, V2f b) {
    return sc2f(b, a);
}
XTD_MATH_FORCE_INLINE V2f& operator*=(V2f& a, f32 b) {
    a = sc2f(a, b);
    return a;
}
XTD_MATH_FORCE_INLINE V2f operator/(V2f a, V2f b) {
    return div2f(a, b);
}
XTD_MATH_FORCE_INLINE V2f operator/(V2f a, f32 b) {
    return divsc2f(a, b);
}

//
// C++: Operator Overloaded versions
//

XTD_MATH_FORCE_INLINE f32 lengthSq(V4f a) {
    return lengthSq4f(a);
}
XTD_MATH_FORCE_INLINE f32 length(V4f a) {
    return length4f(a);
}
XTD_MATH_FORCE_INLINE V4f normalized(V4f a) {
    return normalized4f(a);
}
XTD_MATH_FORCE_INLINE V4f noz(V4f a) {
    return noz4f(a);
}


XTD_MATH_FORCE_INLINE f32 lengthSq(V3f a) {
    return lengthSq3f(a);
}
XTD_MATH_FORCE_INLINE f32 length(V3f a) {
    return length3f(a);
}
XTD_MATH_FORCE_INLINE V4f normalized(V3f a) {
    return normalized3f(a);
}
XTD_MATH_FORCE_INLINE V4f noz(V3f a) {
    return noz3f(a);
}

XTD_MATH_FORCE_INLINE f32 lengthSq(V2f a) {
    return lengthSq2f(a);
}
XTD_MATH_FORCE_INLINE f32 length(V2f a) {
    return length2f(a);
}
XTD_MATH_FORCE_INLINE V4f normalized(V2f a) {
    return normalized2f(a);
}
XTD_MATH_FORCE_INLINE V4f noz(V2f a) {
    return noz2f(a);
}

}
#endif

////////////////////////////////////////
//
//  Vector Utility functions
//



#if XTD_IS_COMPILER_GCC
#pragma GCC diagnostic pop
#endif

////////////////////////////////////////
//
//  Function Declarations
//

XTD_MATH_FUNC_DECL void XTD_InitStdRand();
XTD_MATH_FUNC_DECL void XTD_fprint4f(void* file, V4f a);
XTD_MATH_FUNC_DECL void XTD_fprint3f(void* file, V3f a);
XTD_MATH_FUNC_DECL void XTD_fprint2f(void* file, V2f a);


////////////////////////////////////////
////////////////////////////////////////
//
//  Implementation
//

#ifdef XTD_MATH_IMPLEMENTATION

#include <time.h>

XTD_MATH_FUNC void XTD_InitStdRand(){
    srand(time(NULL));
}

XTD_MATH_FUNC void XTD_fprint4f(void* file, V4f a)
{
    XTD_FPRINTF(file, "[%.4f,%.4f,%.4f,%.4f]", a.x, a.y, a.z, a.w);
}

XTD_MATH_FUNC void XTD_fprint3f(void* file, V3f a)
{
    XTD_FPRINTF(file, "[%.4f,%.4f,%.4f]", a.x, a.y, a.z);
}

XTD_MATH_FUNC void XTD_fprint2f(void* file, V2f a)
{
    XTD_FPRINTF(file, "[%.4f,%.4f]", a.x, a.y);
}

#endif

////////////////////////////////////////
////////////////////////////////////////
//
//  End of Implementation
//

#ifdef __cplusplus //End of extern "C"
}
#endif

#endif
