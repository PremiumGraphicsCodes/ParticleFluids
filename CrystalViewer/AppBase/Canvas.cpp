#include "Canvas.h"
#include "CameraUICtrl.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Scene/Renderer.h"
#include "../../Crystal/Scene/World.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::UI;

Canvas::Canvas() :
	width(0),
	height(0)
{
}

/*
Canvas::Canvas(ICamera* camera) :
	width(0),
	height(0),
	camera(camera)
{
	renderer.reset(new Renderer());
}

void Canvas::build()
{
	setUICtrl(new CameraUICtrl(getCamera()));
}

/*
void Canvas::render(const int width, const int height, IShaderScene* scene, const SceneViewModel& vm)
{
}
*/

void Canvas::onLeftButtonDown(const Vector2df& position)
{
	ctrl->onLeftButtonDown(position);
}

void Canvas::onLeftButtonUp(const Vector2df& position)
{
	ctrl->onLeftButtonUp(position);
}

void Canvas::onRightButtonDown(const Vector2df& position)
{
	ctrl->onRightButtonDown(position);
}

void Canvas::onRightButtonUp(const Vector2df& position)
{
	ctrl->onRightButtonUp(position);
}

void Canvas::onMiddleButtonDown(const Vector2df& position)
{
	ctrl->onMiddleButtonDown(position);
}

void Canvas::onMiddleButtonUp(const Vector2df& position)
{
	ctrl->onMiddleButtonUp(position);
}

void Canvas::onLeftDragging(const Vector2df& position)
{
	ctrl->onLeftDragging(position);
}

void Canvas::onRightDragging(const Vector2df& position)
{
	ctrl->onRightDragging(position);
}

void Canvas::onMiddleDragging(const Vector2df& position)
{
	ctrl->onMiddleDragging(position);
}

void Canvas::onWheel(const float scale)
{
	ctrl->onWheel(scale);
}

Image Canvas::getImage() const
{
	const unsigned int channelNum = 4; // RGB�Ȃ�3, RGBA�Ȃ�4
	void* dataBuffer = NULL;
	dataBuffer = (GLubyte*)malloc(width * height * channelNum);

	// �ǂݎ��OpneGL�̃o�b�t�@���w�� GL_FRONT:�t�����g�o�b�t�@�@GL_BACK:�o�b�N�o�b�t�@
	glReadBuffer(GL_BACK);

	// OpenGL�ŉ�ʂɕ`�悳��Ă�����e���o�b�t�@�Ɋi�[
	glReadPixels(
		0,                 //�ǂݎ��̈�̍�������x���W
		0,                 //�ǂݎ��̈�̍�������y���W //0 or getCurrentWidth() - 1
		width,             //�ǂݎ��̈�̕�
		height,            //�ǂݎ��̈�̍���
		GL_RGBA, //it means GL_BGR,           //�擾�������F���̌`��
		GL_UNSIGNED_BYTE,  //�ǂݎ�����f�[�^��ۑ�����z��̌^
		dataBuffer      //�r�b�g�}�b�v�̃s�N�Z���f�[�^�i���ۂɂ̓o�C�g�z��j�ւ̃|�C���^
	);

	GLubyte* p = static_cast<GLubyte*>(dataBuffer);

	Image image(width, height);
	int index = 0;
	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			const auto r = *p;
			const auto g = *(p + 1);
			const auto b = *(p + 2);
			const auto a = *(p + 3);
			const ColorRGBAuc color(r, g, b, a);
			image.setColor(i, j, color);
			p += 4;
		}
	}
	return image;
}
