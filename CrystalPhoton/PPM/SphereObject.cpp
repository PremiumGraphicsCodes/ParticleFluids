#include "SphereObject.h"

#include "../../CrystalSpace/CrystalAlgo/IntersectionAlgo.h"


double SphereObject::intersect(const Crystal::Math::Ray3d& ray) const
{
    auto diff = sphere.getCenter() - ray.getOrigin();
    auto b = dot( diff, ray.getDirection() );
    auto det = ( b * b ) - dot( diff, diff ) + sphere.getRadius() * sphere.getRadius();
    
    if (det < 0)
        return std::numeric_limits<double>::max();
    
    det = sqrt(det);
    auto t1 = b - det;
    if ( t1 >  D_EPS )
        return t1;
    
    auto t2 = b + det;
    if ( t2 > D_EPS )
        return t2;
    
    return std::numeric_limits<double>::max();
}
