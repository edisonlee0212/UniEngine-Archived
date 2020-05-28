#pragma once
#include "bool.h"
#include <math.h>
namespace UniEngine {
#define ulong unsigned long
#pragma region ulong2
	struct ulong2 {
		ulong x, y;
		ulong2() : x(0), y(0) {}
		ulong2(ulong x, ulong y) : x(x), y(y) {}
		ulong2(ulong v) : x(v), y(v) {}
	};
	/// <summary>Returns the result of a componentwise multiplication operation on two ulong2 vectors.</summary>

	inline static ulong2 operator * (const ulong2& lhs, const ulong2& rhs) { return ulong2(lhs.x * rhs.x, lhs.y * rhs.y); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong2 vector and a ulong value.</summary>

	inline static ulong2 operator * (const ulong2& lhs, ulong rhs) { return ulong2(lhs.x * rhs, lhs.y * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong2 vector.</summary>

	inline static ulong2 operator * (ulong lhs, const ulong2& rhs) { return ulong2(lhs * rhs.x, lhs * rhs.y); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong2 vectors.</summary>

	inline static ulong2 operator + (const ulong2& lhs, const ulong2& rhs) { return ulong2(lhs.x + rhs.x, lhs.y + rhs.y); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong2 vector and a ulong value.</summary>

	inline static ulong2 operator + (const ulong2& lhs, ulong rhs) { return ulong2(lhs.x + rhs, lhs.y + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong2 vector.</summary>

	inline static ulong2 operator + (ulong lhs, const ulong2& rhs) { return ulong2(lhs + rhs.x, lhs + rhs.y); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong2 vectors.</summary>

	inline static ulong2 operator - (const ulong2& lhs, const ulong2& rhs) { return ulong2(lhs.x - rhs.x, lhs.y - rhs.y); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong2 vector and a ulong value.</summary>

	inline static ulong2 operator - (const ulong2& lhs, ulong rhs) { return ulong2(lhs.x - rhs, lhs.y - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong2 vector.</summary>

	inline static ulong2 operator - (ulong lhs, const ulong2& rhs) { return ulong2(lhs - rhs.x, lhs - rhs.y); }


	/// <summary>Returns the result of a componentwise division operation on two ulong2 vectors.</summary>

	inline static ulong2 operator / (const ulong2& lhs, const ulong2& rhs) { return ulong2(lhs.x / rhs.x, lhs.y / rhs.y); }

	/// <summary>Returns the result of a componentwise division operation on a ulong2 vector and a ulong value.</summary>

	inline static ulong2 operator / (const ulong2& lhs, ulong rhs) { return ulong2(lhs.x / rhs, lhs.y / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong2 vector.</summary>

	inline static ulong2 operator / (ulong lhs, const ulong2& rhs) { return ulong2(lhs / rhs.x, lhs / rhs.y); }

	/// <summary>Returns the result of a componentwise increment operation on a ulong2 vector.</summary>

	inline static ulong2 operator ++ (ulong2 val) { return ulong2(++val.x, ++val.y); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong2 vector.</summary>

	inline static ulong2 operator -- (ulong2 val) { return ulong2(--val.x, --val.y); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong2 vectors.</summary>

	inline static bool2 operator < (const ulong2& lhs, const ulong2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong2 vector and a ulong value.</summary>

	inline static bool2 operator < (const ulong2& lhs, ulong rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong2 vector.</summary>

	inline static bool2 operator < (ulong lhs, const ulong2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong2 vectors.</summary>

	inline static bool2 operator <= (const ulong2& lhs, const ulong2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong2 vector and a ulong value.</summary>

	inline static bool2 operator <= (const ulong2& lhs, ulong rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong2 vector.</summary>

	inline static bool2 operator <= (ulong lhs, const ulong2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong2 vectors.</summary>

	inline static bool2 operator > (const ulong2& lhs, const ulong2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong2 vector and a ulong value.</summary>

	inline static bool2 operator > (const ulong2& lhs, ulong rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong2 vector.</summary>

	inline static bool2 operator > (ulong lhs, const ulong2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong2 vectors.</summary>

	inline static bool2 operator >= (const ulong2& lhs, const ulong2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong2 vector and a ulong value.</summary>

	inline static bool2 operator >= (const ulong2& lhs, ulong rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong2 vector.</summary>

	inline static bool2 operator >= (ulong lhs, const ulong2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong2 vectors.</summary>

	inline static bool2 operator == (const ulong2& lhs, const ulong2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong2 vector and a ulong value.</summary>

	inline static bool2 operator == (const ulong2& lhs, ulong rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong2 vector.</summary>

	inline static bool2 operator == (ulong lhs, const ulong2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong2 vectors.</summary>

	inline static bool2 operator != (const ulong2& lhs, const ulong2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong2 vector and a ulong value.</summary>

	inline static bool2 operator != (const ulong2& lhs, ulong rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong2 vector.</summary>

	inline static bool2 operator != (ulong lhs, const ulong2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region ulong2x2
	struct ulong2x2
	{
		ulong2 c0, c1;
		ulong2x2() : c0(), c1() {}
		ulong2x2(ulong m00, ulong m01,
			ulong m10, ulong m11) :c0(ulong2(m00, m10)), c1(ulong2(m01, m11)) {}
		ulong2x2(ulong2 c0, ulong2 c1) : c0(c0), c1(c1) {}
		ulong2x2(ulong v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong2x2 matrices.</summary>

	inline static ulong2x2 operator * (const ulong2x2& lhs, const ulong2x2& rhs) { return ulong2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static ulong2x2 operator * (const ulong2x2& lhs, ulong rhs) { return ulong2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static ulong2x2 operator * (ulong lhs, const ulong2x2& rhs) { return ulong2x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong2x2 matrices.</summary>

	inline static ulong2x2 operator + (const ulong2x2& lhs, const ulong2x2& rhs) { return ulong2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static ulong2x2 operator + (const ulong2x2& lhs, ulong rhs) { return ulong2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static ulong2x2 operator + (ulong lhs, const ulong2x2& rhs) { return ulong2x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong2x2 matrices.</summary>

	inline static ulong2x2 operator - (const ulong2x2& lhs, const ulong2x2& rhs) { return ulong2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static ulong2x2 operator - (const ulong2x2& lhs, ulong rhs) { return ulong2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static ulong2x2 operator - (ulong lhs, const ulong2x2& rhs) { return ulong2x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two ulong2x2 matrices.</summary>

	inline static ulong2x2 operator / (const ulong2x2& lhs, const ulong2x2& rhs) { return ulong2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static ulong2x2 operator / (const ulong2x2& lhs, ulong rhs) { return ulong2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static ulong2x2 operator / (ulong lhs, const ulong2x2& rhs) { return ulong2x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a ulong2x2 matrix.</summary>

	inline static ulong2x2 operator ++ (ulong2x2 val) { return ulong2x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong2x2 matrix.</summary>

	inline static ulong2x2 operator -- (ulong2x2 val) { return ulong2x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong2x2 matrices.</summary>

	inline static bool2x2 operator < (const ulong2x2& lhs, const ulong2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static bool2x2 operator < (const ulong2x2& lhs, ulong rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static bool2x2 operator < (ulong lhs, const ulong2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong2x2 matrices.</summary>

	inline static bool2x2 operator <= (const ulong2x2& lhs, const ulong2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static bool2x2 operator <= (const ulong2x2& lhs, ulong rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static bool2x2 operator <= (ulong lhs, const ulong2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong2x2 matrices.</summary>

	inline static bool2x2 operator > (const ulong2x2& lhs, const ulong2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static bool2x2 operator > (const ulong2x2& lhs, ulong rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static bool2x2 operator > (ulong lhs, const ulong2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong2x2 matrices.</summary>

	inline static bool2x2 operator >= (const ulong2x2& lhs, const ulong2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static bool2x2 operator >= (const ulong2x2& lhs, ulong rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static bool2x2 operator >= (ulong lhs, const ulong2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong2x2 matrices.</summary>

	inline static bool2x2 operator == (const ulong2x2& lhs, const ulong2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static bool2x2 operator == (const ulong2x2& lhs, ulong rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static bool2x2 operator == (ulong lhs, const ulong2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong2x2 matrices.</summary>

	inline static bool2x2 operator != (const ulong2x2& lhs, const ulong2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong2x2 matrix and a ulong value.</summary>

	inline static bool2x2 operator != (const ulong2x2& lhs, ulong rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong2x2 matrix.</summary>

	inline static bool2x2 operator != (ulong lhs, const ulong2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region ulong2x3
	struct ulong2x3
	{
		ulong2 c0, c1, c2;
		ulong2x3() : c0(), c1(), c2() {}
		ulong2x3(ulong m00, ulong m01, ulong m02,
			ulong m10, ulong m11, ulong m12)
		{
			c0 = ulong2(m00, m10);
			c1 = ulong2(m01, m11);
			c2 = ulong2(m02, m12);
		}
		ulong2x3(ulong2 c0, ulong2 c1, ulong2 c2) : c0(c0), c1(c1), c2(c2) {}
		ulong2x3(ulong v) : c0(v), c1(v), c2(v) {}
	};

	/// <summary>Returns the result of a componentwise multiplication operation on two ulong2x3 matrices.</summary>

	inline static ulong2x3 operator * (const ulong2x3& lhs, const ulong2x3& rhs) { return ulong2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static ulong2x3 operator * (const ulong2x3& lhs, ulong rhs) { return ulong2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static ulong2x3 operator * (ulong lhs, const ulong2x3& rhs) { return ulong2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong2x3 matrices.</summary>

	inline static ulong2x3 operator + (const ulong2x3& lhs, const ulong2x3& rhs) { return ulong2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static ulong2x3 operator + (const ulong2x3& lhs, ulong rhs) { return ulong2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static ulong2x3 operator + (ulong lhs, const ulong2x3& rhs) { return ulong2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong2x3 matrices.</summary>

	inline static ulong2x3 operator - (const ulong2x3& lhs, const ulong2x3& rhs) { return ulong2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static ulong2x3 operator - (const ulong2x3& lhs, ulong rhs) { return ulong2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static ulong2x3 operator - (ulong lhs, const ulong2x3& rhs) { return ulong2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two ulong2x3 matrices.</summary>

	inline static ulong2x3 operator / (const ulong2x3& lhs, const ulong2x3& rhs) { return ulong2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static ulong2x3 operator / (const ulong2x3& lhs, ulong rhs) { return ulong2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static ulong2x3 operator / (ulong lhs, const ulong2x3& rhs) { return ulong2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


	/// <summary>Returns the result of a componentwise increment operation on a ulong2x3 matrix.</summary>

	inline static ulong2x3 operator ++ (ulong2x3 val) { return ulong2x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong2x3 matrix.</summary>

	inline static ulong2x3 operator -- (ulong2x3 val) { return ulong2x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong2x3 matrices.</summary>

	inline static bool2x3 operator < (const ulong2x3& lhs, const ulong2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static bool2x3 operator < (const ulong2x3& lhs, ulong rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static bool2x3 operator < (ulong lhs, const ulong2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong2x3 matrices.</summary>

	inline static bool2x3 operator <= (const ulong2x3& lhs, const ulong2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static bool2x3 operator <= (const ulong2x3& lhs, ulong rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static bool2x3 operator <= (ulong lhs, const ulong2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong2x3 matrices.</summary>

	inline static bool2x3 operator > (const ulong2x3& lhs, const ulong2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static bool2x3 operator > (const ulong2x3& lhs, ulong rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static bool2x3 operator > (ulong lhs, const ulong2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong2x3 matrices.</summary>

	inline static bool2x3 operator >= (const ulong2x3& lhs, const ulong2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static bool2x3 operator >= (const ulong2x3& lhs, ulong rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static bool2x3 operator >= (ulong lhs, const ulong2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong2x3 matrices.</summary>

	inline static bool2x3 operator == (const ulong2x3& lhs, const ulong2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static bool2x3 operator == (const ulong2x3& lhs, ulong rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static bool2x3 operator == (ulong lhs, const ulong2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong2x3 matrices.</summary>

	inline static bool2x3 operator != (const ulong2x3& lhs, const ulong2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong2x3 matrix and a ulong value.</summary>

	inline static bool2x3 operator != (const ulong2x3& lhs, ulong rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong2x3 matrix.</summary>

	inline static bool2x3 operator != (ulong lhs, const ulong2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region ulong2x4
	struct ulong2x4
	{
		ulong2 c0, c1, c2, c3;
		ulong2x4() : c0(), c1(), c2(), c3() {}
		ulong2x4(ulong m00, ulong m01, ulong m02, ulong m03,
			ulong m10, ulong m11, ulong m12, ulong m13)
		{
			c0 = ulong2(m00, m10);
			c1 = ulong2(m01, m11);
			c2 = ulong2(m02, m12);
			c3 = ulong2(m03, m13);
		}
		ulong2x4(ulong2 c0, ulong2 c1, ulong2 c2, ulong2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		ulong2x4(ulong v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong2x4 matrices.</summary>

	inline static ulong2x4 operator * (const ulong2x4& lhs, const ulong2x4& rhs) { return ulong2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static ulong2x4 operator * (const ulong2x4& lhs, ulong rhs) { return ulong2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static ulong2x4 operator * (ulong lhs, const ulong2x4& rhs) { return ulong2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong2x4 matrices.</summary>

	inline static ulong2x4 operator + (const ulong2x4& lhs, const ulong2x4& rhs) { return ulong2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static ulong2x4 operator + (const ulong2x4& lhs, ulong rhs) { return ulong2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static ulong2x4 operator + (ulong lhs, const ulong2x4& rhs) { return ulong2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong2x4 matrices.</summary>

	inline static ulong2x4 operator - (const ulong2x4& lhs, const ulong2x4& rhs) { return ulong2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static ulong2x4 operator - (const ulong2x4& lhs, ulong rhs) { return ulong2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static ulong2x4 operator - (ulong lhs, const ulong2x4& rhs) { return ulong2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two ulong2x4 matrices.</summary>

	inline static ulong2x4 operator / (const ulong2x4& lhs, const ulong2x4& rhs) { return ulong2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static ulong2x4 operator / (const ulong2x4& lhs, ulong rhs) { return ulong2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static ulong2x4 operator / (ulong lhs, const ulong2x4& rhs) { return ulong2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a ulong2x4 matrix.</summary>

	inline static ulong2x4 operator ++ (ulong2x4 val) { return ulong2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong2x4 matrix.</summary>

	inline static ulong2x4 operator -- (ulong2x4 val) { return ulong2x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong2x4 matrices.</summary>

	inline static bool2x4 operator < (const ulong2x4& lhs, const ulong2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static bool2x4 operator < (const ulong2x4& lhs, ulong rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static bool2x4 operator < (ulong lhs, const ulong2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong2x4 matrices.</summary>

	inline static bool2x4 operator <= (const ulong2x4& lhs, const ulong2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static bool2x4 operator <= (const ulong2x4& lhs, ulong rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static bool2x4 operator <= (ulong lhs, const ulong2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong2x4 matrices.</summary>

	inline static bool2x4 operator > (const ulong2x4& lhs, const ulong2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static bool2x4 operator > (const ulong2x4& lhs, ulong rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static bool2x4 operator > (ulong lhs, const ulong2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong2x4 matrices.</summary>

	inline static bool2x4 operator >= (const ulong2x4& lhs, const ulong2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static bool2x4 operator >= (const ulong2x4& lhs, ulong rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static bool2x4 operator >= (ulong lhs, const ulong2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong2x4 matrices.</summary>

	inline static bool2x4 operator == (const ulong2x4& lhs, const ulong2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static bool2x4 operator == (const ulong2x4& lhs, ulong rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static bool2x4 operator == (ulong lhs, const ulong2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong2x4 matrices.</summary>

	inline static bool2x4 operator != (const ulong2x4& lhs, const ulong2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong2x4 matrix and a ulong value.</summary>

	inline static bool2x4 operator != (const ulong2x4& lhs, ulong rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong2x4 matrix.</summary>

	inline static bool2x4 operator != (ulong lhs, const ulong2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region ulong3
	struct ulong3 {
		ulong x, y, z;
		ulong3() : x(0), y(0), z(0) {}
		ulong3(ulong x, ulong y, ulong z) : x(x), y(y), z(z) {}
		ulong3(ulong v) : x(v), y(v), z(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong3 vectors.</summary>

	inline static ulong3 operator * (const ulong3& lhs, const ulong3& rhs) { return ulong3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong3 vector and a ulong value.</summary>

	inline static ulong3 operator * (const ulong3& lhs, ulong rhs) { return ulong3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong3 vector.</summary>

	inline static ulong3 operator * (ulong lhs, const ulong3& rhs) { return ulong3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong3 vectors.</summary>

	inline static ulong3 operator + (const ulong3& lhs, const ulong3& rhs) { return ulong3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong3 vector and a ulong value.</summary>

	inline static ulong3 operator + (const ulong3& lhs, ulong rhs) { return ulong3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong3 vector.</summary>

	inline static ulong3 operator + (ulong lhs, const ulong3& rhs) { return ulong3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong3 vectors.</summary>

	inline static ulong3 operator - (const ulong3& lhs, const ulong3& rhs) { return ulong3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong3 vector and a ulong value.</summary>

	inline static ulong3 operator - (const ulong3& lhs, ulong rhs) { return ulong3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong3 vector.</summary>

	inline static ulong3 operator - (ulong lhs, const ulong3& rhs) { return ulong3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


	/// <summary>Returns the result of a componentwise division operation on two ulong3 vectors.</summary>

	inline static ulong3 operator / (const ulong3& lhs, const ulong3& rhs) { return ulong3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

	/// <summary>Returns the result of a componentwise division operation on a ulong3 vector and a ulong value.</summary>

	inline static ulong3 operator / (const ulong3& lhs, ulong rhs) { return ulong3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong3 vector.</summary>

	inline static ulong3 operator / (ulong lhs, const ulong3& rhs) { return ulong3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


	/// <summary>Returns the result of a componentwise increment operation on a ulong3 vector.</summary>

	inline static ulong3 operator ++ (ulong3 val) { return ulong3(++val.x, ++val.y, ++val.z); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong3 vector.</summary>

	inline static ulong3 operator -- (ulong3 val) { return ulong3(--val.x, --val.y, --val.z); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong3 vectors.</summary>

	inline static bool3 operator < (const ulong3& lhs, const ulong3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong3 vector and a ulong value.</summary>

	inline static bool3 operator < (const ulong3& lhs, ulong rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong3 vector.</summary>

	inline static bool3 operator < (ulong lhs, const ulong3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong3 vectors.</summary>

	inline static bool3 operator <= (const ulong3& lhs, const ulong3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong3 vector and a ulong value.</summary>

	inline static bool3 operator <= (const ulong3& lhs, ulong rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong3 vector.</summary>

	inline static bool3 operator <= (ulong lhs, const ulong3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong3 vectors.</summary>

	inline static bool3 operator > (const ulong3& lhs, const ulong3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong3 vector and a ulong value.</summary>

	inline static bool3 operator > (const ulong3& lhs, ulong rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong3 vector.</summary>

	inline static bool3 operator > (ulong lhs, const ulong3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong3 vectors.</summary>

	inline static bool3 operator >= (const ulong3& lhs, const ulong3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong3 vector and a ulong value.</summary>

	inline static bool3 operator >= (const ulong3& lhs, ulong rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong3 vector.</summary>

	inline static bool3 operator >= (ulong lhs, const ulong3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong3 vectors.</summary>

	inline static bool3 operator == (const ulong3& lhs, const ulong3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong3 vector and a ulong value.</summary>

	inline static bool3 operator == (const ulong3& lhs, ulong rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong3 vector.</summary>

	inline static bool3 operator == (ulong lhs, const ulong3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong3 vectors.</summary>

	inline static bool3 operator != (const ulong3& lhs, const ulong3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong3 vector and a ulong value.</summary>

	inline static bool3 operator != (const ulong3& lhs, ulong rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong3 vector.</summary>

	inline static bool3 operator != (ulong lhs, const ulong3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region ulong3x2
	struct ulong3x2
	{
		ulong3 c0, c1;
		ulong3x2() : c0(), c1() {}
		ulong3x2(ulong m00, ulong m01,
			ulong m10, ulong m11,
			ulong m20, ulong m21)
		{
			c0 = ulong3(m00, m10, m20);
			c1 = ulong3(m01, m11, m21);
		}

		ulong3x2(ulong3 c0, ulong3 c1) : c0(c0), c1(c1) {}
		ulong3x2(ulong v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong3x2 matrices.</summary>

	inline static ulong3x2 operator * (const ulong3x2& lhs, const ulong3x2& rhs) { return ulong3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static ulong3x2 operator * (const ulong3x2& lhs, ulong rhs) { return ulong3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static ulong3x2 operator * (ulong lhs, const ulong3x2& rhs) { return ulong3x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong3x2 matrices.</summary>

	inline static ulong3x2 operator + (const ulong3x2& lhs, const ulong3x2& rhs) { return ulong3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static ulong3x2 operator + (const ulong3x2& lhs, ulong rhs) { return ulong3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static ulong3x2 operator + (ulong lhs, const ulong3x2& rhs) { return ulong3x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong3x2 matrices.</summary>

	inline static ulong3x2 operator - (const ulong3x2& lhs, const ulong3x2& rhs) { return ulong3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static ulong3x2 operator - (const ulong3x2& lhs, ulong rhs) { return ulong3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static ulong3x2 operator - (ulong lhs, const ulong3x2& rhs) { return ulong3x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two ulong3x2 matrices.</summary>

	inline static ulong3x2 operator / (const ulong3x2& lhs, const ulong3x2& rhs) { return ulong3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static ulong3x2 operator / (const ulong3x2& lhs, ulong rhs) { return ulong3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static ulong3x2 operator / (ulong lhs, const ulong3x2& rhs) { return ulong3x2(lhs / rhs.c0, lhs / rhs.c1); }


	/// <summary>Returns the result of a componentwise increment operation on a ulong3x2 matrix.</summary>

	inline static ulong3x2 operator ++ (ulong3x2 val) { return ulong3x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong3x2 matrix.</summary>

	inline static ulong3x2 operator -- (ulong3x2 val) { return ulong3x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong3x2 matrices.</summary>

	inline static bool3x2 operator < (const ulong3x2& lhs, const ulong3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static bool3x2 operator < (const ulong3x2& lhs, ulong rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static bool3x2 operator < (ulong lhs, const ulong3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong3x2 matrices.</summary>

	inline static bool3x2 operator <= (const ulong3x2& lhs, const ulong3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static bool3x2 operator <= (const ulong3x2& lhs, ulong rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static bool3x2 operator <= (ulong lhs, const ulong3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong3x2 matrices.</summary>

	inline static bool3x2 operator > (const ulong3x2& lhs, const ulong3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static bool3x2 operator > (const ulong3x2& lhs, ulong rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static bool3x2 operator > (ulong lhs, const ulong3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong3x2 matrices.</summary>

	inline static bool3x2 operator >= (const ulong3x2& lhs, const ulong3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static bool3x2 operator >= (const ulong3x2& lhs, ulong rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static bool3x2 operator >= (ulong lhs, const ulong3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong3x2 matrices.</summary>

	inline static bool3x2 operator == (const ulong3x2& lhs, const ulong3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static bool3x2 operator == (const ulong3x2& lhs, ulong rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static bool3x2 operator == (ulong lhs, const ulong3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong3x2 matrices.</summary>

	inline static bool3x2 operator != (const ulong3x2& lhs, const ulong3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong3x2 matrix and a ulong value.</summary>

	inline static bool3x2 operator != (const ulong3x2& lhs, ulong rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong3x2 matrix.</summary>

	inline static bool3x2 operator != (ulong lhs, const ulong3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region ulong3x3
	struct ulong3x3
	{
		ulong3 c0, c1, c2;
		ulong3x3() : c0(), c1(), c2() {}
		ulong3x3(ulong m00, ulong m01, ulong m02,
			ulong m10, ulong m11, ulong m12,
			ulong m20, ulong m21, ulong m22)
		{
			c0 = ulong3(m00, m10, m20);
			c1 = ulong3(m01, m11, m21);
			c2 = ulong3(m02, m12, m22);
		}
		ulong3x3(ulong3 c0, ulong3 c1, ulong3 c2) : c0(c0), c1(c1), c2(c2) {}
		ulong3x3(ulong v) : c0(v), c1(v), c2(v) {}

	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong3x3 matrices.</summary>

	inline static ulong3x3 operator * (const ulong3x3& lhs, const ulong3x3& rhs) { return ulong3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static ulong3x3 operator * (const ulong3x3& lhs, ulong rhs) { return ulong3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static ulong3x3 operator * (ulong lhs, const ulong3x3& rhs) { return ulong3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong3x3 matrices.</summary>

	inline static ulong3x3 operator + (const ulong3x3& lhs, const ulong3x3& rhs) { return ulong3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static ulong3x3 operator + (const ulong3x3& lhs, ulong rhs) { return ulong3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static ulong3x3 operator + (ulong lhs, const ulong3x3& rhs) { return ulong3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong3x3 matrices.</summary>

	inline static ulong3x3 operator - (const ulong3x3& lhs, const ulong3x3& rhs) { return ulong3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static ulong3x3 operator - (const ulong3x3& lhs, ulong rhs) { return ulong3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static ulong3x3 operator - (ulong lhs, const ulong3x3& rhs) { return ulong3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two ulong3x3 matrices.</summary>

	inline static ulong3x3 operator / (const ulong3x3& lhs, const ulong3x3& rhs) { return ulong3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static ulong3x3 operator / (const ulong3x3& lhs, ulong rhs) { return ulong3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static ulong3x3 operator / (ulong lhs, const ulong3x3& rhs) { return ulong3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a ulong3x3 matrix.</summary>

	inline static ulong3x3 operator ++ (ulong3x3 val) { return ulong3x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong3x3 matrix.</summary>

	inline static ulong3x3 operator -- (ulong3x3 val) { return ulong3x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong3x3 matrices.</summary>

	inline static bool3x3 operator < (const ulong3x3& lhs, const ulong3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static bool3x3 operator < (const ulong3x3& lhs, ulong rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static bool3x3 operator < (ulong lhs, const ulong3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong3x3 matrices.</summary>

	inline static bool3x3 operator <= (const ulong3x3& lhs, const ulong3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static bool3x3 operator <= (const ulong3x3& lhs, ulong rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static bool3x3 operator <= (ulong lhs, const ulong3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong3x3 matrices.</summary>

	inline static bool3x3 operator > (const ulong3x3& lhs, const ulong3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static bool3x3 operator > (const ulong3x3& lhs, ulong rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static bool3x3 operator > (ulong lhs, const ulong3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong3x3 matrices.</summary>

	inline static bool3x3 operator >= (const ulong3x3& lhs, const ulong3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static bool3x3 operator >= (const ulong3x3& lhs, ulong rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static bool3x3 operator >= (ulong lhs, const ulong3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong3x3 matrices.</summary>

	inline static bool3x3 operator == (const ulong3x3& lhs, const ulong3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static bool3x3 operator == (const ulong3x3& lhs, ulong rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static bool3x3 operator == (ulong lhs, const ulong3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong3x3 matrices.</summary>

	inline static bool3x3 operator != (const ulong3x3& lhs, const ulong3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong3x3 matrix and a ulong value.</summary>

	inline static bool3x3 operator != (const ulong3x3& lhs, ulong rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong3x3 matrix.</summary>

	inline static bool3x3 operator != (ulong lhs, const ulong3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region ulong3x4
	struct ulong3x4
	{
		ulong3 c0, c1, c2, c3;
		ulong3x4() : c0(), c1(), c2(), c3() {}
		ulong3x4(ulong m00, ulong m01, ulong m02, ulong m03,
			ulong m10, ulong m11, ulong m12, ulong m13,
			ulong m20, ulong m21, ulong m22, ulong m23)
		{
			c0 = ulong3(m00, m10, m20);
			c1 = ulong3(m01, m11, m21);
			c2 = ulong3(m02, m12, m22);
			c3 = ulong3(m03, m13, m23);
		}
		ulong3x4(ulong3 c0, ulong3 c1, ulong3 c2, ulong3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		ulong3x4(ulong v) : c0(v), c1(v), c2(v), c3(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong3x4 matrices.</summary>

	inline static ulong3x4 operator * (const ulong3x4& lhs, const ulong3x4& rhs) { return ulong3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static ulong3x4 operator * (const ulong3x4& lhs, ulong rhs) { return ulong3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static ulong3x4 operator * (ulong lhs, const ulong3x4& rhs) { return ulong3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong3x4 matrices.</summary>

	inline static ulong3x4 operator + (const ulong3x4& lhs, const ulong3x4& rhs) { return ulong3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static ulong3x4 operator + (const ulong3x4& lhs, ulong rhs) { return ulong3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static ulong3x4 operator + (ulong lhs, const ulong3x4& rhs) { return ulong3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong3x4 matrices.</summary>

	inline static ulong3x4 operator - (const ulong3x4& lhs, const ulong3x4& rhs) { return ulong3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static ulong3x4 operator - (const ulong3x4& lhs, ulong rhs) { return ulong3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static ulong3x4 operator - (ulong lhs, const ulong3x4& rhs) { return ulong3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two ulong3x4 matrices.</summary>

	inline static ulong3x4 operator / (const ulong3x4& lhs, const ulong3x4& rhs) { return ulong3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static ulong3x4 operator / (const ulong3x4& lhs, ulong rhs) { return ulong3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static ulong3x4 operator / (ulong lhs, const ulong3x4& rhs) { return ulong3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

	/// <summary>Returns the result of a componentwise increment operation on a ulong3x4 matrix.</summary>

	inline static ulong3x4 operator ++ (ulong3x4 val) { return ulong3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong3x4 matrix.</summary>

	inline static ulong3x4 operator -- (ulong3x4 val) { return ulong3x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong3x4 matrices.</summary>

	inline static bool3x4 operator < (const ulong3x4& lhs, const ulong3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static bool3x4 operator < (const ulong3x4& lhs, ulong rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static bool3x4 operator < (ulong lhs, const ulong3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong3x4 matrices.</summary>

	inline static bool3x4 operator <= (const ulong3x4& lhs, const ulong3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static bool3x4 operator <= (const ulong3x4& lhs, ulong rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static bool3x4 operator <= (ulong lhs, const ulong3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong3x4 matrices.</summary>

	inline static bool3x4 operator > (const ulong3x4& lhs, const ulong3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static bool3x4 operator > (const ulong3x4& lhs, ulong rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static bool3x4 operator > (ulong lhs, const ulong3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong3x4 matrices.</summary>

	inline static bool3x4 operator >= (const ulong3x4& lhs, const ulong3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static bool3x4 operator >= (const ulong3x4& lhs, ulong rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static bool3x4 operator >= (ulong lhs, const ulong3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong3x4 matrices.</summary>

	inline static bool3x4 operator == (const ulong3x4& lhs, const ulong3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static bool3x4 operator == (const ulong3x4& lhs, ulong rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static bool3x4 operator == (ulong lhs, const ulong3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong3x4 matrices.</summary>

	inline static bool3x4 operator != (const ulong3x4& lhs, const ulong3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong3x4 matrix and a ulong value.</summary>

	inline static bool3x4 operator != (const ulong3x4& lhs, ulong rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong3x4 matrix.</summary>

	inline static bool3x4 operator != (ulong lhs, const ulong3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region ulong4
	struct ulong4 {
		ulong x, y, z, w;
		ulong4() : x(0), y(0), z(0), w(0) {}
		ulong4(ulong x, ulong y, ulong z, ulong w) : x(x), y(y), z(z), w(w) {}
		ulong4(ulong v) : x(v), y(v), z(v), w(v) {}
		ulong4(ulong3 xyz, ulong w) : w(w)
		{
			x = xyz.x;
			y = xyz.y;
			z = xyz.z;
		}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong4 vectors.</summary>

	inline static ulong4 operator * (const ulong4& lhs, const ulong4& rhs) { return ulong4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong4 vector and a ulong value.</summary>

	inline static ulong4 operator * (const ulong4& lhs, ulong rhs) { return ulong4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong4 vector.</summary>

	inline static ulong4 operator * (ulong lhs, const ulong4& rhs) { return ulong4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong4 vectors.</summary>

	inline static ulong4 operator + (const ulong4& lhs, const ulong4& rhs) { return ulong4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong4 vector and a ulong value.</summary>

	inline static ulong4 operator + (const ulong4& lhs, ulong rhs) { return ulong4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong4 vector.</summary>

	inline static ulong4 operator + (ulong lhs, const ulong4& rhs) { return ulong4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong4 vectors.</summary>

	inline static ulong4 operator - (const ulong4& lhs, const ulong4& rhs) { return ulong4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong4 vector and a ulong value.</summary>

	inline static ulong4 operator - (const ulong4& lhs, ulong rhs) { return ulong4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong4 vector.</summary>

	inline static ulong4 operator - (ulong lhs, const ulong4& rhs) { return ulong4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


	/// <summary>Returns the result of a componentwise division operation on two ulong4 vectors.</summary>

	inline static ulong4 operator / (const ulong4& lhs, const ulong4& rhs) { return ulong4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

	/// <summary>Returns the result of a componentwise division operation on a ulong4 vector and a ulong value.</summary>

	inline static ulong4 operator / (const ulong4& lhs, ulong rhs) { return ulong4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong4 vector.</summary>

	inline static ulong4 operator / (ulong lhs, const ulong4& rhs) { return ulong4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

	/// <summary>Returns the result of a componentwise increment operation on a ulong4 vector.</summary>

	inline static ulong4 operator ++ (ulong4 val) { return ulong4(++val.x, ++val.y, ++val.z, ++val.w); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong4 vector.</summary>

	inline static ulong4 operator -- (ulong4 val) { return ulong4(--val.x, --val.y, --val.z, --val.w); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong4 vectors.</summary>

	inline static bool4 operator < (const ulong4& lhs, const ulong4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong4 vector and a ulong value.</summary>

	inline static bool4 operator < (const ulong4& lhs, ulong rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong4 vector.</summary>

	inline static bool4 operator < (ulong lhs, const ulong4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong4 vectors.</summary>

	inline static bool4 operator <= (const ulong4& lhs, const ulong4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong4 vector and a ulong value.</summary>

	inline static bool4 operator <= (const ulong4& lhs, ulong rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong4 vector.</summary>

	inline static bool4 operator <= (ulong lhs, const ulong4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong4 vectors.</summary>

	inline static bool4 operator > (const ulong4& lhs, const ulong4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong4 vector and a ulong value.</summary>

	inline static bool4 operator > (const ulong4& lhs, ulong rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong4 vector.</summary>

	inline static bool4 operator > (ulong lhs, const ulong4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong4 vectors.</summary>

	inline static bool4 operator >= (const ulong4& lhs, const ulong4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong4 vector and a ulong value.</summary>

	inline static bool4 operator >= (const ulong4& lhs, ulong rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong4 vector.</summary>

	inline static bool4 operator >= (ulong lhs, const ulong4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }


	/// <summary>Returns the result of a componentwise equality operation on two ulong4 vectors.</summary>

	inline static bool4 operator == (const ulong4& lhs, const ulong4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong4 vector and a ulong value.</summary>

	inline static bool4 operator == (const ulong4& lhs, ulong rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong4 vector.</summary>

	inline static bool4 operator == (ulong lhs, const ulong4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong4 vectors.</summary>

	inline static bool4 operator != (const ulong4& lhs, const ulong4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong4 vector and a ulong value.</summary>

	inline static bool4 operator != (const ulong4& lhs, ulong rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong4 vector.</summary>

	inline static bool4 operator != (ulong lhs, const ulong4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region ulong4x2
	struct ulong4x2
	{
		ulong4 c0, c1;
		ulong4x2() : c0(), c1() {}
		ulong4x2(ulong m00, ulong m01,
			ulong m10, ulong m11,
			ulong m20, ulong m21,
			ulong m30, ulong m31)
		{
			c0 = ulong4(m00, m10, m20, m30);
			c1 = ulong4(m01, m11, m21, m31);
		}
		ulong4x2(ulong4 c0, ulong4 c1) : c0(c0), c1(c1) {}
		ulong4x2(ulong v) : c0(v), c1(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong4x2 matrices.</summary>

	inline static ulong4x2 operator * (const ulong4x2& lhs, const ulong4x2& rhs) { return ulong4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static ulong4x2 operator * (const ulong4x2& lhs, ulong rhs) { return ulong4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static ulong4x2 operator * (ulong lhs, const ulong4x2& rhs) { return ulong4x2(lhs * rhs.c0, lhs * rhs.c1); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong4x2 matrices.</summary>

	inline static ulong4x2 operator + (const ulong4x2& lhs, const ulong4x2& rhs) { return ulong4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static ulong4x2 operator + (const ulong4x2& lhs, ulong rhs) { return ulong4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static ulong4x2 operator + (ulong lhs, const ulong4x2& rhs) { return ulong4x2(lhs + rhs.c0, lhs + rhs.c1); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong4x2 matrices.</summary>

	inline static ulong4x2 operator - (const ulong4x2& lhs, const ulong4x2& rhs) { return ulong4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static ulong4x2 operator - (const ulong4x2& lhs, ulong rhs) { return ulong4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static ulong4x2 operator - (ulong lhs, const ulong4x2& rhs) { return ulong4x2(lhs - rhs.c0, lhs - rhs.c1); }


	/// <summary>Returns the result of a componentwise division operation on two ulong4x2 matrices.</summary>

	inline static ulong4x2 operator / (const ulong4x2& lhs, const ulong4x2& rhs) { return ulong4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

	/// <summary>Returns the result of a componentwise division operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static ulong4x2 operator / (const ulong4x2& lhs, ulong rhs) { return ulong4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static ulong4x2 operator / (ulong lhs, const ulong4x2& rhs) { return ulong4x2(lhs / rhs.c0, lhs / rhs.c1); }

	/// <summary>Returns the result of a componentwise increment operation on a ulong4x2 matrix.</summary>

	inline static ulong4x2 operator ++ (ulong4x2 val) { return ulong4x2(++val.c0, ++val.c1); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong4x2 matrix.</summary>

	inline static ulong4x2 operator -- (ulong4x2 val) { return ulong4x2(--val.c0, --val.c1); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong4x2 matrices.</summary>

	inline static bool4x2 operator < (const ulong4x2& lhs, const ulong4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static bool4x2 operator < (const ulong4x2& lhs, ulong rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static bool4x2 operator < (ulong lhs, const ulong4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong4x2 matrices.</summary>

	inline static bool4x2 operator <= (const ulong4x2& lhs, const ulong4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static bool4x2 operator <= (const ulong4x2& lhs, ulong rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static bool4x2 operator <= (ulong lhs, const ulong4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong4x2 matrices.</summary>

	inline static bool4x2 operator > (const ulong4x2& lhs, const ulong4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static bool4x2 operator > (const ulong4x2& lhs, ulong rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static bool4x2 operator > (ulong lhs, const ulong4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong4x2 matrices.</summary>

	inline static bool4x2 operator >= (const ulong4x2& lhs, const ulong4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static bool4x2 operator >= (const ulong4x2& lhs, ulong rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static bool4x2 operator >= (ulong lhs, const ulong4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


	/// <summary>Returns the result of a componentwise equality operation on two ulong4x2 matrices.</summary>

	inline static bool4x2 operator == (const ulong4x2& lhs, const ulong4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static bool4x2 operator == (const ulong4x2& lhs, ulong rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static bool4x2 operator == (ulong lhs, const ulong4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong4x2 matrices.</summary>

	inline static bool4x2 operator != (const ulong4x2& lhs, const ulong4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong4x2 matrix and a ulong value.</summary>

	inline static bool4x2 operator != (const ulong4x2& lhs, ulong rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong4x2 matrix.</summary>

	inline static bool4x2 operator != (ulong lhs, const ulong4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region ulong4x3
	struct ulong4x3
	{
		ulong4 c0, c1, c2;
		ulong4x3() : c0(), c1(), c2() {}
		ulong4x3(ulong m00, ulong m01, ulong m02,
			ulong m10, ulong m11, ulong m12,
			ulong m20, ulong m21, ulong m22,
			ulong m30, ulong m31, ulong m32)
		{
			c0 = ulong4(m00, m10, m20, m30);
			c1 = ulong4(m01, m11, m21, m31);
			c2 = ulong4(m02, m12, m22, m32);
		}
		ulong4x3(ulong4 c0, ulong4 c1, ulong4 c2) : c0(c0), c1(c1), c2(c2) {}
		ulong4x3(ulong v) : c0(v), c1(v), c2(v) {}
	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong4x3 matrices.</summary>

	inline static ulong4x3 operator * (const ulong4x3& lhs, const ulong4x3& rhs) { return ulong4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static ulong4x3 operator * (const ulong4x3& lhs, ulong rhs) { return ulong4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static ulong4x3 operator * (ulong lhs, const ulong4x3& rhs) { return ulong4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong4x3 matrices.</summary>

	inline static ulong4x3 operator + (const ulong4x3& lhs, const ulong4x3& rhs) { return ulong4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static ulong4x3 operator + (const ulong4x3& lhs, ulong rhs) { return ulong4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static ulong4x3 operator + (ulong lhs, const ulong4x3& rhs) { return ulong4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong4x3 matrices.</summary>

	inline static ulong4x3 operator - (const ulong4x3& lhs, const ulong4x3& rhs) { return ulong4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static ulong4x3 operator - (const ulong4x3& lhs, ulong rhs) { return ulong4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static ulong4x3 operator - (ulong lhs, const ulong4x3& rhs) { return ulong4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


	/// <summary>Returns the result of a componentwise division operation on two ulong4x3 matrices.</summary>

	inline static ulong4x3 operator / (const ulong4x3& lhs, const ulong4x3& rhs) { return ulong4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

	/// <summary>Returns the result of a componentwise division operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static ulong4x3 operator / (const ulong4x3& lhs, ulong rhs) { return ulong4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static ulong4x3 operator / (ulong lhs, const ulong4x3& rhs) { return ulong4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

	/// <summary>Returns the result of a componentwise increment operation on a ulong4x3 matrix.</summary>

	inline static ulong4x3 operator ++ (ulong4x3 val) { return ulong4x3(++val.c0, ++val.c1, ++val.c2); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong4x3 matrix.</summary>

	inline static ulong4x3 operator -- (ulong4x3 val) { return ulong4x3(--val.c0, --val.c1, --val.c2); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong4x3 matrices.</summary>

	inline static bool4x3 operator < (const ulong4x3& lhs, const ulong4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static bool4x3 operator < (const ulong4x3& lhs, ulong rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static bool4x3 operator < (ulong lhs, const ulong4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong4x3 matrices.</summary>

	inline static bool4x3 operator <= (const ulong4x3& lhs, const ulong4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static bool4x3 operator <= (const ulong4x3& lhs, ulong rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static bool4x3 operator <= (ulong lhs, const ulong4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong4x3 matrices.</summary>

	inline static bool4x3 operator > (const ulong4x3& lhs, const ulong4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static bool4x3 operator > (const ulong4x3& lhs, ulong rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static bool4x3 operator > (ulong lhs, const ulong4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong4x3 matrices.</summary>

	inline static bool4x3 operator >= (const ulong4x3& lhs, const ulong4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static bool4x3 operator >= (const ulong4x3& lhs, ulong rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static bool4x3 operator >= (ulong lhs, const ulong4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong4x3 matrices.</summary>

	inline static bool4x3 operator == (const ulong4x3& lhs, const ulong4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static bool4x3 operator == (const ulong4x3& lhs, ulong rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static bool4x3 operator == (ulong lhs, const ulong4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong4x3 matrices.</summary>

	inline static bool4x3 operator != (const ulong4x3& lhs, const ulong4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong4x3 matrix and a ulong value.</summary>

	inline static bool4x3 operator != (const ulong4x3& lhs, ulong rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong4x3 matrix.</summary>

	inline static bool4x3 operator != (ulong lhs, const ulong4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region ulong4x4
	struct ulong4x4
	{
		ulong4 c0, c1, c2, c3;
		ulong4x4() : c0(), c1(), c2(), c3() {}
		ulong4x4(ulong m00, ulong m01, ulong m02, ulong m03,
			ulong m10, ulong m11, ulong m12, ulong m13,
			ulong m20, ulong m21, ulong m22, ulong m23,
			ulong m30, ulong m31, ulong m32, ulong m33)
		{
			c0 = ulong4(m00, m10, m20, m30);
			c1 = ulong4(m01, m11, m21, m31);
			c2 = ulong4(m02, m12, m22, m32);
			c3 = ulong4(m03, m13, m23, m33);
		}
		ulong4x4(ulong4 c0, ulong4 c1, ulong4 c2, ulong4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
		ulong4x4(ulong v) : c0(v), c1(v), c2(v), c3(v) {}

		ulong4x4(ulong3x3 rotation, ulong3 translation)
		{
			c0 = ulong4(rotation.c0, 0.0f);
			c1 = ulong4(rotation.c1, 0.0f);
			c2 = ulong4(rotation.c2, 0.0f);
			c3 = ulong4(translation, 1.0f);
		}


	};


	/// <summary>Returns the result of a componentwise multiplication operation on two ulong4x4 matrices.</summary>

	inline static ulong4x4 operator * (const ulong4x4& lhs, const ulong4x4& rhs) { return ulong4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static ulong4x4 operator * (const ulong4x4& lhs, ulong rhs) { return ulong4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

	/// <summary>Returns the result of a componentwise multiplication operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static ulong4x4 operator * (ulong lhs, const ulong4x4& rhs) { return ulong4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


	/// <summary>Returns the result of a componentwise addition operation on two ulong4x4 matrices.</summary>

	inline static ulong4x4 operator + (const ulong4x4& lhs, const ulong4x4& rhs) { return ulong4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static ulong4x4 operator + (const ulong4x4& lhs, ulong rhs) { return ulong4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

	/// <summary>Returns the result of a componentwise addition operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static ulong4x4 operator + (ulong lhs, const ulong4x4& rhs) { return ulong4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


	/// <summary>Returns the result of a componentwise subtraction operation on two ulong4x4 matrices.</summary>

	inline static ulong4x4 operator - (const ulong4x4& lhs, const ulong4x4& rhs) { return ulong4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static ulong4x4 operator - (const ulong4x4& lhs, ulong rhs) { return ulong4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

	/// <summary>Returns the result of a componentwise subtraction operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static ulong4x4 operator - (ulong lhs, const ulong4x4& rhs) { return ulong4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


	/// <summary>Returns the result of a componentwise division operation on two ulong4x4 matrices.</summary>

	inline static ulong4x4 operator / (const ulong4x4& lhs, const ulong4x4& rhs) { return ulong4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

	/// <summary>Returns the result of a componentwise division operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static ulong4x4 operator / (const ulong4x4& lhs, ulong rhs) { return ulong4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

	/// <summary>Returns the result of a componentwise division operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static ulong4x4 operator / (ulong lhs, const ulong4x4& rhs) { return ulong4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


	/// <summary>Returns the result of a componentwise increment operation on a ulong4x4 matrix.</summary>

	inline static ulong4x4 operator ++ (ulong4x4 val) { return ulong4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


	/// <summary>Returns the result of a componentwise decrement operation on a ulong4x4 matrix.</summary>

	inline static ulong4x4 operator -- (ulong4x4 val) { return ulong4x4(--val.c0, --val.c1, --val.c2, --val.c3); }


	/// <summary>Returns the result of a componentwise less than operation on two ulong4x4 matrices.</summary>

	inline static bool4x4 operator < (const ulong4x4& lhs, const ulong4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static bool4x4 operator < (const ulong4x4& lhs, ulong rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

	/// <summary>Returns the result of a componentwise less than operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static bool4x4 operator < (ulong lhs, const ulong4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


	/// <summary>Returns the result of a componentwise less or equal operation on two ulong4x4 matrices.</summary>

	inline static bool4x4 operator <= (const ulong4x4& lhs, const ulong4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static bool4x4 operator <= (const ulong4x4& lhs, ulong rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

	/// <summary>Returns the result of a componentwise less or equal operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static bool4x4 operator <= (ulong lhs, const ulong4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


	/// <summary>Returns the result of a componentwise greater than operation on two ulong4x4 matrices.</summary>

	inline static bool4x4 operator > (const ulong4x4& lhs, const ulong4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static bool4x4 operator > (const ulong4x4& lhs, ulong rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

	/// <summary>Returns the result of a componentwise greater than operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static bool4x4 operator > (ulong lhs, const ulong4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


	/// <summary>Returns the result of a componentwise greater or equal operation on two ulong4x4 matrices.</summary>

	inline static bool4x4 operator >= (const ulong4x4& lhs, const ulong4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static bool4x4 operator >= (const ulong4x4& lhs, ulong rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

	/// <summary>Returns the result of a componentwise greater or equal operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static bool4x4 operator >= (ulong lhs, const ulong4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on two ulong4x4 matrices.</summary>

	inline static bool4x4 operator == (const ulong4x4& lhs, const ulong4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static bool4x4 operator == (const ulong4x4& lhs, ulong rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

	/// <summary>Returns the result of a componentwise equality operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static bool4x4 operator == (ulong lhs, const ulong4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


	/// <summary>Returns the result of a componentwise not equal operation on two ulong4x4 matrices.</summary>

	inline static bool4x4 operator != (const ulong4x4& lhs, const ulong4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong4x4 matrix and a ulong value.</summary>

	inline static bool4x4 operator != (const ulong4x4& lhs, ulong rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

	/// <summary>Returns the result of a componentwise not equal operation on a ulong value and a ulong4x4 matrix.</summary>

	inline static bool4x4 operator != (ulong lhs, const ulong4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic


	/// <summary>Returns the Tangent of a ulong value.</summary>
	inline static ulong Tan(ulong x) { return (ulong)tan(x); }

	/// <summary>Returns the componentwise Tangent of a ulong2 vector.</summary>
	inline static ulong2 Tan(ulong2 x) { return ulong2(Tan(x.x), Tan(x.y)); }

	/// <summary>Returns the componentwise Tangent of a ulong3 vector.</summary>
	inline static ulong3 Tan(ulong3 x) { return ulong3(Tan(x.x), Tan(x.y), Tan(x.z)); }

	/// <summary>Returns the componentwise Tangent of a ulong4 vector.</summary>
	inline static ulong4 Tan(ulong4 x) { return ulong4(Tan(x.x), Tan(x.y), Tan(x.z), Tan(x.w)); }


	/// <summary>Returns the hyperbolic Tangent of a ulong value.</summary>
	inline static ulong Tanh(ulong x) { return (ulong)tanh(x); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a ulong2 vector.</summary>
	inline static ulong2 Tanh(ulong2 x) { return ulong2(Tanh(x.x), Tanh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a ulong3 vector.</summary>
	inline static ulong3 Tanh(ulong3 x) { return ulong3(Tanh(x.x), Tanh(x.y), Tanh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Tangent of a ulong4 vector.</summary>
	inline static ulong4 Tanh(ulong4 x) { return ulong4(Tanh(x.x), Tanh(x.y), Tanh(x.z), Tanh(x.w)); }


	/// <summary>Returns the arcTangent of a ulong value.</summary>
	inline static ulong Atan(ulong x) { return (ulong)atan(x); }

	/// <summary>Returns the componentwise arcTangent of a ulong2 vector.</summary>
	inline static ulong2 Atan(ulong2 x) { return ulong2(Atan(x.x), Atan(x.y)); }

	/// <summary>Returns the componentwise arcTangent of a ulong3 vector.</summary>
	inline static ulong3 Atan(ulong3 x) { return ulong3(Atan(x.x), Atan(x.y), Atan(x.z)); }

	/// <summary>Returns the componentwise arcTangent of a ulong4 vector.</summary>
	inline static ulong4 Atan(ulong4 x) { return ulong4(Atan(x.x), Atan(x.y), Atan(x.z), Atan(x.w)); }


	/// <summary>Returns the 2-argument arcTangent of a pair of ulong values.</summary>
	inline static ulong Atan2(ulong y, ulong x) { return (ulong)atan2(y, x); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of ulongs2 vectors.</summary>
	inline static ulong2 Atan2(ulong2 y, ulong2 x) { return ulong2(Atan2(y.x, x.x), Atan2(y.y, x.y)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of ulongs3 vectors.</summary>
	inline static ulong3 Atan2(ulong3 y, ulong3 x) { return ulong3(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z)); }

	/// <summary>Returns the componentwise 2-argument arcTangent of a pair of ulongs4 vectors.</summary>
	inline static ulong4 Atan2(ulong4 y, ulong4 x) { return ulong4(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z), Atan2(y.w, x.w)); }


	/// <summary>Returns the CoSine of a ulong value.</summary>
	inline static ulong Cos(ulong x) { return (ulong)cos(x); }

	/// <summary>Returns the componentwise CoSine of a ulong2 vector.</summary>
	inline static ulong2 Cos(ulong2 x) { return ulong2(Cos(x.x), Cos(x.y)); }

	/// <summary>Returns the componentwise CoSine of a ulong3 vector.</summary>
	inline static ulong3 Cos(ulong3 x) { return ulong3(Cos(x.x), Cos(x.y), Cos(x.z)); }

	/// <summary>Returns the componentwise CoSine of a ulong4 vector.</summary>
	inline static ulong4 Cos(ulong4 x) { return ulong4(Cos(x.x), Cos(x.y), Cos(x.z), Cos(x.w)); }


	/// <summary>Returns the hyperbolic CoSine of a ulong value.</summary>
	inline static ulong Cosh(ulong x) { return (ulong)cosh(x); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a ulong2 vector.</summary>
	inline static ulong2 Cosh(ulong2 x) { return ulong2(Cosh(x.x), Cosh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a ulong3 vector.</summary>
	inline static ulong3 Cosh(ulong3 x) { return ulong3(Cosh(x.x), Cosh(x.y), Cosh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic CoSine of a ulong4 vector.</summary>
	inline static ulong4 Cosh(ulong4 x) { return ulong4(Cosh(x.x), Cosh(x.y), Cosh(x.z), Cosh(x.w)); }

	/// <summary>Returns the arcCoSine of a ulong value.</summary>
	inline static ulong Acos(ulong x) { return (ulong)acos((ulong)x); }

	/// <summary>Returns the componentwise arcCoSine of a ulong2 vector.</summary>
	inline static ulong2 Acos(ulong2 x) { return ulong2(Acos(x.x), Acos(x.y)); }

	/// <summary>Returns the componentwise arcCoSine of a ulong3 vector.</summary>
	inline static ulong3 Acos(ulong3 x) { return ulong3(Acos(x.x), Acos(x.y), Acos(x.z)); }

	/// <summary>Returns the componentwise arcCoSine of a ulong4 vector.</summary>
	inline static ulong4 Acos(ulong4 x) { return ulong4(Acos(x.x), Acos(x.y), Acos(x.z), Acos(x.w)); }


	/// <summary>Returns the Sine of a ulong value.</summary>
	inline static ulong Sin(ulong x) { return (ulong)sin((ulong)x); }

	/// <summary>Returns the componentwise Sine of a ulong2 vector.</summary>
	inline static ulong2 Sin(ulong2 x) { return ulong2(Sin(x.x), Sin(x.y)); }

	/// <summary>Returns the componentwise Sine of a ulong3 vector.</summary>
	inline static ulong3 Sin(ulong3 x) { return ulong3(Sin(x.x), Sin(x.y), Sin(x.z)); }

	/// <summary>Returns the componentwise Sine of a ulong4 vector.</summary>
	inline static ulong4 Sin(ulong4 x) { return ulong4(Sin(x.x), Sin(x.y), Sin(x.z), Sin(x.w)); }



	/// <summary>Returns the hyperbolic Sine of a ulong value.</summary>
	inline static ulong Sinh(ulong x) { return (ulong)sinh((ulong)x); }

	/// <summary>Returns the componentwise hyperbolic Sine of a ulong2 vector.</summary>
	inline static ulong2 Sinh(ulong2 x) { return ulong2(Sinh(x.x), Sinh(x.y)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a ulong3 vector.</summary>
	inline static ulong3 Sinh(ulong3 x) { return ulong3(Sinh(x.x), Sinh(x.y), Sinh(x.z)); }

	/// <summary>Returns the componentwise hyperbolic Sine of a ulong4 vector.</summary>
	inline static ulong4 Sinh(ulong4 x) { return ulong4(Sinh(x.x), Sinh(x.y), Sinh(x.z), Sinh(x.w)); }


	/// <summary>Returns the arcSine of a ulong value.</summary>
	inline static ulong Asin(ulong x) { return (ulong)asin((ulong)x); }

	/// <summary>Returns the componentwise arcSine of a ulong2 vector.</summary>
	inline static ulong2 Asin(ulong2 x) { return ulong2(Asin(x.x), Asin(x.y)); }

	/// <summary>Returns the componentwise arcSine of a ulong3 vector.</summary>
	inline static ulong3 Asin(ulong3 x) { return ulong3(Asin(x.x), Asin(x.y), Asin(x.z)); }

	/// <summary>Returns the componentwise arcSine of a ulong4 vector.</summary>
	inline static ulong4 Asin(ulong4 x) { return ulong4(Asin(x.x), Asin(x.y), Asin(x.z), Asin(x.w)); }


	/// <summary>Returns the Dot product of two ulong values. Equivalent to multiplication.</summary>
	inline static ulong Dot(ulong x, ulong y) { return x * y; }

	/// <summary>Returns the Dot product of two ulong2 vectors.</summary>
	inline static ulong Dot(ulong2 x, ulong2 y) { return x.x * y.x + x.y * y.y; }

	/// <summary>Returns the Dot product of two ulong3 vectors.</summary>
	inline static ulong Dot(ulong3 x, ulong3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }

	/// <summary>Returns the Dot product of two ulong4 vectors.</summary>
	inline static ulong Dot(ulong4 x, ulong4 y) { return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w; }

	/// <summary>Returns the square root of a ulong value.</summary>
	inline static ulong Sqrt(ulong x) { return sqrt((double)x); }

	/// <summary>Returns the componentwise square root of a ulong2 vector.</summary>
	inline static ulong2 Sqrt(ulong2 x) { return ulong2(Sqrt(x.x), Sqrt(x.y)); }

	/// <summary>Returns the componentwise square root of a ulong3 vector.</summary>
	inline static ulong3 Sqrt(ulong3 x) { return ulong3(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z)); }

	/// <summary>Returns the componentwise square root of a ulong4 vector.</summary>
	inline static ulong4 Sqrt(ulong4 x) { return ulong4(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z), Sqrt(x.w)); }


	/// <summary>Returns the reciprocal square root of a ulong value.</summary>
	inline static ulong Rsqrt(ulong x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a ulong2 vector.</summary>
	inline static ulong2 Rsqrt(ulong2 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a ulong3 vector.</summary>
	inline static ulong3 Rsqrt(ulong3 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns the componentwise reciprocal square root of a ulong4 vector</summary>
	inline static ulong4 Rsqrt(ulong4 x) { return 1.0f / Sqrt(x); }

	/// <summary>Returns a Normalized version of the ulong2 vector x by scaling it by 1 / Length(x).</summary>
	inline static ulong2 Normalize(ulong2 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the ulong3 vector x by scaling it by 1 / Length(x).</summary>
	inline static ulong3 Normalize(ulong3 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns a Normalized version of the ulong4 vector x by scaling it by 1 / Length(x).</summary>
	inline static ulong4 Normalize(ulong4 x) { return Rsqrt(Dot(x, x)) * x; }

	/// <summary>Returns the Length of a ulong2 vector.</summary>
	inline static ulong Length(ulong2 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a ulong3 vector.</summary>
	inline static ulong Length(ulong3 x) { return sqrt(Dot(x, x)); }

	/// <summary>Returns the Length of a ulong4 vector.</summary>
	inline static ulong Length(ulong4 x) { return sqrt(Dot(x, x)); }




	/// <summary>Returns the squared Length of a ulong value. Equivalent to squaring the value.</summary>
	inline static ulong Lengthsq(ulong x) { return x * x; }

	/// <summary>Returns the squared Length of a ulong2 vector.</summary>
	inline static ulong Lengthsq(ulong2 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a ulong3 vector.</summary>
	inline static ulong Lengthsq(ulong3 x) { return Dot(x, x); }

	/// <summary>Returns the squared Length of a ulong4 vector.</summary>
	inline static ulong Lengthsq(ulong4 x) { return Dot(x, x); }


	/// <summary>Returns the Distance between two ulong2 vectors.</summary>
	inline static ulong Distance(ulong2 x, ulong2 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two ulong3 vectors.</summary>
	inline static ulong Distance(ulong3 x, ulong3 y) { return Length(y - x); }

	/// <summary>Returns the Distance between two ulong4 vectors.</summary>
	inline static ulong Distance(ulong4 x, ulong4 y) { return Length(y - x); }



	/// <summary>Returns the Distance between two ulong values.</summary>
	inline static ulong Distancesq(ulong x, ulong y) { return (y - x) * (y - x); }

	/// <summary>Returns the Distance between two ulong2 vectors.</summary>
	inline static ulong Distancesq(ulong2 x, ulong2 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two ulong3 vectors.</summary>
	inline static ulong Distancesq(ulong3 x, ulong3 y) { return Lengthsq(y - x); }

	/// <summary>Returns the Distance between two ulong4 vectors.</summary>
	inline static ulong Distancesq(ulong4 x, ulong4 y) { return Lengthsq(y - x); }



	/// <summary>Returns the Cross product of two ulong3 vectors.</summary>
	inline static ulong3 Cross(ulong3 x, ulong3 y) {
		ulong3 retVal = x * ulong3(y.y, y.z, y.x) - ulong3(x.y, x.z, x.x) * y;
		return ulong3(retVal.y, retVal.z, retVal.x);
	}

	/// <summary>Returns the Sine and CoSine of the input ulong value x through the out parameters s and c.</summary>
	inline static void SinCos(ulong x, ulong* s, ulong* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input ulong2 vector x through the out parameters s and c.</summary>
	inline static void SinCos(ulong2 x, ulong2* s, ulong2* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input ulong3 vector x through the out parameters s and c.</summary>
	inline static void SinCos(ulong3 x, ulong3* s, ulong3* c) { *s = Sin(x); *c = Cos(x); }

	/// <summary>Returns the componentwise Sine and CoSine of the input ulong4 vector x through the out parameters s and c.</summary>
	inline static void SinCos(ulong4 x, ulong4* s, ulong4* c) { *s = Sin(x); *c = Cos(x); }


	/// <summary>Returns the Minimum of two ulong values.</summary>
	inline static ulong Min(ulong x, ulong y) { return x < y ? x : y; }

	/// <summary>Returns the componentwise Minimum of two ulong2 vectors.</summary>
	inline static ulong2 Min(ulong2 x, ulong2 y) { return ulong2(Min(x.x, y.x), Min(x.y, y.y)); }

	/// <summary>Returns the componentwise Minimum of two ulong3 vectors.</summary>
	inline static ulong3 Min(ulong3 x, ulong3 y) { return ulong3(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z)); }

	/// <summary>Returns the componentwise Minimum of two ulong4 vectors.</summary>
	inline static ulong4 Min(ulong4 x, ulong4 y) { return ulong4(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z), Min(x.w, y.w)); }


	/// <summary>Returns the Maximum of two ulong values.</summary>
	inline static ulong Max(ulong x, ulong y) { return x > y ? x : y; }

	/// <summary>Returns the componentwise Maximum of two ulong2 vectors.</summary>
	inline static ulong2 Max(ulong2 x, ulong2 y) { return ulong2(Max(x.x, y.x), Max(x.y, y.y)); }

	/// <summary>Returns the componentwise Maximum of two ulong3 vectors.</summary>
	inline static ulong3 Max(ulong3 x, ulong3 y) { return ulong3(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z)); }

	/// <summary>Returns the componentwise Maximum of two ulong4 vectors.</summary>
	inline static ulong4 Max(ulong4 x, ulong4 y) { return ulong4(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z), Max(x.w, y.w)); }

	inline static ulong Lerp(ulong x, ulong y, ulong s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static ulong2 Lerp(ulong2 x, ulong2 y, ulong s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static ulong3 Lerp(ulong3 x, ulong3 y, ulong s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
	inline static ulong4 Lerp(ulong4 x, ulong4 y, ulong s) { return x + s * (y - x); }


	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static ulong2 Lerp(ulong2 x, ulong2 y, ulong2 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static ulong3 Lerp(ulong3 x, ulong3 y, ulong3 s) { return x + s * (y - x); }

	/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
	inline static ulong4 Lerp(ulong4 x, ulong4 y, ulong4 s) { return x + s * (y - x); }

	/// <summary>Returns the result of normalizing a ulonging point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static ulong Unlerp(ulong a, ulong b, ulong x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a ulonging point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static ulong2 Unlerp(ulong2 a, ulong2 b, ulong2 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a ulonging point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static ulong3 Unlerp(ulong3 a, ulong3 b, ulong3 x) { return (x - a) / (b - a); }

	/// <summary>Returns the componentwise result of normalizing a ulonging point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
	inline static ulong4 Unlerp(ulong4 a, ulong4 b, ulong4 x) { return (x - a) / (b - a); }

	/// <summary>Returns the result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static ulong Remap(ulong a, ulong b, ulong c, ulong d, ulong x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static ulong2 Remap(ulong2 a, ulong2 b, ulong2 c, ulong2 d, ulong2 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static ulong3 Remap(ulong3 a, ulong3 b, ulong3 c, ulong3 d, ulong3 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
	inline static ulong4 Remap(ulong4 a, ulong4 b, ulong4 c, ulong4 d, ulong4 x) { return Lerp(c, d, Unlerp(a, b, x)); }

	/// <summary>Returns the result of Clamping the value x into the interval [a, b], where x, a and b are ulong values.</summary>
	inline static ulong Clamp(ulong x, ulong a, ulong b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are ulong2 vectors.</summary>
	inline static ulong2 Clamp(ulong2 x, ulong2 a, ulong2 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are ulong3 vectors.</summary>
	inline static ulong3 Clamp(ulong3 x, ulong3 a, ulong3 b) { return Max(a, Min(b, x)); }

	/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are ulong4 vectors.</summary>
	inline static ulong4 Clamp(ulong4 x, ulong4 a, ulong4 b) { return Max(a, Min(b, x)); }

	inline static ulong select_shuffle_component(ulong4 a, ulong4 b, char component)
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

	inline static ulong4 shuffle(ulong4 a, ulong4 b, char x, char y, char z, char w)
	{
		return ulong4(
			select_shuffle_component(a, b, x),
			select_shuffle_component(a, b, y),
			select_shuffle_component(a, b, z),
			select_shuffle_component(a, b, w));
	}

	inline static ulong4 movelh(ulong4 a, ulong4 b)
	{
		return shuffle(a, b, 0, 1, 4, 5);
	}
	inline static ulong4 movehl(ulong4 a, ulong4 b)
	{
		return shuffle(b, a, 2, 3, 6, 7);
	}
	// SSE shuffles
	inline static ulong4 unpacklo(ulong4 a, ulong4 b)
	{
		return shuffle(a, b, 0, 4, 1, 5);
	}
	inline static ulong4 unpackhi(ulong4 a, ulong4 b)
	{
		return shuffle(a, b, 2, 6, 3, 7);
	}
#pragma endregion
#pragma region Component
	/// <summary>Returns the Maximum component of a ulong2 vector.</summary>
	inline static ulong CMax(ulong2 x) { return Max(x.x, x.y); }

	/// <summary>Returns the Maximum component of a ulong3 vector.</summary>
	inline static ulong CMax(ulong3 x) { return Max(Max(x.x, x.y), x.z); }

	/// <summary>Returns the Maximum component of a ulong4 vector.</summary>
	inline static ulong CMax(ulong4 x) { return Max(Max(x.x, x.y), Max(x.z, x.w)); }

	/// <summary>Returns the horizontal sum of components of a ulong2 vector.</summary>
	inline static ulong Csum(ulong2 x) { return x.x + x.y; }

	/// <summary>Returns the horizontal sum of components of a ulong3 vector.</summary>
	inline static ulong Csum(ulong3 x) { return x.x + x.y + x.z; }

	/// <summary>Returns the horizontal sum of components of a ulong4 vector.</summary>
	inline static ulong Csum(ulong4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion

#pragma region Transpose
	/// <summary>Return the ulong2x2 Transpose of a ulong2x2 matrix.</summary>
	inline ulong2x2 Transpose(ulong2x2 v)
	{
		return ulong2x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y);
	}
	/// <summary>Return the ulong3x2 Transpose of a ulong2x3 matrix.</summary>
	inline ulong3x2 Transpose(ulong2x3 v)
	{
		return ulong3x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y);
	}
	/// <summary>Return the ulong4x2 Transpose of a ulong2x4 matrix.</summary>
	inline ulong4x2 Transpose(ulong2x4 v)
	{
		return ulong4x2(
			v.c0.x, v.c0.y,
			v.c1.x, v.c1.y,
			v.c2.x, v.c2.y,
			v.c3.x, v.c3.y);
	}
	/// <summary>Return the ulong2x3 Transpose of a ulong3x2 matrix.</summary>
	inline ulong2x3 Transpose(ulong3x2 v)
	{
		return ulong2x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z);
	}
	/// <summary>Return the ulong3x3 Transpose of a ulong3x3 matrix.</summary>
	inline ulong3x3 Transpose(ulong3x3 v)
	{
		return ulong3x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z);
	}
	/// <summary>Return the ulong4x3 Transpose of a ulong3x4 matrix.</summary>
	inline static ulong4x3 Transpose(ulong3x4 v)
	{
		return ulong4x3(
			v.c0.x, v.c0.y, v.c0.z,
			v.c1.x, v.c1.y, v.c1.z,
			v.c2.x, v.c2.y, v.c2.z,
			v.c3.x, v.c3.y, v.c3.z);
	}
	/// <summary>Return the ulong2x4 Transpose of a ulong4x2 matrix.</summary>
	inline static ulong2x4 Transpose(ulong4x2 v)
	{
		return ulong2x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w);
	}
	/// <summary>Return the ulong3x4 Transpose of a ulong4x3 matrix.</summary>
	inline static ulong3x4 Transpose(ulong4x3 v)
	{
		return ulong3x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w);
	}
	/// <summary>Return the ulong4x4 Transpose of a ulong4x4 matrix.</summary>
	inline static ulong4x4 Transpose(ulong4x4 v)
	{
		return ulong4x4(
			v.c0.x, v.c0.y, v.c0.z, v.c0.w,
			v.c1.x, v.c1.y, v.c1.z, v.c1.w,
			v.c2.x, v.c2.y, v.c2.z, v.c2.w,
			v.c3.x, v.c3.y, v.c3.z, v.c3.w);
	}

#pragma endregion
#pragma region Inverse

	/// <summary>Returns the ulong4x4 full Inverse of a ulong4x4 matrix.</summary>
	inline static ulong4x4 Inverse(ulong4x4 m)
	{
		ulong4 c0 = m.c0;
		ulong4 c1 = m.c1;
		ulong4 c2 = m.c2;
		ulong4 c3 = m.c3;

		ulong4 r0y_r1y_r0x_r1x = movelh(c1, c0);
		ulong4 r0z_r1z_r0w_r1w = movelh(c2, c3);
		ulong4 r2y_r3y_r2x_r3x = movehl(c0, c1);
		ulong4 r2z_r3z_r2w_r3w = movehl(c3, c2);

		ulong4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
		ulong4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
		ulong4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
		ulong4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

		ulong4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
		ulong4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
		ulong4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
		ulong4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
		ulong4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

		// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
		ulong4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
		ulong4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
		ulong4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

		// Expand inner terms back to 4 components. zw signs still need to be flipped
		ulong4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
		ulong4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

		ulong4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
		ulong4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

		// Calculate Minors
		ulong4 Minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

		ulong4 denom = r0_xyzw * Minors0;

		// Horizontal sum of denoMinator. Free sign flip of z and w compensates for misSing flip in inner terms.
		denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
		denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

		ulong4 rcp_denom_ppnn = ulong4(1.0f) / denom;
		ulong4x4 res;
		res.c0 = Minors0 * rcp_denom_ppnn;

		ulong4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
		ulong4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

		ulong4 Minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
		res.c1 = Minors1 * rcp_denom_ppnn;

		ulong4 Minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
		res.c2 = Minors2 * rcp_denom_ppnn;

		ulong4 Minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
		res.c3 = Minors3 * rcp_denom_ppnn;
		return res;
	}
#pragma endregion
#pragma region Determinant
	/// <summary>Returns the Determinant of a ulong2x2 matrix.</summary>
	inline ulong Determinant(ulong2x2 m)
	{
		ulong a = m.c0.x;
		ulong b = m.c1.x;
		ulong c = m.c0.y;
		ulong d = m.c1.y;

		return a * d - b * c;
	}
	/// <summary>Returns the Determinant of a ulong3x3 matrix.</summary>
	inline ulong Determinant(ulong3x3 m)
	{
		ulong3 c0 = m.c0;
		ulong3 c1 = m.c1;
		ulong3 c2 = m.c2;

		ulong m00 = c1.y * c2.z - c1.z * c2.y;
		ulong m01 = c0.y * c2.z - c0.z * c2.y;
		ulong m02 = c0.y * c1.z - c0.z * c1.y;

		return c0.x * m00 - c1.x * m01 + c2.x * m02;
	}
	/// <summary>Returns the Determinant of a ulong4x4 matrix.</summary>
	inline static ulong Determinant(ulong4x4 m)
	{
		ulong4 c0 = m.c0;
		ulong4 c1 = m.c1;
		ulong4 c2 = m.c2;
		ulong4 c3 = m.c3;

		ulong m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
		ulong m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
		ulong m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
		ulong m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

		return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
	}

#pragma endregion
}