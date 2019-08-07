#pragma once

#include "ShaderScene.h"

#include "../Shape/PolygonMesh.h"
#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"

namespace Crystal {
	namespace Scene {

class SmoothTriangleBuffer
{
public:
	SmoothTriangleBuffer() {}

	SmoothTriangleBuffer(const Shape::PolygonMesh& mesh) {
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

	Graphics::Buffer3d<float> getPositions() const { return positions; }

	Graphics::Buffer3d<float> getNormals() const { return normals; }

	Graphics::Buffer2d<float> getTexCoords() const { return texCoords; }

	Graphics::Buffer1d<unsigned int> getIndices() const { return indices; }

	Graphics::Buffer1d<int> getMaterialIndices() const { return materialIndices; }

	int getLightIndex() const { return 0; }

private:
	Graphics::Buffer3d<float> positions;
	Graphics::Buffer3d<float> normals;
	Graphics::Buffer2d<float> texCoords;
	Graphics::Buffer1d<int> materialIndices;
	Graphics::Buffer1d<unsigned int> indices;
};


class SmoothShaderScene : public ShaderScene
{
public:
	SmoothShaderScene(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const SmoothTriangleBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	SmoothTriangleBuffer buffer;
};

	}
}