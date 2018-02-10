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
		Vector3 GetCameraPos() const
		{
			return camera->pos;
		}
		Matrix  GetWorldMatrix() const
		{
			return renderObject->world;
		}
	};
}

