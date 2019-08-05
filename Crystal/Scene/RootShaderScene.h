#pragma once

#include "IShaderScene.h"

namespace Crystal {
	namespace Scene {

class RootShaderScene : public IShaderScene
{
public:
	RootShaderScene(const int id, const std::string& name) :
		IShaderScene(id, name)
	{}

	~RootShaderScene() {}

	bool build() override { 
		const auto& children = getChildren();
		for (auto child : children) {
			if (!child->build()) {
				return false;
			}
		}
		return true;
	};

	void render(const Graphics::ICamera& camera) override {
		const auto& children = getChildren();
		for (auto child : children) {
			child->render(camera);
		}
	}

	//void addChild(IShaderScene* child) { children.push_back(child); }

private:
};

	}
}