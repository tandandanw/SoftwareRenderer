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

		Matrix	   world;
		Material  *map;

	public:
		RenderObject();
		RenderObject(const RenderObject& rhs) : verticesCount(rhs.verticesCount), indicesCount(rhs.indicesCount), indices(rhs.indices), vertices(rhs.vertices),
			world(rhs.world), map(rhs.map) {}
		~RenderObject() = default;

	public:
		void Delete();

		void Rotate();
		void GenerateBox();
	};
}