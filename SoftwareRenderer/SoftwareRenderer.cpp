#include "SoftwareRenderer.h"

namespace Tan
{
	SoftwareRenderer::SoftwareRenderer()
	{
		hWnd         = nullptr;
		hInstance    = nullptr;
		mHDC         = nullptr;
		hBitMap      = nullptr;

		mFrameBuffer = nullptr;
		mZBuffer     = nullptr;
		mScene       = nullptr;
	}

	bool SoftwareRenderer::Initialize()
	{
		hInstance = GetModuleHandle(NULL);

		// Create a windows class for output.
		WNDCLASSEX wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = (HICON)LoadImage(hInstance, "RenderIcon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = RNDERER_NAME;
		wc.cbSize = sizeof(WNDCLASSEX);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(0, "RegisterClass Failed.", 0, 0);
			return false;
		}

		RECT R = { 0, 0, WND_WIDTH, WND_HEIGHT };
		AdjustWindowRect(&R, GetWindowLong(hWnd, GWL_STYLE), false);

		hWnd = CreateWindowEx
		(
			WS_EX_APPWINDOW,
			RNDERER_NAME,
			RNDERER_NAME,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			WND_WIDTH,
			WND_HEIGHT,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		if (!hWnd)
		{
			MessageBox(0, "CreateWindow Failed.", 0, 0);
			return false;
		}

		// Get a window-related bitmap for rendering.
		HDC hdc = GetDC(hWnd);
		mHDC = CreateCompatibleDC(hdc);
		ReleaseDC(hWnd, hdc);

		BITMAPINFO bmpInfo =
		{
			sizeof(BITMAPINFOHEADER),
			WND_WIDTH,
			-WND_HEIGHT,
			1,
			32,
			BI_RGB,
			WND_WIDTH * WND_HEIGHT * 4,
			0,
			0,
			0,
			0
		};
		LPVOID ptr = nullptr;
		hBitMap = CreateDIBSection(mHDC, &bmpInfo, DIB_RGB_COLORS, &ptr, nullptr, 0);
		if (!hBitMap)
		{
			MessageBox(0, "CreateDIBSection Failed.", 0, 0);
			return false;
		}
		SelectObject(mHDC, hBitMap);

		// Link frame-buffer to the bitmap bit values.
		mFrameBuffer = new UINT*[WND_HEIGHT];
		UINT   *uptr = static_cast<UINT *>(ptr);
		for (int i = 0; i < WND_HEIGHT; ++i)
			mFrameBuffer[i] = uptr + WND_WIDTH * i;
		if (!mFrameBuffer)
		{
			MessageBox(0, "Create FrameBuffer Failed.", 0, 0);
			return false;
		}

		// Allocate memory for z-buffer.
		mZBuffer = new float*[WND_HEIGHT];
		for (int i = 0; i < WND_HEIGHT; ++i)
			mZBuffer[i] = new float[WND_WIDTH] { 0.0f };
		if (!mZBuffer)
		{
			MessageBox(0, "Create ZBuffer Failed.", 0, 0);
			return false;
		}

		// Create a render object(it's a box now).
		mScene = new Scene;
		mScene->Initialize();
		mScene->CreateBox();

		// Show the window.
		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);

		return true;
	}

	void SoftwareRenderer::Shutdown()
	{
		if (mFrameBuffer)
			delete mFrameBuffer;
		mFrameBuffer = nullptr;

		if (mZBuffer)
			for (int i = 0; i < WND_HEIGHT; ++i)
				delete[] mZBuffer[i];
		mZBuffer = nullptr;

		if (mScene)
		{
			mScene->Delete();
			delete mScene;
		}
		mScene = nullptr;

		if (mHDC)
			DeleteDC(mHDC);
		mHDC = nullptr;

		if (hBitMap)
			DeleteObject(hBitMap);
		hBitMap = nullptr;

		DestroyWindow(hWnd);
		hWnd = nullptr;

		UnregisterClass(RNDERER_NAME, hInstance);
		hInstance = nullptr;
	}

