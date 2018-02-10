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

	public:
		RenderObject();
		RenderObject(const RenderObject& rhs) : vertices(rhs.vertices), world(rhs.world) {}
		~RenderObject() = default;

	public:
		void Delete();

		void Rotate();
		void GenerateBox();
	};
}