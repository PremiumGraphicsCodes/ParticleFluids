#include "NewCommand.h"

#include "Public/NewLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

std::string NewCommand::getName()
{
	return ::NewLabels::CommandNameLabel;
}

bool NewCommand::execute(World* model)
{
	model->clear();
	model->init();
	model->getRenderer()->build(*model->getGLFactory());

	//world->getRenderer()->build(*world->getGLFactory());
	model->getCamera()->getPresenter()->createView(model->getRenderer(), *model->getGLFactory());

//	model->updateViewModel();

	return true;
}
