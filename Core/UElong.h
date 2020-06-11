#pragma once
#include "UEbool.h"
#include <math.h>
namespace UniEngine {
#pragma region long2
	struct long2 {
		long x, y;
		long2() : x(0), y(0) {}
		long2(long x, long y) : x(x), y(y) {}
		long2(long v) : x(v), y(v) {}
	};
	/// <summary>Returns the result of a componentwise multiplication operation on two long2 vectors.</summary>

	inline static long2 operator * (const long2& lhs, const long2& rhs) { return long2(lhs.x * rhs.x, lhs.y * rhs.y); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long2 vector and a long value.</summary>

	inline static long2 operator * (const long2& lhs, long rhs) { return long2(lhs.x * rhs, lhs.y * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long2 vector.</summary>

	inline static long2 operator * (long lhs, const long2& rhs) { return long2(lhs * rhs.x, lhs * rhs.y); }


	/// <summary>Returns the result of a componentwise addition operation on two long2 vectors.</summary>

	inline static long2 operator + (const long2& lhs, const long2& rhs) { return long2(lhs.x + rhs.x, lhs.y + rhs.y); }

	/// <summary>Returns the result of a componentwise addition operation on a long2 vector and a long value.</summary>

	inline static long2 operator + (const long2& lhs, long rhs) { return long2(lhs.x + rhs, lhs.y + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long2 vector.</summary>

	inline static long2 operator + (long lhs, const long2& rhs) { return long2(lhs + rhs.x, lhs + rhs.y); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long2 vectors.</summary>

	inline static long2 operator - (const long2& lhs, const long2& rhs) { return long2(lhs.x - rhs.x, lhs.y - rhs.y); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long2 vector and a long value.</summary>

	inline static long2 operator - (const long2& lhs, long rhs) { return long2(lhs.x - rhs, lhs.y - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long2 vector.</summary>

	inline static long2 operator - (long lhs, const long2& rhs) { return long2(lhs - rhs.x, lhs - rhs.y); }


	/// <summary>Returns the result of a componentwise division operation on two long2 vectors.</summary>

	inline static long2 operator / (const long2& lhs, const long2& rhs) { return long2(lhs.x / rhs.x, lhs.y / rhs.y); }

	/// <summary>Returns the result of a componentwise division operation on a long2 vector and a long value.</summary>

	inline static long2 operator / (const long2& lhs, long rhs) { return long2(lhs.x / rhs, lhs.y / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long2 vector.</summary>

	inline static long2 operator / (long lhs, const long2& rhs) { return long2(lhs / rhs.x, lhs / rhs.y); }

	/// <summary>Returns the result of a componentwise increment operation on a long2 vector.</summary>

	inline static long2 operator ++ (long2 val) { return long2(++val.x, ++val.y); }


	/// <summary>Returns the result of a componentwise decrement operation on a long2 vector.</summary>

	inline static long2 operator -- (long2 val) { return long2(--val.x, --val.y); }


	/// <summary>Returns the result of a componentwise less than operation on two long2 vectors.</summary>

	inline static bool2 operator < (const long2& lhs, const long2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

	/// <summary>Returns the result of a componentwise less than operation on a long2 vector and a long value.</summary>

	inline static bool2 operator < (const long2& lhs, long rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long2 vector.</summary>

	inline static bool2 operator < (long lhs, const long2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long2 vectors.</summary>

	inline static bool2 operator <= (const long2& lhs, const long2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long2 vector and a long value.</summary>

	inline static bool2 operator <= (const long2& lhs, long rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long2 vector.</summary>

	inline static bool2 operator <= (long lhs, const long2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


	/// <summary>Returns the result of a componentwise greater than operation on two long2 vectors.</summary>

	inline static bool2 operator > (const long2& lhs, const long2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

	/// <summary>Returns the result of a componentwise greater than operation on a long2 vector and a long value.</summary>

	inline static bool2 operator > (const long2& lhs, long rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long2 vector.</summary>

	inline static bool2 operator > (long lhs, const long2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long2 vectors.</summary>

	inline static bool2 operator >= (const long2& lhs, const long2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long2 vector and a long value.</summary>

	inline static bool2 operator >= (const long2& lhs, long rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long2 vector.</summary>

	inline static bool2 operator >= (long lhs, const long2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long2 vector.</summary>

	inline static long2 operator - (long2 val) { return long2(-val.x, -val.y); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long2 vector.</summary>

	inline static long2 operator + (long2 val) { return long2(+val.x, +val.y); }


	/// <summary>Returns the result of a componentwise equality operation on two long2 vectors.</summary>

	inline static bool2 operator == (const long2& lhs, const long2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on a long2 vector and a long value.</summary>

	inline static bool2 operator == (const long2& lhs, long rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long2 vector.</summary>

	inline static bool2 operator == (long lhs, const long2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


	/// <summary>Returns the result of a componentwise not equal operation on two long2 vectors.</summary>

	inline static bool2 operator != (const long2& lhs, const long2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

	/// <summary>Returns the result of a componentwise not equal operation on a long2 vector and a long value.</summary>

	inline static bool2 operator != (const long2& lhs, long rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long2 vector.</summary>

	inline static bool2 operator != (long lhs, const long2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region long2x2
	struct long2x2
	{
		long2 c0, c1;
		long2x2() : c0(), c1() {}
		long2x2(long m00, long m01,
			long m10, long m11) :c0(long2(m00, m10)), c1(long2(m01, m11)) {}
		long2x2(long2 c0, long2 c1) : c0(c0), c1(c1) {}
		long2x2(long v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long2x2 matrices.</summary>

	inline static long2x2 operator * (const long2x2& lhs, const long2x2& rhs) { return long2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long2x2 matrix and a long value.</summary>

	inline static long2x2 operator * (const long2x2& lhs, long rhs) { return long2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long2x2 matrix.</summary>

	inline static long2x2 operator * (long lhs, const long2x2& rhs) { return long2x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two long2x2 matrices.</summary>

	inline static long2x2 operator + (const long2x2& lhs, const long2x2& rhs) { return long2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a long2x2 matrix and a long value.</summary>

	inline static long2x2 operator + (const long2x2& lhs, long rhs) { return long2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long2x2 matrix.</summary>

	inline static long2x2 operator + (long lhs, const long2x2& rhs) { return long2x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long2x2 matrices.</summary>

	inline static long2x2 operator - (const long2x2& lhs, const long2x2& rhs) { return long2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long2x2 matrix and a long value.</summary>

	inline static long2x2 operator - (const long2x2& lhs, long rhs) { return long2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long2x2 matrix.</summary>

	inline static long2x2 operator - (long lhs, const long2x2& rhs) { return long2x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two long2x2 matrices.</summary>

	inline static long2x2 operator / (const long2x2& lhs, const long2x2& rhs) { return long2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a long2x2 matrix and a long value.</summary>

	inline static long2x2 operator / (const long2x2& lhs, long rhs) { return long2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long2x2 matrix.</summary>

	inline static long2x2 operator / (long lhs, const long2x2& rhs) { return long2x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a long2x2 matrix.</summary>

	inline static long2x2 operator ++ (long2x2 val) { return long2x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a long2x2 matrix.</summary>

	inline static long2x2 operator -- (long2x2 val) { return long2x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two long2x2 matrices.</summary>

	inline static bool2x2 operator < (const long2x2& lhs, const long2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a long2x2 matrix and a long value.</summary>

	inline static bool2x2 operator < (const long2x2& lhs, long rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long2x2 matrix.</summary>

	inline static bool2x2 operator < (long lhs, const long2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long2x2 matrices.</summary>

	inline static bool2x2 operator <= (const long2x2& lhs, const long2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long2x2 matrix and a long value.</summary>

	inline static bool2x2 operator <= (const long2x2& lhs, long rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long2x2 matrix.</summary>

	inline static bool2x2 operator <= (long lhs, const long2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two long2x2 matrices.</summary>

	inline static bool2x2 operator > (const long2x2& lhs, const long2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a long2x2 matrix and a long value.</summary>

	inline static bool2x2 operator > (const long2x2& lhs, long rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long2x2 matrix.</summary>

	inline static bool2x2 operator > (long lhs, const long2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long2x2 matrices.</summary>

	inline static bool2x2 operator >= (const long2x2& lhs, const long2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long2x2 matrix and a long value.</summary>

	inline static bool2x2 operator >= (const long2x2& lhs, long rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long2x2 matrix.</summary>

	inline static bool2x2 operator >= (long lhs, const long2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long2x2 matrix.</summary>

	inline static long2x2 operator - (long2x2 val) { return long2x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long2x2 matrix.</summary>

	inline static long2x2 operator + (long2x2 val) { return long2x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two long2x2 matrices.</summary>

	inline static bool2x2 operator == (const long2x2& lhs, const long2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a long2x2 matrix and a long value.</summary>

	inline static bool2x2 operator == (const long2x2& lhs, long rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long2x2 matrix.</summary>

	inline static bool2x2 operator == (long lhs, const long2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two long2x2 matrices.</summary>

	inline static bool2x2 operator != (const long2x2& lhs, const long2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a long2x2 matrix and a long value.</summary>

	inline static bool2x2 operator != (const long2x2& lhs, long rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long2x2 matrix.</summary>

	inline static bool2x2 operator != (long lhs, const long2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region long2x3
	struct long2x3
	{
		long2 c0, c1, c2;
		long2x3() : c0(), c1(), c2() {}
		long2x3(long m00, long m01, long m02,
			long m10, long m11, long m12)
		{
			c0 = long2(m00, m10);
			c1 = long2(m01, m11);
			c2 = long2(m02, m12);
		}
		long2x3(long2 c0, long2 c1, long2 c2) : c0(c0), c1(c1), c2(c2) {}
		long2x3(long v) : c0(v), c1(v), c2(v) {}
	};

	/// <summary>Returns the result of a componentwise multiplication operation on two long2x3 matrices.</summary>

	inline static long2x3 operator * (const long2x3& lhs, const long2x3& rhs) { return long2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long2x3 matrix and a long value.</summary>

	inline static long2x3 operator * (const long2x3& lhs, long rhs) { return long2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long2x3 matrix.</summary>

	inline static long2x3 operator * (long lhs, const long2x3& rhs) { return long2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two long2x3 matrices.</summary>

	inline static long2x3 operator + (const long2x3& lhs, const long2x3& rhs) { return long2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a long2x3 matrix and a long value.</summary>

	inline static long2x3 operator + (const long2x3& lhs, long rhs) { return long2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long2x3 matrix.</summary>

	inline static long2x3 operator + (long lhs, const long2x3& rhs) { return long2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long2x3 matrices.</summary>

	inline static long2x3 operator - (const long2x3& lhs, const long2x3& rhs) { return long2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long2x3 matrix and a long value.</summary>

	inline static long2x3 operator - (const long2x3& lhs, long rhs) { return long2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long2x3 matrix.</summary>

	inline static long2x3 operator - (long lhs, const long2x3& rhs) { return long2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two long2x3 matrices.</summary>

	inline static long2x3 operator / (const long2x3& lhs, const long2x3& rhs) { return long2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a long2x3 matrix and a long value.</summary>

	inline static long2x3 operator / (const long2x3& lhs, long rhs) { return long2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long2x3 matrix.</summary>

	inline static long2x3 operator / (long lhs, const long2x3& rhs) { return long2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


	/// <summary>Returns the result of a componentwise increment operation on a long2x3 matrix.</summary>

	inline static long2x3 operator ++ (long2x3 val) { return long2x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a long2x3 matrix.</summary>

	inline static long2x3 operator -- (long2x3 val) { return long2x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two long2x3 matrices.</summary>

	inline static bool2x3 operator < (const long2x3& lhs, const long2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a long2x3 matrix and a long value.</summary>

	inline static bool2x3 operator < (const long2x3& lhs, long rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long2x3 matrix.</summary>

	inline static bool2x3 operator < (long lhs, const long2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long2x3 matrices.</summary>

	inline static bool2x3 operator <= (const long2x3& lhs, const long2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long2x3 matrix and a long value.</summary>

	inline static bool2x3 operator <= (const long2x3& lhs, long rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long2x3 matrix.</summary>

	inline static bool2x3 operator <= (long lhs, const long2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two long2x3 matrices.</summary>

	inline static bool2x3 operator > (const long2x3& lhs, const long2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a long2x3 matrix and a long value.</summary>

	inline static bool2x3 operator > (const long2x3& lhs, long rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long2x3 matrix.</summary>

	inline static bool2x3 operator > (long lhs, const long2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long2x3 matrices.</summary>

	inline static bool2x3 operator >= (const long2x3& lhs, const long2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long2x3 matrix and a long value.</summary>

	inline static bool2x3 operator >= (const long2x3& lhs, long rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long2x3 matrix.</summary>

	inline static bool2x3 operator >= (long lhs, const long2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long2x3 matrix.</summary>

	inline static long2x3 operator - (long2x3 val) { return long2x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long2x3 matrix.</summary>

	inline static long2x3 operator + (long2x3 val) { return long2x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two long2x3 matrices.</summary>

	inline static bool2x3 operator == (const long2x3& lhs, const long2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a long2x3 matrix and a long value.</summary>

	inline static bool2x3 operator == (const long2x3& lhs, long rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long2x3 matrix.</summary>

	inline static bool2x3 operator == (long lhs, const long2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two long2x3 matrices.</summary>

	inline static bool2x3 operator != (const long2x3& lhs, const long2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a long2x3 matrix and a long value.</summary>

	inline static bool2x3 operator != (const long2x3& lhs, long rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long2x3 matrix.</summary>

	inline static bool2x3 operator != (long lhs, const long2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region long2x4
	struct long2x4
	{
		long2 c0, c1, c2, c3;
		long2x4() : c0(), c1(), c2(), c3() {}
		long2x4(long m00, long m01, long m02, long m03,
			long m10, long m11, long m12, long m13)
		{
			c0 = long2(m00, m10);
			c1 = long2(m01, m11);
			c2 = long2(m02, m12);
			c3 = long2(m03, m13);
		}
		long2x4(long2 c0, long2 c1, long2 c2, long2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		long2x4(long v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long2x4 matrices.</summary>

	inline static long2x4 operator * (const long2x4& lhs, const long2x4& rhs) { return long2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long2x4 matrix and a long value.</summary>

	inline static long2x4 operator * (const long2x4& lhs, long rhs) { return long2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long2x4 matrix.</summary>

	inline static long2x4 operator * (long lhs, const long2x4& rhs) { return long2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two long2x4 matrices.</summary>

	inline static long2x4 operator + (const long2x4& lhs, const long2x4& rhs) { return long2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a long2x4 matrix and a long value.</summary>

	inline static long2x4 operator + (const long2x4& lhs, long rhs) { return long2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long2x4 matrix.</summary>

	inline static long2x4 operator + (long lhs, const long2x4& rhs) { return long2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long2x4 matrices.</summary>

	inline static long2x4 operator - (const long2x4& lhs, const long2x4& rhs) { return long2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long2x4 matrix and a long value.</summary>

	inline static long2x4 operator - (const long2x4& lhs, long rhs) { return long2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long2x4 matrix.</summary>

	inline static long2x4 operator - (long lhs, const long2x4& rhs) { return long2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two long2x4 matrices.</summary>

	inline static long2x4 operator / (const long2x4& lhs, const long2x4& rhs) { return long2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a long2x4 matrix and a long value.</summary>

	inline static long2x4 operator / (const long2x4& lhs, long rhs) { return long2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long2x4 matrix.</summary>

	inline static long2x4 operator / (long lhs, const long2x4& rhs) { return long2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a long2x4 matrix.</summary>

	inline static long2x4 operator ++ (long2x4 val) { return long2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a long2x4 matrix.</summary>

	inline static long2x4 operator -- (long2x4 val) { return long2x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two long2x4 matrices.</summary>

	inline static bool2x4 operator < (const long2x4& lhs, const long2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a long2x4 matrix and a long value.</summary>

	inline static bool2x4 operator < (const long2x4& lhs, long rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long2x4 matrix.</summary>

	inline static bool2x4 operator < (long lhs, const long2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long2x4 matrices.</summary>

	inline static bool2x4 operator <= (const long2x4& lhs, const long2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long2x4 matrix and a long value.</summary>

	inline static bool2x4 operator <= (const long2x4& lhs, long rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long2x4 matrix.</summary>

	inline static bool2x4 operator <= (long lhs, const long2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two long2x4 matrices.</summary>

	inline static bool2x4 operator > (const long2x4& lhs, const long2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a long2x4 matrix and a long value.</summary>

	inline static bool2x4 operator > (const long2x4& lhs, long rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long2x4 matrix.</summary>

	inline static bool2x4 operator > (long lhs, const long2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long2x4 matrices.</summary>

	inline static bool2x4 operator >= (const long2x4& lhs, const long2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long2x4 matrix and a long value.</summary>

	inline static bool2x4 operator >= (const long2x4& lhs, long rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long2x4 matrix.</summary>

	inline static bool2x4 operator >= (long lhs, const long2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long2x4 matrix.</summary>

	inline static long2x4 operator - (long2x4 val) { return long2x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long2x4 matrix.</summary>

	inline static long2x4 operator + (long2x4 val) { return long2x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two long2x4 matrices.</summary>

	inline static bool2x4 operator == (const long2x4& lhs, const long2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a long2x4 matrix and a long value.</summary>

	inline static bool2x4 operator == (const long2x4& lhs, long rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long2x4 matrix.</summary>

	inline static bool2x4 operator == (long lhs, const long2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two long2x4 matrices.</summary>

	inline static bool2x4 operator != (const long2x4& lhs, const long2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a long2x4 matrix and a long value.</summary>

	inline static bool2x4 operator != (const long2x4& lhs, long rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long2x4 matrix.</summary>

	inline static bool2x4 operator != (long lhs, const long2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region long3
	struct long3 {
		long x, y, z;
		long3() : x(0), y(0), z(0) {}
		long3(long x, long y, long z) : x(x), y(y), z(z) {}
		long3(long v) : x(v), y(v), z(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long3 vectors.</summary>

	inline static long3 operator * (const long3& lhs, const long3& rhs) { return long3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long3 vector and a long value.</summary>

	inline static long3 operator * (const long3& lhs, long rhs) { return long3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long3 vector.</summary>

	inline static long3 operator * (long lhs, const long3& rhs) { return long3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


	/// <summary>Returns the result of a componentwise addition operation on two long3 vectors.</summary>

	inline static long3 operator + (const long3& lhs, const long3& rhs) { return long3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

	/// <summary>Returns the result of a componentwise addition operation on a long3 vector and a long value.</summary>

	inline static long3 operator + (const long3& lhs, long rhs) { return long3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long3 vector.</summary>

	inline static long3 operator + (long lhs, const long3& rhs) { return long3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long3 vectors.</summary>

	inline static long3 operator - (const long3& lhs, const long3& rhs) { return long3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long3 vector and a long value.</summary>

	inline static long3 operator - (const long3& lhs, long rhs) { return long3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long3 vector.</summary>

	inline static long3 operator - (long lhs, const long3& rhs) { return long3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


	/// <summary>Returns the result of a componentwise division operation on two long3 vectors.</summary>

	inline static long3 operator / (const long3& lhs, const long3& rhs) { return long3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

	/// <summary>Returns the result of a componentwise division operation on a long3 vector and a long value.</summary>

	inline static long3 operator / (const long3& lhs, long rhs) { return long3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long3 vector.</summary>

	inline static long3 operator / (long lhs, const long3& rhs) { return long3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


	/// <summary>Returns the result of a componentwise increment operation on a long3 vector.</summary>

	inline static long3 operator ++ (long3 val) { return long3(++val.x, ++val.y, ++val.z); }


	/// <summary>Returns the result of a componentwise decrement operation on a long3 vector.</summary>

	inline static long3 operator -- (long3 val) { return long3(--val.x, --val.y, --val.z); }


	/// <summary>Returns the result of a componentwise less than operation on two long3 vectors.</summary>

	inline static bool3 operator < (const long3& lhs, const long3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

	/// <summary>Returns the result of a componentwise less than operation on a long3 vector and a long value.</summary>

	inline static bool3 operator < (const long3& lhs, long rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long3 vector.</summary>

	inline static bool3 operator < (long lhs, const long3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long3 vectors.</summary>

	inline static bool3 operator <= (const long3& lhs, const long3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long3 vector and a long value.</summary>

	inline static bool3 operator <= (const long3& lhs, long rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long3 vector.</summary>

	inline static bool3 operator <= (long lhs, const long3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


	/// <summary>Returns the result of a componentwise greater than operation on two long3 vectors.</summary>

	inline static bool3 operator > (const long3& lhs, const long3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

	/// <summary>Returns the result of a componentwise greater than operation on a long3 vector and a long value.</summary>

	inline static bool3 operator > (const long3& lhs, long rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long3 vector.</summary>

	inline static bool3 operator > (long lhs, const long3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long3 vectors.</summary>

	inline static bool3 operator >= (const long3& lhs, const long3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long3 vector and a long value.</summary>

	inline static bool3 operator >= (const long3& lhs, long rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long3 vector.</summary>

	inline static bool3 operator >= (long lhs, const long3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long3 vector.</summary>

	inline static long3 operator - (long3 val) { return long3(-val.x, -val.y, -val.z); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long3 vector.</summary>

	inline static long3 operator + (long3 val) { return long3(+val.x, +val.y, +val.z); }


	/// <summary>Returns the result of a componentwise equality operation on two long3 vectors.</summary>

	inline static bool3 operator == (const long3& lhs, const long3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

	/// <summary>Returns the result of a componentwise equality operation on a long3 vector and a long value.</summary>

	inline static bool3 operator == (const long3& lhs, long rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long3 vector.</summary>

	inline static bool3 operator == (long lhs, const long3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


	/// <summary>Returns the result of a componentwise not equal operation on two long3 vectors.</summary>

	inline static bool3 operator != (const long3& lhs, const long3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

	/// <summary>Returns the result of a componentwise not equal operation on a long3 vector and a long value.</summary>

	inline static bool3 operator != (const long3& lhs, long rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long3 vector.</summary>

	inline static bool3 operator != (long lhs, const long3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region long3x2
	struct long3x2
	{
		long3 c0, c1;
		long3x2() : c0(), c1() {}
		long3x2(long m00, long m01,
			long m10, long m11,
			long m20, long m21)
		{
			c0 = long3(m00, m10, m20);
			c1 = long3(m01, m11, m21);
		}

		long3x2(long3 c0, long3 c1) : c0(c0), c1(c1) {}
		long3x2(long v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long3x2 matrices.</summary>

	inline static long3x2 operator * (const long3x2& lhs, const long3x2& rhs) { return long3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long3x2 matrix and a long value.</summary>

	inline static long3x2 operator * (const long3x2& lhs, long rhs) { return long3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long3x2 matrix.</summary>

	inline static long3x2 operator * (long lhs, const long3x2& rhs) { return long3x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two long3x2 matrices.</summary>

	inline static long3x2 operator + (const long3x2& lhs, const long3x2& rhs) { return long3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a long3x2 matrix and a long value.</summary>

	inline static long3x2 operator + (const long3x2& lhs, long rhs) { return long3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long3x2 matrix.</summary>

	inline static long3x2 operator + (long lhs, const long3x2& rhs) { return long3x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long3x2 matrices.</summary>

	inline static long3x2 operator - (const long3x2& lhs, const long3x2& rhs) { return long3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long3x2 matrix and a long value.</summary>

	inline static long3x2 operator - (const long3x2& lhs, long rhs) { return long3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long3x2 matrix.</summary>

	inline static long3x2 operator - (long lhs, const long3x2& rhs) { return long3x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two long3x2 matrices.</summary>

	inline static long3x2 operator / (const long3x2& lhs, const long3x2& rhs) { return long3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a long3x2 matrix and a long value.</summary>

	inline static long3x2 operator / (const long3x2& lhs, long rhs) { return long3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long3x2 matrix.</summary>

	inline static long3x2 operator / (long lhs, const long3x2& rhs) { return long3x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a long3x2 matrix.</summary>

	inline static long3x2 operator ++ (long3x2 val) { return long3x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a long3x2 matrix.</summary>

	inline static long3x2 operator -- (long3x2 val) { return long3x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two long3x2 matrices.</summary>

	inline static bool3x2 operator < (const long3x2& lhs, const long3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a long3x2 matrix and a long value.</summary>

	inline static bool3x2 operator < (const long3x2& lhs, long rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long3x2 matrix.</summary>

	inline static bool3x2 operator < (long lhs, const long3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long3x2 matrices.</summary>

	inline static bool3x2 operator <= (const long3x2& lhs, const long3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long3x2 matrix and a long value.</summary>

	inline static bool3x2 operator <= (const long3x2& lhs, long rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long3x2 matrix.</summary>

	inline static bool3x2 operator <= (long lhs, const long3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two long3x2 matrices.</summary>

	inline static bool3x2 operator > (const long3x2& lhs, const long3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a long3x2 matrix and a long value.</summary>

	inline static bool3x2 operator > (const long3x2& lhs, long rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long3x2 matrix.</summary>

	inline static bool3x2 operator > (long lhs, const long3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long3x2 matrices.</summary>

	inline static bool3x2 operator >= (const long3x2& lhs, const long3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long3x2 matrix and a long value.</summary>

	inline static bool3x2 operator >= (const long3x2& lhs, long rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long3x2 matrix.</summary>

	inline static bool3x2 operator >= (long lhs, const long3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long3x2 matrix.</summary>

	inline static long3x2 operator - (long3x2 val) { return long3x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long3x2 matrix.</summary>

	inline static long3x2 operator + (long3x2 val) { return long3x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two long3x2 matrices.</summary>

	inline static bool3x2 operator == (const long3x2& lhs, const long3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a long3x2 matrix and a long value.</summary>

	inline static bool3x2 operator == (const long3x2& lhs, long rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long3x2 matrix.</summary>

	inline static bool3x2 operator == (long lhs, const long3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two long3x2 matrices.</summary>

	inline static bool3x2 operator != (const long3x2& lhs, const long3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a long3x2 matrix and a long value.</summary>

	inline static bool3x2 operator != (const long3x2& lhs, long rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long3x2 matrix.</summary>

	inline static bool3x2 operator != (long lhs, const long3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region long3x3
	struct long3x3
	{
		long3 c0, c1, c2;
		long3x3() : c0(), c1(), c2() {}
		long3x3(long m00, long m01, long m02,
			long m10, long m11, long m12,
			long m20, long m21, long m22)
		{
			c0 = long3(m00, m10, m20);
			c1 = long3(m01, m11, m21);
			c2 = long3(m02, m12, m22);
		}
		long3x3(long3 c0, long3 c1, long3 c2) : c0(c0), c1(c1), c2(c2) {}
		long3x3(long v) : c0(v), c1(v), c2(v) {}

	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long3x3 matrices.</summary>

	inline static long3x3 operator * (const long3x3& lhs, const long3x3& rhs) { return long3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long3x3 matrix and a long value.</summary>

	inline static long3x3 operator * (const long3x3& lhs, long rhs) { return long3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long3x3 matrix.</summary>

	inline static long3x3 operator * (long lhs, const long3x3& rhs) { return long3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two long3x3 matrices.</summary>

	inline static long3x3 operator + (const long3x3& lhs, const long3x3& rhs) { return long3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a long3x3 matrix and a long value.</summary>

	inline static long3x3 operator + (const long3x3& lhs, long rhs) { return long3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long3x3 matrix.</summary>

	inline static long3x3 operator + (long lhs, const long3x3& rhs) { return long3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long3x3 matrices.</summary>

	inline static long3x3 operator - (const long3x3& lhs, const long3x3& rhs) { return long3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long3x3 matrix and a long value.</summary>

	inline static long3x3 operator - (const long3x3& lhs, long rhs) { return long3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long3x3 matrix.</summary>

	inline static long3x3 operator - (long lhs, const long3x3& rhs) { return long3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two long3x3 matrices.</summary>

	inline static long3x3 operator / (const long3x3& lhs, const long3x3& rhs) { return long3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a long3x3 matrix and a long value.</summary>

	inline static long3x3 operator / (const long3x3& lhs, long rhs) { return long3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long3x3 matrix.</summary>

	inline static long3x3 operator / (long lhs, const long3x3& rhs) { return long3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a long3x3 matrix.</summary>

	inline static long3x3 operator ++ (long3x3 val) { return long3x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a long3x3 matrix.</summary>

	inline static long3x3 operator -- (long3x3 val) { return long3x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two long3x3 matrices.</summary>

	inline static bool3x3 operator < (const long3x3& lhs, const long3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a long3x3 matrix and a long value.</summary>

	inline static bool3x3 operator < (const long3x3& lhs, long rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long3x3 matrix.</summary>

	inline static bool3x3 operator < (long lhs, const long3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long3x3 matrices.</summary>

	inline static bool3x3 operator <= (const long3x3& lhs, const long3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long3x3 matrix and a long value.</summary>

	inline static bool3x3 operator <= (const long3x3& lhs, long rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long3x3 matrix.</summary>

	inline static bool3x3 operator <= (long lhs, const long3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two long3x3 matrices.</summary>

	inline static bool3x3 operator > (const long3x3& lhs, const long3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a long3x3 matrix and a long value.</summary>

	inline static bool3x3 operator > (const long3x3& lhs, long rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long3x3 matrix.</summary>

	inline static bool3x3 operator > (long lhs, const long3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long3x3 matrices.</summary>

	inline static bool3x3 operator >= (const long3x3& lhs, const long3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long3x3 matrix and a long value.</summary>

	inline static bool3x3 operator >= (const long3x3& lhs, long rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long3x3 matrix.</summary>

	inline static bool3x3 operator >= (long lhs, const long3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long3x3 matrix.</summary>

	inline static long3x3 operator - (long3x3 val) { return long3x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long3x3 matrix.</summary>

	inline static long3x3 operator + (long3x3 val) { return long3x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two long3x3 matrices.</summary>

	inline static bool3x3 operator == (const long3x3& lhs, const long3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a long3x3 matrix and a long value.</summary>

	inline static bool3x3 operator == (const long3x3& lhs, long rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long3x3 matrix.</summary>

	inline static bool3x3 operator == (long lhs, const long3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two long3x3 matrices.</summary>

	inline static bool3x3 operator != (const long3x3& lhs, const long3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a long3x3 matrix and a long value.</summary>

	inline static bool3x3 operator != (const long3x3& lhs, long rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long3x3 matrix.</summary>

	inline static bool3x3 operator != (long lhs, const long3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region long3x4
	struct long3x4
	{
		long3 c0, c1, c2, c3;
		long3x4() : c0(), c1(), c2(), c3() {}
		long3x4(long m00, long m01, long m02, long m03,
			long m10, long m11, long m12, long m13,
			long m20, long m21, long m22, long m23)
		{
			c0 = long3(m00, m10, m20);
			c1 = long3(m01, m11, m21);
			c2 = long3(m02, m12, m22);
			c3 = long3(m03, m13, m23);
		}
		long3x4(long3 c0, long3 c1, long3 c2, long3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		long3x4(long v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long3x4 matrices.</summary>

	inline static long3x4 operator * (const long3x4& lhs, const long3x4& rhs) { return long3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long3x4 matrix and a long value.</summary>

	inline static long3x4 operator * (const long3x4& lhs, long rhs) { return long3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long3x4 matrix.</summary>

	inline static long3x4 operator * (long lhs, const long3x4& rhs) { return long3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two long3x4 matrices.</summary>

	inline static long3x4 operator + (const long3x4& lhs, const long3x4& rhs) { return long3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a long3x4 matrix and a long value.</summary>

	inline static long3x4 operator + (const long3x4& lhs, long rhs) { return long3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long3x4 matrix.</summary>

	inline static long3x4 operator + (long lhs, const long3x4& rhs) { return long3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long3x4 matrices.</summary>

	inline static long3x4 operator - (const long3x4& lhs, const long3x4& rhs) { return long3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long3x4 matrix and a long value.</summary>

	inline static long3x4 operator - (const long3x4& lhs, long rhs) { return long3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long3x4 matrix.</summary>

	inline static long3x4 operator - (long lhs, const long3x4& rhs) { return long3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two long3x4 matrices.</summary>

	inline static long3x4 operator / (const long3x4& lhs, const long3x4& rhs) { return long3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a long3x4 matrix and a long value.</summary>

	inline static long3x4 operator / (const long3x4& lhs, long rhs) { return long3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long3x4 matrix.</summary>

	inline static long3x4 operator / (long lhs, const long3x4& rhs) { return long3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

	/// <summary>Returns the result of a componentwise increment operation on a long3x4 matrix.</summary>

	inline static long3x4 operator ++ (long3x4 val) { return long3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a long3x4 matrix.</summary>

	inline static long3x4 operator -- (long3x4 val) { return long3x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two long3x4 matrices.</summary>

	inline static bool3x4 operator < (const long3x4& lhs, const long3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a long3x4 matrix and a long value.</summary>

	inline static bool3x4 operator < (const long3x4& lhs, long rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long3x4 matrix.</summary>

	inline static bool3x4 operator < (long lhs, const long3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long3x4 matrices.</summary>

	inline static bool3x4 operator <= (const long3x4& lhs, const long3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long3x4 matrix and a long value.</summary>

	inline static bool3x4 operator <= (const long3x4& lhs, long rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long3x4 matrix.</summary>

	inline static bool3x4 operator <= (long lhs, const long3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two long3x4 matrices.</summary>

	inline static bool3x4 operator > (const long3x4& lhs, const long3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a long3x4 matrix and a long value.</summary>

	inline static bool3x4 operator > (const long3x4& lhs, long rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long3x4 matrix.</summary>

	inline static bool3x4 operator > (long lhs, const long3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long3x4 matrices.</summary>

	inline static bool3x4 operator >= (const long3x4& lhs, const long3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long3x4 matrix and a long value.</summary>

	inline static bool3x4 operator >= (const long3x4& lhs, long rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long3x4 matrix.</summary>

	inline static bool3x4 operator >= (long lhs, const long3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long3x4 matrix.</summary>

	inline static long3x4 operator - (long3x4 val) { return long3x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long3x4 matrix.</summary>

	inline static long3x4 operator + (long3x4 val) { return long3x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two long3x4 matrices.</summary>

	inline static bool3x4 operator == (const long3x4& lhs, const long3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a long3x4 matrix and a long value.</summary>

	inline static bool3x4 operator == (const long3x4& lhs, long rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long3x4 matrix.</summary>

	inline static bool3x4 operator == (long lhs, const long3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two long3x4 matrices.</summary>

	inline static bool3x4 operator != (const long3x4& lhs, const long3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a long3x4 matrix and a long value.</summary>

	inline static bool3x4 operator != (const long3x4& lhs, long rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long3x4 matrix.</summary>

	inline static bool3x4 operator != (long lhs, const long3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region long4
	struct long4 {
		long x, y, z, w;
		long4() : x(0), y(0), z(0), w(0) {}
		long4(long x, long y, long z, long w) : x(x), y(y), z(z), w(w) {}
		long4(long v) : x(v), y(v), z(v), w(v) {}
		long4(long3 xyz, long w) : w(w)
		{
			x = xyz.x;
			y = xyz.y;
			z = xyz.z;
		}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long4 vectors.</summary>

	inline static long4 operator * (const long4& lhs, const long4& rhs) { return long4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long4 vector and a long value.</summary>

	inline static long4 operator * (const long4& lhs, long rhs) { return long4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long4 vector.</summary>

	inline static long4 operator * (long lhs, const long4& rhs) { return long4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


	/// <summary>Returns the result of a componentwise addition operation on two long4 vectors.</summary>

	inline static long4 operator + (const long4& lhs, const long4& rhs) { return long4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

	/// <summary>Returns the result of a componentwise addition operation on a long4 vector and a long value.</summary>

	inline static long4 operator + (const long4& lhs, long rhs) { return long4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long4 vector.</summary>

	inline static long4 operator + (long lhs, const long4& rhs) { return long4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long4 vectors.</summary>

	inline static long4 operator - (const long4& lhs, const long4& rhs) { return long4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long4 vector and a long value.</summary>

	inline static long4 operator - (const long4& lhs, long rhs) { return long4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long4 vector.</summary>

	inline static long4 operator - (long lhs, const long4& rhs) { return long4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


	/// <summary>Returns the result of a componentwise division operation on two long4 vectors.</summary>

	inline static long4 operator / (const long4& lhs, const long4& rhs) { return long4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

	/// <summary>Returns the result of a componentwise division operation on a long4 vector and a long value.</summary>

	inline static long4 operator / (const long4& lhs, long rhs) { return long4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long4 vector.</summary>

	inline static long4 operator / (long lhs, const long4& rhs) { return long4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

	/// <summary>Returns the result of a componentwise increment operation on a long4 vector.</summary>

	inline static long4 operator ++ (long4 val) { return long4(++val.x, ++val.y, ++val.z, ++val.w); }


	/// <summary>Returns the result of a componentwise decrement operation on a long4 vector.</summary>

	inline static long4 operator -- (long4 val) { return long4(--val.x, --val.y, --val.z, --val.w); }


	/// <summary>Returns the result of a componentwise less than operation on two long4 vectors.</summary>

	inline static bool4 operator < (const long4& lhs, const long4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

	/// <summary>Returns the result of a componentwise less than operation on a long4 vector and a long value.</summary>

	inline static bool4 operator < (const long4& lhs, long rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long4 vector.</summary>

	inline static bool4 operator < (long lhs, const long4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long4 vectors.</summary>

	inline static bool4 operator <= (const long4& lhs, const long4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long4 vector and a long value.</summary>

	inline static bool4 operator <= (const long4& lhs, long rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long4 vector.</summary>

	inline static bool4 operator <= (long lhs, const long4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


	/// <summary>Returns the result of a componentwise greater than operation on two long4 vectors.</summary>

	inline static bool4 operator > (const long4& lhs, const long4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

	/// <summary>Returns the result of a componentwise greater than operation on a long4 vector and a long value.</summary>

	inline static bool4 operator > (const long4& lhs, long rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long4 vector.</summary>

	inline static bool4 operator > (long lhs, const long4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long4 vectors.</summary>

	inline static bool4 operator >= (const long4& lhs, const long4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long4 vector and a long value.</summary>

	inline static bool4 operator >= (const long4& lhs, long rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long4 vector.</summary>

	inline static bool4 operator >= (long lhs, const long4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long4 vector.</summary>

	inline static long4 operator - (long4 val) { return long4(-val.x, -val.y, -val.z, -val.w); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long4 vector.</summary>

	inline static long4 operator + (long4 val) { return long4(+val.x, +val.y, +val.z, +val.w); }


	/// <summary>Returns the result of a componentwise equality operation on two long4 vectors.</summary>

	inline static bool4 operator == (const long4& lhs, const long4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on a long4 vector and a long value.</summary>

	inline static bool4 operator == (const long4& lhs, long rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long4 vector.</summary>

	inline static bool4 operator == (long lhs, const long4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


	/// <summary>Returns the result of a componentwise not equal operation on two long4 vectors.</summary>

	inline static bool4 operator != (const long4& lhs, const long4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

	/// <summary>Returns the result of a componentwise not equal operation on a long4 vector and a long value.</summary>

	inline static bool4 operator != (const long4& lhs, long rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long4 vector.</summary>

	inline static bool4 operator != (long lhs, const long4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region long4x2
	struct long4x2
	{
		long4 c0, c1;
		long4x2() : c0(), c1() {}
		long4x2(long m00, long m01,
			long m10, long m11,
			long m20, long m21,
			long m30, long m31)
		{
			c0 = long4(m00, m10, m20, m30);
			c1 = long4(m01, m11, m21, m31);
		}
		long4x2(long4 c0, long4 c1) : c0(c0), c1(c1) {}
		long4x2(long v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long4x2 matrices.</summary>

	inline static long4x2 operator * (const long4x2& lhs, const long4x2& rhs) { return long4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long4x2 matrix and a long value.</summary>

	inline static long4x2 operator * (const long4x2& lhs, long rhs) { return long4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long4x2 matrix.</summary>

	inline static long4x2 operator * (long lhs, const long4x2& rhs) { return long4x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two long4x2 matrices.</summary>

	inline static long4x2 operator + (const long4x2& lhs, const long4x2& rhs) { return long4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a long4x2 matrix and a long value.</summary>

	inline static long4x2 operator + (const long4x2& lhs, long rhs) { return long4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long4x2 matrix.</summary>

	inline static long4x2 operator + (long lhs, const long4x2& rhs) { return long4x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long4x2 matrices.</summary>

	inline static long4x2 operator - (const long4x2& lhs, const long4x2& rhs) { return long4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long4x2 matrix and a long value.</summary>

	inline static long4x2 operator - (const long4x2& lhs, long rhs) { return long4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long4x2 matrix.</summary>

	inline static long4x2 operator - (long lhs, const long4x2& rhs) { return long4x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two long4x2 matrices.</summary>

	inline static long4x2 operator / (const long4x2& lhs, const long4x2& rhs) { return long4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a long4x2 matrix and a long value.</summary>

	inline static long4x2 operator / (const long4x2& lhs, long rhs) { return long4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long4x2 matrix.</summary>

	inline static long4x2 operator / (long lhs, const long4x2& rhs) { return long4x2(lhs / rhs.c0, lhs / rhs.c1); }

	/// <summary>Returns the result of a componentwise increment operation on a long4x2 matrix.</summary>

	inline static long4x2 operator ++ (long4x2 val) { return long4x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a long4x2 matrix.</summary>

	inline static long4x2 operator -- (long4x2 val) { return long4x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two long4x2 matrices.</summary>

	inline static bool4x2 operator < (const long4x2& lhs, const long4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a long4x2 matrix and a long value.</summary>

	inline static bool4x2 operator < (const long4x2& lhs, long rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long4x2 matrix.</summary>

	inline static bool4x2 operator < (long lhs, const long4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long4x2 matrices.</summary>

	inline static bool4x2 operator <= (const long4x2& lhs, const long4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long4x2 matrix and a long value.</summary>

	inline static bool4x2 operator <= (const long4x2& lhs, long rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long4x2 matrix.</summary>

	inline static bool4x2 operator <= (long lhs, const long4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two long4x2 matrices.</summary>

	inline static bool4x2 operator > (const long4x2& lhs, const long4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a long4x2 matrix and a long value.</summary>

	inline static bool4x2 operator > (const long4x2& lhs, long rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long4x2 matrix.</summary>

	inline static bool4x2 operator > (long lhs, const long4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long4x2 matrices.</summary>

	inline static bool4x2 operator >= (const long4x2& lhs, const long4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long4x2 matrix and a long value.</summary>

	inline static bool4x2 operator >= (const long4x2& lhs, long rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long4x2 matrix.</summary>

	inline static bool4x2 operator >= (long lhs, const long4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long4x2 matrix.</summary>

	inline static long4x2 operator - (long4x2 val) { return long4x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long4x2 matrix.</summary>

	inline static long4x2 operator + (long4x2 val) { return long4x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two long4x2 matrices.</summary>

	inline static bool4x2 operator == (const long4x2& lhs, const long4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a long4x2 matrix and a long value.</summary>

	inline static bool4x2 operator == (const long4x2& lhs, long rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long4x2 matrix.</summary>

	inline static bool4x2 operator == (long lhs, const long4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two long4x2 matrices.</summary>

	inline static bool4x2 operator != (const long4x2& lhs, const long4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a long4x2 matrix and a long value.</summary>

	inline static bool4x2 operator != (const long4x2& lhs, long rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long4x2 matrix.</summary>

	inline static bool4x2 operator != (long lhs, const long4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region long4x3
	struct long4x3
	{
		long4 c0, c1, c2;
		long4x3() : c0(), c1(), c2() {}
		long4x3(long m00, long m01, long m02,
			long m10, long m11, long m12,
			long m20, long m21, long m22,
			long m30, long m31, long m32)
		{
			c0 = long4(m00, m10, m20, m30);
			c1 = long4(m01, m11, m21, m31);
			c2 = long4(m02, m12, m22, m32);
		}
		long4x3(long4 c0, long4 c1, long4 c2) : c0(c0), c1(c1), c2(c2) {}
		long4x3(long v) : c0(v), c1(v), c2(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long4x3 matrices.</summary>

	inline static long4x3 operator * (const long4x3& lhs, const long4x3& rhs) { return long4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long4x3 matrix and a long value.</summary>

	inline static long4x3 operator * (const long4x3& lhs, long rhs) { return long4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long4x3 matrix.</summary>

	inline static long4x3 operator * (long lhs, const long4x3& rhs) { return long4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two long4x3 matrices.</summary>

	inline static long4x3 operator + (const long4x3& lhs, const long4x3& rhs) { return long4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a long4x3 matrix and a long value.</summary>

	inline static long4x3 operator + (const long4x3& lhs, long rhs) { return long4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long4x3 matrix.</summary>

	inline static long4x3 operator + (long lhs, const long4x3& rhs) { return long4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long4x3 matrices.</summary>

	inline static long4x3 operator - (const long4x3& lhs, const long4x3& rhs) { return long4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long4x3 matrix and a long value.</summary>

	inline static long4x3 operator - (const long4x3& lhs, long rhs) { return long4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long4x3 matrix.</summary>

	inline static long4x3 operator - (long lhs, const long4x3& rhs) { return long4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two long4x3 matrices.</summary>

	inline static long4x3 operator / (const long4x3& lhs, const long4x3& rhs) { return long4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a long4x3 matrix and a long value.</summary>

	inline static long4x3 operator / (const long4x3& lhs, long rhs) { return long4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long4x3 matrix.</summary>

	inline static long4x3 operator / (long lhs, const long4x3& rhs) { return long4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a long4x3 matrix.</summary>

	inline static long4x3 operator ++ (long4x3 val) { return long4x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a long4x3 matrix.</summary>

	inline static long4x3 operator -- (long4x3 val) { return long4x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two long4x3 matrices.</summary>

	inline static bool4x3 operator < (const long4x3& lhs, const long4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a long4x3 matrix and a long value.</summary>

	inline static bool4x3 operator < (const long4x3& lhs, long rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long4x3 matrix.</summary>

	inline static bool4x3 operator < (long lhs, const long4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long4x3 matrices.</summary>

	inline static bool4x3 operator <= (const long4x3& lhs, const long4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long4x3 matrix and a long value.</summary>

	inline static bool4x3 operator <= (const long4x3& lhs, long rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long4x3 matrix.</summary>

	inline static bool4x3 operator <= (long lhs, const long4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two long4x3 matrices.</summary>

	inline static bool4x3 operator > (const long4x3& lhs, const long4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a long4x3 matrix and a long value.</summary>

	inline static bool4x3 operator > (const long4x3& lhs, long rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long4x3 matrix.</summary>

	inline static bool4x3 operator > (long lhs, const long4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long4x3 matrices.</summary>

	inline static bool4x3 operator >= (const long4x3& lhs, const long4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long4x3 matrix and a long value.</summary>

	inline static bool4x3 operator >= (const long4x3& lhs, long rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long4x3 matrix.</summary>

	inline static bool4x3 operator >= (long lhs, const long4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long4x3 matrix.</summary>

	inline static long4x3 operator - (long4x3 val) { return long4x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long4x3 matrix.</summary>

	inline static long4x3 operator + (long4x3 val) { return long4x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two long4x3 matrices.</summary>

	inline static bool4x3 operator == (const long4x3& lhs, const long4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a long4x3 matrix and a long value.</summary>

	inline static bool4x3 operator == (const long4x3& lhs, long rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long4x3 matrix.</summary>

	inline static bool4x3 operator == (long lhs, const long4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two long4x3 matrices.</summary>

	inline static bool4x3 operator != (const long4x3& lhs, const long4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a long4x3 matrix and a long value.</summary>

	inline static bool4x3 operator != (const long4x3& lhs, long rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long4x3 matrix.</summary>

	inline static bool4x3 operator != (long lhs, const long4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region long4x4
	struct long4x4
	{
		long4 c0, c1, c2, c3;
		long4x4() : c0(), c1(), c2(), c3() {}
		long4x4(long m00, long m01, long m02, long m03,
			long m10, long m11, long m12, long m13,
			long m20, long m21, long m22, long m23,
			long m30, long m31, long m32, long m33)
		{
			c0 = long4(m00, m10, m20, m30);
			c1 = long4(m01, m11, m21, m31);
			c2 = long4(m02, m12, m22, m32);
			c3 = long4(m03, m13, m23, m33);
		}
		long4x4(long4 c0, long4 c1, long4 c2, long4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		long4x4(long v) : c0(v), c1(v), c2(v), c3(v) {}

		long4x4(long3x3 rotation, long3 translation)
		{
			c0 = long4(rotation.c0, 0.0f);
			c1 = long4(rotation.c1, 0.0f);
			c2 = long4(rotation.c2, 0.0f);
			c3 = long4(translation, 1.0f);
		}


	};


	/// <summary>Returns the result of a componentwise multiplication operation on two long4x4 matrices.</summary>

	inline static long4x4 operator * (const long4x4& lhs, const long4x4& rhs) { return long4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long4x4 matrix and a long value.</summary>

	inline static long4x4 operator * (const long4x4& lhs, long rhs) { return long4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a long value and a long4x4 matrix.</summary>

	inline static long4x4 operator * (long lhs, const long4x4& rhs) { return long4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two long4x4 matrices.</summary>

	inline static long4x4 operator + (const long4x4& lhs, const long4x4& rhs) { return long4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a long4x4 matrix and a long value.</summary>

	inline static long4x4 operator + (const long4x4& lhs, long rhs) { return long4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a long value and a long4x4 matrix.</summary>

	inline static long4x4 operator + (long lhs, const long4x4& rhs) { return long4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two long4x4 matrices.</summary>

	inline static long4x4 operator - (const long4x4& lhs, const long4x4& rhs) { return long4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long4x4 matrix and a long value.</summary>

	inline static long4x4 operator - (const long4x4& lhs, long rhs) { return long4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a long value and a long4x4 matrix.</summary>

	inline static long4x4 operator - (long lhs, const long4x4& rhs) { return long4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two long4x4 matrices.</summary>

	inline static long4x4 operator / (const long4x4& lhs, const long4x4& rhs) { return long4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a long4x4 matrix and a long value.</summary>

	inline static long4x4 operator / (const long4x4& lhs, long rhs) { return long4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a long value and a long4x4 matrix.</summary>

	inline static long4x4 operator / (long lhs, const long4x4& rhs) { return long4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a long4x4 matrix.</summary>

	inline static long4x4 operator ++ (long4x4 val) { return long4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a long4x4 matrix.</summary>

	inline static long4x4 operator -- (long4x4 val) { return long4x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two long4x4 matrices.</summary>

	inline static bool4x4 operator < (const long4x4& lhs, const long4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a long4x4 matrix and a long value.</summary>

	inline static bool4x4 operator < (const long4x4& lhs, long rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a long value and a long4x4 matrix.</summary>

	inline static bool4x4 operator < (long lhs, const long4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two long4x4 matrices.</summary>

	inline static bool4x4 operator <= (const long4x4& lhs, const long4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long4x4 matrix and a long value.</summary>

	inline static bool4x4 operator <= (const long4x4& lhs, long rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a long value and a long4x4 matrix.</summary>

	inline static bool4x4 operator <= (long lhs, const long4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two long4x4 matrices.</summary>

	inline static bool4x4 operator > (const long4x4& lhs, const long4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a long4x4 matrix and a long value.</summary>

	inline static bool4x4 operator > (const long4x4& lhs, long rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a long value and a long4x4 matrix.</summary>

	inline static bool4x4 operator > (long lhs, const long4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two long4x4 matrices.</summary>

	inline static bool4x4 operator >= (const long4x4& lhs, const long4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long4x4 matrix and a long value.</summary>

	inline static bool4x4 operator >= (const long4x4& lhs, long rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a long value and a long4x4 matrix.</summary>

	inline static bool4x4 operator >= (long lhs, const long4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a long4x4 matrix.</summary>

	inline static long4x4 operator - (long4x4 val) { return long4x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a long4x4 matrix.</summary>

	inline static long4x4 operator + (long4x4 val) { return long4x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two long4x4 matrices.</summary>

	inline static bool4x4 operator == (const long4x4& lhs, const long4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a long4x4 matrix and a long value.</summary>

	inline static bool4x4 operator == (const long4x4& lhs, long rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a long value and a long4x4 matrix.</summary>

	inline static bool4x4 operator == (long lhs, const long4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two long4x4 matrices.</summary>

	inline static bool4x4 operator != (const long4x4& lhs, const long4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a long4x4 matrix and a long value.</summary>

	inline static bool4x4 operator != (const long4x4& lhs, long rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a long value and a long4x4 matrix.</summary>

	inline static bool4x4 operator != (long lhs, const long4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic


	/// <summary>Returns the Tangent of a long value.</summary>
	inline static long Tan(long x) { return (long)tan(x); }

	/// <summary>Returns the componentwise Tangent of a long2 vector.</summary>
	inline static long2 Tan(long2 x) { return long2(Tan(x.x), Tan(x.y)); }

	/// <summary>Returns the componentwise Tangent of a long3 vector.</summary>
	inline static long3 Tan(long3 x) { return long3(Tan(x.x), Tan(x.y), Tan(x.z)); }

	/// <summary>Returns the componentwise Tangent of a long4 vector.</summary>
	inline static long4 Tan(long4 x) { return long4(Tan(x.x), Tan(x.y), Tan(x.z), Tan(x.w)); }


	/// <summary>Returns the hyperbolic Tangent of a long value.</summary>
	inline static long Tanh(long x) { return (long)tanh(x); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a long2 vector.</summary>
	inline static long2 Tanh(long2 x) { return long2(Tanh(x.x), Tanh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a long3 vector.</summary>
	inline static long3 Tanh(long3 x) { return long3(Tanh(x.x), Tanh(x.y), Tanh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a long4 vector.</summary>
	inline static long4 Tanh(long4 x) { return long4(Tanh(x.x), Tanh(x.y), Tanh(x.z), Tanh(x.w)); }


	/// <summary>Returns the arcTangent of a long value.</summary>
	inline static long Atan(long x) { return (long)atan(x); }

	/// <summary>Returns the componentwise arcTangent of a long2 vector.</summary>
	inline static long2 Atan(long2 x) { return long2(Atan(x.x), Atan(x.y)); }

	/// <summary>Returns the componentwise arcTangent of a long3 vector.</summary>
	inline static long3 Atan(long3 x) { return long3(Atan(x.x), Atan(x.y), Atan(x.z)); }

	/// <summary>Returns the componentwise arcTangent of a long4 vector.</summary>
	inline static long4 Atan(long4 x) { return long4(Atan(x.x), Atan(x.y), Atan(x.z), Atan(x.w)); }


	/// <summary>Returns the 2-argument arcTangent of a pair of long values.</summary>
	inline static long Atan2(long y, long x) { return (long)atan2(y, x); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of longs2 vectors.</summary>
	inline static long2 Atan2(long2 y, long2 x) { return long2(Atan2(y.x, x.x), Atan2(y.y, x.y)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of longs3 vectors.</summary>
	inline static long3 Atan2(long3 y, long3 x) { return long3(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of longs4 vectors.</summary>
	inline static long4 Atan2(long4 y, long4 x) { return long4(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z), Atan2(y.w, x.w)); }


	/// <summary>Returns the CoSine of a long value.</summary>
	inline static long Cos(long x) { return (long)cos(x); }

	/// <summary>Returns the componentwise CoSine of a long2 vector.</summary>
	inline static long2 Cos(long2 x) { return long2(Cos(x.x), Cos(x.y)); }

	/// <summary>Returns the componentwise CoSine of a long3 vector.</summary>
	inline static long3 Cos(long3 x) { return long3(Cos(x.x), Cos(x.y), Cos(x.z)); }

	/// <summary>Returns the componentwise CoSine of a long4 vector.</summary>
	inline static long4 Cos(long4 x) { return long4(Cos(x.x), Cos(x.y), Cos(x.z), Cos(x.w)); }


	/// <summary>Returns the hyperbolic CoSine of a long value.</summary>
	inline static long Cosh(long x) { return (long)cosh(x); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a long2 vector.</summary>
	inline static long2 Cosh(long2 x) { return long2(Cosh(x.x), Cosh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a long3 vector.</summary>
	inline static long3 Cosh(long3 x) { return long3(Cosh(x.x), Cosh(x.y), Cosh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a long4 vector.</summary>
	inline static long4 Cosh(long4 x) { return long4(Cosh(x.x), Cosh(x.y), Cosh(x.z), Cosh(x.w)); }

	/// <summary>Returns the arcCoSine of a long value.</summary>
	inline static long Acos(long x) { return (long)acos((long)x); }

	/// <summary>Returns the componentwise arcCoSine of a long2 vector.</summary>
	inline static long2 Acos(long2 x) { return long2(Acos(x.x), Acos(x.y)); }

	/// <summary>Returns the componentwise arcCoSine of a long3 vector.</summary>
	inline static long3 Acos(long3 x) { return long3(Acos(x.x), Acos(x.y), Acos(x.z)); }

	/// <summary>Returns the componentwise arcCoSine of a long4 vector.</summary>
	inline static long4 Acos(long4 x) { return long4(Acos(x.x), Acos(x.y), Acos(x.z), Acos(x.w)); }


	/// <summary>Returns the Sine of a long value.</summary>
	inline static long Sin(long x) { return (long)sin((long)x); }

	/// <summary>Returns the componentwise Sine of a long2 vector.</summary>
	inline static long2 Sin(long2 x) { return long2(Sin(x.x), Sin(x.y)); }

	/// <summary>Returns the componentwise Sine of a long3 vector.</summary>
	inline static long3 Sin(long3 x) { return long3(Sin(x.x), Sin(x.y), Sin(x.z)); }

	/// <summary>Returns the componentwise Sine of a long4 vector.</summary>
	inline static long4 Sin(long4 x) { return long4(Sin(x.x), Sin(x.y), Sin(x.z), Sin(x.w)); }



	/// <summary>Returns the hyperbolic Sine of a long value.</summary>
	inline static long Sinh(long x) { return (long)sinh((long)x); }

	/// <summary>Returns the componentwise hyperbolic Sine of a long2 vector.</summary>
	inline static long2 Sinh(long2 x) { return long2(Sinh(x.x), Sinh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a long3 vector.</summary>
	inline static long3 Sinh(long3 x) { return long3(Sinh(x.x), Sinh(x.y), Sinh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a long4 vector.</summary>
	inline static long4 Sinh(long4 x) { return long4(Sinh(x.x), Sinh(x.y), Sinh(x.z), Sinh(x.w)); }


	/// <summary>Returns the arcSine of a long value.</summary>
	inline static long Asin(long x) { return (long)asin((long)x); }

	/// <summary>Returns the componentwise arcSine of a long2 vector.</summary>
	inline static long2 Asin(long2 x) { return long2(Asin(x.x), Asin(x.y)); }

	/// <summary>Returns the componentwise arcSine of a long3 vector.</summary>
	inline static long3 Asin(long3 x) { return long3(Asin(x.x), Asin(x.y), Asin(x.z)); }

	/// <summary>Returns the componentwise arcSine of a long4 vector.</summary>
	inline static long4 Asin(long4 x) { return long4(Asin(x.x), Asin(x.y), Asin(x.z), Asin(x.w)); }


	/// <summary>Returns the Dot product of two long values. Equivalent to multiplication.</summary>
	inline static long Dot(long x, long y) { return x * y; }

	/// <summary>Returns the Dot product of two long2 vectors.</summary>
	inline static long Dot(long2 x, long2 y) { return x.x * y.x + x.y * y.y; }

	/// <summary>Returns the Dot product of two long3 vectors.</summary>
	inline static long Dot(long3 x, long3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }

	/// <summary>Returns the Dot product of two long4 vectors.</summary>
	inline static long Dot(long4 x, long4 y) { return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w; }

	/// <summary>Returns the square root of a long value.</summary>
	inline static long Sqrt(long x) { return sqrt((double)x); }

	/// <summary>Returns the componentwise square root of a long2 vector.</summary>
	inline static long2 Sqrt(long2 x) { return long2(Sqrt(x.x), Sqrt(x.y)); }

	/// <summary>Returns the componentwise square root of a long3 vector.</summary>
	inline static long3 Sqrt(long3 x) { return long3(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z)); }

	/// <summary>Returns the componentwise square root of a long4 vector.</summary>
	inline static long4 Sqrt(long4 x) { return long4(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z), Sqrt(x.w)); }


	/// <summary>Returns the reciprocal square root of a long value.</summary>
	inline static long Rsqrt(long x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a long2 vector.</summary>
	inline static long2 Rsqrt(long2 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a long3 vector.</summary>
	inline static long3 Rsqrt(long3 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a long4 vector</summary>
	inline static long4 Rsqrt(long4 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns a Normalized version of the long2 vector x by scaling it by 1 / Length(x).</summary>
	inline static long2 Normalize(long2 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the long3 vector x by scaling it by 1 / Length(x).</summary>
	inline static long3 Normalize(long3 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the long4 vector x by scaling it by 1 / Length(x).</summary>
	inline static long4 Normalize(long4 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns the Length of a long2 vector.</summary>
	inline static long Length(long2 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a long3 vector.</summary>
	inline static long Length(long3 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a long4 vector.</summary>
	inline static long Length(long4 x) { return sqrt(Dot(x, x)); }




	/// <summary>Returns the squared Length of a long value. Equivalent to squaring the value.</summary>
	inline static long Lengthsq(long x) { return x * x; }

	/// <summary>Returns the squared Length of a long2 vector.</summary>
	inline static long Lengthsq(long2 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a long3 vector.</summary>
	inline static long Lengthsq(long3 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a long4 vector.</summary>
	inline static long Lengthsq(long4 x) { return Dot(x, x); }


	/// <summary>Returns the Distance between two long2 vectors.</summary>
	inline static long Distance(long2 x, long2 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two long3 vectors.</summary>
	inline static long Distance(long3 x, long3 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two long4 vectors.</summary>
	inline static long Distance(long4 x, long4 y) { return Length(y - x); }



	/// <summary>Returns the Distance between two long values.</summary>
	inline static long Distancesq(long x, long y) { return (y - x) * (y - x); }

	/// <summary>Returns the Distance between two long2 vectors.</summary>
	inline static long Distancesq(long2 x, long2 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two long3 vectors.</summary>
	inline static long Distancesq(long3 x, long3 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two long4 vectors.</summary>
	inline static long Distancesq(long4 x, long4 y) { return Lengthsq(y - x); }



	/// <summary>Returns the Cross product of two long3 vectors.</summary>
	inline static long3 Cross(long3 x, long3 y) {
		long3 retVal = x * long3(y.y, y.z, y.x) - long3(x.y, x.z, x.x) * y;
		return long3(retVal.y, retVal.z, retVal.x);
	}

	/// <summary>Returns the Sine and CoSine of the input long value x through the out parameters s and c.</summary>
	inline static void SinCos(long x, long* s, long* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input long2 vector x through the out parameters s and c.</summary>
	inline static void SinCos(long2 x, long2* s, long2* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input long3 vector x through the out parameters s and c.</summary>
	inline static void SinCos(long3 x, long3* s, long3* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input long4 vector x through the out parameters s and c.</summary>
	inline static void SinCos(long4 x, long4* s, long4* c) { *s = Sin(x); *c = Cos(x); }


	/// <summary>Returns the Minimum of two long values.</summary>
	inline static long Min(long x, long y) { return x < y ? x : y; }

	/// <summary>Returns the componentwise Minimum of two long2 vectors.</summary>
	inline static long2 Min(long2 x, long2 y) { return long2(Min(x.x, y.x), Min(x.y, y.y)); }

	/// <summary>Returns the componentwise Minimum of two long3 vectors.</summary>
	inline static long3 Min(long3 x, long3 y) { return long3(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z)); }

	/// <summary>Returns the componentwise Minimum of two long4 vectors.</summary>
	inline static long4 Min(long4 x, long4 y) { return long4(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z), Min(x.w, y.w)); }


	/// <summary>Returns the Maximum of two long values.</summary>
	inline static long Max(long x, long y) { return x > y ? x : y; }

	/// <summary>Returns the componentwise Maximum of two long2 vectors.</summary>
	inline static long2 Max(long2 x, long2 y) { return long2(Max(x.x, y.x), Max(x.y, y.y)); }

	/// <summary>Returns the componentwise Maximum of two long3 vectors.</summary>
	inline static long3 Max(long3 x, long3 y) { return long3(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z)); }

	/// <summary>Returns the componentwise Maximum of two long4 vectors.</summary>
	inline static long4 Max(long4 x, long4 y) { return long4(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z), Max(x.w, y.w)); }

	inline static long Lerp(long x, long y, long s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static long2 Lerp(long2 x, long2 y, long s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static long3 Lerp(long3 x, long3 y, long s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static long4 Lerp(long4 x, long4 y, long s) { return x + s * (y - x); }


	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static long2 Lerp(long2 x, long2 y, long2 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static long3 Lerp(long3 x, long3 y, long3 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static long4 Lerp(long4 x, long4 y, long4 s) { return x + s * (y - x); }

	/// <summary>Returns the result of normalizing a longing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static long Unlerp(long a, long b, long x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a longing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static long2 Unlerp(long2 a, long2 b, long2 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a longing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static long3 Unlerp(long3 a, long3 b, long3 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a longing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static long4 Unlerp(long4 a, long4 b, long4 x) { return (x - a) / (b - a); }

	/// <summary>Returns the result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static long Remap(long a, long b, long c, long d, long x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static long2 Remap(long2 a, long2 b, long2 c, long2 d, long2 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static long3 Remap(long3 a, long3 b, long3 c, long3 d, long3 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static long4 Remap(long4 a, long4 b, long4 c, long4 d, long4 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the result of Clamping the value x into the interval [a, b], where x, a and b are long values.</summary>
	inline static long Clamp(long x, long a, long b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are long2 vectors.</summary>
	inline static long2 Clamp(long2 x, long2 a, long2 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are long3 vectors.</summary>
	inline static long3 Clamp(long3 x, long3 a, long3 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are long4 vectors.</summary>
	inline static long4 Clamp(long4 x, long4 a, long4 b) { return Max(a, Min(b, x)); }

	inline static long select_shuffle_component(long4 a, long4 b, char component)
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

	inline static long4 shuffle(long4 a, long4 b, char x, char y, char z, char w)
	{
		return long4(
			select_shuffle_component(a, b, x),
			select_shuffle_component(a, b, y),
			select_shuffle_component(a, b, z),
			select_shuffle_component(a, b, w));
	}

	inline static long4 movelh(long4 a, long4 b)
	{
		return shuffle(a, b, 0, 1, 4, 5);
	}
	inline static long4 movehl(long4 a, long4 b)
	{
		return shuffle(b, a, 2, 3, 6, 7);
	}
	// SSE shuffles
	inline static long4 unpacklo(long4 a, long4 b)
	{
		return shuffle(a, b, 0, 4, 1, 5);
	}
	inline static long4 unpackhi(long4 a, long4 b)
	{
		return shuffle(a, b, 2, 6, 3, 7);
	}
#pragma endregion
#pragma region Component
	/// <summary>Returns the Maximum component of a long2 vector.</summary>
	inline static long CMax(long2 x) { return Max(x.x, x.y); }

	/// <summary>Returns the Maximum component of a long3 vector.</summary>
	inline static long CMax(long3 x) { return Max(Max(x.x, x.y), x.z); }

	/// <summary>Returns the Maximum component of a long4 vector.</summary>
	inline static long CMax(long4 x) { return Max(Max(x.x, x.y), Max(x.z, x.w)); }

	/// <summary>Returns the horizontal sum of components of a long2 vector.</summary>
	inline static long Csum(long2 x) { return x.x + x.y; }

	/// <summary>Returns the horizontal sum of components of a long3 vector.</summary>
	inline static long Csum(long3 x) { return x.x + x.y + x.z; }

	/// <summary>Returns the horizontal sum of components of a long4 vector.</summary>
	inline static long Csum(long4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion

#pragma region Transpose
	/// <summary>Return the long2x2 Transpose of a long2x2 matrix.</summary>
	inline long2x2 Transpose(long2x2 v)
	{
		return long2x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y);
	}
	/// <summary>Return the long3x2 Transpose of a long2x3 matrix.</summary>
	inline long3x2 Transpose(long2x3 v)
	{
		return long3x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y);
	}
	/// <summary>Return the long4x2 Transpose of a long2x4 matrix.</summary>
	inline long4x2 Transpose(long2x4 v)
	{
		return long4x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y,
			v.c3.x, v.c3.y);
	}
	/// <summary>Return the long2x3 Transpose of a long3x2 matrix.</summary>
	inline long2x3 Transpose(long3x2 v)
	{
		return long2x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z);
	}
	/// <summary>Return the long3x3 Transpose of a long3x3 matrix.</summary>
	inline long3x3 Transpose(long3x3 v)
	{
		return long3x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z);
	}
	/// <summary>Return the long4x3 Transpose of a long3x4 matrix.</summary>
	inline static long4x3 Transpose(long3x4 v)
	{
		return long4x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z,
			v.c3.x, v.c3.y, v.c3.z);
	}
	/// <summary>Return the long2x4 Transpose of a long4x2 matrix.</summary>
	inline static long2x4 Transpose(long4x2 v)
	{
		return long2x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w);
	}
	/// <summary>Return the long3x4 Transpose of a long4x3 matrix.</summary>
	inline static long3x4 Transpose(long4x3 v)
	{
		return long3x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w);
	}
	/// <summary>Return the long4x4 Transpose of a long4x4 matrix.</summary>
	inline static long4x4 Transpose(long4x4 v)
	{
		return long4x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w,
			v.c3.x, v.c3.y, v.c3.z, v.c3.w);
	}

#pragma endregion
#pragma region Inverse
	/// <summary>Returns the long2x2 full Inverse of a long2x2 matrix.</summary>
	inline long2x2 Inverse(long2x2 m)
	{
		long a = m.c0.x;
		long b = m.c1.x;
		long c = m.c0.y;
		long d = m.c1.y;

		long det = a * d - b * c;

		return long2x2(d, -b, -c, a) * (1.0f / det);
	}
	/// <summary>Returns the long3x3 full Inverse of a long3x3 matrix.</summary>
	inline long3x3 Inverse(long3x3 m)
	{
		long3 c0 = m.c0;
		long3 c1 = m.c1;
		long3 c2 = m.c2;

		long3 t0 = long3(c1.x, c2.x, c0.x);
		long3 t1 = long3(c1.y, c2.y, c0.y);
		long3 t2 = long3(c1.z, c2.z, c0.z);

		long3 m0 = t1 * long3(t2.y, t2.z, t2.x) - long3(t1.y, t1.z, t1.x) * t2;
		long3 m1 = long3(t0.y, t0.z, t0.x) * t2 - t0 * long3(t2.y, t2.z, t2.x);
		long3 m2 = t0 * long3(t1.y, t1.z, t1.x) - t0 * long3(t2.y, t2.z, t2.x) * t1;

		long rcpDet = 1.0f / Csum(long3(t0.z, t0.x, t0.y) * m0);
		return long3x3(m0, m1, m2) * rcpDet;
	}
	// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
	inline static long3x4 fastInverse(long3x4 m)
	{
		long3 c0 = m.c0;
		long3 c1 = m.c1;
		long3 c2 = m.c2;
		long3 pos = m.c3;

		long3 r0 = long3(c0.x, c1.x, c2.x);
		long3 r1 = long3(c0.y, c1.y, c2.y);
		long3 r2 = long3(c0.z, c1.z, c2.z);

		pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);

		return long3x4(r0, r1, r2, pos);
	}
	/// <summary>Returns the long4x4 full Inverse of a long4x4 matrix.</summary>
	inline static long4x4 Inverse(long4x4 m)
	{
		long4 c0 = m.c0;
		long4 c1 = m.c1;
		long4 c2 = m.c2;
		long4 c3 = m.c3;

		long4 r0y_r1y_r0x_r1x = movelh(c1, c0);
		long4 r0z_r1z_r0w_r1w = movelh(c2, c3);
		long4 r2y_r3y_r2x_r3x = movehl(c0, c1);
		long4 r2z_r3z_r2w_r3w = movehl(c3, c2);

		long4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
		long4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
		long4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
		long4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

		long4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
		long4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
		long4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
		long4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
		long4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

		// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
		long4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
		long4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
		long4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

		// Expand inner terms back to 4 components. zw signs still need to be flipped
		long4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
		long4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

		long4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
		long4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

		// Calculate Minors
		long4 Minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

		long4 denom = r0_xyzw * Minors0;

		// Horizontal sum of denoMinator. Free sign flip of z and w compensates for misSing flip in inner terms.
		denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
		denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

		long4 rcp_denom_ppnn = long4(1.0f) / denom;
		long4x4 res;
		res.c0 = Minors0 * rcp_denom_ppnn;

		long4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
		long4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

		long4 Minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
		res.c1 = Minors1 * rcp_denom_ppnn;

		long4 Minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
		res.c2 = Minors2 * rcp_denom_ppnn;

		long4 Minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
		res.c3 = Minors3 * rcp_denom_ppnn;
		return res;
	}
	// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
	inline static long4x4 fastInverse(long4x4 m)
	{
		long4 c0 = m.c0;
		long4 c1 = m.c1;
		long4 c2 = m.c2;
		long4 pos = m.c3;

		long4 zero = long4(0);

		long4 t0 = unpacklo(c0, c2);
		long4 t1 = unpacklo(c1, zero);
		long4 t2 = unpackhi(c0, c2);
		long4 t3 = unpackhi(c1, zero);

		long4 r0 = unpacklo(t0, t1);
		long4 r1 = unpackhi(t0, t1);
		long4 r2 = unpacklo(t2, t3);

		pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);
		pos.w = 1.0f;

		return long4x4(r0, r1, r2, pos);
	}
#pragma endregion
#pragma region Determinant
	/// <summary>Returns the Determinant of a long2x2 matrix.</summary>
	inline long Determinant(long2x2 m)
	{
		long a = m.c0.x;
		long b = m.c1.x;
		long c = m.c0.y;
		long d = m.c1.y;

		return a * d - b * c;
	}
	/// <summary>Returns the Determinant of a long3x3 matrix.</summary>
	inline long Determinant(long3x3 m)
	{
		long3 c0 = m.c0;
		long3 c1 = m.c1;
		long3 c2 = m.c2;

		long m00 = c1.y * c2.z - c1.z * c2.y;
		long m01 = c0.y * c2.z - c0.z * c2.y;
		long m02 = c0.y * c1.z - c0.z * c1.y;

		return c0.x * m00 - c1.x * m01 + c2.x * m02;
	}
	/// <summary>Returns the Determinant of a long4x4 matrix.</summary>
	inline static long Determinant(long4x4 m)
	{
		long4 c0 = m.c0;
		long4 c1 = m.c1;
		long4 c2 = m.c2;
		long4 c3 = m.c3;

		long m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
		long m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
		long m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
		long m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

		return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
	}

#pragma endregion
}