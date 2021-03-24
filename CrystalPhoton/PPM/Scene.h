#pragma once

#include <list>
#include <vector>
#include <array>

#include "math_util.h"
#include "hitrecord.h"
#include "sphere.h"

namespace Crystal {
    namespace Photon {

class Scene {
public:
    std::list<HitRecord*>               hitpoints;
    std::vector<std::list<HitRecord*> > hash_grid;
    double                              hash_s;
    BoundingBox                         hpbbox;
    std::array<SphereObject, 9> sph =
    {
        // Scene: radius, position, color, material
        SphereObject(1e5,  Vector3(1e5 + 1,   40.8,       81.6), Vector3(0.99, 0.01, 0.01),  MaterialType::Matte),   //Right
        SphereObject(1e5,  Vector3(-1e5 + 99,  40.8,       81.6), Vector3(0.01, 0.01, 0.99),  MaterialType::Matte),   //Left
        SphereObject(1e5,  Vector3(50,        40.8,        1e5), Vector3(0.75, 0.75, 0.75),  MaterialType::Matte),   //Back
        SphereObject(1e5,  Vector3(50,        40.8, -1e5 + 170), Vector3(0.0,  0.0,  0.0),  MaterialType::Matte),   //Front
        SphereObject(1e5,  Vector3(50,         1e5,       81.6), Vector3(0.75, 0.75, 0.75),  MaterialType::Matte),   //Bottomm
        SphereObject(1e5,  Vector3(50, -1e5 + 81.6,       81.6), Vector3(0.75, 0.75, 0.75),  MaterialType::Matte),   //Top
        SphereObject(16.5, Vector3(27,        16.5,         47), Vector3(0.25, 0.85, 0.25),  MaterialType::Mirror),   //Mirror
        SphereObject(16.5, Vector3(73,        16.5,         88), Vector3(0.99, 0.99, 0.99),  MaterialType::Glass),   //Glass
        SphereObject(8.5,  Vector3(50,         8.5,         60), Vector3(0.75, 0.75, 0.75),  MaterialType::Matte),   //Middle
    };
};

    }
}