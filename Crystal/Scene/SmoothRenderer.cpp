#include "SmoothRenderer.h"

#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

void SmoothTriangleBuffer::addVertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord, const int materialId, const int ambientTexId)
{
	positions.add(position);
	normals.add(normal);
	texCoords.add(texCoord);
	materialIds.add(materialId);
	ambientTexIds.add(ambientTexId);
//	materialIds.add(1);
}

SmoothRenderer::SmoothRenderer()
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
	}
	for (int i = 0; i < 8; ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		addUniform(prefix);
	}
	//shader.findUniformLocation("texture1");

	addAttribute("position");
	addAttribute("normal");
	addAttribute("materialId");
	addAttribute("ambientTexId");
	addAttribute("texCoord");
}

void SmoothRenderer::render(const Camera& camera)
{
	auto shader = getShader();

	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	const auto& texCoords = buffer.getTexCoords().get();
	const auto& ambientTexIds = buffer.getAmbientTexIds().get();
	const auto& materialIds = buffer.getMaterialIds().get();
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelViewMatrix() * Math::Matrix4df( buffer.getMatrix() );
	const auto& eyePos = camera.getEye();

	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);
	shader->sendUniform("eyePosition", eyePos);


	shader->sendVertexAttribute3df("position", positions);
	shader->sendVertexAttribute3df("normal", normals);
	shader->sendVertexAttribute1di("materialId", materialIds);
	shader->sendVertexAttribute1di("ambientTexId", ambientTexIds);
	shader->sendVertexAttribute2df("texCoord", texCoords);
	//glVertexAttribPointer(shader->getAttribLocation("texCoord"), 2, GL_FLOAT, GL_FALSE, 0, texCoords.data());


	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("normal");
	shader->enableVertexAttribute("materialId");
	shader->enableVertexAttribute("texCoord");

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

	for (int i = 0; i < materials.size(); ++i) {
		const auto m = materials[i];
		const auto prefix = "materials[" + std::to_string(i) + "]";
		shader->sendUniform(prefix + ".Ka", m.ambient);
		shader->sendUniform(prefix + ".Kd", m.diffuse);
		shader->sendUniform(prefix + ".Ks", m.specular);
		shader->sendUniform(prefix + ".shininess", m.shininess);
		//glUniform1i(shader->getUniformLocation("texture1"), texture.getId());
	}

	for (int i = 0; i < textures.size(); ++i) {
		const auto prefix = "textures[" + std::to_string(i) + "]";
		textures[i].bind();
		auto loc = glGetUniformLocation(shader->getId(), prefix.c_str());
		glUniform1i(loc, textures[i].getId());
	}


	const int count = positions.size() / 3;
	shader->drawTriangles(count);

	//textures[0].unbind();

	shader->disableVertexAttribute("texCoord");
	shader->disableVertexAttribute("ambientTexId");
	shader->disableVertexAttribute("materialId");
	shader->disableVertexAttribute("position");
	shader->disableVertexAttribute("normal");

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
		<< "in int ambientTexId;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec3 vNormal;" << std::endl
		<< "out vec3 vPosition;" << std::endl
		<< "flat out int vMaterialId;" << std::endl
		<< "flat out int vAmbientTexId;" << std::endl
		<< "out vec2 vTexCoord;" << std::endl
		<< "uniform mat4 projectionMatrix;"
		<< "uniform mat4 modelviewMatrix;"
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vNormal = normalize(normal);" << std::endl
		<< "	vPosition = position;" << std::endl
		<< "	vMaterialId = materialId;" << std::endl
		<< "	vAmbientTexId = ambientTexId;" << std::endl
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
		<< "flat in int vAmbientTexId;" << std::endl
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
		<< "};"
		<< "uniform MaterialInfo materials[256];"
		<< "vec3 getTextureColor(){ "
		<< "	return texture2D(textures[vAmbientTexId], vTexCoord).rgb;" << std::endl
		<< "};" << std::endl
		<< "vec3 getPhongShadedColor( vec3 position, vec3 normal) {"
		<< "	MaterialInfo material = materials[vMaterialId];" << std::endl
		<< "	LightInfo light = lights[0];" << std::endl
		<< "	vec3 s = normalize(light.position - vPosition);" << std::endl
		<< "	vec3 v = normalize(vPosition - eyePosition);" << std::endl
		<< "	vec3 r = reflect( -s, normal );" << std::endl
		<< "	vec3 ambient = light.La * material.Ka;" << std::endl
		<< "	ambient = ambient * getTextureColor();" << std::endl
		<< "	float innerProduct = max( dot(s,normal), 0.0);" << std::endl
		<< "	vec3 diffuse = light.Ld * material.Kd * innerProduct;" << std::endl
		<< "	vec3 specular = vec3(0.0);" << std::endl
		<< "	if(innerProduct > 0.0) {" << std::endl
		<< "		specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0 ), material.shininess );" << std::endl
		<< "	}" << std::endl
		<< "	return ambient + diffuse + specular;" << std::endl
		<< "}"
		<< "void main(void) {" << std::endl
		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal);" << std::endl
//		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal) * getTextureColor();" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}