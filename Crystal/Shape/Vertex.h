#ifndef __CRYSTAL_SHAPE_VERTEX_H__
#define __CRYSTAL_SHAPE_VERTEX_H__

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"
#include "../Math/Box3d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Shape {

struct VertexAttr
{
	int id;
	Math::Vector3dd* normal;
	Math::Vector2dd* texCoord;

	VertexAttr() :
		id(-1),
		normal(nullptr),
		texCoord(nullptr)
	{
	}
};

class Vertex
{
public:
	Vertex(Math::Vector3dd* position, const VertexAttr& attr);

	VertexAttr getAttr() const { return attr; }

	int getId() const { return attr.id; }

	Math::Vector3dd getPosition() const { return *position; }

	Math::Vector3dd getNormal() const { return *attr.normal; }

	Math::Vector2dd getTexCoord() const { return *attr.texCoord; }

	void move(const Math::Vector3df& v) { *this->position += v;}

	void setNormal(const Math::Vector3df& n) { *this->attr.normal = n; }

	void transform(const Math::Matrix3dd& m) { *position = m * *position; }

	void transform(const Math::Matrix4dd& m) { *position = m * glm::vec4( *position, 1.0 ); }

	//void scale(const Vector3df& s) { this->position.scale(s); }

private:
	Math::Vector3dd* position;
	VertexAttr attr;
};


class Util {
public:
	static Math::Box3d getBoundingBox(const std::list<Vertex*>& vertices);
};

	}
}
#endif