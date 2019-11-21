#pragma once

#include "IShapeScene.h"
#include "WireFrameAttribute.h"

#include "../Math/Line3d.h"

namespace Crystal {
	namespace Scene {

class WireFrameEdge
{
public:
	WireFrameEdge() {}

	WireFrameEdge(const int originId, const int destId) :
		originId(originId),
		destId(destId)
	{}

	int originId;
	int destId;
};

class WireFrameScene : public IShapeScene
{
public:
	WireFrameScene() :
		IShapeScene(-1)
	{}

	WireFrameScene(const int id, const std::string& name, const std::vector<Math::Vector3dd>& positions, const std::vector<WireFrameEdge>& edges, const WireFrameAttribute& attribute) :
		IShapeScene(id, name),
		positions(positions),
		edges(edges),
		attribute(attribute)
	{}

	~WireFrameScene() {};

	WireFrameAttribute getAttribute() const { return attribute; }

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	SceneType getType() const override { return SceneType::WireFrameScene; }

	void onClear() override {
		positions.clear();
		edges.clear();
	}

	Math::Box3d getBoundingBox() const;

	std::vector<Math::Vector3dd> getAllVertices() const;

	void toViewModel(SceneViewModel& viewModel) const override;

	void toIdViewModel(SceneIdViewModel& viewModel) const override;

	void getBoundingBox(Math::Box3d& box) const;

	Math::Vector3dd getPosition(const int index) const override;

	IShapeScene* clone() const override;

private:
	std::vector<Math::Vector3dd> positions;
	std::vector<WireFrameEdge> edges;
	WireFrameAttribute attribute;
};

	}
}