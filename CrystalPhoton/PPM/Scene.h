#pragma once

#include <list>
#include <vector>
#include <array>

#include "math_util.h"
#include "hitrecord.h"
#include "SphereObject.h"

namespace Crystal {
    namespace Photon {

class Scene {
public:
    Scene();

    std::list<HitRecord*>               hitpoints;
    std::vector<std::list<HitRecord*> > hash_grid;
    double                              hash_s;
    BoundingBox                         hpbbox;

    std::vector<SphereObject> sph;

    bool intersect(const Math::Ray3d& r, double& t, int& id);
};

    }
}