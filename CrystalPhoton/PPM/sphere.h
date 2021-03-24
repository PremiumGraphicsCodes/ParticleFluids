//------------------------------------------------------------------------------
// File : sphere.h
// Desc : Sphere Object.
//------------------------------------------------------------------------------

#ifndef __SPHERE_H__
#define __SPHERE_H__


//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "math_util.h"


////////////////////////////////////////////////////////////////////////////////
// MaterialType
////////////////////////////////////////////////////////////////////////////////
enum MaterialType
{
    Matte = 0,  // Diffuse
    Mirror,     // Specular
    Glass,      // Refract
};


////////////////////////////////////////////////////////////////////////////////
// SphereObject structure
////////////////////////////////////////////////////////////////////////////////
struct SphereObject : public Sphere
{
    Crystal::Math::Vector3dd         color;
    MaterialType    type;

    SphereObject( double r, Crystal::Math::Vector3dd pos, Crystal::Math::Vector3dd col, MaterialType mat )
    : Sphere( pos, r )
    , color ( col )
    , type  ( mat )
    { /* DO_NOTHING */ }
};


#endif//__SPHERE_H__