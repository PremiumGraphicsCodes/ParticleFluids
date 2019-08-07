#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__

#include "Buffer1d.h"
#include "Buffer2d.h"
#include "Buffer3d.h"
#include "Buffer4d.h"
#include "Material.h"
#include "PointLight.h"
#include "../Shape/PolygonMesh.h"

namespace Crystal {
	namespace Graphics {

class TriangleBuffer
{
public:
	TriangleBuffer() {}

	TriangleBuffer(const Shape::PolygonMesh& mesh) {
		const auto& vertices = mesh.getVertices();
		const auto& ps = mesh.getPositions();
		const auto& ns = mesh.getNormals();
		const auto& tcs = mesh.getTexCoords();
		for (auto v : vertices) {
			positions.add(ps[v.positionId]);
			normals.add(ns[v.normalId]);
			if (v.texCoordId != -1) {
				texCoords.add(tcs[v.texCoordId]);
			}
			else {
				texCoords.add(Math::Vector2dd(0, 0));
			}
		}
	}

	void add(const std::vector<Shape::Face>& faces, const int materialIndex) {
		for (auto f : faces) {
			indices.add(f.v1);
			indices.add(f.v2);
			indices.add(f.v3);
		}
		materialIndices.add(materialIndex);
	}

	Buffer3d<float> getPositions() const { return positions; }

	Buffer3d<float> getNormals() const { return normals; }

	Buffer2d<float> getTexCoords() const { return texCoords; }

	Buffer1d<unsigned int> getIndices() const { return indices; }

	Buffer1d<int> getMaterialIndices() const { return materialIndices; }

	int getLightIndex() const { return 0; }

private:
	Buffer3d<float> positions;
	Buffer3d<float> normals;
	Buffer2d<float> texCoords;
	Buffer1d<int> materialIndices;
	Buffer1d<unsigned int> indices;
};

/*
class TriangleColorBuffer
{
public:
	TriangleColorBuffer() {}

	void add(const Math::Triangle3d& triangle, const Graphics::ColorRGBAf& color) {
		const auto& vertices = polygon.getVertices();
		int id = 0;
		for (auto v : vertices) {
			positions.add(v->getPosition());
		}
		const auto& faces = polygon.getFaces();
		for (auto f : faces) {
			DrawableID did(id, f->getId());
			indices.push_back(f->getV1()->getAttr().id);
			indices.push_back(f->getV2()->getAttr().id);
			indices.push_back(f->getV3()->getAttr().id);
		}
	}

	Buffer3d<float> getPositions() const { return positions; }

	Buffer4d<float> getColors() const { return colors; }

	std::vector<unsigned int> getIndices() const { return indices; }

private:
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer4d<float> colors;
	std::vector<unsigned int> indices;
};
*/

	}
}

#endif