#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	
#pragma region bool2
			struct bool2 {
				bool x, y;
				bool2() : x(0), y(0) {}
				bool2(bool x, bool y) : x(x), y(y) {}
				bool2(bool v) : x(v), y(v) {}
			};
			/// <summary>Returns the result of a componentwise multiplication operation on two bool2 vectors.</summary>

			inline static bool2 operator * (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x * rhs.x, lhs.y * rhs.y); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator * (const bool2& lhs, bool rhs) { return bool2(lhs.x * rhs, lhs.y * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator * (bool lhs, const bool2& rhs) { return bool2(lhs * rhs.x, lhs * rhs.y); }


			/// <summary>Returns the result of a componentwise addition operation on two bool2 vectors.</summary>

			inline static bool2 operator + (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x + rhs.x, lhs.y + rhs.y); }

			/// <summary>Returns the result of a componentwise addition operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator + (const bool2& lhs, bool rhs) { return bool2(lhs.x + rhs, lhs.y + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator + (bool lhs, const bool2& rhs) { return bool2(lhs + rhs.x, lhs + rhs.y); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool2 vectors.</summary>

			inline static bool2 operator - (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x - rhs.x, lhs.y - rhs.y); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator - (const bool2& lhs, bool rhs) { return bool2(lhs.x - rhs, lhs.y - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator - (bool lhs, const bool2& rhs) { return bool2(lhs - rhs.x, lhs - rhs.y); }


			/// <summary>Returns the result of a componentwise division operation on two bool2 vectors.</summary>

			inline static bool2 operator / (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x / rhs.x, lhs.y / rhs.y); }

			/// <summary>Returns the result of a componentwise division operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator / (const bool2& lhs, bool rhs) { return bool2(lhs.x / rhs, lhs.y / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator / (bool lhs, const bool2& rhs) { return bool2(lhs / rhs.x, lhs / rhs.y); }

			/// <summary>Returns the result of a componentwise increment operation on a bool2 vector.</summary>

			inline static bool2 operator ++ (bool2 val) { return bool2(++val.x, ++val.y); }

			/// <summary>Returns the result of a componentwise less than operation on two bool2 vectors.</summary>

			inline static bool2 operator < (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

			/// <summary>Returns the result of a componentwise less than operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator < (const bool2& lhs, bool rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator < (bool lhs, const bool2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool2 vectors.</summary>

			inline static bool2 operator <= (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator <= (const bool2& lhs, bool rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator <= (bool lhs, const bool2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool2 vectors.</summary>

			inline static bool2 operator > (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator > (const bool2& lhs, bool rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator > (bool lhs, const bool2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool2 vectors.</summary>

			inline static bool2 operator >= (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator >= (const bool2& lhs, bool rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator >= (bool lhs, const bool2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool2 vector.</summary>

			inline static bool2 operator - (bool2 val) { return bool2(-val.x, -val.y); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool2 vector.</summary>

			inline static bool2 operator + (bool2 val) { return bool2(+val.x, +val.y); }


			/// <summary>Returns the result of a componentwise equality operation on two bool2 vectors.</summary>

			inline static bool2 operator == (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

			/// <summary>Returns the result of a componentwise equality operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator == (const bool2& lhs, bool rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator == (bool lhs, const bool2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool2 vectors.</summary>

			inline static bool2 operator != (const bool2& lhs, const bool2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool2 vector and a bool value.</summary>

			inline static bool2 operator != (const bool2& lhs, bool rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool2 vector.</summary>

			inline static bool2 operator != (bool lhs, const bool2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region bool2x2
			struct bool2x2
			{
				bool2 c0, c1;
				bool2x2() : c0(), c1() {}
				bool2x2(bool m00, bool m01,
					bool m10, bool m11) :c0(bool2(m00, m10)), c1(bool2(m01, m11)) {}
				bool2x2(bool2 c0, bool2 c1) : c0(c0), c1(c1) {}
				bool2x2(bool v) : c0(v), c1(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator * (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator * (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator * (bool lhs, const bool2x2& rhs) { return bool2x2(lhs * rhs.c0, lhs * rhs.c1); }


			/// <summary>Returns the result of a componentwise addition operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator + (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

			/// <summary>Returns the result of a componentwise addition operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator + (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator + (bool lhs, const bool2x2& rhs) { return bool2x2(lhs + rhs.c0, lhs + rhs.c1); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator - (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator - (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator - (bool lhs, const bool2x2& rhs) { return bool2x2(lhs - rhs.c0, lhs - rhs.c1); }


			/// <summary>Returns the result of a componentwise division operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator / (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

			/// <summary>Returns the result of a componentwise division operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator / (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator / (bool lhs, const bool2x2& rhs) { return bool2x2(lhs / rhs.c0, lhs / rhs.c1); }


			/// <summary>Returns the result of a componentwise increment operation on a bool2x2 matrix.</summary>

			inline static bool2x2 operator ++ (bool2x2 val) { return bool2x2(++val.c0, ++val.c1); }

			/// <summary>Returns the result of a componentwise less than operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator < (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

			/// <summary>Returns the result of a componentwise less than operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator < (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator < (bool lhs, const bool2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator <= (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator <= (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator <= (bool lhs, const bool2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator > (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator > (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator > (bool lhs, const bool2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator >= (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator >= (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator >= (bool lhs, const bool2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool2x2 matrix.</summary>

			inline static bool2x2 operator - (bool2x2 val) { return bool2x2(-val.c0, -val.c1); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool2x2 matrix.</summary>

			inline static bool2x2 operator + (bool2x2 val) { return bool2x2(+val.c0, +val.c1); }


			/// <summary>Returns the result of a componentwise equality operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator == (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

			/// <summary>Returns the result of a componentwise equality operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator == (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator == (bool lhs, const bool2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool2x2 matrices.</summary>

			inline static bool2x2 operator != (const bool2x2& lhs, const bool2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool2x2 matrix and a bool value.</summary>

			inline static bool2x2 operator != (const bool2x2& lhs, bool rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool2x2 matrix.</summary>

			inline static bool2x2 operator != (bool lhs, const bool2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region bool2x3
			struct bool2x3
			{
				bool2 c0, c1, c2;
				bool2x3() : c0(), c1(), c2() {}
				bool2x3(bool m00, bool m01, bool m02,
					bool m10, bool m11, bool m12)
				{
					c0 = bool2(m00, m10);
					c1 = bool2(m01, m11);
					c2 = bool2(m02, m12);
				}
				bool2x3(bool2 c0, bool2 c1, bool2 c2) : c0(c0), c1(c1), c2(c2) {}
				bool2x3(bool v) : c0(v), c1(v), c2(v) {}
			};

			/// <summary>Returns the result of a componentwise multiplication operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator * (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator * (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator * (bool lhs, const bool2x3& rhs) { return bool2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


			/// <summary>Returns the result of a componentwise addition operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator + (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

			/// <summary>Returns the result of a componentwise addition operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator + (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator + (bool lhs, const bool2x3& rhs) { return bool2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator - (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator - (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator - (bool lhs, const bool2x3& rhs) { return bool2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


			/// <summary>Returns the result of a componentwise division operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator / (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

			/// <summary>Returns the result of a componentwise division operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator / (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator / (bool lhs, const bool2x3& rhs) { return bool2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


			/// <summary>Returns the result of a componentwise increment operation on a bool2x3 matrix.</summary>

			inline static bool2x3 operator ++ (bool2x3 val) { return bool2x3(++val.c0, ++val.c1, ++val.c2); }

			/// <summary>Returns the result of a componentwise less than operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator < (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

			/// <summary>Returns the result of a componentwise less than operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator < (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator < (bool lhs, const bool2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator <= (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator <= (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator <= (bool lhs, const bool2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator > (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator > (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator > (bool lhs, const bool2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator >= (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator >= (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator >= (bool lhs, const bool2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool2x3 matrix.</summary>

			inline static bool2x3 operator - (bool2x3 val) { return bool2x3(-val.c0, -val.c1, -val.c2); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool2x3 matrix.</summary>

			inline static bool2x3 operator + (bool2x3 val) { return bool2x3(+val.c0, +val.c1, +val.c2); }


			/// <summary>Returns the result of a componentwise equality operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator == (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

			/// <summary>Returns the result of a componentwise equality operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator == (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator == (bool lhs, const bool2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool2x3 matrices.</summary>

			inline static bool2x3 operator != (const bool2x3& lhs, const bool2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool2x3 matrix and a bool value.</summary>

			inline static bool2x3 operator != (const bool2x3& lhs, bool rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool2x3 matrix.</summary>

			inline static bool2x3 operator != (bool lhs, const bool2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region bool2x4
			struct bool2x4
			{
				bool2 c0, c1, c2, c3;
				bool2x4() : c0(), c1(), c2(), c3() {}
				bool2x4(bool m00, bool m01, bool m02, bool m03,
					bool m10, bool m11, bool m12, bool m13)
				{
					c0 = bool2(m00, m10);
					c1 = bool2(m01, m11);
					c2 = bool2(m02, m12);
					c3 = bool2(m03, m13);
				}
				bool2x4(bool2 c0, bool2 c1, bool2 c2, bool2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
				bool2x4(bool v) : c0(v), c1(v), c2(v), c3(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator * (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator * (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator * (bool lhs, const bool2x4& rhs) { return bool2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


			/// <summary>Returns the result of a componentwise addition operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator + (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

			/// <summary>Returns the result of a componentwise addition operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator + (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator + (bool lhs, const bool2x4& rhs) { return bool2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator - (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator - (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator - (bool lhs, const bool2x4& rhs) { return bool2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


			/// <summary>Returns the result of a componentwise division operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator / (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

			/// <summary>Returns the result of a componentwise division operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator / (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator / (bool lhs, const bool2x4& rhs) { return bool2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


			/// <summary>Returns the result of a componentwise increment operation on a bool2x4 matrix.</summary>

			inline static bool2x4 operator ++ (bool2x4 val) { return bool2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }

			/// <summary>Returns the result of a componentwise less than operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator < (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

			/// <summary>Returns the result of a componentwise less than operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator < (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator < (bool lhs, const bool2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator <= (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator <= (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator <= (bool lhs, const bool2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator > (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator > (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator > (bool lhs, const bool2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator >= (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator >= (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator >= (bool lhs, const bool2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool2x4 matrix.</summary>

			inline static bool2x4 operator - (bool2x4 val) { return bool2x4(-val.c0, -val.c1, -val.c2, -val.c3); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool2x4 matrix.</summary>

			inline static bool2x4 operator + (bool2x4 val) { return bool2x4(+val.c0, +val.c1, +val.c2, +val.c3); }


			/// <summary>Returns the result of a componentwise equality operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator == (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

			/// <summary>Returns the result of a componentwise equality operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator == (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator == (bool lhs, const bool2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool2x4 matrices.</summary>

			inline static bool2x4 operator != (const bool2x4& lhs, const bool2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool2x4 matrix and a bool value.</summary>

			inline static bool2x4 operator != (const bool2x4& lhs, bool rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool2x4 matrix.</summary>

			inline static bool2x4 operator != (bool lhs, const bool2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region bool3
			struct bool3 {
				bool x, y, z;
				bool3() : x(0), y(0), z(0) {}
				bool3(bool x, bool y, bool z) : x(x), y(y), z(z) {}
				bool3(bool v) : x(v), y(v), z(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool3 vectors.</summary>

			inline static bool3 operator * (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator * (const bool3& lhs, bool rhs) { return bool3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator * (bool lhs, const bool3& rhs) { return bool3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


			/// <summary>Returns the result of a componentwise addition operation on two bool3 vectors.</summary>

			inline static bool3 operator + (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

			/// <summary>Returns the result of a componentwise addition operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator + (const bool3& lhs, bool rhs) { return bool3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator + (bool lhs, const bool3& rhs) { return bool3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool3 vectors.</summary>

			inline static bool3 operator - (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator - (const bool3& lhs, bool rhs) { return bool3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator - (bool lhs, const bool3& rhs) { return bool3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


			/// <summary>Returns the result of a componentwise division operation on two bool3 vectors.</summary>

			inline static bool3 operator / (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

			/// <summary>Returns the result of a componentwise division operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator / (const bool3& lhs, bool rhs) { return bool3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator / (bool lhs, const bool3& rhs) { return bool3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


			/// <summary>Returns the result of a componentwise increment operation on a bool3 vector.</summary>

			inline static bool3 operator ++ (bool3 val) { return bool3(++val.x, ++val.y, ++val.z); }

			/// <summary>Returns the result of a componentwise less than operation on two bool3 vectors.</summary>

			inline static bool3 operator < (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

			/// <summary>Returns the result of a componentwise less than operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator < (const bool3& lhs, bool rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator < (bool lhs, const bool3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool3 vectors.</summary>

			inline static bool3 operator <= (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator <= (const bool3& lhs, bool rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator <= (bool lhs, const bool3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool3 vectors.</summary>

			inline static bool3 operator > (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator > (const bool3& lhs, bool rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator > (bool lhs, const bool3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool3 vectors.</summary>

			inline static bool3 operator >= (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator >= (const bool3& lhs, bool rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator >= (bool lhs, const bool3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool3 vector.</summary>

			inline static bool3 operator - (bool3 val) { return bool3(-val.x, -val.y, -val.z); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool3 vector.</summary>

			inline static bool3 operator + (bool3 val) { return bool3(+val.x, +val.y, +val.z); }


			/// <summary>Returns the result of a componentwise equality operation on two bool3 vectors.</summary>

			inline static bool3 operator == (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

			/// <summary>Returns the result of a componentwise equality operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator == (const bool3& lhs, bool rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator == (bool lhs, const bool3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool3 vectors.</summary>

			inline static bool3 operator != (const bool3& lhs, const bool3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool3 vector and a bool value.</summary>

			inline static bool3 operator != (const bool3& lhs, bool rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool3 vector.</summary>

			inline static bool3 operator != (bool lhs, const bool3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region bool3x2
			struct bool3x2
			{
				bool3 c0, c1;
				bool3x2() : c0(), c1() {}
				bool3x2(bool m00, bool m01,
					bool m10, bool m11,
					bool m20, bool m21)
				{
					c0 = bool3(m00, m10, m20);
					c1 = bool3(m01, m11, m21);
				}

				bool3x2(bool3 c0, bool3 c1) : c0(c0), c1(c1) {}
				bool3x2(bool v) : c0(v), c1(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator * (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator * (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator * (bool lhs, const bool3x2& rhs) { return bool3x2(lhs * rhs.c0, lhs * rhs.c1); }


			/// <summary>Returns the result of a componentwise addition operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator + (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

			/// <summary>Returns the result of a componentwise addition operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator + (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator + (bool lhs, const bool3x2& rhs) { return bool3x2(lhs + rhs.c0, lhs + rhs.c1); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator - (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator - (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator - (bool lhs, const bool3x2& rhs) { return bool3x2(lhs - rhs.c0, lhs - rhs.c1); }


			/// <summary>Returns the result of a componentwise division operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator / (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

			/// <summary>Returns the result of a componentwise division operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator / (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator / (bool lhs, const bool3x2& rhs) { return bool3x2(lhs / rhs.c0, lhs / rhs.c1); }


			/// <summary>Returns the result of a componentwise increment operation on a bool3x2 matrix.</summary>

			inline static bool3x2 operator ++ (bool3x2 val) { return bool3x2(++val.c0, ++val.c1); }

			/// <summary>Returns the result of a componentwise less than operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator < (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

			/// <summary>Returns the result of a componentwise less than operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator < (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator < (bool lhs, const bool3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator <= (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator <= (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator <= (bool lhs, const bool3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator > (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator > (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator > (bool lhs, const bool3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator >= (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator >= (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator >= (bool lhs, const bool3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool3x2 matrix.</summary>

			inline static bool3x2 operator - (bool3x2 val) { return bool3x2(-val.c0, -val.c1); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool3x2 matrix.</summary>

			inline static bool3x2 operator + (bool3x2 val) { return bool3x2(+val.c0, +val.c1); }


			/// <summary>Returns the result of a componentwise equality operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator == (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

			/// <summary>Returns the result of a componentwise equality operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator == (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator == (bool lhs, const bool3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool3x2 matrices.</summary>

			inline static bool3x2 operator != (const bool3x2& lhs, const bool3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool3x2 matrix and a bool value.</summary>

			inline static bool3x2 operator != (const bool3x2& lhs, bool rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool3x2 matrix.</summary>

			inline static bool3x2 operator != (bool lhs, const bool3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region bool3x3
			struct bool3x3
			{
				bool3 c0, c1, c2;
				bool3x3() : c0(), c1(), c2() {}
				bool3x3(bool m00, bool m01, bool m02,
					bool m10, bool m11, bool m12,
					bool m20, bool m21, bool m22)
				{
					c0 = bool3(m00, m10, m20);
					c1 = bool3(m01, m11, m21);
					c2 = bool3(m02, m12, m22);
				}
				bool3x3(bool3 c0, bool3 c1, bool3 c2) : c0(c0), c1(c1), c2(c2) {}
				bool3x3(bool v) : c0(v), c1(v), c2(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator * (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator * (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator * (bool lhs, const bool3x3& rhs) { return bool3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


			/// <summary>Returns the result of a componentwise addition operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator + (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

			/// <summary>Returns the result of a componentwise addition operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator + (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator + (bool lhs, const bool3x3& rhs) { return bool3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator - (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator - (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator - (bool lhs, const bool3x3& rhs) { return bool3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


			/// <summary>Returns the result of a componentwise division operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator / (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

			/// <summary>Returns the result of a componentwise division operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator / (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator / (bool lhs, const bool3x3& rhs) { return bool3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

			/// <summary>Returns the result of a componentwise increment operation on a bool3x3 matrix.</summary>

			inline static bool3x3 operator ++ (bool3x3 val) { return bool3x3(++val.c0, ++val.c1, ++val.c2); }

			/// <summary>Returns the result of a componentwise less than operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator < (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

			/// <summary>Returns the result of a componentwise less than operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator < (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator < (bool lhs, const bool3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator <= (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator <= (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator <= (bool lhs, const bool3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator > (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator > (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator > (bool lhs, const bool3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator >= (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator >= (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator >= (bool lhs, const bool3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool3x3 matrix.</summary>

			inline static bool3x3 operator - (bool3x3 val) { return bool3x3(-val.c0, -val.c1, -val.c2); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool3x3 matrix.</summary>

			inline static bool3x3 operator + (bool3x3 val) { return bool3x3(+val.c0, +val.c1, +val.c2); }


			/// <summary>Returns the result of a componentwise equality operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator == (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

			/// <summary>Returns the result of a componentwise equality operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator == (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator == (bool lhs, const bool3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool3x3 matrices.</summary>

			inline static bool3x3 operator != (const bool3x3& lhs, const bool3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool3x3 matrix and a bool value.</summary>

			inline static bool3x3 operator != (const bool3x3& lhs, bool rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool3x3 matrix.</summary>

			inline static bool3x3 operator != (bool lhs, const bool3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region bool3x4
			struct bool3x4
			{
				bool3 c0, c1, c2, c3;
				bool3x4() : c0(), c1(), c2(), c3() {}
				bool3x4(bool m00, bool m01, bool m02, bool m03,
					bool m10, bool m11, bool m12, bool m13,
					bool m20, bool m21, bool m22, bool m23)
				{
					c0 = bool3(m00, m10, m20);
					c1 = bool3(m01, m11, m21);
					c2 = bool3(m02, m12, m22);
					c3 = bool3(m03, m13, m23);
				}
				bool3x4(bool3 c0, bool3 c1, bool3 c2, bool3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
				bool3x4(bool v) : c0(v), c1(v), c2(v), c3(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator * (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator * (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator * (bool lhs, const bool3x4& rhs) { return bool3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


			/// <summary>Returns the result of a componentwise addition operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator + (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

			/// <summary>Returns the result of a componentwise addition operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator + (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator + (bool lhs, const bool3x4& rhs) { return bool3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator - (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator - (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator - (bool lhs, const bool3x4& rhs) { return bool3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


			/// <summary>Returns the result of a componentwise division operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator / (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

			/// <summary>Returns the result of a componentwise division operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator / (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator / (bool lhs, const bool3x4& rhs) { return bool3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

			/// <summary>Returns the result of a componentwise increment operation on a bool3x4 matrix.</summary>

			inline static bool3x4 operator ++ (bool3x4 val) { return bool3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }

			/// <summary>Returns the result of a componentwise less than operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator < (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

			/// <summary>Returns the result of a componentwise less than operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator < (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator < (bool lhs, const bool3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator <= (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator <= (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator <= (bool lhs, const bool3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator > (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator > (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator > (bool lhs, const bool3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator >= (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator >= (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator >= (bool lhs, const bool3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool3x4 matrix.</summary>

			inline static bool3x4 operator - (bool3x4 val) { return bool3x4(-val.c0, -val.c1, -val.c2, -val.c3); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool3x4 matrix.</summary>

			inline static bool3x4 operator + (bool3x4 val) { return bool3x4(+val.c0, +val.c1, +val.c2, +val.c3); }


			/// <summary>Returns the result of a componentwise equality operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator == (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

			/// <summary>Returns the result of a componentwise equality operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator == (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator == (bool lhs, const bool3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool3x4 matrices.</summary>

			inline static bool3x4 operator != (const bool3x4& lhs, const bool3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool3x4 matrix and a bool value.</summary>

			inline static bool3x4 operator != (const bool3x4& lhs, bool rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool3x4 matrix.</summary>

			inline static bool3x4 operator != (bool lhs, const bool3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region bool4
			struct bool4 {
				bool x, y, z, w;
				bool4() : x(0), y(0), z(0), w(0) {}
				bool4(bool x, bool y, bool z, bool w) : x(x), y(y), z(z), w(w) {}
				bool4(bool v) : x(v), y(v), z(v), w(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool4 vectors.</summary>

			inline static bool4 operator * (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator * (const bool4& lhs, bool rhs) { return bool4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator * (bool lhs, const bool4& rhs) { return bool4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


			/// <summary>Returns the result of a componentwise addition operation on two bool4 vectors.</summary>

			inline static bool4 operator + (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

			/// <summary>Returns the result of a componentwise addition operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator + (const bool4& lhs, bool rhs) { return bool4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator + (bool lhs, const bool4& rhs) { return bool4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool4 vectors.</summary>

			inline static bool4 operator - (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator - (const bool4& lhs, bool rhs) { return bool4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator - (bool lhs, const bool4& rhs) { return bool4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


			/// <summary>Returns the result of a componentwise division operation on two bool4 vectors.</summary>

			inline static bool4 operator / (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

			/// <summary>Returns the result of a componentwise division operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator / (const bool4& lhs, bool rhs) { return bool4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator / (bool lhs, const bool4& rhs) { return bool4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

			/// <summary>Returns the result of a componentwise increment operation on a bool4 vector.</summary>

			inline static bool4 operator ++ (bool4 val) { return bool4(++val.x, ++val.y, ++val.z, ++val.w); }

			/// <summary>Returns the result of a componentwise less than operation on two bool4 vectors.</summary>

			inline static bool4 operator < (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

			/// <summary>Returns the result of a componentwise less than operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator < (const bool4& lhs, bool rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator < (bool lhs, const bool4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool4 vectors.</summary>

			inline static bool4 operator <= (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator <= (const bool4& lhs, bool rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator <= (bool lhs, const bool4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool4 vectors.</summary>

			inline static bool4 operator > (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator > (const bool4& lhs, bool rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator > (bool lhs, const bool4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool4 vectors.</summary>

			inline static bool4 operator >= (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator >= (const bool4& lhs, bool rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator >= (bool lhs, const bool4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool4 vector.</summary>

			inline static bool4 operator - (bool4 val) { return bool4(-val.x, -val.y, -val.z, -val.w); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool4 vector.</summary>

			inline static bool4 operator + (bool4 val) { return bool4(+val.x, +val.y, +val.z, +val.w); }


			/// <summary>Returns the result of a componentwise equality operation on two bool4 vectors.</summary>

			inline static bool4 operator == (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

			/// <summary>Returns the result of a componentwise equality operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator == (const bool4& lhs, bool rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator == (bool lhs, const bool4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool4 vectors.</summary>

			inline static bool4 operator != (const bool4& lhs, const bool4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool4 vector and a bool value.</summary>

			inline static bool4 operator != (const bool4& lhs, bool rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool4 vector.</summary>

			inline static bool4 operator != (bool lhs, const bool4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region bool4x2
			struct bool4x2
			{
				bool4 c0, c1;
				bool4x2() : c0(), c1() {}
				bool4x2(bool m00, bool m01,
					bool m10, bool m11,
					bool m20, bool m21,
					bool m30, bool m31)
				{
					c0 = bool4(m00, m10, m20, m30);
					c1 = bool4(m01, m11, m21, m31);
				}
				bool4x2(bool4 c0, bool4 c1) : c0(c0), c1(c1) {}
				bool4x2(bool v) : c0(v), c1(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator * (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator * (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator * (bool lhs, const bool4x2& rhs) { return bool4x2(lhs * rhs.c0, lhs * rhs.c1); }


			/// <summary>Returns the result of a componentwise addition operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator + (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

			/// <summary>Returns the result of a componentwise addition operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator + (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator + (bool lhs, const bool4x2& rhs) { return bool4x2(lhs + rhs.c0, lhs + rhs.c1); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator - (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator - (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator - (bool lhs, const bool4x2& rhs) { return bool4x2(lhs - rhs.c0, lhs - rhs.c1); }


			/// <summary>Returns the result of a componentwise division operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator / (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

			/// <summary>Returns the result of a componentwise division operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator / (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator / (bool lhs, const bool4x2& rhs) { return bool4x2(lhs / rhs.c0, lhs / rhs.c1); }

			/// <summary>Returns the result of a componentwise increment operation on a bool4x2 matrix.</summary>

			inline static bool4x2 operator ++ (bool4x2 val) { return bool4x2(++val.c0, ++val.c1); }

			/// <summary>Returns the result of a componentwise less than operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator < (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

			/// <summary>Returns the result of a componentwise less than operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator < (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator < (bool lhs, const bool4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator <= (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator <= (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator <= (bool lhs, const bool4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator > (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator > (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator > (bool lhs, const bool4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator >= (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator >= (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator >= (bool lhs, const bool4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool4x2 matrix.</summary>

			inline static bool4x2 operator - (bool4x2 val) { return bool4x2(-val.c0, -val.c1); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool4x2 matrix.</summary>

			inline static bool4x2 operator + (bool4x2 val) { return bool4x2(+val.c0, +val.c1); }


			/// <summary>Returns the result of a componentwise equality operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator == (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

			/// <summary>Returns the result of a componentwise equality operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator == (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator == (bool lhs, const bool4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool4x2 matrices.</summary>

			inline static bool4x2 operator != (const bool4x2& lhs, const bool4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool4x2 matrix and a bool value.</summary>

			inline static bool4x2 operator != (const bool4x2& lhs, bool rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool4x2 matrix.</summary>

			inline static bool4x2 operator != (bool lhs, const bool4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region bool4x3
			struct bool4x3
			{
				bool4 c0, c1, c2;
				bool4x3() : c0(), c1(), c2() {}
				bool4x3(bool m00, bool m01, bool m02,
					bool m10, bool m11, bool m12,
					bool m20, bool m21, bool m22,
					bool m30, bool m31, bool m32)
				{
					c0 = bool4(m00, m10, m20, m30);
					c1 = bool4(m01, m11, m21, m31);
					c2 = bool4(m02, m12, m22, m32);
				}
				bool4x3(bool4 c0, bool4 c1, bool4 c2) : c0(c0), c1(c1), c2(c2) {}
				bool4x3(bool v) : c0(v), c1(v), c2(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator * (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator * (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator * (bool lhs, const bool4x3& rhs) { return bool4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


			/// <summary>Returns the result of a componentwise addition operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator + (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

			/// <summary>Returns the result of a componentwise addition operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator + (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator + (bool lhs, const bool4x3& rhs) { return bool4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator - (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator - (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator - (bool lhs, const bool4x3& rhs) { return bool4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


			/// <summary>Returns the result of a componentwise division operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator / (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

			/// <summary>Returns the result of a componentwise division operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator / (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator / (bool lhs, const bool4x3& rhs) { return bool4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

			/// <summary>Returns the result of a componentwise increment operation on a bool4x3 matrix.</summary>

			inline static bool4x3 operator ++ (bool4x3 val) { return bool4x3(++val.c0, ++val.c1, ++val.c2); }

			/// <summary>Returns the result of a componentwise less than operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator < (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

			/// <summary>Returns the result of a componentwise less than operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator < (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator < (bool lhs, const bool4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator <= (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator <= (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator <= (bool lhs, const bool4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator > (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator > (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator > (bool lhs, const bool4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator >= (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator >= (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator >= (bool lhs, const bool4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool4x3 matrix.</summary>

			inline static bool4x3 operator - (bool4x3 val) { return bool4x3(-val.c0, -val.c1, -val.c2); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool4x3 matrix.</summary>

			inline static bool4x3 operator + (bool4x3 val) { return bool4x3(+val.c0, +val.c1, +val.c2); }


			/// <summary>Returns the result of a componentwise equality operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator == (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

			/// <summary>Returns the result of a componentwise equality operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator == (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator == (bool lhs, const bool4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool4x3 matrices.</summary>

			inline static bool4x3 operator != (const bool4x3& lhs, const bool4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool4x3 matrix and a bool value.</summary>

			inline static bool4x3 operator != (const bool4x3& lhs, bool rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool4x3 matrix.</summary>

			inline static bool4x3 operator != (bool lhs, const bool4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region bool4x4
			struct bool4x4
			{
				bool4 c0, c1, c2, c3;
				bool4x4() : c0(), c1(), c2(), c3() {}
				bool4x4(bool m00, bool m01, bool m02, bool m03,
					bool m10, bool m11, bool m12, bool m13,
					bool m20, bool m21, bool m22, bool m23,
					bool m30, bool m31, bool m32, bool m33)
				{
					c0 = bool4(m00, m10, m20, m30);
					c1 = bool4(m01, m11, m21, m31);
					c2 = bool4(m02, m12, m22, m32);
					c3 = bool4(m03, m13, m23, m33);
				}
				bool4x4(bool4 c0, bool4 c1, bool4 c2, bool4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
				bool4x4(bool v) : c0(v), c1(v), c2(v), c3(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator * (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator * (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator * (bool lhs, const bool4x4& rhs) { return bool4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


			/// <summary>Returns the result of a componentwise addition operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator + (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

			/// <summary>Returns the result of a componentwise addition operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator + (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator + (bool lhs, const bool4x4& rhs) { return bool4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


			/// <summary>Returns the result of a componentwise subtraction operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator - (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator - (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator - (bool lhs, const bool4x4& rhs) { return bool4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


			/// <summary>Returns the result of a componentwise division operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator / (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

			/// <summary>Returns the result of a componentwise division operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator / (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator / (bool lhs, const bool4x4& rhs) { return bool4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


			/// <summary>Returns the result of a componentwise increment operation on a bool4x4 matrix.</summary>

			inline static bool4x4 operator ++ (bool4x4 val) { return bool4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }

			/// <summary>Returns the result of a componentwise less than operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator < (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

			/// <summary>Returns the result of a componentwise less than operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator < (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator < (bool lhs, const bool4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


			/// <summary>Returns the result of a componentwise less or equal operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator <= (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator <= (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator <= (bool lhs, const bool4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


			/// <summary>Returns the result of a componentwise greater than operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator > (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator > (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator > (bool lhs, const bool4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator >= (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator >= (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator >= (bool lhs, const bool4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


			/// <summary>Returns the result of a componentwise unary minus operation on a bool4x4 matrix.</summary>

			inline static bool4x4 operator - (bool4x4 val) { return bool4x4(-val.c0, -val.c1, -val.c2, -val.c3); }


			/// <summary>Returns the result of a componentwise unary plus operation on a bool4x4 matrix.</summary>

			inline static bool4x4 operator + (bool4x4 val) { return bool4x4(+val.c0, +val.c1, +val.c2, +val.c3); }


			/// <summary>Returns the result of a componentwise equality operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator == (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

			/// <summary>Returns the result of a componentwise equality operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator == (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator == (bool lhs, const bool4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


			/// <summary>Returns the result of a componentwise not equal operation on two bool4x4 matrices.</summary>

			inline static bool4x4 operator != (const bool4x4& lhs, const bool4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool4x4 matrix and a bool value.</summary>

			inline static bool4x4 operator != (const bool4x4& lhs, bool rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a bool value and a bool4x4 matrix.</summary>

			inline static bool4x4 operator != (bool lhs, const bool4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic

			/// <summary>Returns the minimum of two bool values.</summary>
			inline static bool min(bool x, bool y) { return x < y ? x : y; }

			/// <summary>Returns the componentwise minimum of two bool2 vectors.</summary>
			inline static bool2 min(bool2 x, bool2 y) { return bool2(min(x.x, y.x), min(x.y, y.y)); }

			/// <summary>Returns the componentwise minimum of two bool3 vectors.</summary>
			inline static bool3 min(bool3 x, bool3 y) { return bool3(min(x.x, y.x), min(x.y, y.y), min(x.z, y.z)); }

			/// <summary>Returns the componentwise minimum of two bool4 vectors.</summary>
			inline static bool4 min(bool4 x, bool4 y) { return bool4(min(x.x, y.x), min(x.y, y.y), min(x.z, y.z), min(x.w, y.w)); }


			/// <summary>Returns the maximum of two bool values.</summary>
			inline static bool max(bool x, bool y) { return x > y ? x : y; }

			/// <summary>Returns the componentwise maximum of two bool2 vectors.</summary>
			inline static bool2 max(bool2 x, bool2 y) { return bool2(max(x.x, y.x), max(x.y, y.y)); }

			/// <summary>Returns the componentwise maximum of two bool3 vectors.</summary>
			inline static bool3 max(bool3 x, bool3 y) { return bool3(max(x.x, y.x), max(x.y, y.y), max(x.z, y.z)); }

			/// <summary>Returns the componentwise maximum of two bool4 vectors.</summary>
			inline static bool4 max(bool4 x, bool4 y) { return bool4(max(x.x, y.x), max(x.y, y.y), max(x.z, y.z), max(x.w, y.w)); }

			inline static bool lerp(bool x, bool y, bool s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y using the interpolation parameter s.</summary>
			inline static bool2 lerp(bool2 x, bool2 y, bool s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y using the interpolation parameter s.</summary>
			inline static bool3 lerp(bool3 x, bool3 y, bool s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y using the interpolation parameter s.</summary>
			inline static bool4 lerp(bool4 x, bool4 y, bool s) { return x + s * (y - x); }


			/// <summary>Returns the result of a componentwise linear interpolating from x to y using the corresponding components of the interpolation parameter s.</summary>
			inline static bool2 lerp(bool2 x, bool2 y, bool2 s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y using the corresponding components of the interpolation parameter s.</summary>
			inline static bool3 lerp(bool3 x, bool3 y, bool3 s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y using the corresponding components of the interpolation parameter s.</summary>
			inline static bool4 lerp(bool4 x, bool4 y, bool4 s) { return x + s * (y - x); }

			/// <summary>Returns the result of normalizing a booling point value x to a range [a, b]. The opposite of lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static bool unlerp(bool a, bool b, bool x) { return (x - a) / (b - a); }

			/// <summary>Returns the componentwise result of normalizing a booling point value x to a range [a, b]. The opposite of lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static bool2 unlerp(bool2 a, bool2 b, bool2 x) { return (x - a) / (b - a); }

			/// <summary>Returns the componentwise result of normalizing a booling point value x to a range [a, b]. The opposite of lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static bool3 unlerp(bool3 a, bool3 b, bool3 x) { return (x - a) / (b - a); }

			/// <summary>Returns the componentwise result of normalizing a booling point value x to a range [a, b]. The opposite of lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static bool4 unlerp(bool4 a, bool4 b, bool4 x) { return (x - a) / (b - a); }

			/// <summary>Returns the result of a non-clamping linear remapping of a value x from [a, b] to [c, d].</summary>
			inline static bool remap(bool a, bool b, bool c, bool d, bool x) { return lerp(c, d, unlerp(a, b, x)); }

			/// <summary>Returns the componentwise result of a non-clamping linear remapping of a value x from [a, b] to [c, d].</summary>
			inline static bool2 remap(bool2 a, bool2 b, bool2 c, bool2 d, bool2 x) { return lerp(c, d, unlerp(a, b, x)); }

			/// <summary>Returns the componentwise result of a non-clamping linear remapping of a value x from [a, b] to [c, d].</summary>
			inline static bool3 remap(bool3 a, bool3 b, bool3 c, bool3 d, bool3 x) { return lerp(c, d, unlerp(a, b, x)); }

			/// <summary>Returns the componentwise result of a non-clamping linear remapping of a value x from [a, b] to [c, d].</summary>
			inline static bool4 remap(bool4 a, bool4 b, bool4 c, bool4 d, bool4 x) { return lerp(c, d, unlerp(a, b, x)); }

			/// <summary>Returns the result of clamping the value x into the interval [a, b], where x, a and b are bool values.</summary>
			inline static bool clamp(bool x, bool a, bool b) { return max(a, min(b, x)); }

			/// <summary>Returns the result of a componentwise clamping of the value x into the interval [a, b], where x, a and b are bool2 vectors.</summary>
			inline static bool2 clamp(bool2 x, bool2 a, bool2 b) { return max(a, min(b, x)); }

			/// <summary>Returns the result of a componentwise clamping of the value x into the interval [a, b], where x, a and b are bool3 vectors.</summary>
			inline static bool3 clamp(bool3 x, bool3 a, bool3 b) { return max(a, min(b, x)); }

			/// <summary>Returns the result of a componentwise clamping of the value x into the interval [a, b], where x, a and b are bool4 vectors.</summary>
			inline static bool4 clamp(bool4 x, bool4 a, bool4 b) { return max(a, min(b, x)); }

			inline static bool select_shuffle_component(bool4 a, bool4 b, char component)
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

			inline static bool4 shuffle(bool4 a, bool4 b, char x, char y, char z, char w)
			{
				return bool4(
					select_shuffle_component(a, b, x),
					select_shuffle_component(a, b, y),
					select_shuffle_component(a, b, z),
					select_shuffle_component(a, b, w));
			}

			inline static bool4 movelh(bool4 a, bool4 b)
			{
				return shuffle(a, b, 0, 1, 4, 5);
			}
			inline static bool4 movehl(bool4 a, bool4 b)
			{
				return shuffle(b, a, 2, 3, 6, 7);
			}
			// SSE shuffles
			inline static bool4 unpacklo(bool4 a, bool4 b)
			{
				return shuffle(a, b, 0, 4, 1, 5);
			}
			inline static bool4 unpackhi(bool4 a, bool4 b)
			{
				return shuffle(a, b, 2, 6, 3, 7);
			}
#pragma endregion
#pragma region Component
			/// <summary>Returns the maximum component of a bool2 vector.</summary>
			inline static bool cmax(bool2 x) { return max(x.x, x.y); }

			/// <summary>Returns the maximum component of a bool3 vector.</summary>
			inline static bool cmax(bool3 x) { return max(max(x.x, x.y), x.z); }

			/// <summary>Returns the maximum component of a bool4 vector.</summary>
			inline static bool cmax(bool4 x) { return max(max(x.x, x.y), max(x.z, x.w)); }

			/// <summary>Returns the horizontal sum of components of a bool2 vector.</summary>
			inline static bool csum(bool2 x) { return x.x + x.y; }

			/// <summary>Returns the horizontal sum of components of a bool3 vector.</summary>
			inline static bool csum(bool3 x) { return x.x + x.y + x.z; }

			/// <summary>Returns the horizontal sum of components of a bool4 vector.</summary>
			inline static bool csum(bool4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion
#pragma region Transpose
			/// <summary>Return the bool2x2 transpose of a bool2x2 matrix.</summary>
			inline bool2x2 transpose(bool2x2 v)
			{
				return bool2x2(
					v.c0.x, v.c0.y,
					v.c1.x, v.c1.y);
			}
			/// <summary>Return the bool3x2 transpose of a bool2x3 matrix.</summary>
			inline bool3x2 transpose(bool2x3 v)
			{
				return bool3x2(
					v.c0.x, v.c0.y,
					v.c1.x, v.c1.y,
					v.c2.x, v.c2.y);
			}
			/// <summary>Return the bool4x2 transpose of a bool2x4 matrix.</summary>
			inline bool4x2 transpose(bool2x4 v)
			{
				return bool4x2(
					v.c0.x, v.c0.y,
					v.c1.x, v.c1.y,
					v.c2.x, v.c2.y,
					v.c3.x, v.c3.y);
			}
			/// <summary>Return the bool2x3 transpose of a bool3x2 matrix.</summary>
			inline bool2x3 transpose(bool3x2 v)
			{
				return bool2x3(
					v.c0.x, v.c0.y, v.c0.z,
					v.c1.x, v.c1.y, v.c1.z);
			}
			/// <summary>Return the bool3x3 transpose of a bool3x3 matrix.</summary>
			inline bool3x3 transpose(bool3x3 v)
			{
				return bool3x3(
					v.c0.x, v.c0.y, v.c0.z,
					v.c1.x, v.c1.y, v.c1.z,
					v.c2.x, v.c2.y, v.c2.z);
			}
			/// <summary>Return the bool4x3 transpose of a bool3x4 matrix.</summary>
			inline static bool4x3 transpose(bool3x4 v)
			{
				return bool4x3(
					v.c0.x, v.c0.y, v.c0.z,
					v.c1.x, v.c1.y, v.c1.z,
					v.c2.x, v.c2.y, v.c2.z,
					v.c3.x, v.c3.y, v.c3.z);
			}
			/// <summary>Return the bool2x4 transpose of a bool4x2 matrix.</summary>
			inline static bool2x4 transpose(bool4x2 v)
			{
				return bool2x4(
					v.c0.x, v.c0.y, v.c0.z, v.c0.w,
					v.c1.x, v.c1.y, v.c1.z, v.c1.w);
			}
			/// <summary>Return the bool3x4 transpose of a bool4x3 matrix.</summary>
			inline static bool3x4 transpose(bool4x3 v)
			{
				return bool3x4(
					v.c0.x, v.c0.y, v.c0.z, v.c0.w,
					v.c1.x, v.c1.y, v.c1.z, v.c1.w,
					v.c2.x, v.c2.y, v.c2.z, v.c2.w);
			}
			/// <summary>Return the bool4x4 transpose of a bool4x4 matrix.</summary>
			inline static bool4x4 transpose(bool4x4 v)
			{
				return bool4x4(
					v.c0.x, v.c0.y, v.c0.z, v.c0.w,
					v.c1.x, v.c1.y, v.c1.z, v.c1.w,
					v.c2.x, v.c2.y, v.c2.z, v.c2.w,
					v.c3.x, v.c3.y, v.c3.z, v.c3.w);
			}

#pragma endregion
#pragma region Inverse
			/// <summary>Returns the bool2x2 full inverse of a bool2x2 matrix.</summary>
			inline bool2x2 inverse(bool2x2 m)
			{
				bool a = m.c0.x;
				bool b = m.c1.x;
				bool c = m.c0.y;
				bool d = m.c1.y;

				bool det = a * d - b * c;

				return bool2x2(d, -b, -c, a) * (1.0f / det);
			}
			/// <summary>Returns the bool3x3 full inverse of a bool3x3 matrix.</summary>
			inline bool3x3 inverse(bool3x3 m)
			{
				bool3 c0 = m.c0;
				bool3 c1 = m.c1;
				bool3 c2 = m.c2;

				bool3 t0 = bool3(c1.x, c2.x, c0.x);
				bool3 t1 = bool3(c1.y, c2.y, c0.y);
				bool3 t2 = bool3(c1.z, c2.z, c0.z);

				bool3 m0 = t1 * bool3(t2.y, t2.z, t2.x) - bool3(t1.y, t1.z, t1.x) * t2;
				bool3 m1 = bool3(t0.y, t0.z, t0.x) * t2 - t0 * bool3(t2.y, t2.z, t2.x);
				bool3 m2 = t0 * bool3(t1.y, t1.z, t1.x) - t0 * bool3(t2.y, t2.z, t2.x) * t1;

				bool rcpDet = 1.0f / csum(bool3(t0.z, t0.x, t0.y) * m0);
				return bool3x3(m0, m1, m2) * rcpDet;
			}
			// Fast matrix inverse for rigid transforms (Orthonormal basis and translation)
			inline static bool3x4 fastinverse(bool3x4 m)
			{
				bool3 c0 = m.c0;
				bool3 c1 = m.c1;
				bool3 c2 = m.c2;
				bool3 pos = m.c3;

				bool3 r0 = bool3(c0.x, c1.x, c2.x);
				bool3 r1 = bool3(c0.y, c1.y, c2.y);
				bool3 r2 = bool3(c0.z, c1.z, c2.z);

				pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);

				return bool3x4(r0, r1, r2, pos);
			}
			/// <summary>Returns the bool4x4 full inverse of a bool4x4 matrix.</summary>
			inline static bool4x4 inverse(bool4x4 m)
			{
				bool4 c0 = m.c0;
				bool4 c1 = m.c1;
				bool4 c2 = m.c2;
				bool4 c3 = m.c3;

				bool4 r0y_r1y_r0x_r1x = movelh(c1, c0);
				bool4 r0z_r1z_r0w_r1w = movelh(c2, c3);
				bool4 r2y_r3y_r2x_r3x = movehl(c0, c1);
				bool4 r2z_r3z_r2w_r3w = movehl(c3, c2);

				bool4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
				bool4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
				bool4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
				bool4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

				bool4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
				bool4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
				bool4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
				bool4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
				bool4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

				// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
				bool4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
				bool4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
				bool4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

				// Expand inner terms back to 4 components. zw signs still need to be flipped
				bool4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
				bool4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

				bool4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
				bool4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

				// Calculate minors
				bool4 minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

				bool4 denom = r0_xyzw * minors0;

				// Horizontal sum of denominator. Free sign flip of z and w compensates for missing flip in inner terms.
				denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
				denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

				bool4 rcp_denom_ppnn = bool4(1.0f) / denom;
				bool4x4 res;
				res.c0 = minors0 * rcp_denom_ppnn;

				bool4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
				bool4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

				bool4 minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
				res.c1 = minors1 * rcp_denom_ppnn;

				bool4 minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
				res.c2 = minors2 * rcp_denom_ppnn;

				bool4 minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
				res.c3 = minors3 * rcp_denom_ppnn;
				return res;
			}
			// Fast matrix inverse for rigid transforms (Orthonormal basis and translation)
			inline static bool4x4 fastinverse(bool4x4 m)
			{
				bool4 c0 = m.c0;
				bool4 c1 = m.c1;
				bool4 c2 = m.c2;
				bool4 pos = m.c3;

				bool4 zero = bool4(0);

				bool4 t0 = unpacklo(c0, c2);
				bool4 t1 = unpacklo(c1, zero);
				bool4 t2 = unpackhi(c0, c2);
				bool4 t3 = unpackhi(c1, zero);

				bool4 r0 = unpacklo(t0, t1);
				bool4 r1 = unpackhi(t0, t1);
				bool4 r2 = unpacklo(t2, t3);

				pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);
				pos.w = 1.0f;

				return bool4x4(r0, r1, r2, pos);
			}
#pragma endregion
#pragma region Determinant
			/// <summary>Returns the determinant of a bool2x2 matrix.</summary>
			inline bool determinant(bool2x2 m)
			{
				bool a = m.c0.x;
				bool b = m.c1.x;
				bool c = m.c0.y;
				bool d = m.c1.y;

				return a * d - b * c;
			}
			/// <summary>Returns the determinant of a bool3x3 matrix.</summary>
			inline bool determinant(bool3x3 m)
			{
				bool3 c0 = m.c0;
				bool3 c1 = m.c1;
				bool3 c2 = m.c2;

				bool m00 = c1.y * c2.z - c1.z * c2.y;
				bool m01 = c0.y * c2.z - c0.z * c2.y;
				bool m02 = c0.y * c1.z - c0.z * c1.y;

				return c0.x * m00 - c1.x * m01 + c2.x * m02;
			}
			/// <summary>Returns the determinant of a bool4x4 matrix.</summary>
			inline static bool determinant(bool4x4 m)
			{
				bool4 c0 = m.c0;
				bool4 c1 = m.c1;
				bool4 c2 = m.c2;
				bool4 c3 = m.c3;

				bool m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
				bool m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
				bool m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
				bool m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

				return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
			}

#pragma endregion
		
}