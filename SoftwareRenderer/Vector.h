#pragma once

#include "Config.h"

#include <cfloat>
#include <algorithm>

namespace Tan
{
	class Vector2
	{
	public:
		union
		{
			struct { float x, y; };
			float v[2];
		};

	public:
		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(float x, float y) : x(x), y(y) {}
		Vector2(const Vector2& rhs) : x(rhs.x), y(rhs.y) {}
		~Vector2() = default;

	public:
		Vector2  operator+  (const Vector2& rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}
		Vector2  operator-  (const Vector2& rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}
		Vector2  operator*  (float k) const
		{
			return Vector2(k * x, k * y);
		}
		void	 operator+= (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
		}
		void	 operator-= (const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
		}
		void	 operator*= (float k)
		{
			x *= k;
			y *= k;
		}
		void	 operator=  (const Vector2& rhs)
		{
			if (this == &rhs) return;
			x = rhs.x;
			y = rhs.y;
		}
		bool	 operator== (const Vector2& rhs)
		{
			return (abs(x - rhs.x) < FLT_MIN) && (abs(y - rhs.y) < FLT_MIN);
		}

	public:
		float    Length() const
		{
			return sqrt(x * x + y * y);
		}
		float    LengthSquared() const
		{
			return x * x + y * y;
		}
		float    Dot(const Vector2& rhs)
		{
			return x * rhs.x + y * rhs.y;
		}
		Vector2& Normalize()
		{
			if (LengthSquared() - 0.0f < FLT_MIN) 
				return *this;
			float rec = 1.0f / Length();
			x *= rec;
			y *= rec;
			return *this;
		}
		void     SetZero()
		{
			x = y = 0.0f;
		}
	};

	class Vector3
	{
	public:
		union
		{
			struct { float x, y, z; };
			float v[3];
		};

	public:
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		Vector3(const Vector3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
		~Vector3() = default;

	public:
		Vector3  operator+  (const Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}
		Vector3  operator-  (const Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}
		Vector3  operator*  (float k) const
		{
			return Vector3(k * x, k * y, k * z);
		}
		void	 operator+= (const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
		}
		void	 operator-= (const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
		}
		void	 operator*= (float k)
		{
			x *= k;
			y *= k;
			z *= k;
		}
		void	 operator=  (const Vector3& rhs)
		{
			if (this == &rhs) return;
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
		bool	 operator== (const Vector3& rhs)
		{
			return ((abs(x - rhs.x) < FLT_MIN) && (abs(y - rhs.y) < FLT_MIN) && (abs(z - rhs.z) < FLT_MIN));
		}

	public:
		float    Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}
		float    LengthSquared() const
		{
			return x * x + y * y + z * z;
		}
		float    Dot(const Vector3& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}
		Vector3  Cross(const Vector3& rhs) const
		{
			return Vector3
			(
				y * rhs.z - z * rhs.y, 
				z * rhs.x - x * rhs.z, 
				x * rhs.y - y * rhs.x
			);
		}
		Vector3& Normalize()
		{
			if (LengthSquared() - 0.0f < FLT_MIN) 
				return *this;
			float rec = 1.0f / Length();
			x *= rec;
			y *= rec;
			z *= rec;
			return *this;
		}
		void	 SetZero()
		{
			x = y = z = 0.0f;
		}
	};

	class Vector4
	{
	public:
		union
		{
			struct { float x, y, z, w; };
			float v[4];
		};

	public:
		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4(float x, float y, float z, float w = 0.0f) : x(x), y(y), z(z), w(w) {}
		Vector4(const Vector3& rhs, float w = 0.0f) : x(rhs.x), y(rhs.y), z(rhs.z), w(w) {}
		Vector4(const Vector4& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
		~Vector4() = default;

	public:
		Vector4  operator+  (const Vector4& rhs) const
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w);
		}
		Vector4  operator-  (const Vector4& rhs) const
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w);
		}
		Vector4  operator*  (float k) const
		{
			return Vector4(k * x, k * y, k * z, w);
		}
		void     operator+= (const Vector4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
		}
		void     operator-= (const Vector4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
		}
		void     operator*= (float k)
		{
			x *= k;
			y *= k;
			z *= k;
		}
		void     operator=  (const Vector4& rhs)
		{
			if (this == &rhs) return;
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
		}
		bool     operator== (const Vector4& rhs)
		{
			return (abs(x - rhs.x) < FLT_MIN) && (abs(y - rhs.y) < FLT_MIN)
				&& (abs(z - rhs.z) < FLT_MIN) && (abs(w - rhs.w) < FLT_MIN);
		}

	public:
		float    Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}
		float    LengthSquared() const
		{
			return x * x + y * y + z * z;
		}
		Vector4& Normalize()
		{
			if (LengthSquared() - 0.0f < FLT_MIN) 
				return *this;
			float rec = 1.0f / Length();
			x *= rec;
			y *= rec;
			z *= rec;
			return *this;
		}
		void     SetZero()
		{
			x = y = z = w = 0.0f;
		}
		float    Dot(const Vector4& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
		}
		Vector4  Cross(const Vector4& rhs) const
		{
			return Vector4
			(
				y * rhs.z - z * rhs.y,
				z * rhs.x - x * rhs.z,
				x * rhs.y - y * rhs.x,
				w
			);
		}
		Vector3  ToVector3() const
		{
			return Vector3(x, y, z);
		}
	};
}