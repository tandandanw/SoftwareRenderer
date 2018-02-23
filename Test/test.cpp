#include "pch.h"

using namespace Tan;

TEST(MathTestCases, Vector2Length)
{
	Vector2 v(1, 1);
	float Length = v.Length();
	float Length2 = v.LengthSquared();
	EXPECT_TRUE(Length * Length - Length2 < FLT_MIN);
}
TEST(MathTestCases, Vector2Dot)
{
	Vector2 v1(2.5f, 1.0f);
	Vector2 v2(5.0f, 3.0f);
	float result = v1.Dot(v2);
	EXPECT_TRUE(result - 15.5f < FLT_MIN);

}
TEST(MathTestCases, Vector2Normalize)
{
	Vector2 v(2.0f, 1.0f);
	v.Normalize();
	EXPECT_TRUE(v.Length() - 1.0f < FLT_MIN);
}

TEST(MathTestCases, Vector3Length)
{
	Vector3 v(1, 1, 4);
	float Length = v.Length();
	float Length2 = v.LengthSquared();
	EXPECT_TRUE(Length * Length - Length2 < FLT_MIN);
}
TEST(MathTestCases, Vector3Dot)
{
	Vector3 v1(5.5f, 8.0f, 1.0f);
	Vector3 v2(1.2f, 4.3f, 1.1f);
	float result = v1.Dot(v2);
	EXPECT_TRUE(result - 63.88f < FLT_MIN);

}
TEST(MathTestCases, Vector3Normalize)
{
	Vector3 v(2.8f, 6.1f, 4.9f);
	v.Normalize();
	EXPECT_TRUE(v.Length() - 1.0f < FLT_MIN);
}
TEST(MathTestCases, Vector3Cross1)
{
	Vector3 v1(1.0f, 2.1f, 3.0f);
	Vector3 v2(1.3f, 5.0f, 1.4f);
	Vector3 ret = v1.Cross(v2);
	Vector3 result = Vector3(-12.06f, 2.5f, 2.27f);
	EXPECT_TRUE(ret == result);
}
TEST(MathTestCases, Vector3Cross2)
{
	Vector3 v1(1.0f, 2.0f, 3.0f);
	Vector3 v2(9.0f, 5.0f, 4.0f);
	Vector3 ret = v1.Cross(v2);
	Vector3 result = Vector3(-7.0f, 23.0f, -13.0f);
	EXPECT_TRUE((ret - result).Length() - 0.0f < FLT_MIN);
}

/*TEST(MathTestCases, Vector4MulMatrix)
{
	Vector4 lhs(4.5f, 2.3f, 1.8f, 1.0f);
	Matrix rhs
	(
		3.0f, 8.0f, 2.2f, 0.0f,
		7.4f, 4.0f, 0.6f, 0.0f,
		1.3f, 3.2f, 2.8f, 0.0f,
		5.0f, 9.8f, 4.7f, 1.0f
	);
	Vector4 ret = RenderMath::Vector4MulMatrix(lhs, rhs);
	Vector4 result(37.86f, 60.76f, 21.02f, 1.00f);
	EXPECT_TRUE(ret == result);
}
TEST(MathTestCases, MatrixMulMatrix)
{
	Matrix lhs
	(
		1.0f, 3.0f, 5.0f, 0.0f,
		2.0f, 4.0f, 6.0f, 0.0f,
		8.0f, 3.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	);
	Matrix rhs
	(
		4.0f, 8.0f, 6.0f, 0.0f,
		7.0f, 7.0f, 0.0f, 0.0f,
		1.0f, 3.0f, 2.0f, 0.0f,
		3.0f, 9.0f, 4.0f, 1.0f
	);
	Matrix ret(Tan::RenderMath::MatrixMulMatrix(lhs, rhs));
	Matrix result
	(
		30.0f, 44.0f, 16.0f, 0.0f,
		42.0f, 62.0f, 24.0f, 0.0f,
		54.0f, 88.0f, 50.0f, 0.0f,
		15.0f, 27.0f, 12.0f, 1.0f
	);

	EXPECT_TRUE(ret == result);
}*/