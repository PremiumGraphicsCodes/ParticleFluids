#pragma once

#include <string>
#include <any>
#include <vector>
#include <algorithm>

namespace Crystal {
	namespace Command {

struct IArg
{
	IArg();

	IArg(const std::string& name, std::any value) :
		name(name),
		value(value)
	{}

	std::string name;
	std::any value;
};

template<typename T>
struct Arg : IArg
{
	Arg(const std::string& name, T value) :
		IArg(name, value)
	{}

	T getValue() { return std::any_cast<T>(value); }

	void setValue(const T value) { this->value = value; }
};

struct IArgs
{
	void add(IArg* arg) { args.push_back(arg); }

	std::any getValue(const std::string& name) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		return (*iter)->value;
	};

//	std::type_info


	void setValue(const std::string& name, std::any value) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		(*iter)->value = value;
	}

	std::vector<IArg*> args;
};

	}
}