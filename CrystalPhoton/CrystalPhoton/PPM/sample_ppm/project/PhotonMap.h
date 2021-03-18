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
            Ray ray;
            Vector3 flux;
        };

        class PhotonMap
        {
        public:
            void trace_photon(int s, Scene& scene);

            void density_estimation(Vector3* color, int num_photon, std::list<HitRecord*>& hitpoints);

        private:
            PhotonRay generate_photon_ray(int i);

            void trace_photon_ray(const Ray& r, int dpt, const Vector3& fl, const Vector3& adj, int i, Scene& scene);
        };

	}
}