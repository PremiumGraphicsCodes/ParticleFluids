#include "MeshToVoxelView.h"

#include "../CrystalSpace/MeshToVoxelConverter.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

MeshToVoxelView::MeshToVoxelView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	divideLengthView("DivideLength", 1.0)
{
	add(&divideLengthView);
}

void MeshToVoxelView::onOk()
{
	PolygonMeshBuilder builder;
	const Box3d box(Vector3dd(0, 0, 0), Vector3dd(10, 10, 10));
	builder.add(box);
	auto mesh = builder.build();

	MeshToVoxelConverter converter;
	converter.convert(*mesh, 1.0);
	/*
	auto id = polygonMeshSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<PolygonMeshScene*>(id);
	auto mesh = scene->getShape();

	MeshToParticleAlgo algo;
	algo.subdivide(*mesh, divideLengthView.getValue());
	const auto& positions = algo.getPositions();

	Command::Command command;
	command.create(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command.setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	//command.setArg(ParticleSystemCreateLabels::PointSizeLabel, 1.0f);
	//command.setArg(ParticleSystemCreateLabels::ColorLabel, glm::vec4);
	command.setArg(ParticleSystemCreateLabels::NameLabel, std::string("MeshToParticle"));
	//	command.setArg(ParticleSystemCreateLabels::MatrixLabel, matrixView.getValue());
	command.execute(getWorld());
	auto newId = std::any_cast<int>(command.getResult(ParticleSystemCreateLabels::NewIdLabel));

	command.create(ShaderBuildLabels::CommandNameLabel);
	command.setArg(ShaderBuildLabels::IdLabel, newId);
	command.execute(getWorld());

	command.create(CameraFitCommandLabels::CameraFitCommandLabel);
	command.execute(getWorld());
	*/
}