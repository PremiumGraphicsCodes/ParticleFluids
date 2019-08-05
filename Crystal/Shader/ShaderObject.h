#ifndef __CRYSTAL_SHADER_SHADER_OBJECT_H__
#define __CRYSTAL_SHADER_SHADER_OBJECT_H__


#include <vector>
#include <map>
#include <string>

#include "../Math/Vector3d.h"
#include "ShaderUniform.h"
#include "ShaderAttribute.h"
#include "GL/glew.h"

#include "ShaderUnit.h"

#include "../Graphics/Buffer1d.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

namespace Crystal {
	namespace Shader {

class ShaderObject
{
public:
	ShaderObject(void);

	ShaderObject(const std::string& vFile, const std::string& fFile);

	~ShaderObject(void);

	void clear();

	bool link(const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader);

	bool link(const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader, const ShaderUnit& geometryShader);

	bool build(const std::string& vSource, const std::string& fSource);

	bool build(const std::string& vSource, const std::string& gSource, const std::string& fSource);

	bool buildFromFile(const std::string& vFile, const std::string& fFile);

	bool buildFromFile(const std::string& vFile, const std::string& gFile, const std::string& fFile);

	void findUniformLocation(const std::string& str);

	void findAttribLocation(const std::string& str);

	std::vector<IShaderUniform*> getActiveUniforms();

	std::vector<IShaderAttribute*> getActiveAttributes();

	std::string getLog() const { return log; }

	unsigned int getId() const { return id; }

	unsigned int getUniformLocation(const std::string& str);

	unsigned int getAttribLocation(const std::string& str);

	void bind() {
		glUseProgram(getId());
	}

	void unbind()
	{
		glUseProgram(0);
	}

	void enable(GLenum e) {
		glEnable(e);
	}

	void disable(GLenum e) {
		glDisable(e);
	}

	void sendUniform(const std::string& name, Math::Matrix4df matrix);

	void sendVertexAttribute1df(const std::string& name, const std::vector<float>& data);

	void sendVertexAttribute3df(const std::string& name, const std::vector<float>& data);

	void sendVertexAttribute4df(const std::string& name, const std::vector<float>& data);

	void enableVertexAttribute(const std::string& name);

	void disableVertexAttribute(const std::string& name);

	void enableDepthTest();

	void disableDepthTest();

	void enablePointSprite();

	void disablePointSprite();

	void drawPoints(const int count);

	void bindOutput(const std::string& name);

public:
	unsigned int id;
private:
	std::string log;
	std::map< std::string, unsigned int > uniformMap;
	std::map< std::string, unsigned int > attribMap;


};


	}
}

#endif