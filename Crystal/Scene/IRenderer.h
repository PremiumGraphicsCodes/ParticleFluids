#pragma once

#include "../Graphics/Camera.h"
#include "../Shader/ShaderObject.h"

#include <memory>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {

class IRenderer
{
public:
	IRenderer() {}

	virtual ~IRenderer() {};

	bool build(Shader::GLObjectFactory& factory);

	virtual void render(const Graphics::Camera& camera) = 0;

	void setVertexShaderSource(const std::string& vsSource) { this->vsSource = vsSource; }

	void setFragmentShaderSource(const std::string& fsSource) { this->fsSource = fsSource; }

	void addUniform(const std::string& name) { uniforms.push_back(name); }

	void addAttribute(const std::string& name) { attributes.push_back(name); }

	std::string getVertexShaderSource() const { return vsSource; }

	std::string getFragmentShaderSource() const { return fsSource; }

	Shader::ShaderObject* getShader() { return shader.get(); }

	//void render(const Graphics::Camera& camera) {};

private:
	std::unique_ptr<Shader::ShaderObject> shader;
	std::string vsSource;
	std::string fsSource;
	std::vector<std::string> uniforms;
	std::vector<std::string> attributes;
};

	}
}