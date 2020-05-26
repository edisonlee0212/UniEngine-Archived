#pragma once
namespace UniEngine {
#pragma region unsigned2
	struct unsigned2 {
		unsigned x, y;
		unsigned2() : x(0), y(0) {}
		unsigned2(unsigned x, unsigned y) : x(x), y(y) {}
		unsigned2(unsigned v) : x(v), y(v) {}
	};
	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned2 vectors.</summary>

	inline static unsigned2 operator * (const unsigned2& lhs, const unsigned2& rhs) { return unsigned2(lhs.x * rhs.x, lhs.y * rhs.y); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned2 vector and a unsigned value.</summary>

	inline static unsigned2 operator * (const unsigned2& lhs, unsigned rhs) { return unsigned2(lhs.x * rhs, lhs.y * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned2 vector.</summary>

	inline static unsigned2 operator * (unsigned lhs, const unsigned2& rhs) { return unsigned2(lhs * rhs.x, lhs * rhs.y); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned2 vectors.</summary>

	inline static unsigned2 operator + (const unsigned2& lhs, const unsigned2& rhs) { return unsigned2(lhs.x + rhs.x, lhs.y + rhs.y); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned2 vector and a unsigned value.</summary>

	inline static unsigned2 operator + (const unsigned2& lhs, unsigned rhs) { return unsigned2(lhs.x + rhs, lhs.y + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned2 vector.</summary>

	inline static unsigned2 operator + (unsigned lhs, const unsigned2& rhs) { return unsigned2(lhs + rhs.x, lhs + rhs.y); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned2 vectors.</summary>

	inline static unsigned2 operator - (const unsigned2& lhs, const unsigned2& rhs) { return unsigned2(lhs.x - rhs.x, lhs.y - rhs.y); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned2 vector and a unsigned value.</summary>

	inline static unsigned2 operator - (const unsigned2& lhs, unsigned rhs) { return unsigned2(lhs.x - rhs, lhs.y - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned2 vector.</summary>

	inline static unsigned2 operator - (unsigned lhs, const unsigned2& rhs) { return unsigned2(lhs - rhs.x, lhs - rhs.y); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned2 vectors.</summary>

	inline static unsigned2 operator / (const unsigned2& lhs, const unsigned2& rhs) { return unsigned2(lhs.x / rhs.x, lhs.y / rhs.y); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned2 vector and a unsigned value.</summary>

	inline static unsigned2 operator / (const unsigned2& lhs, unsigned rhs) { return unsigned2(lhs.x / rhs, lhs.y / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned2 vector.</summary>

	inline static unsigned2 operator / (unsigned lhs, const unsigned2& rhs) { return unsigned2(lhs / rhs.x, lhs / rhs.y); }

	/// <summary>Returns the result of a componentwise increment operation on a unsigned2 vector.</summary>

	inline static unsigned2 operator ++ (unsigned2 val) { return unsigned2(++val.x, ++val.y); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned2 vector.</summary>

	inline static unsigned2 operator -- (unsigned2 val) { return unsigned2(--val.x, --val.y); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned2 vectors.</summary>

	inline static bool2 operator < (const unsigned2& lhs, const unsigned2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned2 vector and a unsigned value.</summary>

	inline static bool2 operator < (const unsigned2& lhs, unsigned rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned2 vector.</summary>

	inline static bool2 operator < (unsigned lhs, const unsigned2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned2 vectors.</summary>

	inline static bool2 operator <= (const unsigned2& lhs, const unsigned2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned2 vector and a unsigned value.</summary>

	inline static bool2 operator <= (const unsigned2& lhs, unsigned rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned2 vector.</summary>

	inline static bool2 operator <= (unsigned lhs, const unsigned2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned2 vectors.</summary>

	inline static bool2 operator > (const unsigned2& lhs, const unsigned2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned2 vector and a unsigned value.</summary>

	inline static bool2 operator > (const unsigned2& lhs, unsigned rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned2 vector.</summary>

	inline static bool2 operator > (unsigned lhs, const unsigned2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned2 vectors.</summary>

	inline static bool2 operator >= (const unsigned2& lhs, const unsigned2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned2 vector and a unsigned value.</summary>

	inline static bool2 operator >= (const unsigned2& lhs, unsigned rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned2 vector.</summary>

	inline static bool2 operator >= (unsigned lhs, const unsigned2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned2 vectors.</summary>

	inline static bool2 operator == (const unsigned2& lhs, const unsigned2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned2 vector and a unsigned value.</summary>

	inline static bool2 operator == (const unsigned2& lhs, unsigned rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned2 vector.</summary>

	inline static bool2 operator == (unsigned lhs, const unsigned2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned2 vectors.</summary>

	inline static bool2 operator != (const unsigned2& lhs, const unsigned2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned2 vector and a unsigned value.</summary>

	inline static bool2 operator != (const unsigned2& lhs, unsigned rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned2 vector.</summary>

	inline static bool2 operator != (unsigned lhs, const unsigned2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region unsigned2x2
	struct unsigned2x2
	{
		unsigned2 c0, c1;
		unsigned2x2() : c0(), c1() {}
		unsigned2x2(unsigned m00, unsigned m01,
			unsigned m10, unsigned m11) :c0(unsigned2(m00, m10)), c1(unsigned2(m01, m11)) {}
		unsigned2x2(unsigned2 c0, unsigned2 c1) : c0(c0), c1(c1) {}
		unsigned2x2(unsigned v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned2x2 matrices.</summary>

	inline static unsigned2x2 operator * (const unsigned2x2& lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static unsigned2x2 operator * (const unsigned2x2& lhs, unsigned rhs) { return unsigned2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static unsigned2x2 operator * (unsigned lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned2x2 matrices.</summary>

	inline static unsigned2x2 operator + (const unsigned2x2& lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static unsigned2x2 operator + (const unsigned2x2& lhs, unsigned rhs) { return unsigned2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static unsigned2x2 operator + (unsigned lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned2x2 matrices.</summary>

	inline static unsigned2x2 operator - (const unsigned2x2& lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static unsigned2x2 operator - (const unsigned2x2& lhs, unsigned rhs) { return unsigned2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static unsigned2x2 operator - (unsigned lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned2x2 matrices.</summary>

	inline static unsigned2x2 operator / (const unsigned2x2& lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static unsigned2x2 operator / (const unsigned2x2& lhs, unsigned rhs) { return unsigned2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static unsigned2x2 operator / (unsigned lhs, const unsigned2x2& rhs) { return unsigned2x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a unsigned2x2 matrix.</summary>

	inline static unsigned2x2 operator ++ (unsigned2x2 val) { return unsigned2x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned2x2 matrix.</summary>

	inline static unsigned2x2 operator -- (unsigned2x2 val) { return unsigned2x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned2x2 matrices.</summary>

	inline static bool2x2 operator < (const unsigned2x2& lhs, const unsigned2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static bool2x2 operator < (const unsigned2x2& lhs, unsigned rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static bool2x2 operator < (unsigned lhs, const unsigned2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned2x2 matrices.</summary>

	inline static bool2x2 operator <= (const unsigned2x2& lhs, const unsigned2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static bool2x2 operator <= (const unsigned2x2& lhs, unsigned rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static bool2x2 operator <= (unsigned lhs, const unsigned2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned2x2 matrices.</summary>

	inline static bool2x2 operator > (const unsigned2x2& lhs, const unsigned2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static bool2x2 operator > (const unsigned2x2& lhs, unsigned rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static bool2x2 operator > (unsigned lhs, const unsigned2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned2x2 matrices.</summary>

	inline static bool2x2 operator >= (const unsigned2x2& lhs, const unsigned2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static bool2x2 operator >= (const unsigned2x2& lhs, unsigned rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static bool2x2 operator >= (unsigned lhs, const unsigned2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned2x2 matrices.</summary>

	inline static bool2x2 operator == (const unsigned2x2& lhs, const unsigned2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static bool2x2 operator == (const unsigned2x2& lhs, unsigned rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static bool2x2 operator == (unsigned lhs, const unsigned2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned2x2 matrices.</summary>

	inline static bool2x2 operator != (const unsigned2x2& lhs, const unsigned2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned2x2 matrix and a unsigned value.</summary>

	inline static bool2x2 operator != (const unsigned2x2& lhs, unsigned rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned2x2 matrix.</summary>

	inline static bool2x2 operator != (unsigned lhs, const unsigned2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region unsigned2x3
	struct unsigned2x3
	{
		unsigned2 c0, c1, c2;
		unsigned2x3() : c0(), c1(), c2() {}
		unsigned2x3(unsigned m00, unsigned m01, unsigned m02,
			unsigned m10, unsigned m11, unsigned m12)
		{
			c0 = unsigned2(m00, m10);
			c1 = unsigned2(m01, m11);
			c2 = unsigned2(m02, m12);
		}
		unsigned2x3(unsigned2 c0, unsigned2 c1, unsigned2 c2) : c0(c0), c1(c1), c2(c2) {}
		unsigned2x3(unsigned v) : c0(v), c1(v), c2(v) {}
	};

	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned2x3 matrices.</summary>

	inline static unsigned2x3 operator * (const unsigned2x3& lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static unsigned2x3 operator * (const unsigned2x3& lhs, unsigned rhs) { return unsigned2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static unsigned2x3 operator * (unsigned lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned2x3 matrices.</summary>

	inline static unsigned2x3 operator + (const unsigned2x3& lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static unsigned2x3 operator + (const unsigned2x3& lhs, unsigned rhs) { return unsigned2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static unsigned2x3 operator + (unsigned lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned2x3 matrices.</summary>

	inline static unsigned2x3 operator - (const unsigned2x3& lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static unsigned2x3 operator - (const unsigned2x3& lhs, unsigned rhs) { return unsigned2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static unsigned2x3 operator - (unsigned lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned2x3 matrices.</summary>

	inline static unsigned2x3 operator / (const unsigned2x3& lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static unsigned2x3 operator / (const unsigned2x3& lhs, unsigned rhs) { return unsigned2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static unsigned2x3 operator / (unsigned lhs, const unsigned2x3& rhs) { return unsigned2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


	/// <summary>Returns the result of a componentwise increment operation on a unsigned2x3 matrix.</summary>

	inline static unsigned2x3 operator ++ (unsigned2x3 val) { return unsigned2x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned2x3 matrix.</summary>

	inline static unsigned2x3 operator -- (unsigned2x3 val) { return unsigned2x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned2x3 matrices.</summary>

	inline static bool2x3 operator < (const unsigned2x3& lhs, const unsigned2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static bool2x3 operator < (const unsigned2x3& lhs, unsigned rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static bool2x3 operator < (unsigned lhs, const unsigned2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned2x3 matrices.</summary>

	inline static bool2x3 operator <= (const unsigned2x3& lhs, const unsigned2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static bool2x3 operator <= (const unsigned2x3& lhs, unsigned rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static bool2x3 operator <= (unsigned lhs, const unsigned2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned2x3 matrices.</summary>

	inline static bool2x3 operator > (const unsigned2x3& lhs, const unsigned2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static bool2x3 operator > (const unsigned2x3& lhs, unsigned rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static bool2x3 operator > (unsigned lhs, const unsigned2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned2x3 matrices.</summary>

	inline static bool2x3 operator >= (const unsigned2x3& lhs, const unsigned2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static bool2x3 operator >= (const unsigned2x3& lhs, unsigned rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static bool2x3 operator >= (unsigned lhs, const unsigned2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned2x3 matrices.</summary>

	inline static bool2x3 operator == (const unsigned2x3& lhs, const unsigned2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static bool2x3 operator == (const unsigned2x3& lhs, unsigned rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static bool2x3 operator == (unsigned lhs, const unsigned2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned2x3 matrices.</summary>

	inline static bool2x3 operator != (const unsigned2x3& lhs, const unsigned2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned2x3 matrix and a unsigned value.</summary>

	inline static bool2x3 operator != (const unsigned2x3& lhs, unsigned rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned2x3 matrix.</summary>

	inline static bool2x3 operator != (unsigned lhs, const unsigned2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region unsigned2x4
	struct unsigned2x4
	{
		unsigned2 c0, c1, c2, c3;
		unsigned2x4() : c0(), c1(), c2(), c3() {}
		unsigned2x4(unsigned m00, unsigned m01, unsigned m02, unsigned m03,
			unsigned m10, unsigned m11, unsigned m12, unsigned m13)
		{
			c0 = unsigned2(m00, m10);
			c1 = unsigned2(m01, m11);
			c2 = unsigned2(m02, m12);
			c3 = unsigned2(m03, m13);
		}
		unsigned2x4(unsigned2 c0, unsigned2 c1, unsigned2 c2, unsigned2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		unsigned2x4(unsigned v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned2x4 matrices.</summary>

	inline static unsigned2x4 operator * (const unsigned2x4& lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static unsigned2x4 operator * (const unsigned2x4& lhs, unsigned rhs) { return unsigned2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static unsigned2x4 operator * (unsigned lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned2x4 matrices.</summary>

	inline static unsigned2x4 operator + (const unsigned2x4& lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static unsigned2x4 operator + (const unsigned2x4& lhs, unsigned rhs) { return unsigned2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static unsigned2x4 operator + (unsigned lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned2x4 matrices.</summary>

	inline static unsigned2x4 operator - (const unsigned2x4& lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static unsigned2x4 operator - (const unsigned2x4& lhs, unsigned rhs) { return unsigned2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static unsigned2x4 operator - (unsigned lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned2x4 matrices.</summary>

	inline static unsigned2x4 operator / (const unsigned2x4& lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static unsigned2x4 operator / (const unsigned2x4& lhs, unsigned rhs) { return unsigned2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static unsigned2x4 operator / (unsigned lhs, const unsigned2x4& rhs) { return unsigned2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a unsigned2x4 matrix.</summary>

	inline static unsigned2x4 operator ++ (unsigned2x4 val) { return unsigned2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned2x4 matrix.</summary>

	inline static unsigned2x4 operator -- (unsigned2x4 val) { return unsigned2x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned2x4 matrices.</summary>

	inline static bool2x4 operator < (const unsigned2x4& lhs, const unsigned2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static bool2x4 operator < (const unsigned2x4& lhs, unsigned rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static bool2x4 operator < (unsigned lhs, const unsigned2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned2x4 matrices.</summary>

	inline static bool2x4 operator <= (const unsigned2x4& lhs, const unsigned2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static bool2x4 operator <= (const unsigned2x4& lhs, unsigned rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static bool2x4 operator <= (unsigned lhs, const unsigned2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned2x4 matrices.</summary>

	inline static bool2x4 operator > (const unsigned2x4& lhs, const unsigned2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static bool2x4 operator > (const unsigned2x4& lhs, unsigned rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static bool2x4 operator > (unsigned lhs, const unsigned2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned2x4 matrices.</summary>

	inline static bool2x4 operator >= (const unsigned2x4& lhs, const unsigned2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static bool2x4 operator >= (const unsigned2x4& lhs, unsigned rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static bool2x4 operator >= (unsigned lhs, const unsigned2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned2x4 matrices.</summary>

	inline static bool2x4 operator == (const unsigned2x4& lhs, const unsigned2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static bool2x4 operator == (const unsigned2x4& lhs, unsigned rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static bool2x4 operator == (unsigned lhs, const unsigned2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned2x4 matrices.</summary>

	inline static bool2x4 operator != (const unsigned2x4& lhs, const unsigned2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned2x4 matrix and a unsigned value.</summary>

	inline static bool2x4 operator != (const unsigned2x4& lhs, unsigned rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned2x4 matrix.</summary>

	inline static bool2x4 operator != (unsigned lhs, const unsigned2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region unsigned3
	struct unsigned3 {
		unsigned x, y, z;
		unsigned3() : x(0), y(0), z(0) {}
		unsigned3(unsigned x, unsigned y, unsigned z) : x(x), y(y), z(z) {}
		unsigned3(unsigned v) : x(v), y(v), z(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned3 vectors.</summary>

	inline static unsigned3 operator * (const unsigned3& lhs, const unsigned3& rhs) { return unsigned3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned3 vector and a unsigned value.</summary>

	inline static unsigned3 operator * (const unsigned3& lhs, unsigned rhs) { return unsigned3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned3 vector.</summary>

	inline static unsigned3 operator * (unsigned lhs, const unsigned3& rhs) { return unsigned3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned3 vectors.</summary>

	inline static unsigned3 operator + (const unsigned3& lhs, const unsigned3& rhs) { return unsigned3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned3 vector and a unsigned value.</summary>

	inline static unsigned3 operator + (const unsigned3& lhs, unsigned rhs) { return unsigned3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned3 vector.</summary>

	inline static unsigned3 operator + (unsigned lhs, const unsigned3& rhs) { return unsigned3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned3 vectors.</summary>

	inline static unsigned3 operator - (const unsigned3& lhs, const unsigned3& rhs) { return unsigned3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned3 vector and a unsigned value.</summary>

	inline static unsigned3 operator - (const unsigned3& lhs, unsigned rhs) { return unsigned3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned3 vector.</summary>

	inline static unsigned3 operator - (unsigned lhs, const unsigned3& rhs) { return unsigned3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned3 vectors.</summary>

	inline static unsigned3 operator / (const unsigned3& lhs, const unsigned3& rhs) { return unsigned3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned3 vector and a unsigned value.</summary>

	inline static unsigned3 operator / (const unsigned3& lhs, unsigned rhs) { return unsigned3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned3 vector.</summary>

	inline static unsigned3 operator / (unsigned lhs, const unsigned3& rhs) { return unsigned3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


	/// <summary>Returns the result of a componentwise increment operation on a unsigned3 vector.</summary>

	inline static unsigned3 operator ++ (unsigned3 val) { return unsigned3(++val.x, ++val.y, ++val.z); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned3 vector.</summary>

	inline static unsigned3 operator -- (unsigned3 val) { return unsigned3(--val.x, --val.y, --val.z); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned3 vectors.</summary>

	inline static bool3 operator < (const unsigned3& lhs, const unsigned3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned3 vector and a unsigned value.</summary>

	inline static bool3 operator < (const unsigned3& lhs, unsigned rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned3 vector.</summary>

	inline static bool3 operator < (unsigned lhs, const unsigned3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned3 vectors.</summary>

	inline static bool3 operator <= (const unsigned3& lhs, const unsigned3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned3 vector and a unsigned value.</summary>

	inline static bool3 operator <= (const unsigned3& lhs, unsigned rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned3 vector.</summary>

	inline static bool3 operator <= (unsigned lhs, const unsigned3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned3 vectors.</summary>

	inline static bool3 operator > (const unsigned3& lhs, const unsigned3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned3 vector and a unsigned value.</summary>

	inline static bool3 operator > (const unsigned3& lhs, unsigned rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned3 vector.</summary>

	inline static bool3 operator > (unsigned lhs, const unsigned3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned3 vectors.</summary>

	inline static bool3 operator >= (const unsigned3& lhs, const unsigned3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned3 vector and a unsigned value.</summary>

	inline static bool3 operator >= (const unsigned3& lhs, unsigned rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned3 vector.</summary>

	inline static bool3 operator >= (unsigned lhs, const unsigned3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }


	/// <summary>Returns the result of a componentwise equality operation on two unsigned3 vectors.</summary>

	inline static bool3 operator == (const unsigned3& lhs, const unsigned3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned3 vector and a unsigned value.</summary>

	inline static bool3 operator == (const unsigned3& lhs, unsigned rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned3 vector.</summary>

	inline static bool3 operator == (unsigned lhs, const unsigned3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned3 vectors.</summary>

	inline static bool3 operator != (const unsigned3& lhs, const unsigned3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned3 vector and a unsigned value.</summary>

	inline static bool3 operator != (const unsigned3& lhs, unsigned rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned3 vector.</summary>

	inline static bool3 operator != (unsigned lhs, const unsigned3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region unsigned3x2
	struct unsigned3x2
	{
		unsigned3 c0, c1;
		unsigned3x2() : c0(), c1() {}
		unsigned3x2(unsigned m00, unsigned m01,
			unsigned m10, unsigned m11,
			unsigned m20, unsigned m21)
		{
			c0 = unsigned3(m00, m10, m20);
			c1 = unsigned3(m01, m11, m21);
		}

		unsigned3x2(unsigned3 c0, unsigned3 c1) : c0(c0), c1(c1) {}
		unsigned3x2(unsigned v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned3x2 matrices.</summary>

	inline static unsigned3x2 operator * (const unsigned3x2& lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static unsigned3x2 operator * (const unsigned3x2& lhs, unsigned rhs) { return unsigned3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static unsigned3x2 operator * (unsigned lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned3x2 matrices.</summary>

	inline static unsigned3x2 operator + (const unsigned3x2& lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static unsigned3x2 operator + (const unsigned3x2& lhs, unsigned rhs) { return unsigned3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static unsigned3x2 operator + (unsigned lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned3x2 matrices.</summary>

	inline static unsigned3x2 operator - (const unsigned3x2& lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static unsigned3x2 operator - (const unsigned3x2& lhs, unsigned rhs) { return unsigned3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static unsigned3x2 operator - (unsigned lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned3x2 matrices.</summary>

	inline static unsigned3x2 operator / (const unsigned3x2& lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static unsigned3x2 operator / (const unsigned3x2& lhs, unsigned rhs) { return unsigned3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static unsigned3x2 operator / (unsigned lhs, const unsigned3x2& rhs) { return unsigned3x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a unsigned3x2 matrix.</summary>

	inline static unsigned3x2 operator ++ (unsigned3x2 val) { return unsigned3x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned3x2 matrix.</summary>

	inline static unsigned3x2 operator -- (unsigned3x2 val) { return unsigned3x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned3x2 matrices.</summary>

	inline static bool3x2 operator < (const unsigned3x2& lhs, const unsigned3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static bool3x2 operator < (const unsigned3x2& lhs, unsigned rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static bool3x2 operator < (unsigned lhs, const unsigned3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned3x2 matrices.</summary>

	inline static bool3x2 operator <= (const unsigned3x2& lhs, const unsigned3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static bool3x2 operator <= (const unsigned3x2& lhs, unsigned rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static bool3x2 operator <= (unsigned lhs, const unsigned3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned3x2 matrices.</summary>

	inline static bool3x2 operator > (const unsigned3x2& lhs, const unsigned3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static bool3x2 operator > (const unsigned3x2& lhs, unsigned rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static bool3x2 operator > (unsigned lhs, const unsigned3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned3x2 matrices.</summary>

	inline static bool3x2 operator >= (const unsigned3x2& lhs, const unsigned3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static bool3x2 operator >= (const unsigned3x2& lhs, unsigned rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static bool3x2 operator >= (unsigned lhs, const unsigned3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned3x2 matrices.</summary>

	inline static bool3x2 operator == (const unsigned3x2& lhs, const unsigned3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static bool3x2 operator == (const unsigned3x2& lhs, unsigned rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static bool3x2 operator == (unsigned lhs, const unsigned3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned3x2 matrices.</summary>

	inline static bool3x2 operator != (const unsigned3x2& lhs, const unsigned3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned3x2 matrix and a unsigned value.</summary>

	inline static bool3x2 operator != (const unsigned3x2& lhs, unsigned rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned3x2 matrix.</summary>

	inline static bool3x2 operator != (unsigned lhs, const unsigned3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region unsigned3x3
	struct unsigned3x3
	{
		unsigned3 c0, c1, c2;
		unsigned3x3() : c0(), c1(), c2() {}
		unsigned3x3(unsigned m00, unsigned m01, unsigned m02,
			unsigned m10, unsigned m11, unsigned m12,
			unsigned m20, unsigned m21, unsigned m22)
		{
			c0 = unsigned3(m00, m10, m20);
			c1 = unsigned3(m01, m11, m21);
			c2 = unsigned3(m02, m12, m22);
		}
		unsigned3x3(unsigned3 c0, unsigned3 c1, unsigned3 c2) : c0(c0), c1(c1), c2(c2) {}
		unsigned3x3(unsigned v) : c0(v), c1(v), c2(v) {}

	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned3x3 matrices.</summary>

	inline static unsigned3x3 operator * (const unsigned3x3& lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static unsigned3x3 operator * (const unsigned3x3& lhs, unsigned rhs) { return unsigned3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static unsigned3x3 operator * (unsigned lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned3x3 matrices.</summary>

	inline static unsigned3x3 operator + (const unsigned3x3& lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static unsigned3x3 operator + (const unsigned3x3& lhs, unsigned rhs) { return unsigned3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static unsigned3x3 operator + (unsigned lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned3x3 matrices.</summary>

	inline static unsigned3x3 operator - (const unsigned3x3& lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static unsigned3x3 operator - (const unsigned3x3& lhs, unsigned rhs) { return unsigned3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static unsigned3x3 operator - (unsigned lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned3x3 matrices.</summary>

	inline static unsigned3x3 operator / (const unsigned3x3& lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static unsigned3x3 operator / (const unsigned3x3& lhs, unsigned rhs) { return unsigned3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static unsigned3x3 operator / (unsigned lhs, const unsigned3x3& rhs) { return unsigned3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a unsigned3x3 matrix.</summary>

	inline static unsigned3x3 operator ++ (unsigned3x3 val) { return unsigned3x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned3x3 matrix.</summary>

	inline static unsigned3x3 operator -- (unsigned3x3 val) { return unsigned3x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned3x3 matrices.</summary>

	inline static bool3x3 operator < (const unsigned3x3& lhs, const unsigned3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static bool3x3 operator < (const unsigned3x3& lhs, unsigned rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static bool3x3 operator < (unsigned lhs, const unsigned3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned3x3 matrices.</summary>

	inline static bool3x3 operator <= (const unsigned3x3& lhs, const unsigned3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static bool3x3 operator <= (const unsigned3x3& lhs, unsigned rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static bool3x3 operator <= (unsigned lhs, const unsigned3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned3x3 matrices.</summary>

	inline static bool3x3 operator > (const unsigned3x3& lhs, const unsigned3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static bool3x3 operator > (const unsigned3x3& lhs, unsigned rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static bool3x3 operator > (unsigned lhs, const unsigned3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned3x3 matrices.</summary>

	inline static bool3x3 operator >= (const unsigned3x3& lhs, const unsigned3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static bool3x3 operator >= (const unsigned3x3& lhs, unsigned rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static bool3x3 operator >= (unsigned lhs, const unsigned3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned3x3 matrices.</summary>

	inline static bool3x3 operator == (const unsigned3x3& lhs, const unsigned3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static bool3x3 operator == (const unsigned3x3& lhs, unsigned rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static bool3x3 operator == (unsigned lhs, const unsigned3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned3x3 matrices.</summary>

	inline static bool3x3 operator != (const unsigned3x3& lhs, const unsigned3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned3x3 matrix and a unsigned value.</summary>

	inline static bool3x3 operator != (const unsigned3x3& lhs, unsigned rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned3x3 matrix.</summary>

	inline static bool3x3 operator != (unsigned lhs, const unsigned3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region unsigned3x4
	struct unsigned3x4
	{
		unsigned3 c0, c1, c2, c3;
		unsigned3x4() : c0(), c1(), c2(), c3() {}
		unsigned3x4(unsigned m00, unsigned m01, unsigned m02, unsigned m03,
			unsigned m10, unsigned m11, unsigned m12, unsigned m13,
			unsigned m20, unsigned m21, unsigned m22, unsigned m23)
		{
			c0 = unsigned3(m00, m10, m20);
			c1 = unsigned3(m01, m11, m21);
			c2 = unsigned3(m02, m12, m22);
			c3 = unsigned3(m03, m13, m23);
		}
		unsigned3x4(unsigned3 c0, unsigned3 c1, unsigned3 c2, unsigned3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		unsigned3x4(unsigned v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned3x4 matrices.</summary>

	inline static unsigned3x4 operator * (const unsigned3x4& lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static unsigned3x4 operator * (const unsigned3x4& lhs, unsigned rhs) { return unsigned3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static unsigned3x4 operator * (unsigned lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned3x4 matrices.</summary>

	inline static unsigned3x4 operator + (const unsigned3x4& lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static unsigned3x4 operator + (const unsigned3x4& lhs, unsigned rhs) { return unsigned3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static unsigned3x4 operator + (unsigned lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned3x4 matrices.</summary>

	inline static unsigned3x4 operator - (const unsigned3x4& lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static unsigned3x4 operator - (const unsigned3x4& lhs, unsigned rhs) { return unsigned3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static unsigned3x4 operator - (unsigned lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned3x4 matrices.</summary>

	inline static unsigned3x4 operator / (const unsigned3x4& lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static unsigned3x4 operator / (const unsigned3x4& lhs, unsigned rhs) { return unsigned3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static unsigned3x4 operator / (unsigned lhs, const unsigned3x4& rhs) { return unsigned3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

	/// <summary>Returns the result of a componentwise increment operation on a unsigned3x4 matrix.</summary>

	inline static unsigned3x4 operator ++ (unsigned3x4 val) { return unsigned3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned3x4 matrix.</summary>

	inline static unsigned3x4 operator -- (unsigned3x4 val) { return unsigned3x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned3x4 matrices.</summary>

	inline static bool3x4 operator < (const unsigned3x4& lhs, const unsigned3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static bool3x4 operator < (const unsigned3x4& lhs, unsigned rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static bool3x4 operator < (unsigned lhs, const unsigned3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned3x4 matrices.</summary>

	inline static bool3x4 operator <= (const unsigned3x4& lhs, const unsigned3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static bool3x4 operator <= (const unsigned3x4& lhs, unsigned rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static bool3x4 operator <= (unsigned lhs, const unsigned3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned3x4 matrices.</summary>

	inline static bool3x4 operator > (const unsigned3x4& lhs, const unsigned3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static bool3x4 operator > (const unsigned3x4& lhs, unsigned rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static bool3x4 operator > (unsigned lhs, const unsigned3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned3x4 matrices.</summary>

	inline static bool3x4 operator >= (const unsigned3x4& lhs, const unsigned3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static bool3x4 operator >= (const unsigned3x4& lhs, unsigned rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static bool3x4 operator >= (unsigned lhs, const unsigned3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two unsigned3x4 matrices.</summary>

	inline static bool3x4 operator == (const unsigned3x4& lhs, const unsigned3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static bool3x4 operator == (const unsigned3x4& lhs, unsigned rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static bool3x4 operator == (unsigned lhs, const unsigned3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned3x4 matrices.</summary>

	inline static bool3x4 operator != (const unsigned3x4& lhs, const unsigned3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned3x4 matrix and a unsigned value.</summary>

	inline static bool3x4 operator != (const unsigned3x4& lhs, unsigned rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned3x4 matrix.</summary>

	inline static bool3x4 operator != (unsigned lhs, const unsigned3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region unsigned4
	struct unsigned4 {
		unsigned x, y, z, w;
		unsigned4() : x(0), y(0), z(0), w(0) {}
		unsigned4(unsigned x, unsigned y, unsigned z, unsigned w) : x(x), y(y), z(z), w(w) {}
		unsigned4(unsigned v) : x(v), y(v), z(v), w(v) {}
		unsigned4(unsigned3 xyz, unsigned w) : w(w)
		{
			x = xyz.x;
			y = xyz.y;
			z = xyz.z;
		}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned4 vectors.</summary>

	inline static unsigned4 operator * (const unsigned4& lhs, const unsigned4& rhs) { return unsigned4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned4 vector and a unsigned value.</summary>

	inline static unsigned4 operator * (const unsigned4& lhs, unsigned rhs) { return unsigned4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned4 vector.</summary>

	inline static unsigned4 operator * (unsigned lhs, const unsigned4& rhs) { return unsigned4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned4 vectors.</summary>

	inline static unsigned4 operator + (const unsigned4& lhs, const unsigned4& rhs) { return unsigned4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned4 vector and a unsigned value.</summary>

	inline static unsigned4 operator + (const unsigned4& lhs, unsigned rhs) { return unsigned4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned4 vector.</summary>

	inline static unsigned4 operator + (unsigned lhs, const unsigned4& rhs) { return unsigned4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned4 vectors.</summary>

	inline static unsigned4 operator - (const unsigned4& lhs, const unsigned4& rhs) { return unsigned4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned4 vector and a unsigned value.</summary>

	inline static unsigned4 operator - (const unsigned4& lhs, unsigned rhs) { return unsigned4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned4 vector.</summary>

	inline static unsigned4 operator - (unsigned lhs, const unsigned4& rhs) { return unsigned4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned4 vectors.</summary>

	inline static unsigned4 operator / (const unsigned4& lhs, const unsigned4& rhs) { return unsigned4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned4 vector and a unsigned value.</summary>

	inline static unsigned4 operator / (const unsigned4& lhs, unsigned rhs) { return unsigned4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned4 vector.</summary>

	inline static unsigned4 operator / (unsigned lhs, const unsigned4& rhs) { return unsigned4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

	/// <summary>Returns the result of a componentwise increment operation on a unsigned4 vector.</summary>

	inline static unsigned4 operator ++ (unsigned4 val) { return unsigned4(++val.x, ++val.y, ++val.z, ++val.w); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned4 vector.</summary>

	inline static unsigned4 operator -- (unsigned4 val) { return unsigned4(--val.x, --val.y, --val.z, --val.w); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned4 vectors.</summary>

	inline static bool4 operator < (const unsigned4& lhs, const unsigned4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned4 vector and a unsigned value.</summary>

	inline static bool4 operator < (const unsigned4& lhs, unsigned rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned4 vector.</summary>

	inline static bool4 operator < (unsigned lhs, const unsigned4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned4 vectors.</summary>

	inline static bool4 operator <= (const unsigned4& lhs, const unsigned4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned4 vector and a unsigned value.</summary>

	inline static bool4 operator <= (const unsigned4& lhs, unsigned rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned4 vector.</summary>

	inline static bool4 operator <= (unsigned lhs, const unsigned4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned4 vectors.</summary>

	inline static bool4 operator > (const unsigned4& lhs, const unsigned4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned4 vector and a unsigned value.</summary>

	inline static bool4 operator > (const unsigned4& lhs, unsigned rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned4 vector.</summary>

	inline static bool4 operator > (unsigned lhs, const unsigned4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned4 vectors.</summary>

	inline static bool4 operator >= (const unsigned4& lhs, const unsigned4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned4 vector and a unsigned value.</summary>

	inline static bool4 operator >= (const unsigned4& lhs, unsigned rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned4 vector.</summary>

	inline static bool4 operator >= (unsigned lhs, const unsigned4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned4 vectors.</summary>

	inline static bool4 operator == (const unsigned4& lhs, const unsigned4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned4 vector and a unsigned value.</summary>

	inline static bool4 operator == (const unsigned4& lhs, unsigned rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned4 vector.</summary>

	inline static bool4 operator == (unsigned lhs, const unsigned4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned4 vectors.</summary>

	inline static bool4 operator != (const unsigned4& lhs, const unsigned4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned4 vector and a unsigned value.</summary>

	inline static bool4 operator != (const unsigned4& lhs, unsigned rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned4 vector.</summary>

	inline static bool4 operator != (unsigned lhs, const unsigned4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region unsigned4x2
	struct unsigned4x2
	{
		unsigned4 c0, c1;
		unsigned4x2() : c0(), c1() {}
		unsigned4x2(unsigned m00, unsigned m01,
			unsigned m10, unsigned m11,
			unsigned m20, unsigned m21,
			unsigned m30, unsigned m31)
		{
			c0 = unsigned4(m00, m10, m20, m30);
			c1 = unsigned4(m01, m11, m21, m31);
		}
		unsigned4x2(unsigned4 c0, unsigned4 c1) : c0(c0), c1(c1) {}
		unsigned4x2(unsigned v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned4x2 matrices.</summary>

	inline static unsigned4x2 operator * (const unsigned4x2& lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static unsigned4x2 operator * (const unsigned4x2& lhs, unsigned rhs) { return unsigned4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static unsigned4x2 operator * (unsigned lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned4x2 matrices.</summary>

	inline static unsigned4x2 operator + (const unsigned4x2& lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static unsigned4x2 operator + (const unsigned4x2& lhs, unsigned rhs) { return unsigned4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static unsigned4x2 operator + (unsigned lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned4x2 matrices.</summary>

	inline static unsigned4x2 operator - (const unsigned4x2& lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static unsigned4x2 operator - (const unsigned4x2& lhs, unsigned rhs) { return unsigned4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static unsigned4x2 operator - (unsigned lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned4x2 matrices.</summary>

	inline static unsigned4x2 operator / (const unsigned4x2& lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static unsigned4x2 operator / (const unsigned4x2& lhs, unsigned rhs) { return unsigned4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static unsigned4x2 operator / (unsigned lhs, const unsigned4x2& rhs) { return unsigned4x2(lhs / rhs.c0, lhs / rhs.c1); }

	/// <summary>Returns the result of a componentwise increment operation on a unsigned4x2 matrix.</summary>

	inline static unsigned4x2 operator ++ (unsigned4x2 val) { return unsigned4x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned4x2 matrix.</summary>

	inline static unsigned4x2 operator -- (unsigned4x2 val) { return unsigned4x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned4x2 matrices.</summary>

	inline static bool4x2 operator < (const unsigned4x2& lhs, const unsigned4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static bool4x2 operator < (const unsigned4x2& lhs, unsigned rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static bool4x2 operator < (unsigned lhs, const unsigned4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned4x2 matrices.</summary>

	inline static bool4x2 operator <= (const unsigned4x2& lhs, const unsigned4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static bool4x2 operator <= (const unsigned4x2& lhs, unsigned rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static bool4x2 operator <= (unsigned lhs, const unsigned4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned4x2 matrices.</summary>

	inline static bool4x2 operator > (const unsigned4x2& lhs, const unsigned4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static bool4x2 operator > (const unsigned4x2& lhs, unsigned rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static bool4x2 operator > (unsigned lhs, const unsigned4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned4x2 matrices.</summary>

	inline static bool4x2 operator >= (const unsigned4x2& lhs, const unsigned4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static bool4x2 operator >= (const unsigned4x2& lhs, unsigned rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static bool4x2 operator >= (unsigned lhs, const unsigned4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two unsigned4x2 matrices.</summary>

	inline static bool4x2 operator == (const unsigned4x2& lhs, const unsigned4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static bool4x2 operator == (const unsigned4x2& lhs, unsigned rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static bool4x2 operator == (unsigned lhs, const unsigned4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned4x2 matrices.</summary>

	inline static bool4x2 operator != (const unsigned4x2& lhs, const unsigned4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned4x2 matrix and a unsigned value.</summary>

	inline static bool4x2 operator != (const unsigned4x2& lhs, unsigned rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned4x2 matrix.</summary>

	inline static bool4x2 operator != (unsigned lhs, const unsigned4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region unsigned4x3
	struct unsigned4x3
	{
		unsigned4 c0, c1, c2;
		unsigned4x3() : c0(), c1(), c2() {}
		unsigned4x3(unsigned m00, unsigned m01, unsigned m02,
			unsigned m10, unsigned m11, unsigned m12,
			unsigned m20, unsigned m21, unsigned m22,
			unsigned m30, unsigned m31, unsigned m32)
		{
			c0 = unsigned4(m00, m10, m20, m30);
			c1 = unsigned4(m01, m11, m21, m31);
			c2 = unsigned4(m02, m12, m22, m32);
		}
		unsigned4x3(unsigned4 c0, unsigned4 c1, unsigned4 c2) : c0(c0), c1(c1), c2(c2) {}
		unsigned4x3(unsigned v) : c0(v), c1(v), c2(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned4x3 matrices.</summary>

	inline static unsigned4x3 operator * (const unsigned4x3& lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static unsigned4x3 operator * (const unsigned4x3& lhs, unsigned rhs) { return unsigned4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static unsigned4x3 operator * (unsigned lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned4x3 matrices.</summary>

	inline static unsigned4x3 operator + (const unsigned4x3& lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static unsigned4x3 operator + (const unsigned4x3& lhs, unsigned rhs) { return unsigned4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static unsigned4x3 operator + (unsigned lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned4x3 matrices.</summary>

	inline static unsigned4x3 operator - (const unsigned4x3& lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static unsigned4x3 operator - (const unsigned4x3& lhs, unsigned rhs) { return unsigned4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static unsigned4x3 operator - (unsigned lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned4x3 matrices.</summary>

	inline static unsigned4x3 operator / (const unsigned4x3& lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static unsigned4x3 operator / (const unsigned4x3& lhs, unsigned rhs) { return unsigned4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static unsigned4x3 operator / (unsigned lhs, const unsigned4x3& rhs) { return unsigned4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a unsigned4x3 matrix.</summary>

	inline static unsigned4x3 operator ++ (unsigned4x3 val) { return unsigned4x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned4x3 matrix.</summary>

	inline static unsigned4x3 operator -- (unsigned4x3 val) { return unsigned4x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned4x3 matrices.</summary>

	inline static bool4x3 operator < (const unsigned4x3& lhs, const unsigned4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static bool4x3 operator < (const unsigned4x3& lhs, unsigned rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static bool4x3 operator < (unsigned lhs, const unsigned4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned4x3 matrices.</summary>

	inline static bool4x3 operator <= (const unsigned4x3& lhs, const unsigned4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static bool4x3 operator <= (const unsigned4x3& lhs, unsigned rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static bool4x3 operator <= (unsigned lhs, const unsigned4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned4x3 matrices.</summary>

	inline static bool4x3 operator > (const unsigned4x3& lhs, const unsigned4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static bool4x3 operator > (const unsigned4x3& lhs, unsigned rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static bool4x3 operator > (unsigned lhs, const unsigned4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned4x3 matrices.</summary>

	inline static bool4x3 operator >= (const unsigned4x3& lhs, const unsigned4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static bool4x3 operator >= (const unsigned4x3& lhs, unsigned rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static bool4x3 operator >= (unsigned lhs, const unsigned4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two unsigned4x3 matrices.</summary>

	inline static bool4x3 operator == (const unsigned4x3& lhs, const unsigned4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static bool4x3 operator == (const unsigned4x3& lhs, unsigned rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static bool4x3 operator == (unsigned lhs, const unsigned4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned4x3 matrices.</summary>

	inline static bool4x3 operator != (const unsigned4x3& lhs, const unsigned4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned4x3 matrix and a unsigned value.</summary>

	inline static bool4x3 operator != (const unsigned4x3& lhs, unsigned rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned4x3 matrix.</summary>

	inline static bool4x3 operator != (unsigned lhs, const unsigned4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region unsigned4x4
	struct unsigned4x4
	{
		unsigned4 c0, c1, c2, c3;
		unsigned4x4() : c0(), c1(), c2(), c3() {}
		unsigned4x4(unsigned m00, unsigned m01, unsigned m02, unsigned m03,
			unsigned m10, unsigned m11, unsigned m12, unsigned m13,
			unsigned m20, unsigned m21, unsigned m22, unsigned m23,
			unsigned m30, unsigned m31, unsigned m32, unsigned m33)
		{
			c0 = unsigned4(m00, m10, m20, m30);
			c1 = unsigned4(m01, m11, m21, m31);
			c2 = unsigned4(m02, m12, m22, m32);
			c3 = unsigned4(m03, m13, m23, m33);
		}
		unsigned4x4(unsigned4 c0, unsigned4 c1, unsigned4 c2, unsigned4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		unsigned4x4(unsigned v) : c0(v), c1(v), c2(v), c3(v) {}

		unsigned4x4(unsigned3x3 rotation, unsigned3 translation)
		{
			c0 = unsigned4(rotation.c0, 0.0f);
			c1 = unsigned4(rotation.c1, 0.0f);
			c2 = unsigned4(rotation.c2, 0.0f);
			c3 = unsigned4(translation, 1.0f);
		}


	};


	/// <summary>Returns the result of a componentwise multiplication operation on two unsigned4x4 matrices.</summary>

	inline static unsigned4x4 operator * (const unsigned4x4& lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static unsigned4x4 operator * (const unsigned4x4& lhs, unsigned rhs) { return unsigned4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static unsigned4x4 operator * (unsigned lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two unsigned4x4 matrices.</summary>

	inline static unsigned4x4 operator + (const unsigned4x4& lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static unsigned4x4 operator + (const unsigned4x4& lhs, unsigned rhs) { return unsigned4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static unsigned4x4 operator + (unsigned lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two unsigned4x4 matrices.</summary>

	inline static unsigned4x4 operator - (const unsigned4x4& lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static unsigned4x4 operator - (const unsigned4x4& lhs, unsigned rhs) { return unsigned4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static unsigned4x4 operator - (unsigned lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two unsigned4x4 matrices.</summary>

	inline static unsigned4x4 operator / (const unsigned4x4& lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static unsigned4x4 operator / (const unsigned4x4& lhs, unsigned rhs) { return unsigned4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static unsigned4x4 operator / (unsigned lhs, const unsigned4x4& rhs) { return unsigned4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a unsigned4x4 matrix.</summary>

	inline static unsigned4x4 operator ++ (unsigned4x4 val) { return unsigned4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a unsigned4x4 matrix.</summary>

	inline static unsigned4x4 operator -- (unsigned4x4 val) { return unsigned4x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two unsigned4x4 matrices.</summary>

	inline static bool4x4 operator < (const unsigned4x4& lhs, const unsigned4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static bool4x4 operator < (const unsigned4x4& lhs, unsigned rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static bool4x4 operator < (unsigned lhs, const unsigned4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two unsigned4x4 matrices.</summary>

	inline static bool4x4 operator <= (const unsigned4x4& lhs, const unsigned4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static bool4x4 operator <= (const unsigned4x4& lhs, unsigned rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static bool4x4 operator <= (unsigned lhs, const unsigned4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two unsigned4x4 matrices.</summary>

	inline static bool4x4 operator > (const unsigned4x4& lhs, const unsigned4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static bool4x4 operator > (const unsigned4x4& lhs, unsigned rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static bool4x4 operator > (unsigned lhs, const unsigned4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two unsigned4x4 matrices.</summary>

	inline static bool4x4 operator >= (const unsigned4x4& lhs, const unsigned4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static bool4x4 operator >= (const unsigned4x4& lhs, unsigned rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static bool4x4 operator >= (unsigned lhs, const unsigned4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on two unsigned4x4 matrices.</summary>

	inline static bool4x4 operator == (const unsigned4x4& lhs, const unsigned4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static bool4x4 operator == (const unsigned4x4& lhs, unsigned rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static bool4x4 operator == (unsigned lhs, const unsigned4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two unsigned4x4 matrices.</summary>

	inline static bool4x4 operator != (const unsigned4x4& lhs, const unsigned4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned4x4 matrix and a unsigned value.</summary>

	inline static bool4x4 operator != (const unsigned4x4& lhs, unsigned rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a unsigned value and a unsigned4x4 matrix.</summary>

	inline static bool4x4 operator != (unsigned lhs, const unsigned4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic


	/// <summary>Returns the Tangent of a unsigned value.</summary>
	inline static unsigned Tan(unsigned x) { return (unsigned)tan(x); }

	/// <summary>Returns the componentwise Tangent of a unsigned2 vector.</summary>
	inline static unsigned2 Tan(unsigned2 x) { return unsigned2(Tan(x.x), Tan(x.y)); }

	/// <summary>Returns the componentwise Tangent of a unsigned3 vector.</summary>
	inline static unsigned3 Tan(unsigned3 x) { return unsigned3(Tan(x.x), Tan(x.y), Tan(x.z)); }

	/// <summary>Returns the componentwise Tangent of a unsigned4 vector.</summary>
	inline static unsigned4 Tan(unsigned4 x) { return unsigned4(Tan(x.x), Tan(x.y), Tan(x.z), Tan(x.w)); }


	/// <summary>Returns the hyperbolic Tangent of a unsigned value.</summary>
	inline static unsigned Tanh(unsigned x) { return (unsigned)tanh(x); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a unsigned2 vector.</summary>
	inline static unsigned2 Tanh(unsigned2 x) { return unsigned2(Tanh(x.x), Tanh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a unsigned3 vector.</summary>
	inline static unsigned3 Tanh(unsigned3 x) { return unsigned3(Tanh(x.x), Tanh(x.y), Tanh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a unsigned4 vector.</summary>
	inline static unsigned4 Tanh(unsigned4 x) { return unsigned4(Tanh(x.x), Tanh(x.y), Tanh(x.z), Tanh(x.w)); }


	/// <summary>Returns the arcTangent of a unsigned value.</summary>
	inline static unsigned Atan(unsigned x) { return (unsigned)atan(x); }

	/// <summary>Returns the componentwise arcTangent of a unsigned2 vector.</summary>
	inline static unsigned2 Atan(unsigned2 x) { return unsigned2(Atan(x.x), Atan(x.y)); }

	/// <summary>Returns the componentwise arcTangent of a unsigned3 vector.</summary>
	inline static unsigned3 Atan(unsigned3 x) { return unsigned3(Atan(x.x), Atan(x.y), Atan(x.z)); }

	/// <summary>Returns the componentwise arcTangent of a unsigned4 vector.</summary>
	inline static unsigned4 Atan(unsigned4 x) { return unsigned4(Atan(x.x), Atan(x.y), Atan(x.z), Atan(x.w)); }


	/// <summary>Returns the 2-argument arcTangent of a pair of unsigned values.</summary>
	inline static unsigned Atan2(unsigned y, unsigned x) { return (unsigned)atan2(y, x); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of unsigneds2 vectors.</summary>
	inline static unsigned2 Atan2(unsigned2 y, unsigned2 x) { return unsigned2(Atan2(y.x, x.x), Atan2(y.y, x.y)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of unsigneds3 vectors.</summary>
	inline static unsigned3 Atan2(unsigned3 y, unsigned3 x) { return unsigned3(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of unsigneds4 vectors.</summary>
	inline static unsigned4 Atan2(unsigned4 y, unsigned4 x) { return unsigned4(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z), Atan2(y.w, x.w)); }


	/// <summary>Returns the CoSine of a unsigned value.</summary>
	inline static unsigned Cos(unsigned x) { return (unsigned)cos(x); }

	/// <summary>Returns the componentwise CoSine of a unsigned2 vector.</summary>
	inline static unsigned2 Cos(unsigned2 x) { return unsigned2(Cos(x.x), Cos(x.y)); }

	/// <summary>Returns the componentwise CoSine of a unsigned3 vector.</summary>
	inline static unsigned3 Cos(unsigned3 x) { return unsigned3(Cos(x.x), Cos(x.y), Cos(x.z)); }

	/// <summary>Returns the componentwise CoSine of a unsigned4 vector.</summary>
	inline static unsigned4 Cos(unsigned4 x) { return unsigned4(Cos(x.x), Cos(x.y), Cos(x.z), Cos(x.w)); }


	/// <summary>Returns the hyperbolic CoSine of a unsigned value.</summary>
	inline static unsigned Cosh(unsigned x) { return (unsigned)cosh(x); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a unsigned2 vector.</summary>
	inline static unsigned2 Cosh(unsigned2 x) { return unsigned2(Cosh(x.x), Cosh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a unsigned3 vector.</summary>
	inline static unsigned3 Cosh(unsigned3 x) { return unsigned3(Cosh(x.x), Cosh(x.y), Cosh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a unsigned4 vector.</summary>
	inline static unsigned4 Cosh(unsigned4 x) { return unsigned4(Cosh(x.x), Cosh(x.y), Cosh(x.z), Cosh(x.w)); }

	/// <summary>Returns the arcCoSine of a unsigned value.</summary>
	inline static unsigned Acos(unsigned x) { return (unsigned)acos((unsigned)x); }

	/// <summary>Returns the componentwise arcCoSine of a unsigned2 vector.</summary>
	inline static unsigned2 Acos(unsigned2 x) { return unsigned2(Acos(x.x), Acos(x.y)); }

	/// <summary>Returns the componentwise arcCoSine of a unsigned3 vector.</summary>
	inline static unsigned3 Acos(unsigned3 x) { return unsigned3(Acos(x.x), Acos(x.y), Acos(x.z)); }

	/// <summary>Returns the componentwise arcCoSine of a unsigned4 vector.</summary>
	inline static unsigned4 Acos(unsigned4 x) { return unsigned4(Acos(x.x), Acos(x.y), Acos(x.z), Acos(x.w)); }


	/// <summary>Returns the Sine of a unsigned value.</summary>
	inline static unsigned Sin(unsigned x) { return (unsigned)sin((unsigned)x); }

	/// <summary>Returns the componentwise Sine of a unsigned2 vector.</summary>
	inline static unsigned2 Sin(unsigned2 x) { return unsigned2(Sin(x.x), Sin(x.y)); }

	/// <summary>Returns the componentwise Sine of a unsigned3 vector.</summary>
	inline static unsigned3 Sin(unsigned3 x) { return unsigned3(Sin(x.x), Sin(x.y), Sin(x.z)); }

	/// <summary>Returns the componentwise Sine of a unsigned4 vector.</summary>
	inline static unsigned4 Sin(unsigned4 x) { return unsigned4(Sin(x.x), Sin(x.y), Sin(x.z), Sin(x.w)); }



	/// <summary>Returns the hyperbolic Sine of a unsigned value.</summary>
	inline static unsigned Sinh(unsigned x) { return (unsigned)sinh((unsigned)x); }

	/// <summary>Returns the componentwise hyperbolic Sine of a unsigned2 vector.</summary>
	inline static unsigned2 Sinh(unsigned2 x) { return unsigned2(Sinh(x.x), Sinh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a unsigned3 vector.</summary>
	inline static unsigned3 Sinh(unsigned3 x) { return unsigned3(Sinh(x.x), Sinh(x.y), Sinh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a unsigned4 vector.</summary>
	inline static unsigned4 Sinh(unsigned4 x) { return unsigned4(Sinh(x.x), Sinh(x.y), Sinh(x.z), Sinh(x.w)); }


	/// <summary>Returns the arcSine of a unsigned value.</summary>
	inline static unsigned Asin(unsigned x) { return (unsigned)asin((unsigned)x); }

	/// <summary>Returns the componentwise arcSine of a unsigned2 vector.</summary>
	inline static unsigned2 Asin(unsigned2 x) { return unsigned2(Asin(x.x), Asin(x.y)); }

	/// <summary>Returns the componentwise arcSine of a unsigned3 vector.</summary>
	inline static unsigned3 Asin(unsigned3 x) { return unsigned3(Asin(x.x), Asin(x.y), Asin(x.z)); }

	/// <summary>Returns the componentwise arcSine of a unsigned4 vector.</summary>
	inline static unsigned4 Asin(unsigned4 x) { return unsigned4(Asin(x.x), Asin(x.y), Asin(x.z), Asin(x.w)); }


	/// <summary>Returns the Dot product of two unsigned values. Equivalent to multiplication.</summary>
	inline static unsigned Dot(unsigned x, unsigned y) { return x * y; }

	/// <summary>Returns the Dot product of two unsigned2 vectors.</summary>
	inline static unsigned Dot(unsigned2 x, unsigned2 y) { return x.x * y.x + x.y * y.y; }

	/// <summary>Returns the Dot product of two unsigned3 vectors.</summary>
	inline static unsigned Dot(unsigned3 x, unsigned3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }

	/// <summary>Returns the Dot product of two unsigned4 vectors.</summary>
	inline static unsigned Dot(unsigned4 x, unsigned4 y) { return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w; }

	/// <summary>Returns the square root of a unsigned value.</summary>
	inline static unsigned Sqrt(unsigned x) { return sqrt((double)x); }

	/// <summary>Returns the componentwise square root of a unsigned2 vector.</summary>
	inline static unsigned2 Sqrt(unsigned2 x) { return unsigned2(Sqrt(x.x), Sqrt(x.y)); }

	/// <summary>Returns the componentwise square root of a unsigned3 vector.</summary>
	inline static unsigned3 Sqrt(unsigned3 x) { return unsigned3(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z)); }

	/// <summary>Returns the componentwise square root of a unsigned4 vector.</summary>
	inline static unsigned4 Sqrt(unsigned4 x) { return unsigned4(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z), Sqrt(x.w)); }


	/// <summary>Returns the reciprocal square root of a unsigned value.</summary>
	inline static unsigned Rsqrt(unsigned x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a unsigned2 vector.</summary>
	inline static unsigned2 Rsqrt(unsigned2 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a unsigned3 vector.</summary>
	inline static unsigned3 Rsqrt(unsigned3 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a unsigned4 vector</summary>
	inline static unsigned4 Rsqrt(unsigned4 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns a Normalized version of the unsigned2 vector x by scaling it by 1 / Length(x).</summary>
	inline static unsigned2 Normalize(unsigned2 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the unsigned3 vector x by scaling it by 1 / Length(x).</summary>
	inline static unsigned3 Normalize(unsigned3 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the unsigned4 vector x by scaling it by 1 / Length(x).</summary>
	inline static unsigned4 Normalize(unsigned4 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns the Length of a unsigned2 vector.</summary>
	inline static unsigned Length(unsigned2 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a unsigned3 vector.</summary>
	inline static unsigned Length(unsigned3 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a unsigned4 vector.</summary>
	inline static unsigned Length(unsigned4 x) { return sqrt(Dot(x, x)); }




	/// <summary>Returns the squared Length of a unsigned value. Equivalent to squaring the value.</summary>
	inline static unsigned Lengthsq(unsigned x) { return x * x; }

	/// <summary>Returns the squared Length of a unsigned2 vector.</summary>
	inline static unsigned Lengthsq(unsigned2 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a unsigned3 vector.</summary>
	inline static unsigned Lengthsq(unsigned3 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a unsigned4 vector.</summary>
	inline static unsigned Lengthsq(unsigned4 x) { return Dot(x, x); }


	/// <summary>Returns the Distance between two unsigned2 vectors.</summary>
	inline static unsigned Distance(unsigned2 x, unsigned2 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two unsigned3 vectors.</summary>
	inline static unsigned Distance(unsigned3 x, unsigned3 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two unsigned4 vectors.</summary>
	inline static unsigned Distance(unsigned4 x, unsigned4 y) { return Length(y - x); }



	/// <summary>Returns the Distance between two unsigned values.</summary>
	inline static unsigned Distancesq(unsigned x, unsigned y) { return (y - x) * (y - x); }

	/// <summary>Returns the Distance between two unsigned2 vectors.</summary>
	inline static unsigned Distancesq(unsigned2 x, unsigned2 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two unsigned3 vectors.</summary>
	inline static unsigned Distancesq(unsigned3 x, unsigned3 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two unsigned4 vectors.</summary>
	inline static unsigned Distancesq(unsigned4 x, unsigned4 y) { return Lengthsq(y - x); }



	/// <summary>Returns the Cross product of two unsigned3 vectors.</summary>
	inline static unsigned3 Cross(unsigned3 x, unsigned3 y) {
		unsigned3 retVal = x * unsigned3(y.y, y.z, y.x) - unsigned3(x.y, x.z, x.x) * y;
		return unsigned3(retVal.y, retVal.z, retVal.x);
	}

	/// <summary>Returns the Sine and CoSine of the input unsigned value x through the out parameters s and c.</summary>
	inline static void SinCos(unsigned x, unsigned* s, unsigned* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input unsigned2 vector x through the out parameters s and c.</summary>
	inline static void SinCos(unsigned2 x, unsigned2* s, unsigned2* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input unsigned3 vector x through the out parameters s and c.</summary>
	inline static void SinCos(unsigned3 x, unsigned3* s, unsigned3* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input unsigned4 vector x through the out parameters s and c.</summary>
	inline static void SinCos(unsigned4 x, unsigned4* s, unsigned4* c) { *s = Sin(x); *c = Cos(x); }


	/// <summary>Returns the Minimum of two unsigned values.</summary>
	inline static unsigned Min(unsigned x, unsigned y) { return x < y ? x : y; }

	/// <summary>Returns the componentwise Minimum of two unsigned2 vectors.</summary>
	inline static unsigned2 Min(unsigned2 x, unsigned2 y) { return unsigned2(Min(x.x, y.x), Min(x.y, y.y)); }

	/// <summary>Returns the componentwise Minimum of two unsigned3 vectors.</summary>
	inline static unsigned3 Min(unsigned3 x, unsigned3 y) { return unsigned3(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z)); }

	/// <summary>Returns the componentwise Minimum of two unsigned4 vectors.</summary>
	inline static unsigned4 Min(unsigned4 x, unsigned4 y) { return unsigned4(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z), Min(x.w, y.w)); }


	/// <summary>Returns the Maximum of two unsigned values.</summary>
	inline static unsigned Max(unsigned x, unsigned y) { return x > y ? x : y; }

	/// <summary>Returns the componentwise Maximum of two unsigned2 vectors.</summary>
	inline static unsigned2 Max(unsigned2 x, unsigned2 y) { return unsigned2(Max(x.x, y.x), Max(x.y, y.y)); }

	/// <summary>Returns the componentwise Maximum of two unsigned3 vectors.</summary>
	inline static unsigned3 Max(unsigned3 x, unsigned3 y) { return unsigned3(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z)); }

	/// <summary>Returns the componentwise Maximum of two unsigned4 vectors.</summary>
	inline static unsigned4 Max(unsigned4 x, unsigned4 y) { return unsigned4(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z), Max(x.w, y.w)); }

	inline static unsigned Lerp(unsigned x, unsigned y, unsigned s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static unsigned2 Lerp(unsigned2 x, unsigned2 y, unsigned s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static unsigned3 Lerp(unsigned3 x, unsigned3 y, unsigned s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static unsigned4 Lerp(unsigned4 x, unsigned4 y, unsigned s) { return x + s * (y - x); }


	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static unsigned2 Lerp(unsigned2 x, unsigned2 y, unsigned2 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static unsigned3 Lerp(unsigned3 x, unsigned3 y, unsigned3 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static unsigned4 Lerp(unsigned4 x, unsigned4 y, unsigned4 s) { return x + s * (y - x); }

	/// <summary>Returns the result of normalizing a unsigneding point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static unsigned Unlerp(unsigned a, unsigned b, unsigned x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a unsigneding point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static unsigned2 Unlerp(unsigned2 a, unsigned2 b, unsigned2 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a unsigneding point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static unsigned3 Unlerp(unsigned3 a, unsigned3 b, unsigned3 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a unsigneding point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static unsigned4 Unlerp(unsigned4 a, unsigned4 b, unsigned4 x) { return (x - a) / (b - a); }

	/// <summary>Returns the result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static unsigned Remap(unsigned a, unsigned b, unsigned c, unsigned d, unsigned x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static unsigned2 Remap(unsigned2 a, unsigned2 b, unsigned2 c, unsigned2 d, unsigned2 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static unsigned3 Remap(unsigned3 a, unsigned3 b, unsigned3 c, unsigned3 d, unsigned3 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static unsigned4 Remap(unsigned4 a, unsigned4 b, unsigned4 c, unsigned4 d, unsigned4 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the result of Clamping the value x into the interval [a, b], where x, a and b are unsigned values.</summary>
	inline static unsigned Clamp(unsigned x, unsigned a, unsigned b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are unsigned2 vectors.</summary>
	inline static unsigned2 Clamp(unsigned2 x, unsigned2 a, unsigned2 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are unsigned3 vectors.</summary>
	inline static unsigned3 Clamp(unsigned3 x, unsigned3 a, unsigned3 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are unsigned4 vectors.</summary>
	inline static unsigned4 Clamp(unsigned4 x, unsigned4 a, unsigned4 b) { return Max(a, Min(b, x)); }

	inline static unsigned select_shuffle_component(unsigned4 a, unsigned4 b, char component)
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

	inline static unsigned4 shuffle(unsigned4 a, unsigned4 b, char x, char y, char z, char w)
	{
		return unsigned4(
			select_shuffle_component(a, b, x),
			select_shuffle_component(a, b, y),
			select_shuffle_component(a, b, z),
			select_shuffle_component(a, b, w));
	}

	inline static unsigned4 movelh(unsigned4 a, unsigned4 b)
	{
		return shuffle(a, b, 0, 1, 4, 5);
	}
	inline static unsigned4 movehl(unsigned4 a, unsigned4 b)
	{
		return shuffle(b, a, 2, 3, 6, 7);
	}
	// SSE shuffles
	inline static unsigned4 unpacklo(unsigned4 a, unsigned4 b)
	{
		return shuffle(a, b, 0, 4, 1, 5);
	}
	inline static unsigned4 unpackhi(unsigned4 a, unsigned4 b)
	{
		return shuffle(a, b, 2, 6, 3, 7);
	}
#pragma endregion
#pragma region Component
	/// <summary>Returns the Maximum component of a unsigned2 vector.</summary>
	inline static unsigned CMax(unsigned2 x) { return Max(x.x, x.y); }

	/// <summary>Returns the Maximum component of a unsigned3 vector.</summary>
	inline static unsigned CMax(unsigned3 x) { return Max(Max(x.x, x.y), x.z); }

	/// <summary>Returns the Maximum component of a unsigned4 vector.</summary>
	inline static unsigned CMax(unsigned4 x) { return Max(Max(x.x, x.y), Max(x.z, x.w)); }

	/// <summary>Returns the horizontal sum of components of a unsigned2 vector.</summary>
	inline static unsigned Csum(unsigned2 x) { return x.x + x.y; }

	/// <summary>Returns the horizontal sum of components of a unsigned3 vector.</summary>
	inline static unsigned Csum(unsigned3 x) { return x.x + x.y + x.z; }

	/// <summary>Returns the horizontal sum of components of a unsigned4 vector.</summary>
	inline static unsigned Csum(unsigned4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion

#pragma region Transpose
	/// <summary>Return the unsigned2x2 Transpose of a unsigned2x2 matrix.</summary>
	inline unsigned2x2 Transpose(unsigned2x2 v)
	{
		return unsigned2x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y);
	}
	/// <summary>Return the unsigned3x2 Transpose of a unsigned2x3 matrix.</summary>
	inline unsigned3x2 Transpose(unsigned2x3 v)
	{
		return unsigned3x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y);
	}
	/// <summary>Return the unsigned4x2 Transpose of a unsigned2x4 matrix.</summary>
	inline unsigned4x2 Transpose(unsigned2x4 v)
	{
		return unsigned4x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y,
			v.c3.x, v.c3.y);
	}
	/// <summary>Return the unsigned2x3 Transpose of a unsigned3x2 matrix.</summary>
	inline unsigned2x3 Transpose(unsigned3x2 v)
	{
		return unsigned2x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z);
	}
	/// <summary>Return the unsigned3x3 Transpose of a unsigned3x3 matrix.</summary>
	inline unsigned3x3 Transpose(unsigned3x3 v)
	{
		return unsigned3x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z);
	}
	/// <summary>Return the unsigned4x3 Transpose of a unsigned3x4 matrix.</summary>
	inline static unsigned4x3 Transpose(unsigned3x4 v)
	{
		return unsigned4x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z,
			v.c3.x, v.c3.y, v.c3.z);
	}
	/// <summary>Return the unsigned2x4 Transpose of a unsigned4x2 matrix.</summary>
	inline static unsigned2x4 Transpose(unsigned4x2 v)
	{
		return unsigned2x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w);
	}
	/// <summary>Return the unsigned3x4 Transpose of a unsigned4x3 matrix.</summary>
	inline static unsigned3x4 Transpose(unsigned4x3 v)
	{
		return unsigned3x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w);
	}
	/// <summary>Return the unsigned4x4 Transpose of a unsigned4x4 matrix.</summary>
	inline static unsigned4x4 Transpose(unsigned4x4 v)
	{
		return unsigned4x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w,
			v.c3.x, v.c3.y, v.c3.z, v.c3.w);
	}

#pragma endregion
#pragma region Inverse
	
	/// <summary>Returns the unsigned3x3 full Inverse of a unsigned3x3 matrix.</summary>
	inline unsigned3x3 Inverse(unsigned3x3 m)
	{
		unsigned3 c0 = m.c0;
		unsigned3 c1 = m.c1;
		unsigned3 c2 = m.c2;

		unsigned3 t0 = unsigned3(c1.x, c2.x, c0.x);
		unsigned3 t1 = unsigned3(c1.y, c2.y, c0.y);
		unsigned3 t2 = unsigned3(c1.z, c2.z, c0.z);

		unsigned3 m0 = t1 * unsigned3(t2.y, t2.z, t2.x) - unsigned3(t1.y, t1.z, t1.x) * t2;
		unsigned3 m1 = unsigned3(t0.y, t0.z, t0.x) * t2 - t0 * unsigned3(t2.y, t2.z, t2.x);
		unsigned3 m2 = t0 * unsigned3(t1.y, t1.z, t1.x) - t0 * unsigned3(t2.y, t2.z, t2.x) * t1;

		unsigned rcpDet = 1.0f / Csum(unsigned3(t0.z, t0.x, t0.y) * m0);
		return unsigned3x3(m0, m1, m2) * rcpDet;
	}
	
	/// <summary>Returns the unsigned4x4 full Inverse of a unsigned4x4 matrix.</summary>
	inline static unsigned4x4 Inverse(unsigned4x4 m)
	{
		unsigned4 c0 = m.c0;
		unsigned4 c1 = m.c1;
		unsigned4 c2 = m.c2;
		unsigned4 c3 = m.c3;

		unsigned4 r0y_r1y_r0x_r1x = movelh(c1, c0);
		unsigned4 r0z_r1z_r0w_r1w = movelh(c2, c3);
		unsigned4 r2y_r3y_r2x_r3x = movehl(c0, c1);
		unsigned4 r2z_r3z_r2w_r3w = movehl(c3, c2);

		unsigned4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
		unsigned4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
		unsigned4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
		unsigned4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

		unsigned4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
		unsigned4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
		unsigned4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
		unsigned4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
		unsigned4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

		// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
		unsigned4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
		unsigned4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
		unsigned4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

		// Expand inner terms back to 4 components. zw signs still need to be flipped
		unsigned4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
		unsigned4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

		unsigned4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
		unsigned4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

		// Calculate Minors
		unsigned4 Minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

		unsigned4 denom = r0_xyzw * Minors0;

		// Horizontal sum of denoMinator. Free sign flip of z and w compensates for misSing flip in inner terms.
		denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
		denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

		unsigned4 rcp_denom_ppnn = unsigned4(1.0f) / denom;
		unsigned4x4 res;
		res.c0 = Minors0 * rcp_denom_ppnn;

		unsigned4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
		unsigned4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

		unsigned4 Minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
		res.c1 = Minors1 * rcp_denom_ppnn;

		unsigned4 Minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
		res.c2 = Minors2 * rcp_denom_ppnn;

		unsigned4 Minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
		res.c3 = Minors3 * rcp_denom_ppnn;
		return res;
	}
	
#pragma endregion
#pragma region DeterMinant
	/// <summary>Returns the DeterMinant of a unsigned2x2 matrix.</summary>
	inline unsigned DeterMinant(unsigned2x2 m)
	{
		unsigned a = m.c0.x;
		unsigned b = m.c1.x;
		unsigned c = m.c0.y;
		unsigned d = m.c1.y;

		return a * d - b * c;
	}
	/// <summary>Returns the DeterMinant of a unsigned3x3 matrix.</summary>
	inline unsigned DeterMinant(unsigned3x3 m)
	{
		unsigned3 c0 = m.c0;
		unsigned3 c1 = m.c1;
		unsigned3 c2 = m.c2;

		unsigned m00 = c1.y * c2.z - c1.z * c2.y;
		unsigned m01 = c0.y * c2.z - c0.z * c2.y;
		unsigned m02 = c0.y * c1.z - c0.z * c1.y;

		return c0.x * m00 - c1.x * m01 + c2.x * m02;
	}
	/// <summary>Returns the DeterMinant of a unsigned4x4 matrix.</summary>
	inline static unsigned DeterMinant(unsigned4x4 m)
	{
		unsigned4 c0 = m.c0;
		unsigned4 c1 = m.c1;
		unsigned4 c2 = m.c2;
		unsigned4 c3 = m.c3;

		unsigned m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
		unsigned m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
		unsigned m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
		unsigned m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

		return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
	}

#pragma endregion
}