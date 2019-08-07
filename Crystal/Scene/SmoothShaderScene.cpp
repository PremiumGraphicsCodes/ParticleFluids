#include "SmoothShaderScene.h"

#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

SmoothShaderScene::SmoothShaderScene(const int id, const std::string& name) :
	ShaderScene(id, name)
{
	setVertexShaderSource(getBuildInVertexShaderSource());
	setFragmentShaderSource(getBuiltInFragmentShaderSource());

	addUniform("projectionMatrix");
	addUniform("modelviewMatrix");
	addUniform("eyePosition");
	addUniform("lights[0].position");
	addUniform("lights[0].La");
	addUniform("lights[0].Ld");
	addUniform("lights[0].Ls");
	addUniform("materials[0].Ka");
	addUniform("materials[0].Kd");
	addUniform("materials[0].Ks");
	addUniform("materials[0].shininess");
	//shader.findUniformLocation("texture1");

	addAttribute("position");
	addAttribute("normal");
	//shader.findAttribLocation("texCoord");
}

void SmoothShaderScene::render(const ICamera& camera)
{
	auto shader = getShader();

	const auto& indices = buffer.getIndices().get();
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	const auto& texCoords = buffer.getTexCoords().get();
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();
	const auto& eyePos = camera.getPosition();

	shader->bind();
	shader->bindOutput("fragColor");

	shader->enableDepthTest();

	shader->sendUniform("projectionMatrix", projectionMatrix);
	shader->sendUniform("modelviewMatrix", modelviewMatrix);
	shader->sendUniform("eyePosition", eyePos);


	shader->sendVertexAttribute3df("position", positions);
	shader->sendVertexAttribute3df("normal", normals);
	//glVertexAttribPointer(shader->getAttribLocation("texCoord"), 2, GL_FLOAT, GL_FALSE, 0, texCoords.data());


	shader->enableVertexAttribute("position");
	shader->enableVertexAttribute("normal");

	//texture.bind();

	{
		const auto light = Graphics::PointLight();
		const auto& lightPos = light.getPosition();//{ -10.0f, 10.0f, 10.0f };
		const auto& ambient = light.getAmbient();
		const auto& diffuse = light.getDiffuse();
		const auto& specular = light.getSpecular();

		//glUniform3fv(shader->getUniformLocation("light.position"), 1, &lightPos[0]);
		shader->sendUniform("lights[0].La", ambient);
		shader->sendUniform("lights[0].Ld", diffuse);
		shader->sendUniform("lights[0].Ls", specular);

		const auto& m = Graphics::Material();
		shader->sendUniform("materials[0].Ka", m.ambient);
		shader->sendUniform("materials[0].Kd", m.diffuse);
		shader->sendUniform("materials[0].Ks", m.specular);
		shader->sendUniform("materials[0].shininess", m.shininess);
		//glUniform1i(shader->getUniformLocation("texture1"), texture.getId());
		shader->drawTriangles(indices);
		//glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}

	//texture.unbind();

	shader->disableVertexAttribute("position");
	shader->disableVertexAttribute("normal");

	shader->disableDepthTest();
	shader->unbind();
}

std::string SmoothShaderScene::getBuildInVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		//<< "in vec2 texCoord;" << std::endl
		<< "out vec3 vNormal;" << std::endl
		<< "out vec3 vPosition;" << std::endl
		//<< "out vec2 vTexCoord;" << std::endl
		<< "uniform mat4 projectionMatrix;"
		<< "uniform mat4 modelviewMatrix;"
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vNormal = normalize(normal);" << std::endl
		<< "	vPosition = position;" << std::endl
		//<< "	vTexCoord = texCoord;" << std::endl
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
		//<< "in vec2 vTexCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		//<< "uniform sampler2D texture1;" << std::endl
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
		<< "vec3 getPhongShadedColor( vec3 position, vec3 normal) {"
		<< "	MaterialInfo material = materials[0];" << std::endl
		<< "	LightInfo light = lights[0];" << std::endl
		<< "	vec3 s = normalize(light.position - vPosition);" << std::endl
		<< "	vec3 v = normalize(vPosition - eyePosition);" << std::endl
		<< "	vec3 r = reflect( -s, normal );" << std::endl
		<< "	vec3 ambient = light.La * material.Ka;" << std::endl
		//		<< "	vec3 ambient = light.La * texture(texture1, vTexCoord).rgb;" << std::endl
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
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}