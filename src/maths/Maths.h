#ifndef MATH_H_
#define MATH_H_

#include "Vector3.h"
#include <cmath>

namespace Maths
{
	static const float PI = 3.1415926535f;
	static const float EPSILON = 0.0001f;

	inline bool FP_EQUAL(float a, float b)
	{
			return (std::abs(a - b) < Maths::EPSILON);
	}
	float GetRandomFloatNonGame();

	inline bool	Is2DVectorEqual( const Vector3& inA, const Vector3& inB )
	{
		return ( inA.mX == inB.mX && inA.mY == inB.mY );
	}

	inline bool	Is3DVectorEqual( const Vector3& inA, const Vector3& inB )
	{
		return ( inA.mX == inB.mX && inA.mY == inB.mY &&  inA.mZ == inB.mZ);
	}

	inline float ToDegrees( float inRadians )
	{
		return inRadians * 180.0f / PI;
	}
}

#endif
