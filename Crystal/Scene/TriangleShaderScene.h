#include "ShaderScene.h"
#include "../Graphics/LineBuffer.h"

namespace Crystal {
	namespace Scene {

class TriangleShaderScene : public ShaderScene
{
public:
	TriangleShaderScene(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const Graphics::LineBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Graphics::LineBuffer buffer;
};

	}
}