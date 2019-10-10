#include "PickCommand.h"

#include "Public/PickLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PickCommand::Args::Args() :
	position(::PositionLabel, Vector2dd())
{
	add(&position);
}

PickCommand::Results::Results() :
	parentId(::ParentIdLabel, -1),
	childId(::ChildIdLabel,-1)
{
	add(&parentId);
	add(&childId);
}

std::string PickCommand::getName()
{
	return ::PickCommandLabel;
}

void PickCommand::execute(World* world)
{
	const auto& p = args.position.getValue();
	const auto id = world->getRenderer()->getObjectIdRenderer()->getId(p.x, p.y);
	results.parentId.setValue( id.getParentId() );
	results.childId.setValue( id.getChildId() );
}

