#pragma once

#include <string>
#include <any>
#include <vector>
#include <algorithm>

namespace Crystal {
	namespace Command {

struct ILabeledValue
{
	ILabeledValue()
	{}

	ILabeledValue(const std::string& name, std::any value) :
		name(name),
		value(value)
	{}

	std::string name;
	std::any value;
};

template<typename T>
struct LabeledValue : public ILabeledValue
{
	LabeledValue(const std::string& name, T value) :
		ILabeledValue(name, value)
	{}

	T getValue() { return std::any_cast<T>(value); }

	void setValue(const T value) { this->value = value; }
};

	}
}