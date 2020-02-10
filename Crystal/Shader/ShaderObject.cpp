#include "ShaderObject.h"
//#include "TextureObject.h"

#include <cassert>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glew.h"

#include "VertexBufferObject.h"
#include "TextureObject.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string getShaderString() {
		const GLubyte* str = glGetString(GL_RENDERER);
		const GLubyte* vendor = glGetString(GL_VENDOR);
		const GLubyte* glVersion = glGetString(GL_VERSION);
		const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::stringstream stream;
		stream << str;
		stream << vendor;
		stream << glVersion;
		stream << glslVersion;
		return stream.str();
	}

	namespace {
		std::string getStrFromFile(const std::string& file)
		{
			std::ifstream stream(file);
			if (stream.fail()) {
				assert(false);
				return "";
			}
			std::istreambuf_iterator<char> it(stream);
			std::istreambuf_iterator<char> last;
			return std::string(it, last);
		}
	}

}

/*
bool ShaderUnit::dump(const std::string& filename)
{
std::ofstream stream(filename);
stream <<
}
*/


ShaderObject::ShaderObject(void) :
	handle(-1),
	isBuildOk(false)
{
}

ShaderObject::~ShaderObject(void)
{
	clear();
}

void ShaderObject::clear()
{
	glUseProgram(0);
	if (handle != -1) {
		glDeleteProgram(handle);
	}
}

bool ShaderObject::link(const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader)
{
	clear();

	assert(glGetError() == GL_NO_ERROR);

	handle = glCreateProgram();
	glAttachShader(handle, vertexShader.getID());
	glAttachShader(handle, fragmentShader.getID());

	GLint success;
	glLinkProgram(handle);
	glGetProgramiv(handle, GL_LINK_STATUS, &success);

	GLchar infoLog[2048];
	glGetProgramInfoLog(handle, 2048, NULL, infoLog);
	log += infoLog;

	if (success == 0) {
		return false;
	}

	assert(glGetError() == GL_NO_ERROR);

	return true;
}

bool ShaderObject::link(const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader, const ShaderUnit& geometryShader)
{
	clear();

	assert(glGetError() == GL_NO_ERROR);

	handle = glCreateProgram();
	glAttachShader(handle, vertexShader.getID());
	glAttachShader(handle, fragmentShader.getID());
	glAttachShader(handle, geometryShader.getID());

	GLint success;
	glLinkProgram(handle);
	glGetProgramiv(handle, GL_LINK_STATUS, &success);

	GLchar infoLog[2048];
	glGetProgramInfoLog(handle, 2048, NULL, infoLog);
	log += infoLog;

	if (success == 0) {
		return false;
	}

	assert(glGetError() == GL_NO_ERROR);

	return true;
}

bool ShaderObject::build(const std::string& vSource, const std::string& fSource)
{
	ShaderUnit vShader;
	ShaderUnit fShader;

	assert(glGetError() == GL_NO_ERROR);

	if (!vShader.compile(vSource, ShaderUnit::Stage::VERTEX)) {
		log += vShader.getLog();
		return false;
	}
	assert(glGetError() == GL_NO_ERROR);

	if (!fShader.compile(fSource, ShaderUnit::Stage::FRAGMENT)) {
		log += fShader.getLog();
		return false;
	}
	assert(glGetError() == GL_NO_ERROR);

	if (!link(vShader, fShader)) {
		return false;
	}

	isBuildOk = true;
	return true;
	//positionLocation = glGetUniformLocation( shader.getId(), "position" );
}


bool ShaderObject::build(const std::string& vSource, const std::string& gSource, const std::string& fSource)
{
	ShaderUnit vShader;
	ShaderUnit gShader;
	ShaderUnit fShader;
	if (!vShader.compile(vSource, ShaderUnit::Stage::VERTEX)) {
		log += vShader.getLog();
		return false;
	}
	if (!gShader.compile(gSource, ShaderUnit::Stage::GEOMETRY)) {
		log += gShader.getLog();
		return false;
	}
	if (!fShader.compile(fSource, ShaderUnit::Stage::FRAGMENT)) {
		log += fShader.getLog();
		return false;
	}
	if (!link(vShader, fShader, gShader)) {
		return false;
	}

	return true;
	//positionLocation = glGetUniformLocation( shader.getId(), "position" );
}

