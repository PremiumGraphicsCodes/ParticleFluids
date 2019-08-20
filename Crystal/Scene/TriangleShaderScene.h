#include "IRenderer.h"
#include "LineShaderScene.h"

namespace Crystal {
	namespace Scene {

class TriangleShaderScene : public IRenderer
{
public:
	TriangleShaderScene(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const LineBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	LineBuffer buffer;
};

	}
}