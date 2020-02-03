#include "IRenderer.h"
#include "LineRenderer.h"

namespace Crystal {
	namespace Scene {

class TriangleRenderer : public IRenderer
{
public:
	TriangleRenderer();

	bool build(Shader::GLObjectFactory& factory) override;

	void send(const LineBuffer& buffer);

	void render(const Graphics::Camera& camera) override;

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	LineBuffer buffer;
};

	}
}