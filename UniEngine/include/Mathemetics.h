#pragma once
#include <math.h>
#include "UniEngineAPI.h"

#include "UEbool.h"
#include "UEdouble.h"
#include "UEfloat.h"
#include "UEint.h"
#include "UElong.h"
#include "UEunsigned.h"
#include "UEulong.h"
namespace UniEngine {
#pragma region As
	union IntFloatUnion
	{
		int intValue;
		float floatValue;
	};

	union LongDoubleUnion
	{
		long longValue;
		double doubleValue;
	};

	/// <summary>Returns the bit pattern of a unsigned as an int.</summary>

	inline static int asint(unsigned x) { return (int)x; }

	/// <summary>Returns the bit pattern of a unsigned2 as an int2.</summary>

	inline static int2 asint(unsigned2 x) { return int2((int)x.x, (int)x.y); }

	/// <summary>Returns the bit pattern of a unsigned3 as an int3.</summary>

	inline static int3 asint(unsigned3 x) { return int3((int)x.x, (int)x.y, (int)x.z); }

	/// <summary>Returns the bit pattern of a unsigned4 as an int4.</summary>

	inline static int4 asint(unsigned4 x) { return int4((int)x.x, (int)x.y, (int)x.z, (int)x.w); }


	/// <summary>Returns the bit pattern of a float as an int.</summary>

	inline static int asint(float x) {
		IntFloatUnion u;
		u.intValue = 0;
		u.floatValue = x;
		return u.intValue;
	}

	/// <summary>Returns the bit pattern of a float2 as an int2.</summary>

	inline static int2 asint(float2 x) { return int2(asint(x.x), asint(x.y)); }

	/// <summary>Returns the bit pattern of a float3 as an int3.</summary>

	inline static int3 asint(float3 x) { return int3(asint(x.x), asint(x.y), asint(x.z)); }

	/// <summary>Returns the bit pattern of a float4 as an int4.</summary>

	inline static int4 asint(float4 x) { return int4(asint(x.x), asint(x.y), asint(x.z), asint(x.w)); }


	/// <summary>Returns the bit pattern of an int as a unsigned.</summary>

	inline static unsigned asunsigned(int x) { return (unsigned)x; }

	/// <summary>Returns the bit pattern of an int2 as a unsigned2.</summary>

	inline static unsigned2 asunsigned(int2 x) { return unsigned2((unsigned)x.x, (unsigned)x.y); }

	/// <summary>Returns the bit pattern of an int3 as a unsigned3.</summary>

	inline static unsigned3 asunsigned(int3 x) { return unsigned3((unsigned)x.x, (unsigned)x.y, (unsigned)x.z); }

	/// <summary>Returns the bit pattern of an int4 as a unsigned4.</summary>

	inline static unsigned4 asunsigned(int4 x) { return unsigned4((unsigned)x.x, (unsigned)x.y, (unsigned)x.z, (unsigned)x.w); }


	/// <summary>Returns the bit pattern of a float as a unsigned.</summary>

	inline static unsigned asunsigned(float x) { return (unsigned)asint(x); }

	/// <summary>Returns the bit pattern of a float2 as a unsigned2.</summary>

	inline static unsigned2 asunsigned(float2 x) { return unsigned2(asunsigned(x.x), asunsigned(x.y)); }

	/// <summary>Returns the bit pattern of a float3 as a unsigned3.</summary>

	inline static unsigned3 asunsigned(float3 x) { return unsigned3(asunsigned(x.x), asunsigned(x.y), asunsigned(x.z)); }

	/// <summary>Returns the bit pattern of a float4 as a unsigned4.</summary>

	inline static unsigned4 asunsigned(float4 x) { return unsigned4(asunsigned(x.x), asunsigned(x.y), asunsigned(x.z), asunsigned(x.w)); }


	/// <summary>Returns the bit pattern of a ulong as a long.</summary>

	inline static long aslong(ulong x) { return (long)x; }

	/// <summary>Returns the bit pattern of a double as a long.</summary>

	inline static long aslong(double x)
	{
		LongDoubleUnion u;
		u.longValue = 0;
		u.doubleValue = x;
		return u.longValue;
	}


	/// <summary>Returns the bit pattern of a long as a ulong.</summary>

	inline static ulong asulong(long x) { return (ulong)x; }

	/// <summary>Returns the bit pattern of a double as a ulong.</summary>

	inline static ulong asulong(double x) { return (ulong)aslong(x); }


	/// <summary>Returns the bit pattern of an int as a float.</summary>

	inline static float asfloat(int x)
	{
		IntFloatUnion u;
		u.floatValue = 0;
		u.intValue = x;

		return u.floatValue;
	}

	/// <summary>Returns the bit pattern of an int2 as a float2.</summary>

	inline static float2 asfloat(int2 x) { return float2(asfloat(x.x), asfloat(x.y)); }

	/// <summary>Returns the bit pattern of an int3 as a float3.</summary>

	inline static float3 asfloat(int3 x) { return float3(asfloat(x.x), asfloat(x.y), asfloat(x.z)); }

	/// <summary>Returns the bit pattern of an int4 as a float4.</summary>

	inline static float4 asfloat(int4 x) { return float4(asfloat(x.x), asfloat(x.y), asfloat(x.z), asfloat(x.w)); }


	/// <summary>Returns the bit pattern of a unsigned as a float.</summary>

	inline static float  asfloat(unsigned x) { return asfloat((int)x); }

	/// <summary>Returns the bit pattern of a unsigned2 as a float2.</summary>

	inline static float2 asfloat(unsigned2 x) { return float2(asfloat(x.x), asfloat(x.y)); }

	/// <summary>Returns the bit pattern of a unsigned3 as a float3.</summary>

	inline static float3 asfloat(unsigned3 x) { return float3(asfloat(x.x), asfloat(x.y), asfloat(x.z)); }

	/// <summary>Returns the bit pattern of a unsigned4 as a float4.</summary>

	inline static float4 asfloat(unsigned4 x) { return float4(asfloat(x.x), asfloat(x.y), asfloat(x.z), asfloat(x.w)); }
	/// <summary>Returns the bit pattern of a long as a double.</summary>
	inline static double asdouble(long x)
	{
		LongDoubleUnion u;
		u.doubleValue = 0;
		u.longValue = x;
		return u.doubleValue;
	}


	/// <summary>Returns the bit pattern of a ulong as a double.</summary>
	inline static double asdouble(ulong x) { return asdouble((long)x); }

#pragma endregion
#pragma region Basic

	/// <summary>Returns the result of a componentwise bitwise exclusive or operation on two unsigned3 vectors.</summary>
	inline static unsigned3 operator ^ (const unsigned3& lhs, const unsigned3& rhs) { return unsigned3(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z); }

	/// <summary>Returns the result of a componentwise bitwise exclusive or operation on a unsigned3 vector and a unsigned value.</summary>
	inline static unsigned3 operator ^ (const unsigned3& lhs, unsigned rhs) { return unsigned3(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs); }

	/// <summary>Returns the result of a componentwise bitwise exclusive or operation on a unsigned value and a unsigned3 vector.</summary>
	inline static unsigned3 operator ^ (unsigned lhs, const unsigned3& rhs) { return unsigned3(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z); }

	/// <summary>Returns the result of a componentwise bitwise exclusive or operation on two unsigned4 vectors.</summary>
	inline static unsigned4 operator ^ (const unsigned4& lhs, const unsigned4& rhs) { return unsigned4(lhs.x ^ rhs.x, lhs.y ^ rhs.y, lhs.z ^ rhs.z, lhs.w ^ rhs.w); }

	/// <summary>Returns the result of a componentwise bitwise exclusive or operation on a unsigned4 vector and a unsigned value.</summary>
	inline static unsigned4 operator ^ (const unsigned4& lhs, unsigned rhs) { return unsigned4(lhs.x ^ rhs, lhs.y ^ rhs, lhs.z ^ rhs, lhs.w ^ rhs); }

	/// <summary>Returns the result of a componentwise bitwise exclusive or operation on a unsigned value and a unsigned4 vector.</summary>
	inline static unsigned4 operator ^ (unsigned lhs, const unsigned4& rhs) { return unsigned4(lhs ^ rhs.x, lhs ^ rhs.y, lhs ^ rhs.z, lhs ^ rhs.w); }

	/// <summary>Returns the result of a componentwise bitwise and operation on two unsigned2 vectors.</summary>
	inline static unsigned2 operator & (const unsigned2& lhs, const unsigned2& rhs) { return unsigned2(lhs.x & rhs.x, lhs.y & rhs.y); }

	/// <summary>Returns the result of a componentwise bitwise and operation on a unsigned2 vector and a unsigned value.</summary>
	inline static unsigned2 operator & (const unsigned2& lhs, unsigned rhs) { return unsigned2(lhs.x & rhs, lhs.y & rhs); }

	/// <summary>Returns the result of a componentwise bitwise and operation on a unsigned value and a unsigned2 vector.</summary>
	inline static unsigned2 operator & (unsigned lhs, const unsigned2& rhs) { return  unsigned2(lhs & rhs.x, lhs & rhs.y); }

	/// <summary>Returns the result of a componentwise bitwise and operation on two unsigned3 vectors.</summary>
	inline static unsigned3 operator & (const unsigned3& lhs, const unsigned3& rhs) { return unsigned3(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z); }

	/// <summary>Returns the result of a componentwise bitwise and operation on a unsigned3 vector and a unsigned value.</summary>
	inline static unsigned3 operator & (const unsigned3& lhs, unsigned rhs) { return unsigned3(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs); }

	/// <summary>Returns the result of a componentwise bitwise and operation on a unsigned value and a unsigned3 vector.</summary>
	inline static unsigned3 operator & (unsigned lhs, const unsigned3& rhs) { return unsigned3(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z); }

	/// <summary>Returns the result of a componentwise bitwise and operation on two unsigned4 vectors.</summary>
	inline static unsigned4 operator & (const unsigned4& lhs, const unsigned4& rhs) { return unsigned4(lhs.x & rhs.x, lhs.y & rhs.y, lhs.z & rhs.z, lhs.w & rhs.w); }

	/// <summary>Returns the result of a componentwise bitwise and operation on a unsigned4 vector and a unsigned value.</summary>
	inline static unsigned4 operator & (const unsigned4& lhs, unsigned rhs) { return unsigned4(lhs.x & rhs, lhs.y & rhs, lhs.z & rhs, lhs.w & rhs); }

	/// <summary>Returns the result of a componentwise bitwise and operation on a unsigned value and a unsigned4 vector.</summary>
	inline static unsigned4 operator & (unsigned lhs, const unsigned4& rhs) { return unsigned4(lhs & rhs.x, lhs & rhs.y, lhs & rhs.z, lhs & rhs.w); }


	/// <summary>Returns the result of a componentwise bitwise or operation on two unsigned4 vectors.</summary>
	inline static unsigned4 operator | (const unsigned4& lhs, const unsigned4& rhs) { return unsigned4(lhs.x | rhs.x, lhs.y | rhs.y, lhs.z | rhs.z, lhs.w | rhs.w); }

