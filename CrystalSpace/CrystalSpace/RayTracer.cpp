#include "RayTracer.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;


void RayTracer::build(const Box3dd& space, const int level)
{
	octree.init(space, level);
}

void RayTracer::add(RayTraceItem* item)
{
	octree.add(item);
}

// ref https://riyaaaaasan.hatenablog.com/entry/2018/05/08/224545

std::list<const LinearOctreeCell*> RayTracer::trace(const Ray3d& ray, const double pitch)
{
	//const auto grid = octree.calculateGridIndex(ray.getOrigin()); // ���C�̏����ʒu�����Ԃ̃O���b�h���W���Z�o
	const auto dir = glm::normalize(ray.getDirection());

	Vector3dd pos = ray.getOrigin(); // �����ʒu
	std::list<const LinearOctreeCell*> cells; // �Փ˃��X�g�i���X�g�̒��g�͋�ԃn�b�V���j

	double length = 0.0;
	while (octree.getRootSpace().isInside(pos)) {
		const auto nextPos = pos + dir * pitch;
		auto index = octree.getIndex(Box3dd(pos, nextPos));
		auto level = index.getLevelAndNumber().first;
		while (level >= 0) {
			auto cell = octree.findCell(index);
			if (cell != nullptr) {
				cells.push_back(cell);
			}
			if (level == 0) {
				break;
			}
			index = index.getParentIndex();
			level = index.getLevelAndNumber().first;
		}

		pos = nextPos;
		length += pitch;
	}

	return cells;
}

/*
std::list<const LinearOctreeCell*> RayTracer::traceLv0(const Ray3d& ray, const double pitch)
{
	octree.findCell(LinearOctreeIndex)
}
*/