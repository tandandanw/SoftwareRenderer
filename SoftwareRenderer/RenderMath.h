#pragma once

#include "Config.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"
#include "RenderType.h"

namespace Tan
{
	class RenderMath
	{
	public:
		RenderMath() = default;
		RenderMath(const RenderMath& rhs) = delete;
		~RenderMath() = default;

	public:
		static Vector3      Vector3MulMatrix(const Vector3& vector, const Matrix& matrix);
		static Vector4      Vector4MulMatrix(const Vector4& vector, const Matrix& matrix);
		static Matrix       MatrixMulMatrix(const Matrix& lhs, const Matrix& rhs);
		static Matrix       GetTranslateMatrix(float x, float y, float z);
		static Matrix       GetScaleMatrix(float x, float y, float z);
		static Matrix       GetRotateMatrix(float x, float y, float z, float theta);
		static Matrix       GetViewMatrix(const Vector3& eye, const Vector3& at, const Vector3& up);
		static Matrix	    GetPerspectiveMatrix(float fovy, float aspect, float zn, float zf);

		static Vertex       Lerp(const Vertex& v1, const Vertex& v2, float t);
		static Color        Lerp(const Color& c1, const Color& c2, float t);
		static Vector2      Lerp(const Vector2& v1, const Vector2& v2, float t);
		static Vector3      Lerp(const Vector3& v1, const Vector3& v2, float t);
		static Vector4      Lerp(const Vector4& v1, const Vector4& v2, float t);
		static float	    Lerp(float x1, float x2, float t)
		{
			if (t < 0.0f)
				return x1;
			else if (1.0f < t)
				return x2;
			else
				return x1 + (x2 - x1) * t;
		}

		static float        Clamp(float value, float min, float max)
		{
			if (value < min)
				return min;
			else if (max < value)
				return max;
			else
				return value;
		}
		static UINT         ColorToUINT(float r, float g, float b);
	};
}