//---------------------------------------------------------------------------------------
// File : math_util.h
// Desc : Math Utility.
//---------------------------------------------------------------------------------------

#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

//---------------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------------
#include <cmath>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Ray3d.h"


//---------------------------------------------------------------------------------------
// Constant Values
//---------------------------------------------------------------------------------------
static const double     D_PI  = 3.1415926535897932384626433832795;
static const double     D_INF = 1e20;
static const double     D_EPS = 1e-4;

/////////////////////////////////////////////////////////////////////////////////////////
// BoundingBox structure
/////////////////////////////////////////////////////////////////////////////////////////
struct BoundingBox
{
    Crystal::Math::Vector3dd mini;
    Crystal::Math::Vector3dd maxi;

    inline void merge( const Crystal::Math::Vector3dd& value )
    {
        mini.x = ( value.x < mini.x ) ? value.x : mini.x;
        mini.y = ( value.y < mini.y ) ? value.y : mini.y;
        mini.z = ( value.z < mini.z ) ? value.z : mini.z;

        maxi.x = ( value.x > maxi.x ) ? value.x : maxi.x;
        maxi.y = ( value.y > maxi.y ) ? value.y : maxi.y;
        maxi.z = ( value.z > maxi.z ) ? value.z : maxi.z;
    }

    inline void reset()
    {
        mini = Crystal::Math::Vector3dd(  D_INF,  D_INF,  D_INF );
        maxi = Crystal::Math::Vector3dd( -D_INF, -D_INF, -D_INF );
    }
};

#endif//__MATH_UTIL_H__
