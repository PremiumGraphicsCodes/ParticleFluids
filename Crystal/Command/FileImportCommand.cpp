#include "FileImportCommand.h"

#include "../IO/FileImporter.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

void FileImportCommand::execute(World* scene)
{
	FileImporter importer;
	if (!importer.importFile(args.filePath.getValue(), scene->getObjects(), scene->getObjectFactory())) {
		results.isOk.value = false;
	}
	//scene->getObjects()
}