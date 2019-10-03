#include "PickCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PickCommand::Args::Args() :
	position("Position", Vector2dd())
{
	add(&position);
}

PickCommand::Results::Results() :
	parentId("ParentId", -1),
	childId("ChildId",-1)
{
	add(&parentId);
	add(&childId);
}

void PickCommand::execute(World* world)
{
	const auto& p = args.position.getValue();
	const auto id = world->getRenderer()->getObjectIdRenderer()->getId(p.x, p.y);
	results.parentId.setValue( id.getParentId() );
	results.childId.setValue( id.getChildId() );
}

