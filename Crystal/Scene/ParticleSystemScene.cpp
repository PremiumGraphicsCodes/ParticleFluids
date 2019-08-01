#include "ParticleSystemScene.h"

#include "SceneViewModel.h"
#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"
#include "../Shader/Renderer.h"
#include "ShaderScene.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneViewModel ParticleSystemScene::toViewModel() const
{
	SceneViewModel viewModel;
	if (!isVisible()) {
		return viewModel;
	}
	const auto& particles = getShape()->getParticles();
	for (auto p : particles) {
		viewModel.pointBuffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	return viewModel;
}

SceneIdViewModel ParticleSystemScene::toIdViewModel() const
{
	SceneIdViewModel viewModel;
	const auto objectId = getId();
	const auto& particles = getShape()->getParticles();
	int particleId = 0;
	for (auto p : particles) {
		Graphics::DrawableID did(objectId, particleId++);
		viewModel.pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
	}
	return viewModel;
}

void ParticleSystemScene::getBoundingBox(Crystal::Math::Box3d& box) const
{
	box.add(getShape()->getBoundingBox());
}

Vector3dd ParticleSystemScene::getPosition(const int index) const
{
	const auto& ps = getShape()->getParticles();
	return ps[index]->getPosition();
}

void ParticleSystemScene::build()
{
	if (!isVisible()) {
		return;
	}
	const auto& particles = getShape()->getParticles();
	for (auto p : particles) {
		buffer.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	this->shader = getRoot()->findSceneByName<ShaderScene*>("PointShader")->getShader();
}

void ParticleSystemScene::render(const ICamera& camera)
{
	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->getId());

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, &modelviewMatrix[0][0]);

	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader->getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glVertexAttribPointer(shader->getAttribLocation("pointSize"), 1, GL_FLOAT, GL_FALSE, 0, sizes.data());


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size() / 3));

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glDisable(GL_DEPTH_TEST);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);


	glUseProgram(0);
}