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
#include <bitmap.h>
#include <math_util.h>
#include <list>
#include <vector>
#include <chrono>
#include <sphere.h>
#include <hitrecord.h>


namespace /* anonymous */ {

constexpr double ALPHA = 0.7; // the alpha parameter of PPM

std::list<HitRecord*>               hitpoints;
std::vector<std::list<HitRecord*> > hash_grid;
double                              hash_s;
BoundingBox                         hpbbox;
SphereObject sph[] = 
{
    // Scene: radius, position, color, material
    SphereObject(1e5,  Vector3( 1e5 + 1,   40.8,       81.6 ), Vector3( 0.99, 0.01, 0.01 ),  MaterialType::Matte ),   //Right
    SphereObject(1e5,  Vector3(-1e5 + 99,  40.8,       81.6 ), Vector3( 0.01, 0.01, 0.99 ),  MaterialType::Matte ),   //Left
    SphereObject(1e5,  Vector3( 50,        40.8,        1e5 ), Vector3( 0.75, 0.75, 0.75 ),  MaterialType::Matte ),   //Back
    SphereObject(1e5,  Vector3( 50,        40.8, -1e5 + 170 ), Vector3( 0.0,  0.0,  0.0  ),  MaterialType::Matte ),   //Front
    SphereObject(1e5,  Vector3( 50,         1e5,       81.6 ), Vector3( 0.75, 0.75, 0.75 ),  MaterialType::Matte ),   //Bottomm
    SphereObject(1e5,  Vector3( 50, -1e5 + 81.6,       81.6 ), Vector3( 0.75, 0.75, 0.75 ),  MaterialType::Matte ),   //Top
    SphereObject(16.5, Vector3( 27,        16.5,         47 ), Vector3( 0.25, 0.85, 0.25 ),  MaterialType::Mirror),   //Mirror
    SphereObject(16.5, Vector3( 73,        16.5,         88 ), Vector3( 0.99, 0.99, 0.99 ),  MaterialType::Glass ),   //Glass
    SphereObject(8.5,  Vector3( 50,         8.5,         60 ), Vector3( 0.75, 0.75, 0.75 ),  MaterialType::Matte ),   //Middle
};

} // namespace /* anonymous */


//-------------------------------------------------------------------------------------------
//      ハッシュキーを取得します.
//-------------------------------------------------------------------------------------------
inline unsigned int hash
(
    const int ix,
    const int iy,
    const int iz
) 
{
    return (unsigned int)(
        (ix * 73856093) ^
        (iy * 19349663) ^
        (iz * 83492791)) % hash_grid.size();
}

//-------------------------------------------------------------------------------------------
//      ハッシュグリッドを構築します.
//-------------------------------------------------------------------------------------------
void build_hash_grid
(
    const int w,
    const int h
)
{
    // heuristic for initial radius
    auto size = hpbbox.maxi - hpbbox.mini;
    auto irad = ((size.x + size.y + size.z) / 3.0) / ((w + h) / 2.0) * 2.0;

    // determine hash table size
    // we now find the bounding box of all the measurement points inflated by the initial radius
    hpbbox.reset();
    auto photon_count = 0;
    for( auto itr = hitpoints.begin(); itr != hitpoints.end(); ++itr )
    {
        auto hp  = (*itr);
        hp->r2   = irad *irad;
        hp->n    = 0;
        hp->flux = Vector3();

        photon_count++;
        hpbbox.merge( hp->pos - irad );
        hpbbox.merge( hp->pos + irad );
    }

    // make each grid cell two times larger than the initial radius
    hash_s = 1.0 / (irad * 2.0);

    // build the hash table
    hash_grid.resize( photon_count );
    hash_grid.shrink_to_fit();
    for( auto itr = hitpoints.begin(); itr != hitpoints.end(); ++itr )
    {
        auto hp = (*itr);
        auto min = ((hp->pos - irad) - hpbbox.mini) * hash_s;
        auto max = ((hp->pos + irad) - hpbbox.mini) * hash_s;

        for (int iz = abs(int(min.z)); iz <= abs(int(max.z)); iz++)
        {
            for (int iy = abs(int(min.y)); iy <= abs(int(max.y)); iy++)
            {
                for (int ix = abs(int(min.x)); ix <= abs(int(max.x)); ix++)
                {
                    int hv = hash( ix, iy, iz );
                    hash_grid[ hv ].push_back( hp );
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------
//      交差判定を行います.
//-------------------------------------------------------------------------------------------
inline bool intersect( const Ray &r, double &t, int &id )
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

    return ( t < D_INF );
}

class RayTracer
{
public:
    void trace_ray(int w, int h)
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
                trace(Ray(cam.pos + d * 140, normalize(d)), 0, Vector3(), Vector3(1, 1, 1), idx);
            }
        }
        fprintf(stdout, "\n");
        auto end = std::chrono::system_clock::now();
        auto dif = end - start;
        fprintf(stdout, "Ray Tracing Pass : %lld(msec)\n", std::chrono::duration_cast<std::chrono::milliseconds>(dif).count());

        start = std::chrono::system_clock::now();

        // build the hash table over the measurement points
        build_hash_grid(w, h);

        end = std::chrono::system_clock::now();
        dif = end - start;
        fprintf(stdout, "Build Hash Grid : %lld(msec)\n", std::chrono::duration_cast<std::chrono::milliseconds>(dif).count());
    }

private:
    void trace(const Ray& r, int dpt, const Vector3& fl, const Vector3& adj, int i)
    {
        double t;
        int id;

        dpt++;
        if (!intersect(r, t, id) || (dpt >= 20))
            return;

        auto d3 = dpt * 3;
        const auto& obj = sph[id];
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
                hitpoints.push_back(hp);

                // find the bounding box of all the measurement points
                hpbbox.merge(x);
            }

        }
        else if (obj.type == MaterialType::Mirror)
        {
            trace(Ray(x, reflect(r.dir, n)), dpt, mul(f, fl), mul(f, adj), i);
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
                return trace(lr, dpt, mul(f, fl), mul(f, adj), i);

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
                trace(lr, dpt, ffl, fa * Re, i);
                trace(rr, dpt, ffl, fa * (1.0 - Re), i);
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

    hpbbox.reset();

    RayTracer rayTracer;
    rayTracer.trace_ray(w, h);

    Crystal::Photon::PhotonMap photonMap;
    photonMap.trace_photon( s );
    photonMap.density_estimation( c, s );

    save_to_bmp( "image.bmp", w, h, &c[0].x, 2.2 );

    delete [] c;
    c = nullptr;

    return 0;
}
