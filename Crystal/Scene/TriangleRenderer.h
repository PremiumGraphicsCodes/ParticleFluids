#include "IRenderer.h"
#include "LineRenderer.h"

namespace Crystal {
	namespace Scene {

class TriangleRenderer : public IRenderer
{
public:
	TriangleRenderer(const int id, const std::string& name);

	void render(const Graphics::ICamera& camera) override;

	void setBuffer(const LineBuffer& buffer) { this->buffer = buffer; }

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	LineBuffer buffer;
};

	}
}