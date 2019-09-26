#include "stdafx.h"
#include "Command.h"

#include <msclr/marshal_cppstd.h>

#include "../../Crystal/Command/Command.h"
#include "AnyConverter.h"

using namespace PG::CLI;

namespace {
	Crystal::Command::Command instance;
}

Command::Command(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	::instance.create(str);
}

void Command::SetArg(System::String^ name, System::Object^ value)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	const auto v = AnyConverter::toCpp(value);
	::instance.setArg(str, v);
}

void Command::Execute()
{
	::instance.execute();
}

System::Object^ Command::GetResult(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto result = ::instance.getResult(str);
	return AnyConverter::fromCpp(result);
}

void Command::Clear()
{
	::instance.clear();
}
