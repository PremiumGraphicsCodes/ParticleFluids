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

struct LabledValueTree
{
	void add(ILabeledValue* arg) { args.push_back(arg); }

	void add(LabledValueTree* child) { children.push_back(child); }

	std::any getValue(const std::string& name) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		return (*iter)->value;
	};

	const std::type_info& getType(const std::string& name) {
		return getValue(name).type();
	}
	/*

	void setValue(const std::string& name, std::any value) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		(*iter)->value = value;
	}
	*/

private:
	std::vector<ILabeledValue*> args;
	std::vector<LabledValueTree*> children;
};

	}
}