#include "Scene.h"

using namespace Crystal::Math;
using namespace Crystal::Photon;

bool Scene::intersect(const Ray3d& r, double& t, int& id)
{
    int n = sizeof(sph) / sizeof(sph[0]);
    auto d = D_INF;
    t = D_INF;
    for (int i = 0; i < n; i++)
    {
        d = sph[i].intersect(r);
        if (d < t)
        {
            t = d;
            id = i;
        }
    }

    return (t < D_INF);
}
