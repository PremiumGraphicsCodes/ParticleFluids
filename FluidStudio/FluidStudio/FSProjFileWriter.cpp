#include "FSProjFileWriter.h"

using namespace PG::FS;

nlohmann::json FSProjFileWriter::write(const FSScene& scene)
{
	return { {"MaxTimeStep", scene.args.maxTimeStep } };
}
