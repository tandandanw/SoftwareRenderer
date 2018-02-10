#pragma once

#include "Config.h"

#include <cfloat>

namespace Tan
{
	class Matrix
	{
	public:
		union 
		{
			struct
			{
				float _11, _12, _13, _14,
					  _21, _22, _23, _24,
					  _31, _32, _33, _34,
					  _41, _42, _43, _44;
			};
			float m[4][4];
		};

	public:
		Matrix
		(
			float _11 = 0.0f, float _12 = 0.0f, float _13 = 0.0f, float _14 = 0.0f,
			float _21 = 0.0f, float _22 = 0.0f, float _23 = 0.0f, float _24 = 0.0f,
			float _31 = 0.0f, float _32 = 0.0f, float _33 = 0.0f, float _34 = 0.0f,
			float _41 = 0.0f, float _42 = 0.0f, float _43 = 0.0f, float _44 = 0.0f
		) : _11(_11), _12(_12), _13(_13), _14(_14),
			_21(_21), _22(_22), _23(_23), _24(_14),
			_31(_31), _32(_32), _33(_33), _34(_34),
			_41(_41), _42(_42), _43(_43), _44(_44) {}
		Matrix(const Matrix& rhs)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m[i][j] = rhs.m[i][j];
		}
		~Matrix() = default;

	public:
		Matrix  operator+   (const Matrix& rhs) const
		{
			Matrix ret;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.m[i][j] = m[i][j] + rhs.m[i][j];
			return ret;
		}
		Matrix  operator-   (const Matrix& rhs) const
		{
			Matrix ret;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.m[i][j] = m[i][j] - rhs.m[i][j];
			return ret;
		}
		Matrix  operator*   (float k) const
		{
			Matrix ret;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.m[i][j] = k * m[i][j];
			return ret;
		}
		void    operator+=  (const Matrix& rhs)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m[i][j] += rhs.m[i][j];
		}
		void    operator-=  (const Matrix& rhs)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m[i][j] -= rhs.m[i][j];
		}
		void    operator*=  (float k)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m[i][j] *= k;
		}
		void    operator=   (const Matrix& rhs)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m[i][j] = rhs.m[i][j];
		}
		bool    operator==  (const Matrix& rhs)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (!(abs(m[i][j] - rhs.m[i][j]) < FLT_MIN))
						return false;
			return true;
		}

	public:
		Matrix  GetInverse() const
		{

		}
		Matrix  GetTranspose() const
		{
			Matrix ret;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.m[i][j] = m[j][i];
			return ret;
		}
		void    Transpose()
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = i + 1; j < 4; j++)
				{
					float temp = m[i][j];
					m[i][j] = m[j][i];
					m[j][i] = temp;
				}
			}
		}
		void    SetZero()
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					m[i][j] = 0.0f;
		}
		void    SetIdentity()
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					if (i == j) m[i][j] = 1.0f;
					else		m[i][j] = 0.0f;
				}
		}
	};
}
