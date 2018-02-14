#pragma once

#include "Config.h"
#include "Vector.h"
#include "Color.h"

namespace Tan
{
	typedef enum RENDER_STATE
	{
		WIREFRAME = 1,
		COLOR     = 2,
		TEXTURE   = 4
	} RENDER_STATE;

	typedef enum LIGHTING_STATE
	{
		ON,
		OFF
	} LIGHTING_STATE;

	class Vertex
	{
	public:
		Vector4 pos;
		Color   color;
		Vector2 uv;
		Vector3 normal;

		Color   litColor;  // lighting color.
		float   rhw;    // 1 / z.

	public:
		Vertex() = default;
		Vertex(const Vector4& pos, const Color& color, const Vector2 uv, const Vector3& normal, const Color& litColor, float rhw = 0.0f) :
			pos(pos), color(color), uv(uv), normal(normal), litColor(litColor), rhw(rhw) {}
		Vertex(const Vertex& rhs) : pos(rhs.pos), color(rhs.color), uv(rhs.uv), normal(rhs.normal), litColor(rhs.litColor), rhw(rhs.rhw) {}
		~Vertex() = default;
	};

	class Camera
	{
	public:
		Vector3 pos  = { EYE };
		Vector3 up   = { UP };
		Vector3 at   = { AT };

		float   near = { NEAR };
		float   far  = { FAR };

	public:
		Camera() = default;
		Camera(const Camera& rhs) : pos(rhs.pos), up(rhs.up), at(rhs.at), near(rhs.near), far(rhs.far) {}
		~Camera() = default;
	};

	class Light
	{
	public:
		Vector3 pos   = { LIGHT_POS };

		Color   Kamb  = { LIGHT_AMB };
		Color   Kdif  = { LIGHT_DIF };
		Color   Kspec = { LIGHT_SPEC };

	public:
		Light() = default;
		Light(const Light& rhs) :pos(rhs.pos), Kamb(rhs.Kamb), Kdif(rhs.Kdif), Kspec(rhs.Kspec) {}
		~Light() = default;
	};

	class Material
	{
	public:
		Color   Mamb      = { DEFULT_AMB };
		Color   Mdif      = { DEFULT_DIF };
		Color   Mspec     = { DEFULT_SPEC };

		float   shininess = { DEFULT_SHINE };

	public:
		Material() = default;
		Material(const Material& rhs) : Mamb(rhs.Mamb), Mdif(rhs.Mdif), Mspec(rhs.Mspec), shininess(rhs.shininess) {}
		~Material() = default;
	};
}
