#include "GL/glew.h"

#include "ImageView.h"


using namespace Crystal::Graphics;
using namespace Crystal::UI;

void ImageView::show()
{
	Graphics::Image image(32, 32, 255);

	// Turn the RGBA pixel data into an OpenGL texture:
	GLuint my_opengl_texture;
	glGenTextures(1, &my_opengl_texture);
	glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	auto data = image.getValues();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	ImGui::Image((void*)(intptr_t)my_opengl_texture, ImVec2(image.getWidth(), image.getHeight()));

}
