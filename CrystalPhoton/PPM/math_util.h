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

inline Crystal::Math::Vector3dd reflect( const Crystal::Math::Vector3dd& a, const Crystal::Math::Vector3dd& b )
{
    auto dot = a.x * b.x + a.y * b.y + a.z * b.z;
    return Crystal::Math::Vector3dd(
        a.x - 2.0 * dot * b.x,
        a.y - 2.0 * dot * b.y,
        a.z - 2.0 * dot * b.z );
}

/////////////////////////////////////////////////////////////////////////////////////////
// Ray structure
/////////////////////////////////////////////////////////////////////////////////////////
struct Ray
{
    Crystal::Math::Vector3dd pos;
    Crystal::Math::Vector3dd dir;

    Ray()
    : pos(), dir()
    { /* DO_NOTHING */ }

    Ray( const Crystal::Math::Vector3dd& _position, const Crystal::Math::Vector3dd& _direction )
    : pos( _position ), dir( _direction )
    { /* DO_NOTHING */ }
};


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

    inline double intersect( const Ray& ray ) const
    {
        auto diff = pos - ray.pos;
        auto b = dot( diff, ray.dir );
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


/////////////////////////////////////////////////////////////////////////////////////////
// Random class
/////////////////////////////////////////////////////////////////////////////////////////
class Random
{
public:
    Random()
    { seed( 123456789 ); }

    Random( const unsigned int _seed )
    { seed( _seed ); }

    Random( const Random& v )
    : m_x( v.m_x ), m_y( v.m_y ), m_z( v.m_z ), m_w( v.m_w )
    { /* DO_NOTHING */ }

    inline void seed( const unsigned int _seed )
    {
        m_x = 123456789;
        m_y = 362436069;
        m_z = 521288629;
        m_w = ( _seed <= 0 ) ? 88675123 : _seed;
    }

    inline unsigned int get_uint()
    {
        unsigned int t = m_x ^ ( m_x << 11 );
        m_x = m_y;
        m_y = m_z;
        m_z = m_w;
        m_w = ( m_w ^ ( m_w >> 19 ) ) ^ ( t ^ ( t >> 8 ) );
        return m_w;
    }

    inline double get_double()
    { return static_cast<double>( get_uint() ) / 0xffffffffui32; }

    inline Random& operator = ( const Random& v )
    {
        m_x = v.m_x;
        m_y = v.m_y;
        m_z = v.m_z;
        m_w = v.m_w;
        return (*this);
    }

private:
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_z;
    unsigned int m_w;
};


#endif//__MATH_UTIL_H__