bool ShaderObject::buildFromFile(const std::string& vFile, const std::string& fFile)
{
	return build(::getStrFromFile(vFile), ::getStrFromFile(fFile));
}

bool ShaderObject::buildFromFile(const std::string& vFile, const std::string& gFile, const std::string& fFile)
{
	return build(::getStrFromFile(vFile), ::getStrFromFile(gFile), ::getStrFromFile(fFile));
}


void ShaderObject::findUniformLocation(const std::string& str)
{
	const auto location = glGetUniformLocation(handle, str.c_str());
	assert(location != -1);
	uniformMap[str] = location;
}

void ShaderObject::findAttribLocation(const std::string& str)
{
	const auto location = glGetAttribLocation(handle, str.c_str());
	assert(location != -1);
	attribMap[str] = location;
}

std::vector<IShaderUniform*> ShaderObject::getActiveUniforms()
{
	GLsizei maxLength = 0;
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
	int count = 0;
	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &count);
	GLchar* name = (GLchar*)malloc(maxLength);
	std::vector<IShaderUniform*> uniforms;
	for (auto i = 0; i < count; ++i) {
		GLsizei written;
		GLint size;
		GLenum type;
		glGetActiveUniform(handle, i, maxLength, &written, &size, &type, name);
		switch (type) {
		case GL_FLOAT:
			uniforms.push_back(new ShaderUniform1f(name));
			break;
		case GL_FLOAT_VEC2:
			uniforms.push_back(new ShaderUniform2f(name));
			break;
		case GL_FLOAT_VEC3:
			uniforms.push_back(new ShaderUniform3f(name));
			break;
		case GL_FLOAT_VEC4:
			uniforms.push_back(new ShaderUniform4f(name));
			break;
		case GL_INT:
			uniforms.push_back(new ShaderUniform1i(name));
			break;
		case GL_INT_VEC2:
			uniforms.push_back(new ShaderUniform2i(name));
			break;
		case GL_INT_VEC3:
			uniforms.push_back(new ShaderUniform3i(name));
			break;
		case GL_INT_VEC4:
			uniforms.push_back(new ShaderUniform4i(name));
			break;
		case GL_BOOL:
			uniforms.push_back(new ShaderUniform1b(name));
			break;
		case GL_BOOL_VEC2:
			uniforms.push_back(new ShaderUniform2b(name));
			break;
		case GL_BOOL_VEC3:
			uniforms.push_back(new ShaderUniform3b(name));
			break;
		case GL_BOOL_VEC4:
			uniforms.push_back(new ShaderUniform4b(name));
			break;
		case GL_FLOAT_MAT2:
			uniforms.push_back(new ShaderUniformMatrix2d(name));
			break;
		case GL_FLOAT_MAT3:
			uniforms.push_back(new ShaderUniformMatrix3d(name));
			break;
		case GL_FLOAT_MAT4:
			uniforms.push_back(new ShaderUniformMatrix4d(name));
			break;
		case GL_SAMPLER_2D:
			uniforms.push_back(new ShaderUniformSampler2d(name));
			break;
		case GL_SAMPLER_CUBE:
			uniforms.push_back(new ShaderUniformCubeSampler(name));
			break;
		default:
			assert(false);
		}
	}
	free(name);
	return uniforms;
}

