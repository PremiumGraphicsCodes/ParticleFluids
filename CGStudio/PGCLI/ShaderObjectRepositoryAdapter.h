#pragma once

using namespace System;

namespace Crystal {
	namespace Shader {
		class ShaderObjectRepository;
	}
}

namespace PG {
	namespace CLI {
		//ref class MaterialObjectRepositoryAdapter;

public ref class ShaderObjectRepositoryAdapter
{
public:
	~ShaderObjectRepositoryAdapter();

	//MaterialObjectRepositoryAdapter^ Material();

internal:
	ShaderObjectRepositoryAdapter(Crystal::Shader::ShaderObjectRepository* instance);

	Crystal::Shader::ShaderObjectRepository* instance;
};

	}
}