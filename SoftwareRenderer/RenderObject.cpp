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
	}

	void RenderObject::GenerateBox()
	{
		// 24 vertices
		verticesCount = 24;
		vertices = new Vertex[24] // pos, color, uv, normal, light, rhw.
		{
/* 0 */		{ {  0.5f, -0.5f,  0.5f, 1.0f },  Colors::White,   { 0.0f, 0.0f },  {  0.0f,  0.0f,  1.0f },  Colors::White,  0.0f },
			{ { -0.5f, -0.5f,  0.5f, 1.0f },  Colors::Black,   { 1.0f, 0.0f },  {  0.0f,  0.0f,  1.0f },  Colors::White,  0.0f },
			{ {  0.5f,  0.5f,  0.5f, 1.0f },  Colors::Red,     { 0.0f, 1.0f },  {  0.0f,  0.0f,  1.0f },  Colors::White,  0.0f },
			{ { -0.5f,  0.5f,  0.5f, 1.0f },  Colors::Green,   { 1.0f, 1.0f },  {  0.0f,  0.0f,  1.0f },  Colors::White,  0.0f },

/* 4 */		{ {  0.5f,  0.5f, -0.5f, 1.0f },  Colors::Blue,    { 0.0f, 1.0f },  {  0.0f,  1.0f,  0.0f },  Colors::White,  0.0f },
			{ { -0.5f,  0.5f, -0.5f, 1.0f },  Colors::Yellow,  { 1.0f, 1.0f },  {  0.0f,  1.0f,  0.0f },  Colors::White,  0.0f },
			{ {  0.5f, -0.5f, -0.5f, 1.0f },  Colors::Cyan,    { 0.0f, 1.0f },  {  0.0f,  0.0f, -1.0f },  Colors::White,  0.0f },
			{ { -0.5f, -0.5f, -0.5f, 1.0f },  Colors::Magenta, { 1.0f, 1.0f },  {  0.0f,  0.0f, -1.0f },  Colors::White,  0.0f },
 
/* 8 */		{ {  0.5f,  0.5f,  0.5f, 1.0f },  Colors::Red,     { 0.0f, 0.0f },	{  0.0f,  1.0f,  0.0f },  Colors::White,  0.0f },
			{ { -0.5f,  0.5f,  0.5f, 1.0f },  Colors::Green,   { 1.0f, 0.0f },  {  0.0f,  1.0f,  0.0f },  Colors::White,  0.0f },
			{ {  0.5f,  0.5f, -0.5f, 1.0f },  Colors::Blue,    { 0.0f, 0.0f },  {  0.0f,  0.0f, -1.0f },  Colors::White,  0.0f },
			{ { -0.5f,  0.5f, -0.5f, 1.0f },  Colors::Yellow,  { 1.0f, 0.0f },  {  0.0f,  0.0f, -1.0f },  Colors::White,  0.0f },
			
/* 12 */	{ {  0.5f, -0.5f, -0.5f, 1.0f },  Colors::Cyan,    { 0.0f, 0.0f },  {  0.0f, -1.0f,  0.0f },  Colors::White,  0.0f },
			{ {  0.5f, -0.5f,  0.5f, 1.0f },  Colors::White,   { 0.0f, 1.0f },  {  0.0f, -1.0f,  0.0f },  Colors::White,  0.0f },
			{ { -0.5f, -0.5f,  0.5f, 1.0f },  Colors::Black,   { 1.0f, 1.0f },  {  0.0f, -1.0f,  0.0f },  Colors::White,  0.0f },
			{ { -0.5f, -0.5f, -0.5f, 1.0f },  Colors::Magenta, { 1.0f, 0.0f },  {  0.0f, -1.0f,  0.0f },  Colors::White,  0.0f },

/* 16 */	{ { -0.5f, -0.5f,  0.5f, 1.0f },  Colors::Black,   { 0.0f, 0.0f },  { -1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
			{ { -0.5f,  0.5f,  0.5f, 1.0f },  Colors::Green,   { 0.0f, 1.0f },  { -1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
			{ { -0.5f,  0.5f, -0.5f, 1.0f },  Colors::Yellow,  { 1.0f, 1.0f },  { -1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
			{ { -0.5f, -0.5f, -0.5f, 1.0f },  Colors::Magenta, { 1.0f, 0.0f },  { -1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
			
/* 20 */	{ {  0.5f, -0.5f, -0.5f, 1.0f },  Colors::Cyan,    { 0.0f, 0.0f },  {  1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
			{ {  0.5f,  0.5f, -0.5f, 1.0f },  Colors::Blue,    { 0.0f, 1.0f },  {  1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
			{ {  0.5f,  0.5f,  0.5f, 1.0f },  Colors::Red,     { 1.0f, 1.0f },  {  1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
			{ {  0.5f, -0.5f,  0.5f, 1.0f },  Colors::White,   { 1.0f, 0.0f },  {  1.0f,  0.0f,  0.0f },  Colors::White,  0.0f },
		};

		// 12 x 3 = 36 indices
		indicesCount = 36;
		indices = new UINT[36]
		{
			// back (counter-clockwise)
		    0, 2, 3,
			0, 3, 1,

			// top
			8, 4, 5,
			8, 5, 9,

			// front
			10, 6, 7,
			10, 7, 11,

			// bottom (counter-clockwise)
			12, 13, 14,
			12, 14, 15,

			// left (counter-clockwise)
			16, 17, 18,
			16, 18, 19,

			// right
			20, 21, 22,
			20, 22, 23
		};

		// Scale 4 times.
		world.m[0][0] *= 3.5f;
		world.m[1][1] *= 3.5f;
		world.m[2][2] *= 3.5f;
	}
}