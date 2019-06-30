#pragma once

#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "../Scene/SceneFactory.h"
#include "../Scene/Scene.h"
#include "../Scene/MaterialObjectRepository.h"

namespace Crystal {
	namespace Model {
		class AppearanceObjectRepository;
	}
	namespace UI {

class AppearanceViewModel
{
public:

	void add(Model::AppearanceObjectRepository& appearances);

	void add(const Model::MaterialObjectRepository& materials);

	Graphics::MaterialBuffer getMaterialBuffer() const { return materialBuffer; }

private:
	Graphics::MaterialBuffer materialBuffer;
};

	}
}