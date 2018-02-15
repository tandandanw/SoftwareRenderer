#pragma once

#include "Config.h"
#include "Scene.h"
#include "RenderMath.h"
#include "RenderObject.h"

#include <Windows.h>

namespace Tan
{
	class SoftwareRenderer
	{
	public:
		SoftwareRenderer();
		SoftwareRenderer(const SoftwareRenderer&) = delete;
		~SoftwareRenderer() = default;

	public:
		bool	      Initialize();
		void          Shutdown();
		void          Run();

		void          Draw();
		void	      Update();
		void		  Clear();

		void	      DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void		  Lighting(Vertex& vertex);
		bool          BackfaceCulling(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		bool	      Clipping(const Vertex& vertex);
		void	      Homogenize(Vertex& vertex);

		void	      FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void	      FillTopTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void          FillBottomTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void          FillScanline(const Vertex& vl, const Vertex& vr, int y);

		void          DrawLine(float x1, float y1, float x2, float y2);

		inline void   DrawPixel(float x, float y, UINT color);

	private:
		Scene        *mScene; // It can be a list of scenes.

		UINT        **mFrameBuffer;
		float       **mZBuffer;

		HDC           mHDC;
		HBITMAP       hBitMap;
		HWND          hWnd;
		HINSTANCE     hInstance;
	};

	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}




