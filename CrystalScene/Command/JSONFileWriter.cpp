#include "JSONFileWriter.h"
#include "JSONConverter.h"
#include <fstream>

using namespace Crystal::Command;

void JSONFileWriter::add(ICommand* command)
{
	commands.push_back(command);
}

bool JSONFileWriter::write(const std::filesystem::path& path)
{
	std::ofstream stream(path);
	if (!stream.is_open()) {
		return false;
	}
	JSONConverter converter;
	for (auto c : commands) {
		const auto j = converter.toJSON(*c);
		stream << std::setw(4) << std::endl;
	}
	return true;
}
