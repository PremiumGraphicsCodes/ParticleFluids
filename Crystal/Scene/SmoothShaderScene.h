#include "ShaderScene.h"
#include "../Graphics/TriangleBuffer.h"

namespace Crystal {
	namespace Scene {

class SmoothShaderScene : public ShaderScene
{
public:
	SmoothShaderScene(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const Graphics::TriangleBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	Graphics::TriangleBuffer buffer;
};

	}
}