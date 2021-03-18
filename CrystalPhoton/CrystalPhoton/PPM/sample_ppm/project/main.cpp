//-------------------------------------------------------------------------------------------
// File : main.cpp
// Desc : expanded smallppm (code is exactly the same as smallppm.cpp but with more comments)
//        Original Code by T.Hachisuka (http://users-cs.au.dk/toshiya/)
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <vector>
#include <chrono>

#include "bitmap.h"
#include "math_util.h"
#include "sphere.h"
#include "hitrecord.h"

#include "Scene.h"
#include "SpaceHash.h"

#include <array>

using namespace Crystal::Photon;

//-------------------------------------------------------------------------------------------
//      交差判定を行います.
//-------------------------------------------------------------------------------------------
inline bool intersect( const Ray &r, double &t, int &id, Scene& scene )
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

    return ( t < D_INF );
}

class RayTracer
{
public:
    void trace_ray(int w, int h, Scene& scene)
    {
        auto start = std::chrono::system_clock::now();

        // trace eye rays and store measurement points
        Ray cam(
            Vector3(50, 48, 295.6),
            normalize(Vector3(0, -0.042612, -1))
        );
        auto cx = Vector3(w * 0.5135 / h, 0, 0);
        auto cy = normalize(cross(cx, cam.dir)) * 0.5135;

        for (int y = 0; y < h; y++)
        {
            fprintf(stdout, "\rHitPointPass %5.2f%%", 100.0 * y / (h - 1));
            for (int x = 0; x < w; x++)
            {
                auto idx = x + y * w;
                auto d = cx * ((x + 0.5) / w - 0.5) + cy * (-(y + 0.5) / h + 0.5) + cam.dir;
                trace(Ray(cam.pos + d * 140, normalize(d)), 0, Vector3(), Vector3(1, 1, 1), idx, scene);
            }
        }
        fprintf(stdout, "\n");
        auto end = std::chrono::system_clock::now();
        auto dif = end - start;
        fprintf(stdout, "Ray Tracing Pass : %lld(msec)\n", std::chrono::duration_cast<std::chrono::milliseconds>(dif).count());

        start = std::chrono::system_clock::now();

        // build the hash table over the measurement points
        SpaceHash::build_hash_grid(w, h, scene);

        end = std::chrono::system_clock::now();
        dif = end - start;
        fprintf(stdout, "Build Hash Grid : %lld(msec)\n", std::chrono::duration_cast<std::chrono::milliseconds>(dif).count());
    }

private:
    void trace(const Ray& r, int dpt, const Vector3& fl, const Vector3& adj, int i, Scene& scene)
    {
        double t;
        int id;

        dpt++;
        if (!intersect(r, t, id, scene) || (dpt >= 20))
            return;

        auto d3 = dpt * 3;
        const auto& obj = scene.sph[id];
        auto x = r.pos + r.dir * t, n = normalize(x - obj.pos);
        auto f = obj.color;
        auto nl = (dot(n, r.dir) < 0) ? n : n * -1;
        auto p = (f.x > f.y && f.x > f.z) ? f.x : (f.y > f.z) ? f.y : f.z;

        if (obj.type == MaterialType::Matte)
        {
            {
                // eye ray
                // store the measurment point
                auto hp = new HitRecord;
                hp->f = mul(f, adj);
                hp->pos = x;
                hp->nrm = n;
                hp->idx = i;
                scene.hitpoints.push_back(hp);

                // find the bounding box of all the measurement points
                scene.hpbbox.merge(x);
            }

        }
        else if (obj.type == MaterialType::Mirror)
        {
            trace(Ray(x, reflect(r.dir, n)), dpt, mul(f, fl), mul(f, adj), i, scene);
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
            if (cos2t < 0)
                return trace(lr, dpt, mul(f, fl), mul(f, adj), i, scene);

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

            {
                // eye ray (trace both rays)
                trace(lr, dpt, ffl, fa * Re, i, scene);
                trace(rr, dpt, ffl, fa * (1.0 - Re), i, scene);
            }
        }
    }

};

#include "PhotonMap.h"


int main(int argc, char **argv) 
{
    auto w = 512;      // 画像の横幅.
    auto h = 512;      // 画像の縦幅.
    auto s = 1000;     // s * 1000 photon paths will be traced
    auto c = new Vector3[ w * h ];

    Scene scene;
    scene.hpbbox.reset();

    RayTracer rayTracer;
    rayTracer.trace_ray(w, h, scene);

    Crystal::Photon::PhotonMap photonMap;
    photonMap.trace_photon( s, scene );
    photonMap.density_estimation( c, s, scene.hitpoints );

    save_to_bmp( "image.bmp", w, h, &c[0].x, 2.2 );

    delete [] c;
    c = nullptr;

    return 0;
}
