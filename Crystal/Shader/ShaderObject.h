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