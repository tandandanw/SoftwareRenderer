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
		       static Vector4 Vector4MulMatrix(const Vector4& vector, const Matrix& matrix);
			   static Matrix  MatrixMulMatrix(const Matrix& lhs, const Matrix& rhs);
			   static Matrix  GetTranslateMatrix(float x, float y, float z);
			   static Matrix  GetScaleMatrix(float x, float y, float z);
			   static Matrix  GetRotateMatrix(float x, float y, float z, float theta);
			   static Matrix  GetViewMatrix(const Vector3& eye, const Vector3& at, const Vector3& up);
			   static Matrix  GetPerspectiveMatrix(float fovy, float aspect, float zn, float zf);

			   static UINT    ColorToUINT(float r, float g, float b);

		inline static float   Lerp(float x1, float x2, float t);
		inline static Color   Lerp(const Color& c1, const Color& c2, float t);
		inline static Vector4 Lerp(const Vector4& v1, const Vector4& v2, float t);
			   static Vertex  Lerp(const Vertex& v1, const Vertex& v2, float t);
	};
}