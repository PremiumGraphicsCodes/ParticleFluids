#pragma once

#include "../Graphics/LightBuffer.h"
#include "../Graphics/MaterialBuffer.h"
#include "LightObjectRepository.h"
#include "ObjectRepository.h"
#include "MaterialObjectRepository.h"

namespace Crystal {
	namespace UI {
		class AppearanceObjectRepository;

class AppearanceViewModel
{
public:

	void add(AppearanceObjectRepository& appearances);

	void add(const LightObjectRepository& lights);

	void add(const MaterialObjectRepository& materials);

	Graphics::LightBuffer getLightBuffer() const { return lightBuffer; }

	Graphics::MaterialBuffer getMaterialBuffer() const { return materialBuffer; }

private:
	Graphics::LightBuffer lightBuffer;
	Graphics::MaterialBuffer materialBuffer;
};

	}
}