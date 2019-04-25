#pragma once

using namespace System;

namespace Crystal {
	namespace Shader {
		class TextureObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class TextureObjectRepositoryAdapter
{
public:
	TextureObjectRepositoryAdapter();

	~TextureObjectRepositoryAdapter();

	int Add(PG::Core::Graphics::Texture^ texture);

internal:
	TextureObjectRepositoryAdapter(Crystal::Shader::TextureObjectRepository* instance);

	Crystal::Shader::TextureObjectRepository* instance;
};

	}
}