	void SoftwareRenderer::Run()
	{
		MSG msg;
		bool done = false;

		ZeroMemory(&msg, sizeof(MSG));
		while (!done)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				Clear();
				Draw();
				Update();
			}
		}
	}

	void SoftwareRenderer::Draw()
	{
		int count = mScene->GetIndicesCount();
		UINT index1, index2, index3;
		for (int i = 0; i < count; i += 3)
		{
			index1 = mScene->GetIndex(i);
			index2 = mScene->GetIndex(i + 1);
			index3 = mScene->GetIndex(i + 2);

			DrawTriangle(mScene->GetVertex(index1), mScene->GetVertex(index2), mScene->GetVertex(index3));
		}
	}

	void SoftwareRenderer::Update()
	{
		mScene->Update();

		HDC hdc = GetDC(hWnd);
		BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, mHDC, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdc);
	}

	void SoftwareRenderer::Clear()
	{
		for (int y = 0; y < WND_HEIGHT; ++y)
			for (int x = 0; x < WND_WIDTH; ++x)
				mFrameBuffer[y][x] = BACKGROUNDCOLOR;

		for (int y = 0; y < WND_HEIGHT; ++y)
			for (int x = 0; x < WND_WIDTH; ++x)
				mZBuffer[y][x] = BACKGROUNDCOLOR;
	}

	void SoftwareRenderer::Lighting(Vertex& vertex)
	{
		// If the render object has a non-uniform scaling, world matrix should be transpose then inverse.
		Matrix world = mScene->GetWorldMatrix();
		vertex.normal = RenderMath::Vector3MulMatrix(vertex.normal, world);

		// Cfinal = Kambi * Mamb * Iamb + Kdif * Mdif * Idif + Kspec * Mspec * Ispec.
		Color finalColor;

		float Iamb = ENVIRONMENT_AMB;
		finalColor = (mScene->GetLightAmbient() * mScene->GetMatAmbient() * Iamb);

		Vector3 N = vertex.normal.Normalize();
		Vector3 L = mScene->GetLightPos() - vertex.pos.ToVector3();
		float Idif = RenderMath::Clamp(N.Dot(L), 0.0f, 1.0f);
		finalColor += (mScene->GetLightDiffuse() * mScene->GetMatDiffuse() * Idif);

		Vector3 V = mScene->GetCameraPos() - vertex.pos.ToVector3();
		float Ispec = 0.0f;
		if (N.Dot(L) > 0.0f)
		{
			Vector3 H = (L + V).Normalize();
			Ispec = pow(N.Dot(H), mScene->GetMatShininess());
		}
		finalColor += (mScene->GetLightSpecular() * mScene->GetMatSpecular() * Ispec);

	    vertex.litColor = finalColor;
	}

	bool SoftwareRenderer::BackfaceCulling(const Vertex& v1, const Vertex& v2, const Vertex& v3)
	{
		if (mScene->renderState & WIREFRAME)
		{
			return false;
		}
		else
		{
			Vector3 e0 = (v2.pos - v1.pos).ToVector3();
			Vector3 e1 = (v3.pos - v1.pos).ToVector3();
			Vector3 normal = e0.Cross(e1);
			Vector3 view = (v1.pos - Vector3(0.0f, 0.0f, 0.0f)).ToVector3(); // Camera point is (0,0,0) in the view space.
			if (normal.Dot(view) > 0)
				return true;
			return false;
		}
	}

	bool SoftwareRenderer::Clipping(const Vertex& vertex)
	{
		float w = vertex.pos.w;
		if (vertex.pos.z < 0.0f || vertex.pos.z > w) return true;
		if (vertex.pos.x <   -w || vertex.pos.x > w) return true;
		if (vertex.pos.y <   -w || vertex.pos.y > w) return true;
		return false;
	}

	void SoftwareRenderer::Homogenize(Vertex& vertex)
	{
		float rhw = 1.0f / vertex.pos.w;
		vertex.rhw = rhw; // "reciprocally homogeneous w" = 1 / z.
		vertex.pos.x = 0.5f * WND_WIDTH * (vertex.pos.x * rhw + 1.0f);
		vertex.pos.y = 0.5f * WND_HEIGHT * (1.0f - vertex.pos.y * rhw);
		vertex.pos.z = vertex.pos.z * rhw;
		vertex.pos.w = 1.0f;

		vertex.color *= rhw;
		vertex.uv *= rhw;
		vertex.litColor *= rhw;
	}

	void SoftwareRenderer::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
	{
		Vertex vert[3]{ v1, v2, v3 };

		/*--Geometry stage--*/

		for (auto &v : vert)
		{
			// To the world space.
			v.pos = RenderMath::Vector4MulMatrix(v.pos, mScene->GetWorldMatrix());
			// Lighting in the world space.
			if(mScene->lightingState & ON) Lighting(v);
			// To the view space.
			v.pos = RenderMath::Vector4MulMatrix(v.pos, mScene->view);
		}

		// Backface culling in the view space.
		if (BackfaceCulling(vert[0], vert[1], vert[2])) return;

		for (auto &v : vert)
		{
			// To the homogeneous clip space.
			v.pos = RenderMath::Vector4MulMatrix(v.pos, mScene->projection);
			// Clipping in the canonical view volume.
			if (Clipping(v)) return;
			// Perspective dividing and mapping to the screen space.
			Homogenize(v);
		}

		/*--Rasterization stage--*/
		if (mScene->renderState & WIREFRAME)
		{
			DrawLine(vert[0].pos.x, vert[0].pos.y, vert[1].pos.x, vert[1].pos.y);
			DrawLine(vert[1].pos.x, vert[1].pos.y, vert[2].pos.x, vert[2].pos.y);
			DrawLine(vert[2].pos.x, vert[2].pos.y, vert[0].pos.x, vert[0].pos.y);
		}
		else // if(COLOR || TEXTURE)
		{
			FillTriangle(vert[0], vert[1], vert[2]);
		}
	}

	void SoftwareRenderer::FillTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
	{
		if (v1.pos.y == v2.pos.y)
		{
			if (v1.pos.y < v3.pos.y)
				FillTopTriangle(v1, v2, v3);
			else
				FillBottomTriangle(v1, v2, v3);
		}
		else if (v2.pos.y == v3.pos.y)
		{
			if (v2.pos.y < v1.pos.y)
				FillTopTriangle(v2, v3, v1);
			else
				FillBottomTriangle(v2, v3, v1);
		}
		else if (v3.pos.y == v1.pos.y)
		{
			if (v3.pos.y < v2.pos.y)
				FillTopTriangle(v3, v1, v2);
			else
				FillBottomTriangle(v3, v1, v2);
		}
		else // Divide the triangle.
		{
			const Vertex *top = nullptr, *bottom = nullptr, *middle = nullptr;
			if (v1.pos.y > v2.pos.y && v2.pos.y > v3.pos.y)
			{
				top = &v3;
				middle = &v2;
				bottom = &v1;
			}
			else if (v3.pos.y > v2.pos.y && v2.pos.y > v1.pos.y)
			{
				top = &v1;
				middle = &v2;
				bottom = &v3;
			}
			else if (v2.pos.y > v1.pos.y && v1.pos.y > v3.pos.y)
			{
				top = &v3;
				middle = &v1;
				bottom = &v2;
			}
			else if (v3.pos.y > v1.pos.y && v1.pos.y > v2.pos.y)
			{
				top = &v2;
				middle = &v1;
				bottom = &v3;
			}
			else if (v1.pos.y > v3.pos.y && v3.pos.y > v2.pos.y)
			{
				top = &v2;
				middle = &v3;
				bottom = &v1;
			}
			else if (v2.pos.y > v3.pos.y && v3.pos.y > v1.pos.y)
			{
				top = &v1;
				middle = &v3;
				bottom = &v2;
			}
			else
			{
				return; // Three point a line.
			}

			// x = (y - y1) * (x2 - x1) / (y2 - y1) + x1
			float midX = (middle->pos.y - top->pos.y) * (bottom->pos.x - top->pos.x) / (bottom->pos.y - top->pos.y) + top->pos.x;
			float t = (middle->pos.y - top->pos.y) / (bottom->pos.y - top->pos.y);

			Vertex mid = RenderMath::Lerp(*top, *bottom, t);
			mid.pos.x = midX;
			mid.pos.y = middle->pos.y;

			FillBottomTriangle(mid, *middle, *top);
			FillTopTriangle(mid, *middle, *bottom);

			top = nullptr;
			bottom = nullptr;
			middle = nullptr;
		}
	}

	void SoftwareRenderer::FillTopTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
	{
		// v3 -> bottom vertex.
		for (float y = v1.pos.y; y <= v3.pos.y; y += 0.5f)
		{
			int yRound = static_cast<int>(y + 0.5f);
			if (0 <= yRound && yRound < WND_HEIGHT)
			{
				// x = (y - y1) * (x2 - x1) / (y2 - y1) + x1
				float xl = (y - v1.pos.y) * (v3.pos.x - v1.pos.x) / (v3.pos.y - v1.pos.y) + v1.pos.x;
				float xr = (y - v2.pos.y) * (v3.pos.x - v2.pos.x) / (v3.pos.y - v2.pos.y) + v2.pos.x;

				float dy = y - v1.pos.y;
				float t = dy / (v3.pos.y - v1.pos.y);

				Vertex vl = RenderMath::Lerp(v1, v3, t);
				vl.pos.x = xl;
				vl.pos.y = y;

				Vertex vr = RenderMath::Lerp(v2, v3, t);
				vr.pos.x = xr;
				vr.pos.y = y;

				if (xl < xr)
					FillScanline(vl, vr, yRound);
				else
					FillScanline(vr, vl, yRound);
			}
		}

	}

	void SoftwareRenderer::FillBottomTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
	{
		// v3 -> top vertex.
		for (float y = v3.pos.y; y <= v1.pos.y; y += 0.5f)
		{
			int yRound = static_cast<int>(y + 0.5f);
			if (0 <= yRound && yRound < WND_HEIGHT)
			{
				float xl = (y - v3.pos.y) * (v1.pos.x - v3.pos.x) / (v1.pos.y - v3.pos.y) + v3.pos.x;
				float xr = (y - v3.pos.y) * (v2.pos.x - v3.pos.x) / (v2.pos.y - v3.pos.y) + v3.pos.x;

				float dy = y - v3.pos.y;
				float t = dy / (v2.pos.y - v3.pos.y);

				Vertex vl = RenderMath::Lerp(v3, v1, t);
				vl.pos.x = xl;
				vl.pos.y = y;

				Vertex vr = RenderMath::Lerp(v3, v2, t);
				vr.pos.x = xr;
				vr.pos.y = y;

				if (xl < xr)
					FillScanline(vl, vr, yRound);
				else
					FillScanline(vr, vl, yRound);
			}
		}
	}

	void SoftwareRenderer::FillScanline(const Vertex& vl, const Vertex& vr, int yRound)
	{
		float dx = vr.pos.x - vl.pos.x;
		float step = 1.0f;
		if (!(dx - 0.0f < FLT_MIN)) // dx != 0.0f.
			step = 1.0f / dx;

		for (float x = vl.pos.x; x <= vr.pos.x; x += 0.5f)
		{
			int xRound = static_cast<int>(x + 0.5f);
			if (0 <= xRound && xRound < WND_WIDTH)
			{
				float lerpFactor = 0.0f;
				if (!(dx - 0.0f < FLT_MIN))
					lerpFactor = (x - vl.pos.x) / dx;

				float reciprocalZ = RenderMath::Lerp(vl.rhw, vr.rhw, lerpFactor);
				if (mZBuffer[yRound][xRound] < reciprocalZ || mZBuffer[yRound][xRound] - reciprocalZ < FLT_MIN) // Depth Test.(must be mZBuffer - rZ)
				{
					// Update z-buffer(actually, it contains 1/z).
					mZBuffer[yRound][xRound] = reciprocalZ;

					float w = 1.0f / reciprocalZ;
					Color finalColor;

					finalColor = RenderMath::Lerp(vl.color, vr.color, lerpFactor) * w;
					
					if (mScene->lightingState & ON)
						finalColor *= RenderMath::Lerp(vl.litColor, vr.litColor, lerpFactor) * w;

					mFrameBuffer[yRound][xRound] = finalColor.ToUINT();
				}
			}
		}
	}

	void SoftwareRenderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		// The bresenham / midway line-drawing algorithm.
		int dx = static_cast<int>(x2 - x1);
		int dy = static_cast<int>(y2 - y1);
		int stepx = 1;
		int stepy = 1;

		if (dx >= 0)
		{
			stepx = 1;
		}
		else
		{
			stepx = -1;
			dx = abs(dx);
		}

		if (dy >= 0)
		{
			stepy = 1;
		}
		else
		{
			stepy = -1;
			dy = abs(dy);
		}

		int dx2 = 2 * dx;
		int dy2 = 2 * dy;
		if (dx > dy)
		{
			int mid = dy2 - dx;
			for (int i = 0; i <= dx; ++i)
			{
				DrawPixel(x1, y1, FOREGROUNDCOLOR);
				if (mid >= 0)
				{
					mid -= dx2;
					y1 += stepy;
				}
				mid += dy2;
				x1 += stepx;
			}
		}
		else
		{
			int mid = dx2 - dy;
			for (int i = 0; i <= dy; ++i)
			{
				DrawPixel(x1, y1, FOREGROUNDCOLOR);
				if (mid >= 0)
				{
					mid -= dy2;
					x1 += stepx;
				}
				mid += dx2;
				y1 += stepy;
			}
		}
	}

	inline void SoftwareRenderer::DrawPixel(float x, float y, UINT color)
	{
		if (x > 0 && x < WND_WIDTH && y > 0 && y < WND_HEIGHT)
			mFrameBuffer[static_cast<int>(y)][static_cast<int>(x)] = color;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		switch (umessage)
		{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}


