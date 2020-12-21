#include "IShaderScene.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Shader {
		class SmoothRenderer;
	}
	namespace Scene {

class MaterialShaderScene : public IShaderScene
{
public:
	explicit MaterialShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void send(const Graphics::Material& buffer);

	void release(Shader::GLObjectFactory& glFactory) override;

	void render(const Graphics::Camera& camera) override;

	void setShader(Shader::SmoothRenderer* shader) { this->shader = shader; }

private:
	Shader::SmoothRenderer* shader;
	//Shader::SmoothRenderer::Buffer rBuffer;
};

	}
}