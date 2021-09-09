#include "RayTracer.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;


void RayTracer::buildSpace(const PolygonMesh& polygon, const Box3dd& space, const int level)
{
	const auto faces = polygon.getFaces();

	octree.init(space, level);

	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		LinearOctreeItem* item = new LinearOctreeItem(triangle.getBoundingBox());
		octree.add(item);
	}
}

// ref https://riyaaaaasan.hatenablog.com/entry/2018/05/08/224545

std::list<const LinearOctreeCell*> RayTracer::trace(const Ray3d& ray, const double pitch)
{
	//const auto grid = octree.calculateGridIndex(ray.getOrigin()); // ���C�̏����ʒu�����Ԃ̃O���b�h���W���Z�o
	const auto dir = ray.getDirection();

	Vector3dd pos = ray.getOrigin(); // �����ʒu
	std::list<const LinearOctreeCell*> cells; // �Փ˃��X�g�i���X�g�̒��g�͋�ԃn�b�V���j

	double length = 0.0;
	while (octree.getRootSpace().isInside(pos)) {
		const auto nextPos = pos + ray.getDirection() * length;
		auto index = octree.getIndex(Box3dd(pos, nextPos));
		while (index.getLevelAndNumber().first >= 0) {
			auto cell = octree.findCell(index);
			if (cell != nullptr) {
				cells.push_back(cell);
			}
			index = index.getParentIndex();
		}

		pos = nextPos;
	}

	return cells;
}
