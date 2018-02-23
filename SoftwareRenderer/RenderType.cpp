#pragma comment(lib, "gdiplus.lib")

#include "RenderType.h"

#include <Windows.h>
#include <gdiplus.h>

namespace Tan
{
	Texture::Texture()
	{
		path        = nullptr;
		width       = 0;
		height      = 0;
		pixelBuffer = nullptr;
		filterMode  = DEFULT_FILTER;
	}

	Texture::Texture(std::wstring path, UINT width, UINT height)
	{
		this->path   = path;
		this->width  = width;
		this->height = height;
		pixelBuffer = new Color*[height];
		for (UINT i = 0; i < height; ++i)
			pixelBuffer[i] = new Color[width]{ Colors::Black };
		Load();
		filterMode = DEFULT_FILTER;
	}

	void Texture::Load()
	{
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

		Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(path.c_str());
		if (!bitmap)
			MessageBox(0, "Load Texture Failed.", 0, 0);
		else
		{
		    height = bitmap->GetHeight();
			width  = bitmap->GetWidth();

			Gdiplus::Color color;

			for (UINT y = 0; y < height; ++y)
				for (UINT x = 0; x < width; ++x)
				{
					bitmap->GetPixel(x, y, &color);

					pixelBuffer[height - 1 - y][x] = Color(
						color.GetRed()   / 255.f,
						color.GetGreen() / 255.f,
						color.GetBlue()  / 255.f
					);

				}
		}
		delete bitmap;
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}

	Color Texture::Sample(float u, float v)
	{
		if (filterMode & POINT)
		{
			int uIndex = static_cast<int>(u * (width - 1) + 0.5f);
			int vIndex = static_cast<int>(v * (height - 1) + 0.5f);
			return pixelBuffer[vIndex][uIndex];
		}
		else if(filterMode & BILINEAR)
		{
			float  uIndex = u * (width - 1);
			float  vIndex = v * (height - 1);
			UINT   x = static_cast<UINT>(uIndex);
			UINT   y = static_cast<UINT>(vIndex);

			if (x + 1 < width && y + 1 < height)
			{
				float  uRatio = uIndex - x;
				float  vRatio = vIndex - y;
				float  uOpposite = 1.0f - uRatio;
				float  vOpposite = 1.0f - vRatio;

				return pixelBuffer[y][x]         * uOpposite  * vOpposite 
					 + pixelBuffer[y][x + 1]     * uOpposite  * vRatio
					 + pixelBuffer[y + 1][x]     * uRatio     * vOpposite
					 + pixelBuffer[y + 1][x + 1] * uRatio     * vRatio;
			}
			else
				return pixelBuffer[y][x];
		}
	}

	void Texture::Delete()
	{
		if (pixelBuffer)
			for (UINT i = 0; i < height; ++i)
				delete[] pixelBuffer[i];
		pixelBuffer = nullptr;
	}

	Material::Material()
	{
		if (TEXTURE_PATH)
			texture = new Texture{ TEXTURE_PATH, TEXTURE_WIDTH, TEXTURE_HEIGHT };
		else
			texture = nullptr;
	}

	void Material::Delete()
	{
		if(texture)
			texture->Delete();
	}

}