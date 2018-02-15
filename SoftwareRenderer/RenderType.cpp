#include "RenderType.h"

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
		for (int i = 0; i < height; ++i)
			pixelBuffer[i] = new Color[width]{ Colors::Black };
		Load();
	}

	bool Texture::Load()
	{
		return true;
	}

	Color Texture::Sample(float u, float v)
	{
		int uIndex = static_cast<int>(u * width + 0.5f);
		int vIndex = static_cast<int>(v * height + 0.5f);

		if (filterMode & POINT)
		{
			return pixelBuffer[vIndex][uIndex];
		}
		else if(filterMode & BILINEAR)
		{
		}
	}

	void Texture::Delete()
	{
		if (pixelBuffer)
			for (int i = 0; i < height; ++i)
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