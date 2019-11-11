#pragma once

#include <any>

namespace PG {
	namespace CLI {

class AnyConverter
{
public:
	static std::any toCpp(System::Object^ object, System::Type^ type);

	static System::Object^ fromCpp(std::any any);
};

	}
}