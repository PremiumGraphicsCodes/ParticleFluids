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


double halton( const int b, int j );

inline Crystal::Math::Vector3dd mul(const Crystal::Math::Vector3dd& a, const Crystal::Math::Vector3dd& b)
{
    return Crystal::Math::Vector3dd(a.x * b.x, a.y * b.y, a.z * b.z);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Sphre structure
/////////////////////////////////////////////////////////////////////////////////////////
struct Sphere
{
    Crystal::Math::Vector3dd pos;
    double  r;

    Sphere( const Crystal::Math::Vector3dd& _pos, double _radius )
    : pos( _pos ), r( _radius )
    { /* DO_NOTHING */ }

    inline double intersect( const Crystal::Math::Ray3d& ray ) const
    {
        auto diff = pos - ray.getOrigin();
        auto b = dot( diff, ray.getDirection() );
        auto det = ( b * b ) - dot( diff, diff ) + r * r;

        if (det < 0)
            return D_INF;

        det = sqrt(det);
        auto t1 = b - det;
        if ( t1 >  D_EPS )
            return t1;

        auto t2 = b + det;
        if ( t2 > D_EPS )
            return t2;

        return D_INF;
    }
};


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
