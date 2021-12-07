#include "SPHSurfaceConstructionCommand.h"

//#include "../CrystalPhysics/KFFluidScene.h"
#include "CrystalScene/Scene/IParticleSystemScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"
#include "CrystalSpace/CrystalSpace/SparseVolumeScene.h"
#include "CrystalSpace/CrystalSpace/MarchingCubesAlgo.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPParticleBuilder.h"
#include "CrystalPhysics/CrystalPhysics/MVPSurfaceBuilder.h"

#include "../../CrystalPhysics/CrystalPhysics/SurfaceConstruction/SPHSurfaceBuilder.h"

#include "CrystalScene/Command/Public/PublicLabel.h"

namespace {
	PublicLabel CommandNameLabel = "SPHSurfaceConstructionCommand";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
	PublicLabel TriangleMeshIdLabel = "TriangleMeshId";
	PublicLabel ParticleRadiusLabel = "ParticleRadius";
	PublicLabel CellLengthLabel = "CellLength";
	PublicLabel ThresholdLabel = "Threshold";
	PublicLabel IsIsotropicLabel = "IsIsotoropic";
}


using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;
using namespace Crystal::Scene;

std::string SPHSurfaceConstructionCommand::getName()
{
	return ::CommandNameLabel;
}

SPHSurfaceConstructionCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	triangleMeshId(::TriangleMeshIdLabel, -1),
	particleRadius(::ParticleRadiusLabel, 1.0),
	cellLength(::CellLengthLabel, 1.0),
	threshold(::ThresholdLabel, 1.0f),
	isIsotorpic(::IsIsotropicLabel, true)
{
	add(&particleSystemId);
	add(&triangleMeshId);
	add(&particleRadius);
	add(&cellLength);
	add(&threshold);
	add(&isIsotorpic);
}

SPHSurfaceConstructionCommand::Results::Results()// :
//	newId(::NewIdLabel, 0)
{
//	add(&newId);
}

SPHSurfaceConstructionCommand::SPHSurfaceConstructionCommand() :
	ICommand(&args, &results)
{}

bool SPHSurfaceConstructionCommand::execute(World* world)
{
	auto ps = world->getScenes()->findSceneById<IParticleSystemScene*>(args.particleSystemId.getValue());
	if (ps == nullptr) {
		return false;
	}
	auto sp = world->getScenes()->findSceneById<TriangleMeshScene*>(args.triangleMeshId.getValue());
	if (sp == nullptr) {
		return false;
	}

	const auto positions = ps->getPositions();

	const auto particleRadius = args.particleRadius.getValue();
	const auto cellLength = args.cellLength.getValue();

	MVPParticleBuilder pbuilder;
	std::vector<MVPVolumeParticle*> mvps;
	for (const auto& p : positions) {
		auto mp = pbuilder.create(p, particleRadius, 3, 3, 3, 1.0f);
		mvps.push_back(mp);
	}


	MVPSurfaceBuilder builder;
	builder.build(mvps, 1, args.threshold.getValue());
	auto mesh = std::make_unique<TriangleMesh>();
	const auto triangles = builder.getTriangles();
	for (const auto& t : triangles) {
		mesh->addFace(TriangleFace(t));
	}
	sp->setShape(std::move(mesh));

	for (auto mp : mvps) {
		delete mp;
	}

	/*
	SPHSurfaceBuilder builder;
	std::unique_ptr<SparseVolumed> volume;
	if (args.isIsotorpic.getValue()) {
		builder.buildIsotoropic(positions, particleRadius, cellLength);
	}
	else {
		builder.buildAnisotoropic(positions, args.particleRadius.getValue(), cellLength);
	}

	MarchingCubesAlgo mcAlgo;
	mcAlgo.build(*builder.getVolume(), args.threshold.getValue());

	//PolygonMeshBuilder pmBuilder;
	auto mesh = std::make_unique<TriangleMesh>();
	const auto triangles = mcAlgo.getTriangles();
	for (const auto& t : triangles) {
		mesh->addFace(TriangleFace(t));
	}
	sp->setShape(std::move(mesh));
	*/
	//sp->
	//results.newId.setValue(fluidScene->getId());
	return true;
}