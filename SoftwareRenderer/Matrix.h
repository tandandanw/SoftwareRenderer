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
				coord _11, _12, _13, _14,
					  _21, _22, _23, _24,
					  _31, _32, _33, _34,
					  _41, _42, _43, _44;
			};
			coord m[4][4];
		};

	public:
		Matrix
		(
			coord _11 = 0.0f, coord _12 = 0.0f, coord _13 = 0.0f, coord _14 = 0.0f,
			coord _21 = 0.0f, coord _22 = 0.0f, coord _23 = 0.0f, coord _24 = 0.0f,
			coord _31 = 0.0f, coord _32 = 0.0f, coord _33 = 0.0f, coord _34 = 0.0f,
			coord _41 = 0.0f, coord _42 = 0.0f, coord _43 = 0.0f, coord _44 = 0.0f
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
					coord temp = m[i][j];
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
