#include "stdafx.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "PGCLI.h"

#pragma once

//

//
//↑こいつの#include は、たぶんこことかではなく、
// コードの中でもusing namespace System;とか記述する
// よりも前にしないと、C2872 に苦しめられることになる。

class OpenGLSimpleAdapter
	// ↑CLRでやる場合は、class の前に、public ref を入れてね
{
	// 
	// OpenGL Simple Adaptor loOGLHost (C) 2008 nurs 
	// 
	// 使い方： 
	// 1)本クラスのインスタンスを、ターゲットビューのメンバとして作成する。 
	//   コンストラクタのHDCは、Win32なら
	//   　⇒  ::GetDC( this->GetSafeHwnd() ) );
	//   CLRのFormなら、
	//     ⇒　::GetDC( (HWND)parentForm->Handle.ToPointer() );
	//   などとして取ってきます。 
	// 2)ターゲットビューの、適切な箇所（初期化、描画、リサイズ）にて、
	//   本ホストの、BeginRender()と、EndRender() を呼び出し、その間に、
	//   目的のOpenGL描画コードを記述します。
	// *)ちなみに利用側コードのどこかのcpp内にて、
	//#pragma comment( lib, "opengl32.lib" )
	//#pragma comment( lib, "glu32.lib" )
	//#pragma comment( lib, "gdi32.lib" )
	//#pragma comment( lib, "User32.lib" )
	// 　の記述も、忘れないで下さい。
	//
	// ★RenderPolicyを予め作成しておき、必要なときに必要な描画
	//   ポリシーで、Render() をかける、という使い方もできます。
	// ★注意：WindowsForm、.NET環境の場合は、プロジェクトの共通言語
	//   ランタイムサポートを、/clr:pure ではなく、/clr にする。
	//
	//
public:
	OpenGLSimpleAdapter(HDC dc) {
		if (dc == 0) return;
		m_hdc = dc;
		{
			_pfd = {
				sizeof(PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL
				| PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
			};
			GLint iPixelFormat;
			if ((iPixelFormat = ChoosePixelFormat(m_hdc, &_pfd)) == 0)
				return;
			if (SetPixelFormat(m_hdc, iPixelFormat, &_pfd) == FALSE)
				return;
		}
		if ((m_hglrc = wglCreateContext(m_hdc)) == 0)
			return; // pure Managed だとランタイムでエラーに 
		if ((wglMakeCurrent(m_hdc, m_hglrc)) == 0)
			return;
		wglMakeCurrent(0, 0);
		return;
	}
	~OpenGLSimpleAdapter(void) {}
	template< class RenderPolicy > void Render(RenderPolicy& po) {
		wglMakeCurrent(this->m_hdc, this->m_hglrc);
		po();
		wglMakeCurrent(this->m_hdc, 0);
		SwapBuffers(this->m_hdc);
	}
	HDC BeginRender(void) {
		wglMakeCurrent(this->m_hdc, this->m_hglrc);
		return this->m_hdc;
	}
	void EndRender(void) {
		SwapBuffers(this->m_hdc);
		wglMakeCurrent(NULL, NULL);
	}
	HDC BeginRender(HDC hdc) {
		wglMakeCurrent(hdc, this->m_hglrc);
		return hdc;
	}
	void EndRender(HDC hdc) {
		SwapBuffers(hdc);
		wglMakeCurrent(NULL, NULL);
	}
	void EndRenderNoSwap(void) {
		wglMakeCurrent(this->m_hdc, 0);
	}
	void EndRenderNoSwap(HDC hdc) {
		wglMakeCurrent(hdc, 0);
	}
private:
	HDC m_hdc;
	HGLRC m_hglrc;
	PIXELFORMATDESCRIPTOR _pfd;
	//POC_PROP(PIXELFORMATDESCRIPTOR, _pfd, Pfd);
};