#include "IRenderer.h"
#include "LineRenderer.h"

namespace Crystal {
	namespace Scene {

class TriangleRenderer : public IRenderer
{
public:
	TriangleRenderer();

	void render(const Graphics::Camera& camera) override;

	void setBuffer(const LineBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	LineBuffer buffer;
};

	}
}