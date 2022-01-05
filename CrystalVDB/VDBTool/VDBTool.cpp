#include "CommandLineOptions.h"

#include "PSToMeshTool.h"

#include <vector>

//using namespace Crystal::VDB;
using namespace Crystal::VDBTool;

int main(int argc, char* argv[])
{
    CommandLineOptions options;
    std::vector<std::string> strs;
    for (int i = 0; i < argc; ++i) {
        strs.push_back(argv[i]);
    }
    options.parse(strs);

    PSToMeshTool tool;
    tool.execute(options);
}