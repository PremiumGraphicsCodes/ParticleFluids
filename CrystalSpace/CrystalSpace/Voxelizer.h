#pragma once

namespace Crystal {
	namespace Shape {
		class PolygonMesh;
	}
	namespace Space {

class Voxelizer
{
public:
	void voxelize(Shape::PolygonMesh* polygon);
};
	}
}