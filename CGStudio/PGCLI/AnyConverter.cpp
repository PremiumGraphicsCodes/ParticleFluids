#include "stdafx.h"
#include "AnyConverter.h"
#include "Converter.h"

using namespace PG::CLI;

std::any AnyConverter::toCpp(System::Object^ object)
{
	auto type = object->GetType();
	if (type == int::typeid) {
		const auto a = (int)(object);
		return std::any(a);
	}
	else if (type == float::typeid) {
		const auto a = (float)(object);
		return std::any(a);
	}
	else if (type == double::typeid) {
		const auto a = (double)(object);
		return std::any(a);
	}
	else if (type == System::String::typeid) {
		const auto str = Converter::toCpp((System::String^)object);
		return std::any(str);
	}
	else if (type == System::Collections::Generic::List<Core::Math::Vector3d^>::typeid) {
		auto values = (System::Collections::Generic::List<Core::Math::Vector3d^>^)object;
		std::vector<Crystal::Math::Vector3dd> dest(values->Count);
		for (int i = 0; i < values->Count; ++i) {
			dest[i] = Converter::toCpp(values[i]);
		}
		return std::any(dest);
	}
	else if (type == System::Collections::Generic::List<Core::Math::Line3d^>::typeid) {
		auto values = (System::Collections::Generic::List<Core::Math::Line3d^>^)object;
		std::vector<Crystal::Math::Line3dd> dest(values->Count);
		for (int i = 0; i < values->Count; ++i) {
			dest[i] = Converter::toCpp(values[i]);
		}
		return std::any(dest);
	}

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
