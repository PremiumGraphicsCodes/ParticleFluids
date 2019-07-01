#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Model {

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	~MaterialScene() {};

	Graphics::Material getMaterial(const std::string& name) { return materialMap[name]; }

	void addMaterial(const std::string& name, Graphics::Material mat) { materialMap[name] = mat; }

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	bool isNull() const { return materialMap.empty(); }

	SceneType getType() const override { return SceneType::MaterialObject; }

	void onClear() override
	{
		materialMap.clear();
	}


private:
	std::map<std::string, Graphics::Material> materialMap;
};

	}
}