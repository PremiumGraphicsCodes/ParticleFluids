#include "stdafx.h"
#include "AnyConverter.h"

using namespace PG::CLI;

std::any AnyConverter::toCpp(System::Object^ object)
{
	auto type = object->GetType();
	if (type == int::typeid) {
		const auto a = (int)(object);
		return std::any(a);
	}
	/*
	else if (type == double::typeid) {
		return std::any()
	}
	*/
	return std::any(0);
}

System::Object^ AnyConverter::fromCpp(std::any any)
{
	auto& type = any.type();
	if (type == typeid(int)) {
		return std::any_cast<int>(any);
	}
	return nullptr;
}
