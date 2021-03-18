#include "PhotonMap.h"

#include "SpaceHash.h"

#include <chrono>

using namespace Crystal::Photon;

namespace {

    inline bool intersect(const Ray& r, double& t, int& id, Scene& scene)
    {
        int n = sizeof(scene.sph) / sizeof(scene.sph[0]);
        auto d = D_INF;
        t = D_INF;
        for (int i = 0; i < n; i++)
        {
            d = scene.sph[i].intersect(r);
            if (d < t)
            {
                t = d;
                id = i;
            }
        }

        return (t < D_INF);
    }
}

void PhotonMap::trace_photon(int s, Scene& scene)
{
    auto start = std::chrono::system_clock::now();

    // trace photon rays with multi-threading
    auto vw = Vector3(1, 1, 1);

#pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < s; i++)
    {
        auto p = 100.0 * (i + 1) / s;
        fprintf(stdout, "\rPhotonPass %5.2f%%", p);
        int m = 1000 * i;
        for (int j = 0; j < 1000; j++)
        {
            PhotonRay pray = generate_photon_ray(m + j);
            trace_photon_ray(pray.ray, 0, pray.flux, vw, m + j, scene);
        }
    }

    fprintf(stdout, "\n");
    auto end = std::chrono::system_clock::now();
    auto dif = end - start;
    fprintf(stdout, "Photon Tracing Pass : %lld(sec)\n", std::chrono::duration_cast<std::chrono::seconds>(dif).count());
}

void PhotonMap::density_estimation(Vector3* color, int num_photon, std::list<HitRecord*>& hitpoints)
{
    // density estimation
    for (auto itr = hitpoints.begin(); itr != hitpoints.end(); ++itr)
    {
        auto hp = (*itr);
        auto i = hp->idx;
        color[i] = color[i] + hp->flux * (1.0 / (D_PI * hp->r2 * num_photon * 1000.0));
    }
}

PhotonRay PhotonMap::generate_photon_ray(int i)
{
    // generate a photon ray from the point light source with QMC
    PhotonRay photonRay;
    photonRay.flux = Vector3(2500, 2500, 2500) * (D_PI * 4.0); // flux
    auto p = 2.0 * D_PI * halton(0, i);
    auto t = 2.0 * acos(sqrt(1. - halton(1, i)));
    auto st = sin(t);

    photonRay.ray.dir = Vector3(cos(p) * st, cos(t), sin(p) * st);
    photonRay.ray.pos = Vector3(50, 60, 85);
    return photonRay;
}

void PhotonMap::trace_photon_ray(const Ray& r, int dpt, const Vector3& fl, const Vector3& adj, int i, Scene& scene)
{
    double t;
    int id;

    dpt++;
    if (!intersect(r, t, id, scene) || (dpt >= 20)) {
        return;
    }

    auto d3 = dpt * 3;
    const auto& obj = scene.sph[id];
    auto x = r.pos + r.dir * t, n = normalize(x - obj.pos);
    auto f = obj.color;
    auto nl = (dot(n, r.dir) < 0) ? n : n * -1;
    auto p = (f.x > f.y && f.x > f.z) ? f.x : (f.y > f.z) ? f.y : f.z;

    if (obj.type == MaterialType::Matte)
    {
        {
            // photon ray
            // find neighboring measurement points and accumulate flux via progressive density estimation
            auto hh = (x - scene.hpbbox.mini) * scene.hash_s;
            auto ix = abs(int(hh.x));
            auto iy = abs(int(hh.y));
            auto iz = abs(int(hh.z));
            // strictly speaking, we should use #pragma omp critical here.
            // it usually works without an artifact due to the fact that photons are 
            // rarely accumulated to the same measurement points at the same time (especially with QMC).
            // it is also significantly faster.
            {
                auto list = scene.hash_grid[SpaceHash::hash(ix, iy, iz, scene)];
                for (auto itr = list.begin(); itr != list.end(); itr++)
                {
                    auto hp = (*itr);
                    auto v = hp->pos - x;
                    // check normals to be closer than 90 degree (avoids some edge brightning)
                    if ((dot(hp->nrm, n) > 1e-3) && (dot(v, v) <= hp->r2))
                    {
                        // unlike N in the paper, hp->n stores "N / ALPHA" to make it an integer value
                        auto g = (hp->n * ALPHA + ALPHA) / (hp->n * ALPHA + 1.0);
                        hp->r2 = hp->r2 * g;
                        hp->n++;
                        hp->flux = (hp->flux + mul(hp->f, fl) / D_PI) * g;
                    }
                }
            }

            // use QMC to sample the next direction
            auto r1 = 2.0 * D_PI * halton(d3 - 1, i);
            auto r2 = halton(d3 + 0, i);
            auto r2s = sqrt(r2);
            auto w = nl;
            auto u = normalize(cross((fabs(w.x) > .1 ? Vector3(0, 1, 0) : Vector3(1, 0, 0)), w));
            auto v = cross(w, u);
            auto d = normalize(u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2));

            if (halton(d3 + 1, i) < p)
                trace_photon_ray(Ray(x, d), dpt, mul(f, fl) * (1. / p), mul(f, adj), i, scene);
        }

    }
    else if (obj.type == MaterialType::Mirror)
    {
        trace_photon_ray(Ray(x, reflect(r.dir, n)), dpt, mul(f, fl), mul(f, adj), i, scene);
    }
    else
    {
        Ray lr(x, reflect(r.dir, n));
        auto into = dot(n, nl) > 0.0;
        auto nc = 1.0;
        auto nt = 1.5;
        auto nnt = (into) ? nc / nt : nt / nc;
        auto ddn = dot(r.dir, nl);
        auto cos2t = 1 - nnt * nnt * (1 - ddn * ddn);

        // total internal reflection
        if (cos2t < 0) {
            return trace_photon_ray(lr, dpt, mul(f, fl), mul(f, adj), i, scene);
        }

        auto td = normalize(r.dir * nnt - n * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t))));
        auto a = nt - nc;
        auto b = nt + nc;
        auto R0 = a * a / (b * b);
        auto c = 1 - (into ? -ddn : dot(td, n));
        auto Re = R0 + (1 - R0) * c * c * c * c * c;
        auto P = Re;
        Ray  rr(x, td);
        auto fa = mul(f, adj);
        auto ffl = mul(f, fl);

        (halton(d3 - 1, i) < P)
            ? trace_photon_ray(lr, dpt, ffl, fa * Re, i, scene)
            : trace_photon_ray(rr, dpt, ffl, fa * (1.0 - Re), i, scene);
    }
}