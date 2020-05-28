#pragma once
#include "bool.h"
#include <math.h>
namespace UniEngine {
#pragma region double2
	struct double2 {
		double x, y;
		double2() : x(0), y(0) {}
		double2(double x, double y) : x(x), y(y) {}
		double2(double v) : x(v), y(v) {}
	};
	/// <summary>Returns the result of a componentwise multiplication operation on two double2 vectors.</summary>

	inline static double2 operator * (const double2& lhs, const double2& rhs) { return double2(lhs.x * rhs.x, lhs.y * rhs.y); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double2 vector and a double value.</summary>

	inline static double2 operator * (const double2& lhs, double rhs) { return double2(lhs.x * rhs, lhs.y * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double2 vector.</summary>

	inline static double2 operator * (double lhs, const double2& rhs) { return double2(lhs * rhs.x, lhs * rhs.y); }


	/// <summary>Returns the result of a componentwise addition operation on two double2 vectors.</summary>

	inline static double2 operator + (const double2& lhs, const double2& rhs) { return double2(lhs.x + rhs.x, lhs.y + rhs.y); }

	/// <summary>Returns the result of a componentwise addition operation on a double2 vector and a double value.</summary>

	inline static double2 operator + (const double2& lhs, double rhs) { return double2(lhs.x + rhs, lhs.y + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double2 vector.</summary>

	inline static double2 operator + (double lhs, const double2& rhs) { return double2(lhs + rhs.x, lhs + rhs.y); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double2 vectors.</summary>

	inline static double2 operator - (const double2& lhs, const double2& rhs) { return double2(lhs.x - rhs.x, lhs.y - rhs.y); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double2 vector and a double value.</summary>

	inline static double2 operator - (const double2& lhs, double rhs) { return double2(lhs.x - rhs, lhs.y - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double2 vector.</summary>

	inline static double2 operator - (double lhs, const double2& rhs) { return double2(lhs - rhs.x, lhs - rhs.y); }


	/// <summary>Returns the result of a componentwise division operation on two double2 vectors.</summary>

	inline static double2 operator / (const double2& lhs, const double2& rhs) { return double2(lhs.x / rhs.x, lhs.y / rhs.y); }

	/// <summary>Returns the result of a componentwise division operation on a double2 vector and a double value.</summary>

	inline static double2 operator / (const double2& lhs, double rhs) { return double2(lhs.x / rhs, lhs.y / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double2 vector.</summary>

	inline static double2 operator / (double lhs, const double2& rhs) { return double2(lhs / rhs.x, lhs / rhs.y); }

	/// <summary>Returns the result of a componentwise increment operation on a double2 vector.</summary>

	inline static double2 operator ++ (double2 val) { return double2(++val.x, ++val.y); }


	/// <summary>Returns the result of a componentwise decrement operation on a double2 vector.</summary>

	inline static double2 operator -- (double2 val) { return double2(--val.x, --val.y); }


	/// <summary>Returns the result of a componentwise less than operation on two double2 vectors.</summary>

	inline static bool2 operator < (const double2& lhs, const double2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

	/// <summary>Returns the result of a componentwise less than operation on a double2 vector and a double value.</summary>

	inline static bool2 operator < (const double2& lhs, double rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double2 vector.</summary>

	inline static bool2 operator < (double lhs, const double2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double2 vectors.</summary>

	inline static bool2 operator <= (const double2& lhs, const double2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double2 vector and a double value.</summary>

	inline static bool2 operator <= (const double2& lhs, double rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double2 vector.</summary>

	inline static bool2 operator <= (double lhs, const double2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


	/// <summary>Returns the result of a componentwise greater than operation on two double2 vectors.</summary>

	inline static bool2 operator > (const double2& lhs, const double2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

	/// <summary>Returns the result of a componentwise greater than operation on a double2 vector and a double value.</summary>

	inline static bool2 operator > (const double2& lhs, double rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double2 vector.</summary>

	inline static bool2 operator > (double lhs, const double2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double2 vectors.</summary>

	inline static bool2 operator >= (const double2& lhs, const double2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double2 vector and a double value.</summary>

	inline static bool2 operator >= (const double2& lhs, double rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double2 vector.</summary>

	inline static bool2 operator >= (double lhs, const double2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double2 vector.</summary>

	inline static double2 operator - (double2 val) { return double2(-val.x, -val.y); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double2 vector.</summary>

	inline static double2 operator + (double2 val) { return double2(+val.x, +val.y); }


	/// <summary>Returns the result of a componentwise equality operation on two double2 vectors.</summary>

	inline static bool2 operator == (const double2& lhs, const double2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on a double2 vector and a double value.</summary>

	inline static bool2 operator == (const double2& lhs, double rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double2 vector.</summary>

	inline static bool2 operator == (double lhs, const double2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


	/// <summary>Returns the result of a componentwise not equal operation on two double2 vectors.</summary>

	inline static bool2 operator != (const double2& lhs, const double2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

	/// <summary>Returns the result of a componentwise not equal operation on a double2 vector and a double value.</summary>

	inline static bool2 operator != (const double2& lhs, double rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double2 vector.</summary>

	inline static bool2 operator != (double lhs, const double2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region double2x2
	struct double2x2
	{
		double2 c0, c1;
		double2x2() : c0(), c1() {}
		double2x2(double m00, double m01,
			double m10, double m11) :c0(double2(m00, m10)), c1(double2(m01, m11)) {}
		double2x2(double2 c0, double2 c1) : c0(c0), c1(c1) {}
		double2x2(double v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double2x2 matrices.</summary>

	inline static double2x2 operator * (const double2x2& lhs, const double2x2& rhs) { return double2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double2x2 matrix and a double value.</summary>

	inline static double2x2 operator * (const double2x2& lhs, double rhs) { return double2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double2x2 matrix.</summary>

	inline static double2x2 operator * (double lhs, const double2x2& rhs) { return double2x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two double2x2 matrices.</summary>

	inline static double2x2 operator + (const double2x2& lhs, const double2x2& rhs) { return double2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a double2x2 matrix and a double value.</summary>

	inline static double2x2 operator + (const double2x2& lhs, double rhs) { return double2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double2x2 matrix.</summary>

	inline static double2x2 operator + (double lhs, const double2x2& rhs) { return double2x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double2x2 matrices.</summary>

	inline static double2x2 operator - (const double2x2& lhs, const double2x2& rhs) { return double2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double2x2 matrix and a double value.</summary>

	inline static double2x2 operator - (const double2x2& lhs, double rhs) { return double2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double2x2 matrix.</summary>

	inline static double2x2 operator - (double lhs, const double2x2& rhs) { return double2x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two double2x2 matrices.</summary>

	inline static double2x2 operator / (const double2x2& lhs, const double2x2& rhs) { return double2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a double2x2 matrix and a double value.</summary>

	inline static double2x2 operator / (const double2x2& lhs, double rhs) { return double2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double2x2 matrix.</summary>

	inline static double2x2 operator / (double lhs, const double2x2& rhs) { return double2x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a double2x2 matrix.</summary>

	inline static double2x2 operator ++ (double2x2 val) { return double2x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a double2x2 matrix.</summary>

	inline static double2x2 operator -- (double2x2 val) { return double2x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two double2x2 matrices.</summary>

	inline static bool2x2 operator < (const double2x2& lhs, const double2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a double2x2 matrix and a double value.</summary>

	inline static bool2x2 operator < (const double2x2& lhs, double rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double2x2 matrix.</summary>

	inline static bool2x2 operator < (double lhs, const double2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double2x2 matrices.</summary>

	inline static bool2x2 operator <= (const double2x2& lhs, const double2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double2x2 matrix and a double value.</summary>

	inline static bool2x2 operator <= (const double2x2& lhs, double rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double2x2 matrix.</summary>

	inline static bool2x2 operator <= (double lhs, const double2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two double2x2 matrices.</summary>

	inline static bool2x2 operator > (const double2x2& lhs, const double2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a double2x2 matrix and a double value.</summary>

	inline static bool2x2 operator > (const double2x2& lhs, double rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double2x2 matrix.</summary>

	inline static bool2x2 operator > (double lhs, const double2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double2x2 matrices.</summary>

	inline static bool2x2 operator >= (const double2x2& lhs, const double2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double2x2 matrix and a double value.</summary>

	inline static bool2x2 operator >= (const double2x2& lhs, double rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double2x2 matrix.</summary>

	inline static bool2x2 operator >= (double lhs, const double2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double2x2 matrix.</summary>

	inline static double2x2 operator - (double2x2 val) { return double2x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double2x2 matrix.</summary>

	inline static double2x2 operator + (double2x2 val) { return double2x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two double2x2 matrices.</summary>

	inline static bool2x2 operator == (const double2x2& lhs, const double2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a double2x2 matrix and a double value.</summary>

	inline static bool2x2 operator == (const double2x2& lhs, double rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double2x2 matrix.</summary>

	inline static bool2x2 operator == (double lhs, const double2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two double2x2 matrices.</summary>

	inline static bool2x2 operator != (const double2x2& lhs, const double2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a double2x2 matrix and a double value.</summary>

	inline static bool2x2 operator != (const double2x2& lhs, double rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double2x2 matrix.</summary>

	inline static bool2x2 operator != (double lhs, const double2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region double2x3
	struct double2x3
	{
		double2 c0, c1, c2;
		double2x3() : c0(), c1(), c2() {}
		double2x3(double m00, double m01, double m02,
			double m10, double m11, double m12)
		{
			c0 = double2(m00, m10);
			c1 = double2(m01, m11);
			c2 = double2(m02, m12);
		}
		double2x3(double2 c0, double2 c1, double2 c2) : c0(c0), c1(c1), c2(c2) {}
		double2x3(double v) : c0(v), c1(v), c2(v) {}
	};

	/// <summary>Returns the result of a componentwise multiplication operation on two double2x3 matrices.</summary>

	inline static double2x3 operator * (const double2x3& lhs, const double2x3& rhs) { return double2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double2x3 matrix and a double value.</summary>

	inline static double2x3 operator * (const double2x3& lhs, double rhs) { return double2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double2x3 matrix.</summary>

	inline static double2x3 operator * (double lhs, const double2x3& rhs) { return double2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two double2x3 matrices.</summary>

	inline static double2x3 operator + (const double2x3& lhs, const double2x3& rhs) { return double2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a double2x3 matrix and a double value.</summary>

	inline static double2x3 operator + (const double2x3& lhs, double rhs) { return double2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double2x3 matrix.</summary>

	inline static double2x3 operator + (double lhs, const double2x3& rhs) { return double2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double2x3 matrices.</summary>

	inline static double2x3 operator - (const double2x3& lhs, const double2x3& rhs) { return double2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double2x3 matrix and a double value.</summary>

	inline static double2x3 operator - (const double2x3& lhs, double rhs) { return double2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double2x3 matrix.</summary>

	inline static double2x3 operator - (double lhs, const double2x3& rhs) { return double2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two double2x3 matrices.</summary>

	inline static double2x3 operator / (const double2x3& lhs, const double2x3& rhs) { return double2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a double2x3 matrix and a double value.</summary>

	inline static double2x3 operator / (const double2x3& lhs, double rhs) { return double2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double2x3 matrix.</summary>

	inline static double2x3 operator / (double lhs, const double2x3& rhs) { return double2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


	/// <summary>Returns the result of a componentwise increment operation on a double2x3 matrix.</summary>

	inline static double2x3 operator ++ (double2x3 val) { return double2x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a double2x3 matrix.</summary>

	inline static double2x3 operator -- (double2x3 val) { return double2x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two double2x3 matrices.</summary>

	inline static bool2x3 operator < (const double2x3& lhs, const double2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a double2x3 matrix and a double value.</summary>

	inline static bool2x3 operator < (const double2x3& lhs, double rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double2x3 matrix.</summary>

	inline static bool2x3 operator < (double lhs, const double2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double2x3 matrices.</summary>

	inline static bool2x3 operator <= (const double2x3& lhs, const double2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double2x3 matrix and a double value.</summary>

	inline static bool2x3 operator <= (const double2x3& lhs, double rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double2x3 matrix.</summary>

	inline static bool2x3 operator <= (double lhs, const double2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two double2x3 matrices.</summary>

	inline static bool2x3 operator > (const double2x3& lhs, const double2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a double2x3 matrix and a double value.</summary>

	inline static bool2x3 operator > (const double2x3& lhs, double rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double2x3 matrix.</summary>

	inline static bool2x3 operator > (double lhs, const double2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double2x3 matrices.</summary>

	inline static bool2x3 operator >= (const double2x3& lhs, const double2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double2x3 matrix and a double value.</summary>

	inline static bool2x3 operator >= (const double2x3& lhs, double rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double2x3 matrix.</summary>

	inline static bool2x3 operator >= (double lhs, const double2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double2x3 matrix.</summary>

	inline static double2x3 operator - (double2x3 val) { return double2x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double2x3 matrix.</summary>

	inline static double2x3 operator + (double2x3 val) { return double2x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two double2x3 matrices.</summary>

	inline static bool2x3 operator == (const double2x3& lhs, const double2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a double2x3 matrix and a double value.</summary>

	inline static bool2x3 operator == (const double2x3& lhs, double rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double2x3 matrix.</summary>

	inline static bool2x3 operator == (double lhs, const double2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two double2x3 matrices.</summary>

	inline static bool2x3 operator != (const double2x3& lhs, const double2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a double2x3 matrix and a double value.</summary>

	inline static bool2x3 operator != (const double2x3& lhs, double rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double2x3 matrix.</summary>

	inline static bool2x3 operator != (double lhs, const double2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region double2x4
	struct double2x4
	{
		double2 c0, c1, c2, c3;
		double2x4() : c0(), c1(), c2(), c3() {}
		double2x4(double m00, double m01, double m02, double m03,
			double m10, double m11, double m12, double m13)
		{
			c0 = double2(m00, m10);
			c1 = double2(m01, m11);
			c2 = double2(m02, m12);
			c3 = double2(m03, m13);
		}
		double2x4(double2 c0, double2 c1, double2 c2, double2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		double2x4(double v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double2x4 matrices.</summary>

	inline static double2x4 operator * (const double2x4& lhs, const double2x4& rhs) { return double2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double2x4 matrix and a double value.</summary>

	inline static double2x4 operator * (const double2x4& lhs, double rhs) { return double2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double2x4 matrix.</summary>

	inline static double2x4 operator * (double lhs, const double2x4& rhs) { return double2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two double2x4 matrices.</summary>

	inline static double2x4 operator + (const double2x4& lhs, const double2x4& rhs) { return double2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a double2x4 matrix and a double value.</summary>

	inline static double2x4 operator + (const double2x4& lhs, double rhs) { return double2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double2x4 matrix.</summary>

	inline static double2x4 operator + (double lhs, const double2x4& rhs) { return double2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double2x4 matrices.</summary>

	inline static double2x4 operator - (const double2x4& lhs, const double2x4& rhs) { return double2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double2x4 matrix and a double value.</summary>

	inline static double2x4 operator - (const double2x4& lhs, double rhs) { return double2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double2x4 matrix.</summary>

	inline static double2x4 operator - (double lhs, const double2x4& rhs) { return double2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two double2x4 matrices.</summary>

	inline static double2x4 operator / (const double2x4& lhs, const double2x4& rhs) { return double2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a double2x4 matrix and a double value.</summary>

	inline static double2x4 operator / (const double2x4& lhs, double rhs) { return double2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double2x4 matrix.</summary>

	inline static double2x4 operator / (double lhs, const double2x4& rhs) { return double2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a double2x4 matrix.</summary>

	inline static double2x4 operator ++ (double2x4 val) { return double2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a double2x4 matrix.</summary>

	inline static double2x4 operator -- (double2x4 val) { return double2x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two double2x4 matrices.</summary>

	inline static bool2x4 operator < (const double2x4& lhs, const double2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a double2x4 matrix and a double value.</summary>

	inline static bool2x4 operator < (const double2x4& lhs, double rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double2x4 matrix.</summary>

	inline static bool2x4 operator < (double lhs, const double2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double2x4 matrices.</summary>

	inline static bool2x4 operator <= (const double2x4& lhs, const double2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double2x4 matrix and a double value.</summary>

	inline static bool2x4 operator <= (const double2x4& lhs, double rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double2x4 matrix.</summary>

	inline static bool2x4 operator <= (double lhs, const double2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two double2x4 matrices.</summary>

	inline static bool2x4 operator > (const double2x4& lhs, const double2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a double2x4 matrix and a double value.</summary>

	inline static bool2x4 operator > (const double2x4& lhs, double rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double2x4 matrix.</summary>

	inline static bool2x4 operator > (double lhs, const double2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double2x4 matrices.</summary>

	inline static bool2x4 operator >= (const double2x4& lhs, const double2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double2x4 matrix and a double value.</summary>

	inline static bool2x4 operator >= (const double2x4& lhs, double rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double2x4 matrix.</summary>

	inline static bool2x4 operator >= (double lhs, const double2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double2x4 matrix.</summary>

	inline static double2x4 operator - (double2x4 val) { return double2x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double2x4 matrix.</summary>

	inline static double2x4 operator + (double2x4 val) { return double2x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two double2x4 matrices.</summary>

	inline static bool2x4 operator == (const double2x4& lhs, const double2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a double2x4 matrix and a double value.</summary>

	inline static bool2x4 operator == (const double2x4& lhs, double rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double2x4 matrix.</summary>

	inline static bool2x4 operator == (double lhs, const double2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two double2x4 matrices.</summary>

	inline static bool2x4 operator != (const double2x4& lhs, const double2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a double2x4 matrix and a double value.</summary>

	inline static bool2x4 operator != (const double2x4& lhs, double rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double2x4 matrix.</summary>

	inline static bool2x4 operator != (double lhs, const double2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region double3
	struct double3 {
		double x, y, z;
		double3() : x(0), y(0), z(0) {}
		double3(double x, double y, double z) : x(x), y(y), z(z) {}
		double3(double v) : x(v), y(v), z(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double3 vectors.</summary>

	inline static double3 operator * (const double3& lhs, const double3& rhs) { return double3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double3 vector and a double value.</summary>

	inline static double3 operator * (const double3& lhs, double rhs) { return double3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double3 vector.</summary>

	inline static double3 operator * (double lhs, const double3& rhs) { return double3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


	/// <summary>Returns the result of a componentwise addition operation on two double3 vectors.</summary>

	inline static double3 operator + (const double3& lhs, const double3& rhs) { return double3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

	/// <summary>Returns the result of a componentwise addition operation on a double3 vector and a double value.</summary>

	inline static double3 operator + (const double3& lhs, double rhs) { return double3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double3 vector.</summary>

	inline static double3 operator + (double lhs, const double3& rhs) { return double3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double3 vectors.</summary>

	inline static double3 operator - (const double3& lhs, const double3& rhs) { return double3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double3 vector and a double value.</summary>

	inline static double3 operator - (const double3& lhs, double rhs) { return double3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double3 vector.</summary>

	inline static double3 operator - (double lhs, const double3& rhs) { return double3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


	/// <summary>Returns the result of a componentwise division operation on two double3 vectors.</summary>

	inline static double3 operator / (const double3& lhs, const double3& rhs) { return double3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

	/// <summary>Returns the result of a componentwise division operation on a double3 vector and a double value.</summary>

	inline static double3 operator / (const double3& lhs, double rhs) { return double3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double3 vector.</summary>

	inline static double3 operator / (double lhs, const double3& rhs) { return double3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


	/// <summary>Returns the result of a componentwise increment operation on a double3 vector.</summary>

	inline static double3 operator ++ (double3 val) { return double3(++val.x, ++val.y, ++val.z); }


	/// <summary>Returns the result of a componentwise decrement operation on a double3 vector.</summary>

	inline static double3 operator -- (double3 val) { return double3(--val.x, --val.y, --val.z); }


	/// <summary>Returns the result of a componentwise less than operation on two double3 vectors.</summary>

	inline static bool3 operator < (const double3& lhs, const double3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

	/// <summary>Returns the result of a componentwise less than operation on a double3 vector and a double value.</summary>

	inline static bool3 operator < (const double3& lhs, double rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double3 vector.</summary>

	inline static bool3 operator < (double lhs, const double3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double3 vectors.</summary>

	inline static bool3 operator <= (const double3& lhs, const double3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double3 vector and a double value.</summary>

	inline static bool3 operator <= (const double3& lhs, double rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double3 vector.</summary>

	inline static bool3 operator <= (double lhs, const double3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


	/// <summary>Returns the result of a componentwise greater than operation on two double3 vectors.</summary>

	inline static bool3 operator > (const double3& lhs, const double3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

	/// <summary>Returns the result of a componentwise greater than operation on a double3 vector and a double value.</summary>

	inline static bool3 operator > (const double3& lhs, double rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double3 vector.</summary>

	inline static bool3 operator > (double lhs, const double3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double3 vectors.</summary>

	inline static bool3 operator >= (const double3& lhs, const double3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double3 vector and a double value.</summary>

	inline static bool3 operator >= (const double3& lhs, double rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double3 vector.</summary>

	inline static bool3 operator >= (double lhs, const double3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double3 vector.</summary>

	inline static double3 operator - (double3 val) { return double3(-val.x, -val.y, -val.z); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double3 vector.</summary>

	inline static double3 operator + (double3 val) { return double3(+val.x, +val.y, +val.z); }


	/// <summary>Returns the result of a componentwise equality operation on two double3 vectors.</summary>

	inline static bool3 operator == (const double3& lhs, const double3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

	/// <summary>Returns the result of a componentwise equality operation on a double3 vector and a double value.</summary>

	inline static bool3 operator == (const double3& lhs, double rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double3 vector.</summary>

	inline static bool3 operator == (double lhs, const double3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


	/// <summary>Returns the result of a componentwise not equal operation on two double3 vectors.</summary>

	inline static bool3 operator != (const double3& lhs, const double3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

	/// <summary>Returns the result of a componentwise not equal operation on a double3 vector and a double value.</summary>

	inline static bool3 operator != (const double3& lhs, double rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double3 vector.</summary>

	inline static bool3 operator != (double lhs, const double3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region double3x2
	struct double3x2
	{
		double3 c0, c1;
		double3x2() : c0(), c1() {}
		double3x2(double m00, double m01,
			double m10, double m11,
			double m20, double m21)
		{
			c0 = double3(m00, m10, m20);
			c1 = double3(m01, m11, m21);
		}

		double3x2(double3 c0, double3 c1) : c0(c0), c1(c1) {}
		double3x2(double v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double3x2 matrices.</summary>

	inline static double3x2 operator * (const double3x2& lhs, const double3x2& rhs) { return double3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double3x2 matrix and a double value.</summary>

	inline static double3x2 operator * (const double3x2& lhs, double rhs) { return double3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double3x2 matrix.</summary>

	inline static double3x2 operator * (double lhs, const double3x2& rhs) { return double3x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two double3x2 matrices.</summary>

	inline static double3x2 operator + (const double3x2& lhs, const double3x2& rhs) { return double3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a double3x2 matrix and a double value.</summary>

	inline static double3x2 operator + (const double3x2& lhs, double rhs) { return double3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double3x2 matrix.</summary>

	inline static double3x2 operator + (double lhs, const double3x2& rhs) { return double3x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double3x2 matrices.</summary>

	inline static double3x2 operator - (const double3x2& lhs, const double3x2& rhs) { return double3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double3x2 matrix and a double value.</summary>

	inline static double3x2 operator - (const double3x2& lhs, double rhs) { return double3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double3x2 matrix.</summary>

	inline static double3x2 operator - (double lhs, const double3x2& rhs) { return double3x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two double3x2 matrices.</summary>

	inline static double3x2 operator / (const double3x2& lhs, const double3x2& rhs) { return double3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a double3x2 matrix and a double value.</summary>

	inline static double3x2 operator / (const double3x2& lhs, double rhs) { return double3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double3x2 matrix.</summary>

	inline static double3x2 operator / (double lhs, const double3x2& rhs) { return double3x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a double3x2 matrix.</summary>

	inline static double3x2 operator ++ (double3x2 val) { return double3x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a double3x2 matrix.</summary>

	inline static double3x2 operator -- (double3x2 val) { return double3x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two double3x2 matrices.</summary>

	inline static bool3x2 operator < (const double3x2& lhs, const double3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a double3x2 matrix and a double value.</summary>

	inline static bool3x2 operator < (const double3x2& lhs, double rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double3x2 matrix.</summary>

	inline static bool3x2 operator < (double lhs, const double3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double3x2 matrices.</summary>

	inline static bool3x2 operator <= (const double3x2& lhs, const double3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double3x2 matrix and a double value.</summary>

	inline static bool3x2 operator <= (const double3x2& lhs, double rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double3x2 matrix.</summary>

	inline static bool3x2 operator <= (double lhs, const double3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two double3x2 matrices.</summary>

	inline static bool3x2 operator > (const double3x2& lhs, const double3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a double3x2 matrix and a double value.</summary>

	inline static bool3x2 operator > (const double3x2& lhs, double rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double3x2 matrix.</summary>

	inline static bool3x2 operator > (double lhs, const double3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double3x2 matrices.</summary>

	inline static bool3x2 operator >= (const double3x2& lhs, const double3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double3x2 matrix and a double value.</summary>

	inline static bool3x2 operator >= (const double3x2& lhs, double rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double3x2 matrix.</summary>

	inline static bool3x2 operator >= (double lhs, const double3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double3x2 matrix.</summary>

	inline static double3x2 operator - (double3x2 val) { return double3x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double3x2 matrix.</summary>

	inline static double3x2 operator + (double3x2 val) { return double3x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two double3x2 matrices.</summary>

	inline static bool3x2 operator == (const double3x2& lhs, const double3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a double3x2 matrix and a double value.</summary>

	inline static bool3x2 operator == (const double3x2& lhs, double rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double3x2 matrix.</summary>

	inline static bool3x2 operator == (double lhs, const double3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two double3x2 matrices.</summary>

	inline static bool3x2 operator != (const double3x2& lhs, const double3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a double3x2 matrix and a double value.</summary>

	inline static bool3x2 operator != (const double3x2& lhs, double rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double3x2 matrix.</summary>

	inline static bool3x2 operator != (double lhs, const double3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region double3x3
	struct double3x3
	{
		double3 c0, c1, c2;
		double3x3() : c0(), c1(), c2() {}
		double3x3(double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22)
		{
			c0 = double3(m00, m10, m20);
			c1 = double3(m01, m11, m21);
			c2 = double3(m02, m12, m22);
		}
		double3x3(double3 c0, double3 c1, double3 c2) : c0(c0), c1(c1), c2(c2) {}
		double3x3(double v) : c0(v), c1(v), c2(v) {}

	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double3x3 matrices.</summary>

	inline static double3x3 operator * (const double3x3& lhs, const double3x3& rhs) { return double3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double3x3 matrix and a double value.</summary>

	inline static double3x3 operator * (const double3x3& lhs, double rhs) { return double3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double3x3 matrix.</summary>

	inline static double3x3 operator * (double lhs, const double3x3& rhs) { return double3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two double3x3 matrices.</summary>

	inline static double3x3 operator + (const double3x3& lhs, const double3x3& rhs) { return double3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a double3x3 matrix and a double value.</summary>

	inline static double3x3 operator + (const double3x3& lhs, double rhs) { return double3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double3x3 matrix.</summary>

	inline static double3x3 operator + (double lhs, const double3x3& rhs) { return double3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double3x3 matrices.</summary>

	inline static double3x3 operator - (const double3x3& lhs, const double3x3& rhs) { return double3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double3x3 matrix and a double value.</summary>

	inline static double3x3 operator - (const double3x3& lhs, double rhs) { return double3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double3x3 matrix.</summary>

	inline static double3x3 operator - (double lhs, const double3x3& rhs) { return double3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two double3x3 matrices.</summary>

	inline static double3x3 operator / (const double3x3& lhs, const double3x3& rhs) { return double3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a double3x3 matrix and a double value.</summary>

	inline static double3x3 operator / (const double3x3& lhs, double rhs) { return double3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double3x3 matrix.</summary>

	inline static double3x3 operator / (double lhs, const double3x3& rhs) { return double3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a double3x3 matrix.</summary>

	inline static double3x3 operator ++ (double3x3 val) { return double3x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a double3x3 matrix.</summary>

	inline static double3x3 operator -- (double3x3 val) { return double3x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two double3x3 matrices.</summary>

	inline static bool3x3 operator < (const double3x3& lhs, const double3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a double3x3 matrix and a double value.</summary>

	inline static bool3x3 operator < (const double3x3& lhs, double rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double3x3 matrix.</summary>

	inline static bool3x3 operator < (double lhs, const double3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double3x3 matrices.</summary>

	inline static bool3x3 operator <= (const double3x3& lhs, const double3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double3x3 matrix and a double value.</summary>

	inline static bool3x3 operator <= (const double3x3& lhs, double rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double3x3 matrix.</summary>

	inline static bool3x3 operator <= (double lhs, const double3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two double3x3 matrices.</summary>

	inline static bool3x3 operator > (const double3x3& lhs, const double3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a double3x3 matrix and a double value.</summary>

	inline static bool3x3 operator > (const double3x3& lhs, double rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double3x3 matrix.</summary>

	inline static bool3x3 operator > (double lhs, const double3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double3x3 matrices.</summary>

	inline static bool3x3 operator >= (const double3x3& lhs, const double3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double3x3 matrix and a double value.</summary>

	inline static bool3x3 operator >= (const double3x3& lhs, double rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double3x3 matrix.</summary>

	inline static bool3x3 operator >= (double lhs, const double3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double3x3 matrix.</summary>

	inline static double3x3 operator - (double3x3 val) { return double3x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double3x3 matrix.</summary>

	inline static double3x3 operator + (double3x3 val) { return double3x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two double3x3 matrices.</summary>

	inline static bool3x3 operator == (const double3x3& lhs, const double3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a double3x3 matrix and a double value.</summary>

	inline static bool3x3 operator == (const double3x3& lhs, double rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double3x3 matrix.</summary>

	inline static bool3x3 operator == (double lhs, const double3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two double3x3 matrices.</summary>

	inline static bool3x3 operator != (const double3x3& lhs, const double3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a double3x3 matrix and a double value.</summary>

	inline static bool3x3 operator != (const double3x3& lhs, double rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double3x3 matrix.</summary>

	inline static bool3x3 operator != (double lhs, const double3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region double3x4
	struct double3x4
	{
		double3 c0, c1, c2, c3;
		double3x4() : c0(), c1(), c2(), c3() {}
		double3x4(double m00, double m01, double m02, double m03,
			double m10, double m11, double m12, double m13,
			double m20, double m21, double m22, double m23)
		{
			c0 = double3(m00, m10, m20);
			c1 = double3(m01, m11, m21);
			c2 = double3(m02, m12, m22);
			c3 = double3(m03, m13, m23);
		}
		double3x4(double3 c0, double3 c1, double3 c2, double3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		double3x4(double v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double3x4 matrices.</summary>

	inline static double3x4 operator * (const double3x4& lhs, const double3x4& rhs) { return double3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double3x4 matrix and a double value.</summary>

	inline static double3x4 operator * (const double3x4& lhs, double rhs) { return double3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double3x4 matrix.</summary>

	inline static double3x4 operator * (double lhs, const double3x4& rhs) { return double3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two double3x4 matrices.</summary>

	inline static double3x4 operator + (const double3x4& lhs, const double3x4& rhs) { return double3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a double3x4 matrix and a double value.</summary>

	inline static double3x4 operator + (const double3x4& lhs, double rhs) { return double3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double3x4 matrix.</summary>

	inline static double3x4 operator + (double lhs, const double3x4& rhs) { return double3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double3x4 matrices.</summary>

	inline static double3x4 operator - (const double3x4& lhs, const double3x4& rhs) { return double3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double3x4 matrix and a double value.</summary>

	inline static double3x4 operator - (const double3x4& lhs, double rhs) { return double3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double3x4 matrix.</summary>

	inline static double3x4 operator - (double lhs, const double3x4& rhs) { return double3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two double3x4 matrices.</summary>

	inline static double3x4 operator / (const double3x4& lhs, const double3x4& rhs) { return double3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a double3x4 matrix and a double value.</summary>

	inline static double3x4 operator / (const double3x4& lhs, double rhs) { return double3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double3x4 matrix.</summary>

	inline static double3x4 operator / (double lhs, const double3x4& rhs) { return double3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

	/// <summary>Returns the result of a componentwise increment operation on a double3x4 matrix.</summary>

	inline static double3x4 operator ++ (double3x4 val) { return double3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a double3x4 matrix.</summary>

	inline static double3x4 operator -- (double3x4 val) { return double3x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two double3x4 matrices.</summary>

	inline static bool3x4 operator < (const double3x4& lhs, const double3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a double3x4 matrix and a double value.</summary>

	inline static bool3x4 operator < (const double3x4& lhs, double rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double3x4 matrix.</summary>

	inline static bool3x4 operator < (double lhs, const double3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double3x4 matrices.</summary>

	inline static bool3x4 operator <= (const double3x4& lhs, const double3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double3x4 matrix and a double value.</summary>

	inline static bool3x4 operator <= (const double3x4& lhs, double rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double3x4 matrix.</summary>

	inline static bool3x4 operator <= (double lhs, const double3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two double3x4 matrices.</summary>

	inline static bool3x4 operator > (const double3x4& lhs, const double3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a double3x4 matrix and a double value.</summary>

	inline static bool3x4 operator > (const double3x4& lhs, double rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double3x4 matrix.</summary>

	inline static bool3x4 operator > (double lhs, const double3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double3x4 matrices.</summary>

	inline static bool3x4 operator >= (const double3x4& lhs, const double3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double3x4 matrix and a double value.</summary>

	inline static bool3x4 operator >= (const double3x4& lhs, double rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double3x4 matrix.</summary>

	inline static bool3x4 operator >= (double lhs, const double3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double3x4 matrix.</summary>

	inline static double3x4 operator - (double3x4 val) { return double3x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double3x4 matrix.</summary>

	inline static double3x4 operator + (double3x4 val) { return double3x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two double3x4 matrices.</summary>

	inline static bool3x4 operator == (const double3x4& lhs, const double3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a double3x4 matrix and a double value.</summary>

	inline static bool3x4 operator == (const double3x4& lhs, double rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double3x4 matrix.</summary>

	inline static bool3x4 operator == (double lhs, const double3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two double3x4 matrices.</summary>

	inline static bool3x4 operator != (const double3x4& lhs, const double3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a double3x4 matrix and a double value.</summary>

	inline static bool3x4 operator != (const double3x4& lhs, double rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double3x4 matrix.</summary>

	inline static bool3x4 operator != (double lhs, const double3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region double4
	struct double4 {
		double x, y, z, w;
		double4() : x(0), y(0), z(0), w(0) {}
		double4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
		double4(double v) : x(v), y(v), z(v), w(v) {}
		double4(double3 xyz, double w) : w(w)
		{
			x = xyz.x;
			y = xyz.y;
			z = xyz.z;
		}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double4 vectors.</summary>

	inline static double4 operator * (const double4& lhs, const double4& rhs) { return double4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double4 vector and a double value.</summary>

	inline static double4 operator * (const double4& lhs, double rhs) { return double4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double4 vector.</summary>

	inline static double4 operator * (double lhs, const double4& rhs) { return double4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


	/// <summary>Returns the result of a componentwise addition operation on two double4 vectors.</summary>

	inline static double4 operator + (const double4& lhs, const double4& rhs) { return double4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

	/// <summary>Returns the result of a componentwise addition operation on a double4 vector and a double value.</summary>

	inline static double4 operator + (const double4& lhs, double rhs) { return double4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double4 vector.</summary>

	inline static double4 operator + (double lhs, const double4& rhs) { return double4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double4 vectors.</summary>

	inline static double4 operator - (const double4& lhs, const double4& rhs) { return double4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double4 vector and a double value.</summary>

	inline static double4 operator - (const double4& lhs, double rhs) { return double4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double4 vector.</summary>

	inline static double4 operator - (double lhs, const double4& rhs) { return double4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


	/// <summary>Returns the result of a componentwise division operation on two double4 vectors.</summary>

	inline static double4 operator / (const double4& lhs, const double4& rhs) { return double4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

	/// <summary>Returns the result of a componentwise division operation on a double4 vector and a double value.</summary>

	inline static double4 operator / (const double4& lhs, double rhs) { return double4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double4 vector.</summary>

	inline static double4 operator / (double lhs, const double4& rhs) { return double4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

	/// <summary>Returns the result of a componentwise increment operation on a double4 vector.</summary>

	inline static double4 operator ++ (double4 val) { return double4(++val.x, ++val.y, ++val.z, ++val.w); }


	/// <summary>Returns the result of a componentwise decrement operation on a double4 vector.</summary>

	inline static double4 operator -- (double4 val) { return double4(--val.x, --val.y, --val.z, --val.w); }


	/// <summary>Returns the result of a componentwise less than operation on two double4 vectors.</summary>

	inline static bool4 operator < (const double4& lhs, const double4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

	/// <summary>Returns the result of a componentwise less than operation on a double4 vector and a double value.</summary>

	inline static bool4 operator < (const double4& lhs, double rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double4 vector.</summary>

	inline static bool4 operator < (double lhs, const double4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double4 vectors.</summary>

	inline static bool4 operator <= (const double4& lhs, const double4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double4 vector and a double value.</summary>

	inline static bool4 operator <= (const double4& lhs, double rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double4 vector.</summary>

	inline static bool4 operator <= (double lhs, const double4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


	/// <summary>Returns the result of a componentwise greater than operation on two double4 vectors.</summary>

	inline static bool4 operator > (const double4& lhs, const double4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

	/// <summary>Returns the result of a componentwise greater than operation on a double4 vector and a double value.</summary>

	inline static bool4 operator > (const double4& lhs, double rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double4 vector.</summary>

	inline static bool4 operator > (double lhs, const double4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double4 vectors.</summary>

	inline static bool4 operator >= (const double4& lhs, const double4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double4 vector and a double value.</summary>

	inline static bool4 operator >= (const double4& lhs, double rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double4 vector.</summary>

	inline static bool4 operator >= (double lhs, const double4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double4 vector.</summary>

	inline static double4 operator - (double4 val) { return double4(-val.x, -val.y, -val.z, -val.w); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double4 vector.</summary>

	inline static double4 operator + (double4 val) { return double4(+val.x, +val.y, +val.z, +val.w); }


	/// <summary>Returns the result of a componentwise equality operation on two double4 vectors.</summary>

	inline static bool4 operator == (const double4& lhs, const double4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on a double4 vector and a double value.</summary>

	inline static bool4 operator == (const double4& lhs, double rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double4 vector.</summary>

	inline static bool4 operator == (double lhs, const double4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


	/// <summary>Returns the result of a componentwise not equal operation on two double4 vectors.</summary>

	inline static bool4 operator != (const double4& lhs, const double4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

	/// <summary>Returns the result of a componentwise not equal operation on a double4 vector and a double value.</summary>

	inline static bool4 operator != (const double4& lhs, double rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double4 vector.</summary>

	inline static bool4 operator != (double lhs, const double4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region double4x2
	struct double4x2
	{
		double4 c0, c1;
		double4x2() : c0(), c1() {}
		double4x2(double m00, double m01,
			double m10, double m11,
			double m20, double m21,
			double m30, double m31)
		{
			c0 = double4(m00, m10, m20, m30);
			c1 = double4(m01, m11, m21, m31);
		}
		double4x2(double4 c0, double4 c1) : c0(c0), c1(c1) {}
		double4x2(double v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double4x2 matrices.</summary>

	inline static double4x2 operator * (const double4x2& lhs, const double4x2& rhs) { return double4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double4x2 matrix and a double value.</summary>

	inline static double4x2 operator * (const double4x2& lhs, double rhs) { return double4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double4x2 matrix.</summary>

	inline static double4x2 operator * (double lhs, const double4x2& rhs) { return double4x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two double4x2 matrices.</summary>

	inline static double4x2 operator + (const double4x2& lhs, const double4x2& rhs) { return double4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a double4x2 matrix and a double value.</summary>

	inline static double4x2 operator + (const double4x2& lhs, double rhs) { return double4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double4x2 matrix.</summary>

	inline static double4x2 operator + (double lhs, const double4x2& rhs) { return double4x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double4x2 matrices.</summary>

	inline static double4x2 operator - (const double4x2& lhs, const double4x2& rhs) { return double4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double4x2 matrix and a double value.</summary>

	inline static double4x2 operator - (const double4x2& lhs, double rhs) { return double4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double4x2 matrix.</summary>

	inline static double4x2 operator - (double lhs, const double4x2& rhs) { return double4x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two double4x2 matrices.</summary>

	inline static double4x2 operator / (const double4x2& lhs, const double4x2& rhs) { return double4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a double4x2 matrix and a double value.</summary>

	inline static double4x2 operator / (const double4x2& lhs, double rhs) { return double4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double4x2 matrix.</summary>

	inline static double4x2 operator / (double lhs, const double4x2& rhs) { return double4x2(lhs / rhs.c0, lhs / rhs.c1); }

	/// <summary>Returns the result of a componentwise increment operation on a double4x2 matrix.</summary>

	inline static double4x2 operator ++ (double4x2 val) { return double4x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a double4x2 matrix.</summary>

	inline static double4x2 operator -- (double4x2 val) { return double4x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two double4x2 matrices.</summary>

	inline static bool4x2 operator < (const double4x2& lhs, const double4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a double4x2 matrix and a double value.</summary>

	inline static bool4x2 operator < (const double4x2& lhs, double rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double4x2 matrix.</summary>

	inline static bool4x2 operator < (double lhs, const double4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double4x2 matrices.</summary>

	inline static bool4x2 operator <= (const double4x2& lhs, const double4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double4x2 matrix and a double value.</summary>

	inline static bool4x2 operator <= (const double4x2& lhs, double rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double4x2 matrix.</summary>

	inline static bool4x2 operator <= (double lhs, const double4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two double4x2 matrices.</summary>

	inline static bool4x2 operator > (const double4x2& lhs, const double4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a double4x2 matrix and a double value.</summary>

	inline static bool4x2 operator > (const double4x2& lhs, double rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double4x2 matrix.</summary>

	inline static bool4x2 operator > (double lhs, const double4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double4x2 matrices.</summary>

	inline static bool4x2 operator >= (const double4x2& lhs, const double4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double4x2 matrix and a double value.</summary>

	inline static bool4x2 operator >= (const double4x2& lhs, double rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double4x2 matrix.</summary>

	inline static bool4x2 operator >= (double lhs, const double4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double4x2 matrix.</summary>

	inline static double4x2 operator - (double4x2 val) { return double4x2(-val.c0, -val.c1); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double4x2 matrix.</summary>

	inline static double4x2 operator + (double4x2 val) { return double4x2(+val.c0, +val.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two double4x2 matrices.</summary>

	inline static bool4x2 operator == (const double4x2& lhs, const double4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a double4x2 matrix and a double value.</summary>

	inline static bool4x2 operator == (const double4x2& lhs, double rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double4x2 matrix.</summary>

	inline static bool4x2 operator == (double lhs, const double4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two double4x2 matrices.</summary>

	inline static bool4x2 operator != (const double4x2& lhs, const double4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a double4x2 matrix and a double value.</summary>

	inline static bool4x2 operator != (const double4x2& lhs, double rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double4x2 matrix.</summary>

	inline static bool4x2 operator != (double lhs, const double4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region double4x3
	struct double4x3
	{
		double4 c0, c1, c2;
		double4x3() : c0(), c1(), c2() {}
		double4x3(double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22,
			double m30, double m31, double m32)
		{
			c0 = double4(m00, m10, m20, m30);
			c1 = double4(m01, m11, m21, m31);
			c2 = double4(m02, m12, m22, m32);
		}
		double4x3(double4 c0, double4 c1, double4 c2) : c0(c0), c1(c1), c2(c2) {}
		double4x3(double v) : c0(v), c1(v), c2(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double4x3 matrices.</summary>

	inline static double4x3 operator * (const double4x3& lhs, const double4x3& rhs) { return double4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double4x3 matrix and a double value.</summary>

	inline static double4x3 operator * (const double4x3& lhs, double rhs) { return double4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double4x3 matrix.</summary>

	inline static double4x3 operator * (double lhs, const double4x3& rhs) { return double4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two double4x3 matrices.</summary>

	inline static double4x3 operator + (const double4x3& lhs, const double4x3& rhs) { return double4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a double4x3 matrix and a double value.</summary>

	inline static double4x3 operator + (const double4x3& lhs, double rhs) { return double4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double4x3 matrix.</summary>

	inline static double4x3 operator + (double lhs, const double4x3& rhs) { return double4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double4x3 matrices.</summary>

	inline static double4x3 operator - (const double4x3& lhs, const double4x3& rhs) { return double4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double4x3 matrix and a double value.</summary>

	inline static double4x3 operator - (const double4x3& lhs, double rhs) { return double4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double4x3 matrix.</summary>

	inline static double4x3 operator - (double lhs, const double4x3& rhs) { return double4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two double4x3 matrices.</summary>

	inline static double4x3 operator / (const double4x3& lhs, const double4x3& rhs) { return double4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a double4x3 matrix and a double value.</summary>

	inline static double4x3 operator / (const double4x3& lhs, double rhs) { return double4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double4x3 matrix.</summary>

	inline static double4x3 operator / (double lhs, const double4x3& rhs) { return double4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a double4x3 matrix.</summary>

	inline static double4x3 operator ++ (double4x3 val) { return double4x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a double4x3 matrix.</summary>

	inline static double4x3 operator -- (double4x3 val) { return double4x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two double4x3 matrices.</summary>

	inline static bool4x3 operator < (const double4x3& lhs, const double4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a double4x3 matrix and a double value.</summary>

	inline static bool4x3 operator < (const double4x3& lhs, double rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double4x3 matrix.</summary>

	inline static bool4x3 operator < (double lhs, const double4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double4x3 matrices.</summary>

	inline static bool4x3 operator <= (const double4x3& lhs, const double4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double4x3 matrix and a double value.</summary>

	inline static bool4x3 operator <= (const double4x3& lhs, double rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double4x3 matrix.</summary>

	inline static bool4x3 operator <= (double lhs, const double4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two double4x3 matrices.</summary>

	inline static bool4x3 operator > (const double4x3& lhs, const double4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a double4x3 matrix and a double value.</summary>

	inline static bool4x3 operator > (const double4x3& lhs, double rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double4x3 matrix.</summary>

	inline static bool4x3 operator > (double lhs, const double4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double4x3 matrices.</summary>

	inline static bool4x3 operator >= (const double4x3& lhs, const double4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double4x3 matrix and a double value.</summary>

	inline static bool4x3 operator >= (const double4x3& lhs, double rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double4x3 matrix.</summary>

	inline static bool4x3 operator >= (double lhs, const double4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double4x3 matrix.</summary>

	inline static double4x3 operator - (double4x3 val) { return double4x3(-val.c0, -val.c1, -val.c2); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double4x3 matrix.</summary>

	inline static double4x3 operator + (double4x3 val) { return double4x3(+val.c0, +val.c1, +val.c2); }


	/// <summary>Returns the result of a componentwise equality operation on two double4x3 matrices.</summary>

	inline static bool4x3 operator == (const double4x3& lhs, const double4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a double4x3 matrix and a double value.</summary>

	inline static bool4x3 operator == (const double4x3& lhs, double rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double4x3 matrix.</summary>

	inline static bool4x3 operator == (double lhs, const double4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two double4x3 matrices.</summary>

	inline static bool4x3 operator != (const double4x3& lhs, const double4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a double4x3 matrix and a double value.</summary>

	inline static bool4x3 operator != (const double4x3& lhs, double rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double4x3 matrix.</summary>

	inline static bool4x3 operator != (double lhs, const double4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region double4x4
	struct double4x4
	{
		double4 c0, c1, c2, c3;
		double4x4() : c0(), c1(), c2(), c3() {}
		double4x4(double m00, double m01, double m02, double m03,
			double m10, double m11, double m12, double m13,
			double m20, double m21, double m22, double m23,
			double m30, double m31, double m32, double m33)
		{
			c0 = double4(m00, m10, m20, m30);
			c1 = double4(m01, m11, m21, m31);
			c2 = double4(m02, m12, m22, m32);
			c3 = double4(m03, m13, m23, m33);
		}
		double4x4(double4 c0, double4 c1, double4 c2, double4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		double4x4(double v) : c0(v), c1(v), c2(v), c3(v) {}

		double4x4(double3x3 rotation, double3 translation)
		{
			c0 = double4(rotation.c0, 0.0f);
			c1 = double4(rotation.c1, 0.0f);
			c2 = double4(rotation.c2, 0.0f);
			c3 = double4(translation, 1.0f);
		}


	};


	/// <summary>Returns the result of a componentwise multiplication operation on two double4x4 matrices.</summary>

	inline static double4x4 operator * (const double4x4& lhs, const double4x4& rhs) { return double4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double4x4 matrix and a double value.</summary>

	inline static double4x4 operator * (const double4x4& lhs, double rhs) { return double4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a double value and a double4x4 matrix.</summary>

	inline static double4x4 operator * (double lhs, const double4x4& rhs) { return double4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two double4x4 matrices.</summary>

	inline static double4x4 operator + (const double4x4& lhs, const double4x4& rhs) { return double4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a double4x4 matrix and a double value.</summary>

	inline static double4x4 operator + (const double4x4& lhs, double rhs) { return double4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a double value and a double4x4 matrix.</summary>

	inline static double4x4 operator + (double lhs, const double4x4& rhs) { return double4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two double4x4 matrices.</summary>

	inline static double4x4 operator - (const double4x4& lhs, const double4x4& rhs) { return double4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double4x4 matrix and a double value.</summary>

	inline static double4x4 operator - (const double4x4& lhs, double rhs) { return double4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a double value and a double4x4 matrix.</summary>

	inline static double4x4 operator - (double lhs, const double4x4& rhs) { return double4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two double4x4 matrices.</summary>

	inline static double4x4 operator / (const double4x4& lhs, const double4x4& rhs) { return double4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a double4x4 matrix and a double value.</summary>

	inline static double4x4 operator / (const double4x4& lhs, double rhs) { return double4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a double value and a double4x4 matrix.</summary>

	inline static double4x4 operator / (double lhs, const double4x4& rhs) { return double4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a double4x4 matrix.</summary>

	inline static double4x4 operator ++ (double4x4 val) { return double4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a double4x4 matrix.</summary>

	inline static double4x4 operator -- (double4x4 val) { return double4x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two double4x4 matrices.</summary>

	inline static bool4x4 operator < (const double4x4& lhs, const double4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a double4x4 matrix and a double value.</summary>

	inline static bool4x4 operator < (const double4x4& lhs, double rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a double value and a double4x4 matrix.</summary>

	inline static bool4x4 operator < (double lhs, const double4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two double4x4 matrices.</summary>

	inline static bool4x4 operator <= (const double4x4& lhs, const double4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double4x4 matrix and a double value.</summary>

	inline static bool4x4 operator <= (const double4x4& lhs, double rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a double value and a double4x4 matrix.</summary>

	inline static bool4x4 operator <= (double lhs, const double4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two double4x4 matrices.</summary>

	inline static bool4x4 operator > (const double4x4& lhs, const double4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a double4x4 matrix and a double value.</summary>

	inline static bool4x4 operator > (const double4x4& lhs, double rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a double value and a double4x4 matrix.</summary>

	inline static bool4x4 operator > (double lhs, const double4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two double4x4 matrices.</summary>

	inline static bool4x4 operator >= (const double4x4& lhs, const double4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double4x4 matrix and a double value.</summary>

	inline static bool4x4 operator >= (const double4x4& lhs, double rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a double value and a double4x4 matrix.</summary>

	inline static bool4x4 operator >= (double lhs, const double4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


	/// <summary>Returns the result of a componentwise unary Minus operation on a double4x4 matrix.</summary>

	inline static double4x4 operator - (double4x4 val) { return double4x4(-val.c0, -val.c1, -val.c2, -val.c3); }


	/// <summary>Returns the result of a componentwise unary plus operation on a double4x4 matrix.</summary>

	inline static double4x4 operator + (double4x4 val) { return double4x4(+val.c0, +val.c1, +val.c2, +val.c3); }


	/// <summary>Returns the result of a componentwise equality operation on two double4x4 matrices.</summary>

	inline static bool4x4 operator == (const double4x4& lhs, const double4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a double4x4 matrix and a double value.</summary>

	inline static bool4x4 operator == (const double4x4& lhs, double rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a double value and a double4x4 matrix.</summary>

	inline static bool4x4 operator == (double lhs, const double4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two double4x4 matrices.</summary>

	inline static bool4x4 operator != (const double4x4& lhs, const double4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a double4x4 matrix and a double value.</summary>

	inline static bool4x4 operator != (const double4x4& lhs, double rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a double value and a double4x4 matrix.</summary>

	inline static bool4x4 operator != (double lhs, const double4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic


	/// <summary>Returns the Tangent of a double value.</summary>
	inline static double Tan(double x) { return (double)tan(x); }

	/// <summary>Returns the componentwise Tangent of a double2 vector.</summary>
	inline static double2 Tan(double2 x) { return double2(Tan(x.x), Tan(x.y)); }

	/// <summary>Returns the componentwise Tangent of a double3 vector.</summary>
	inline static double3 Tan(double3 x) { return double3(Tan(x.x), Tan(x.y), Tan(x.z)); }

	/// <summary>Returns the componentwise Tangent of a double4 vector.</summary>
	inline static double4 Tan(double4 x) { return double4(Tan(x.x), Tan(x.y), Tan(x.z), Tan(x.w)); }


	/// <summary>Returns the hyperbolic Tangent of a double value.</summary>
	inline static double Tanh(double x) { return (double)tanh(x); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a double2 vector.</summary>
	inline static double2 Tanh(double2 x) { return double2(Tanh(x.x), Tanh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a double3 vector.</summary>
	inline static double3 Tanh(double3 x) { return double3(Tanh(x.x), Tanh(x.y), Tanh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a double4 vector.</summary>
	inline static double4 Tanh(double4 x) { return double4(Tanh(x.x), Tanh(x.y), Tanh(x.z), Tanh(x.w)); }


	/// <summary>Returns the arcTangent of a double value.</summary>
	inline static double Atan(double x) { return (double)atan(x); }

	/// <summary>Returns the componentwise arcTangent of a double2 vector.</summary>
	inline static double2 Atan(double2 x) { return double2(Atan(x.x), Atan(x.y)); }

	/// <summary>Returns the componentwise arcTangent of a double3 vector.</summary>
	inline static double3 Atan(double3 x) { return double3(Atan(x.x), Atan(x.y), Atan(x.z)); }

	/// <summary>Returns the componentwise arcTangent of a double4 vector.</summary>
	inline static double4 Atan(double4 x) { return double4(Atan(x.x), Atan(x.y), Atan(x.z), Atan(x.w)); }


	/// <summary>Returns the 2-argument arcTangent of a pair of double values.</summary>
	inline static double Atan2(double y, double x) { return (double)atan2(y, x); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of doubles2 vectors.</summary>
	inline static double2 Atan2(double2 y, double2 x) { return double2(Atan2(y.x, x.x), Atan2(y.y, x.y)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of doubles3 vectors.</summary>
	inline static double3 Atan2(double3 y, double3 x) { return double3(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of doubles4 vectors.</summary>
	inline static double4 Atan2(double4 y, double4 x) { return double4(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z), Atan2(y.w, x.w)); }


	/// <summary>Returns the CoSine of a double value.</summary>
	inline static double Cos(double x) { return (double)cos(x); }

	/// <summary>Returns the componentwise CoSine of a double2 vector.</summary>
	inline static double2 Cos(double2 x) { return double2(Cos(x.x), Cos(x.y)); }

	/// <summary>Returns the componentwise CoSine of a double3 vector.</summary>
	inline static double3 Cos(double3 x) { return double3(Cos(x.x), Cos(x.y), Cos(x.z)); }

	/// <summary>Returns the componentwise CoSine of a double4 vector.</summary>
	inline static double4 Cos(double4 x) { return double4(Cos(x.x), Cos(x.y), Cos(x.z), Cos(x.w)); }


	/// <summary>Returns the hyperbolic CoSine of a double value.</summary>
	inline static double Cosh(double x) { return (double)cosh(x); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a double2 vector.</summary>
	inline static double2 Cosh(double2 x) { return double2(Cosh(x.x), Cosh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a double3 vector.</summary>
	inline static double3 Cosh(double3 x) { return double3(Cosh(x.x), Cosh(x.y), Cosh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a double4 vector.</summary>
	inline static double4 Cosh(double4 x) { return double4(Cosh(x.x), Cosh(x.y), Cosh(x.z), Cosh(x.w)); }

	/// <summary>Returns the arcCoSine of a double value.</summary>
	inline static double Acos(double x) { return (double)acos((double)x); }

	/// <summary>Returns the componentwise arcCoSine of a double2 vector.</summary>
	inline static double2 Acos(double2 x) { return double2(Acos(x.x), Acos(x.y)); }

	/// <summary>Returns the componentwise arcCoSine of a double3 vector.</summary>
	inline static double3 Acos(double3 x) { return double3(Acos(x.x), Acos(x.y), Acos(x.z)); }

	/// <summary>Returns the componentwise arcCoSine of a double4 vector.</summary>
	inline static double4 Acos(double4 x) { return double4(Acos(x.x), Acos(x.y), Acos(x.z), Acos(x.w)); }


	/// <summary>Returns the Sine of a double value.</summary>
	inline static double Sin(double x) { return (double)sin((double)x); }

	/// <summary>Returns the componentwise Sine of a double2 vector.</summary>
	inline static double2 Sin(double2 x) { return double2(Sin(x.x), Sin(x.y)); }

	/// <summary>Returns the componentwise Sine of a double3 vector.</summary>
	inline static double3 Sin(double3 x) { return double3(Sin(x.x), Sin(x.y), Sin(x.z)); }

	/// <summary>Returns the componentwise Sine of a double4 vector.</summary>
	inline static double4 Sin(double4 x) { return double4(Sin(x.x), Sin(x.y), Sin(x.z), Sin(x.w)); }



	/// <summary>Returns the hyperbolic Sine of a double value.</summary>
	inline static double Sinh(double x) { return (double)sinh((double)x); }

	/// <summary>Returns the componentwise hyperbolic Sine of a double2 vector.</summary>
	inline static double2 Sinh(double2 x) { return double2(Sinh(x.x), Sinh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a double3 vector.</summary>
	inline static double3 Sinh(double3 x) { return double3(Sinh(x.x), Sinh(x.y), Sinh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a double4 vector.</summary>
	inline static double4 Sinh(double4 x) { return double4(Sinh(x.x), Sinh(x.y), Sinh(x.z), Sinh(x.w)); }


	/// <summary>Returns the arcSine of a double value.</summary>
	inline static double Asin(double x) { return (double)asin((double)x); }

	/// <summary>Returns the componentwise arcSine of a double2 vector.</summary>
	inline static double2 Asin(double2 x) { return double2(Asin(x.x), Asin(x.y)); }

	/// <summary>Returns the componentwise arcSine of a double3 vector.</summary>
	inline static double3 Asin(double3 x) { return double3(Asin(x.x), Asin(x.y), Asin(x.z)); }

	/// <summary>Returns the componentwise arcSine of a double4 vector.</summary>
	inline static double4 Asin(double4 x) { return double4(Asin(x.x), Asin(x.y), Asin(x.z), Asin(x.w)); }


	/// <summary>Returns the Dot product of two double values. Equivalent to multiplication.</summary>
	inline static double Dot(double x, double y) { return x * y; }

	/// <summary>Returns the Dot product of two double2 vectors.</summary>
	inline static double Dot(double2 x, double2 y) { return x.x * y.x + x.y * y.y; }

	/// <summary>Returns the Dot product of two double3 vectors.</summary>
	inline static double Dot(double3 x, double3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }

	/// <summary>Returns the Dot product of two double4 vectors.</summary>
	inline static double Dot(double4 x, double4 y) { return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w; }

	/// <summary>Returns the square root of a double value.</summary>
	inline static double Sqrt(double x) { return sqrt((double)x); }

	/// <summary>Returns the componentwise square root of a double2 vector.</summary>
	inline static double2 Sqrt(double2 x) { return double2(Sqrt(x.x), Sqrt(x.y)); }

	/// <summary>Returns the componentwise square root of a double3 vector.</summary>
	inline static double3 Sqrt(double3 x) { return double3(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z)); }

	/// <summary>Returns the componentwise square root of a double4 vector.</summary>
	inline static double4 Sqrt(double4 x) { return double4(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z), Sqrt(x.w)); }


	/// <summary>Returns the reciprocal square root of a double value.</summary>
	inline static double Rsqrt(double x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a double2 vector.</summary>
	inline static double2 Rsqrt(double2 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a double3 vector.</summary>
	inline static double3 Rsqrt(double3 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a double4 vector</summary>
	inline static double4 Rsqrt(double4 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns a Normalized version of the double2 vector x by scaling it by 1 / Length(x).</summary>
	inline static double2 Normalize(double2 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the double3 vector x by scaling it by 1 / Length(x).</summary>
	inline static double3 Normalize(double3 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the double4 vector x by scaling it by 1 / Length(x).</summary>
	inline static double4 Normalize(double4 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns the Length of a double2 vector.</summary>
	inline static double Length(double2 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a double3 vector.</summary>
	inline static double Length(double3 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a double4 vector.</summary>
	inline static double Length(double4 x) { return sqrt(Dot(x, x)); }




	/// <summary>Returns the squared Length of a double value. Equivalent to squaring the value.</summary>
	inline static double Lengthsq(double x) { return x * x; }

	/// <summary>Returns the squared Length of a double2 vector.</summary>
	inline static double Lengthsq(double2 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a double3 vector.</summary>
	inline static double Lengthsq(double3 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a double4 vector.</summary>
	inline static double Lengthsq(double4 x) { return Dot(x, x); }


	/// <summary>Returns the Distance between two double2 vectors.</summary>
	inline static double Distance(double2 x, double2 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two double3 vectors.</summary>
	inline static double Distance(double3 x, double3 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two double4 vectors.</summary>
	inline static double Distance(double4 x, double4 y) { return Length(y - x); }



	/// <summary>Returns the Distance between two double values.</summary>
	inline static double Distancesq(double x, double y) { return (y - x) * (y - x); }

	/// <summary>Returns the Distance between two double2 vectors.</summary>
	inline static double Distancesq(double2 x, double2 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two double3 vectors.</summary>
	inline static double Distancesq(double3 x, double3 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two double4 vectors.</summary>
	inline static double Distancesq(double4 x, double4 y) { return Lengthsq(y - x); }



	/// <summary>Returns the Cross product of two double3 vectors.</summary>
	inline static double3 Cross(double3 x, double3 y) {
		double3 retVal = x * double3(y.y, y.z, y.x) - double3(x.y, x.z, x.x) * y;
		return double3(retVal.y, retVal.z, retVal.x);
	}

	/// <summary>Returns the Sine and CoSine of the input double value x through the out parameters s and c.</summary>
	inline static void SinCos(double x, double* s, double* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input double2 vector x through the out parameters s and c.</summary>
	inline static void SinCos(double2 x, double2* s, double2* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input double3 vector x through the out parameters s and c.</summary>
	inline static void SinCos(double3 x, double3* s, double3* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input double4 vector x through the out parameters s and c.</summary>
	inline static void SinCos(double4 x, double4* s, double4* c) { *s = Sin(x); *c = Cos(x); }


	/// <summary>Returns the Minimum of two double values.</summary>
	inline static double Min(double x, double y) { return x < y ? x : y; }

	/// <summary>Returns the componentwise Minimum of two double2 vectors.</summary>
	inline static double2 Min(double2 x, double2 y) { return double2(Min(x.x, y.x), Min(x.y, y.y)); }

	/// <summary>Returns the componentwise Minimum of two double3 vectors.</summary>
	inline static double3 Min(double3 x, double3 y) { return double3(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z)); }

	/// <summary>Returns the componentwise Minimum of two double4 vectors.</summary>
	inline static double4 Min(double4 x, double4 y) { return double4(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z), Min(x.w, y.w)); }


	/// <summary>Returns the Maximum of two double values.</summary>
	inline static double Max(double x, double y) { return x > y ? x : y; }

	/// <summary>Returns the componentwise Maximum of two double2 vectors.</summary>
	inline static double2 Max(double2 x, double2 y) { return double2(Max(x.x, y.x), Max(x.y, y.y)); }

	/// <summary>Returns the componentwise Maximum of two double3 vectors.</summary>
	inline static double3 Max(double3 x, double3 y) { return double3(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z)); }

	/// <summary>Returns the componentwise Maximum of two double4 vectors.</summary>
	inline static double4 Max(double4 x, double4 y) { return double4(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z), Max(x.w, y.w)); }

	inline static double Lerp(double x, double y, double s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static double2 Lerp(double2 x, double2 y, double s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static double3 Lerp(double3 x, double3 y, double s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static double4 Lerp(double4 x, double4 y, double s) { return x + s * (y - x); }


	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static double2 Lerp(double2 x, double2 y, double2 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static double3 Lerp(double3 x, double3 y, double3 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static double4 Lerp(double4 x, double4 y, double4 s) { return x + s * (y - x); }

	/// <summary>Returns the result of normalizing a doubleing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static double Unlerp(double a, double b, double x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a doubleing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static double2 Unlerp(double2 a, double2 b, double2 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a doubleing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static double3 Unlerp(double3 a, double3 b, double3 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a doubleing point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static double4 Unlerp(double4 a, double4 b, double4 x) { return (x - a) / (b - a); }

	/// <summary>Returns the result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static double Remap(double a, double b, double c, double d, double x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static double2 Remap(double2 a, double2 b, double2 c, double2 d, double2 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static double3 Remap(double3 a, double3 b, double3 c, double3 d, double3 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static double4 Remap(double4 a, double4 b, double4 c, double4 d, double4 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the result of Clamping the value x into the interval [a, b], where x, a and b are double values.</summary>
	inline static double Clamp(double x, double a, double b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are double2 vectors.</summary>
	inline static double2 Clamp(double2 x, double2 a, double2 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are double3 vectors.</summary>
	inline static double3 Clamp(double3 x, double3 a, double3 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are double4 vectors.</summary>
	inline static double4 Clamp(double4 x, double4 a, double4 b) { return Max(a, Min(b, x)); }

	inline static double select_shuffle_component(double4 a, double4 b, char component)
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

	inline static double4 shuffle(double4 a, double4 b, char x, char y, char z, char w)
	{
		return double4(
			select_shuffle_component(a, b, x),
			select_shuffle_component(a, b, y),
			select_shuffle_component(a, b, z),
			select_shuffle_component(a, b, w));
	}

	inline static double4 movelh(double4 a, double4 b)
	{
		return shuffle(a, b, 0, 1, 4, 5);
	}
	inline static double4 movehl(double4 a, double4 b)
	{
		return shuffle(b, a, 2, 3, 6, 7);
	}
	// SSE shuffles
	inline static double4 unpacklo(double4 a, double4 b)
	{
		return shuffle(a, b, 0, 4, 1, 5);
	}
	inline static double4 unpackhi(double4 a, double4 b)
	{
		return shuffle(a, b, 2, 6, 3, 7);
	}
#pragma endregion
#pragma region Component
	/// <summary>Returns the Maximum component of a double2 vector.</summary>
	inline static double CMax(double2 x) { return Max(x.x, x.y); }

	/// <summary>Returns the Maximum component of a double3 vector.</summary>
	inline static double CMax(double3 x) { return Max(Max(x.x, x.y), x.z); }

	/// <summary>Returns the Maximum component of a double4 vector.</summary>
	inline static double CMax(double4 x) { return Max(Max(x.x, x.y), Max(x.z, x.w)); }

	/// <summary>Returns the horizontal sum of components of a double2 vector.</summary>
	inline static double Csum(double2 x) { return x.x + x.y; }

	/// <summary>Returns the horizontal sum of components of a double3 vector.</summary>
	inline static double Csum(double3 x) { return x.x + x.y + x.z; }

	/// <summary>Returns the horizontal sum of components of a double4 vector.</summary>
	inline static double Csum(double4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion

#pragma region Transpose
	/// <summary>Return the double2x2 Transpose of a double2x2 matrix.</summary>
	inline double2x2 Transpose(double2x2 v)
	{
		return double2x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y);
	}
	/// <summary>Return the double3x2 Transpose of a double2x3 matrix.</summary>
	inline double3x2 Transpose(double2x3 v)
	{
		return double3x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y);
	}
	/// <summary>Return the double4x2 Transpose of a double2x4 matrix.</summary>
	inline double4x2 Transpose(double2x4 v)
	{
		return double4x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y,
			v.c3.x, v.c3.y);
	}
	/// <summary>Return the double2x3 Transpose of a double3x2 matrix.</summary>
	inline double2x3 Transpose(double3x2 v)
	{
		return double2x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z);
	}
	/// <summary>Return the double3x3 Transpose of a double3x3 matrix.</summary>
	inline double3x3 Transpose(double3x3 v)
	{
		return double3x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z);
	}
	/// <summary>Return the double4x3 Transpose of a double3x4 matrix.</summary>
	inline static double4x3 Transpose(double3x4 v)
	{
		return double4x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z,
			v.c3.x, v.c3.y, v.c3.z);
	}
	/// <summary>Return the double2x4 Transpose of a double4x2 matrix.</summary>
	inline static double2x4 Transpose(double4x2 v)
	{
		return double2x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w);
	}
	/// <summary>Return the double3x4 Transpose of a double4x3 matrix.</summary>
	inline static double3x4 Transpose(double4x3 v)
	{
		return double3x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w);
	}
	/// <summary>Return the double4x4 Transpose of a double4x4 matrix.</summary>
	inline static double4x4 Transpose(double4x4 v)
	{
		return double4x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w,
			v.c3.x, v.c3.y, v.c3.z, v.c3.w);
	}

#pragma endregion
#pragma region Inverse
	/// <summary>Returns the double2x2 full Inverse of a double2x2 matrix.</summary>
	inline double2x2 Inverse(double2x2 m)
	{
		double a = m.c0.x;
		double b = m.c1.x;
		double c = m.c0.y;
		double d = m.c1.y;

		double det = a * d - b * c;

		return double2x2(d, -b, -c, a) * (1.0f / det);
	}
	/// <summary>Returns the double3x3 full Inverse of a double3x3 matrix.</summary>
	inline double3x3 Inverse(double3x3 m)
	{
		double3 c0 = m.c0;
		double3 c1 = m.c1;
		double3 c2 = m.c2;

		double3 t0 = double3(c1.x, c2.x, c0.x);
		double3 t1 = double3(c1.y, c2.y, c0.y);
		double3 t2 = double3(c1.z, c2.z, c0.z);

		double3 m0 = t1 * double3(t2.y, t2.z, t2.x) - double3(t1.y, t1.z, t1.x) * t2;
		double3 m1 = double3(t0.y, t0.z, t0.x) * t2 - t0 * double3(t2.y, t2.z, t2.x);
		double3 m2 = t0 * double3(t1.y, t1.z, t1.x) - t0 * double3(t2.y, t2.z, t2.x) * t1;

		double rcpDet = 1.0f / Csum(double3(t0.z, t0.x, t0.y) * m0);
		return double3x3(m0, m1, m2) * rcpDet;
	}
	// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
	inline static double3x4 fastInverse(double3x4 m)
	{
		double3 c0 = m.c0;
		double3 c1 = m.c1;
		double3 c2 = m.c2;
		double3 pos = m.c3;

		double3 r0 = double3(c0.x, c1.x, c2.x);
		double3 r1 = double3(c0.y, c1.y, c2.y);
		double3 r2 = double3(c0.z, c1.z, c2.z);

		pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);

		return double3x4(r0, r1, r2, pos);
	}
	/// <summary>Returns the double4x4 full Inverse of a double4x4 matrix.</summary>
	inline static double4x4 Inverse(double4x4 m)
	{
		double4 c0 = m.c0;
		double4 c1 = m.c1;
		double4 c2 = m.c2;
		double4 c3 = m.c3;

		double4 r0y_r1y_r0x_r1x = movelh(c1, c0);
		double4 r0z_r1z_r0w_r1w = movelh(c2, c3);
		double4 r2y_r3y_r2x_r3x = movehl(c0, c1);
		double4 r2z_r3z_r2w_r3w = movehl(c3, c2);

		double4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
		double4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
		double4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
		double4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

		double4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
		double4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
		double4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
		double4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
		double4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

		// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
		double4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
		double4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
		double4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

		// Expand inner terms back to 4 components. zw signs still need to be flipped
		double4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
		double4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

		double4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
		double4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

		// Calculate Minors
		double4 Minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

		double4 denom = r0_xyzw * Minors0;

		// Horizontal sum of denoMinator. Free sign flip of z and w compensates for misSing flip in inner terms.
		denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
		denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

		double4 rcp_denom_ppnn = double4(1.0f) / denom;
		double4x4 res;
		res.c0 = Minors0 * rcp_denom_ppnn;

		double4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
		double4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

		double4 Minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
		res.c1 = Minors1 * rcp_denom_ppnn;

		double4 Minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
		res.c2 = Minors2 * rcp_denom_ppnn;

		double4 Minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
		res.c3 = Minors3 * rcp_denom_ppnn;
		return res;
	}
	// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
	inline static double4x4 fastInverse(double4x4 m)
	{
		double4 c0 = m.c0;
		double4 c1 = m.c1;
		double4 c2 = m.c2;
		double4 pos = m.c3;

		double4 zero = double4(0);

		double4 t0 = unpacklo(c0, c2);
		double4 t1 = unpacklo(c1, zero);
		double4 t2 = unpackhi(c0, c2);
		double4 t3 = unpackhi(c1, zero);

		double4 r0 = unpacklo(t0, t1);
		double4 r1 = unpackhi(t0, t1);
		double4 r2 = unpacklo(t2, t3);

		pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);
		pos.w = 1.0f;

		return double4x4(r0, r1, r2, pos);
	}
#pragma endregion
#pragma region Determinant
	/// <summary>Returns the Determinant of a double2x2 matrix.</summary>
	inline double Determinant(double2x2 m)
	{
		double a = m.c0.x;
		double b = m.c1.x;
		double c = m.c0.y;
		double d = m.c1.y;

		return a * d - b * c;
	}
	/// <summary>Returns the Determinant of a double3x3 matrix.</summary>
	inline double Determinant(double3x3 m)
	{
		double3 c0 = m.c0;
		double3 c1 = m.c1;
		double3 c2 = m.c2;

		double m00 = c1.y * c2.z - c1.z * c2.y;
		double m01 = c0.y * c2.z - c0.z * c2.y;
		double m02 = c0.y * c1.z - c0.z * c1.y;

		return c0.x * m00 - c1.x * m01 + c2.x * m02;
	}
	/// <summary>Returns the Determinant of a double4x4 matrix.</summary>
	inline static double Determinant(double4x4 m)
	{
		double4 c0 = m.c0;
		double4 c1 = m.c1;
		double4 c2 = m.c2;
		double4 c3 = m.c3;

		double m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
		double m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
		double m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
		double m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

		return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
	}

#pragma endregion
}