#pragma once

#include "ShaderScene.h"

#include "../Shader/ShaderObject.h"

namespace Crystal {
	namespace Scene {

class PointShaderScene : ShaderScene
{
public:
	PointShaderScene(const int id, const std::string& name) :
		ShaderScene(id, name)
	{}

private:
};

	}
}