	/// <summary>Returns the result of a componentwise bitwise or operation on a unsigned4 vector and a unsigned value.</summary>

	inline static unsigned4 operator | (const unsigned4& lhs, unsigned rhs) { return unsigned4(lhs.x | rhs, lhs.y | rhs, lhs.z | rhs, lhs.w | rhs); }

	/// <summary>Returns the result of a componentwise bitwise or operation on a unsigned value and a unsigned4 vector.</summary>

	inline static unsigned4 operator | (unsigned lhs, const unsigned4& rhs) { return unsigned4(lhs | rhs.x, lhs | rhs.y, lhs | rhs.z, lhs | rhs.w); }
	/// <summary>Returns the Absolute value of a int value.</summary>

	inline static int Abs(int x) { return Max(-x, x); }

	/// <summary>Returns the componentwise Absolute value of a int2 vector.</summary>

	inline static int2 Abs(int2 x) { return Max(-x, x); }

	/// <summary>Returns the componentwise Absolute value of a int3 vector.</summary>

	inline static int3 Abs(int3 x) { return Max(-x, x); }

	/// <summary>Returns the componentwise Absolute value of a int4 vector.</summary>

	inline static int4 Abs(int4 x) { return Max(-x, x); }

	/// <summary>Returns the Absolute value of a long value.</summary>

	inline static long Abs(long x) { return max(-x, x); }


	/// <summary>Returns the Absolute value of a float value.</summary>

	inline static float Abs(float x) { return asfloat(asunsigned(x) & (unsigned)0x7FFFFFFF); }

	/// <summary>Returns the componentwise Absolute value of a float2 vector.</summary>

	inline static float2 Abs(float2 x) { return asfloat(asunsigned(x) & (unsigned)0x7FFFFFFF); }

	/// <summary>Returns the componentwise Absolute value of a float3 vector.</summary>

	inline static float3 Abs(float3 x) { return asfloat(asunsigned(x) & (unsigned)0x7FFFFFFF); }

	/// <summary>Returns the componentwise Absolute value of a float4 vector.</summary>

	inline static float4 Abs(float4 x) { return asfloat(asunsigned(x) & (unsigned)0x7FFFFFFF); }


	/// <summary>Returns the Absolute value of a double value.</summary>

	inline static double Abs(double x) { return asdouble(asulong(x) & (ulong)0x7FFFFFFFFFFFFFFF); }

	/// <summary>Returns the componentwise Absolute value of a double2 vector.</summary>

	inline static double2 Abs(double2 x) { return double2(asdouble(asulong(x.x) & (ulong)0x7FFFFFFFFFFFFFFF), asdouble(asulong(x.y) & (ulong)0x7FFFFFFFFFFFFFFF)); }

	/// <summary>Returns the componentwise Absolute value of a double3 vector.</summary>

	inline static double3 Abs(double3 x) { return double3(asdouble(asulong(x.x) & (ulong)0x7FFFFFFFFFFFFFFF), asdouble(asulong(x.y) & (ulong)0x7FFFFFFFFFFFFFFF), asdouble(asulong(x.z) & (ulong)0x7FFFFFFFFFFFFFFF)); }

	/// <summary>Returns the componentwise Absolute value of a double4 vector.</summary>

	inline static double4 Abs(double4 x) { return double4(asdouble(asulong(x.x) & (ulong)0x7FFFFFFFFFFFFFFF), asdouble(asulong(x.y) & (ulong)0x7FFFFFFFFFFFFFFF), asdouble(asulong(x.z) & (ulong)0x7FFFFFFFFFFFFFFF), asdouble(asulong(x.w) & (ulong)0x7FFFFFFFFFFFFFFF)); }



#pragma endregion
#pragma region Multiplytiplication
	/// <summary>Returns the float value result of a matrix Multiplytiplication between a float value and a float value.</summary>

	inline static float Multiply(float a, float b)
	{
		return a * b;
	}

	/// <summary>Returns the float value result of a matrix Multiplytiplication between a float2 row vector and a float2 column vector.</summary>

	inline static float Multiply(float2 a, float2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/// <summary>Returns the float2 row vector result of a matrix Multiplytiplication between a float2 row vector and a float2x2 matrix.</summary>

	inline static float2 Multiply(float2 a, float2x2 b)
	{
		return float2(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y);
	}

	/// <summary>Returns the float3 row vector result of a matrix Multiplytiplication between a float2 row vector and a float2x3 matrix.</summary>

	inline static float3 Multiply(float2 a, float2x3 b)
	{
		return float3(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y);
	}

	/// <summary>Returns the float4 row vector result of a matrix Multiplytiplication between a float2 row vector and a float2x4 matrix.</summary>

	inline static float4 Multiply(float2 a, float2x4 b)
	{
		return float4(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y,
			a.x * b.c3.x + a.y * b.c3.y);
	}

	/// <summary>Returns the float value result of a matrix Multiplytiplication between a float3 row vector and a float3 column vector.</summary>

	inline static float Multiply(float3 a, float3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/// <summary>Returns the float2 row vector result of a matrix Multiplytiplication between a float3 row vector and a float3x2 matrix.</summary>

	inline static float2 Multiply(float3 a, float3x2 b)
	{
		return float2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z);
	}

	/// <summary>Returns the float3 row vector result of a matrix Multiplytiplication between a float3 row vector and a float3x3 matrix.</summary>

	inline static float3 Multiply(float3 a, float3x3 b)
	{
		return float3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z);
	}

	/// <summary>Returns the float4 row vector result of a matrix Multiplytiplication between a float3 row vector and a float3x4 matrix.</summary>

