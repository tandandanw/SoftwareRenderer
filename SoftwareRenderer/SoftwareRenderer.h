#pragma once

#include "Config.h"
#include "RenderMath.h"
#include "RenderObject.h"

#include <Windows.h>

namespace Tan
{
	typedef enum RENDER_STATE
	{
		WIREFRAME = 1,
		COLOR     = 2,
		TEXTURE   = 4
	} RENDER_STATE;

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
		inline void	  Clear();

        void	      DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		inline bool   BackfaceCulling(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		inline bool	  Clipping(const Vertex& vertex);
		inline void	  Homogenize(Vertex& vertex);
		
		void	      FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void	      FillTopTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void          FillBottomTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void          FillScanline(const Vertex& vl, const Vertex& vr, int y);
		
		void          DrawLine(coord x1, coord y1, coord x2, coord y2);
		
		inline void   DrawPixel(coord x, coord y, UINT color);

	private:
		RenderObject *mRenderObject;
		RENDER_STATE  mRenderState;

		UINT        **mFrameBuffer;
		float       **mZBuffer;
	
		HDC           mHDC;
		HBITMAP       hBitMap;
		HWND          hWnd;
		HINSTANCE     hInstance;
	};
	
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}




