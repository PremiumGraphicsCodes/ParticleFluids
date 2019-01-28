#pragma once

#include <string>

namespace Crystal {
	namespace UI {

class IObject
{
public:
	explicit IObject(const int id) :
		id(id),
		_isVisible(true)
	{}

	IObject(const int id, const std::string& name) :
		id(id),
		name(name),
		_isVisible(true)
	{}

	~IObject() {};

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	int getId() const { return id; }

	bool isVisible() const { return _isVisible; }

	//void setVisible(const bool b) { this->_isVisible = b; }

	bool _isVisible;

private:
	std::string name;
	int id;
};
	}
}