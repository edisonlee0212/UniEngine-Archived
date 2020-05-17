#pragma once
#include "bool.h"
#include <math.h>
namespace UniEngine {
#pragma region int2
	struct int2 {
		int x, y;
		int2() : x(0), y(0) {}
		int2(int x, int y) : x(x), y(y) {}
		int2(int v) : x(v), y(v) {}
	};
	/// <summary>Returns the result of a componentwise multiplication operation on two int2 vectors.</summary>

	inline static int2 operator * (const int2& lhs, const int2& rhs) { return int2(lhs.x * rhs.x, lhs.y * rhs.y); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int2 vector and a int value.</summary>

	inline static int2 operator * (const int2& lhs, int rhs) { return int2(lhs.x * rhs, lhs.y * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int2 vector.</summary>

	inline static int2 operator * (int lhs, const int2& rhs) { return int2(lhs * rhs.x, lhs * rhs.y); }


	/// <summary>Returns the result of a componentwise addition operation on two int2 vectors.</summary>

	inline static int2 operator + (const int2& lhs, const int2& rhs) { return int2(lhs.x + rhs.x, lhs.y + rhs.y); }

	/// <summary>Returns the result of a componentwise addition operation on a int2 vector and a int value.</summary>

	inline static int2 operator + (const int2& lhs, int rhs) { return int2(lhs.x + rhs, lhs.y + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int2 vector.</summary>

	inline static int2 operator + (int lhs, const int2& rhs) { return int2(lhs + rhs.x, lhs + rhs.y); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int2 vectors.</summary>

	inline static int2 operator - (const int2& lhs, const int2& rhs) { return int2(lhs.x - rhs.x, lhs.y - rhs.y); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int2 vector and a int value.</summary>

	inline static int2 operator - (const int2& lhs, int rhs) { return int2(lhs.x - rhs, lhs.y - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int2 vector.</summary>

	inline static int2 operator - (int lhs, const int2& rhs) { return int2(lhs - rhs.x, lhs - rhs.y); }


	/// <summary>Returns the result of a componentwise division operation on two int2 vectors.</summary>

	inline static int2 operator / (const int2& lhs, const int2& rhs) { return int2(lhs.x / rhs.x, lhs.y / rhs.y); }

	/// <summary>Returns the result of a componentwise division operation on a int2 vector and a int value.</summary>

	inline static int2 operator / (const int2& lhs, int rhs) { return int2(lhs.x / rhs, lhs.y / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int2 vector.</summary>

	inline static int2 operator / (int lhs, const int2& rhs) { return int2(lhs / rhs.x, lhs / rhs.y); }

	/// <summary>Returns the result of a componentwise increment operation on a int2 vector.</summary>

	inline static int2 operator ++ (int2 val) { return int2(++val.x, ++val.y); }


	/// <summary>Returns the result of a componentwise decrement operation on a int2 vector.</summary>

	inline static int2 operator -- (int2 val) { return int2(--val.x, --val.y); }


	/// <summary>Returns the result of a componentwise less than operation on two int2 vectors.</summary>

	inline static bool2 operator < (const int2& lhs, const int2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

	/// <summary>Returns the result of a componentwise less than operation on a int2 vector and a int value.</summary>

	inline static bool2 operator < (const int2& lhs, int rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int2 vector.</summary>

	inline static bool2 operator < (int lhs, const int2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int2 vectors.</summary>

	inline static bool2 operator <= (const int2& lhs, const int2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int2 vector and a int value.</summary>

	inline static bool2 operator <= (const int2& lhs, int rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int2 vector.</summary>

	inline static bool2 operator <= (int lhs, const int2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


	/// <summary>Returns the result of a componentwise greater than operation on two int2 vectors.</summary>

	inline static bool2 operator > (const int2& lhs, const int2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

	/// <summary>Returns the result of a componentwise greater than operation on a int2 vector and a int value.</summary>

	inline static bool2 operator > (const int2& lhs, int rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int2 vector.</summary>

	inline static bool2 operator > (int lhs, const int2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int2 vectors.</summary>

	inline static bool2 operator >= (const int2& lhs, const int2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int2 vector and a int value.</summary>

	inline static bool2 operator >= (const int2& lhs, int rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int2 vector.</summary>

	inline static bool2 operator >= (int lhs, const int2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int2 vector.</summary>

	inline static int2 operator - (int2 val) { return int2(-val.x, -val.y); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int2 vector.</summary>

	inline static int2 operator + (int2 val) { return int2(+val.x, +val.y); }


	/// <summary>Returns the result of a componentwise equality operation on two int2 vectors.</summary>

	inline static bool2 operator == (const int2& lhs, const int2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on a int2 vector and a int value.</summary>

	inline static bool2 operator == (const int2& lhs, int rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int2 vector.</summary>

	inline static bool2 operator == (int lhs, const int2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


	/// <summary>Returns the result of a componentwise not equal operation on two int2 vectors.</summary>

	inline static bool2 operator != (const int2& lhs, const int2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

	/// <summary>Returns the result of a componentwise not equal operation on a int2 vector and a int value.</summary>

	inline static bool2 operator != (const int2& lhs, int rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int2 vector.</summary>

	inline static bool2 operator != (int lhs, const int2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region int2x2
	struct int2x2
	{
		int2 c0, c1;
		int2x2() : c0(), c1() {}
		int2x2(int m00, int m01,
			int m10, int m11) :c0(int2(m00, m10)), c1(int2(m01, m11)) {}
		int2x2(int2 c0, int2 c1) : c0(c0), c1(c1) {}
		int2x2(int v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int2x2 matrices.</summary>

	inline static int2x2 operator * (const int2x2& lhs, const int2x2& rhs) { return int2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int2x2 matrix and a int value.</summary>

	inline static int2x2 operator * (const int2x2& lhs, int rhs) { return int2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int2x2 matrix.</summary>

	inline static int2x2 operator * (int lhs, const int2x2& rhs) { return int2x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two int2x2 matrices.</summary>

	inline static int2x2 operator + (const int2x2& lhs, const int2x2& rhs) { return int2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a int2x2 matrix and a int value.</summary>

	inline static int2x2 operator + (const int2x2& lhs, int rhs) { return int2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int2x2 matrix.</summary>

	inline static int2x2 operator + (int lhs, const int2x2& rhs) { return int2x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int2x2 matrices.</summary>

	inline static int2x2 operator - (const int2x2& lhs, const int2x2& rhs) { return int2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int2x2 matrix and a int value.</summary>

	inline static int2x2 operator - (const int2x2& lhs, int rhs) { return int2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int2x2 matrix.</summary>

	inline static int2x2 operator - (int lhs, const int2x2& rhs) { return int2x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two int2x2 matrices.</summary>

	inline static int2x2 operator / (const int2x2& lhs, const int2x2& rhs) { return int2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a int2x2 matrix and a int value.</summary>

	inline static int2x2 operator / (const int2x2& lhs, int rhs) { return int2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int2x2 matrix.</summary>

	inline static int2x2 operator / (int lhs, const int2x2& rhs) { return int2x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a int2x2 matrix.</summary>

	inline static int2x2 operator ++ (int2x2 val) { return int2x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a int2x2 matrix.</summary>

	inline static int2x2 operator -- (int2x2 val) { return int2x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two int2x2 matrices.</summary>

	inline static bool2x2 operator < (const int2x2& lhs, const int2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a int2x2 matrix and a int value.</summary>

	inline static bool2x2 operator < (const int2x2& lhs, int rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int2x2 matrix.</summary>

	inline static bool2x2 operator < (int lhs, const int2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int2x2 matrices.</summary>

	inline static bool2x2 operator <= (const int2x2& lhs, const int2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int2x2 matrix and a int value.</summary>

	inline static bool2x2 operator <= (const int2x2& lhs, int rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int2x2 matrix.</summary>

	inline static bool2x2 operator <= (int lhs, const int2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two int2x2 matrices.</summary>

	inline static bool2x2 operator > (const int2x2& lhs, const int2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a int2x2 matrix and a int value.</summary>

	inline static bool2x2 operator > (const int2x2& lhs, int rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int2x2 matrix.</summary>

	inline static bool2x2 operator > (int lhs, const int2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int2x2 matrices.</summary>

	inline static bool2x2 operator >= (const int2x2& lhs, const int2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int2x2 matrix and a int value.</summary>

	inline static bool2x2 operator >= (const int2x2& lhs, int rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int2x2 matrix.</summary>

	inline static bool2x2 operator >= (int lhs, const int2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int2x2 matrix.</summary>

	inline static int2x2 operator - (int2x2 val) { return int2x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int2x2 matrix.</summary>

	inline static int2x2 operator + (int2x2 val) { return int2x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two int2x2 matrices.</summary>

	inline static bool2x2 operator == (const int2x2& lhs, const int2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a int2x2 matrix and a int value.</summary>

	inline static bool2x2 operator == (const int2x2& lhs, int rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int2x2 matrix.</summary>

	inline static bool2x2 operator == (int lhs, const int2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two int2x2 matrices.</summary>

	inline static bool2x2 operator != (const int2x2& lhs, const int2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a int2x2 matrix and a int value.</summary>

	inline static bool2x2 operator != (const int2x2& lhs, int rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int2x2 matrix.</summary>

	inline static bool2x2 operator != (int lhs, const int2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region int2x3
	struct int2x3
	{
		int2 c0, c1, c2;
		int2x3() : c0(), c1(), c2() {}
		int2x3(int m00, int m01, int m02,
			int m10, int m11, int m12)
		{
			c0 = int2(m00, m10);
			c1 = int2(m01, m11);
			c2 = int2(m02, m12);
		}
		int2x3(int2 c0, int2 c1, int2 c2) : c0(c0), c1(c1), c2(c2) {}
		int2x3(int v) : c0(v), c1(v), c2(v) {}
	};

	/// <summary>Returns the result of a componentwise multiplication operation on two int2x3 matrices.</summary>

	inline static int2x3 operator * (const int2x3& lhs, const int2x3& rhs) { return int2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int2x3 matrix and a int value.</summary>

	inline static int2x3 operator * (const int2x3& lhs, int rhs) { return int2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int2x3 matrix.</summary>

	inline static int2x3 operator * (int lhs, const int2x3& rhs) { return int2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two int2x3 matrices.</summary>

	inline static int2x3 operator + (const int2x3& lhs, const int2x3& rhs) { return int2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a int2x3 matrix and a int value.</summary>

	inline static int2x3 operator + (const int2x3& lhs, int rhs) { return int2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int2x3 matrix.</summary>

	inline static int2x3 operator + (int lhs, const int2x3& rhs) { return int2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int2x3 matrices.</summary>

	inline static int2x3 operator - (const int2x3& lhs, const int2x3& rhs) { return int2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int2x3 matrix and a int value.</summary>

	inline static int2x3 operator - (const int2x3& lhs, int rhs) { return int2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int2x3 matrix.</summary>

	inline static int2x3 operator - (int lhs, const int2x3& rhs) { return int2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two int2x3 matrices.</summary>

	inline static int2x3 operator / (const int2x3& lhs, const int2x3& rhs) { return int2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a int2x3 matrix and a int value.</summary>

	inline static int2x3 operator / (const int2x3& lhs, int rhs) { return int2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int2x3 matrix.</summary>

	inline static int2x3 operator / (int lhs, const int2x3& rhs) { return int2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


	/// <summary>Returns the result of a componentwise increment operation on a int2x3 matrix.</summary>

	inline static int2x3 operator ++ (int2x3 val) { return int2x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a int2x3 matrix.</summary>

	inline static int2x3 operator -- (int2x3 val) { return int2x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two int2x3 matrices.</summary>

	inline static bool2x3 operator < (const int2x3& lhs, const int2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a int2x3 matrix and a int value.</summary>

	inline static bool2x3 operator < (const int2x3& lhs, int rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int2x3 matrix.</summary>

	inline static bool2x3 operator < (int lhs, const int2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int2x3 matrices.</summary>

	inline static bool2x3 operator <= (const int2x3& lhs, const int2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int2x3 matrix and a int value.</summary>

	inline static bool2x3 operator <= (const int2x3& lhs, int rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int2x3 matrix.</summary>

	inline static bool2x3 operator <= (int lhs, const int2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two int2x3 matrices.</summary>

	inline static bool2x3 operator > (const int2x3& lhs, const int2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a int2x3 matrix and a int value.</summary>

	inline static bool2x3 operator > (const int2x3& lhs, int rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int2x3 matrix.</summary>

	inline static bool2x3 operator > (int lhs, const int2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int2x3 matrices.</summary>

	inline static bool2x3 operator >= (const int2x3& lhs, const int2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int2x3 matrix and a int value.</summary>

	inline static bool2x3 operator >= (const int2x3& lhs, int rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int2x3 matrix.</summary>

	inline static bool2x3 operator >= (int lhs, const int2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int2x3 matrix.</summary>

	inline static int2x3 operator - (int2x3 val) { return int2x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int2x3 matrix.</summary>

	inline static int2x3 operator + (int2x3 val) { return int2x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two int2x3 matrices.</summary>

	inline static bool2x3 operator == (const int2x3& lhs, const int2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a int2x3 matrix and a int value.</summary>

	inline static bool2x3 operator == (const int2x3& lhs, int rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int2x3 matrix.</summary>

	inline static bool2x3 operator == (int lhs, const int2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two int2x3 matrices.</summary>

	inline static bool2x3 operator != (const int2x3& lhs, const int2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a int2x3 matrix and a int value.</summary>

	inline static bool2x3 operator != (const int2x3& lhs, int rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int2x3 matrix.</summary>

	inline static bool2x3 operator != (int lhs, const int2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region int2x4
	struct int2x4
	{
		int2 c0, c1, c2, c3;
		int2x4() : c0(), c1(), c2(), c3() {}
		int2x4(int m00, int m01, int m02, int m03,
			int m10, int m11, int m12, int m13)
		{
			c0 = int2(m00, m10);
			c1 = int2(m01, m11);
			c2 = int2(m02, m12);
			c3 = int2(m03, m13);
		}
		int2x4(int2 c0, int2 c1, int2 c2, int2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		int2x4(int v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int2x4 matrices.</summary>

	inline static int2x4 operator * (const int2x4& lhs, const int2x4& rhs) { return int2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int2x4 matrix and a int value.</summary>

	inline static int2x4 operator * (const int2x4& lhs, int rhs) { return int2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int2x4 matrix.</summary>

	inline static int2x4 operator * (int lhs, const int2x4& rhs) { return int2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two int2x4 matrices.</summary>

	inline static int2x4 operator + (const int2x4& lhs, const int2x4& rhs) { return int2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a int2x4 matrix and a int value.</summary>

	inline static int2x4 operator + (const int2x4& lhs, int rhs) { return int2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int2x4 matrix.</summary>

	inline static int2x4 operator + (int lhs, const int2x4& rhs) { return int2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int2x4 matrices.</summary>

	inline static int2x4 operator - (const int2x4& lhs, const int2x4& rhs) { return int2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int2x4 matrix and a int value.</summary>

	inline static int2x4 operator - (const int2x4& lhs, int rhs) { return int2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int2x4 matrix.</summary>

	inline static int2x4 operator - (int lhs, const int2x4& rhs) { return int2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two int2x4 matrices.</summary>

	inline static int2x4 operator / (const int2x4& lhs, const int2x4& rhs) { return int2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a int2x4 matrix and a int value.</summary>

	inline static int2x4 operator / (const int2x4& lhs, int rhs) { return int2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int2x4 matrix.</summary>

	inline static int2x4 operator / (int lhs, const int2x4& rhs) { return int2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a int2x4 matrix.</summary>

	inline static int2x4 operator ++ (int2x4 val) { return int2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a int2x4 matrix.</summary>

	inline static int2x4 operator -- (int2x4 val) { return int2x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two int2x4 matrices.</summary>

	inline static bool2x4 operator < (const int2x4& lhs, const int2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a int2x4 matrix and a int value.</summary>

	inline static bool2x4 operator < (const int2x4& lhs, int rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int2x4 matrix.</summary>

	inline static bool2x4 operator < (int lhs, const int2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int2x4 matrices.</summary>

	inline static bool2x4 operator <= (const int2x4& lhs, const int2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int2x4 matrix and a int value.</summary>

	inline static bool2x4 operator <= (const int2x4& lhs, int rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int2x4 matrix.</summary>

	inline static bool2x4 operator <= (int lhs, const int2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two int2x4 matrices.</summary>

	inline static bool2x4 operator > (const int2x4& lhs, const int2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a int2x4 matrix and a int value.</summary>

	inline static bool2x4 operator > (const int2x4& lhs, int rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int2x4 matrix.</summary>

	inline static bool2x4 operator > (int lhs, const int2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int2x4 matrices.</summary>

	inline static bool2x4 operator >= (const int2x4& lhs, const int2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int2x4 matrix and a int value.</summary>

	inline static bool2x4 operator >= (const int2x4& lhs, int rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int2x4 matrix.</summary>

	inline static bool2x4 operator >= (int lhs, const int2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int2x4 matrix.</summary>

	inline static int2x4 operator - (int2x4 val) { return int2x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int2x4 matrix.</summary>

	inline static int2x4 operator + (int2x4 val) { return int2x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two int2x4 matrices.</summary>

	inline static bool2x4 operator == (const int2x4& lhs, const int2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a int2x4 matrix and a int value.</summary>

	inline static bool2x4 operator == (const int2x4& lhs, int rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int2x4 matrix.</summary>

	inline static bool2x4 operator == (int lhs, const int2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two int2x4 matrices.</summary>

	inline static bool2x4 operator != (const int2x4& lhs, const int2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a int2x4 matrix and a int value.</summary>

	inline static bool2x4 operator != (const int2x4& lhs, int rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int2x4 matrix.</summary>

	inline static bool2x4 operator != (int lhs, const int2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region int3
	struct int3 {
		int x, y, z;
		int3() : x(0), y(0), z(0) {}
		int3(int x, int y, int z) : x(x), y(y), z(z) {}
		int3(int v) : x(v), y(v), z(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int3 vectors.</summary>

	inline static int3 operator * (const int3& lhs, const int3& rhs) { return int3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int3 vector and a int value.</summary>

	inline static int3 operator * (const int3& lhs, int rhs) { return int3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int3 vector.</summary>

	inline static int3 operator * (int lhs, const int3& rhs) { return int3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


	/// <summary>Returns the result of a componentwise addition operation on two int3 vectors.</summary>

	inline static int3 operator + (const int3& lhs, const int3& rhs) { return int3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

	/// <summary>Returns the result of a componentwise addition operation on a int3 vector and a int value.</summary>

	inline static int3 operator + (const int3& lhs, int rhs) { return int3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int3 vector.</summary>

	inline static int3 operator + (int lhs, const int3& rhs) { return int3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int3 vectors.</summary>

	inline static int3 operator - (const int3& lhs, const int3& rhs) { return int3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int3 vector and a int value.</summary>

	inline static int3 operator - (const int3& lhs, int rhs) { return int3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int3 vector.</summary>

	inline static int3 operator - (int lhs, const int3& rhs) { return int3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


	/// <summary>Returns the result of a componentwise division operation on two int3 vectors.</summary>

	inline static int3 operator / (const int3& lhs, const int3& rhs) { return int3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

	/// <summary>Returns the result of a componentwise division operation on a int3 vector and a int value.</summary>

	inline static int3 operator / (const int3& lhs, int rhs) { return int3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int3 vector.</summary>

	inline static int3 operator / (int lhs, const int3& rhs) { return int3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


	/// <summary>Returns the result of a componentwise increment operation on a int3 vector.</summary>

	inline static int3 operator ++ (int3 val) { return int3(++val.x, ++val.y, ++val.z); }


	/// <summary>Returns the result of a componentwise decrement operation on a int3 vector.</summary>

	inline static int3 operator -- (int3 val) { return int3(--val.x, --val.y, --val.z); }


	/// <summary>Returns the result of a componentwise less than operation on two int3 vectors.</summary>

	inline static bool3 operator < (const int3& lhs, const int3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

	/// <summary>Returns the result of a componentwise less than operation on a int3 vector and a int value.</summary>

	inline static bool3 operator < (const int3& lhs, int rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int3 vector.</summary>

	inline static bool3 operator < (int lhs, const int3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int3 vectors.</summary>

	inline static bool3 operator <= (const int3& lhs, const int3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int3 vector and a int value.</summary>

	inline static bool3 operator <= (const int3& lhs, int rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int3 vector.</summary>

	inline static bool3 operator <= (int lhs, const int3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


	/// <summary>Returns the result of a componentwise greater than operation on two int3 vectors.</summary>

	inline static bool3 operator > (const int3& lhs, const int3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

	/// <summary>Returns the result of a componentwise greater than operation on a int3 vector and a int value.</summary>

	inline static bool3 operator > (const int3& lhs, int rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int3 vector.</summary>

	inline static bool3 operator > (int lhs, const int3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int3 vectors.</summary>

	inline static bool3 operator >= (const int3& lhs, const int3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int3 vector and a int value.</summary>

	inline static bool3 operator >= (const int3& lhs, int rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int3 vector.</summary>

	inline static bool3 operator >= (int lhs, const int3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int3 vector.</summary>

	inline static int3 operator - (int3 val) { return int3(-val.x, -val.y, -val.z); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int3 vector.</summary>

	inline static int3 operator + (int3 val) { return int3(+val.x, +val.y, +val.z); }


	/// <summary>Returns the result of a componentwise equality operation on two int3 vectors.</summary>

	inline static bool3 operator == (const int3& lhs, const int3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

	/// <summary>Returns the result of a componentwise equality operation on a int3 vector and a int value.</summary>

	inline static bool3 operator == (const int3& lhs, int rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int3 vector.</summary>

	inline static bool3 operator == (int lhs, const int3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


	/// <summary>Returns the result of a componentwise not equal operation on two int3 vectors.</summary>

	inline static bool3 operator != (const int3& lhs, const int3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

	/// <summary>Returns the result of a componentwise not equal operation on a int3 vector and a int value.</summary>

	inline static bool3 operator != (const int3& lhs, int rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int3 vector.</summary>

	inline static bool3 operator != (int lhs, const int3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region int3x2
	struct int3x2
	{
		int3 c0, c1;
		int3x2() : c0(), c1() {}
		int3x2(int m00, int m01,
			int m10, int m11,
			int m20, int m21)
		{
			c0 = int3(m00, m10, m20);
			c1 = int3(m01, m11, m21);
		}

		int3x2(int3 c0, int3 c1) : c0(c0), c1(c1) {}
		int3x2(int v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int3x2 matrices.</summary>

	inline static int3x2 operator * (const int3x2& lhs, const int3x2& rhs) { return int3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int3x2 matrix and a int value.</summary>

	inline static int3x2 operator * (const int3x2& lhs, int rhs) { return int3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int3x2 matrix.</summary>

	inline static int3x2 operator * (int lhs, const int3x2& rhs) { return int3x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two int3x2 matrices.</summary>

	inline static int3x2 operator + (const int3x2& lhs, const int3x2& rhs) { return int3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a int3x2 matrix and a int value.</summary>

	inline static int3x2 operator + (const int3x2& lhs, int rhs) { return int3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int3x2 matrix.</summary>

	inline static int3x2 operator + (int lhs, const int3x2& rhs) { return int3x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int3x2 matrices.</summary>

	inline static int3x2 operator - (const int3x2& lhs, const int3x2& rhs) { return int3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int3x2 matrix and a int value.</summary>

	inline static int3x2 operator - (const int3x2& lhs, int rhs) { return int3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int3x2 matrix.</summary>

	inline static int3x2 operator - (int lhs, const int3x2& rhs) { return int3x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two int3x2 matrices.</summary>

	inline static int3x2 operator / (const int3x2& lhs, const int3x2& rhs) { return int3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a int3x2 matrix and a int value.</summary>

	inline static int3x2 operator / (const int3x2& lhs, int rhs) { return int3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int3x2 matrix.</summary>

	inline static int3x2 operator / (int lhs, const int3x2& rhs) { return int3x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a int3x2 matrix.</summary>

	inline static int3x2 operator ++ (int3x2 val) { return int3x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a int3x2 matrix.</summary>

	inline static int3x2 operator -- (int3x2 val) { return int3x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two int3x2 matrices.</summary>

	inline static bool3x2 operator < (const int3x2& lhs, const int3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a int3x2 matrix and a int value.</summary>

	inline static bool3x2 operator < (const int3x2& lhs, int rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int3x2 matrix.</summary>

	inline static bool3x2 operator < (int lhs, const int3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int3x2 matrices.</summary>

	inline static bool3x2 operator <= (const int3x2& lhs, const int3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int3x2 matrix and a int value.</summary>

	inline static bool3x2 operator <= (const int3x2& lhs, int rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int3x2 matrix.</summary>

	inline static bool3x2 operator <= (int lhs, const int3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two int3x2 matrices.</summary>

	inline static bool3x2 operator > (const int3x2& lhs, const int3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a int3x2 matrix and a int value.</summary>

	inline static bool3x2 operator > (const int3x2& lhs, int rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int3x2 matrix.</summary>

	inline static bool3x2 operator > (int lhs, const int3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int3x2 matrices.</summary>

	inline static bool3x2 operator >= (const int3x2& lhs, const int3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int3x2 matrix and a int value.</summary>

	inline static bool3x2 operator >= (const int3x2& lhs, int rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int3x2 matrix.</summary>

	inline static bool3x2 operator >= (int lhs, const int3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int3x2 matrix.</summary>

	inline static int3x2 operator - (int3x2 val) { return int3x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int3x2 matrix.</summary>

	inline static int3x2 operator + (int3x2 val) { return int3x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two int3x2 matrices.</summary>

	inline static bool3x2 operator == (const int3x2& lhs, const int3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a int3x2 matrix and a int value.</summary>

	inline static bool3x2 operator == (const int3x2& lhs, int rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int3x2 matrix.</summary>

	inline static bool3x2 operator == (int lhs, const int3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two int3x2 matrices.</summary>

	inline static bool3x2 operator != (const int3x2& lhs, const int3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a int3x2 matrix and a int value.</summary>

	inline static bool3x2 operator != (const int3x2& lhs, int rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int3x2 matrix.</summary>

	inline static bool3x2 operator != (int lhs, const int3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region int3x3
	struct int3x3
	{
		int3 c0, c1, c2;
		int3x3() : c0(), c1(), c2() {}
		int3x3(int m00, int m01, int m02,
			int m10, int m11, int m12,
			int m20, int m21, int m22)
		{
			c0 = int3(m00, m10, m20);
			c1 = int3(m01, m11, m21);
			c2 = int3(m02, m12, m22);
		}
		int3x3(int3 c0, int3 c1, int3 c2) : c0(c0), c1(c1), c2(c2) {}
		int3x3(int v) : c0(v), c1(v), c2(v) {}

	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int3x3 matrices.</summary>

	inline static int3x3 operator * (const int3x3& lhs, const int3x3& rhs) { return int3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int3x3 matrix and a int value.</summary>

	inline static int3x3 operator * (const int3x3& lhs, int rhs) { return int3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int3x3 matrix.</summary>

	inline static int3x3 operator * (int lhs, const int3x3& rhs) { return int3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two int3x3 matrices.</summary>

	inline static int3x3 operator + (const int3x3& lhs, const int3x3& rhs) { return int3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a int3x3 matrix and a int value.</summary>

	inline static int3x3 operator + (const int3x3& lhs, int rhs) { return int3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int3x3 matrix.</summary>

	inline static int3x3 operator + (int lhs, const int3x3& rhs) { return int3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int3x3 matrices.</summary>

	inline static int3x3 operator - (const int3x3& lhs, const int3x3& rhs) { return int3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int3x3 matrix and a int value.</summary>

	inline static int3x3 operator - (const int3x3& lhs, int rhs) { return int3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int3x3 matrix.</summary>

	inline static int3x3 operator - (int lhs, const int3x3& rhs) { return int3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two int3x3 matrices.</summary>

	inline static int3x3 operator / (const int3x3& lhs, const int3x3& rhs) { return int3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a int3x3 matrix and a int value.</summary>

	inline static int3x3 operator / (const int3x3& lhs, int rhs) { return int3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int3x3 matrix.</summary>

	inline static int3x3 operator / (int lhs, const int3x3& rhs) { return int3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a int3x3 matrix.</summary>

	inline static int3x3 operator ++ (int3x3 val) { return int3x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a int3x3 matrix.</summary>

	inline static int3x3 operator -- (int3x3 val) { return int3x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two int3x3 matrices.</summary>

	inline static bool3x3 operator < (const int3x3& lhs, const int3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a int3x3 matrix and a int value.</summary>

	inline static bool3x3 operator < (const int3x3& lhs, int rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int3x3 matrix.</summary>

	inline static bool3x3 operator < (int lhs, const int3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int3x3 matrices.</summary>

	inline static bool3x3 operator <= (const int3x3& lhs, const int3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int3x3 matrix and a int value.</summary>

	inline static bool3x3 operator <= (const int3x3& lhs, int rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int3x3 matrix.</summary>

	inline static bool3x3 operator <= (int lhs, const int3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two int3x3 matrices.</summary>

	inline static bool3x3 operator > (const int3x3& lhs, const int3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a int3x3 matrix and a int value.</summary>

	inline static bool3x3 operator > (const int3x3& lhs, int rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int3x3 matrix.</summary>

	inline static bool3x3 operator > (int lhs, const int3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int3x3 matrices.</summary>

	inline static bool3x3 operator >= (const int3x3& lhs, const int3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int3x3 matrix and a int value.</summary>

	inline static bool3x3 operator >= (const int3x3& lhs, int rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int3x3 matrix.</summary>

	inline static bool3x3 operator >= (int lhs, const int3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int3x3 matrix.</summary>

	inline static int3x3 operator - (int3x3 val) { return int3x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int3x3 matrix.</summary>

	inline static int3x3 operator + (int3x3 val) { return int3x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two int3x3 matrices.</summary>

	inline static bool3x3 operator == (const int3x3& lhs, const int3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a int3x3 matrix and a int value.</summary>

	inline static bool3x3 operator == (const int3x3& lhs, int rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int3x3 matrix.</summary>

	inline static bool3x3 operator == (int lhs, const int3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two int3x3 matrices.</summary>

	inline static bool3x3 operator != (const int3x3& lhs, const int3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a int3x3 matrix and a int value.</summary>

	inline static bool3x3 operator != (const int3x3& lhs, int rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int3x3 matrix.</summary>

	inline static bool3x3 operator != (int lhs, const int3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region int3x4
	struct int3x4
	{
		int3 c0, c1, c2, c3;
		int3x4() : c0(), c1(), c2(), c3() {}
		int3x4(int m00, int m01, int m02, int m03,
			int m10, int m11, int m12, int m13,
			int m20, int m21, int m22, int m23)
		{
			c0 = int3(m00, m10, m20);
			c1 = int3(m01, m11, m21);
			c2 = int3(m02, m12, m22);
			c3 = int3(m03, m13, m23);
		}
		int3x4(int3 c0, int3 c1, int3 c2, int3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		int3x4(int v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int3x4 matrices.</summary>

	inline static int3x4 operator * (const int3x4& lhs, const int3x4& rhs) { return int3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int3x4 matrix and a int value.</summary>

	inline static int3x4 operator * (const int3x4& lhs, int rhs) { return int3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int3x4 matrix.</summary>

	inline static int3x4 operator * (int lhs, const int3x4& rhs) { return int3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two int3x4 matrices.</summary>

	inline static int3x4 operator + (const int3x4& lhs, const int3x4& rhs) { return int3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a int3x4 matrix and a int value.</summary>

	inline static int3x4 operator + (const int3x4& lhs, int rhs) { return int3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int3x4 matrix.</summary>

	inline static int3x4 operator + (int lhs, const int3x4& rhs) { return int3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int3x4 matrices.</summary>

	inline static int3x4 operator - (const int3x4& lhs, const int3x4& rhs) { return int3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int3x4 matrix and a int value.</summary>

	inline static int3x4 operator - (const int3x4& lhs, int rhs) { return int3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int3x4 matrix.</summary>

	inline static int3x4 operator - (int lhs, const int3x4& rhs) { return int3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two int3x4 matrices.</summary>

	inline static int3x4 operator / (const int3x4& lhs, const int3x4& rhs) { return int3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a int3x4 matrix and a int value.</summary>

	inline static int3x4 operator / (const int3x4& lhs, int rhs) { return int3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int3x4 matrix.</summary>

	inline static int3x4 operator / (int lhs, const int3x4& rhs) { return int3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

	/// <summary>Returns the result of a componentwise increment operation on a int3x4 matrix.</summary>

	inline static int3x4 operator ++ (int3x4 val) { return int3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a int3x4 matrix.</summary>

	inline static int3x4 operator -- (int3x4 val) { return int3x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two int3x4 matrices.</summary>

	inline static bool3x4 operator < (const int3x4& lhs, const int3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a int3x4 matrix and a int value.</summary>

	inline static bool3x4 operator < (const int3x4& lhs, int rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int3x4 matrix.</summary>

	inline static bool3x4 operator < (int lhs, const int3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int3x4 matrices.</summary>

	inline static bool3x4 operator <= (const int3x4& lhs, const int3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int3x4 matrix and a int value.</summary>

	inline static bool3x4 operator <= (const int3x4& lhs, int rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int3x4 matrix.</summary>

	inline static bool3x4 operator <= (int lhs, const int3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two int3x4 matrices.</summary>

	inline static bool3x4 operator > (const int3x4& lhs, const int3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a int3x4 matrix and a int value.</summary>

	inline static bool3x4 operator > (const int3x4& lhs, int rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int3x4 matrix.</summary>

	inline static bool3x4 operator > (int lhs, const int3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int3x4 matrices.</summary>

	inline static bool3x4 operator >= (const int3x4& lhs, const int3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int3x4 matrix and a int value.</summary>

	inline static bool3x4 operator >= (const int3x4& lhs, int rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int3x4 matrix.</summary>

	inline static bool3x4 operator >= (int lhs, const int3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int3x4 matrix.</summary>

	inline static int3x4 operator - (int3x4 val) { return int3x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int3x4 matrix.</summary>

	inline static int3x4 operator + (int3x4 val) { return int3x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two int3x4 matrices.</summary>

	inline static bool3x4 operator == (const int3x4& lhs, const int3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a int3x4 matrix and a int value.</summary>

	inline static bool3x4 operator == (const int3x4& lhs, int rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int3x4 matrix.</summary>

	inline static bool3x4 operator == (int lhs, const int3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two int3x4 matrices.</summary>

	inline static bool3x4 operator != (const int3x4& lhs, const int3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a int3x4 matrix and a int value.</summary>

	inline static bool3x4 operator != (const int3x4& lhs, int rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int3x4 matrix.</summary>

	inline static bool3x4 operator != (int lhs, const int3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region int4
	struct int4 {
		int x, y, z, w;
		int4() : x(0), y(0), z(0), w(0) {}
		int4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
		int4(int v) : x(v), y(v), z(v), w(v) {}
		int4(int3 xyz, int w) : w(w)
		{
			x = xyz.x;
			y = xyz.y;
			z = xyz.z;
		}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int4 vectors.</summary>

	inline static int4 operator * (const int4& lhs, const int4& rhs) { return int4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int4 vector and a int value.</summary>

	inline static int4 operator * (const int4& lhs, int rhs) { return int4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int4 vector.</summary>

	inline static int4 operator * (int lhs, const int4& rhs) { return int4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


	/// <summary>Returns the result of a componentwise addition operation on two int4 vectors.</summary>

	inline static int4 operator + (const int4& lhs, const int4& rhs) { return int4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

	/// <summary>Returns the result of a componentwise addition operation on a int4 vector and a int value.</summary>

	inline static int4 operator + (const int4& lhs, int rhs) { return int4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int4 vector.</summary>

	inline static int4 operator + (int lhs, const int4& rhs) { return int4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int4 vectors.</summary>

	inline static int4 operator - (const int4& lhs, const int4& rhs) { return int4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int4 vector and a int value.</summary>

	inline static int4 operator - (const int4& lhs, int rhs) { return int4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int4 vector.</summary>

	inline static int4 operator - (int lhs, const int4& rhs) { return int4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


	/// <summary>Returns the result of a componentwise division operation on two int4 vectors.</summary>

	inline static int4 operator / (const int4& lhs, const int4& rhs) { return int4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

	/// <summary>Returns the result of a componentwise division operation on a int4 vector and a int value.</summary>

	inline static int4 operator / (const int4& lhs, int rhs) { return int4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int4 vector.</summary>

	inline static int4 operator / (int lhs, const int4& rhs) { return int4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

	/// <summary>Returns the result of a componentwise increment operation on a int4 vector.</summary>

	inline static int4 operator ++ (int4 val) { return int4(++val.x, ++val.y, ++val.z, ++val.w); }


	/// <summary>Returns the result of a componentwise decrement operation on a int4 vector.</summary>

	inline static int4 operator -- (int4 val) { return int4(--val.x, --val.y, --val.z, --val.w); }


	/// <summary>Returns the result of a componentwise less than operation on two int4 vectors.</summary>

	inline static bool4 operator < (const int4& lhs, const int4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

	/// <summary>Returns the result of a componentwise less than operation on a int4 vector and a int value.</summary>

	inline static bool4 operator < (const int4& lhs, int rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int4 vector.</summary>

	inline static bool4 operator < (int lhs, const int4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int4 vectors.</summary>

	inline static bool4 operator <= (const int4& lhs, const int4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int4 vector and a int value.</summary>

	inline static bool4 operator <= (const int4& lhs, int rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int4 vector.</summary>

	inline static bool4 operator <= (int lhs, const int4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


	/// <summary>Returns the result of a componentwise greater than operation on two int4 vectors.</summary>

	inline static bool4 operator > (const int4& lhs, const int4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

	/// <summary>Returns the result of a componentwise greater than operation on a int4 vector and a int value.</summary>

	inline static bool4 operator > (const int4& lhs, int rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int4 vector.</summary>

	inline static bool4 operator > (int lhs, const int4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int4 vectors.</summary>

	inline static bool4 operator >= (const int4& lhs, const int4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int4 vector and a int value.</summary>

	inline static bool4 operator >= (const int4& lhs, int rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int4 vector.</summary>

	inline static bool4 operator >= (int lhs, const int4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int4 vector.</summary>

	inline static int4 operator - (int4 val) { return int4(-val.x, -val.y, -val.z, -val.w); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int4 vector.</summary>

	inline static int4 operator + (int4 val) { return int4(+val.x, +val.y, +val.z, +val.w); }


	/// <summary>Returns the result of a componentwise equality operation on two int4 vectors.</summary>

	inline static bool4 operator == (const int4& lhs, const int4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on a int4 vector and a int value.</summary>

	inline static bool4 operator == (const int4& lhs, int rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int4 vector.</summary>

	inline static bool4 operator == (int lhs, const int4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


	/// <summary>Returns the result of a componentwise not equal operation on two int4 vectors.</summary>

	inline static bool4 operator != (const int4& lhs, const int4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

	/// <summary>Returns the result of a componentwise not equal operation on a int4 vector and a int value.</summary>

	inline static bool4 operator != (const int4& lhs, int rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int4 vector.</summary>

	inline static bool4 operator != (int lhs, const int4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region int4x2
	struct int4x2
	{
		int4 c0, c1;
		int4x2() : c0(), c1() {}
		int4x2(int m00, int m01,
			int m10, int m11,
			int m20, int m21,
			int m30, int m31)
		{
			c0 = int4(m00, m10, m20, m30);
			c1 = int4(m01, m11, m21, m31);
		}
		int4x2(int4 c0, int4 c1) : c0(c0), c1(c1) {}
		int4x2(int v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int4x2 matrices.</summary>

	inline static int4x2 operator * (const int4x2& lhs, const int4x2& rhs) { return int4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int4x2 matrix and a int value.</summary>

	inline static int4x2 operator * (const int4x2& lhs, int rhs) { return int4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int4x2 matrix.</summary>

	inline static int4x2 operator * (int lhs, const int4x2& rhs) { return int4x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two int4x2 matrices.</summary>

	inline static int4x2 operator + (const int4x2& lhs, const int4x2& rhs) { return int4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a int4x2 matrix and a int value.</summary>

	inline static int4x2 operator + (const int4x2& lhs, int rhs) { return int4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int4x2 matrix.</summary>

	inline static int4x2 operator + (int lhs, const int4x2& rhs) { return int4x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int4x2 matrices.</summary>

	inline static int4x2 operator - (const int4x2& lhs, const int4x2& rhs) { return int4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int4x2 matrix and a int value.</summary>

	inline static int4x2 operator - (const int4x2& lhs, int rhs) { return int4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int4x2 matrix.</summary>

	inline static int4x2 operator - (int lhs, const int4x2& rhs) { return int4x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two int4x2 matrices.</summary>

	inline static int4x2 operator / (const int4x2& lhs, const int4x2& rhs) { return int4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a int4x2 matrix and a int value.</summary>

	inline static int4x2 operator / (const int4x2& lhs, int rhs) { return int4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int4x2 matrix.</summary>

	inline static int4x2 operator / (int lhs, const int4x2& rhs) { return int4x2(lhs / rhs.c0, lhs / rhs.c1); }

	/// <summary>Returns the result of a componentwise increment operation on a int4x2 matrix.</summary>

	inline static int4x2 operator ++ (int4x2 val) { return int4x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a int4x2 matrix.</summary>

	inline static int4x2 operator -- (int4x2 val) { return int4x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two int4x2 matrices.</summary>

	inline static bool4x2 operator < (const int4x2& lhs, const int4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a int4x2 matrix and a int value.</summary>

	inline static bool4x2 operator < (const int4x2& lhs, int rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int4x2 matrix.</summary>

	inline static bool4x2 operator < (int lhs, const int4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int4x2 matrices.</summary>

	inline static bool4x2 operator <= (const int4x2& lhs, const int4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int4x2 matrix and a int value.</summary>

	inline static bool4x2 operator <= (const int4x2& lhs, int rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int4x2 matrix.</summary>

	inline static bool4x2 operator <= (int lhs, const int4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two int4x2 matrices.</summary>

	inline static bool4x2 operator > (const int4x2& lhs, const int4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a int4x2 matrix and a int value.</summary>

	inline static bool4x2 operator > (const int4x2& lhs, int rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int4x2 matrix.</summary>

	inline static bool4x2 operator > (int lhs, const int4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int4x2 matrices.</summary>

	inline static bool4x2 operator >= (const int4x2& lhs, const int4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int4x2 matrix and a int value.</summary>

	inline static bool4x2 operator >= (const int4x2& lhs, int rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int4x2 matrix.</summary>

	inline static bool4x2 operator >= (int lhs, const int4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int4x2 matrix.</summary>

	inline static int4x2 operator - (int4x2 val) { return int4x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int4x2 matrix.</summary>

	inline static int4x2 operator + (int4x2 val) { return int4x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two int4x2 matrices.</summary>

	inline static bool4x2 operator == (const int4x2& lhs, const int4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a int4x2 matrix and a int value.</summary>

	inline static bool4x2 operator == (const int4x2& lhs, int rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int4x2 matrix.</summary>

	inline static bool4x2 operator == (int lhs, const int4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two int4x2 matrices.</summary>

	inline static bool4x2 operator != (const int4x2& lhs, const int4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a int4x2 matrix and a int value.</summary>

	inline static bool4x2 operator != (const int4x2& lhs, int rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int4x2 matrix.</summary>

	inline static bool4x2 operator != (int lhs, const int4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region int4x3
	struct int4x3
	{
		int4 c0, c1, c2;
		int4x3() : c0(), c1(), c2() {}
		int4x3(int m00, int m01, int m02,
			int m10, int m11, int m12,
			int m20, int m21, int m22,
			int m30, int m31, int m32)
		{
			c0 = int4(m00, m10, m20, m30);
			c1 = int4(m01, m11, m21, m31);
			c2 = int4(m02, m12, m22, m32);
		}
		int4x3(int4 c0, int4 c1, int4 c2) : c0(c0), c1(c1), c2(c2) {}
		int4x3(int v) : c0(v), c1(v), c2(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int4x3 matrices.</summary>

	inline static int4x3 operator * (const int4x3& lhs, const int4x3& rhs) { return int4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int4x3 matrix and a int value.</summary>

	inline static int4x3 operator * (const int4x3& lhs, int rhs) { return int4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int4x3 matrix.</summary>

	inline static int4x3 operator * (int lhs, const int4x3& rhs) { return int4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two int4x3 matrices.</summary>

	inline static int4x3 operator + (const int4x3& lhs, const int4x3& rhs) { return int4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a int4x3 matrix and a int value.</summary>

	inline static int4x3 operator + (const int4x3& lhs, int rhs) { return int4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int4x3 matrix.</summary>

	inline static int4x3 operator + (int lhs, const int4x3& rhs) { return int4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int4x3 matrices.</summary>

	inline static int4x3 operator - (const int4x3& lhs, const int4x3& rhs) { return int4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int4x3 matrix and a int value.</summary>

	inline static int4x3 operator - (const int4x3& lhs, int rhs) { return int4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int4x3 matrix.</summary>

	inline static int4x3 operator - (int lhs, const int4x3& rhs) { return int4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two int4x3 matrices.</summary>

	inline static int4x3 operator / (const int4x3& lhs, const int4x3& rhs) { return int4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a int4x3 matrix and a int value.</summary>

	inline static int4x3 operator / (const int4x3& lhs, int rhs) { return int4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int4x3 matrix.</summary>

	inline static int4x3 operator / (int lhs, const int4x3& rhs) { return int4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a int4x3 matrix.</summary>

	inline static int4x3 operator ++ (int4x3 val) { return int4x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a int4x3 matrix.</summary>

	inline static int4x3 operator -- (int4x3 val) { return int4x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two int4x3 matrices.</summary>

	inline static bool4x3 operator < (const int4x3& lhs, const int4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a int4x3 matrix and a int value.</summary>

	inline static bool4x3 operator < (const int4x3& lhs, int rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int4x3 matrix.</summary>

	inline static bool4x3 operator < (int lhs, const int4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int4x3 matrices.</summary>

	inline static bool4x3 operator <= (const int4x3& lhs, const int4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int4x3 matrix and a int value.</summary>

	inline static bool4x3 operator <= (const int4x3& lhs, int rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int4x3 matrix.</summary>

	inline static bool4x3 operator <= (int lhs, const int4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two int4x3 matrices.</summary>

	inline static bool4x3 operator > (const int4x3& lhs, const int4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a int4x3 matrix and a int value.</summary>

	inline static bool4x3 operator > (const int4x3& lhs, int rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int4x3 matrix.</summary>

	inline static bool4x3 operator > (int lhs, const int4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int4x3 matrices.</summary>

	inline static bool4x3 operator >= (const int4x3& lhs, const int4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int4x3 matrix and a int value.</summary>

	inline static bool4x3 operator >= (const int4x3& lhs, int rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int4x3 matrix.</summary>

	inline static bool4x3 operator >= (int lhs, const int4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int4x3 matrix.</summary>

	inline static int4x3 operator - (int4x3 val) { return int4x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int4x3 matrix.</summary>

	inline static int4x3 operator + (int4x3 val) { return int4x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two int4x3 matrices.</summary>

	inline static bool4x3 operator == (const int4x3& lhs, const int4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a int4x3 matrix and a int value.</summary>

	inline static bool4x3 operator == (const int4x3& lhs, int rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int4x3 matrix.</summary>

	inline static bool4x3 operator == (int lhs, const int4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two int4x3 matrices.</summary>

	inline static bool4x3 operator != (const int4x3& lhs, const int4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a int4x3 matrix and a int value.</summary>

	inline static bool4x3 operator != (const int4x3& lhs, int rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int4x3 matrix.</summary>

	inline static bool4x3 operator != (int lhs, const int4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region int4x4
	struct int4x4
	{
		int4 c0, c1, c2, c3;
		int4x4() : c0(), c1(), c2(), c3() {}
		int4x4(int m00, int m01, int m02, int m03,
			int m10, int m11, int m12, int m13,
			int m20, int m21, int m22, int m23,
			int m30, int m31, int m32, int m33)
		{
			c0 = int4(m00, m10, m20, m30);
			c1 = int4(m01, m11, m21, m31);
			c2 = int4(m02, m12, m22, m32);
			c3 = int4(m03, m13, m23, m33);
		}
		int4x4(int4 c0, int4 c1, int4 c2, int4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		int4x4(int v) : c0(v), c1(v), c2(v), c3(v) {}

		int4x4(int3x3 rotation, int3 translation)
		{
			c0 = int4(rotation.c0, 0.0f);
			c1 = int4(rotation.c1, 0.0f);
			c2 = int4(rotation.c2, 0.0f);
			c3 = int4(translation, 1.0f);
		}


	};


	/// <summary>Returns the result of a componentwise multiplication operation on two int4x4 matrices.</summary>

	inline static int4x4 operator * (const int4x4& lhs, const int4x4& rhs) { return int4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int4x4 matrix and a int value.</summary>

	inline static int4x4 operator * (const int4x4& lhs, int rhs) { return int4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a int value and a int4x4 matrix.</summary>

	inline static int4x4 operator * (int lhs, const int4x4& rhs) { return int4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two int4x4 matrices.</summary>

	inline static int4x4 operator + (const int4x4& lhs, const int4x4& rhs) { return int4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a int4x4 matrix and a int value.</summary>

	inline static int4x4 operator + (const int4x4& lhs, int rhs) { return int4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a int value and a int4x4 matrix.</summary>

	inline static int4x4 operator + (int lhs, const int4x4& rhs) { return int4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two int4x4 matrices.</summary>

	inline static int4x4 operator - (const int4x4& lhs, const int4x4& rhs) { return int4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int4x4 matrix and a int value.</summary>

	inline static int4x4 operator - (const int4x4& lhs, int rhs) { return int4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a int value and a int4x4 matrix.</summary>

	inline static int4x4 operator - (int lhs, const int4x4& rhs) { return int4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two int4x4 matrices.</summary>

	inline static int4x4 operator / (const int4x4& lhs, const int4x4& rhs) { return int4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a int4x4 matrix and a int value.</summary>

	inline static int4x4 operator / (const int4x4& lhs, int rhs) { return int4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a int value and a int4x4 matrix.</summary>

	inline static int4x4 operator / (int lhs, const int4x4& rhs) { return int4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a int4x4 matrix.</summary>

	inline static int4x4 operator ++ (int4x4 val) { return int4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a int4x4 matrix.</summary>

	inline static int4x4 operator -- (int4x4 val) { return int4x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two int4x4 matrices.</summary>

	inline static bool4x4 operator < (const int4x4& lhs, const int4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a int4x4 matrix and a int value.</summary>

	inline static bool4x4 operator < (const int4x4& lhs, int rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a int value and a int4x4 matrix.</summary>

	inline static bool4x4 operator < (int lhs, const int4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two int4x4 matrices.</summary>

	inline static bool4x4 operator <= (const int4x4& lhs, const int4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int4x4 matrix and a int value.</summary>

	inline static bool4x4 operator <= (const int4x4& lhs, int rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a int value and a int4x4 matrix.</summary>

	inline static bool4x4 operator <= (int lhs, const int4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two int4x4 matrices.</summary>

	inline static bool4x4 operator > (const int4x4& lhs, const int4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a int4x4 matrix and a int value.</summary>

	inline static bool4x4 operator > (const int4x4& lhs, int rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a int value and a int4x4 matrix.</summary>

	inline static bool4x4 operator > (int lhs, const int4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two int4x4 matrices.</summary>

	inline static bool4x4 operator >= (const int4x4& lhs, const int4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int4x4 matrix and a int value.</summary>

	inline static bool4x4 operator >= (const int4x4& lhs, int rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a int value and a int4x4 matrix.</summary>

	inline static bool4x4 operator >= (int lhs, const int4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a int4x4 matrix.</summary>

	inline static int4x4 operator - (int4x4 val) { return int4x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a int4x4 matrix.</summary>

	inline static int4x4 operator + (int4x4 val) { return int4x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two int4x4 matrices.</summary>

	inline static bool4x4 operator == (const int4x4& lhs, const int4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a int4x4 matrix and a int value.</summary>

	inline static bool4x4 operator == (const int4x4& lhs, int rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a int value and a int4x4 matrix.</summary>

	inline static bool4x4 operator == (int lhs, const int4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two int4x4 matrices.</summary>

	inline static bool4x4 operator != (const int4x4& lhs, const int4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a int4x4 matrix and a int value.</summary>

	inline static bool4x4 operator != (const int4x4& lhs, int rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a int value and a int4x4 matrix.</summary>

	inline static bool4x4 operator != (int lhs, const int4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic


	/// <summary>Returns the Tangent of a int value.</summary>
	inline static int Tan(int x) { return (int)tan(x); }

	/// <summary>Returns the componentwise Tangent of a int2 vector.</summary>
	inline static int2 Tan(int2 x) { return int2(Tan(x.x), Tan(x.y)); }

	/// <summary>Returns the componentwise Tangent of a int3 vector.</summary>
	inline static int3 Tan(int3 x) { return int3(Tan(x.x), Tan(x.y), Tan(x.z)); }

	/// <summary>Returns the componentwise Tangent of a int4 vector.</summary>
	inline static int4 Tan(int4 x) { return int4(Tan(x.x), Tan(x.y), Tan(x.z), Tan(x.w)); }


	/// <summary>Returns the hyperbolic Tangent of a int value.</summary>
	inline static int Tanh(int x) { return (int)tanh(x); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a int2 vector.</summary>
	inline static int2 Tanh(int2 x) { return int2(Tanh(x.x), Tanh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a int3 vector.</summary>
	inline static int3 Tanh(int3 x) { return int3(Tanh(x.x), Tanh(x.y), Tanh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a int4 vector.</summary>
	inline static int4 Tanh(int4 x) { return int4(Tanh(x.x), Tanh(x.y), Tanh(x.z), Tanh(x.w)); }


	/// <summary>Returns the arcTangent of a int value.</summary>
	inline static int Atan(int x) { return (int)atan(x); }

	/// <summary>Returns the componentwise arcTangent of a int2 vector.</summary>
	inline static int2 Atan(int2 x) { return int2(Atan(x.x), Atan(x.y)); }

	/// <summary>Returns the componentwise arcTangent of a int3 vector.</summary>
	inline static int3 Atan(int3 x) { return int3(Atan(x.x), Atan(x.y), Atan(x.z)); }

	/// <summary>Returns the componentwise arcTangent of a int4 vector.</summary>
	inline static int4 Atan(int4 x) { return int4(Atan(x.x), Atan(x.y), Atan(x.z), Atan(x.w)); }


	/// <summary>Returns the 2-argument arcTangent of a pair of int values.</summary>
	inline static int Atan2(int y, int x) { return (int)atan2(y, x); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of ints2 vectors.</summary>
	inline static int2 Atan2(int2 y, int2 x) { return int2(Atan2(y.x, x.x), Atan2(y.y, x.y)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of ints3 vectors.</summary>
	inline static int3 Atan2(int3 y, int3 x) { return int3(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of ints4 vectors.</summary>
	inline static int4 Atan2(int4 y, int4 x) { return int4(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z), Atan2(y.w, x.w)); }


	/// <summary>Returns the CoSine of a int value.</summary>
	inline static int Cos(int x) { return (int)cos(x); }

	/// <summary>Returns the componentwise CoSine of a int2 vector.</summary>
	inline static int2 Cos(int2 x) { return int2(Cos(x.x), Cos(x.y)); }

	/// <summary>Returns the componentwise CoSine of a int3 vector.</summary>
	inline static int3 Cos(int3 x) { return int3(Cos(x.x), Cos(x.y), Cos(x.z)); }

	/// <summary>Returns the componentwise CoSine of a int4 vector.</summary>
	inline static int4 Cos(int4 x) { return int4(Cos(x.x), Cos(x.y), Cos(x.z), Cos(x.w)); }


	/// <summary>Returns the hyperbolic CoSine of a int value.</summary>
	inline static int Cosh(int x) { return (int)cosh(x); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a int2 vector.</summary>
	inline static int2 Cosh(int2 x) { return int2(Cosh(x.x), Cosh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a int3 vector.</summary>
	inline static int3 Cosh(int3 x) { return int3(Cosh(x.x), Cosh(x.y), Cosh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a int4 vector.</summary>
	inline static int4 Cosh(int4 x) { return int4(Cosh(x.x), Cosh(x.y), Cosh(x.z), Cosh(x.w)); }

	/// <summary>Returns the arcCoSine of a int value.</summary>
	inline static int Acos(int x) { return (int)acos((int)x); }

	/// <summary>Returns the componentwise arcCoSine of a int2 vector.</summary>
	inline static int2 Acos(int2 x) { return int2(Acos(x.x), Acos(x.y)); }

	/// <summary>Returns the componentwise arcCoSine of a int3 vector.</summary>
	inline static int3 Acos(int3 x) { return int3(Acos(x.x), Acos(x.y), Acos(x.z)); }

	/// <summary>Returns the componentwise arcCoSine of a int4 vector.</summary>
	inline static int4 Acos(int4 x) { return int4(Acos(x.x), Acos(x.y), Acos(x.z), Acos(x.w)); }


	/// <summary>Returns the Sine of a int value.</summary>
	inline static int Sin(int x) { return (int)sin((int)x); }

	/// <summary>Returns the componentwise Sine of a int2 vector.</summary>
	inline static int2 Sin(int2 x) { return int2(Sin(x.x), Sin(x.y)); }

	/// <summary>Returns the componentwise Sine of a int3 vector.</summary>
	inline static int3 Sin(int3 x) { return int3(Sin(x.x), Sin(x.y), Sin(x.z)); }

	/// <summary>Returns the componentwise Sine of a int4 vector.</summary>
	inline static int4 Sin(int4 x) { return int4(Sin(x.x), Sin(x.y), Sin(x.z), Sin(x.w)); }



	/// <summary>Returns the hyperbolic Sine of a int value.</summary>
	inline static int Sinh(int x) { return (int)sinh((int)x); }

	/// <summary>Returns the componentwise hyperbolic Sine of a int2 vector.</summary>
	inline static int2 Sinh(int2 x) { return int2(Sinh(x.x), Sinh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a int3 vector.</summary>
	inline static int3 Sinh(int3 x) { return int3(Sinh(x.x), Sinh(x.y), Sinh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a int4 vector.</summary>
	inline static int4 Sinh(int4 x) { return int4(Sinh(x.x), Sinh(x.y), Sinh(x.z), Sinh(x.w)); }


	/// <summary>Returns the arcSine of a int value.</summary>
	inline static int Asin(int x) { return (int)asin((int)x); }

	/// <summary>Returns the componentwise arcSine of a int2 vector.</summary>
	inline static int2 Asin(int2 x) { return int2(Asin(x.x), Asin(x.y)); }

	/// <summary>Returns the componentwise arcSine of a int3 vector.</summary>
	inline static int3 Asin(int3 x) { return int3(Asin(x.x), Asin(x.y), Asin(x.z)); }

	/// <summary>Returns the componentwise arcSine of a int4 vector.</summary>
	inline static int4 Asin(int4 x) { return int4(Asin(x.x), Asin(x.y), Asin(x.z), Asin(x.w)); }


	/// <summary>Returns the Dot product of two int values. Equivalent to multiplication.</summary>
	inline static int Dot(int x, int y) { return x * y; }

	/// <summary>Returns the Dot product of two int2 vectors.</summary>
	inline static int Dot(int2 x, int2 y) { return x.x * y.x + x.y * y.y; }

	/// <summary>Returns the Dot product of two int3 vectors.</summary>
	inline static int Dot(int3 x, int3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }

	/// <summary>Returns the Dot product of two int4 vectors.</summary>
	inline static int Dot(int4 x, int4 y) { return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w; }

	/// <summary>Returns the square root of a int value.</summary>
	inline static int Sqrt(int x) { return sqrt((double)x); }

	/// <summary>Returns the componentwise square root of a int2 vector.</summary>
	inline static int2 Sqrt(int2 x) { return int2(Sqrt(x.x), Sqrt(x.y)); }

	/// <summary>Returns the componentwise square root of a int3 vector.</summary>
	inline static int3 Sqrt(int3 x) { return int3(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z)); }

	/// <summary>Returns the componentwise square root of a int4 vector.</summary>
	inline static int4 Sqrt(int4 x) { return int4(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z), Sqrt(x.w)); }


	/// <summary>Returns the reciprocal square root of a int value.</summary>
	inline static int Rsqrt(int x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a int2 vector.</summary>
	inline static int2 Rsqrt(int2 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a int3 vector.</summary>
	inline static int3 Rsqrt(int3 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a int4 vector</summary>
	inline static int4 Rsqrt(int4 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns a Normalized version of the int2 vector x by scaling it by 1 / Length(x).</summary>
	inline static int2 Normalize(int2 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the int3 vector x by scaling it by 1 / Length(x).</summary>
	inline static int3 Normalize(int3 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the int4 vector x by scaling it by 1 / Length(x).</summary>
	inline static int4 Normalize(int4 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns the Length of a int2 vector.</summary>
	inline static int Length(int2 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a int3 vector.</summary>
	inline static int Length(int3 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a int4 vector.</summary>
	inline static int Length(int4 x) { return sqrt(Dot(x, x)); }




	/// <summary>Returns the squared Length of a int value. Equivalent to squaring the value.</summary>
	inline static int Lengthsq(int x) { return x * x; }

	/// <summary>Returns the squared Length of a int2 vector.</summary>
	inline static int Lengthsq(int2 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a int3 vector.</summary>
	inline static int Lengthsq(int3 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a int4 vector.</summary>
	inline static int Lengthsq(int4 x) { return Dot(x, x); }


	/// <summary>Returns the Distance between two int2 vectors.</summary>
	inline static int Distance(int2 x, int2 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two int3 vectors.</summary>
	inline static int Distance(int3 x, int3 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two int4 vectors.</summary>
	inline static int Distance(int4 x, int4 y) { return Length(y - x); }



	/// <summary>Returns the Distance between two int values.</summary>
	inline static int Distancesq(int x, int y) { return (y - x) * (y - x); }

	/// <summary>Returns the Distance between two int2 vectors.</summary>
	inline static int Distancesq(int2 x, int2 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two int3 vectors.</summary>
	inline static int Distancesq(int3 x, int3 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two int4 vectors.</summary>
	inline static int Distancesq(int4 x, int4 y) { return Lengthsq(y - x); }



	/// <summary>Returns the Cross product of two int3 vectors.</summary>
	inline static int3 Cross(int3 x, int3 y) {
		int3 retVal = x * int3(y.y, y.z, y.x) - int3(x.y, x.z, x.x) * y;
		return int3(retVal.y, retVal.z, retVal.x);
	}

	/// <summary>Returns the Sine and CoSine of the input int value x through the out parameters s and c.</summary>
	inline static void SinCos(int x, int* s, int* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input int2 vector x through the out parameters s and c.</summary>
	inline static void SinCos(int2 x, int2* s, int2* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input int3 vector x through the out parameters s and c.</summary>
	inline static void SinCos(int3 x, int3* s, int3* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input int4 vector x through the out parameters s and c.</summary>
	inline static void SinCos(int4 x, int4* s, int4* c) { *s = Sin(x); *c = Cos(x); }


	/// <summary>Returns the Minimum of two int values.</summary>
	inline static int Min(int x, int y) { return x < y ? x : y; }

	/// <summary>Returns the componentwise Minimum of two int2 vectors.</summary>
	inline static int2 Min(int2 x, int2 y) { return int2(Min(x.x, y.x), Min(x.y, y.y)); }

	/// <summary>Returns the componentwise Minimum of two int3 vectors.</summary>
	inline static int3 Min(int3 x, int3 y) { return int3(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z)); }

	/// <summary>Returns the componentwise Minimum of two int4 vectors.</summary>
	inline static int4 Min(int4 x, int4 y) { return int4(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z), Min(x.w, y.w)); }


	/// <summary>Returns the Maximum of two int values.</summary>
	inline static int Max(int x, int y) { return x > y ? x : y; }

	/// <summary>Returns the componentwise Maximum of two int2 vectors.</summary>
	inline static int2 Max(int2 x, int2 y) { return int2(Max(x.x, y.x), Max(x.y, y.y)); }

	/// <summary>Returns the componentwise Maximum of two int3 vectors.</summary>
	inline static int3 Max(int3 x, int3 y) { return int3(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z)); }

	/// <summary>Returns the componentwise Maximum of two int4 vectors.</summary>
	inline static int4 Max(int4 x, int4 y) { return int4(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z), Max(x.w, y.w)); }

	inline static int Lerp(int x, int y, int s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static int2 Lerp(int2 x, int2 y, int s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static int3 Lerp(int3 x, int3 y, int s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static int4 Lerp(int4 x, int4 y, int s) { return x + s * (y - x); }


	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static int2 Lerp(int2 x, int2 y, int2 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static int3 Lerp(int3 x, int3 y, int3 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static int4 Lerp(int4 x, int4 y, int4 s) { return x + s * (y - x); }

	/// <summary>Returns the result of normalizing a inting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static int Unlerp(int a, int b, int x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a inting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static int2 Unlerp(int2 a, int2 b, int2 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a inting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static int3 Unlerp(int3 a, int3 b, int3 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a inting point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static int4 Unlerp(int4 a, int4 b, int4 x) { return (x - a) / (b - a); }

	/// <summary>Returns the result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static int Remap(int a, int b, int c, int d, int x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static int2 Remap(int2 a, int2 b, int2 c, int2 d, int2 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static int3 Remap(int3 a, int3 b, int3 c, int3 d, int3 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static int4 Remap(int4 a, int4 b, int4 c, int4 d, int4 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the result of Clamping the value x into the interval [a, b], where x, a and b are int values.</summary>
	inline static int Clamp(int x, int a, int b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are int2 vectors.</summary>
	inline static int2 Clamp(int2 x, int2 a, int2 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are int3 vectors.</summary>
	inline static int3 Clamp(int3 x, int3 a, int3 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are int4 vectors.</summary>
	inline static int4 Clamp(int4 x, int4 a, int4 b) { return Max(a, Min(b, x)); }

	inline static int select_shuffle_component(int4 a, int4 b, char component)
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

	inline static int4 shuffle(int4 a, int4 b, char x, char y, char z, char w)
	{
		return int4(
			select_shuffle_component(a, b, x),
			select_shuffle_component(a, b, y),
			select_shuffle_component(a, b, z),
			select_shuffle_component(a, b, w));
	}

	inline static int4 movelh(int4 a, int4 b)
	{
		return shuffle(a, b, 0, 1, 4, 5);
	}
	inline static int4 movehl(int4 a, int4 b)
	{
		return shuffle(b, a, 2, 3, 6, 7);
	}
	// SSE shuffles
	inline static int4 unpacklo(int4 a, int4 b)
	{
		return shuffle(a, b, 0, 4, 1, 5);
	}
	inline static int4 unpackhi(int4 a, int4 b)
	{
		return shuffle(a, b, 2, 6, 3, 7);
	}
#pragma endregion
#pragma region Component
	/// <summary>Returns the Maximum component of a int2 vector.</summary>
	inline static int CMax(int2 x) { return Max(x.x, x.y); }

	/// <summary>Returns the Maximum component of a int3 vector.</summary>
	inline static int CMax(int3 x) { return Max(Max(x.x, x.y), x.z); }

	/// <summary>Returns the Maximum component of a int4 vector.</summary>
	inline static int CMax(int4 x) { return Max(Max(x.x, x.y), Max(x.z, x.w)); }

	/// <summary>Returns the horizontal sum of components of a int2 vector.</summary>
	inline static int Csum(int2 x) { return x.x + x.y; }

	/// <summary>Returns the horizontal sum of components of a int3 vector.</summary>
	inline static int Csum(int3 x) { return x.x + x.y + x.z; }

	/// <summary>Returns the horizontal sum of components of a int4 vector.</summary>
	inline static int Csum(int4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion

#pragma region Transpose
	/// <summary>Return the int2x2 Transpose of a int2x2 matrix.</summary>
	inline int2x2 Transpose(int2x2 v)
	{
		return int2x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y);
	}
	/// <summary>Return the int3x2 Transpose of a int2x3 matrix.</summary>
	inline int3x2 Transpose(int2x3 v)
	{
		return int3x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y);
	}
	/// <summary>Return the int4x2 Transpose of a int2x4 matrix.</summary>
	inline int4x2 Transpose(int2x4 v)
	{
		return int4x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y,
			v.c3.x, v.c3.y);
	}
	/// <summary>Return the int2x3 Transpose of a int3x2 matrix.</summary>
	inline int2x3 Transpose(int3x2 v)
	{
		return int2x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z);
	}
	/// <summary>Return the int3x3 Transpose of a int3x3 matrix.</summary>
	inline int3x3 Transpose(int3x3 v)
	{
		return int3x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z);
	}
	/// <summary>Return the int4x3 Transpose of a int3x4 matrix.</summary>
	inline static int4x3 Transpose(int3x4 v)
	{
		return int4x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z,
			v.c3.x, v.c3.y, v.c3.z);
	}
	/// <summary>Return the int2x4 Transpose of a int4x2 matrix.</summary>
	inline static int2x4 Transpose(int4x2 v)
	{
		return int2x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w);
	}
	/// <summary>Return the int3x4 Transpose of a int4x3 matrix.</summary>
	inline static int3x4 Transpose(int4x3 v)
	{
		return int3x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w);
	}
	/// <summary>Return the int4x4 Transpose of a int4x4 matrix.</summary>
	inline static int4x4 Transpose(int4x4 v)
	{
		return int4x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w,
			v.c3.x, v.c3.y, v.c3.z, v.c3.w);
	}

#pragma endregion
#pragma region Inverse
	/// <summary>Returns the int2x2 full Inverse of a int2x2 matrix.</summary>
	inline int2x2 Inverse(int2x2 m)
	{
		int a = m.c0.x;
		int b = m.c1.x;
		int c = m.c0.y;
		int d = m.c1.y;

		int det = a * d - b * c;

		return int2x2(d, -b, -c, a) * (1.0f / det);
	}
	/// <summary>Returns the int3x3 full Inverse of a int3x3 matrix.</summary>
	inline int3x3 Inverse(int3x3 m)
	{
		int3 c0 = m.c0;
		int3 c1 = m.c1;
		int3 c2 = m.c2;

		int3 t0 = int3(c1.x, c2.x, c0.x);
		int3 t1 = int3(c1.y, c2.y, c0.y);
		int3 t2 = int3(c1.z, c2.z, c0.z);

		int3 m0 = t1 * int3(t2.y, t2.z, t2.x) - int3(t1.y, t1.z, t1.x) * t2;
		int3 m1 = int3(t0.y, t0.z, t0.x) * t2 - t0 * int3(t2.y, t2.z, t2.x);
		int3 m2 = t0 * int3(t1.y, t1.z, t1.x) - t0 * int3(t2.y, t2.z, t2.x) * t1;

		int rcpDet = 1.0f / Csum(int3(t0.z, t0.x, t0.y) * m0);
		return int3x3(m0, m1, m2) * rcpDet;
	}
	// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
	inline static int3x4 fastInverse(int3x4 m)
	{
		int3 c0 = m.c0;
		int3 c1 = m.c1;
		int3 c2 = m.c2;
		int3 pos = m.c3;

		int3 r0 = int3(c0.x, c1.x, c2.x);
		int3 r1 = int3(c0.y, c1.y, c2.y);
		int3 r2 = int3(c0.z, c1.z, c2.z);

		pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);

		return int3x4(r0, r1, r2, pos);
	}
	/// <summary>Returns the int4x4 full Inverse of a int4x4 matrix.</summary>
	inline static int4x4 Inverse(int4x4 m)
	{
		int4 c0 = m.c0;
		int4 c1 = m.c1;
		int4 c2 = m.c2;
		int4 c3 = m.c3;

		int4 r0y_r1y_r0x_r1x = movelh(c1, c0);
		int4 r0z_r1z_r0w_r1w = movelh(c2, c3);
		int4 r2y_r3y_r2x_r3x = movehl(c0, c1);
		int4 r2z_r3z_r2w_r3w = movehl(c3, c2);

		int4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
		int4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
		int4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
		int4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

		int4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
		int4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
		int4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
		int4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
		int4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

		// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
		int4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
		int4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
		int4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

		// Expand inner terms back to 4 components. zw signs still need to be flipped
		int4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
		int4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

		int4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
		int4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

		// Calculate Minors
		int4 Minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

		int4 denom = r0_xyzw * Minors0;

		// Horizontal sum of denoMinator. Free sign flip of z and w compensates for misSing flip in inner terms.
		denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
		denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

		int4 rcp_denom_ppnn = int4(1.0f) / denom;
		int4x4 res;
		res.c0 = Minors0 * rcp_denom_ppnn;

		int4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
		int4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

		int4 Minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
		res.c1 = Minors1 * rcp_denom_ppnn;

		int4 Minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
		res.c2 = Minors2 * rcp_denom_ppnn;

		int4 Minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
		res.c3 = Minors3 * rcp_denom_ppnn;
		return res;
	}
	// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
	inline static int4x4 fastInverse(int4x4 m)
	{
		int4 c0 = m.c0;
		int4 c1 = m.c1;
		int4 c2 = m.c2;
		int4 pos = m.c3;

		int4 zero = int4(0);

		int4 t0 = unpacklo(c0, c2);
		int4 t1 = unpacklo(c1, zero);
		int4 t2 = unpackhi(c0, c2);
		int4 t3 = unpackhi(c1, zero);

		int4 r0 = unpacklo(t0, t1);
		int4 r1 = unpackhi(t0, t1);
		int4 r2 = unpacklo(t2, t3);

		pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);
		pos.w = 1.0f;

		return int4x4(r0, r1, r2, pos);
	}
#pragma endregion
#pragma region Determinant
	/// <summary>Returns the Determinant of a int2x2 matrix.</summary>
	inline int Determinant(int2x2 m)
	{
		int a = m.c0.x;
		int b = m.c1.x;
		int c = m.c0.y;
		int d = m.c1.y;

		return a * d - b * c;
	}
	/// <summary>Returns the Determinant of a int3x3 matrix.</summary>
	inline int Determinant(int3x3 m)
	{
		int3 c0 = m.c0;
		int3 c1 = m.c1;
		int3 c2 = m.c2;

		int m00 = c1.y * c2.z - c1.z * c2.y;
		int m01 = c0.y * c2.z - c0.z * c2.y;
		int m02 = c0.y * c1.z - c0.z * c1.y;

		return c0.x * m00 - c1.x * m01 + c2.x * m02;
	}
	/// <summary>Returns the Determinant of a int4x4 matrix.</summary>
	inline static int Determinant(int4x4 m)
	{
		int4 c0 = m.c0;
		int4 c1 = m.c1;
		int4 c2 = m.c2;
		int4 c3 = m.c3;

		int m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
		int m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
		int m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
		int m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

		return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
	}

#pragma endregion
}