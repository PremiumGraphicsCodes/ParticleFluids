#pragma once

#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "../Scene/LightObjectRepository.h"
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

	void add(const Model::LightObjectRepository& lights);

	void add(const Model::MaterialObjectRepository& materials);

	Graphics::LightBuffer getLightBuffer() const { return lightBuffer; }

	Graphics::MaterialBuffer getMaterialBuffer() const { return materialBuffer; }

private:
	Graphics::LightBuffer lightBuffer;
	Graphics::MaterialBuffer materialBuffer;
};

	}
}