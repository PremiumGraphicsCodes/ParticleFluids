#include "TriangleMeshBuilder.h"

#include "../Math/Quad3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

namespace {
	constexpr auto tolerance = 1.0e-12;
}

TriangleMeshBuilder::TriangleMeshBuilder()
{
}

void TriangleMeshBuilder::add(const Triangle3d& triangle)
{
	faces.push_back(TriangleFace(triangle));
}

void TriangleMeshBuilder::add(const Quad3d& quad)
{
	const auto p0 = quad.getPosition(0.0, 0.0);
	const auto p1 = quad.getPosition(1.0, 0.0);
	const auto p2 = quad.getPosition(0.0, 1.0);
	const auto p3 = quad.getPosition(1.0, 1.0);

	const Triangle3d t1(p0, p1, p2);
	const TriangleFace f1(t1);

	const Triangle3d t2(p3, p2, p1);
	const TriangleFace f2(t2);

	faces.push_back(f1);
	faces.push_back(f2);
}

void TriangleMeshBuilder::add(const Box3dd& box)
{
	auto p0 = box.getPosition(0, 0, 0);
	auto p1 = box.getPosition(1, 0, 0);
	auto p2 = box.getPosition(1, 1, 0);
	auto p3 = box.getPosition(0, 1, 0);

	auto p4 = box.getPosition(0, 0, 1);
	auto p5 = box.getPosition(1, 0, 1);
	auto p6 = box.getPosition(1, 1, 1);
	auto p7 = box.getPosition(0, 1, 1);

	faces.push_back(TriangleFace(Triangle3d(p0, p1, p2))); // front
	faces.push_back(TriangleFace(Triangle3d(p3, p2, p1)));
	faces.push_back(TriangleFace(Triangle3d(p4, p5, p6)));
	faces.push_back(TriangleFace(Triangle3d(p7, p4, p5)));
}

std::unique_ptr<TriangleMesh> TriangleMeshBuilder::build()
{
	auto mesh = std::make_unique<TriangleMesh>();
	for (const auto& f : faces) {
		mesh->addFace(f);
	}
	return std::move(mesh);
}

void TriangleMeshBuilder::add(const ISurface3dd& surface, const int unum, const int vnum)
{
	const auto du = 1.0 / static_cast<double>(unum);
	const auto dv = 1.0 / static_cast<double>(vnum);

	std::vector<std::vector<Vector3dd>> positions;

	for (auto u = 0.0; u < 1.0 + tolerance; u += du) {
		std::vector<Vector3dd> ps;

		for (auto v = 0.0; v < 1.0 + tolerance; v += du) {
			ps.push_back(surface.getPosition(u, v));
		}
		positions.push_back(ps);
	}

	for (int i = 0; i < unum; ++i) {
		for (int j = 0; j < vnum; ++j) {
			const Triangle3d t1(positions[i][j], positions[i+1][j], positions[i][j+1]);
			faces.push_back(TriangleFace(t1));
			const Triangle3d t2(positions[i+1][j+1], positions[i][j+1], positions[i+1][j]);
			faces.push_back(TriangleFace(t2));
		}
	}
}
