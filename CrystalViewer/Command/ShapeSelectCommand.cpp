#include "ShapeSelectCommand.h"
#include "../../Crystal/Scene/IShapeScene.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Command;

std::string ShapeSelectCommand::getName()
{
	return "ShapeSelectCommand";
}

ShapeSelectCommand::Args::Args() :
	shapeId("ShapeId", -1)
{
}

ShapeSelectCommand::Results::Results() :
	boundingBoxItemId("BoundingBoxItemId", -1)
{
}

void ShapeSelectCommand::execute(World* scene)
{
	auto shape = scene->getObjects()->findSceneById<IShapeScene*>(args.shapeId.getValue());
	if (shape == nullptr) {
		return;
	}
	auto isSelected = shape->isSelected();
	if (isSelected) {
		Box3d bb;
		shape->getBoundingBox(bb);
		WireFrameBuilder builder;
		builder.build(bb);
//		scene->getItemFactory()->createWireFrameScene()

		shape->setSelected(true);
	}
}