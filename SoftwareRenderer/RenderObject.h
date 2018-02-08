#pragma once

#include "Config.h"
#include "RenderMath.h"

namespace Tan
{

	class RenderObject
	{
	public:
		UINT      verticesCount;
		UINT      indicesCount;
		UINT     *indices;
		Vertex   *vertices;
	
		Matrix	  world;
		Matrix	  view;
		Matrix	  projection;

		Matrix	  wvTransform;

	public:
		RenderObject();
		RenderObject(const RenderObject& rhs) : vertices(rhs.vertices), world(rhs.world), 
		view(rhs.view), projection(rhs.projection), wvTransform(rhs.wvTransform) {}
		~RenderObject() = default;

	public:
		void	    GenerateBox();
		void	    Delete();

		void	    Rotate();
		inline void Update();
	};
}