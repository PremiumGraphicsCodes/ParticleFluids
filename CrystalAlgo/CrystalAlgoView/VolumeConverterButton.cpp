#include "VolumeConverterButton.h"

#include "../CrystalAlgo/VolumeConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

VolumeConverterButton::VolumeConverterButton(Repository* model, Canvas* canvas) :
	IPopupButton("VolumeConverter", model, canvas)//,
//	objectButton1("ParticleSystem", model, canvas, Model::ObjectType::ParticleSystemObject)
{
}

void VolumeConverterButton::onShow()
{
//	objectButton1.show();
}

void VolumeConverterButton::onOk()
{
	Math::Box3d box;
	Volume3d volume(32, 32, 32, box);

	//Crystal::Shape::PolygonMeshBuilder builder;
	//builder.build(triangles);
	//Crystal::Shape::ParticleSystem particleSystem(volume.to)
	//getModel()->getObjects()->getParticleSystems()->addObject(volume.toParticles(), 1, "VolumeConverter");
	//getCanvas()->setViewModel(getModel()->toViewModel());
}

void VolumeConverterButton::onCancel()
{
}

