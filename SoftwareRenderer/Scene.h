#pragma once

#include "Config.h"
#include "RenderObject.h"

namespace Tan
{
	class Scene
	{
	public:
		RenderObject *renderObject;
		RENDER_STATE  renderState;
		
		Light		 *lightSource;
		Camera		 *camera;

		Matrix		  view;
		Matrix		  projection;

	public:
		Scene();
		Scene(const Scene& rhs) = delete;
		~Scene() = default;

	public:
		void    Initialize();
		void    Delete();
		void    Update();

		void    CreateBox();

		UINT    GetIndicesCount() const
		{ 
			return renderObject->indicesCount; 
		};
		UINT    GetIndex(UINT i) const
		{
			return renderObject->indices[i];
		}
		Vertex  GetVertex(UINT i) const
		{
			return renderObject->vertices[i];
		}
		Matrix  GetWorldMatrix() const // can be GetWorldMatrix(INDEX objectIndex)
		{
			return renderObject->world;
		}

		Vector3 GetCameraPos() const
		{
			return camera->pos;
		}
		Vector3 GetLightPos() const
		{
			return lightSource->pos;
		}
		Color   GetLightAmbient() const
		{
			return lightSource->Kamb;
		}
		Color   GetLightDiffuse() const
		{
			return lightSource->Kdif;
		}
		Color   GetLightSpecular() const
		{
			return lightSource->Kspec;
		}

		Color   GetMatAmbient() const
		{
			return renderObject->map->Mamb;
		}
		Color   GetMatDiffuse() const
		{
			return renderObject->map->Mdif;
		}
		Color   GetMatSpecular() const
		{
			return renderObject->map->Mspec;
		}
		float   GetMatShininess() const
		{
			return renderObject->map->shininess;
		}
	};
}

