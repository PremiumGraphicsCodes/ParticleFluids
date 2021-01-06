#include "OBJFileImportView.h"

#include "../VDBCommand/VDBOBJFileReadCommand.h"
#include "../VDBCommand/PublicLabels/VDBOBJFileReadLabels.h"

#include "../VDBConverter/VDBPolygonMesh.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

OBJFileImportView::OBJFileImportView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	fileOpenView("OBJFile")
{
	add(&fileOpenView);
	fileOpenView.addFilter("obj");
}

void OBJFileImportView::onOk()
{
	VDBOBJFileReadCommand::Args args;
	args.filePath.setValue(fileOpenView.getFileName());
	VDBOBJFileReadCommand command(args);
	command.execute(getWorld());
	auto newId = std::any_cast<int>( command.getResult(::VDBMeshIdLabel) );
	auto mesh = getWorld()->getScenes()->findSceneById<VDBPolygonMesh*>(newId);
	mesh->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}