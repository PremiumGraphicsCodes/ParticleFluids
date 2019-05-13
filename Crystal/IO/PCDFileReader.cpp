#include "PCDFileReader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::IO;

namespace {
	std::vector<std::string> split(const std::string& input, char delimiter)
	{
		std::istringstream stream(input);

		std::string field;
		std::vector<std::string> result;
		while (std::getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}
}

bool PCDFileReader::read(const std::string& filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool PCDFileReader::read(std::istream& stream)
{
	if (!parseHeader(stream)) {
		return false;
	}
	if (!parseData(stream)) {
		return false;
	}
	return true;
}

bool PCDFileReader::parseHeader(std::istream& stream)
{
	std::string str;
	while (std::getline(stream, str)) {
		if (str.empty()) {
			continue;
		}
		if (str[0] == '#') {
			continue;
		}
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 2);
		if (splitted[0] == "VERSION") {
			this->version = splitted[1];
			continue;
		}
		else if (splitted[0] == "FIELDS") {
			continue;
		}
		else if (splitted[0] == "DATA") {
			return true;
		}
	}

	return true;
}

bool PCDFileReader::parseData(std::istream& stream)
{
	std::string str;
	while (std::getline(stream, str)) {
		const auto& splitted = ::split(str, ' ');
		assert(splitted.size() >= 3);
		const auto x = std::stod(splitted[0]);
		const auto y = std::stod(splitted[1]);
		const auto z = std::stod(splitted[2]);
		positions.push_back(Vector3dd(x, y, z));
	}

	return true;
}

