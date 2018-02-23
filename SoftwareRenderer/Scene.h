#pragma once

#include "Config.h"
#include "RenderObject.h"

namespace Tan
{
	class Scene
	{
	public:
		RenderObject * renderObject; // It can be a list of render objects.
		RENDER_STATE   renderState;

		LIGHTING_STATE lightingState;
		Light		  *lightSource;

		Camera		  *camera;
		Matrix		   view;
		Matrix		   projection;

	public:
		Scene();
		Scene(const Scene& rhs) = delete;
		~Scene() = default;

	public:
		void     Initialize();
		void     Delete();
		void     Update();

		void     CreateBox();

		Vector3  GetLightPos() const
		{
			return lightSource->pos;
		}
		Color    GetLightAmbient() const
		{
			return lightSource->Kamb;
		}
		Color    GetLightDiffuse() const
		{
			return lightSource->Kdif;
		}
		Color    GetLightSpecular() const
		{
			return lightSource->Kspec;
		}
		Vector3  GetCameraPos() const
		{
			return camera->pos;
		}

		// If there are render objects, the following methods can be Get [attribute] (OBJ_INDEX objectIndex, ...[other paras]).
		UINT     GetIndex(UINT i) const
		{
			return renderObject->indices[i];
		}
		Vertex   GetVertex(UINT i) const
		{
			return renderObject->vertices[i];
		}
		UINT     GetIndicesCount() const
		{
			return renderObject->indicesCount;
		};

		Matrix   GetWorldMatrix() const
		{
			return renderObject->world;
		}
		Color    GetMatAmbient() const
		{
			return renderObject->map->Mamb;
		}
		Color    GetMatDiffuse() const
		{
			return renderObject->map->Mdif;
		}
		Color    GetMatSpecular() const
		{
			return renderObject->map->Mspec;
		}
		float    GetMatShininess() const
		{
			return renderObject->map->shininess;
		}
		Color    GetTexturePixel(const Vector2& coord) const
		{
			return renderObject->map->texture->Sample(coord.x, coord.y);
		}
	};
}

