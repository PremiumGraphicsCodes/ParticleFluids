#pragma once

#include <string>
#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace UI {

class IObject
{
public:
	IObject() :
		id(-1),
		_isVisible(false)
	{}

	explicit IObject(const int id) :
		id(id),
		_isVisible(true)
	{}

	IObject(const int id, const std::string& name) :
		id(id),
		name(name),
		_isVisible(true)
	{}

	virtual ~IObject() {};

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	int getId() const { return id; }

	bool isVisible() const { return _isVisible; }

	void setVisible(const bool b) { this->_isVisible = b; }

	//void setVisible(const bool b) { this->_isVisible = b; }

	bool _isVisible;

	virtual void move(const Math::Vector3dd& v) = 0;

	virtual void transform(const Math::Matrix3dd& m) = 0;

	virtual void transform(const Math::Matrix4dd& m) = 0;

	virtual bool isNull() const = 0;

private:
	std::string name;
	int id;
};
	}
}