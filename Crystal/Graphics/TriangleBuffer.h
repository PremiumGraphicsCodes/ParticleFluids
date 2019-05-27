#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__

#include "Buffer1d.h"
#include "Buffer2d.h"
#include "Buffer3d.h"
#include "Buffer4d.h"
#include "Material.h"
#include "../Shape/PolygonMesh.h"

namespace Crystal {
	namespace Graphics {

class TriangleBufferBlock
{
public:
	TriangleBufferBlock(const std::vector<unsigned int>& indices, const Material& material) :
		indices(indices),
		material(material)
	{}

	std::vector<unsigned int> getIndices() const { return indices; }

	Material getMaterial() const { return material; }

private:
	std::vector<unsigned int> indices;
	Material material;
};


class TriangleBuffer
{
public:
	TriangleBuffer() {}

	void add(const Shape::PolygonMesh& polygon, const Material& mat) {
		const auto& vertices = polygon.getVertices();
		for (auto v : vertices) {
			positions.add(v->getPosition());
			normals.add(v->getNormal());
			if (v->getAttr().texCoord != nullptr) {
				texCoords.add(v->getTexCoord());
			}
			else {
				texCoords.add(Math::Vector2dd(0,0));
			}
		}
		const auto& faces = polygon.getFaces();
		std::vector<unsigned int> indices;
		for (auto f : faces) {
			indices.push_back(f->getV1()->getAttr().id);
			indices.push_back(f->getV2()->getAttr().id);
			indices.push_back(f->getV3()->getAttr().id);
		}
		TriangleBufferBlock block(indices, mat);
		blocks.push_back(block);
	}

	Buffer3d<float> getPositions() const { return positions; }

	Buffer3d<float> getNormals() const { return normals; }

	Buffer2d<float> getTexCoords() const { return texCoords; }

	std::vector<TriangleBufferBlock> getBlocks() const { return blocks; }

private:
	Buffer3d<float> positions;
	Buffer3d<float> normals;
	Buffer2d<float> texCoords;
	std::vector<TriangleBufferBlock> blocks;
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