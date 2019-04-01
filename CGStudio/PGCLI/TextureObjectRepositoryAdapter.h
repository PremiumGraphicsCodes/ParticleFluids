#pragma once

using namespace System;

namespace Crystal {
	namespace UI {
		class TextureObjectRepository;
	}
}

namespace PG {
	namespace CLI {

public ref class TextureObjectRepositoryAdapter
{
public:
	~TextureObjectRepositoryAdapter();

	int Add(PG::Core::Graphics::Texture^ texture);

internal:
	TextureObjectRepositoryAdapter(Crystal::UI::TextureObjectRepository* instance);

	Crystal::UI::TextureObjectRepository* instance;
};

	}
}