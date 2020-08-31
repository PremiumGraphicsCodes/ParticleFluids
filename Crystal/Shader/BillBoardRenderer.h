#pragma once

#include "ShaderObject.h"
#include "../Math/Box2d.h"
#include <memory>

namespace Crystal {
	namespace Shader {
		class ITextureObject;
		class GLObjectFactory;

class BillBoard
{
public:
	BillBoard(Math::Box2d area, ITextureObject* texture) :
		area(area),
		texture(texture)
	{}

private:
	Math::Box2d area;
	ITextureObject* texture;
};

class BillBoardRenderer
{
public:
	bool build(GLObjectFactory& factory);

	void render(const ITextureObject& texture);

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	std::unique_ptr<ShaderObject> shader;
};

	}
}