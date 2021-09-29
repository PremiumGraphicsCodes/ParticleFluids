#include "VoxelizerCommandView.h"

#include "CrystalSpace/CrystalSpaceCommand/SpaceCommandFactory.h"
#include "CrystalSpace/CrystalSpaceCommand/PublicLabels/VoxelizerLabels.h"

#include "Crystal/Shape/TriangleMeshBuilder.h"
#include "Crystal/Math/Sphere3d.h"

#include "Crystal/IO/TXTFileWriter.h"

#include "CrystalScene/Scene/VoxelScene.h"
#include "CrystalScene/Scene/ParticleSystemScene.h"
#include "CrystalScene/Scene/TriangleMeshScene.h"


using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Space;
using namespace Crystal::UI;

VoxelizerCommandView::VoxelizerCommandView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	divideLengthView("DivideLength", 1.0f)
{
	add(&divideLengthView);
}

void VoxelizerCommandView::onOk()
{
	TriangleMeshBuilder builder;
	//const Box3d box(Vector3dd(2, 2, 2), Vector3dd(8, 8, 8));
	//builder.add(box, 2, 2, 2);
	const Sphere3dd sphere(Vector3dd(0, 0, 0), 5);
	builder.add(sphere, 32, 32);
	auto mesh = builder.build();
	auto meshScene = new TriangleMeshScene(getWorld()->getNextSceneId(), "", std::move(mesh));
	getWorld()->getScenes()->addScene(meshScene);

	auto voxel = std::make_unique<Volume<bool>>();
	auto voxelScene = new VoxelScene(getWorld()->getNextSceneId(), "", std::move(voxel));
	getWorld()->getScenes()->addScene(voxelScene);

	SpaceCommandFactory factory;
	auto command = factory.create(VoxelizerLabels::CommandNameLabel);
	command->setArg(VoxelizerLabels::MeshIdLabel, meshScene->getId());
	command->setArg(VoxelizerLabels::VoxelIdLabel, voxelScene->getId());
	command->setArg(VoxelizerLabels::DivideLengthLabel, divideLengthView.getValue());
	command->execute(getWorld());
	/*
	Voxelizer voxelizer;
	voxelizer.voxelize(*mesh, 1.0);
	//voxelizer.fill();
	auto voxel = voxelizer.getVoxel();

	std::vector<Math::Vector3dd> positions;
	for (int i = 0; i < voxel->getResolutions()[0]; ++i) {
		for (int j = 0; j < voxel->getResolutions()[1]; ++j) {
			for (int k = 0; k < voxel->getResolutions()[2]; ++k) {
				if (voxel->getValue(i, j, k)) {
					auto p = voxel->getCellPosition(i, j, k);
					positions.push_back(p);
				}
			}
		}
	}
	TXTFileWriter writer;
	writer.write("test2.txt", positions);
*/

	auto presenter = meshScene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}