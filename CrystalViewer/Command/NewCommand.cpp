#include "NewCommand.h"

#include "Public/NewLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

std::string NewCommand::getName()
{
	return ::NewLabels::CommandNameLabel;
}

void NewCommand::execute(World* model)
{
	model->clear();
	model->init();
	model->getRenderer()->build();
	model->updateViewModel();
}
