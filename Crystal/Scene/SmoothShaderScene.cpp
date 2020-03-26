#include "SmoothShaderScene.h"

#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

namespace {
	constexpr char* projectionMatrixLabel = "projectionMatrix";
	constexpr char* modelviewMatrixLabel = "modelviewMatrix";
	constexpr char* eyePositionLabel = "eyePosition";
	constexpr char* positionLabel = "position";
	constexpr char* normalLabel = "normal";
	constexpr char* materialIdLabel = "materialId";
	constexpr char* texCoordLabel = "texCoord";
}

SmoothShaderScene::SmoothShaderScene()
{
}

bool SmoothShaderScene::build()
{
	const auto& vsSource = getBuildInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	const auto isOk = shader.build(vsSource, fsSource);

	shader.findUniformLocation(::projectionMatrixLabel);
	shader.findUniformLocation(::modelviewMatrixLabel);
	shader.findUniformLocation(::eyePositionLabel);
	//shader.findUniformLocation("texture1");

	shader.findAttribLocation(::positionLabel);
	shader.findAttribLocation(::normalLabel);
	shader.findAttribLocation(::materialIdLabel);
	shader.findAttribLocation(::texCoordLabel);

	//materialShader.build(&shader);
	for (int i = 0; i < 256; ++i) {
		const auto prefix = "materials[" + std::to_string(i) + "]";
		shader.findUniformLocation(prefix + ".Ka");
		shader.findUniformLocation(prefix + ".Kd");
		shader.findUniformLocation(prefix + ".Ks");
		shader.findUniformLocation(prefix + ".shininess");
		shader.findUniformLocation(prefix + ".ambientTexId");
		shader.findUniformLocation(prefix + ".diffuseTexId");
		shader.findUniformLocation(prefix + ".specularTexId");
	}

	for (int i = 0; i < 8; ++i) {
		const auto prefix = "lights[" + std::to_string(i) + "]";
		shader.findUniformLocation(prefix + ".position");
		shader.findUniformLocation(prefix + ".La");
		shader.findUniformLocation(prefix + ".Ld");
		shader.findUniformLocation(prefix + ".Ls");
	}

	for (int i = 0; i < 8; ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		shader.findUniformLocation(prefix);
	}

	return isOk;
}

void SmoothShaderScene::release()
{
	shader.release();
}

void SmoothShaderScene::send(const SmoothShaderBuffer& glBuffer)
{
	const auto& projectionMatrix = glBuffer.camera.getProjectionMatrix();
	const auto& modelviewMatrix = glBuffer.camera.getModelViewMatrix() * matrix;
	const auto& eyePos = glBuffer.camera.getEye();

	shader.bind();

	shader.sendUniform(::projectionMatrixLabel, projectionMatrix);
	shader.sendUniform(::modelviewMatrixLabel, modelviewMatrix);
	shader.sendUniform(::eyePositionLabel, eyePos);

	shader.sendVertexAttribute3df(::positionLabel, glBuffer.position);
	shader.sendVertexAttribute3df(::normalLabel, glBuffer.normal);
	shader.sendVertexAttribute2df(::texCoordLabel, glBuffer.texCoord);
	shader.sendVertexAttribute1di(::materialIdLabel, glBuffer.materialId);


	//lightShader.send();
	shader.unbind();

	this->matrix = glBuffer.matrix;
	this->count = glBuffer.count;
}

void SmoothShaderScene::send(const std::vector<Material>& materials)
{
	shader.bind();
	for (int i = 0; i < materials.size(); ++i) {
		const auto m = materials[i];
		const auto prefix = "materials[" + std::to_string(i) + "]";
		shader.sendUniform(prefix + ".Ka", m.ambient);
		shader.sendUniform(prefix + ".Kd", m.diffuse);
		shader.sendUniform(prefix + ".Ks", m.specular);
		shader.sendUniform(prefix + ".shininess", m.shininess);
		//		shader->sendUniform(prefix + ".ambientTexId", findIndex(m.ambientTexName));
		//		shader->sendUniform(prefix + ".diffuseTexId", findIndex(m.diffuseTexName));// m.diffuseTexId);
		//		shader->sendUniform(prefix + ".specularTexId", findIndex(m.specularTexName));// m.specularTexId);
	}
	shader.unbind();
}

void SmoothShaderScene::send(const std::vector<PointLight>& lights)
{
	shader.bind();
	for (int i = 0; i < lights.size(); ++i) {
		const auto& light = lights[i];
		const auto prefix = "lights[" + std::to_string(i) + "]";

		const auto& lightPos = light.getPosition();//{ -10.0f, 10.0f, 10.0f };
		const auto& ambient = light.getAmbient();
		const auto& diffuse = light.getDiffuse();
		const auto& specular = light.getSpecular();

		shader.sendUniform(prefix + ".position", lightPos);
		shader.sendUniform(prefix + ".La", ambient);
		shader.sendUniform(prefix + ".Ld", diffuse);
		shader.sendUniform(prefix + ".Ls", specular);
	}
	shader.unbind();
}

void SmoothShaderScene::send(const std::vector<TextureObject>& textures)
{
	shader.bind();
	for (int i = 0; i < textures.size(); ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		shader.sendUniform(prefix, textures[i]);
	}
	shader.unbind();
}

