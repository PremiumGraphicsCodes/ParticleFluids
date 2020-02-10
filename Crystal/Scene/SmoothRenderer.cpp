#include "SmoothRenderer.h"

#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

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
	setVertexShaderSource(getBuildInVertexShaderSource());
	setFragmentShaderSource(getBuiltInFragmentShaderSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");
	addUniform("eyePosition");
	for (int i = 0; i < 8; ++i) {
		const auto prefix = "lights[" + std::to_string(i) + "]";
		addUniform(prefix + ".position");
		addUniform(prefix + ".La");
		addUniform(prefix + ".Ld");
		addUniform(prefix + ".Ls");
	}
	for (int i = 0; i < 256; ++i) {
		const auto prefix = "materials[" + std::to_string(i) + "]";
		addUniform(prefix + ".Ka");
		addUniform(prefix + ".Kd");
		addUniform(prefix + ".Ks");
		addUniform(prefix + ".shininess");
		addUniform(prefix + ".ambientTexId");
		addUniform(prefix + ".diffuseTexId");
		addUniform(prefix + ".specularTexId");
	}
	for (int i = 0; i < 8; ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		addUniform(prefix);
	}
	//shader.findUniformLocation("texture1");

	addAttribute("position");
	addAttribute("normal");
	addAttribute("materialId");
	addAttribute("texCoord");

	return build_(factory);
}

void SmoothRenderer::setLights(const std::vector<PointLight>& lights)
{
	auto shader = getShader();

	shader->bind();
	for (int i = 0; i < lights.size(); ++i) {
		const auto light = lights[i];
		const auto& lightPos = light.getPosition();//{ -10.0f, 10.0f, 10.0f };
		const auto& ambient = light.getAmbient();
		const auto& diffuse = light.getDiffuse();
		const auto& specular = light.getSpecular();

		const auto prefix = "lights[" + std::to_string(i) + "]";

		shader->sendUniform(prefix + ".position", lightPos);
		shader->sendUniform(prefix + ".La", ambient);
		shader->sendUniform(prefix + ".Ld", diffuse);
		shader->sendUniform(prefix + ".Ls", specular);
	}
	shader->unbind();
}

void SmoothRenderer::setTextures(const std::vector<TextureObject>& textures)
{
	auto shader = getShader();

	shader->bind();
	for (int i = 0; i < textures.size(); ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		shader->sendUniform(prefix, textures[i]);
	}
	shader->unbind();

	this->textures = textures;
}

void SmoothRenderer::setMaterials(const std::vector<Material>& materials)
{
	auto shader = getShader();
	shader->bind();

	for (int i = 0; i < materials.size(); ++i) {
		const auto m = materials[i];
		const auto prefix = "materials[" + std::to_string(i) + "]";
		shader->sendUniform(prefix + ".Ka", m.ambient);
		shader->sendUniform(prefix + ".Kd", m.diffuse);
		shader->sendUniform(prefix + ".Ks", m.specular);
		shader->sendUniform(prefix + ".shininess", m.shininess);
		auto index = findIndex(m.ambientTexName);
		shader->sendUniform(prefix + ".ambientTexId", index);
		shader->sendUniform(prefix + ".diffuseTexId", 0);// m.diffuseTexId);
		shader->sendUniform(prefix + ".specularTexId", 0);// m.specularTexId);
		//glUniform1i(shader->getUniformLocation("texture1"), texture.getId());
	}

	shader->unbind();

	const auto error = glGetError();
	assert(error == GL_NO_ERROR);
}

int SmoothRenderer::findIndex(const std::string& name)
{
	for (int i = 0; i < textures.size(); ++i) {
		if (textures[i].getName() == name) {
			return i;
		}
	}
	return -1;
}


void SmoothRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix() * glBuffer.matrix;
	const auto& eyePos = camera.getEye();

	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);
	shader->sendUniform("eyePosition", eyePos);

	shader->sendVertexAttribute3df("position", glBuffer.position);
	shader->sendVertexAttribute3df("normal", glBuffer.normal);
	shader->sendVertexAttribute2df("texCoord", glBuffer.texCoord);
	shader->sendVertexAttribute1di("materialId", glBuffer.materialId);


	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("normal");
	shader->enableVertexAttribute("materialId");
	shader->enableVertexAttribute("texCoord");

	for (const auto& t : textures) {
		t.bind();
	}

	shader->drawTriangles(glBuffer.count);

	for (const auto& t : textures) {
		t.unbind();
	}

	//textures[0].unbind();

	shader->disableVertexAttribute("texCoord");
	shader->disableVertexAttribute("materialId");
	shader->disableVertexAttribute("position");
	shader->disableVertexAttribute("normal");

	{
		const auto error = glGetError();
		assert(error == GL_NO_ERROR);
	}

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
		<< "struct LightInfo {" << std::endl
		<< "	vec3 position;" << std::endl
		<< "	vec3 La;" << std::endl
		<< "	vec3 Ld;" << std::endl
		<< "	vec3 Ls;" << std::endl
		<< "};"
		<< "uniform LightInfo lights[8];"
		<< "struct MaterialInfo {" << std::endl
		<< "	vec3 Ka;" << std::endl
		<< "	vec3 Kd;" << std::endl
		<< "	vec3 Ks;" << std::endl
		<< "	float shininess;" << std::endl
		<< "	int ambientTexId;" << std::endl
		<< "	int diffuseTexId;" << std::endl
		<< "	int specularTexId;" << std::endl
		<< "};"
		<< "uniform MaterialInfo materials[256];"
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
		<< "vec3 getDiffuseColor(LightInfo light, MaterialInfo material, float innerProduct){" << std::endl
		<< "	vec3 diffuse = light.Ld * material.Kd * innerProduct;" << std::endl
		<< "	return diffuse * getTextureColor(material.diffuseTexId);" << std::endl
		<< "};" << std::endl
		<< "vec3 getPhongShadedColor( vec3 position, vec3 normal) {"
		<< "	MaterialInfo material = materials[vMaterialId];" << std::endl
		<< "	LightInfo light = lights[0];" << std::endl
		<< "	vec3 s = normalize(light.position - vPosition);" << std::endl
		<< "	vec3 v = normalize(vPosition - eyePosition);" << std::endl
		<< "	vec3 r = reflect( -s, normal );" << std::endl
		<< "	vec3 ambient = getAmbientColor(light, material);" << std::endl
		<< "	float innerProduct = max( dot(s,normal), 0.0);" << std::endl
		<< "	vec3 diffuse = getDiffuseColor(light, material, innerProduct);" << std::endl
		<< "	vec3 specular = vec3(0.0);" << std::endl
		<< "	if(innerProduct > 0.0) {" << std::endl
		<< "		specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0 ), material.shininess );" << std::endl
		<< "	}" << std::endl
		<< "	specular *= getTextureColor(material.specularTexId);" << std::endl
		<< "	return ambient + diffuse + specular;" << std::endl
		<< "}"
		<< "void main(void) {" << std::endl
		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal);" << std::endl
//		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal) * getTextureColor();" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}