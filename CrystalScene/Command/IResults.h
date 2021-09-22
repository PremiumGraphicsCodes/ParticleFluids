#pragma once

#include <vector>
#include <string>
#include <any>
#include <algorithm>

namespace Crystal {
	namespace Command {

struct IResult
{
	IResult(const std::string& name, std::any value) :
		name(name),
		value(value)
	{}


	std::string name;
	std::any value;
};

template<typename T>
struct Result : IResult
{
	Result(const std::string& name, T value) :
		IResult(name, value)
	{}

	T getValue() { return std::any_cast<T>(value); }

	void setValue(const T value) { this->value = value; }
};


struct IResults
{
	void add(IResult* arg) { args.push_back(arg); }

	std::any getValue(const std::string& name) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		return (*iter)->value;
	};

	void setValue(const std::string& name, std::any value) {
		auto iter = std::find_if(args.begin(), args.end(), [=](auto a) { return a->name == name; });
		(*iter)->value = value;
	}

	std::vector<IResult*> args;

};

	}
}