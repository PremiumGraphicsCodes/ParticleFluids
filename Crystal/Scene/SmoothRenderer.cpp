#include "SmoothRenderer.h"

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

void SmoothTriangleBuffer::addVertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord, const int materialId)
{
	positions.add(position);
	normals.add(normal);
	texCoords.add(texCoord);
	materialIds.add(materialId);
}

void SmoothRenderer::GLBuffer::build()
{
	position.build();
	normal.build();
	texCoord.build();
	materialId.build();
}

void SmoothRenderer::GLBuffer::release()
{
	position.release();
	normal.release();
	texCoord.release();
	materialId.release();
}

void SmoothRenderer::GLBuffer::send(const SmoothTriangleBuffer& buffer)
{
	position.send(buffer.getPositions().get());
	normal.send(buffer.getNormals().get());
	texCoord.send(buffer.getTexCoords().get());
	materialId.send(buffer.getMaterialIds().get());

	count = buffer.getPositions().get().size() / 3;
	matrix = buffer.getMatrix();
}

SmoothRenderer::SmoothRenderer()
{
}

bool SmoothRenderer::build(GLObjectFactory& factory)
{
	lightRenderer.build(this);
	materialRenderer.build(this);
	textureRenderer.build(this);

	setVertexShaderSource(getBuildInVertexShaderSource());
	setFragmentShaderSource(getBuiltInFragmentShaderSource());

	addUniform(::projectionMatrixLabel);
	addUniform(::modelviewMatrixLabel);
	addUniform(::eyePositionLabel);
	//shader.findUniformLocation("texture1");

	addAttribute(::positionLabel);
	addAttribute(::normalLabel);
	addAttribute(::materialIdLabel);
	addAttribute(::texCoordLabel);

	return build_(factory);
}

void SmoothRenderer::send(const GLBuffer& glBuffer, const Camera& camera)
{
	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix() * matrix;
	const auto& eyePos = camera.getEye();

	auto shader = getShader();

	shader->bind();

	shader->sendUniform(::projectionMatrixLabel, projectionMatrix);
	shader->sendUniform(::modelviewMatrixLabel, modelviewMatrix);
	shader->sendUniform(::eyePositionLabel, eyePos);

	shader->sendVertexAttribute3df(::positionLabel, glBuffer.position);
	shader->sendVertexAttribute3df(::normalLabel, glBuffer.normal);
	shader->sendVertexAttribute2df(::texCoordLabel, glBuffer.texCoord);
	shader->sendVertexAttribute1di(::materialIdLabel, glBuffer.materialId);

	shader->unbind();

	this->matrix = glBuffer.matrix;
	this->count = glBuffer.count;
}

void SmoothRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();


	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);
	shader->enableVertexAttribute(::texCoordLabel);
	shader->enableVertexAttribute(::materialIdLabel);


	/*
	for (const auto& t : textures) {
		t.bind();
	}
	*/

	shader->drawTriangles(count);

	/*
	for (const auto& t : textures) {
		t.unbind();
	}
	*/

	//textures[0].unbind();

	shader->disableVertexAttribute(::materialIdLabel);
	shader->disableVertexAttribute(::texCoordLabel);
	shader->disableVertexAttribute(::normalLabel);
	shader->disableVertexAttribute(::positionLabel);

	assert(GL_NO_ERROR == glGetError());

	shader->disableDepthTest();
	shader->unbind();
}

std::string SmoothRenderer::getBuildInVertexShaderSource() const
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

std::string SmoothRenderer::getBuiltInFragmentShaderSource() const
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
		<< lightRenderer.getBuiltInFragmentShaderSource()
		<< materialRenderer.getBuiltInFragmentShaderSource()
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