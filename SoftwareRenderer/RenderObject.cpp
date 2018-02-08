#include "RenderObject.h"

namespace Tan
{
	RenderObject::RenderObject()
	{
		verticesCount = 0;
		indicesCount  = 0;

		indices  = nullptr;
		vertices = nullptr;

		world = Matrix
		(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		view = RenderMath::GetViewMatrix
		(
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(0.0f, 0.0f, 1.0f),
			Vector3(0.0f, 1.0f, 0.0f)
		);
		projection = RenderMath::GetPerspectiveMatrix
		(
			static_cast<float>(PI * 0.5f),
			static_cast<float>(WND_WIDTH / WND_HEIGHT),
			NEAR,
			FAR
		);

		Update();
	}

	void RenderObject::GenerateBox()
	{
		// 8 vertices
		verticesCount = 8;
		vertices = new Vertex[8]
		{
			{ {0.0f, 0.0f, 0.0f, 1.0f },   Colors::White, 0.0f },
			{ {0.0f, 0.0f, 6.0f, 1.0f },   Colors::Black, 0.0f },
			{ {6.0f, 0.0f, 6.0f, 1.0f },     Colors::Red, 0.0f },
			{ {6.0f, 0.0f, 0.0f, 1.0f },   Colors::Green, 0.0f },
			{ {0.0f, 6.0f, 0.0f, 1.0f },    Colors::Blue, 0.0f },
			{ {0.0f, 6.0f, 6.0f, 1.0f },  Colors::Yellow, 0.0f },
			{ {6.0f, 6.0f, 6.0f, 1.0f },    Colors::Cyan, 0.0f },
			{ {6.0f, 6.0f, 0.0f, 1.0f }, Colors::Magenta, 0.0f }
		};
	
		// 12 x 3 = 36 indices
		indicesCount = 36;
		indices = new UINT[36]
		{
			// bottom (counter-clockwise)
			0, 2, 1,
			0, 3, 2, 

			// front
			0, 4, 7,
			0, 7, 3,

			// left (counter-clockwise)
			0, 5, 4,
			0, 1, 5,
			
			// back (counter-clockwise)
			1, 6, 5,
			1, 2, 6,
		
			// right
			3, 7, 6,
			3, 6, 2,

			// top
			4, 5, 6,
			4, 6, 7
		};

		world = Matrix
		(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		view = RenderMath::GetViewMatrix
		(
			Vector3(12.0f, 3.0f, -6.0f),
			Vector3( 6.0f, 3.0f,  0.0f),
			Vector3( 0.0f, 1.0f,  0.0f)
		);
		projection = RenderMath::GetPerspectiveMatrix
		(
			static_cast<float>(PI * 0.5f),
			static_cast<float>(WND_WIDTH / WND_HEIGHT), 
			1.0f, 
			500.0f
		);

		Update();
	}

	void RenderObject::Delete()
	{
		if (vertices)
			delete vertices;
		vertices = nullptr;

		if (indices)
			delete indices;
		indices = nullptr;
	}

	void RenderObject::Rotate()
	{
		static float theta = 0.005f;
		static Matrix rotate = RenderMath::GetRotateMatrix(1.0f, 1.0f, 1.0f, theta);
		world = RenderMath::MatrixMulMatrix(world, rotate);
		Update();
	}

	inline void RenderObject::Update()
	{
		wvTransform = RenderMath::MatrixMulMatrix(world, view);
	}
}