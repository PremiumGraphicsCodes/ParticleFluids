#include "ShapeSelectCommand.h"
#include "../../Crystal/Scene/IShapeScene.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/WireFrameScene.h"

#include "Public/ShapeSelectLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Command;

std::string ShapeSelectCommand::getName()
{
	return ShapeSelectLabels::CommandNameLabel;
}

ShapeSelectCommand::Args::Args() :
	shapeId(ShapeSelectLabels::ShapeIdLabel, -1)
{
	add(&shapeId);
}

ShapeSelectCommand::Results::Results() :
	boundingBoxItemId(ShapeSelectLabels::BoundingBoxItemIdLabel, -1)
{
	add(&boundingBoxItemId);
}

void ShapeSelectCommand::execute(World* scene)
{
	auto shape = scene->getObjects()->findSceneById<IShapeScene*>(args.shapeId.getValue());
	if (shape == nullptr) {
		return;
	}
	auto isSelected = shape->isSelected();
	if (!isSelected) {
		Box3d bb;
		shape->getBoundingBox(bb);
		WireFrameBuilder builder;
		builder.build(bb);
		WireFrameAttribute attribute;
		attribute.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
		attribute.width = 1.0f;
		auto shape = scene->getItemFactory()->createWireFrameScene(builder.createWireFrame(),attribute,"BoundingBox");
		scene->getItems()->addScene(shape);
		shape->setSelected(true);
	}
}