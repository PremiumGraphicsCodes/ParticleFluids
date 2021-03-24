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
#include "../../Crystal/Math/Sphere3d.h"


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
struct SphereObject
{
    Crystal::Math::Vector3dd         color;
    MaterialType    type;
    Crystal::Math::Sphere3d sphere;

    SphereObject( double r, Crystal::Math::Vector3dd pos, Crystal::Math::Vector3dd col, MaterialType mat )
    : sphere( pos, r )
    , color ( col )
    , type  ( mat )
    { /* DO_NOTHING */ }

    double intersect(const Crystal::Math::Ray3d& ray) const;

private:
};


#endif//__SPHERE_H__