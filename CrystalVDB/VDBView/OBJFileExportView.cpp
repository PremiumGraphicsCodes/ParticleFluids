#include "OBJFileExportView.h"

#include "../VDBCommand/VDBOBJFileWriteCommand.h"

using namespace Crystal::UI;
using namespace Crystal::VDB;

OBJFileExportView::OBJFileExportView(const std::string& name, Scene::World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	vdbMeshSelectView("VDBMesh", model, canvas),
	filePathView("OBJFile")
{
	add(&vdbMeshSelectView);
	add(&filePathView);
}

void OBJFileExportView::onOk()
{
	VDBOBJFileWriteCommand::Args args;
	args.vdbMeshId.setValue( vdbMeshSelectView.getId() );
	args.filePath.setValue( filePathView.getFileName() );
	VDBOBJFileWriteCommand command(args);
	command.execute(getWorld());
}