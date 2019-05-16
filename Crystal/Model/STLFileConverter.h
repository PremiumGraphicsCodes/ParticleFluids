#pragma once

#include "../IO/STLFile.h"

namespace Crystal {
	namespace Model {
		class ObjectRepository;

class STLFileConverter
{
public:
	IO::STLFile toSTL(ObjectRepository& repository);

	void fromSTL(const IO::STLFile& stl, ObjectRepository& repository);

private:
	
};
	}
}