#pragma once

#include "IRenderer.h"

namespace Crystal {
	namespace Scene {

class MaterialRenderer
{
public:
	bool build(IRenderer* parent);

	std::string getBuiltInFragmentShaderSource() const;
};

	}
}
