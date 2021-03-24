#pragma once

#include "math_util.h"
#include "hitrecord.h"
#include "sphere.h"
#include "Scene.h"
#include <list>

namespace Crystal {
	namespace Photon {

class PhotonRay
{
public:
    Math::Ray3d ray;
    Math::Vector3dd flux;
};

class PhotonMap
{
public:
    void trace_photon(int s, Scene& scene);

    void density_estimation(Math::Vector3dd* color, int num_photon, std::list<HitRecord*>& hitpoints);

private:
    PhotonRay generate_photon_ray(int i);

    void trace_photon_ray(const Math::Ray3d& r, int dpt, const Math::Vector3dd& fl, const Math::Vector3dd& adj, int i, Scene& scene);
};

	}
}