	inline static float4 Multiply(float3 a, float3x4 b)
	{
		return float4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z);
	}

	/// <summary>Returns the float value result of a matrix Multiplytiplication between a float4 row vector and a float4 column vector.</summary>

	inline static float Multiply(float4 a, float4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	/// <summary>Returns the float2 row vector result of a matrix Multiplytiplication between a float4 row vector and a float4x2 matrix.</summary>

	inline static float2 Multiply(float4 a, float4x2 b)
	{
		return float2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w);
	}

	/// <summary>Returns the float3 row vector result of a matrix Multiplytiplication between a float4 row vector and a float4x3 matrix.</summary>

	inline static float3 Multiply(float4 a, float4x3 b)
	{
		return float3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w);
	}

	/// <summary>Returns the float4 row vector result of a matrix Multiplytiplication between a float4 row vector and a float4x4 matrix.</summary>

	inline static float4 Multiply(float4 a, float4x4 b)
	{
		return float4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z + a.w * b.c3.w);
	}

	/// <summary>Returns the float2 column vector result of a matrix Multiplytiplication between a float2x2 matrix and a float2 column vector.</summary>

	inline static float2 Multiply(float2x2 a, float2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the float2x2 matrix result of a matrix Multiplytiplication between a float2x2 matrix and a float2x2 matrix.</summary>

	inline static float2x2 Multiply(float2x2 a, float2x2 b)
	{
		return float2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the float2x3 matrix result of a matrix Multiplytiplication between a float2x2 matrix and a float2x3 matrix.</summary>

	inline static float2x3 Multiply(float2x2 a, float2x3 b)
	{
		return float2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the float2x4 matrix result of a matrix Multiplytiplication between a float2x2 matrix and a float2x4 matrix.</summary>

	inline static float2x4 Multiply(float2x2 a, float2x4 b)
	{
		return float2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the float2 column vector result of a matrix Multiplytiplication between a float2x3 matrix and a float3 column vector.</summary>

	inline static float2 Multiply(float2x3 a, float3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the float2x2 matrix result of a matrix Multiplytiplication between a float2x3 matrix and a float3x2 matrix.</summary>

	inline static float2x2 Multiply(float2x3 a, float3x2 b)
	{
		return float2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the float2x3 matrix result of a matrix Multiplytiplication between a float2x3 matrix and a float3x3 matrix.</summary>

	inline static float2x3 Multiply(float2x3 a, float3x3 b)
	{
		return float2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the float2x4 matrix result of a matrix Multiplytiplication between a float2x3 matrix and a float3x4 matrix.</summary>

	inline static float2x4 Multiply(float2x3 a, float3x4 b)
	{
		return float2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the float2 column vector result of a matrix Multiplytiplication between a float2x4 matrix and a float4 column vector.</summary>

	inline static float2 Multiply(float2x4 a, float4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the float2x2 matrix result of a matrix Multiplytiplication between a float2x4 matrix and a float4x2 matrix.</summary>

	inline static float2x2 Multiply(float2x4 a, float4x2 b)
	{
		return float2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the float2x3 matrix result of a matrix Multiplytiplication between a float2x4 matrix and a float4x3 matrix.</summary>

	inline static float2x3 Multiply(float2x4 a, float4x3 b)
	{
		return float2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the float2x4 matrix result of a matrix Multiplytiplication between a float2x4 matrix and a float4x4 matrix.</summary>

	inline static float2x4 Multiply(float2x4 a, float4x4 b)
	{
		return float2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the float3 column vector result of a matrix Multiplytiplication between a float3x2 matrix and a float2 column vector.</summary>

	inline static float3 Multiply(float3x2 a, float2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the float3x2 matrix result of a matrix Multiplytiplication between a float3x2 matrix and a float2x2 matrix.</summary>

	inline static float3x2 Multiply(float3x2 a, float2x2 b)
	{
		return float3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the float3x3 matrix result of a matrix Multiplytiplication between a float3x2 matrix and a float2x3 matrix.</summary>

	inline static float3x3 Multiply(float3x2 a, float2x3 b)
	{
		return float3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the float3x4 matrix result of a matrix Multiplytiplication between a float3x2 matrix and a float2x4 matrix.</summary>

	inline static float3x4 Multiply(float3x2 a, float2x4 b)
	{
		return float3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the float3 column vector result of a matrix Multiplytiplication between a float3x3 matrix and a float3 column vector.</summary>

	inline static float3 Multiply(float3x3 a, float3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the float3x2 matrix result of a matrix Multiplytiplication between a float3x3 matrix and a float3x2 matrix.</summary>

	inline static float3x2 Multiply(float3x3 a, float3x2 b)
	{
		return float3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the float3x3 matrix result of a matrix Multiplytiplication between a float3x3 matrix and a float3x3 matrix.</summary>

	inline static float3x3 Multiply(float3x3 a, float3x3 b)
	{
		return float3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the float3x4 matrix result of a matrix Multiplytiplication between a float3x3 matrix and a float3x4 matrix.</summary>

	inline static float3x4 Multiply(float3x3 a, float3x4 b)
	{
		return float3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the float3 column vector result of a matrix Multiplytiplication between a float3x4 matrix and a float4 column vector.</summary>

	inline static float3 Multiply(float3x4 a, float4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the float3x2 matrix result of a matrix Multiplytiplication between a float3x4 matrix and a float4x2 matrix.</summary>

	inline static float3x2 Multiply(float3x4 a, float4x2 b)
	{
		return float3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the float3x3 matrix result of a matrix Multiplytiplication between a float3x4 matrix and a float4x3 matrix.</summary>

	inline static float3x3 Multiply(float3x4 a, float4x3 b)
	{
		return float3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the float3x4 matrix result of a matrix Multiplytiplication between a float3x4 matrix and a float4x4 matrix.</summary>

	inline static float3x4 Multiply(float3x4 a, float4x4 b)
	{
		return float3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the float4 column vector result of a matrix Multiplytiplication between a float4x2 matrix and a float2 column vector.</summary>

	inline static float4 Multiply(float4x2 a, float2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the float4x2 matrix result of a matrix Multiplytiplication between a float4x2 matrix and a float2x2 matrix.</summary>

	inline static float4x2 Multiply(float4x2 a, float2x2 b)
	{
		return float4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the float4x3 matrix result of a matrix Multiplytiplication between a float4x2 matrix and a float2x3 matrix.</summary>

	inline static float4x3 Multiply(float4x2 a, float2x3 b)
	{
		return float4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the float4x4 matrix result of a matrix Multiplytiplication between a float4x2 matrix and a float2x4 matrix.</summary>

	inline static float4x4 Multiply(float4x2 a, float2x4 b)
	{
		return float4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the float4 column vector result of a matrix Multiplytiplication between a float4x3 matrix and a float3 column vector.</summary>

	inline static float4 Multiply(float4x3 a, float3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the float4x2 matrix result of a matrix Multiplytiplication between a float4x3 matrix and a float3x2 matrix.</summary>

	inline static float4x2 Multiply(float4x3 a, float3x2 b)
	{
		return float4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the float4x3 matrix result of a matrix Multiplytiplication between a float4x3 matrix and a float3x3 matrix.</summary>

	inline static float4x3 Multiply(float4x3 a, float3x3 b)
	{
		return float4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the float4x4 matrix result of a matrix Multiplytiplication between a float4x3 matrix and a float3x4 matrix.</summary>

	inline static float4x4 Multiply(float4x3 a, float3x4 b)
	{
		return float4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the float4 column vector result of a matrix Multiplytiplication between a float4x4 matrix and a float4 column vector.</summary>

	inline static float4 Multiply(float4x4 a, float4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the float4x2 matrix result of a matrix Multiplytiplication between a float4x4 matrix and a float4x2 matrix.</summary>

	inline static float4x2 Multiply(float4x4 a, float4x2 b)
	{
		return float4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the float4x3 matrix result of a matrix Multiplytiplication between a float4x4 matrix and a float4x3 matrix.</summary>

	inline static float4x3 Multiply(float4x4 a, float4x3 b)
	{
		return float4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the float4x4 matrix result of a matrix Multiplytiplication between a float4x4 matrix and a float4x4 matrix.</summary>

	inline static float4x4 Multiply(float4x4 a, float4x4 b)
	{
		return float4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the double value result of a matrix Multiplytiplication between a double value and a double value.</summary>

	inline static double Multiply(double a, double b)
	{
		return a * b;
	}

	/// <summary>Returns the double value result of a matrix Multiplytiplication between a double2 row vector and a double2 column vector.</summary>

	inline static double Multiply(double2 a, double2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/// <summary>Returns the double2 row vector result of a matrix Multiplytiplication between a double2 row vector and a double2x2 matrix.</summary>

	inline static double2 Multiply(double2 a, double2x2 b)
	{
		return double2(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y);
	}

	/// <summary>Returns the double3 row vector result of a matrix Multiplytiplication between a double2 row vector and a double2x3 matrix.</summary>

	inline static double3 Multiply(double2 a, double2x3 b)
	{
		return double3(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y);
	}

	/// <summary>Returns the double4 row vector result of a matrix Multiplytiplication between a double2 row vector and a double2x4 matrix.</summary>

	inline static double4 Multiply(double2 a, double2x4 b)
	{
		return double4(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y,
			a.x * b.c3.x + a.y * b.c3.y);
	}

	/// <summary>Returns the double value result of a matrix Multiplytiplication between a double3 row vector and a double3 column vector.</summary>

	inline static double Multiply(double3 a, double3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/// <summary>Returns the double2 row vector result of a matrix Multiplytiplication between a double3 row vector and a double3x2 matrix.</summary>

	inline static double2 Multiply(double3 a, double3x2 b)
	{
		return double2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z);
	}

	/// <summary>Returns the double3 row vector result of a matrix Multiplytiplication between a double3 row vector and a double3x3 matrix.</summary>

	inline static double3 Multiply(double3 a, double3x3 b)
	{
		return double3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z);
	}

	/// <summary>Returns the double4 row vector result of a matrix Multiplytiplication between a double3 row vector and a double3x4 matrix.</summary>

	inline static double4 Multiply(double3 a, double3x4 b)
	{
		return double4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z);
	}

	/// <summary>Returns the double value result of a matrix Multiplytiplication between a double4 row vector and a double4 column vector.</summary>

	inline static double Multiply(double4 a, double4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	/// <summary>Returns the double2 row vector result of a matrix Multiplytiplication between a double4 row vector and a double4x2 matrix.</summary>

	inline static double2 Multiply(double4 a, double4x2 b)
	{
		return double2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w);
	}

	/// <summary>Returns the double3 row vector result of a matrix Multiplytiplication between a double4 row vector and a double4x3 matrix.</summary>

	inline static double3 Multiply(double4 a, double4x3 b)
	{
		return double3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w);
	}

	/// <summary>Returns the double4 row vector result of a matrix Multiplytiplication between a double4 row vector and a double4x4 matrix.</summary>

	inline static double4 Multiply(double4 a, double4x4 b)
	{
		return double4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z + a.w * b.c3.w);
	}

	/// <summary>Returns the double2 column vector result of a matrix Multiplytiplication between a double2x2 matrix and a double2 column vector.</summary>

	inline static double2 Multiply(double2x2 a, double2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the double2x2 matrix result of a matrix Multiplytiplication between a double2x2 matrix and a double2x2 matrix.</summary>

	inline static double2x2 Multiply(double2x2 a, double2x2 b)
	{
		return double2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the double2x3 matrix result of a matrix Multiplytiplication between a double2x2 matrix and a double2x3 matrix.</summary>

	inline static double2x3 Multiply(double2x2 a, double2x3 b)
	{
		return double2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the double2x4 matrix result of a matrix Multiplytiplication between a double2x2 matrix and a double2x4 matrix.</summary>

	inline static double2x4 Multiply(double2x2 a, double2x4 b)
	{
		return double2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the double2 column vector result of a matrix Multiplytiplication between a double2x3 matrix and a double3 column vector.</summary>

	inline static double2 Multiply(double2x3 a, double3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the double2x2 matrix result of a matrix Multiplytiplication between a double2x3 matrix and a double3x2 matrix.</summary>

	inline static double2x2 Multiply(double2x3 a, double3x2 b)
	{
		return double2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the double2x3 matrix result of a matrix Multiplytiplication between a double2x3 matrix and a double3x3 matrix.</summary>

	inline static double2x3 Multiply(double2x3 a, double3x3 b)
	{
		return double2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the double2x4 matrix result of a matrix Multiplytiplication between a double2x3 matrix and a double3x4 matrix.</summary>

	inline static double2x4 Multiply(double2x3 a, double3x4 b)
	{
		return double2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the double2 column vector result of a matrix Multiplytiplication between a double2x4 matrix and a double4 column vector.</summary>

	inline static double2 Multiply(double2x4 a, double4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the double2x2 matrix result of a matrix Multiplytiplication between a double2x4 matrix and a double4x2 matrix.</summary>

	inline static double2x2 Multiply(double2x4 a, double4x2 b)
	{
		return double2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the double2x3 matrix result of a matrix Multiplytiplication between a double2x4 matrix and a double4x3 matrix.</summary>

	inline static double2x3 Multiply(double2x4 a, double4x3 b)
	{
		return double2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the double2x4 matrix result of a matrix Multiplytiplication between a double2x4 matrix and a double4x4 matrix.</summary>

	inline static double2x4 Multiply(double2x4 a, double4x4 b)
	{
		return double2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the double3 column vector result of a matrix Multiplytiplication between a double3x2 matrix and a double2 column vector.</summary>

	inline static double3 Multiply(double3x2 a, double2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the double3x2 matrix result of a matrix Multiplytiplication between a double3x2 matrix and a double2x2 matrix.</summary>

	inline static double3x2 Multiply(double3x2 a, double2x2 b)
	{
		return double3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the double3x3 matrix result of a matrix Multiplytiplication between a double3x2 matrix and a double2x3 matrix.</summary>

	inline static double3x3 Multiply(double3x2 a, double2x3 b)
	{
		return double3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the double3x4 matrix result of a matrix Multiplytiplication between a double3x2 matrix and a double2x4 matrix.</summary>

	inline static double3x4 Multiply(double3x2 a, double2x4 b)
	{
		return double3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the double3 column vector result of a matrix Multiplytiplication between a double3x3 matrix and a double3 column vector.</summary>

	inline static double3 Multiply(double3x3 a, double3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the double3x2 matrix result of a matrix Multiplytiplication between a double3x3 matrix and a double3x2 matrix.</summary>

	inline static double3x2 Multiply(double3x3 a, double3x2 b)
	{
		return double3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the double3x3 matrix result of a matrix Multiplytiplication between a double3x3 matrix and a double3x3 matrix.</summary>

	inline static double3x3 Multiply(double3x3 a, double3x3 b)
	{
		return double3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the double3x4 matrix result of a matrix Multiplytiplication between a double3x3 matrix and a double3x4 matrix.</summary>

	inline static double3x4 Multiply(double3x3 a, double3x4 b)
	{
		return double3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the double3 column vector result of a matrix Multiplytiplication between a double3x4 matrix and a double4 column vector.</summary>

	inline static double3 Multiply(double3x4 a, double4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the double3x2 matrix result of a matrix Multiplytiplication between a double3x4 matrix and a double4x2 matrix.</summary>

	inline static double3x2 Multiply(double3x4 a, double4x2 b)
	{
		return double3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the double3x3 matrix result of a matrix Multiplytiplication between a double3x4 matrix and a double4x3 matrix.</summary>

	inline static double3x3 Multiply(double3x4 a, double4x3 b)
	{
		return double3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the double3x4 matrix result of a matrix Multiplytiplication between a double3x4 matrix and a double4x4 matrix.</summary>

	inline static double3x4 Multiply(double3x4 a, double4x4 b)
	{
		return double3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the double4 column vector result of a matrix Multiplytiplication between a double4x2 matrix and a double2 column vector.</summary>

	inline static double4 Multiply(double4x2 a, double2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the double4x2 matrix result of a matrix Multiplytiplication between a double4x2 matrix and a double2x2 matrix.</summary>

	inline static double4x2 Multiply(double4x2 a, double2x2 b)
	{
		return double4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the double4x3 matrix result of a matrix Multiplytiplication between a double4x2 matrix and a double2x3 matrix.</summary>

	inline static double4x3 Multiply(double4x2 a, double2x3 b)
	{
		return double4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the double4x4 matrix result of a matrix Multiplytiplication between a double4x2 matrix and a double2x4 matrix.</summary>

	inline static double4x4 Multiply(double4x2 a, double2x4 b)
	{
		return double4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the double4 column vector result of a matrix Multiplytiplication between a double4x3 matrix and a double3 column vector.</summary>

	inline static double4 Multiply(double4x3 a, double3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the double4x2 matrix result of a matrix Multiplytiplication between a double4x3 matrix and a double3x2 matrix.</summary>

	inline static double4x2 Multiply(double4x3 a, double3x2 b)
	{
		return double4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the double4x3 matrix result of a matrix Multiplytiplication between a double4x3 matrix and a double3x3 matrix.</summary>

	inline static double4x3 Multiply(double4x3 a, double3x3 b)
	{
		return double4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the double4x4 matrix result of a matrix Multiplytiplication between a double4x3 matrix and a double3x4 matrix.</summary>

	inline static double4x4 Multiply(double4x3 a, double3x4 b)
	{
		return double4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the double4 column vector result of a matrix Multiplytiplication between a double4x4 matrix and a double4 column vector.</summary>

	inline static double4 Multiply(double4x4 a, double4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the double4x2 matrix result of a matrix Multiplytiplication between a double4x4 matrix and a double4x2 matrix.</summary>

	inline static double4x2 Multiply(double4x4 a, double4x2 b)
	{
		return double4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the double4x3 matrix result of a matrix Multiplytiplication between a double4x4 matrix and a double4x3 matrix.</summary>

	inline static double4x3 Multiply(double4x4 a, double4x3 b)
	{
		return double4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the double4x4 matrix result of a matrix Multiplytiplication between a double4x4 matrix and a double4x4 matrix.</summary>

	inline static double4x4 Multiply(double4x4 a, double4x4 b)
	{
		return double4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the int value result of a matrix Multiplytiplication between an int value and an int value.</summary>

	inline static int Multiply(int a, int b)
	{
		return a * b;
	}

	/// <summary>Returns the int value result of a matrix Multiplytiplication between an int2 row vector and an int2 column vector.</summary>

	inline static int Multiply(int2 a, int2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/// <summary>Returns the int2 row vector result of a matrix Multiplytiplication between an int2 row vector and an int2x2 matrix.</summary>

	inline static int2 Multiply(int2 a, int2x2 b)
	{
		return int2(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y);
	}

	/// <summary>Returns the int3 row vector result of a matrix Multiplytiplication between an int2 row vector and an int2x3 matrix.</summary>

	inline static int3 Multiply(int2 a, int2x3 b)
	{
		return int3(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y);
	}

	/// <summary>Returns the int4 row vector result of a matrix Multiplytiplication between an int2 row vector and an int2x4 matrix.</summary>

	inline static int4 Multiply(int2 a, int2x4 b)
	{
		return int4(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y,
			a.x * b.c3.x + a.y * b.c3.y);
	}

	/// <summary>Returns the int value result of a matrix Multiplytiplication between an int3 row vector and an int3 column vector.</summary>

	inline static int Multiply(int3 a, int3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/// <summary>Returns the int2 row vector result of a matrix Multiplytiplication between an int3 row vector and an int3x2 matrix.</summary>

	inline static int2 Multiply(int3 a, int3x2 b)
	{
		return int2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z);
	}

	/// <summary>Returns the int3 row vector result of a matrix Multiplytiplication between an int3 row vector and an int3x3 matrix.</summary>

	inline static int3 Multiply(int3 a, int3x3 b)
	{
		return int3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z);
	}

	/// <summary>Returns the int4 row vector result of a matrix Multiplytiplication between an int3 row vector and an int3x4 matrix.</summary>

	inline static int4 Multiply(int3 a, int3x4 b)
	{
		return int4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z);
	}

	/// <summary>Returns the int value result of a matrix Multiplytiplication between an int4 row vector and an int4 column vector.</summary>

	inline static int Multiply(int4 a, int4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	/// <summary>Returns the int2 row vector result of a matrix Multiplytiplication between an int4 row vector and an int4x2 matrix.</summary>

	inline static int2 Multiply(int4 a, int4x2 b)
	{
		return int2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w);
	}

	/// <summary>Returns the int3 row vector result of a matrix Multiplytiplication between an int4 row vector and an int4x3 matrix.</summary>

	inline static int3 Multiply(int4 a, int4x3 b)
	{
		return int3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w);
	}

	/// <summary>Returns the int4 row vector result of a matrix Multiplytiplication between an int4 row vector and an int4x4 matrix.</summary>

	inline static int4 Multiply(int4 a, int4x4 b)
	{
		return int4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z + a.w * b.c3.w);
	}

	/// <summary>Returns the int2 column vector result of a matrix Multiplytiplication between an int2x2 matrix and an int2 column vector.</summary>

	inline static int2 Multiply(int2x2 a, int2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the int2x2 matrix result of a matrix Multiplytiplication between an int2x2 matrix and an int2x2 matrix.</summary>

	inline static int2x2 Multiply(int2x2 a, int2x2 b)
	{
		return int2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the int2x3 matrix result of a matrix Multiplytiplication between an int2x2 matrix and an int2x3 matrix.</summary>

	inline static int2x3 Multiply(int2x2 a, int2x3 b)
	{
		return int2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the int2x4 matrix result of a matrix Multiplytiplication between an int2x2 matrix and an int2x4 matrix.</summary>

	inline static int2x4 Multiply(int2x2 a, int2x4 b)
	{
		return int2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the int2 column vector result of a matrix Multiplytiplication between an int2x3 matrix and an int3 column vector.</summary>

	inline static int2 Multiply(int2x3 a, int3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the int2x2 matrix result of a matrix Multiplytiplication between an int2x3 matrix and an int3x2 matrix.</summary>

	inline static int2x2 Multiply(int2x3 a, int3x2 b)
	{
		return int2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the int2x3 matrix result of a matrix Multiplytiplication between an int2x3 matrix and an int3x3 matrix.</summary>

	inline static int2x3 Multiply(int2x3 a, int3x3 b)
	{
		return int2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the int2x4 matrix result of a matrix Multiplytiplication between an int2x3 matrix and an int3x4 matrix.</summary>

	inline static int2x4 Multiply(int2x3 a, int3x4 b)
	{
		return int2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the int2 column vector result of a matrix Multiplytiplication between an int2x4 matrix and an int4 column vector.</summary>

	inline static int2 Multiply(int2x4 a, int4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the int2x2 matrix result of a matrix Multiplytiplication between an int2x4 matrix and an int4x2 matrix.</summary>

	inline static int2x2 Multiply(int2x4 a, int4x2 b)
	{
		return int2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the int2x3 matrix result of a matrix Multiplytiplication between an int2x4 matrix and an int4x3 matrix.</summary>

	inline static int2x3 Multiply(int2x4 a, int4x3 b)
	{
		return int2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the int2x4 matrix result of a matrix Multiplytiplication between an int2x4 matrix and an int4x4 matrix.</summary>

	inline static int2x4 Multiply(int2x4 a, int4x4 b)
	{
		return int2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the int3 column vector result of a matrix Multiplytiplication between an int3x2 matrix and an int2 column vector.</summary>

	inline static int3 Multiply(int3x2 a, int2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the int3x2 matrix result of a matrix Multiplytiplication between an int3x2 matrix and an int2x2 matrix.</summary>

	inline static int3x2 Multiply(int3x2 a, int2x2 b)
	{
		return int3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the int3x3 matrix result of a matrix Multiplytiplication between an int3x2 matrix and an int2x3 matrix.</summary>

	inline static int3x3 Multiply(int3x2 a, int2x3 b)
	{
		return int3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the int3x4 matrix result of a matrix Multiplytiplication between an int3x2 matrix and an int2x4 matrix.</summary>

	inline static int3x4 Multiply(int3x2 a, int2x4 b)
	{
		return int3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the int3 column vector result of a matrix Multiplytiplication between an int3x3 matrix and an int3 column vector.</summary>

	inline static int3 Multiply(int3x3 a, int3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the int3x2 matrix result of a matrix Multiplytiplication between an int3x3 matrix and an int3x2 matrix.</summary>

	inline static int3x2 Multiply(int3x3 a, int3x2 b)
	{
		return int3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the int3x3 matrix result of a matrix Multiplytiplication between an int3x3 matrix and an int3x3 matrix.</summary>

	inline static int3x3 Multiply(int3x3 a, int3x3 b)
	{
		return int3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the int3x4 matrix result of a matrix Multiplytiplication between an int3x3 matrix and an int3x4 matrix.</summary>

	inline static int3x4 Multiply(int3x3 a, int3x4 b)
	{
		return int3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the int3 column vector result of a matrix Multiplytiplication between an int3x4 matrix and an int4 column vector.</summary>

	inline static int3 Multiply(int3x4 a, int4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the int3x2 matrix result of a matrix Multiplytiplication between an int3x4 matrix and an int4x2 matrix.</summary>

	inline static int3x2 Multiply(int3x4 a, int4x2 b)
	{
		return int3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the int3x3 matrix result of a matrix Multiplytiplication between an int3x4 matrix and an int4x3 matrix.</summary>

	inline static int3x3 Multiply(int3x4 a, int4x3 b)
	{
		return int3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the int3x4 matrix result of a matrix Multiplytiplication between an int3x4 matrix and an int4x4 matrix.</summary>

	inline static int3x4 Multiply(int3x4 a, int4x4 b)
	{
		return int3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the int4 column vector result of a matrix Multiplytiplication between an int4x2 matrix and an int2 column vector.</summary>

	inline static int4 Multiply(int4x2 a, int2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the int4x2 matrix result of a matrix Multiplytiplication between an int4x2 matrix and an int2x2 matrix.</summary>

	inline static int4x2 Multiply(int4x2 a, int2x2 b)
	{
		return int4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the int4x3 matrix result of a matrix Multiplytiplication between an int4x2 matrix and an int2x3 matrix.</summary>

	inline static int4x3 Multiply(int4x2 a, int2x3 b)
	{
		return int4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the int4x4 matrix result of a matrix Multiplytiplication between an int4x2 matrix and an int2x4 matrix.</summary>

	inline static int4x4 Multiply(int4x2 a, int2x4 b)
	{
		return int4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the int4 column vector result of a matrix Multiplytiplication between an int4x3 matrix and an int3 column vector.</summary>

	inline static int4 Multiply(int4x3 a, int3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the int4x2 matrix result of a matrix Multiplytiplication between an int4x3 matrix and an int3x2 matrix.</summary>

	inline static int4x2 Multiply(int4x3 a, int3x2 b)
	{
		return int4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the int4x3 matrix result of a matrix Multiplytiplication between an int4x3 matrix and an int3x3 matrix.</summary>

	inline static int4x3 Multiply(int4x3 a, int3x3 b)
	{
		return int4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the int4x4 matrix result of a matrix Multiplytiplication between an int4x3 matrix and an int3x4 matrix.</summary>

	inline static int4x4 Multiply(int4x3 a, int3x4 b)
	{
		return int4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the int4 column vector result of a matrix Multiplytiplication between an int4x4 matrix and an int4 column vector.</summary>

	inline static int4 Multiply(int4x4 a, int4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the int4x2 matrix result of a matrix Multiplytiplication between an int4x4 matrix and an int4x2 matrix.</summary>

	inline static int4x2 Multiply(int4x4 a, int4x2 b)
	{
		return int4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the int4x3 matrix result of a matrix Multiplytiplication between an int4x4 matrix and an int4x3 matrix.</summary>

	inline static int4x3 Multiply(int4x4 a, int4x3 b)
	{
		return int4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the int4x4 matrix result of a matrix Multiplytiplication between an int4x4 matrix and an int4x4 matrix.</summary>

	inline static int4x4 Multiply(int4x4 a, int4x4 b)
	{
		return int4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the unsigned value result of a matrix Multiplytiplication between a unsigned value and a unsigned value.</summary>

	inline static unsigned Multiply(unsigned a, unsigned b)
	{
		return a * b;
	}

	/// <summary>Returns the unsigned value result of a matrix Multiplytiplication between a unsigned2 row vector and a unsigned2 column vector.</summary>

	inline static unsigned Multiply(unsigned2 a, unsigned2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/// <summary>Returns the unsigned2 row vector result of a matrix Multiplytiplication between a unsigned2 row vector and a unsigned2x2 matrix.</summary>

	inline static unsigned2 Multiply(unsigned2 a, unsigned2x2 b)
	{
		return unsigned2(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y);
	}

	/// <summary>Returns the unsigned3 row vector result of a matrix Multiplytiplication between a unsigned2 row vector and a unsigned2x3 matrix.</summary>

	inline static unsigned3 Multiply(unsigned2 a, unsigned2x3 b)
	{
		return unsigned3(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y);
	}

	/// <summary>Returns the unsigned4 row vector result of a matrix Multiplytiplication between a unsigned2 row vector and a unsigned2x4 matrix.</summary>

	inline static unsigned4 Multiply(unsigned2 a, unsigned2x4 b)
	{
		return unsigned4(
			a.x * b.c0.x + a.y * b.c0.y,
			a.x * b.c1.x + a.y * b.c1.y,
			a.x * b.c2.x + a.y * b.c2.y,
			a.x * b.c3.x + a.y * b.c3.y);
	}

	/// <summary>Returns the unsigned value result of a matrix Multiplytiplication between a unsigned3 row vector and a unsigned3 column vector.</summary>

	inline static unsigned Multiply(unsigned3 a, unsigned3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/// <summary>Returns the unsigned2 row vector result of a matrix Multiplytiplication between a unsigned3 row vector and a unsigned3x2 matrix.</summary>

	inline static unsigned2 Multiply(unsigned3 a, unsigned3x2 b)
	{
		return unsigned2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z);
	}

	/// <summary>Returns the unsigned3 row vector result of a matrix Multiplytiplication between a unsigned3 row vector and a unsigned3x3 matrix.</summary>

	inline static unsigned3 Multiply(unsigned3 a, unsigned3x3 b)
	{
		return unsigned3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z);
	}

	/// <summary>Returns the unsigned4 row vector result of a matrix Multiplytiplication between a unsigned3 row vector and a unsigned3x4 matrix.</summary>

	inline static unsigned4 Multiply(unsigned3 a, unsigned3x4 b)
	{
		return unsigned4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z);
	}

	/// <summary>Returns the unsigned value result of a matrix Multiplytiplication between a unsigned4 row vector and a unsigned4 column vector.</summary>

	inline static unsigned Multiply(unsigned4 a, unsigned4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	/// <summary>Returns the unsigned2 row vector result of a matrix Multiplytiplication between a unsigned4 row vector and a unsigned4x2 matrix.</summary>

	inline static unsigned2 Multiply(unsigned4 a, unsigned4x2 b)
	{
		return unsigned2(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w);
	}

	/// <summary>Returns the unsigned3 row vector result of a matrix Multiplytiplication between a unsigned4 row vector and a unsigned4x3 matrix.</summary>

	inline static unsigned3 Multiply(unsigned4 a, unsigned4x3 b)
	{
		return unsigned3(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w);
	}

	/// <summary>Returns the unsigned4 row vector result of a matrix Multiplytiplication between a unsigned4 row vector and a unsigned4x4 matrix.</summary>

	inline static unsigned4 Multiply(unsigned4 a, unsigned4x4 b)
	{
		return unsigned4(
			a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
			a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
			a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w,
			a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z + a.w * b.c3.w);
	}

	/// <summary>Returns the unsigned2 column vector result of a matrix Multiplytiplication between a unsigned2x2 matrix and a unsigned2 column vector.</summary>

	inline static unsigned2 Multiply(unsigned2x2 a, unsigned2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the unsigned2x2 matrix result of a matrix Multiplytiplication between a unsigned2x2 matrix and a unsigned2x2 matrix.</summary>

	inline static unsigned2x2 Multiply(unsigned2x2 a, unsigned2x2 b)
	{
		return unsigned2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the unsigned2x3 matrix result of a matrix Multiplytiplication between a unsigned2x2 matrix and a unsigned2x3 matrix.</summary>

	inline static unsigned2x3 Multiply(unsigned2x2 a, unsigned2x3 b)
	{
		return unsigned2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the unsigned2x4 matrix result of a matrix Multiplytiplication between a unsigned2x2 matrix and a unsigned2x4 matrix.</summary>

	inline static unsigned2x4 Multiply(unsigned2x2 a, unsigned2x4 b)
	{
		return unsigned2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the unsigned2 column vector result of a matrix Multiplytiplication between a unsigned2x3 matrix and a unsigned3 column vector.</summary>

	inline static unsigned2 Multiply(unsigned2x3 a, unsigned3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the unsigned2x2 matrix result of a matrix Multiplytiplication between a unsigned2x3 matrix and a unsigned3x2 matrix.</summary>

	inline static unsigned2x2 Multiply(unsigned2x3 a, unsigned3x2 b)
	{
		return unsigned2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the unsigned2x3 matrix result of a matrix Multiplytiplication between a unsigned2x3 matrix and a unsigned3x3 matrix.</summary>

	inline static unsigned2x3 Multiply(unsigned2x3 a, unsigned3x3 b)
	{
		return unsigned2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the unsigned2x4 matrix result of a matrix Multiplytiplication between a unsigned2x3 matrix and a unsigned3x4 matrix.</summary>

	inline static unsigned2x4 Multiply(unsigned2x3 a, unsigned3x4 b)
	{
		return unsigned2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the unsigned2 column vector result of a matrix Multiplytiplication between a unsigned2x4 matrix and a unsigned4 column vector.</summary>

	inline static unsigned2 Multiply(unsigned2x4 a, unsigned4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the unsigned2x2 matrix result of a matrix Multiplytiplication between a unsigned2x4 matrix and a unsigned4x2 matrix.</summary>

	inline static unsigned2x2 Multiply(unsigned2x4 a, unsigned4x2 b)
	{
		return unsigned2x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the unsigned2x3 matrix result of a matrix Multiplytiplication between a unsigned2x4 matrix and a unsigned4x3 matrix.</summary>

	inline static unsigned2x3 Multiply(unsigned2x4 a, unsigned4x3 b)
	{
		return unsigned2x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the unsigned2x4 matrix result of a matrix Multiplytiplication between a unsigned2x4 matrix and a unsigned4x4 matrix.</summary>

	inline static unsigned2x4 Multiply(unsigned2x4 a, unsigned4x4 b)
	{
		return unsigned2x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the unsigned3 column vector result of a matrix Multiplytiplication between a unsigned3x2 matrix and a unsigned2 column vector.</summary>

	inline static unsigned3 Multiply(unsigned3x2 a, unsigned2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the unsigned3x2 matrix result of a matrix Multiplytiplication between a unsigned3x2 matrix and a unsigned2x2 matrix.</summary>

	inline static unsigned3x2 Multiply(unsigned3x2 a, unsigned2x2 b)
	{
		return unsigned3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the unsigned3x3 matrix result of a matrix Multiplytiplication between a unsigned3x2 matrix and a unsigned2x3 matrix.</summary>

	inline static unsigned3x3 Multiply(unsigned3x2 a, unsigned2x3 b)
	{
		return unsigned3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the unsigned3x4 matrix result of a matrix Multiplytiplication between a unsigned3x2 matrix and a unsigned2x4 matrix.</summary>

	inline static unsigned3x4 Multiply(unsigned3x2 a, unsigned2x4 b)
	{
		return unsigned3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the unsigned3 column vector result of a matrix Multiplytiplication between a unsigned3x3 matrix and a unsigned3 column vector.</summary>

	inline static unsigned3 Multiply(unsigned3x3 a, unsigned3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the unsigned3x2 matrix result of a matrix Multiplytiplication between a unsigned3x3 matrix and a unsigned3x2 matrix.</summary>

	inline static unsigned3x2 Multiply(unsigned3x3 a, unsigned3x2 b)
	{
		return unsigned3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the unsigned3x3 matrix result of a matrix Multiplytiplication between a unsigned3x3 matrix and a unsigned3x3 matrix.</summary>

	inline static unsigned3x3 Multiply(unsigned3x3 a, unsigned3x3 b)
	{
		return unsigned3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the unsigned3x4 matrix result of a matrix Multiplytiplication between a unsigned3x3 matrix and a unsigned3x4 matrix.</summary>

	inline static unsigned3x4 Multiply(unsigned3x3 a, unsigned3x4 b)
	{
		return unsigned3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the unsigned3 column vector result of a matrix Multiplytiplication between a unsigned3x4 matrix and a unsigned4 column vector.</summary>

	inline static unsigned3 Multiply(unsigned3x4 a, unsigned4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the unsigned3x2 matrix result of a matrix Multiplytiplication between a unsigned3x4 matrix and a unsigned4x2 matrix.</summary>

	inline static unsigned3x2 Multiply(unsigned3x4 a, unsigned4x2 b)
	{
		return unsigned3x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the unsigned3x3 matrix result of a matrix Multiplytiplication between a unsigned3x4 matrix and a unsigned4x3 matrix.</summary>

	inline static unsigned3x3 Multiply(unsigned3x4 a, unsigned4x3 b)
	{
		return unsigned3x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the unsigned3x4 matrix result of a matrix Multiplytiplication between a unsigned3x4 matrix and a unsigned4x4 matrix.</summary>

	inline static unsigned3x4 Multiply(unsigned3x4 a, unsigned4x4 b)
	{
		return unsigned3x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}

	/// <summary>Returns the unsigned4 column vector result of a matrix Multiplytiplication between a unsigned4x2 matrix and a unsigned2 column vector.</summary>

	inline static unsigned4 Multiply(unsigned4x2 a, unsigned2 b)
	{
		return a.c0 * b.x + a.c1 * b.y;
	}

	/// <summary>Returns the unsigned4x2 matrix result of a matrix Multiplytiplication between a unsigned4x2 matrix and a unsigned2x2 matrix.</summary>

	inline static unsigned4x2 Multiply(unsigned4x2 a, unsigned2x2 b)
	{
		return unsigned4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y);
	}

	/// <summary>Returns the unsigned4x3 matrix result of a matrix Multiplytiplication between a unsigned4x2 matrix and a unsigned2x3 matrix.</summary>

	inline static unsigned4x3 Multiply(unsigned4x2 a, unsigned2x3 b)
	{
		return unsigned4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y);
	}

	/// <summary>Returns the unsigned4x4 matrix result of a matrix Multiplytiplication between a unsigned4x2 matrix and a unsigned2x4 matrix.</summary>

	inline static unsigned4x4 Multiply(unsigned4x2 a, unsigned2x4 b)
	{
		return unsigned4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y,
			a.c0 * b.c1.x + a.c1 * b.c1.y,
			a.c0 * b.c2.x + a.c1 * b.c2.y,
			a.c0 * b.c3.x + a.c1 * b.c3.y);
	}

	/// <summary>Returns the unsigned4 column vector result of a matrix Multiplytiplication between a unsigned4x3 matrix and a unsigned3 column vector.</summary>

	inline static unsigned4 Multiply(unsigned4x3 a, unsigned3 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z;
	}

	/// <summary>Returns the unsigned4x2 matrix result of a matrix Multiplytiplication between a unsigned4x3 matrix and a unsigned3x2 matrix.</summary>

	inline static unsigned4x2 Multiply(unsigned4x3 a, unsigned3x2 b)
	{
		return unsigned4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z);
	}

	/// <summary>Returns the unsigned4x3 matrix result of a matrix Multiplytiplication between a unsigned4x3 matrix and a unsigned3x3 matrix.</summary>

	inline static unsigned4x3 Multiply(unsigned4x3 a, unsigned3x3 b)
	{
		return unsigned4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z);
	}

	/// <summary>Returns the unsigned4x4 matrix result of a matrix Multiplytiplication between a unsigned4x3 matrix and a unsigned3x4 matrix.</summary>

	inline static unsigned4x4 Multiply(unsigned4x3 a, unsigned3x4 b)
	{
		return unsigned4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z);
	}

	/// <summary>Returns the unsigned4 column vector result of a matrix Multiplytiplication between a unsigned4x4 matrix and a unsigned4 column vector.</summary>

	inline static unsigned4 Multiply(unsigned4x4 a, unsigned4 b)
	{
		return a.c0 * b.x + a.c1 * b.y + a.c2 * b.z + a.c3 * b.w;
	}

	/// <summary>Returns the unsigned4x2 matrix result of a matrix Multiplytiplication between a unsigned4x4 matrix and a unsigned4x2 matrix.</summary>

	inline static unsigned4x2 Multiply(unsigned4x4 a, unsigned4x2 b)
	{
		return unsigned4x2(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w);
	}

	/// <summary>Returns the unsigned4x3 matrix result of a matrix Multiplytiplication between a unsigned4x4 matrix and a unsigned4x3 matrix.</summary>

	inline static unsigned4x3 Multiply(unsigned4x4 a, unsigned4x3 b)
	{
		return unsigned4x3(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w);
	}

	/// <summary>Returns the unsigned4x4 matrix result of a matrix Multiplytiplication between a unsigned4x4 matrix and a unsigned4x4 matrix.</summary>

	inline static unsigned4x4 Multiply(unsigned4x4 a, unsigned4x4 b)
	{
		return unsigned4x4(
			a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
			a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
			a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
			a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
	}
#pragma endregion
#pragma region Matrix
	enum RotationOrder
	{
		/// <summary>Extrinsic rotation around the x axis, then around the y axis and finally around the z axis.</summary>
		XYZ,
		/// <summary>Extrinsic rotation around the x axis, then around the z axis and finally around the y axis.</summary>
		XZY,
		/// <summary>Extrinsic rotation around the y axis, then around the x axis and finally around the z axis.</summary>
		YXZ,
		/// <summary>Extrinsic rotation around the y axis, then around the z axis and finally around the x axis.</summary>
		YZX,
		/// <summary>Extrinsic rotation around the z axis, then around the x axis and finally around the y axis.</summary>
		ZXY,
		/// <summary>Extrinsic rotation around the z axis, then around the y axis and finally around the x axis.</summary>
		ZYX,
		/// <summary>Unity default rotation order. Extrinsic Rotation around the z axis, then around the x axis and finally around the y axis.</summary>
		Default = ZXY
	};
	inline static float2x2 Rotate2x2(float angle)
	{
		float s, c;
		s = sinf(angle);
		c = cosf(angle);
		return float2x2(c, -s,
			s, c);
	}

	/// <summary>Returns a float2x2 matrix representing a uniform scaling of both axes by s.</summary>
	inline static float2x2 Scale2x2(float s)
	{
		return float2x2(s, 0.0f,
			0.0f, s);
	}

	/// <summary>Returns a float2x2 matrix representing a non-uniform axis scaling by x and y.</summary>
	inline static float2x2 Scale2x2(float x, float y)
	{
		return float2x2(x, 0.0f,
			0.0f, y);
	}

	/// <summary>Returns a float2x2 matrix representing a non-uniform axis scaling by the components of the float2 vector v.</summary>
	inline static float2x2 Scale2x2(float2 v)
	{
		return Scale2x2(v.x, v.y);
	}

	inline static float3x3 Asfloat3x3(float4x4 f4x4)
	{
		float3x3 retVal;
		retVal.c0 = float3(f4x4.c0.z, f4x4.c0.z, f4x4.c0.z);
		retVal.c1 = float3(f4x4.c1.z, f4x4.c1.z, f4x4.c1.z);
		retVal.c2 = float3(f4x4.c2.z, f4x4.c2.z, f4x4.c2.z);
		return retVal;
	}

	/// <summary>Constructs a float3x3 matrix from a unit quaternion.</summary>
	inline static float3x3 Asfloat3x3(float4 v)
	{
		float3x3 retVal;
		float4 v2 = v + v;

		unsigned3 npn = unsigned3(0x80000000, 0x00000000, 0x80000000);
		unsigned3 nnp = unsigned3(0x80000000, 0x80000000, 0x00000000);
		unsigned3 pnn = unsigned3(0x00000000, 0x80000000, 0x80000000);
		retVal.c0 = v2.y * asfloat(asunsigned(float3(v.y, v.x, v.w)) ^ npn) - v2.z * asfloat(asunsigned(float3(v.z, v.w, v.x)) ^ pnn) + float3(1, 0, 0);
		retVal.c1 = v2.z * asfloat(asunsigned(float3(v.w, v.z, v.y)) ^ nnp) - v2.x * asfloat(asunsigned(float3(v.y, v.x, v.w)) ^ npn) + float3(0, 1, 0);
		retVal.c2 = v2.x * asfloat(asunsigned(float3(v.z, v.w, v.x)) ^ pnn) - v2.y * asfloat(asunsigned(float3(v.w, v.z, v.y)) ^ nnp) + float3(0, 0, 1);
		return retVal;
	}

	/// <summary>
		/// Returns a float3x3 matrix representing a rotation around a unit axis by an angle in radians.
		/// The rotation direction is clockwise when looking along the rotation axis towards the origin.
		/// </summary>
	inline static float3x3 AxisAngle3x3(float3 axis, float angle)
	{
		float sina, cosa;
		sina = sinf(angle);
		cosa = cosf(angle);
		float3 u = axis;
		float3 u_yzx = float3(u.y, u.z, u.x);
		float3 u_zxy = float3(u.z, u.x, u.y);
		float3 u_inv_cosa = u - u * cosa;  // u * (1.0f - cosa);
		float4 t = float4(u * sina, cosa);

		unsigned3 ppn = unsigned3(0x00000000, 0x00000000, 0x80000000);
		unsigned3 npp = unsigned3(0x80000000, 0x00000000, 0x00000000);
		unsigned3 pnp = unsigned3(0x00000000, 0x80000000, 0x00000000);

		return float3x3(
			u.x * u_inv_cosa + asfloat(asunsigned(float3(t.w, t.z, t.y)) ^ ppn),
			u.y * u_inv_cosa + asfloat(asunsigned(float3(t.z, t.w, t.x)) ^ npp),
			u.z * u_inv_cosa + asfloat(asunsigned(float3(t.y, t.x, t.w)) ^ pnp)
		);
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the x-axis, then the y-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float3x3 EulerXYZ3x3(float3 xyz)
	{
		// return Multiply(rotateZ(xyz.z), Multiply(rotateY(xyz.y), rotateX(xyz.x)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float3x3(
			c.y * c.z, c.z * s.x * s.y - c.x * s.z, c.x * c.z * s.y + s.x * s.z,
			c.y * s.z, c.x * c.z + s.x * s.y * s.z, c.x * s.y * s.z - c.z * s.x,
			-s.y, c.y * s.x, c.x * c.y
		);
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the x-axis, then the z-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float3x3 EulerXZY3x3(float3 xyz)
	{
		// return Multiply(rotateY(xyz.y), Multiply(rotateZ(xyz.z), rotateX(xyz.x))); }
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float3x3(
			c.y * c.z, s.x * s.y - c.x * c.y * s.z, c.x * s.y + c.y * s.x * s.z,
			s.z, c.x * c.z, -c.z * s.x,
			-c.z * s.y, c.y * s.x + c.x * s.y * s.z, c.x * c.y - s.x * s.y * s.z
		);
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the y-axis, then the x-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float3x3 EulerYXZ3x3(float3 xyz)
	{
		// return Multiply(rotateZ(xyz.z), Multiply(rotateX(xyz.x), rotateY(xyz.y)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float3x3(
			c.y * c.z - s.x * s.y * s.z, -c.x * s.z, c.z * s.y + c.y * s.x * s.z,
			c.z * s.x * s.y + c.y * s.z, c.x * c.z, s.y * s.z - c.y * c.z * s.x,
			-c.x * s.y, s.x, c.x * c.y
		);
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the y-axis, then the z-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float3x3 EulerYZX3x3(float3 xyz)
	{
		// return Multiply(rotateX(xyz.x), Multiply(rotateZ(xyz.z), rotateY(xyz.y)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float3x3(
			c.y * c.z, -s.z, c.z * s.y,
			s.x * s.y + c.x * c.y * s.z, c.x * c.z, c.x * s.y * s.z - c.y * s.x,
			c.y * s.x * s.z - c.x * s.y, c.z * s.x, c.x * c.y + s.x * s.y * s.z
		);
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the z-axis, then the x-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// This is the default order rotation order in Unity.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float3x3 EulerZXY3x3(float3 xyz)
	{
		// return Multiply(rotateY(xyz.y), Multiply(rotateX(xyz.x), rotateZ(xyz.z)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float3x3(
			c.y * c.z + s.x * s.y * s.z, c.z * s.x * s.y - c.y * s.z, c.x * s.y,
			c.x * s.z, c.x * c.z, -s.x,
			c.y * s.x * s.z - c.z * s.y, c.y * c.z * s.x + s.y * s.z, c.x * c.y
		);
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the z-axis, then the y-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float3x3 EulerZYX3x3(float3 xyz)
	{
		// return Multiply(rotateX(xyz.x), Multiply(rotateY(xyz.y), rotateZ(xyz.z)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float3x3(
			c.y * c.z, -c.y * s.z, s.y,
			c.z * s.x * s.y + c.x * s.z, c.x * c.z - s.x * s.y * s.z, -c.y * s.x,
			s.x * s.z - c.x * c.z * s.y, c.z * s.x + c.x * s.y * s.z, c.x * c.y
		);
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the x-axis, then the y-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float3x3 EulerXYZ3x3(float x, float y, float z) { return EulerXYZ3x3(float3(x, y, z)); }

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the x-axis, then the z-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float3x3 EulerXZY3x3(float x, float y, float z) { return EulerXZY3x3(float3(x, y, z)); }

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the y-axis, then the x-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float3x3 EulerYXZ3x3(float x, float y, float z) { return EulerYXZ3x3(float3(x, y, z)); }

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the y-axis, then the z-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float3x3 EulerYZX3x3(float x, float y, float z) { return EulerYZX3x3(float3(x, y, z)); }

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the z-axis, then the x-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// This is the default order rotation order in Unity.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float3x3 EulerZXY3x3(float x, float y, float z) { return EulerZXY3x3(float3(x, y, z)); }

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing a rotation around the z-axis, then the y-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float3x3 EulerZYX3x3(float x, float y, float z) { return EulerZYX3x3(float3(x, y, z)); }

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing 3 rotations around the principal axes in a given order.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// When the rotation order is known at compile time, it is recommended for performance reasons to use specific
	/// Euler rotation constructors such as EulerZXY(...).
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	/// <param name="order">The order in which the rotations are applied.</param>
	inline static float3x3 Euler3x3(float3 xyz, RotationOrder order = RotationOrder::Default)
	{
		switch (order)
		{
		case RotationOrder::XYZ:
			return EulerXYZ3x3(xyz);
		case RotationOrder::XZY:
			return EulerXZY3x3(xyz);
		case RotationOrder::YXZ:
			return EulerYXZ3x3(xyz);
		case RotationOrder::YZX:
			return EulerYZX3x3(xyz);
		case RotationOrder::ZXY:
			return EulerZXY3x3(xyz);
		case RotationOrder::ZYX:
			return EulerZYX3x3(xyz);
		default:
			return float3x3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	/// <summary>
	/// Returns a float3x3 rotation matrix constructed by first performing 3 rotations around the principal axes in a given order.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// When the rotation order is known at compile time, it is recommended for performance reasons to use specific
	/// Euler rotation constructors such as EulerZXY(...).
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>
	/// <param name="order">The order in which the rotations are applied.</param>
	inline static float3x3 Euler3x3(float x, float y, float z, RotationOrder order = RotationOrder::Default)
	{
		return Euler3x3(float3(x, y, z), order);
	}

	/// <summary>Returns a float4x4 matrix that rotates around the x-axis by a given number of radians.</summary>
	/// <param name="angle">The clockwise rotation angle when looking along the x-axis towards the origin in radians.</param>
	inline static float3x3 RotateX3x3(float angle)
	{
		// {{1, 0, 0}, {0, c_0, -s_0}, {0, s_0, c_0}}
		float s, c;
		SinCos(angle, &s, &c);
		return float3x3(1.0f, 0.0f, 0.0f,
			0.0f, c, -s,
			0.0f, s, c);
	}

	/// <summary>Returns a float4x4 matrix that rotates around the y-axis by a given number of radians.</summary>
	/// <param name="angle">The clockwise rotation angle when looking along the y-axis towards the origin in radians.</param>
	inline static float3x3 RotateY3x3(float angle)
	{
		// {{c_1, 0, s_1}, {0, 1, 0}, {-s_1, 0, c_1}}
		float s, c;
		SinCos(angle, &s, &c);
		return float3x3(c, 0.0f, s,
			0.0f, 1.0f, 0.0f,
			-s, 0.0f, c);
	}

	/// <summary>Returns a float4x4 matrix that rotates around the z-axis by a given number of radians.</summary>
	/// <param name="angle">The clockwise rotation angle when looking along the z-axis towards the origin in radians.</param>
	inline static float3x3 RotateZ3x3(float angle)
	{
		// {{c_2, -s_2, 0}, {s_2, c_2, 0}, {0, 0, 1}}
		float s, c;
		SinCos(angle, &s, &c);
		return float3x3(c, -s, 0.0f,
			s, c, 0.0f,
			0.0f, 0.0f, 1.0f);
	}

	//<summary>Returns a float3x3 matrix representing a uniform scaling of all axes by s.</summary>
	inline static float3x3 Scale3x3(float s)
	{
		return float3x3(s, 0.0f, 0.0f,
			0.0f, s, 0.0f,
			0.0f, 0.0f, s);
	}

	/// <summary>Returns a float3x3 matrix representing a non-uniform axis scaling by x, y and z.</summary>
	inline static float3x3 Scale3x3(float x, float y, float z)
	{
		return float3x3(x, 0.0f, 0.0f,
			0.0f, y, 0.0f,
			0.0f, 0.0f, z);
	}

	/// <summary>Returns a float3x3 matrix representing a non-uniform axis scaling by the components of the float3 vector v.</summary>
	inline static float3x3 Scale3x3(float3 v)
	{
		return Scale3x3(v.x, v.y, v.z);
	}

	/// <summary>
	/// Returns a float3x3 view rotation matrix given a unit length forward vector and a unit length up vector.
	/// The two input vectors are assumed to be unit length and not collinear.
	/// If these assumptions are not met use float3x3.LookRotationSafe instead.
	/// </summary>
	inline static float3x3 LookRotation(float3 forward, float3 up)
	{
		float3 t = Normalize(Cross(up, forward));
		return float3x3(t, Cross(forward, t), forward);
	}

	inline static float4x4 Asfloat4x4(float4 rotation, float3 translation)
	{
		float4x4 retVal;
		float3x3 rot = Asfloat3x3(rotation);
		retVal.c0 = float4(rot.c0, 0.0f);
		retVal.c1 = float4(rot.c1, 0.0f);
		retVal.c2 = float4(rot.c2, 0.0f);
		retVal.c3 = float4(translation, 1.0f);
		return retVal;
	}

	/// <summary>
		/// Returns a float4x4 matrix representing a rotation around a unit axis by an angle in radians.
		/// The rotation direction is clockwise when looking along the rotation axis towards the origin.
		/// </summary>
	inline static float4x4 AxisAngle4x4(float3 axis, float angle)
	{
		float sina, cosa;
		SinCos(angle, &sina, &cosa);

		float4 u = float4(axis, 0.0f);
		float4 u_yzx = float4(u.y, u.z, u.x, u.x);
		float4 u_zxy = float4(u.z, u.x, u.y, u.x);
		float4 u_inv_cosa = u - u * cosa;  // u * (1.0f - cosa);
		float4 t = float4(float3(u.x, u.y, u.z) * sina, cosa);

		unsigned4 ppnp = unsigned4(0x00000000, 0x00000000, 0x80000000, 0x00000000);
		unsigned4 nppp = unsigned4(0x80000000, 0x00000000, 0x00000000, 0x00000000);
		unsigned4 pnpp = unsigned4(0x00000000, 0x80000000, 0x00000000, 0x00000000);
		unsigned4 mask = unsigned4(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);

		return float4x4(
			u.x * u_inv_cosa + asfloat((asunsigned(float4(t.w, t.z, t.y, t.x)) ^ ppnp) & mask),
			u.y * u_inv_cosa + asfloat((asunsigned(float4(t.z, t.w, t.x, t.x)) ^ nppp) & mask),
			u.z * u_inv_cosa + asfloat((asunsigned(float4(t.y, t.x, t.w, t.x)) ^ pnpp) & mask),
			float4(0.0f, 0.0f, 0.0f, 1.0f)
		);

	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the x-axis, then the y-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float4x4 EulerXYZ4x4(float3 xyz)
	{
		// return Multiply(rotateZ(xyz.z), Multiply(rotateY(xyz.y), rotateX(xyz.x)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float4x4(
			c.y * c.z, c.z * s.x * s.y - c.x * s.z, c.x * c.z * s.y + s.x * s.z, 0.0f,
			c.y * s.z, c.x * c.z + s.x * s.y * s.z, c.x * s.y * s.z - c.z * s.x, 0.0f,
			-s.y, c.y * s.x, c.x * c.y, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the x-axis, then the z-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float4x4 EulerXZY4x4(float3 xyz)
	{
		// return Multiply(rotateY(xyz.y), Multiply(rotateZ(xyz.z), rotateX(xyz.x))); }
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float4x4(
			c.y * c.z, s.x * s.y - c.x * c.y * s.z, c.x * s.y + c.y * s.x * s.z, 0.0f,
			s.z, c.x * c.z, -c.z * s.x, 0.0f,
			-c.z * s.y, c.y * s.x + c.x * s.y * s.z, c.x * c.y - s.x * s.y * s.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the y-axis, then the x-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float4x4 EulerYXZ4x4(float3 xyz)
	{
		// return Multiply(rotateZ(xyz.z), Multiply(rotateX(xyz.x), rotateY(xyz.y)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float4x4(
			c.y * c.z - s.x * s.y * s.z, -c.x * s.z, c.z * s.y + c.y * s.x * s.z, 0.0f,
			c.z * s.x * s.y + c.y * s.z, c.x * c.z, s.y * s.z - c.y * c.z * s.x, 0.0f,
			-c.x * s.y, s.x, c.x * c.y, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the y-axis, then the z-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float4x4 EulerYZX4x4(float3 xyz)
	{
		// return Multiply(rotateX(xyz.x), Multiply(rotateZ(xyz.z), rotateY(xyz.y)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float4x4(
			c.y * c.z, -s.z, c.z * s.y, 0.0f,
			s.x * s.y + c.x * c.y * s.z, c.x * c.z, c.x * s.y * s.z - c.y * s.x, 0.0f,
			c.y * s.x * s.z - c.x * s.y, c.z * s.x, c.x * c.y + s.x * s.y * s.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the z-axis, then the x-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// This is the default order rotation order in Unity.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float4x4 EulerZXY4x4(float3 xyz)
	{
		// return Multiply(rotateY(xyz.y), Multiply(rotateX(xyz.x), rotateZ(xyz.z)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float4x4(
			c.y * c.z + s.x * s.y * s.z, c.z * s.x * s.y - c.y * s.z, c.x * s.y, 0.0f,
			c.x * s.z, c.x * c.z, -s.x, 0.0f,
			c.y * s.x * s.z - c.z * s.y, c.y * c.z * s.x + s.y * s.z, c.x * c.y, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the z-axis, then the y-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="xyz">A float3 vector containing the rotation angles around the x-, y- and z-axis measures in radians.</param>
	inline static float4x4 EulerZYX4x4(float3 xyz)
	{
		// return Multiply(rotateX(xyz.x), Multiply(rotateY(xyz.y), rotateZ(xyz.z)));
		float3 s, c;
		SinCos(xyz, &s, &c);
		return float4x4(
			c.y * c.z, -c.y * s.z, s.y, 0.0f,
			c.z * s.x * s.y + c.x * s.z, c.x * c.z - s.x * s.y * s.z, -c.y * s.x, 0.0f,
			s.x * s.z - c.x * c.z * s.y, c.z * s.x + c.x * s.y * s.z, c.x * c.y, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the x-axis, then the y-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float4x4 EulerXYZ4x4(float x, float y, float z) { return EulerXYZ4x4(float3(x, y, z)); }

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the x-axis, then the z-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float4x4 EulerXZY4x4(float x, float y, float z) { return EulerXZY4x4(float3(x, y, z)); }

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the y-axis, then the x-axis and finally the z-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float4x4 EulerYXZ4x4(float x, float y, float z) { return EulerYXZ4x4(float3(x, y, z)); }

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the y-axis, then the z-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float4x4 EulerYZX4x4(float x, float y, float z) { return EulerYZX4x4(float3(x, y, z)); }

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the z-axis, then the x-axis and finally the y-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// This is the default order rotation order in Unity.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float4x4 EulerZXY4x4(float x, float y, float z) { return EulerZXY4x4(float3(x, y, z)); }

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing a rotation around the z-axis, then the y-axis and finally the x-axis.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>

	inline static float4x4 EulerZYX4x4(float x, float y, float z) { return EulerZYX4x4(float3(x, y, z)); }

	inline static float4x4 Euler4x4(float3 xyz, RotationOrder order = RotationOrder::Default)
	{
		switch (order)
		{
		case RotationOrder::XYZ:
			return EulerXYZ4x4(xyz);
		case RotationOrder::XZY:
			return EulerXZY4x4(xyz);
		case RotationOrder::YXZ:
			return EulerYXZ4x4(xyz);
		case RotationOrder::YZX:
			return EulerYZX4x4(xyz);
		case RotationOrder::ZXY:
			return EulerZXY4x4(xyz);
		case RotationOrder::ZYX:
			return EulerZYX4x4(xyz);
		default:
			return float4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	/// <summary>
	/// Returns a float4x4 rotation matrix constructed by first performing 3 rotations around the principal axes in a given order.
	/// All rotation angles are in radians and clockwise when looking along the rotation axis towards the origin.
	/// When the rotation order is known at compile time, it is recommended for performance reasons to use specific
	/// Euler rotation constructors such as EulerZXY(...).
	/// </summary>
	/// <param name="x">The rotation angle around the x-axis in radians.</param>
	/// <param name="y">The rotation angle around the y-axis in radians.</param>
	/// <param name="z">The rotation angle around the z-axis in radians.</param>
	/// <param name="order">The order in which the rotations are applied.</param>

	inline static float4x4 Euler4x4(float x, float y, float z, RotationOrder order = RotationOrder::Default)
	{
		return Euler4x4(float3(x, y, z), order);
	}

	/// <summary>Returns a float4x4 matrix that rotates around the x-axis by a given number of radians.</summary>
	/// <param name="angle">The clockwise rotation angle when looking along the x-axis towards the origin in radians.</param>
	inline static float4x4 RotateX4x4(float angle)
	{
		// {{1, 0, 0}, {0, c_0, -s_0}, {0, s_0, c_0}}
		float s, c;
		SinCos(angle, &s, &c);
		return float4x4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, c, -s, 0.0f,
			0.0f, s, c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

	}

	/// <summary>Returns a float4x4 matrix that rotates around the y-axis by a given number of radians.</summary>
	/// <param name="angle">The clockwise rotation angle when looking along the y-axis towards the origin in radians.</param>
	inline static float4x4 RotateY4x4(float angle)
	{
		// {{c_1, 0, s_1}, {0, 1, 0}, {-s_1, 0, c_1}}
		float s, c;
		SinCos(angle, &s, &c);
		return float4x4(c, 0.0f, s, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-s, 0.0f, c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

	}

	/// <summary>Returns a float4x4 matrix that rotates around the z-axis by a given number of radians.</summary>
	/// <param name="angle">The clockwise rotation angle when looking along the z-axis towards the origin in radians.</param>
	inline static float4x4 RotateZ4x4(float angle)
	{
		// {{c_2, -s_2, 0}, {s_2, c_2, 0}, {0, 0, 1}}
		float s, c;
		SinCos(angle, &s, &c);
		return float4x4(c, -s, 0.0f, 0.0f,
			s, c, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

	}

	/// <summary>Returns a float4x4 scale matrix given 3 axis scales.</summary>
	inline static float4x4 Scale4x4(float s)
	{
		return float4x4(s, 0.0f, 0.0f, 0.0f,
			0.0f, s, 0.0f, 0.0f,
			0.0f, 0.0f, s, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	/// <summary>Returns a float4x4 scale matrix given a float3 vector containing the 3 axis scales.</summary>
	inline static float4x4 Scale4x4(float x, float y, float z)
	{
		return float4x4(x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	/// <summary>Returns a float4x4 scale matrix given a float3 vector containing the 3 axis scales.</summary>
	inline static float4x4 Scale4x4(float3 scales)
	{
		return Scale4x4(scales.x, scales.y, scales.z);
	}

	/// <summary>Returns a float4x4 translation matrix given a float3 translation vector.</summary>
	inline static float4x4 Translate4x4(float3 vector)
	{
		return float4x4(float4(1.0f, 0.0f, 0.0f, 0.0f),
			float4(0.0f, 1.0f, 0.0f, 0.0f),
			float4(0.0f, 0.0f, 1.0f, 0.0f),
			float4(vector.x, vector.y, vector.z, 1.0f));
	}

	/// <summary>
	/// Returns a float4x4 view matrix given an eye position, a target point and a unit length up vector.
	/// The up vector is assumed to be unit length, the eye and target points are assumed to be distinct and
	/// the vector between them is assumes to be collinear with the up vector.
	/// If these assumptions are not met use float4x4.LookRotationSafe instead.
	/// </summary>
	inline static float4x4 LookAt4x4(float3 eye, float3 target, float3 up)
	{
		float3x3 rot = LookRotation(Normalize(target - eye), up);

		float4x4 matrix;
		matrix.c0 = float4(rot.c0, 0.0F);
		matrix.c1 = float4(rot.c1, 0.0F);
		matrix.c2 = float4(rot.c2, 0.0F);
		matrix.c3 = float4(eye, 1.0F);
		return matrix;
	}

	/// <summary>
	/// Returns a float4x4 centered orthographic projection matrix.
	/// </summary>
	/// <param name="width">The width of the view volume.</param>
	/// <param name="height">The height of the view volume.</param>
	/// <param name="nearDist">The distance to the nearDist plane.</param>
	/// <param name="farDist">The distance to the farDist plane.</param>
	inline static float4x4 Ortho(float width, float height, float nearDist, float farDist)
	{
		float rcpdx = 1.0f / width;
		float rcpdy = 1.0f / height;
		float rcpdz = 1.0f / (farDist - nearDist);

		return float4x4(
			2.0f * rcpdx, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f * rcpdy, 0.0f, 0.0f,
			0.0f, 0.0f, -2.0f * rcpdz, -(farDist + nearDist) * rcpdz,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 off-center orthographic projection matrix.
	/// </summary>
	/// <param name="left">The minimum x-coordinate of the view volume.</param>
	/// <param name="right">The maximum x-coordinate of the view volume.</param>
	/// <param name="bottom">The minimum y-coordinate of the view volume.</param>
	/// <param name="top">The minimum y-coordinate of the view volume.</param>
	/// <param name="nearDist">The distance to the nearDist plane.</param>
	/// <param name="farDist">The distance to the farDist plane.</param>
	inline static float4x4 OrthoOffCenter(float left, float right, float bottom, float top, float nearDist, float farDist)
	{
		float rcpdx = 1.0f / (right - left);
		float rcpdy = 1.0f / (top - bottom);
		float rcpdz = 1.0f / (farDist - nearDist);

		return float4x4(
			2.0f * rcpdx, 0.0f, 0.0f, -(right + left) * rcpdx,
			0.0f, 2.0f * rcpdy, 0.0f, -(top + bottom) * rcpdy,
			0.0f, 0.0f, -2.0f * rcpdz, -(farDist + nearDist) * rcpdz,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 perspective projection matrix based on field of view.
	/// </summary>
	/// <param name="verticalFov">Vertical Field of view in radians.</param>
	/// <param name="aspect">X:Y aspect ratio.</param>
	/// <param name="nearDist">Distance to nearDist plane. Must be greater than zero.</param>
	/// <param name="farDist">Distance to farDist plane. Must be greater than zero.</param>
	inline static float4x4 PerspectiveFov(float verticalFov, float aspect, float nearDist, float farDist)
	{
		float cotangent = 1.0f / tan(verticalFov * 0.5f);
		float rcpdz = 1.0f / (nearDist - farDist);

		return float4x4(
			cotangent / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, cotangent, 0.0f, 0.0f,
			0.0f, 0.0f, (farDist + nearDist) * rcpdz, 2.0f * nearDist * farDist * rcpdz,
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 off-center perspective projection matrix.
	/// </summary>
	/// <param name="left">The x-coordinate of the left side of the clipping frustum at the nearDist plane.</param>
	/// <param name="right">The x-coordinate of the right side of the clipping frustum at the nearDist plane.</param>
	/// <param name="bottom">The y-coordinate of the bottom side of the clipping frustum at the nearDist plane.</param>
	/// <param name="top">The y-coordinate of the top side of the clipping frustum at the nearDist plane.</param>
	/// <param name="nearDist">Distance to the nearDist plane. Must be greater than zero.</param>
	/// <param name="farDist">Distance to the farDist plane. Must be greater than zero.</param>
	inline static float4x4 PerspectiveOffCenter(float left, float right, float bottom, float top, float nearDist, float farDist)
	{
		float rcpdz = 1.0f / (nearDist - farDist);
		float rcpWidth = 1.0f / (right - left);
		float rcpHeight = 1.0f / (top - bottom);

		return float4x4(
			2.0f * nearDist * rcpWidth, 0.0f, (left + right) * rcpWidth, 0.0f,
			0.0f, 2.0f * nearDist * rcpHeight, (bottom + top) * rcpHeight, 0.0f,
			0.0f, 0.0f, (farDist + nearDist) * rcpdz, 2.0f * nearDist * farDist * rcpdz,
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}

	/// <summary>
	/// Returns a float4x4 matrix representing a combined scale-, rotation- and translation transform.
	/// Equivalent to Multiply(translationTransform, Multiply(rotationTransform, scaleTransform)).
	/// </summary>
	inline static float4x4 TRS(float3 translation, float4 rotation, float3 scale)
	{
		float3x3 r = Asfloat3x3(rotation);
		return float4x4(float4(r.c0 * scale.x, 0.0f),
			float4(r.c1 * scale.y, 0.0f),
			float4(r.c2 * scale.z, 0.0f),
			float4(translation, 1.0f));
	}
#pragma endregion
}