void SmoothShaderScene::render()
{
	shader.bind();
	shader.bindOutput("fragColor");

	shader.enableDepthTest();


	shader.enableVertexAttribute(::positionLabel);
	shader.enableVertexAttribute(::normalLabel);
	shader.enableVertexAttribute(::texCoordLabel);
	shader.enableVertexAttribute(::materialIdLabel);


	/*
	for (const auto& t : textures) {
		t.bind();
	}
	*/

	shader.drawTriangles(count);

	/*
	for (const auto& t : textures) {
		t.unbind();
	}
	*/

	//textures[0].unbind();

	shader.disableVertexAttribute(::materialIdLabel);
	shader.disableVertexAttribute(::texCoordLabel);
	shader.disableVertexAttribute(::normalLabel);
	shader.disableVertexAttribute(::positionLabel);

	assert(GL_NO_ERROR == glGetError());

	shader.disableDepthTest();
	shader.unbind();
}

std::string SmoothShaderScene::getBuildInVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "in int materialId;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec3 vNormal;" << std::endl
		<< "out vec3 vPosition;" << std::endl
		<< "flat out int vMaterialId;" << std::endl
		<< "out vec2 vTexCoord;" << std::endl
		<< "uniform mat4 projectionMatrix;"
		<< "uniform mat4 modelviewMatrix;"
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vNormal = normalize(normal);" << std::endl
		<< "	vPosition = position;" << std::endl
		<< "	vMaterialId = materialId;" << std::endl
		<< "	vTexCoord = texCoord;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string SmoothShaderScene::getBuiltInFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 vNormal;" << std::endl
		<< "in vec3 vPosition;" << std::endl
		<< "flat in int vMaterialId;" << std::endl
		<< "in vec2 vTexCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform sampler2D textures[8];" << std::endl
		<< "struct LightInfo {" << std::endl
		<< "	vec3 position;" << std::endl
		<< "	vec3 La;" << std::endl
		<< "	vec3 Ld;" << std::endl
		<< "	vec3 Ls;" << std::endl
		<< "};"
		<< "uniform LightInfo lights[8];" << std::endl
		<< "struct MaterialInfo {" << std::endl
		<< "	vec3 Ka;" << std::endl
		<< "	vec3 Kd;" << std::endl
		<< "	vec3 Ks;" << std::endl
		<< "	float shininess;" << std::endl
		<< "	int ambientTexId;" << std::endl
		<< "	int diffuseTexId;" << std::endl
		<< "	int specularTexId;" << std::endl
		<< "};"
		<< "uniform MaterialInfo materials[256];" << std::endl
		<< "vec3 getTextureColor(int id){ " << std::endl
		<< "	if(id == -1) {" << std::endl
		<< "		return vec3(1,1,1);" << std::endl
		<< "	}" << std::endl
		<< "	return texture2D(textures[id], vTexCoord).rgb;" << std::endl
		<< "};" << std::endl
		<< "vec3 getAmbientColor(LightInfo light, MaterialInfo material){" << std::endl
		<< "	vec3 ambient = light.La * material.Ka;" << std::endl
		<< "	return ambient * getTextureColor(material.ambientTexId);" << std::endl
		<< "};" << std::endl
		<< "vec3 getS(LightInfo light){" << std::endl
		<< "	return normalize(light.position - vPosition);" << std::endl
		<< "};" << std::endl
		<< "vec3 getV() {" << std::endl
		<< "	return normalize(vPosition - eyePosition);" << std::endl
		<< "};" << std::endl
		<< "vec3 getR(LightInfo light, vec3 normal) {" << std::endl
		<< "	vec3 s = getS(light);" << std::endl
		<< "	return reflect( -s, normal );" << std::endl
		<< "};" << std::endl
		<< "vec3 getDiffuseColor(LightInfo light, MaterialInfo material, float innerProduct){" << std::endl
		<< "	vec3 diffuse = light.Ld * material.Kd * innerProduct;" << std::endl
		<< "	return diffuse * getTextureColor(material.diffuseTexId);" << std::endl
		<< "};" << std::endl
		<< "vec3 getSpecularColor(LightInfo light, MaterialInfo material, float innerProduct, vec3 normal){" << std::endl
		<< "	vec3 s = getS(light);" << std::endl
		<< "	vec3 v = getV();" << std::endl
		<< "	vec3 r = reflect( -s, normal );" << std::endl
		<< "	vec3 specular = vec3(0.0);" << std::endl
		<< "	if(innerProduct > 0.0) {" << std::endl
		<< "		specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0 ), material.shininess );" << std::endl
		<< "	}" << std::endl
		<< "	return specular * getTextureColor(material.specularTexId);" << std::endl
		<< "};" << std::endl
		<< "vec3 getPhongShadedColor( vec3 position, vec3 normal) {"
		<< "	MaterialInfo material = materials[vMaterialId];" << std::endl
		<< "	LightInfo light = lights[0];" << std::endl
		<< "	vec3 s = getS(light);" << std::endl
		<< "	vec3 r = getR(light, normal);" << std::endl
		<< "	vec3 ambient = getAmbientColor(light, material);" << std::endl
		<< "	float innerProduct = max( dot(s,normal), 0.0);" << std::endl
		<< "	vec3 diffuse = getDiffuseColor(light, material, innerProduct);" << std::endl
		<< "	vec3 specular = getSpecularColor(light, material, innerProduct, normal);" << std::endl
		<< "	return ambient + diffuse + specular;" << std::endl
		<< "}"
		<< "void main(void) {" << std::endl
		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal);" << std::endl
//		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal) * getTextureColor();" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}