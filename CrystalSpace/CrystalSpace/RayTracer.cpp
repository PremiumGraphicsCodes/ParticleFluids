#include "RayTracer.h"
#include "SpaceHash3d.h"
#include "Octree.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	const auto e = 1.0e-12;

	class FaceItem : public IOctreeItem
	{
	public:
		explicit FaceItem(const Box3dd& box) :
			box(box)
		{
		}

		Box3dd getBoundingBox() override
		{
			return box;
		}

	private:
		Box3dd box;
	};

}


void RayTracer::buildSpace(const PolygonMesh& polygon, const double res)
{
	const auto bb = polygon.getBoundingBox();
	const auto xres = static_cast<size_t>(bb.getLength().x / res) + 1;
	const auto yres = static_cast<size_t>(bb.getLength().y / res) + 1;
	const auto zres = static_cast<size_t>(bb.getLength().z / res) + 1;
	std::array<size_t, 3> ress = { xres, yres, zres };

	const auto faces = polygon.getFaces();
	SpaceHash3d table(res, faces.size() * 3);

	const auto voxelSize = Vector3dd(res);
	Octree octree(bb);

	std::vector<IParticle*> particles;
	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		if (triangle.getArea() < e) {
			continue;
		}
		const auto smallBB = triangle.getBoundingBox();
		auto item = new FaceItem(smallBB);
		octree.add(item);

		/*
		for (float x = smallBB.getMinX(); x < smallBB.getMaxX() + e; x += voxelSize.x) {
			for (float y = smallBB.getMinY(); y < smallBB.getMaxY() + e; y += voxelSize.y) {
				for (float z = smallBB.getMinZ(); z < smallBB.getMaxZ() + e; z += voxelSize.z) {
					const Vector3dd p(x, y, z);
					const auto v1 = p - voxelSize * 0.5;// - 1.0e-3;
					const auto v2 = p + voxelSize * 0.5;// + 1.0e-3;
					Box3dd smallBox(v1, v2);
					if (Overlap::overlap(smallBox, triangle)) {
						particles.push_back(particle);
						table.add(particle);
					}
				}
			}
		}
		*/
	}
}