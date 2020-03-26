#include "LineShader.h"

#include "../Shader/VertexBufferObject.h"

namespace Crystal {
	namespace Scene {

class TriangleShader
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

		void release();

		void send(const LineBuffer& buffer);
	};

	TriangleShader();

	bool build();

	void setBuffer(const GLBuffer& glBuffer) { this->glBuffer = glBuffer; }

	void render(const Graphics::Camera& camera);

private:
	std::string getBuildInVertexShaderSource() const;

	std::string getBuiltInFragmentShaderSource() const;

	GLBuffer glBuffer;
	Shader::ShaderObject shader;
};

	}
}