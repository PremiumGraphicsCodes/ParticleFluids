#pragma once

#include "../Util/UnCopyable.h"
#include <any>
#include <string>

namespace Crystal {
	namespace Command {

class IArg
{

};

struct IResult
{

};

class ICommand : private UnCopyable
{
public:
//	void setArg(const std::string& str, std::any value);

	virtual void execute() = 0;
};
	}
}