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

std::list<LinearOctreeCell*> RayTracer::trace(const Ray3d& ray)
{
	const auto grid = octree.calculateGridIndex(ray.getOrigin()); // ���C�̏����ʒu�����Ԃ̃O���b�h���W���Z�o
	const auto dir = ray.getDirection();

	// ���C�����x�N�g���̕�������1�X�e�b�v�ɂ�����O���b�h�̈ړ��f�[�^���Z�o
	std::array<int, 3> gridForward;
	gridForward[0] = (dir.x >= 0.0f ? 1 : -1);
	gridForward[1] = (dir.y >= 0.0f ? 1 : -1);
	gridForward[2] = (dir.z >= 0.0f ? 1 : -1);

	const Vector3dd pos = octree.calculateAABB(grid).getMin(); // �����ʒu
	auto nextGrid = grid;
	std::list<LinearOctreeCell*> cells; // �Փ˃��X�g�i���X�g�̒��g�͋�ԃn�b�V���j

	while (octree.getRootSpace().isInside(pos)) {
		/*
		// �O���b�h�����ԃn�b�V���Z�o
		uint32_t number = SpaceOctree::Get3DMortonOrder(grid);

		// ��ԃn�b�V�����A���[�g��Ԃ܂ők���āA�Փ˃��X�g�Ɋi�[���Ă����i���݂���ꍇ�̂݁j
		for (int i = 0; i <= factory->GetSplitLevel(); i++) {
			uint32_t idx = static_cast<uint32_t>((number >> i * 3) + PrecomputedConstants::PowNumbers<8, 8>::Get(factory->GetSplitLevel() - i) / 7);
			if (factory->BoxExists(idx)) {
				colliderList.insert(idx);
			}
		}
		*/

		// ���̃O���b�h
		for (int i = 0; i < 3; ++i) {
			nextGrid[i] = grid[i] + gridForward[i];
		}
		// ���̍��W
		const auto nextpos = octree.calculateAABB(grid).getMin();

		/*

		// ���C�x�N�g������AX�����AY�����AZ�����̃O���b�h�ɓ��B���鎞�̃��C�x�N�g���̌W�����Z�o 
		float ax = ray.dir.x != 0.0f ? std::abs((nextpos.x - pos.x) / rayForward.x) : FLT_MAX;
		float ay = ray.dir.y != 0.0f ? std::abs((nextpos.y - pos.y) / rayForward.y) : FLT_MAX;
		float az = ray.dir.z != 0.0f ? std::abs((nextpos.z - pos.z) / rayForward.z) : FLT_MAX;

		// �ŒZ�œ��B����O���b�h�̒T��
		if (ax < ay && ax < az) {
			pos += rayForward * ax;
			grid.x += gridForward.x;
		}
		else if (ay < ax && ay < az) {
			pos += rayForward * ay;
			grid.y += gridForward.y;
		}
		else if (az < ax && az < ay) {
			pos += rayForward * az;
			grid.z += gridForward.z;
		}
		else {
			pos += rayForward;
			grid += gridForward;
		}
		*/
	}

	return cells;
}
