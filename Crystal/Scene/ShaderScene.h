#pragma once

#include "IScene.h"

#include "../Shader/ShaderObject.h"

#include <memory>

namespace Crystal {
	namespace Scene {

class IShaderScene
{
public:
	IShaderScene(const int id, const std::string& name) :
		id(id),
		name(name)
	{}

	virtual ~IShaderScene() {}

	virtual bool build() = 0;

private:
	const int id;
	std::string name;
};

class ShaderScene : public IShaderScene
{
public:
	ShaderScene(const int id, const std::string& name) :
		IShaderScene(id, name)
	{}

	virtual ~ShaderScene() {};

	bool build() override;

	void setVertexShaderSource(const std::string& vsSource) { this->vsSource = vsSource; }

	void setFragmentShaderSource(const std::string& fsSource) { this->fsSource = fsSource; }

	void addUniform(const std::string& name) { uniforms.push_back(name); }

	void addAttribute(const std::string& name) { attributes.push_back(name); }

	std::string getVertexShaderSource() const { return vsSource; }

	std::string getFragmentShaderSource() const { return fsSource; }

	Shader::ShaderObject* getShader() { return shader.get(); }

private:
	std::unique_ptr<Shader::ShaderObject> shader;
	std::string vsSource;
	std::string fsSource;
	std::vector<std::string> uniforms;
	std::vector<std::string> attributes;
};

	}
}