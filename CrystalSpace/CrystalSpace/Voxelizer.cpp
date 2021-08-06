#include "Voxelizer.h"

#define VOXELIZER_IMPLEMENTATION

#include "../ThirdParty/voxelizer/voxelizer.h"
#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	vx_mesh_t* toMesh(const PolygonMesh& polygon)
	{
		const auto positions = polygon.getPositions();
		const auto vertices = polygon.getVertices();
		const auto faces = polygon.getFaces();

		std::vector<int> indices;
		for (const auto& f : faces) {
			indices.push_back(vertices[f.getV1()].positionId);
			indices.push_back(vertices[f.getV2()].positionId);
			indices.push_back(vertices[f.getV3()].positionId);
		}

		auto mesh = vx_mesh_alloc(positions.size(), indices.size());

		for (int i = 0; i < positions.size(); ++i) {
			mesh->vertices[i].x = positions[i].x;
			mesh->vertices[i].y = positions[i].y;
			mesh->vertices[i].z = positions[i].z;
		}
		for (int i = 0; i < indices.size(); ++i) {
			mesh->indices[i] = indices[i];
		}

		return mesh;
	}

	vx_aabb_t* calculateAABB(vx_mesh_t* m)
	{
		vx_aabb_t* meshaabb = NULL;

		for (size_t i = 0; i < m->nindices; i += 3) {
			vx_triangle_t triangle;
			unsigned int i1, i2, i3;

			VX_ASSERT(m->indices[i + 0] < m->nvertices);
			VX_ASSERT(m->indices[i + 1] < m->nvertices);
			VX_ASSERT(m->indices[i + 2] < m->nvertices);

			i1 = m->indices[i + 0];
			i2 = m->indices[i + 1];
			i3 = m->indices[i + 2];

			triangle.p1 = m->vertices[i1];
			triangle.p2 = m->vertices[i2];
			triangle.p3 = m->vertices[i3];

			if (!meshaabb) {
				meshaabb = VX_MALLOC(vx_aabb_t, 1);
				*meshaabb = vx__triangle_aabb(&triangle);
			}
			else {
				vx_aabb_t naabb = vx__triangle_aabb(&triangle);
				*meshaabb = vx__aabb_merge(meshaabb, &naabb);
			}
		}
		return meshaabb;
	}
}

void Voxelizer::voxelize(const PolygonMesh& polygon, const float res)
{
	vx_point_cloud_t* result;

	auto mesh = toMesh(polygon);

	const float precision = 0.0;//0.01;

	// Run voxelization
	result = vx_voxelize_pc(mesh, res, res, res, precision);

	for (int i = 0; i < result->nvertices; ++i) {
		const auto v = result->vertices[i];
		Vector3df p( v.x, v.y, v.z);
		this->points.push_back(p);
	}

	/*
	const auto width = 10;
	const auto height = 10;
	const auto depth = 10;
	auto result_volume = vx_voxelize_snap_3dgrid(mesh, width, height, depth);
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			for (int k = 0; k < depth; ++k) {
				auto index = i + i * width + i * (width * height);
				auto v = result_volume[index];
			}
		}
	}
	//result_volume.[0][0][0];
	*/

	vx_point_cloud_free(result);
	vx_mesh_free(mesh);
}

void Voxelizer::voxelize(const PolygonMesh& polygon, const std::array<int, 3>& res)
{
	vx_aabb_t* aabb = NULL;
	vx_aabb_t* meshaabb = NULL;
	float ax, ay, az;

	const auto bb = polygon.getBoundingBox();
	const auto length = bb.getLength();

	auto m = toMesh(polygon);

	const float resx = length.x / res[0];
	const float resy = length.y / res[1];
	const float resz = length.z / res[2];

	vx_point_cloud_t* pc = vx_voxelize_pc(m, resx, resy, resz, 0.0);

	/*
	for (size_t i = 0; i < pc->nvertices; ++i) {
		ox = pc->vertices[i].x + fabs(aabb->min.x);
		oy = pc->vertices[i].y + fabs(aabb->min.y);
		oz = pc->vertices[i].z + fabs(aabb->min.z);

		VX_ASSERT(ox >= 0.f);
		VX_ASSERT(oy >= 0.f);
		VX_ASSERT(oz >= 0.f);

		ix = (ax == 0.0) ? 0 : (ox / ax) * (width - 1);
		iy = (ay == 0.0) ? 0 : (oy / ay) * (height - 1);
		iz = (az == 0.0) ? 0 : (oz / az) * (depth - 1);


		VX_ASSERT(ix >= 0);
		VX_ASSERT(iy >= 0);
		VX_ASSERT(iz >= 0);

		const auto ix = (ax == 0.0) ? 0 : (ox / ax) * (width - 1);
		iy = (ay == 0.0) ? 0 : (oy / ay) * (height - 1);
		iz = (az == 0.0) ? 0 : (oz / az) * (depth - 1);


		VX_ASSERT(ix >= 0);
		VX_ASSERT(iy >= 0);
		VX_ASSERT(iz >= 0);

		VX_ASSERT(ix + iy * width + iz * (width * height) < width * height * depth);

		color = vx__rgbaf32_to_abgr8888(rgba);
		index = ix + iy * width + iz * (width * height);

		if (data[index] != 0) {
			data[index] = vx__mix(color, data[index]);
		}
		else {
			data[index] = color;
		}
	}
	*/

	//VX_FREE(aabb);
	VX_FREE(meshaabb);

}

/* from https://github.com/sylefeb/VoxSurf/blob/master/main.cpp
// --------------------------------------------------------------

// This version is more robust by using all three direction
// and voting among them to decide what is filled or not
void fillInsideVoting(Array3D<uchar>& _voxs)
{
  // along x
  ForIndex(k, _voxs.zsize()) {
	ForIndex(j, _voxs.ysize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.xsize()) {
		if (_voxs.at(i, j, k) & ALONG_X) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(i, j, k) |= INSIDE_X;
		}
	  }
	}
  }
  // along y
  ForIndex(k, _voxs.zsize()) {
	ForIndex(j, _voxs.xsize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.ysize()) {
		if (_voxs.at(j, i, k) & ALONG_Y) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(j, i, k) |= INSIDE_Y;
		}
	  }
	}
  }
  // along z
  ForIndex(k, _voxs.ysize()) {
	ForIndex(j, _voxs.xsize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.zsize()) {
		if (_voxs.at(j, k, i) & ALONG_Z) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(j, k, i) |= INSIDE_Z;
		}
	  }
	}
  }
  // voting
  ForArray3D(_voxs, i, j, k) {
	uchar v = _voxs.at(i, j, k);
	int votes =
	  (  (v & INSIDE_X) ? 1 : 0)
	  + ((v & INSIDE_Y) ? 1 : 0)
	  + ((v & INSIDE_Z) ? 1 : 0);
	// clean
	_voxs.at(i, j, k) &= ~(INSIDE_X | INSIDE_Y | INSIDE_Z);
	if (votes > 1) {
	  // tag as inside
	  _voxs.at(i, j, k) |= INSIDE;
	}
  }
}

// --------------------------------------------------------------

void fillInside(Array3D<uchar>& _voxs)
{
  ForIndex(k, _voxs.zsize()) {
	ForIndex(j, _voxs.ysize()) {
	  bool inside = false;
	  ForIndex(i, _voxs.xsize()) {
		if (_voxs.at(i, j, k) & ALONG_X) {
		  inside = !inside;
		}
		if (inside) {
		  _voxs.at(i, j, k) |= INSIDE;
		}
	  }
	}
  }
}*/