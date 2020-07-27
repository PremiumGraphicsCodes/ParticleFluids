#include "VolumeScene.h"

#include "../../Crystal/Math/Sphere3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;

VolumeScene::VolumeScene(const int id, const std::string& name, std::unique_ptr<Volume<double>> shape) :
	IShapeScene(id, name, shape.get())
{
}
