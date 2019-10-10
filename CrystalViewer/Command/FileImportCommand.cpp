#include "FileImportCommand.h"
#include "Public/FileImportLabel.h"

#include "../../Crystal/IO/FileImporter.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

FileImportCommand::Args::Args() :
	filePath("FilePath", "")
{
	add(&filePath);
}

FileImportCommand::Results::Results() :
	isOk("IsOk", false)
{
	add(&isOk);
}

std::string FileImportCommand::getName()
{
	return ::FileImportCommandLabel;
}

void FileImportCommand::execute(World* scene)
{
	FileImporter importer;
	if (!importer.importFile(args.filePath.getValue(), scene->getObjects(), scene->getObjectFactory())) {
		results.isOk.value = false;
	}
	//scene->getObjects()
}