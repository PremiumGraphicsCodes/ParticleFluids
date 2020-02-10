#include "IRenderer.h"
#include "LineRenderer.h"

#include "../Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Scene {

class TriangleRenderer : public IRenderer
{
public:
	struct GLBuffer
	{
		struct VBO {
			Shader::VertexBufferObject position;
			Shader::VertexBufferObject color;
		};
		VBO vbo;
		std::vector<unsigned int> indices;

		void build();

		void send(const LineBuffer& buffer);
	};

	TriangleRenderer();

	bool build(Shader::GLObjectFactory& factory) override;

	void setBuffer(const GLBuffer& glBuffer) { this->glBuffer = glBuffer; }

	void render(const Graphics::Camera& camera) override;

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	GLBuffer glBuffer;
};

	}
}