std::vector<IShaderAttribute*> ShaderObject::getActiveAttributes()
{
	GLsizei maxLength = 0;
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
	int count = 0;
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &count);
	GLchar* name = (GLchar*)malloc(maxLength);
	std::vector<IShaderAttribute*> attributes;
	for (auto i = 0; i < count; ++i) {
		GLsizei written;
		GLint size;
		GLenum type;
		glGetActiveAttrib(handle, i, maxLength, &written, &size, &type, name);
		switch (type) {
		case GL_FLOAT:
			attributes.push_back(new ShaderAttribute1f(name));
			break;
		case GL_FLOAT_VEC2:
			attributes.push_back(new ShaderAttribute2f(name));
			break;
		case GL_FLOAT_VEC3:
			attributes.push_back(new ShaderAttribute3f(name));
			break;
		case GL_FLOAT_VEC4:
			attributes.push_back(new ShaderAttribute4f(name));
			break;
		case GL_FLOAT_MAT2:
			attributes.push_back(new ShaderAttributeMatrix2d(name));
			break;
		case GL_FLOAT_MAT3:
			attributes.push_back(new ShaderAttributeMatrix3d(name));
			break;
		case GL_FLOAT_MAT4:
			attributes.push_back(new ShaderAttributeMatrix4d(name));
			break;
		default:
			assert(false);
		}
	}
	free(name);
	return attributes;
}

unsigned int ShaderObject::getUniformLocation(const std::string& str)
{
	assert(uniformMap.find(str) != uniformMap.end());
	return uniformMap[str];
}

unsigned int ShaderObject::getAttribLocation(const std::string& str)
{
	assert(attribMap.find(str) != attribMap.end());
	return attribMap[str];
}

void ShaderObject::sendUniform(const std::string& name, const Matrix4df& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void ShaderObject::sendUniform(const std::string& name, const Vector3df& v)
{
	glUniform3fv(getUniformLocation(name), 1, &v[0]);
}

void ShaderObject::sendUniform(const std::string& name, const int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void ShaderObject::sendUniform(const std::string& name, const float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void ShaderObject::sendUniform(const std::string& name, const TextureObject& texture)
{
	texture.bind();
	const auto location = getUniformLocation(name);
	glUniform1i(location, texture.getId());
	texture.unbind();
}

void ShaderObject::sendVertexAttribute1df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 0, data.data());
	//glEnableVertexAttribArray(location);
}

void ShaderObject::sendVertexAttribute2df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(getAttribLocation(name), 2, GL_FLOAT, GL_FALSE, 0, data.data());
}

void ShaderObject::sendVertexAttribute3df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(getAttribLocation(name), 3, GL_FLOAT, GL_FALSE, 0, data.data());
	//	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
}

void ShaderObject::sendVertexAttribute4df(const std::string& name, const std::vector<float>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, data.data());
	//glEnableVertexAttribArray(location);
}

void ShaderObject::sendVertexAttribute1di(const std::string& name, const std::vector<int>& data)
{
	const auto location = getAttribLocation(name);
	glVertexAttribIPointer(getAttribLocation(name), 1, GL_INT, 0, data.data());
	//	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
}

void ShaderObject::sendVertexAttribute1di(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribIPointer(location, 1, GL_INT, 0, (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute1df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute2df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute3df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::sendVertexAttribute4df(const std::string& name, const VertexBufferObject& vbo)
{
	vbo.bind();
	auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	vbo.unbind();
}

void ShaderObject::enableVertexAttribute(const std::string& name)
{
	const auto location = getAttribLocation(name);
	glEnableVertexAttribArray(location);
}

void ShaderObject::disableVertexAttribute(const std::string& name)
{
	const auto location = getAttribLocation(name);
	glDisableVertexAttribArray(2);
}

void ShaderObject::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void ShaderObject::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void ShaderObject::enablePointSprite()
{
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void ShaderObject::disablePointSprite()
{
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}

void ShaderObject::drawPoints(const int count)
{
	glDrawArrays(GL_POINTS, 0, count);
}

void ShaderObject::drawLines(const std::vector<unsigned int>& indices)
{
	glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
}

void ShaderObject::drawLines(const int count)
{
	glDrawArrays(GL_LINES, 0, count);
}

void ShaderObject::drawTriangles(const int count)
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}

void ShaderObject::drawTriangles(const std::vector<unsigned int>& indices)
{
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
}

void ShaderObject::bindOutput(const std::string& name)
{
	auto str = name.c_str();
	glBindFragDataLocation(getHandle(), 0, str);
}

void ShaderObject::setLineWidth(const float width)
{
	glLineWidth(width);
}