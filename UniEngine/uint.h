#pragma once
namespace UniEngine {
#pragma region uint2
	struct uint2 {
		uint x, y;
		uint2() : x(0), y(0) {}
		uint2(uint x, uint y) : x(x), y(y) {}
		uint2(uint v) : x(v), y(v) {}
	};
	/// <summary>Returns the result of a componentwise multiplication operation on two uint2 vectors.</summary>

	inline static uint2 operator * (const uint2& lhs, const uint2& rhs) { return uint2(lhs.x * rhs.x, lhs.y * rhs.y); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint2 vector and a uint value.</summary>

	inline static uint2 operator * (const uint2& lhs, uint rhs) { return uint2(lhs.x * rhs, lhs.y * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint2 vector.</summary>

	inline static uint2 operator * (uint lhs, const uint2& rhs) { return uint2(lhs * rhs.x, lhs * rhs.y); }


	/// <summary>Returns the result of a componentwise addition operation on two uint2 vectors.</summary>

	inline static uint2 operator + (const uint2& lhs, const uint2& rhs) { return uint2(lhs.x + rhs.x, lhs.y + rhs.y); }

	/// <summary>Returns the result of a componentwise addition operation on a uint2 vector and a uint value.</summary>

	inline static uint2 operator + (const uint2& lhs, uint rhs) { return uint2(lhs.x + rhs, lhs.y + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint2 vector.</summary>

	inline static uint2 operator + (uint lhs, const uint2& rhs) { return uint2(lhs + rhs.x, lhs + rhs.y); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint2 vectors.</summary>

	inline static uint2 operator - (const uint2& lhs, const uint2& rhs) { return uint2(lhs.x - rhs.x, lhs.y - rhs.y); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint2 vector and a uint value.</summary>

	inline static uint2 operator - (const uint2& lhs, uint rhs) { return uint2(lhs.x - rhs, lhs.y - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint2 vector.</summary>

	inline static uint2 operator - (uint lhs, const uint2& rhs) { return uint2(lhs - rhs.x, lhs - rhs.y); }


	/// <summary>Returns the result of a componentwise division operation on two uint2 vectors.</summary>

	inline static uint2 operator / (const uint2& lhs, const uint2& rhs) { return uint2(lhs.x / rhs.x, lhs.y / rhs.y); }

	/// <summary>Returns the result of a componentwise division operation on a uint2 vector and a uint value.</summary>

	inline static uint2 operator / (const uint2& lhs, uint rhs) { return uint2(lhs.x / rhs, lhs.y / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint2 vector.</summary>

	inline static uint2 operator / (uint lhs, const uint2& rhs) { return uint2(lhs / rhs.x, lhs / rhs.y); }

	/// <summary>Returns the result of a componentwise increment operation on a uint2 vector.</summary>

	inline static uint2 operator ++ (uint2 val) { return uint2(++val.x, ++val.y); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint2 vector.</summary>

	inline static uint2 operator -- (uint2 val) { return uint2(--val.x, --val.y); }


	/// <summary>Returns the result of a componentwise less than operation on two uint2 vectors.</summary>

	inline static bool2 operator < (const uint2& lhs, const uint2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

	/// <summary>Returns the result of a componentwise less than operation on a uint2 vector and a uint value.</summary>

	inline static bool2 operator < (const uint2& lhs, uint rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint2 vector.</summary>

	inline static bool2 operator < (uint lhs, const uint2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint2 vectors.</summary>

	inline static bool2 operator <= (const uint2& lhs, const uint2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint2 vector and a uint value.</summary>

	inline static bool2 operator <= (const uint2& lhs, uint rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint2 vector.</summary>

	inline static bool2 operator <= (uint lhs, const uint2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint2 vectors.</summary>

	inline static bool2 operator > (const uint2& lhs, const uint2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint2 vector and a uint value.</summary>

	inline static bool2 operator > (const uint2& lhs, uint rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint2 vector.</summary>

	inline static bool2 operator > (uint lhs, const uint2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint2 vectors.</summary>

	inline static bool2 operator >= (const uint2& lhs, const uint2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint2 vector and a uint value.</summary>

	inline static bool2 operator >= (const uint2& lhs, uint rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint2 vector.</summary>

	inline static bool2 operator >= (uint lhs, const uint2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on two uint2 vectors.</summary>

	inline static bool2 operator == (const uint2& lhs, const uint2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on a uint2 vector and a uint value.</summary>

	inline static bool2 operator == (const uint2& lhs, uint rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint2 vector.</summary>

	inline static bool2 operator == (uint lhs, const uint2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint2 vectors.</summary>

	inline static bool2 operator != (const uint2& lhs, const uint2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint2 vector and a uint value.</summary>

	inline static bool2 operator != (const uint2& lhs, uint rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint2 vector.</summary>

	inline static bool2 operator != (uint lhs, const uint2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region uint2x2
	struct uint2x2
	{
		uint2 c0, c1;
		uint2x2() : c0(), c1() {}
		uint2x2(uint m00, uint m01,
			uint m10, uint m11) :c0(uint2(m00, m10)), c1(uint2(m01, m11)) {}
		uint2x2(uint2 c0, uint2 c1) : c0(c0), c1(c1) {}
		uint2x2(uint v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint2x2 matrices.</summary>

	inline static uint2x2 operator * (const uint2x2& lhs, const uint2x2& rhs) { return uint2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint2x2 matrix and a uint value.</summary>

	inline static uint2x2 operator * (const uint2x2& lhs, uint rhs) { return uint2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint2x2 matrix.</summary>

	inline static uint2x2 operator * (uint lhs, const uint2x2& rhs) { return uint2x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two uint2x2 matrices.</summary>

	inline static uint2x2 operator + (const uint2x2& lhs, const uint2x2& rhs) { return uint2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a uint2x2 matrix and a uint value.</summary>

	inline static uint2x2 operator + (const uint2x2& lhs, uint rhs) { return uint2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint2x2 matrix.</summary>

	inline static uint2x2 operator + (uint lhs, const uint2x2& rhs) { return uint2x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint2x2 matrices.</summary>

	inline static uint2x2 operator - (const uint2x2& lhs, const uint2x2& rhs) { return uint2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint2x2 matrix and a uint value.</summary>

	inline static uint2x2 operator - (const uint2x2& lhs, uint rhs) { return uint2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint2x2 matrix.</summary>

	inline static uint2x2 operator - (uint lhs, const uint2x2& rhs) { return uint2x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two uint2x2 matrices.</summary>

	inline static uint2x2 operator / (const uint2x2& lhs, const uint2x2& rhs) { return uint2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a uint2x2 matrix and a uint value.</summary>

	inline static uint2x2 operator / (const uint2x2& lhs, uint rhs) { return uint2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint2x2 matrix.</summary>

	inline static uint2x2 operator / (uint lhs, const uint2x2& rhs) { return uint2x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a uint2x2 matrix.</summary>

	inline static uint2x2 operator ++ (uint2x2 val) { return uint2x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint2x2 matrix.</summary>

	inline static uint2x2 operator -- (uint2x2 val) { return uint2x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two uint2x2 matrices.</summary>

	inline static bool2x2 operator < (const uint2x2& lhs, const uint2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a uint2x2 matrix and a uint value.</summary>

	inline static bool2x2 operator < (const uint2x2& lhs, uint rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint2x2 matrix.</summary>

	inline static bool2x2 operator < (uint lhs, const uint2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint2x2 matrices.</summary>

	inline static bool2x2 operator <= (const uint2x2& lhs, const uint2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint2x2 matrix and a uint value.</summary>

	inline static bool2x2 operator <= (const uint2x2& lhs, uint rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint2x2 matrix.</summary>

	inline static bool2x2 operator <= (uint lhs, const uint2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint2x2 matrices.</summary>

	inline static bool2x2 operator > (const uint2x2& lhs, const uint2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint2x2 matrix and a uint value.</summary>

	inline static bool2x2 operator > (const uint2x2& lhs, uint rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint2x2 matrix.</summary>

	inline static bool2x2 operator > (uint lhs, const uint2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint2x2 matrices.</summary>

	inline static bool2x2 operator >= (const uint2x2& lhs, const uint2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint2x2 matrix and a uint value.</summary>

	inline static bool2x2 operator >= (const uint2x2& lhs, uint rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint2x2 matrix.</summary>

	inline static bool2x2 operator >= (uint lhs, const uint2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on two uint2x2 matrices.</summary>

	inline static bool2x2 operator == (const uint2x2& lhs, const uint2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a uint2x2 matrix and a uint value.</summary>

	inline static bool2x2 operator == (const uint2x2& lhs, uint rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint2x2 matrix.</summary>

	inline static bool2x2 operator == (uint lhs, const uint2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint2x2 matrices.</summary>

	inline static bool2x2 operator != (const uint2x2& lhs, const uint2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint2x2 matrix and a uint value.</summary>

	inline static bool2x2 operator != (const uint2x2& lhs, uint rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint2x2 matrix.</summary>

	inline static bool2x2 operator != (uint lhs, const uint2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region uint2x3
	struct uint2x3
	{
		uint2 c0, c1, c2;
		uint2x3() : c0(), c1(), c2() {}
		uint2x3(uint m00, uint m01, uint m02,
			uint m10, uint m11, uint m12)
		{
			c0 = uint2(m00, m10);
			c1 = uint2(m01, m11);
			c2 = uint2(m02, m12);
		}
		uint2x3(uint2 c0, uint2 c1, uint2 c2) : c0(c0), c1(c1), c2(c2) {}
		uint2x3(uint v) : c0(v), c1(v), c2(v) {}
	};

	/// <summary>Returns the result of a componentwise multiplication operation on two uint2x3 matrices.</summary>

	inline static uint2x3 operator * (const uint2x3& lhs, const uint2x3& rhs) { return uint2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint2x3 matrix and a uint value.</summary>

	inline static uint2x3 operator * (const uint2x3& lhs, uint rhs) { return uint2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint2x3 matrix.</summary>

	inline static uint2x3 operator * (uint lhs, const uint2x3& rhs) { return uint2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two uint2x3 matrices.</summary>

	inline static uint2x3 operator + (const uint2x3& lhs, const uint2x3& rhs) { return uint2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a uint2x3 matrix and a uint value.</summary>

	inline static uint2x3 operator + (const uint2x3& lhs, uint rhs) { return uint2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint2x3 matrix.</summary>

	inline static uint2x3 operator + (uint lhs, const uint2x3& rhs) { return uint2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint2x3 matrices.</summary>

	inline static uint2x3 operator - (const uint2x3& lhs, const uint2x3& rhs) { return uint2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint2x3 matrix and a uint value.</summary>

	inline static uint2x3 operator - (const uint2x3& lhs, uint rhs) { return uint2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint2x3 matrix.</summary>

	inline static uint2x3 operator - (uint lhs, const uint2x3& rhs) { return uint2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two uint2x3 matrices.</summary>

	inline static uint2x3 operator / (const uint2x3& lhs, const uint2x3& rhs) { return uint2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a uint2x3 matrix and a uint value.</summary>

	inline static uint2x3 operator / (const uint2x3& lhs, uint rhs) { return uint2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint2x3 matrix.</summary>

	inline static uint2x3 operator / (uint lhs, const uint2x3& rhs) { return uint2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


	/// <summary>Returns the result of a componentwise increment operation on a uint2x3 matrix.</summary>

	inline static uint2x3 operator ++ (uint2x3 val) { return uint2x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint2x3 matrix.</summary>

	inline static uint2x3 operator -- (uint2x3 val) { return uint2x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two uint2x3 matrices.</summary>

	inline static bool2x3 operator < (const uint2x3& lhs, const uint2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a uint2x3 matrix and a uint value.</summary>

	inline static bool2x3 operator < (const uint2x3& lhs, uint rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint2x3 matrix.</summary>

	inline static bool2x3 operator < (uint lhs, const uint2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint2x3 matrices.</summary>

	inline static bool2x3 operator <= (const uint2x3& lhs, const uint2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint2x3 matrix and a uint value.</summary>

	inline static bool2x3 operator <= (const uint2x3& lhs, uint rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint2x3 matrix.</summary>

	inline static bool2x3 operator <= (uint lhs, const uint2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint2x3 matrices.</summary>

	inline static bool2x3 operator > (const uint2x3& lhs, const uint2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint2x3 matrix and a uint value.</summary>

	inline static bool2x3 operator > (const uint2x3& lhs, uint rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint2x3 matrix.</summary>

	inline static bool2x3 operator > (uint lhs, const uint2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint2x3 matrices.</summary>

	inline static bool2x3 operator >= (const uint2x3& lhs, const uint2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint2x3 matrix and a uint value.</summary>

	inline static bool2x3 operator >= (const uint2x3& lhs, uint rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint2x3 matrix.</summary>

	inline static bool2x3 operator >= (uint lhs, const uint2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on two uint2x3 matrices.</summary>

	inline static bool2x3 operator == (const uint2x3& lhs, const uint2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a uint2x3 matrix and a uint value.</summary>

	inline static bool2x3 operator == (const uint2x3& lhs, uint rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint2x3 matrix.</summary>

	inline static bool2x3 operator == (uint lhs, const uint2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint2x3 matrices.</summary>

	inline static bool2x3 operator != (const uint2x3& lhs, const uint2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint2x3 matrix and a uint value.</summary>

	inline static bool2x3 operator != (const uint2x3& lhs, uint rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint2x3 matrix.</summary>

	inline static bool2x3 operator != (uint lhs, const uint2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region uint2x4
	struct uint2x4
	{
		uint2 c0, c1, c2, c3;
		uint2x4() : c0(), c1(), c2(), c3() {}
		uint2x4(uint m00, uint m01, uint m02, uint m03,
			uint m10, uint m11, uint m12, uint m13)
		{
			c0 = uint2(m00, m10);
			c1 = uint2(m01, m11);
			c2 = uint2(m02, m12);
			c3 = uint2(m03, m13);
		}
		uint2x4(uint2 c0, uint2 c1, uint2 c2, uint2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		uint2x4(uint v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint2x4 matrices.</summary>

	inline static uint2x4 operator * (const uint2x4& lhs, const uint2x4& rhs) { return uint2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint2x4 matrix and a uint value.</summary>

	inline static uint2x4 operator * (const uint2x4& lhs, uint rhs) { return uint2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint2x4 matrix.</summary>

	inline static uint2x4 operator * (uint lhs, const uint2x4& rhs) { return uint2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two uint2x4 matrices.</summary>

	inline static uint2x4 operator + (const uint2x4& lhs, const uint2x4& rhs) { return uint2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a uint2x4 matrix and a uint value.</summary>

	inline static uint2x4 operator + (const uint2x4& lhs, uint rhs) { return uint2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint2x4 matrix.</summary>

	inline static uint2x4 operator + (uint lhs, const uint2x4& rhs) { return uint2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint2x4 matrices.</summary>

	inline static uint2x4 operator - (const uint2x4& lhs, const uint2x4& rhs) { return uint2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint2x4 matrix and a uint value.</summary>

	inline static uint2x4 operator - (const uint2x4& lhs, uint rhs) { return uint2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint2x4 matrix.</summary>

	inline static uint2x4 operator - (uint lhs, const uint2x4& rhs) { return uint2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two uint2x4 matrices.</summary>

	inline static uint2x4 operator / (const uint2x4& lhs, const uint2x4& rhs) { return uint2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a uint2x4 matrix and a uint value.</summary>

	inline static uint2x4 operator / (const uint2x4& lhs, uint rhs) { return uint2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint2x4 matrix.</summary>

	inline static uint2x4 operator / (uint lhs, const uint2x4& rhs) { return uint2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a uint2x4 matrix.</summary>

	inline static uint2x4 operator ++ (uint2x4 val) { return uint2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint2x4 matrix.</summary>

	inline static uint2x4 operator -- (uint2x4 val) { return uint2x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two uint2x4 matrices.</summary>

	inline static bool2x4 operator < (const uint2x4& lhs, const uint2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a uint2x4 matrix and a uint value.</summary>

	inline static bool2x4 operator < (const uint2x4& lhs, uint rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint2x4 matrix.</summary>

	inline static bool2x4 operator < (uint lhs, const uint2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint2x4 matrices.</summary>

	inline static bool2x4 operator <= (const uint2x4& lhs, const uint2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint2x4 matrix and a uint value.</summary>

	inline static bool2x4 operator <= (const uint2x4& lhs, uint rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint2x4 matrix.</summary>

	inline static bool2x4 operator <= (uint lhs, const uint2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint2x4 matrices.</summary>

	inline static bool2x4 operator > (const uint2x4& lhs, const uint2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint2x4 matrix and a uint value.</summary>

	inline static bool2x4 operator > (const uint2x4& lhs, uint rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint2x4 matrix.</summary>

	inline static bool2x4 operator > (uint lhs, const uint2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint2x4 matrices.</summary>

	inline static bool2x4 operator >= (const uint2x4& lhs, const uint2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint2x4 matrix and a uint value.</summary>

	inline static bool2x4 operator >= (const uint2x4& lhs, uint rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint2x4 matrix.</summary>

	inline static bool2x4 operator >= (uint lhs, const uint2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on two uint2x4 matrices.</summary>

	inline static bool2x4 operator == (const uint2x4& lhs, const uint2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a uint2x4 matrix and a uint value.</summary>

	inline static bool2x4 operator == (const uint2x4& lhs, uint rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint2x4 matrix.</summary>

	inline static bool2x4 operator == (uint lhs, const uint2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint2x4 matrices.</summary>

	inline static bool2x4 operator != (const uint2x4& lhs, const uint2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint2x4 matrix and a uint value.</summary>

	inline static bool2x4 operator != (const uint2x4& lhs, uint rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint2x4 matrix.</summary>

	inline static bool2x4 operator != (uint lhs, const uint2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region uint3
	struct uint3 {
		uint x, y, z;
		uint3() : x(0), y(0), z(0) {}
		uint3(uint x, uint y, uint z) : x(x), y(y), z(z) {}
		uint3(uint v) : x(v), y(v), z(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint3 vectors.</summary>

	inline static uint3 operator * (const uint3& lhs, const uint3& rhs) { return uint3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint3 vector and a uint value.</summary>

	inline static uint3 operator * (const uint3& lhs, uint rhs) { return uint3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint3 vector.</summary>

	inline static uint3 operator * (uint lhs, const uint3& rhs) { return uint3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


	/// <summary>Returns the result of a componentwise addition operation on two uint3 vectors.</summary>

	inline static uint3 operator + (const uint3& lhs, const uint3& rhs) { return uint3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

	/// <summary>Returns the result of a componentwise addition operation on a uint3 vector and a uint value.</summary>

	inline static uint3 operator + (const uint3& lhs, uint rhs) { return uint3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint3 vector.</summary>

	inline static uint3 operator + (uint lhs, const uint3& rhs) { return uint3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint3 vectors.</summary>

	inline static uint3 operator - (const uint3& lhs, const uint3& rhs) { return uint3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint3 vector and a uint value.</summary>

	inline static uint3 operator - (const uint3& lhs, uint rhs) { return uint3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint3 vector.</summary>

	inline static uint3 operator - (uint lhs, const uint3& rhs) { return uint3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


	/// <summary>Returns the result of a componentwise division operation on two uint3 vectors.</summary>

	inline static uint3 operator / (const uint3& lhs, const uint3& rhs) { return uint3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

	/// <summary>Returns the result of a componentwise division operation on a uint3 vector and a uint value.</summary>

	inline static uint3 operator / (const uint3& lhs, uint rhs) { return uint3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint3 vector.</summary>

	inline static uint3 operator / (uint lhs, const uint3& rhs) { return uint3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


	/// <summary>Returns the result of a componentwise increment operation on a uint3 vector.</summary>

	inline static uint3 operator ++ (uint3 val) { return uint3(++val.x, ++val.y, ++val.z); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint3 vector.</summary>

	inline static uint3 operator -- (uint3 val) { return uint3(--val.x, --val.y, --val.z); }


	/// <summary>Returns the result of a componentwise less than operation on two uint3 vectors.</summary>

	inline static bool3 operator < (const uint3& lhs, const uint3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

	/// <summary>Returns the result of a componentwise less than operation on a uint3 vector and a uint value.</summary>

	inline static bool3 operator < (const uint3& lhs, uint rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint3 vector.</summary>

	inline static bool3 operator < (uint lhs, const uint3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint3 vectors.</summary>

	inline static bool3 operator <= (const uint3& lhs, const uint3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint3 vector and a uint value.</summary>

	inline static bool3 operator <= (const uint3& lhs, uint rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint3 vector.</summary>

	inline static bool3 operator <= (uint lhs, const uint3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint3 vectors.</summary>

	inline static bool3 operator > (const uint3& lhs, const uint3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint3 vector and a uint value.</summary>

	inline static bool3 operator > (const uint3& lhs, uint rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint3 vector.</summary>

	inline static bool3 operator > (uint lhs, const uint3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint3 vectors.</summary>

	inline static bool3 operator >= (const uint3& lhs, const uint3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint3 vector and a uint value.</summary>

	inline static bool3 operator >= (const uint3& lhs, uint rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint3 vector.</summary>

	inline static bool3 operator >= (uint lhs, const uint3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }


	/// <summary>Returns the result of a componentwise equality operation on two uint3 vectors.</summary>

	inline static bool3 operator == (const uint3& lhs, const uint3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

	/// <summary>Returns the result of a componentwise equality operation on a uint3 vector and a uint value.</summary>

	inline static bool3 operator == (const uint3& lhs, uint rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint3 vector.</summary>

	inline static bool3 operator == (uint lhs, const uint3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint3 vectors.</summary>

	inline static bool3 operator != (const uint3& lhs, const uint3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint3 vector and a uint value.</summary>

	inline static bool3 operator != (const uint3& lhs, uint rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint3 vector.</summary>

	inline static bool3 operator != (uint lhs, const uint3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region uint3x2
	struct uint3x2
	{
		uint3 c0, c1;
		uint3x2() : c0(), c1() {}
		uint3x2(uint m00, uint m01,
			uint m10, uint m11,
			uint m20, uint m21)
		{
			c0 = uint3(m00, m10, m20);
			c1 = uint3(m01, m11, m21);
		}

		uint3x2(uint3 c0, uint3 c1) : c0(c0), c1(c1) {}
		uint3x2(uint v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint3x2 matrices.</summary>

	inline static uint3x2 operator * (const uint3x2& lhs, const uint3x2& rhs) { return uint3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint3x2 matrix and a uint value.</summary>

	inline static uint3x2 operator * (const uint3x2& lhs, uint rhs) { return uint3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint3x2 matrix.</summary>

	inline static uint3x2 operator * (uint lhs, const uint3x2& rhs) { return uint3x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two uint3x2 matrices.</summary>

	inline static uint3x2 operator + (const uint3x2& lhs, const uint3x2& rhs) { return uint3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a uint3x2 matrix and a uint value.</summary>

	inline static uint3x2 operator + (const uint3x2& lhs, uint rhs) { return uint3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint3x2 matrix.</summary>

	inline static uint3x2 operator + (uint lhs, const uint3x2& rhs) { return uint3x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint3x2 matrices.</summary>

	inline static uint3x2 operator - (const uint3x2& lhs, const uint3x2& rhs) { return uint3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint3x2 matrix and a uint value.</summary>

	inline static uint3x2 operator - (const uint3x2& lhs, uint rhs) { return uint3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint3x2 matrix.</summary>

	inline static uint3x2 operator - (uint lhs, const uint3x2& rhs) { return uint3x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two uint3x2 matrices.</summary>

	inline static uint3x2 operator / (const uint3x2& lhs, const uint3x2& rhs) { return uint3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a uint3x2 matrix and a uint value.</summary>

	inline static uint3x2 operator / (const uint3x2& lhs, uint rhs) { return uint3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint3x2 matrix.</summary>

	inline static uint3x2 operator / (uint lhs, const uint3x2& rhs) { return uint3x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a uint3x2 matrix.</summary>

	inline static uint3x2 operator ++ (uint3x2 val) { return uint3x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint3x2 matrix.</summary>

	inline static uint3x2 operator -- (uint3x2 val) { return uint3x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two uint3x2 matrices.</summary>

	inline static bool3x2 operator < (const uint3x2& lhs, const uint3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a uint3x2 matrix and a uint value.</summary>

	inline static bool3x2 operator < (const uint3x2& lhs, uint rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint3x2 matrix.</summary>

	inline static bool3x2 operator < (uint lhs, const uint3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint3x2 matrices.</summary>

	inline static bool3x2 operator <= (const uint3x2& lhs, const uint3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint3x2 matrix and a uint value.</summary>

	inline static bool3x2 operator <= (const uint3x2& lhs, uint rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint3x2 matrix.</summary>

	inline static bool3x2 operator <= (uint lhs, const uint3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint3x2 matrices.</summary>

	inline static bool3x2 operator > (const uint3x2& lhs, const uint3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint3x2 matrix and a uint value.</summary>

	inline static bool3x2 operator > (const uint3x2& lhs, uint rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint3x2 matrix.</summary>

	inline static bool3x2 operator > (uint lhs, const uint3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint3x2 matrices.</summary>

	inline static bool3x2 operator >= (const uint3x2& lhs, const uint3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint3x2 matrix and a uint value.</summary>

	inline static bool3x2 operator >= (const uint3x2& lhs, uint rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint3x2 matrix.</summary>

	inline static bool3x2 operator >= (uint lhs, const uint3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on two uint3x2 matrices.</summary>

	inline static bool3x2 operator == (const uint3x2& lhs, const uint3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a uint3x2 matrix and a uint value.</summary>

	inline static bool3x2 operator == (const uint3x2& lhs, uint rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint3x2 matrix.</summary>

	inline static bool3x2 operator == (uint lhs, const uint3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint3x2 matrices.</summary>

	inline static bool3x2 operator != (const uint3x2& lhs, const uint3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint3x2 matrix and a uint value.</summary>

	inline static bool3x2 operator != (const uint3x2& lhs, uint rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint3x2 matrix.</summary>

	inline static bool3x2 operator != (uint lhs, const uint3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region uint3x3
	struct uint3x3
	{
		uint3 c0, c1, c2;
		uint3x3() : c0(), c1(), c2() {}
		uint3x3(uint m00, uint m01, uint m02,
			uint m10, uint m11, uint m12,
			uint m20, uint m21, uint m22)
		{
			c0 = uint3(m00, m10, m20);
			c1 = uint3(m01, m11, m21);
			c2 = uint3(m02, m12, m22);
		}
		uint3x3(uint3 c0, uint3 c1, uint3 c2) : c0(c0), c1(c1), c2(c2) {}
		uint3x3(uint v) : c0(v), c1(v), c2(v) {}

	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint3x3 matrices.</summary>

	inline static uint3x3 operator * (const uint3x3& lhs, const uint3x3& rhs) { return uint3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint3x3 matrix and a uint value.</summary>

	inline static uint3x3 operator * (const uint3x3& lhs, uint rhs) { return uint3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint3x3 matrix.</summary>

	inline static uint3x3 operator * (uint lhs, const uint3x3& rhs) { return uint3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two uint3x3 matrices.</summary>

	inline static uint3x3 operator + (const uint3x3& lhs, const uint3x3& rhs) { return uint3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a uint3x3 matrix and a uint value.</summary>

	inline static uint3x3 operator + (const uint3x3& lhs, uint rhs) { return uint3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint3x3 matrix.</summary>

	inline static uint3x3 operator + (uint lhs, const uint3x3& rhs) { return uint3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint3x3 matrices.</summary>

	inline static uint3x3 operator - (const uint3x3& lhs, const uint3x3& rhs) { return uint3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint3x3 matrix and a uint value.</summary>

	inline static uint3x3 operator - (const uint3x3& lhs, uint rhs) { return uint3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint3x3 matrix.</summary>

	inline static uint3x3 operator - (uint lhs, const uint3x3& rhs) { return uint3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two uint3x3 matrices.</summary>

	inline static uint3x3 operator / (const uint3x3& lhs, const uint3x3& rhs) { return uint3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a uint3x3 matrix and a uint value.</summary>

	inline static uint3x3 operator / (const uint3x3& lhs, uint rhs) { return uint3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint3x3 matrix.</summary>

	inline static uint3x3 operator / (uint lhs, const uint3x3& rhs) { return uint3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a uint3x3 matrix.</summary>

	inline static uint3x3 operator ++ (uint3x3 val) { return uint3x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint3x3 matrix.</summary>

	inline static uint3x3 operator -- (uint3x3 val) { return uint3x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two uint3x3 matrices.</summary>

	inline static bool3x3 operator < (const uint3x3& lhs, const uint3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a uint3x3 matrix and a uint value.</summary>

	inline static bool3x3 operator < (const uint3x3& lhs, uint rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint3x3 matrix.</summary>

	inline static bool3x3 operator < (uint lhs, const uint3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint3x3 matrices.</summary>

	inline static bool3x3 operator <= (const uint3x3& lhs, const uint3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint3x3 matrix and a uint value.</summary>

	inline static bool3x3 operator <= (const uint3x3& lhs, uint rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint3x3 matrix.</summary>

	inline static bool3x3 operator <= (uint lhs, const uint3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint3x3 matrices.</summary>

	inline static bool3x3 operator > (const uint3x3& lhs, const uint3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint3x3 matrix and a uint value.</summary>

	inline static bool3x3 operator > (const uint3x3& lhs, uint rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint3x3 matrix.</summary>

	inline static bool3x3 operator > (uint lhs, const uint3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint3x3 matrices.</summary>

	inline static bool3x3 operator >= (const uint3x3& lhs, const uint3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint3x3 matrix and a uint value.</summary>

	inline static bool3x3 operator >= (const uint3x3& lhs, uint rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint3x3 matrix.</summary>

	inline static bool3x3 operator >= (uint lhs, const uint3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on two uint3x3 matrices.</summary>

	inline static bool3x3 operator == (const uint3x3& lhs, const uint3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a uint3x3 matrix and a uint value.</summary>

	inline static bool3x3 operator == (const uint3x3& lhs, uint rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint3x3 matrix.</summary>

	inline static bool3x3 operator == (uint lhs, const uint3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint3x3 matrices.</summary>

	inline static bool3x3 operator != (const uint3x3& lhs, const uint3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint3x3 matrix and a uint value.</summary>

	inline static bool3x3 operator != (const uint3x3& lhs, uint rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint3x3 matrix.</summary>

	inline static bool3x3 operator != (uint lhs, const uint3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region uint3x4
	struct uint3x4
	{
		uint3 c0, c1, c2, c3;
		uint3x4() : c0(), c1(), c2(), c3() {}
		uint3x4(uint m00, uint m01, uint m02, uint m03,
			uint m10, uint m11, uint m12, uint m13,
			uint m20, uint m21, uint m22, uint m23)
		{
			c0 = uint3(m00, m10, m20);
			c1 = uint3(m01, m11, m21);
			c2 = uint3(m02, m12, m22);
			c3 = uint3(m03, m13, m23);
		}
		uint3x4(uint3 c0, uint3 c1, uint3 c2, uint3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		uint3x4(uint v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint3x4 matrices.</summary>

	inline static uint3x4 operator * (const uint3x4& lhs, const uint3x4& rhs) { return uint3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint3x4 matrix and a uint value.</summary>

	inline static uint3x4 operator * (const uint3x4& lhs, uint rhs) { return uint3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint3x4 matrix.</summary>

	inline static uint3x4 operator * (uint lhs, const uint3x4& rhs) { return uint3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two uint3x4 matrices.</summary>

	inline static uint3x4 operator + (const uint3x4& lhs, const uint3x4& rhs) { return uint3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a uint3x4 matrix and a uint value.</summary>

	inline static uint3x4 operator + (const uint3x4& lhs, uint rhs) { return uint3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint3x4 matrix.</summary>

	inline static uint3x4 operator + (uint lhs, const uint3x4& rhs) { return uint3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint3x4 matrices.</summary>

	inline static uint3x4 operator - (const uint3x4& lhs, const uint3x4& rhs) { return uint3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint3x4 matrix and a uint value.</summary>

	inline static uint3x4 operator - (const uint3x4& lhs, uint rhs) { return uint3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint3x4 matrix.</summary>

	inline static uint3x4 operator - (uint lhs, const uint3x4& rhs) { return uint3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two uint3x4 matrices.</summary>

	inline static uint3x4 operator / (const uint3x4& lhs, const uint3x4& rhs) { return uint3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a uint3x4 matrix and a uint value.</summary>

	inline static uint3x4 operator / (const uint3x4& lhs, uint rhs) { return uint3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint3x4 matrix.</summary>

	inline static uint3x4 operator / (uint lhs, const uint3x4& rhs) { return uint3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

	/// <summary>Returns the result of a componentwise increment operation on a uint3x4 matrix.</summary>

	inline static uint3x4 operator ++ (uint3x4 val) { return uint3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint3x4 matrix.</summary>

	inline static uint3x4 operator -- (uint3x4 val) { return uint3x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two uint3x4 matrices.</summary>

	inline static bool3x4 operator < (const uint3x4& lhs, const uint3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a uint3x4 matrix and a uint value.</summary>

	inline static bool3x4 operator < (const uint3x4& lhs, uint rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint3x4 matrix.</summary>

	inline static bool3x4 operator < (uint lhs, const uint3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint3x4 matrices.</summary>

	inline static bool3x4 operator <= (const uint3x4& lhs, const uint3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint3x4 matrix and a uint value.</summary>

	inline static bool3x4 operator <= (const uint3x4& lhs, uint rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint3x4 matrix.</summary>

	inline static bool3x4 operator <= (uint lhs, const uint3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint3x4 matrices.</summary>

	inline static bool3x4 operator > (const uint3x4& lhs, const uint3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint3x4 matrix and a uint value.</summary>

	inline static bool3x4 operator > (const uint3x4& lhs, uint rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint3x4 matrix.</summary>

	inline static bool3x4 operator > (uint lhs, const uint3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint3x4 matrices.</summary>

	inline static bool3x4 operator >= (const uint3x4& lhs, const uint3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint3x4 matrix and a uint value.</summary>

	inline static bool3x4 operator >= (const uint3x4& lhs, uint rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint3x4 matrix.</summary>

	inline static bool3x4 operator >= (uint lhs, const uint3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two uint3x4 matrices.</summary>

	inline static bool3x4 operator == (const uint3x4& lhs, const uint3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a uint3x4 matrix and a uint value.</summary>

	inline static bool3x4 operator == (const uint3x4& lhs, uint rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint3x4 matrix.</summary>

	inline static bool3x4 operator == (uint lhs, const uint3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint3x4 matrices.</summary>

	inline static bool3x4 operator != (const uint3x4& lhs, const uint3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint3x4 matrix and a uint value.</summary>

	inline static bool3x4 operator != (const uint3x4& lhs, uint rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint3x4 matrix.</summary>

	inline static bool3x4 operator != (uint lhs, const uint3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region uint4
	struct uint4 {
		uint x, y, z, w;
		uint4() : x(0), y(0), z(0), w(0) {}
		uint4(uint x, uint y, uint z, uint w) : x(x), y(y), z(z), w(w) {}
		uint4(uint v) : x(v), y(v), z(v), w(v) {}
		uint4(uint3 xyz, uint w) : w(w)
		{
			x = xyz.x;
			y = xyz.y;
			z = xyz.z;
		}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint4 vectors.</summary>

	inline static uint4 operator * (const uint4& lhs, const uint4& rhs) { return uint4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint4 vector and a uint value.</summary>

	inline static uint4 operator * (const uint4& lhs, uint rhs) { return uint4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint4 vector.</summary>

	inline static uint4 operator * (uint lhs, const uint4& rhs) { return uint4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


	/// <summary>Returns the result of a componentwise addition operation on two uint4 vectors.</summary>

	inline static uint4 operator + (const uint4& lhs, const uint4& rhs) { return uint4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

	/// <summary>Returns the result of a componentwise addition operation on a uint4 vector and a uint value.</summary>

	inline static uint4 operator + (const uint4& lhs, uint rhs) { return uint4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint4 vector.</summary>

	inline static uint4 operator + (uint lhs, const uint4& rhs) { return uint4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint4 vectors.</summary>

	inline static uint4 operator - (const uint4& lhs, const uint4& rhs) { return uint4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint4 vector and a uint value.</summary>

	inline static uint4 operator - (const uint4& lhs, uint rhs) { return uint4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint4 vector.</summary>

	inline static uint4 operator - (uint lhs, const uint4& rhs) { return uint4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


	/// <summary>Returns the result of a componentwise division operation on two uint4 vectors.</summary>

	inline static uint4 operator / (const uint4& lhs, const uint4& rhs) { return uint4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

	/// <summary>Returns the result of a componentwise division operation on a uint4 vector and a uint value.</summary>

	inline static uint4 operator / (const uint4& lhs, uint rhs) { return uint4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint4 vector.</summary>

	inline static uint4 operator / (uint lhs, const uint4& rhs) { return uint4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

	/// <summary>Returns the result of a componentwise increment operation on a uint4 vector.</summary>

	inline static uint4 operator ++ (uint4 val) { return uint4(++val.x, ++val.y, ++val.z, ++val.w); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint4 vector.</summary>

	inline static uint4 operator -- (uint4 val) { return uint4(--val.x, --val.y, --val.z, --val.w); }


	/// <summary>Returns the result of a componentwise less than operation on two uint4 vectors.</summary>

	inline static bool4 operator < (const uint4& lhs, const uint4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

	/// <summary>Returns the result of a componentwise less than operation on a uint4 vector and a uint value.</summary>

	inline static bool4 operator < (const uint4& lhs, uint rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint4 vector.</summary>

	inline static bool4 operator < (uint lhs, const uint4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint4 vectors.</summary>

	inline static bool4 operator <= (const uint4& lhs, const uint4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint4 vector and a uint value.</summary>

	inline static bool4 operator <= (const uint4& lhs, uint rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint4 vector.</summary>

	inline static bool4 operator <= (uint lhs, const uint4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint4 vectors.</summary>

	inline static bool4 operator > (const uint4& lhs, const uint4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint4 vector and a uint value.</summary>

	inline static bool4 operator > (const uint4& lhs, uint rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint4 vector.</summary>

	inline static bool4 operator > (uint lhs, const uint4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint4 vectors.</summary>

	inline static bool4 operator >= (const uint4& lhs, const uint4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint4 vector and a uint value.</summary>

	inline static bool4 operator >= (const uint4& lhs, uint rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint4 vector.</summary>

	inline static bool4 operator >= (uint lhs, const uint4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on two uint4 vectors.</summary>

	inline static bool4 operator == (const uint4& lhs, const uint4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on a uint4 vector and a uint value.</summary>

	inline static bool4 operator == (const uint4& lhs, uint rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint4 vector.</summary>

	inline static bool4 operator == (uint lhs, const uint4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint4 vectors.</summary>

	inline static bool4 operator != (const uint4& lhs, const uint4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint4 vector and a uint value.</summary>

	inline static bool4 operator != (const uint4& lhs, uint rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint4 vector.</summary>

	inline static bool4 operator != (uint lhs, const uint4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region uint4x2
	struct uint4x2
	{
		uint4 c0, c1;
		uint4x2() : c0(), c1() {}
		uint4x2(uint m00, uint m01,
			uint m10, uint m11,
			uint m20, uint m21,
			uint m30, uint m31)
		{
			c0 = uint4(m00, m10, m20, m30);
			c1 = uint4(m01, m11, m21, m31);
		}
		uint4x2(uint4 c0, uint4 c1) : c0(c0), c1(c1) {}
		uint4x2(uint v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint4x2 matrices.</summary>

	inline static uint4x2 operator * (const uint4x2& lhs, const uint4x2& rhs) { return uint4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint4x2 matrix and a uint value.</summary>

	inline static uint4x2 operator * (const uint4x2& lhs, uint rhs) { return uint4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint4x2 matrix.</summary>

	inline static uint4x2 operator * (uint lhs, const uint4x2& rhs) { return uint4x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two uint4x2 matrices.</summary>

	inline static uint4x2 operator + (const uint4x2& lhs, const uint4x2& rhs) { return uint4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a uint4x2 matrix and a uint value.</summary>

	inline static uint4x2 operator + (const uint4x2& lhs, uint rhs) { return uint4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint4x2 matrix.</summary>

	inline static uint4x2 operator + (uint lhs, const uint4x2& rhs) { return uint4x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint4x2 matrices.</summary>

	inline static uint4x2 operator - (const uint4x2& lhs, const uint4x2& rhs) { return uint4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint4x2 matrix and a uint value.</summary>

	inline static uint4x2 operator - (const uint4x2& lhs, uint rhs) { return uint4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint4x2 matrix.</summary>

	inline static uint4x2 operator - (uint lhs, const uint4x2& rhs) { return uint4x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two uint4x2 matrices.</summary>

	inline static uint4x2 operator / (const uint4x2& lhs, const uint4x2& rhs) { return uint4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a uint4x2 matrix and a uint value.</summary>

	inline static uint4x2 operator / (const uint4x2& lhs, uint rhs) { return uint4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint4x2 matrix.</summary>

	inline static uint4x2 operator / (uint lhs, const uint4x2& rhs) { return uint4x2(lhs / rhs.c0, lhs / rhs.c1); }

	/// <summary>Returns the result of a componentwise increment operation on a uint4x2 matrix.</summary>

	inline static uint4x2 operator ++ (uint4x2 val) { return uint4x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint4x2 matrix.</summary>

	inline static uint4x2 operator -- (uint4x2 val) { return uint4x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two uint4x2 matrices.</summary>

	inline static bool4x2 operator < (const uint4x2& lhs, const uint4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a uint4x2 matrix and a uint value.</summary>

	inline static bool4x2 operator < (const uint4x2& lhs, uint rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint4x2 matrix.</summary>

	inline static bool4x2 operator < (uint lhs, const uint4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint4x2 matrices.</summary>

	inline static bool4x2 operator <= (const uint4x2& lhs, const uint4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint4x2 matrix and a uint value.</summary>

	inline static bool4x2 operator <= (const uint4x2& lhs, uint rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint4x2 matrix.</summary>

	inline static bool4x2 operator <= (uint lhs, const uint4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint4x2 matrices.</summary>

	inline static bool4x2 operator > (const uint4x2& lhs, const uint4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint4x2 matrix and a uint value.</summary>

	inline static bool4x2 operator > (const uint4x2& lhs, uint rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint4x2 matrix.</summary>

	inline static bool4x2 operator > (uint lhs, const uint4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint4x2 matrices.</summary>

	inline static bool4x2 operator >= (const uint4x2& lhs, const uint4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint4x2 matrix and a uint value.</summary>

	inline static bool4x2 operator >= (const uint4x2& lhs, uint rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint4x2 matrix.</summary>

	inline static bool4x2 operator >= (uint lhs, const uint4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two uint4x2 matrices.</summary>

	inline static bool4x2 operator == (const uint4x2& lhs, const uint4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a uint4x2 matrix and a uint value.</summary>

	inline static bool4x2 operator == (const uint4x2& lhs, uint rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint4x2 matrix.</summary>

	inline static bool4x2 operator == (uint lhs, const uint4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint4x2 matrices.</summary>

	inline static bool4x2 operator != (const uint4x2& lhs, const uint4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint4x2 matrix and a uint value.</summary>

	inline static bool4x2 operator != (const uint4x2& lhs, uint rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint4x2 matrix.</summary>

	inline static bool4x2 operator != (uint lhs, const uint4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region uint4x3
	struct uint4x3
	{
		uint4 c0, c1, c2;
		uint4x3() : c0(), c1(), c2() {}
		uint4x3(uint m00, uint m01, uint m02,
			uint m10, uint m11, uint m12,
			uint m20, uint m21, uint m22,
			uint m30, uint m31, uint m32)
		{
			c0 = uint4(m00, m10, m20, m30);
			c1 = uint4(m01, m11, m21, m31);
			c2 = uint4(m02, m12, m22, m32);
		}
		uint4x3(uint4 c0, uint4 c1, uint4 c2) : c0(c0), c1(c1), c2(c2) {}
		uint4x3(uint v) : c0(v), c1(v), c2(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint4x3 matrices.</summary>

	inline static uint4x3 operator * (const uint4x3& lhs, const uint4x3& rhs) { return uint4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint4x3 matrix and a uint value.</summary>

	inline static uint4x3 operator * (const uint4x3& lhs, uint rhs) { return uint4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint4x3 matrix.</summary>

	inline static uint4x3 operator * (uint lhs, const uint4x3& rhs) { return uint4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two uint4x3 matrices.</summary>

	inline static uint4x3 operator + (const uint4x3& lhs, const uint4x3& rhs) { return uint4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a uint4x3 matrix and a uint value.</summary>

	inline static uint4x3 operator + (const uint4x3& lhs, uint rhs) { return uint4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint4x3 matrix.</summary>

	inline static uint4x3 operator + (uint lhs, const uint4x3& rhs) { return uint4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint4x3 matrices.</summary>

	inline static uint4x3 operator - (const uint4x3& lhs, const uint4x3& rhs) { return uint4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint4x3 matrix and a uint value.</summary>

	inline static uint4x3 operator - (const uint4x3& lhs, uint rhs) { return uint4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint4x3 matrix.</summary>

	inline static uint4x3 operator - (uint lhs, const uint4x3& rhs) { return uint4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two uint4x3 matrices.</summary>

	inline static uint4x3 operator / (const uint4x3& lhs, const uint4x3& rhs) { return uint4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a uint4x3 matrix and a uint value.</summary>

	inline static uint4x3 operator / (const uint4x3& lhs, uint rhs) { return uint4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint4x3 matrix.</summary>

	inline static uint4x3 operator / (uint lhs, const uint4x3& rhs) { return uint4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a uint4x3 matrix.</summary>

	inline static uint4x3 operator ++ (uint4x3 val) { return uint4x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint4x3 matrix.</summary>

	inline static uint4x3 operator -- (uint4x3 val) { return uint4x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two uint4x3 matrices.</summary>

	inline static bool4x3 operator < (const uint4x3& lhs, const uint4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a uint4x3 matrix and a uint value.</summary>

	inline static bool4x3 operator < (const uint4x3& lhs, uint rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint4x3 matrix.</summary>

	inline static bool4x3 operator < (uint lhs, const uint4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint4x3 matrices.</summary>

	inline static bool4x3 operator <= (const uint4x3& lhs, const uint4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint4x3 matrix and a uint value.</summary>

	inline static bool4x3 operator <= (const uint4x3& lhs, uint rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint4x3 matrix.</summary>

	inline static bool4x3 operator <= (uint lhs, const uint4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint4x3 matrices.</summary>

	inline static bool4x3 operator > (const uint4x3& lhs, const uint4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint4x3 matrix and a uint value.</summary>

	inline static bool4x3 operator > (const uint4x3& lhs, uint rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint4x3 matrix.</summary>

	inline static bool4x3 operator > (uint lhs, const uint4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint4x3 matrices.</summary>

	inline static bool4x3 operator >= (const uint4x3& lhs, const uint4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint4x3 matrix and a uint value.</summary>

	inline static bool4x3 operator >= (const uint4x3& lhs, uint rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint4x3 matrix.</summary>

	inline static bool4x3 operator >= (uint lhs, const uint4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two uint4x3 matrices.</summary>

	inline static bool4x3 operator == (const uint4x3& lhs, const uint4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a uint4x3 matrix and a uint value.</summary>

	inline static bool4x3 operator == (const uint4x3& lhs, uint rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint4x3 matrix.</summary>

	inline static bool4x3 operator == (uint lhs, const uint4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint4x3 matrices.</summary>

	inline static bool4x3 operator != (const uint4x3& lhs, const uint4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint4x3 matrix and a uint value.</summary>

	inline static bool4x3 operator != (const uint4x3& lhs, uint rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint4x3 matrix.</summary>

	inline static bool4x3 operator != (uint lhs, const uint4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region uint4x4
	struct uint4x4
	{
		uint4 c0, c1, c2, c3;
		uint4x4() : c0(), c1(), c2(), c3() {}
		uint4x4(uint m00, uint m01, uint m02, uint m03,
			uint m10, uint m11, uint m12, uint m13,
			uint m20, uint m21, uint m22, uint m23,
			uint m30, uint m31, uint m32, uint m33)
		{
			c0 = uint4(m00, m10, m20, m30);
			c1 = uint4(m01, m11, m21, m31);
			c2 = uint4(m02, m12, m22, m32);
			c3 = uint4(m03, m13, m23, m33);
		}
		uint4x4(uint4 c0, uint4 c1, uint4 c2, uint4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		uint4x4(uint v) : c0(v), c1(v), c2(v), c3(v) {}

		uint4x4(uint3x3 rotation, uint3 translation)
		{
			c0 = uint4(rotation.c0, 0.0f);
			c1 = uint4(rotation.c1, 0.0f);
			c2 = uint4(rotation.c2, 0.0f);
			c3 = uint4(translation, 1.0f);
		}


	};


	/// <summary>Returns the result of a componentwise multiplication operation on two uint4x4 matrices.</summary>

	inline static uint4x4 operator * (const uint4x4& lhs, const uint4x4& rhs) { return uint4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint4x4 matrix and a uint value.</summary>

	inline static uint4x4 operator * (const uint4x4& lhs, uint rhs) { return uint4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a uint value and a uint4x4 matrix.</summary>

	inline static uint4x4 operator * (uint lhs, const uint4x4& rhs) { return uint4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two uint4x4 matrices.</summary>

	inline static uint4x4 operator + (const uint4x4& lhs, const uint4x4& rhs) { return uint4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a uint4x4 matrix and a uint value.</summary>

	inline static uint4x4 operator + (const uint4x4& lhs, uint rhs) { return uint4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a uint value and a uint4x4 matrix.</summary>

	inline static uint4x4 operator + (uint lhs, const uint4x4& rhs) { return uint4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two uint4x4 matrices.</summary>

	inline static uint4x4 operator - (const uint4x4& lhs, const uint4x4& rhs) { return uint4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint4x4 matrix and a uint value.</summary>

	inline static uint4x4 operator - (const uint4x4& lhs, uint rhs) { return uint4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a uint value and a uint4x4 matrix.</summary>

	inline static uint4x4 operator - (uint lhs, const uint4x4& rhs) { return uint4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two uint4x4 matrices.</summary>

	inline static uint4x4 operator / (const uint4x4& lhs, const uint4x4& rhs) { return uint4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a uint4x4 matrix and a uint value.</summary>

	inline static uint4x4 operator / (const uint4x4& lhs, uint rhs) { return uint4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a uint value and a uint4x4 matrix.</summary>

	inline static uint4x4 operator / (uint lhs, const uint4x4& rhs) { return uint4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a uint4x4 matrix.</summary>

	inline static uint4x4 operator ++ (uint4x4 val) { return uint4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a uint4x4 matrix.</summary>

	inline static uint4x4 operator -- (uint4x4 val) { return uint4x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two uint4x4 matrices.</summary>

	inline static bool4x4 operator < (const uint4x4& lhs, const uint4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a uint4x4 matrix and a uint value.</summary>

	inline static bool4x4 operator < (const uint4x4& lhs, uint rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a uint value and a uint4x4 matrix.</summary>

	inline static bool4x4 operator < (uint lhs, const uint4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two uint4x4 matrices.</summary>

	inline static bool4x4 operator <= (const uint4x4& lhs, const uint4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint4x4 matrix and a uint value.</summary>

	inline static bool4x4 operator <= (const uint4x4& lhs, uint rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a uint value and a uint4x4 matrix.</summary>

	inline static bool4x4 operator <= (uint lhs, const uint4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two uint4x4 matrices.</summary>

	inline static bool4x4 operator > (const uint4x4& lhs, const uint4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint4x4 matrix and a uint value.</summary>

	inline static bool4x4 operator > (const uint4x4& lhs, uint rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a uint value and a uint4x4 matrix.</summary>

	inline static bool4x4 operator > (uint lhs, const uint4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two uint4x4 matrices.</summary>

	inline static bool4x4 operator >= (const uint4x4& lhs, const uint4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint4x4 matrix and a uint value.</summary>

	inline static bool4x4 operator >= (const uint4x4& lhs, uint rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a uint value and a uint4x4 matrix.</summary>

	inline static bool4x4 operator >= (uint lhs, const uint4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on two uint4x4 matrices.</summary>

	inline static bool4x4 operator == (const uint4x4& lhs, const uint4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a uint4x4 matrix and a uint value.</summary>

	inline static bool4x4 operator == (const uint4x4& lhs, uint rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a uint value and a uint4x4 matrix.</summary>

	inline static bool4x4 operator == (uint lhs, const uint4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two uint4x4 matrices.</summary>

	inline static bool4x4 operator != (const uint4x4& lhs, const uint4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint4x4 matrix and a uint value.</summary>

	inline static bool4x4 operator != (const uint4x4& lhs, uint rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a uint value and a uint4x4 matrix.</summary>

	inline static bool4x4 operator != (uint lhs, const uint4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic


	/// <summary>Returns the Tangent of a uint value.</summary>
	inline static uint Tan(uint x) { return (uint)tan(x); }

	/// <summary>Returns the componentwise Tangent of a uint2 vector.</summary>
	inline static uint2 Tan(uint2 x) { return uint2(Tan(x.x), Tan(x.y)); }

	/// <summary>Returns the componentwise Tangent of a uint3 vector.</summary>
	inline static uint3 Tan(uint3 x) { return uint3(Tan(x.x), Tan(x.y), Tan(x.z)); }

	/// <summary>Returns the componentwise Tangent of a uint4 vector.</summary>
	inline static uint4 Tan(uint4 x) { return uint4(Tan(x.x), Tan(x.y), Tan(x.z), Tan(x.w)); }


	/// <summary>Returns the hyperbolic Tangent of a uint value.</summary>
	inline static uint Tanh(uint x) { return (uint)tanh(x); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a uint2 vector.</summary>
	inline static uint2 Tanh(uint2 x) { return uint2(Tanh(x.x), Tanh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a uint3 vector.</summary>
	inline static uint3 Tanh(uint3 x) { return uint3(Tanh(x.x), Tanh(x.y), Tanh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a uint4 vector.</summary>
	inline static uint4 Tanh(uint4 x) { return uint4(Tanh(x.x), Tanh(x.y), Tanh(x.z), Tanh(x.w)); }


	/// <summary>Returns the arcTangent of a uint value.</summary>
	inline static uint Atan(uint x) { return (uint)atan(x); }

	/// <summary>Returns the componentwise arcTangent of a uint2 vector.</summary>
	inline static uint2 Atan(uint2 x) { return uint2(Atan(x.x), Atan(x.y)); }

	/// <summary>Returns the componentwise arcTangent of a uint3 vector.</summary>
	inline static uint3 Atan(uint3 x) { return uint3(Atan(x.x), Atan(x.y), Atan(x.z)); }

	/// <summary>Returns the componentwise arcTangent of a uint4 vector.</summary>
	inline static uint4 Atan(uint4 x) { return uint4(Atan(x.x), Atan(x.y), Atan(x.z), Atan(x.w)); }


	/// <summary>Returns the 2-argument arcTangent of a pair of uint values.</summary>
	inline static uint Atan2(uint y, uint x) { return (uint)atan2(y, x); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of uints2 vectors.</summary>
	inline static uint2 Atan2(uint2 y, uint2 x) { return uint2(Atan2(y.x, x.x), Atan2(y.y, x.y)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of uints3 vectors.</summary>
	inline static uint3 Atan2(uint3 y, uint3 x) { return uint3(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of uints4 vectors.</summary>
	inline static uint4 Atan2(uint4 y, uint4 x) { return uint4(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z), Atan2(y.w, x.w)); }


	/// <summary>Returns the CoSine of a uint value.</summary>
	inline static uint Cos(uint x) { return (uint)cos(x); }

	/// <summary>Returns the componentwise CoSine of a uint2 vector.</summary>
	inline static uint2 Cos(uint2 x) { return uint2(Cos(x.x), Cos(x.y)); }

	/// <summary>Returns the componentwise CoSine of a uint3 vector.</summary>
	inline static uint3 Cos(uint3 x) { return uint3(Cos(x.x), Cos(x.y), Cos(x.z)); }

	/// <summary>Returns the componentwise CoSine of a uint4 vector.</summary>
	inline static uint4 Cos(uint4 x) { return uint4(Cos(x.x), Cos(x.y), Cos(x.z), Cos(x.w)); }


	/// <summary>Returns the hyperbolic CoSine of a uint value.</summary>
	inline static uint Cosh(uint x) { return (uint)cosh(x); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a uint2 vector.</summary>
	inline static uint2 Cosh(uint2 x) { return uint2(Cosh(x.x), Cosh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a uint3 vector.</summary>
	inline static uint3 Cosh(uint3 x) { return uint3(Cosh(x.x), Cosh(x.y), Cosh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a uint4 vector.</summary>
	inline static uint4 Cosh(uint4 x) { return uint4(Cosh(x.x), Cosh(x.y), Cosh(x.z), Cosh(x.w)); }

	/// <summary>Returns the arcCoSine of a uint value.</summary>
	inline static uint Acos(uint x) { return (uint)acos((uint)x); }

	/// <summary>Returns the componentwise arcCoSine of a uint2 vector.</summary>
	inline static uint2 Acos(uint2 x) { return uint2(Acos(x.x), Acos(x.y)); }

	/// <summary>Returns the componentwise arcCoSine of a uint3 vector.</summary>
	inline static uint3 Acos(uint3 x) { return uint3(Acos(x.x), Acos(x.y), Acos(x.z)); }

	/// <summary>Returns the componentwise arcCoSine of a uint4 vector.</summary>
	inline static uint4 Acos(uint4 x) { return uint4(Acos(x.x), Acos(x.y), Acos(x.z), Acos(x.w)); }


	/// <summary>Returns the Sine of a uint value.</summary>
	inline static uint Sin(uint x) { return (uint)sin((uint)x); }

	/// <summary>Returns the componentwise Sine of a uint2 vector.</summary>
	inline static uint2 Sin(uint2 x) { return uint2(Sin(x.x), Sin(x.y)); }

	/// <summary>Returns the componentwise Sine of a uint3 vector.</summary>
	inline static uint3 Sin(uint3 x) { return uint3(Sin(x.x), Sin(x.y), Sin(x.z)); }

	/// <summary>Returns the componentwise Sine of a uint4 vector.</summary>
	inline static uint4 Sin(uint4 x) { return uint4(Sin(x.x), Sin(x.y), Sin(x.z), Sin(x.w)); }



	/// <summary>Returns the hyperbolic Sine of a uint value.</summary>
	inline static uint Sinh(uint x) { return (uint)sinh((uint)x); }

	/// <summary>Returns the componentwise hyperbolic Sine of a uint2 vector.</summary>
	inline static uint2 Sinh(uint2 x) { return uint2(Sinh(x.x), Sinh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a uint3 vector.</summary>
	inline static uint3 Sinh(uint3 x) { return uint3(Sinh(x.x), Sinh(x.y), Sinh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a uint4 vector.</summary>
	inline static uint4 Sinh(uint4 x) { return uint4(Sinh(x.x), Sinh(x.y), Sinh(x.z), Sinh(x.w)); }


	/// <summary>Returns the arcSine of a uint value.</summary>
	inline static uint Asin(uint x) { return (uint)asin((uint)x); }

	/// <summary>Returns the componentwise arcSine of a uint2 vector.</summary>
	inline static uint2 Asin(uint2 x) { return uint2(Asin(x.x), Asin(x.y)); }

	/// <summary>Returns the componentwise arcSine of a uint3 vector.</summary>
	inline static uint3 Asin(uint3 x) { return uint3(Asin(x.x), Asin(x.y), Asin(x.z)); }

	/// <summary>Returns the componentwise arcSine of a uint4 vector.</summary>
	inline static uint4 Asin(uint4 x) { return uint4(Asin(x.x), Asin(x.y), Asin(x.z), Asin(x.w)); }


	/// <summary>Returns the Dot product of two uint values. Equivalent to multiplication.</summary>
	inline static uint Dot(uint x, uint y) { return x * y; }

	/// <summary>Returns the Dot product of two uint2 vectors.</summary>
	inline static uint Dot(uint2 x, uint2 y) { return x.x * y.x + x.y * y.y; }

	/// <summary>Returns the Dot product of two uint3 vectors.</summary>
	inline static uint Dot(uint3 x, uint3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }

	/// <summary>Returns the Dot product of two uint4 vectors.</summary>
	inline static uint Dot(uint4 x, uint4 y) { return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w; }

	/// <summary>Returns the square root of a uint value.</summary>
	inline static uint Sqrt(uint x) { return sqrt((double)x); }

	/// <summary>Returns the componentwise square root of a uint2 vector.</summary>
	inline static uint2 Sqrt(uint2 x) { return uint2(Sqrt(x.x), Sqrt(x.y)); }

	/// <summary>Returns the componentwise square root of a uint3 vector.</summary>
	inline static uint3 Sqrt(uint3 x) { return uint3(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z)); }

	/// <summary>Returns the componentwise square root of a uint4 vector.</summary>
	inline static uint4 Sqrt(uint4 x) { return uint4(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z), Sqrt(x.w)); }


	/// <summary>Returns the reciprocal square root of a uint value.</summary>
	inline static uint Rsqrt(uint x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a uint2 vector.</summary>
	inline static uint2 Rsqrt(uint2 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a uint3 vector.</summary>
	inline static uint3 Rsqrt(uint3 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a uint4 vector</summary>
	inline static uint4 Rsqrt(uint4 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns a Normalized version of the uint2 vector x by scaling it by 1 / Length(x).</summary>
	inline static uint2 Normalize(uint2 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the uint3 vector x by scaling it by 1 / Length(x).</summary>
	inline static uint3 Normalize(uint3 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the uint4 vector x by scaling it by 1 / Length(x).</summary>
	inline static uint4 Normalize(uint4 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns the Length of a uint2 vector.</summary>
	inline static uint Length(uint2 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a uint3 vector.</summary>
	inline static uint Length(uint3 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a uint4 vector.</summary>
	inline static uint Length(uint4 x) { return sqrt(Dot(x, x)); }




	/// <summary>Returns the squared Length of a uint value. Equivalent to squaring the value.</summary>
	inline static uint Lengthsq(uint x) { return x * x; }

	/// <summary>Returns the squared Length of a uint2 vector.</summary>
	inline static uint Lengthsq(uint2 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a uint3 vector.</summary>
	inline static uint Lengthsq(uint3 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a uint4 vector.</summary>
	inline static uint Lengthsq(uint4 x) { return Dot(x, x); }


	/// <summary>Returns the Distance between two uint2 vectors.</summary>
	inline static uint Distance(uint2 x, uint2 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two uint3 vectors.</summary>
	inline static uint Distance(uint3 x, uint3 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two uint4 vectors.</summary>
	inline static uint Distance(uint4 x, uint4 y) { return Length(y - x); }



	/// <summary>Returns the Distance between two uint values.</summary>
	inline static uint Distancesq(uint x, uint y) { return (y - x) * (y - x); }

	/// <summary>Returns the Distance between two uint2 vectors.</summary>
	inline static uint Distancesq(uint2 x, uint2 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two uint3 vectors.</summary>
	inline static uint Distancesq(uint3 x, uint3 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two uint4 vectors.</summary>
	inline static uint Distancesq(uint4 x, uint4 y) { return Lengthsq(y - x); }



	/// <summary>Returns the Cross product of two uint3 vectors.</summary>
	inline static uint3 Cross(uint3 x, uint3 y) {
		uint3 retVal = x * uint3(y.y, y.z, y.x) - uint3(x.y, x.z, x.x) * y;
		return uint3(retVal.y, retVal.z, retVal.x);
	}

	/// <summary>Returns the Sine and CoSine of the input uint value x through the out parameters s and c.</summary>
	inline static void SinCos(uint x, uint* s, uint* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input uint2 vector x through the out parameters s and c.</summary>
	inline static void SinCos(uint2 x, uint2* s, uint2* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input uint3 vector x through the out parameters s and c.</summary>
	inline static void SinCos(uint3 x, uint3* s, uint3* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input uint4 vector x through the out parameters s and c.</summary>
	inline static void SinCos(uint4 x, uint4* s, uint4* c) { *s = Sin(x); *c = Cos(x); }


	/// <summary>Returns the Minimum of two uint values.</summary>
	inline static uint Min(uint x, uint y) { return x < y ? x : y; }

	/// <summary>Returns the componentwise Minimum of two uint2 vectors.</summary>
	inline static uint2 Min(uint2 x, uint2 y) { return uint2(Min(x.x, y.x), Min(x.y, y.y)); }

	/// <summary>Returns the componentwise Minimum of two uint3 vectors.</summary>
	inline static uint3 Min(uint3 x, uint3 y) { return uint3(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z)); }

	/// <summary>Returns the componentwise Minimum of two uint4 vectors.</summary>
	inline static uint4 Min(uint4 x, uint4 y) { return uint4(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z), Min(x.w, y.w)); }


	/// <summary>Returns the Maximum of two uint values.</summary>
	inline static uint Max(uint x, uint y) { return x > y ? x : y; }

	/// <summary>Returns the componentwise Maximum of two uint2 vectors.</summary>
	inline static uint2 Max(uint2 x, uint2 y) { return uint2(Max(x.x, y.x), Max(x.y, y.y)); }

	/// <summary>Returns the componentwise Maximum of two uint3 vectors.</summary>
	inline static uint3 Max(uint3 x, uint3 y) { return uint3(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z)); }

	/// <summary>Returns the componentwise Maximum of two uint4 vectors.</summary>
	inline static uint4 Max(uint4 x, uint4 y) { return uint4(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z), Max(x.w, y.w)); }

	inline static uint Lerp(uint x, uint y, uint s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static uint2 Lerp(uint2 x, uint2 y, uint s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static uint3 Lerp(uint3 x, uint3 y, uint s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static uint4 Lerp(uint4 x, uint4 y, uint s) { return x + s * (y - x); }


	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static uint2 Lerp(uint2 x, uint2 y, uint2 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static uint3 Lerp(uint3 x, uint3 y, uint3 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static uint4 Lerp(uint4 x, uint4 y, uint4 s) { return x + s * (y - x); }

	/// <summary>Returns the result of normalizing a uinting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static uint Unlerp(uint a, uint b, uint x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a uinting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static uint2 Unlerp(uint2 a, uint2 b, uint2 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a uinting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static uint3 Unlerp(uint3 a, uint3 b, uint3 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a uinting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static uint4 Unlerp(uint4 a, uint4 b, uint4 x) { return (x - a) / (b - a); }

	/// <summary>Returns the result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static uint Remap(uint a, uint b, uint c, uint d, uint x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static uint2 Remap(uint2 a, uint2 b, uint2 c, uint2 d, uint2 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static uint3 Remap(uint3 a, uint3 b, uint3 c, uint3 d, uint3 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static uint4 Remap(uint4 a, uint4 b, uint4 c, uint4 d, uint4 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the result of Clamping the value x into the interval [a, b], where x, a and b are uint values.</summary>
	inline static uint Clamp(uint x, uint a, uint b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are uint2 vectors.</summary>
	inline static uint2 Clamp(uint2 x, uint2 a, uint2 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are uint3 vectors.</summary>
	inline static uint3 Clamp(uint3 x, uint3 a, uint3 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are uint4 vectors.</summary>
	inline static uint4 Clamp(uint4 x, uint4 a, uint4 b) { return Max(a, Min(b, x)); }

	inline static uint select_shuffle_component(uint4 a, uint4 b, char component)
	{
		switch (component)
		{
		case 0:
			return a.x;
		case 1:
			return a.y;
		case 2:
			return a.z;
		case 3:
			return a.w;
		case 4:
			return b.x;
		case 5:
			return b.y;
		case 6:
			return b.z;
		case 7:
			return b.w;
		default:
			//TODO: Exception Handle
			throw;
		}
	}

	inline static uint4 shuffle(uint4 a, uint4 b, char x, char y, char z, char w)
	{
		return uint4(
			select_shuffle_component(a, b, x),
			select_shuffle_component(a, b, y),
			select_shuffle_component(a, b, z),
			select_shuffle_component(a, b, w));
	}

	inline static uint4 movelh(uint4 a, uint4 b)
	{
		return shuffle(a, b, 0, 1, 4, 5);
	}
	inline static uint4 movehl(uint4 a, uint4 b)
	{
		return shuffle(b, a, 2, 3, 6, 7);
	}
	// SSE shuffles
	inline static uint4 unpacklo(uint4 a, uint4 b)
	{
		return shuffle(a, b, 0, 4, 1, 5);
	}
	inline static uint4 unpackhi(uint4 a, uint4 b)
	{
		return shuffle(a, b, 2, 6, 3, 7);
	}
#pragma endregion
#pragma region Component
	/// <summary>Returns the Maximum component of a uint2 vector.</summary>
	inline static uint CMax(uint2 x) { return Max(x.x, x.y); }

	/// <summary>Returns the Maximum component of a uint3 vector.</summary>
	inline static uint CMax(uint3 x) { return Max(Max(x.x, x.y), x.z); }

	/// <summary>Returns the Maximum component of a uint4 vector.</summary>
	inline static uint CMax(uint4 x) { return Max(Max(x.x, x.y), Max(x.z, x.w)); }

	/// <summary>Returns the horizontal sum of components of a uint2 vector.</summary>
	inline static uint Csum(uint2 x) { return x.x + x.y; }

	/// <summary>Returns the horizontal sum of components of a uint3 vector.</summary>
	inline static uint Csum(uint3 x) { return x.x + x.y + x.z; }

	/// <summary>Returns the horizontal sum of components of a uint4 vector.</summary>
	inline static uint Csum(uint4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion

#pragma region Transpose
	/// <summary>Return the uint2x2 Transpose of a uint2x2 matrix.</summary>
	inline uint2x2 Transpose(uint2x2 v)
	{
		return uint2x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y);
	}
	/// <summary>Return the uint3x2 Transpose of a uint2x3 matrix.</summary>
	inline uint3x2 Transpose(uint2x3 v)
	{
		return uint3x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y);
	}
	/// <summary>Return the uint4x2 Transpose of a uint2x4 matrix.</summary>
	inline uint4x2 Transpose(uint2x4 v)
	{
		return uint4x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y,
			v.c3.x, v.c3.y);
	}
	/// <summary>Return the uint2x3 Transpose of a uint3x2 matrix.</summary>
	inline uint2x3 Transpose(uint3x2 v)
	{
		return uint2x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z);
	}
	/// <summary>Return the uint3x3 Transpose of a uint3x3 matrix.</summary>
	inline uint3x3 Transpose(uint3x3 v)
	{
		return uint3x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z);
	}
	/// <summary>Return the uint4x3 Transpose of a uint3x4 matrix.</summary>
	inline static uint4x3 Transpose(uint3x4 v)
	{
		return uint4x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z,
			v.c3.x, v.c3.y, v.c3.z);
	}
	/// <summary>Return the uint2x4 Transpose of a uint4x2 matrix.</summary>
	inline static uint2x4 Transpose(uint4x2 v)
	{
		return uint2x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w);
	}
	/// <summary>Return the uint3x4 Transpose of a uint4x3 matrix.</summary>
	inline static uint3x4 Transpose(uint4x3 v)
	{
		return uint3x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w);
	}
	/// <summary>Return the uint4x4 Transpose of a uint4x4 matrix.</summary>
	inline static uint4x4 Transpose(uint4x4 v)
	{
		return uint4x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w,
			v.c3.x, v.c3.y, v.c3.z, v.c3.w);
	}

#pragma endregion
#pragma region Inverse
	
	/// <summary>Returns the uint3x3 full Inverse of a uint3x3 matrix.</summary>
	inline uint3x3 Inverse(uint3x3 m)
	{
		uint3 c0 = m.c0;
		uint3 c1 = m.c1;
		uint3 c2 = m.c2;

		uint3 t0 = uint3(c1.x, c2.x, c0.x);
		uint3 t1 = uint3(c1.y, c2.y, c0.y);
		uint3 t2 = uint3(c1.z, c2.z, c0.z);

		uint3 m0 = t1 * uint3(t2.y, t2.z, t2.x) - uint3(t1.y, t1.z, t1.x) * t2;
		uint3 m1 = uint3(t0.y, t0.z, t0.x) * t2 - t0 * uint3(t2.y, t2.z, t2.x);
		uint3 m2 = t0 * uint3(t1.y, t1.z, t1.x) - t0 * uint3(t2.y, t2.z, t2.x) * t1;

		uint rcpDet = 1.0f / Csum(uint3(t0.z, t0.x, t0.y) * m0);
		return uint3x3(m0, m1, m2) * rcpDet;
	}
	
	/// <summary>Returns the uint4x4 full Inverse of a uint4x4 matrix.</summary>
	inline static uint4x4 Inverse(uint4x4 m)
	{
		uint4 c0 = m.c0;
		uint4 c1 = m.c1;
		uint4 c2 = m.c2;
		uint4 c3 = m.c3;

		uint4 r0y_r1y_r0x_r1x = movelh(c1, c0);
		uint4 r0z_r1z_r0w_r1w = movelh(c2, c3);
		uint4 r2y_r3y_r2x_r3x = movehl(c0, c1);
		uint4 r2z_r3z_r2w_r3w = movehl(c3, c2);

		uint4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
		uint4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
		uint4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
		uint4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

		uint4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
		uint4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
		uint4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
		uint4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
		uint4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

		// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
		uint4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
		uint4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
		uint4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

		// Expand inner terms back to 4 components. zw signs still need to be flipped
		uint4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
		uint4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

		uint4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
		uint4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

		// Calculate Minors
		uint4 Minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

		uint4 denom = r0_xyzw * Minors0;

		// Horizontal sum of denoMinator. Free sign flip of z and w compensates for misSing flip in inner terms.
		denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
		denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

		uint4 rcp_denom_ppnn = uint4(1.0f) / denom;
		uint4x4 res;
		res.c0 = Minors0 * rcp_denom_ppnn;

		uint4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
		uint4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

		uint4 Minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
		res.c1 = Minors1 * rcp_denom_ppnn;

		uint4 Minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
		res.c2 = Minors2 * rcp_denom_ppnn;

		uint4 Minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
		res.c3 = Minors3 * rcp_denom_ppnn;
		return res;
	}
	
#pragma endregion
#pragma region DeterMinant
	/// <summary>Returns the DeterMinant of a uint2x2 matrix.</summary>
	inline uint DeterMinant(uint2x2 m)
	{
		uint a = m.c0.x;
		uint b = m.c1.x;
		uint c = m.c0.y;
		uint d = m.c1.y;

		return a * d - b * c;
	}
	/// <summary>Returns the DeterMinant of a uint3x3 matrix.</summary>
	inline uint DeterMinant(uint3x3 m)
	{
		uint3 c0 = m.c0;
		uint3 c1 = m.c1;
		uint3 c2 = m.c2;

		uint m00 = c1.y * c2.z - c1.z * c2.y;
		uint m01 = c0.y * c2.z - c0.z * c2.y;
		uint m02 = c0.y * c1.z - c0.z * c1.y;

		return c0.x * m00 - c1.x * m01 + c2.x * m02;
	}
	/// <summary>Returns the DeterMinant of a uint4x4 matrix.</summary>
	inline static uint DeterMinant(uint4x4 m)
	{
		uint4 c0 = m.c0;
		uint4 c1 = m.c1;
		uint4 c2 = m.c2;
		uint4 c3 = m.c3;

		uint m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
		uint m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
		uint m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
		uint m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

		return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
	}

#pragma endregion
}