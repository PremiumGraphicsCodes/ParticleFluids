#include "Canvas.h"
#include "../Graphics/PerspectiveCamera.h"
#include "CameraUICtrl.h"
#include "../Math/Box3d.h"
#include "ObjectRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Model;
using namespace Crystal::UI;

Canvas::Canvas() :
	Canvas(new PerspectiveCamera(
	1.0,
	0.5f * Tolerance<double>::getPI(),
	Vector3df(0, 0, 0),
	Vector3df(0, 0, -10.0),
	1.0f, 10.0f))
{
}

Canvas::Canvas(ICamera* camera) :
	width(0),
	height(0),
	camera(camera)
{
	renderer.reset(new Renderer(camera));
}

void Canvas::build(TextureObjectRepository& textures)
{
	setUICtrl(new CameraUICtrl(getCamera()));

	renderer->build(textures);
}

void Canvas::render(const int width, const int height, const TextureObjectRepository& textures)
{
	this->width = width;
	this->height = height;
	renderer->render(width, height, textures);
}

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

void Canvas::fitCamera(const Box3d& boundingBox)
{
	const auto& dist = static_cast<float>( glm::distance(boundingBox.getMin(), boundingBox.getMax()) );
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->setTarget(boundingBox.getCenter());
	camera->moveTo(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0));
}

void Canvas::setCameraXY(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->setRotation(glm::mat4());
}

void Canvas::setCameraYZ(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->rotate(glm::radians(90.0f), 0.0);
}

void Canvas::setCameraZX(const Box3d& boundingBox)
{
	fitCamera(boundingBox);
	camera->rotate(0.0, glm::radians(90.0f));
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
