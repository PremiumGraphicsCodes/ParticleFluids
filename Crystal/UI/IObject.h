#pragma once

#include <string>

namespace Crystal {
	namespace UI {

class IObject
{
public:
	explicit IObject(const int id) :
		id(id)
	{}

	IObject(const int id, const std::string& name) :
		id(id),
		name(name)
	{}

	~IObject() {};

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	int getId() const { return id; }

private:
	std::string name;
	int id;
};
	}
}