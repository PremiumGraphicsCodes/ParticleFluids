#pragma once

#include "LabeledValue.h"

namespace Crystal {
	namespace Command {

struct LabeledValueTree
{
	LabeledValueTree()
	{}

	explicit LabeledValueTree(const std::string& name) :
		name(name)
	{}

	void setName(const std::string& name) {
		this->name = name;
	}

	std::string getName() const { return name; }

	void add(ILabeledValue* arg) { values.push_back(arg); }

	void add(LabeledValueTree* child) { children.push_back(child); }

	std::any getValue(const std::string& name) const {
		auto iter = std::find_if(values.begin(), values.end(), [=](auto a) { return a->name == name; });
		return (*iter)->value;
	};

	const std::type_info& getType(const std::string& name) const {
		return getValue(name).type();
	}

	std::vector<ILabeledValue*> getValues() const { return values; }

	std::vector<LabeledValueTree*> getChildren() const { return children; }

	/*

	void setValue(const std::string& name, std::any value) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		(*iter)->value = value;
	}
	*/

private:
	std::string name;
	std::vector<ILabeledValue*> values;
	std::vector<LabeledValueTree*> children;
};

	}
}