#pragma once
#include <vector>
#include <any>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

enum class PLYType
{
	CHAR,
	UCHAR,
	SHORT,
	USHORT,
	INT,
	UINT,
	FLOAT,
	DOUBLE,
};

struct PLYPoint
{
	PLYPoint() = default;

	std::vector<std::any> values;

	float getFloatValue(const size_t index) const
	{
		return std::any_cast<float>(values[index]);
	}
};

struct PLYProperty
{
	PLYProperty() = default;

	PLYProperty(const std::string& name, const PLYType& type) :
		name(name),
		type(type)
	{}

	std::string getTypeName() const {
		return "float";
	}

	std::string name;
	PLYType type;
};

struct PLYFile
{
	std::vector<PLYProperty> properties;
	std::vector<PLYPoint> vertices;

	PLYFile()
	{
		properties.push_back(PLYProperty("x", PLYType::FLOAT));
		properties.push_back(PLYProperty("y", PLYType::FLOAT));
		properties.push_back(PLYProperty("z", PLYType::FLOAT));
	}

	explicit PLYFile(const std::vector<PLYProperty>& properties) : properties(properties)
	{
	}

	void addPoint(const Math::Vector3df& position)
	{
		PLYPoint p;
		p.values.push_back(position.x);
		p.values.push_back(position.y);
		p.values.push_back(position.z);
		vertices.push_back(p);
	}
};

	}
}