#pragma once

#include "Config.h"
#include "Vector.h"
#include "Color.h"

namespace Tan
{
	class Vertex
	{
	public:
		Vector4 pos;
		Color   color;

		float   rhw; // 1/z.

	public:
		Vertex() = default;
		Vertex(const Vector4& pos, const Color& color, float rhw = 0.0f) : pos(pos), color(color), rhw(rhw) {}
		Vertex(const Vertex& rhs) : pos(rhs.pos), color(rhs.color), rhw(rhs.rhw) {}
		~Vertex() = default;
	};
}
