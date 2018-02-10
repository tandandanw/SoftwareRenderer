#pragma once

#include "Config.h"
#include "Vector.h"
#include "Color.h"

namespace Tan
{
	typedef enum RENDER_STATE
	{
		WIREFRAME = 1,
		COLOR = 2,
		TEXTURE = 4
	} RENDER_STATE;

	class Vertex
	{
	public:
		Vector4 pos;
		Color   color;
		Vector2 uv;
		Vector3 normal;

		Color   light;  // lighting color.
		float   rhw;    // 1 / z.

	public:
		Vertex() = default;
		Vertex(const Vector4& pos, const Color& color, const Vector2 uv, const Vector3& normal, const Color& light, float rhw = 0.0f) :
			pos(pos), color(color), uv(uv), normal(normal), light(light), rhw(rhw) {}
		Vertex(const Vertex& rhs) : pos(rhs.pos), color(rhs.color), uv(rhs.uv), normal(rhs.normal), light(rhs.light), rhw(rhs.rhw) {}
		~Vertex() = default;
	};

	class Camera
	{
	public:
		Vector3 pos  = { EYE  };
		Vector3 up   = { UP   };
		Vector3 at   = { AT   };

		float   near = { NEAR };
		float   far  = { FAR  };

	public:
		Camera() = default;
		Camera(const Camera& rhs) : pos(rhs.pos), up(rhs.up), at(rhs.at), near(rhs.near), far(rhs.far) {}
		~Camera() = default;
	};

	class Light
	{
	public:
		Vector3 pos      = { LIGHT_POS  };

		float   ambient  = { LIGHT_AMB  };
		float   diffuse  = { LIGHT_DIF  };
		float   specular = { LIGHT_SPEC };

	public:
		Light() = default;
		Light(const Light& rhs) :pos(rhs.pos), ambient(rhs.ambient), diffuse(rhs.diffuse), specular(rhs.specular) {}
		~Light() = default;
	};

	class Material
	{
	public:
		float ambient =   { DEFULT_AMB   };
		float diffuse =   { DEFULT_DIF   };
		float specular =  { DEFULT_SPEC  };
		float shininess = { DEFULT_SHINE };

	public :
		Material() = default;
		Material(const Material& rhs) : ambient(rhs.ambient), diffuse(rhs.diffuse), specular(rhs.specular), shininess(rhs.shininess) {}
		~Material() = default;
	};
}
