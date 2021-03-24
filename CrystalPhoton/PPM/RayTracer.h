#pragma once

#include "Scene.h"

namespace Crystal {
    namespace Photon {

class RayTracer
{
public:
    void trace_ray(int w, int h, Scene& scene);

private:
    void trace(const Ray& r, int dpt, const Vector3& fl, const Vector3& adj, int i, Scene& scene);
    
};

    }
}