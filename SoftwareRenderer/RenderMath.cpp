#include "RenderMath.h"

namespace Tan
{
	Vector4 RenderMath::Vector4MulMatrix(const Vector4& vector, const Matrix& matrix)
	{
		Vector4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.v[i] += (vector.v[j] * matrix.m[j][i]);
		return ret;
	}

	Matrix  RenderMath::MatrixMulMatrix(const Matrix& lhs, const Matrix& rhs)
	{
		Matrix ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					ret.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
		return ret;
	}

	Matrix  RenderMath::GetTranslateMatrix(float x, float y, float z)
	{
		Matrix ret;
		ret.SetIdentity();
		ret.m[3][0] = x;
		ret.m[3][1] = y;
		ret.m[3][2] = z;
		return ret;
	}

	Matrix  RenderMath::GetScaleMatrix(float x, float y, float z)
	{
		Matrix ret;
		ret.SetIdentity();
		ret.m[0][0] = x;
		ret.m[1][1] = y;
		ret.m[2][2] = z;
		return ret;
	}

	Matrix  RenderMath::GetRotateMatrix(float x, float y, float z, float theta)
	{
		Matrix ret;
		float qsin = static_cast<float>(sin(theta * 0.5f));
		float qcos = static_cast<float>(cos(theta * 0.5f));
		float w = qcos;

		Vector4 rotateAxis = { x, y, z, 1.0f };
		rotateAxis.Normalize();
		x = rotateAxis.x * qsin;
		y = rotateAxis.y * qsin;
		z = rotateAxis.z * qsin;

		ret.m[0][0] = 1 - 2 * y * y - 2 * z * z;
		ret.m[1][0] = 2 * x * y - 2 * w * z;
		ret.m[2][0] = 2 * x * z + 2 * w * y;
		ret.m[0][1] = 2 * x * y + 2 * w * z;
		ret.m[1][1] = 1 - 2 * x * x - 2 * z * z;
		ret.m[2][1] = 2 * y * z - 2 * w * x;
		ret.m[0][2] = 2 * x * z - 2 * w * y;
		ret.m[1][2] = 2 * y * z + 2 * w * x;
		ret.m[2][2] = 1 - 2 * x * x - 2 * y * y;
		ret.m[0][3] = 0.0f; 
		ret.m[1][3] = 0.0f; 
		ret.m[2][3] = 0.0f;
		ret.m[3][0] = 0.0f; 
		ret.m[3][1] = 0.0f; 
		ret.m[3][2] = 0.0f;
		ret.m[3][3] = 1.0f;
		return ret;
	}

	Matrix  RenderMath::GetViewMatrix(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Vector3 zAxis = at - eye;
		zAxis.Normalize();
		Vector3 xAxis = up.Cross(zAxis);
		xAxis.Normalize();
		Vector3 yAxis = zAxis.Cross(xAxis);

		Matrix ret;
		ret.m[0][0] = xAxis.x;
		ret.m[1][0] = xAxis.y;
		ret.m[2][0] = xAxis.z;
		ret.m[3][0] = -xAxis.Dot(eye);

		ret.m[0][1] = yAxis.x;
		ret.m[1][1] = yAxis.y;
		ret.m[2][1] = yAxis.z;
		ret.m[3][1] = -yAxis.Dot(eye);

		ret.m[0][2] = zAxis.x;
		ret.m[1][2] = zAxis.y;
		ret.m[2][2] = zAxis.z;
		ret.m[3][2] = -zAxis.Dot(eye);

		ret.m[0][3] = 0.0f;
		ret.m[1][3] = 0.0f;
		ret.m[2][3] = 0.0f;
		ret.m[3][3] = 1.0f;
		return ret;
	}

	Matrix  RenderMath::GetPerspectiveMatrix(float fovy, float aspect, float zn, float zf)
	{
		Matrix ret;
		ret.SetZero();
		float fax = 1.0f / static_cast<float>(tan(fovy * 0.5f));
		ret.m[0][0] = static_cast<float>(fax / aspect);
		ret.m[1][1] = static_cast<float>(fax);
		ret.m[2][2] = zf / (zf - zn);
		ret.m[3][2] = -zn * zf / (zf - zn);
		ret.m[2][3] = 1.0f;
		return ret;
	}

	UINT    RenderMath::ColorToUINT(float r, float g, float b)
	{
		int R = static_cast<int>(r * 255.0f);
		int G = static_cast<int>(g * 255.0f);
		int B = static_cast<int>(b * 255.0f);
		return (R << 16) | (G << 8) | (B);
	}

	inline float RenderMath::Clamp(float value, float min, float max)
	{
		if (value < min) 
			return min;
		else if (max < value) 
			return max;
		else
			return value;
	}

	inline float  RenderMath::Lerp(float x1, float x2, float t)
	{
		if (t < 0.0f) 
			return x1;
		else if (1.0f < t) 
			return x2;
		else 
			return x1 + (x2 - x1) * t;
	}

	Color   RenderMath::Lerp(const Color& c1, const Color& c2, float t)
	{
		return Color
		{
			Lerp(c1.r, c2.r, t),
			Lerp(c1.g, c2.g, t),
			Lerp(c1.b, c2.b, t)
		};
	}

	Vector2 RenderMath::Lerp(const Vector2& v1, const Vector2& v2, float t)
	{
		return Vector2
		{
			Lerp(v1.x, v2.x, t),
			Lerp(v1.y, v2.y, t)
		};
	}

	Vector3 RenderMath::Lerp(const Vector3& v1, const Vector3& v2, float t)
	{
		return Vector3
		{
			Lerp(v1.x, v2.x, t),
			Lerp(v1.y, v2.y, t),
			Lerp(v1.z, v2.z, t)
		};
	}

	Vector4 RenderMath::Lerp(const Vector4& v1, const Vector4& v2, float t)
	{
		return Vector4
		{
			Lerp(v1.x, v2.x, t),
			Lerp(v1.y, v2.y, t),
			Lerp(v1.z, v2.z, t)
		};
	}

	Vertex  RenderMath::Lerp(const Vertex& v1, const Vertex& v2, float t)
	{
		return Vertex
		{
			Lerp(v1.pos,    v2.pos,    t),
			Lerp(v1.color,  v2.color,  t),
			Lerp(v1.uv,	    v2.uv,     t),
			Lerp(v1.normal, v2.normal, t),
			Lerp(v1.light,  v2.light,  t),
			Lerp(v1.rhw,    v2.rhw,    t)
		};
	}

}