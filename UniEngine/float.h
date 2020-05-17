#pragma once
#include "bool.h"
#include <math.h>
namespace UniEngine {
#pragma region float2
			struct float2 {
				float x, y;
				float2() : x(0), y(0) {}
				float2(float x, float y) : x(x), y(y) {}
				float2(float v) : x(v), y(v) {}
			};
			/// <summary>Returns the result of a componentwise multiplication operation on two float2 vectors.</summary>

			inline static float2 operator * (const float2& lhs, const float2& rhs) { return float2(lhs.x * rhs.x, lhs.y * rhs.y); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float2 vector and a float value.</summary>

			inline static float2 operator * (const float2& lhs, float rhs) { return float2(lhs.x * rhs, lhs.y * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float2 vector.</summary>

			inline static float2 operator * (float lhs, const float2& rhs) { return float2(lhs * rhs.x, lhs * rhs.y); }


			/// <summary>Returns the result of a componentwise addition operation on two float2 vectors.</summary>

			inline static float2 operator + (const float2& lhs, const float2& rhs) { return float2(lhs.x + rhs.x, lhs.y + rhs.y); }

			/// <summary>Returns the result of a componentwise addition operation on a float2 vector and a float value.</summary>

			inline static float2 operator + (const float2& lhs, float rhs) { return float2(lhs.x + rhs, lhs.y + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float2 vector.</summary>

			inline static float2 operator + (float lhs, const float2& rhs) { return float2(lhs + rhs.x, lhs + rhs.y); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float2 vectors.</summary>

			inline static float2 operator - (const float2& lhs, const float2& rhs) { return float2(lhs.x - rhs.x, lhs.y - rhs.y); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float2 vector and a float value.</summary>

			inline static float2 operator - (const float2& lhs, float rhs) { return float2(lhs.x - rhs, lhs.y - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float2 vector.</summary>

			inline static float2 operator - (float lhs, const float2& rhs) { return float2(lhs - rhs.x, lhs - rhs.y); }


			/// <summary>Returns the result of a componentwise division operation on two float2 vectors.</summary>

			inline static float2 operator / (const float2& lhs, const float2& rhs) { return float2(lhs.x / rhs.x, lhs.y / rhs.y); }

			/// <summary>Returns the result of a componentwise division operation on a float2 vector and a float value.</summary>

			inline static float2 operator / (const float2& lhs, float rhs) { return float2(lhs.x / rhs, lhs.y / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float2 vector.</summary>

			inline static float2 operator / (float lhs, const float2& rhs) { return float2(lhs / rhs.x, lhs / rhs.y); }

			/// <summary>Returns the result of a componentwise increment operation on a float2 vector.</summary>

			inline static float2 operator ++ (float2 val) { return float2(++val.x, ++val.y); }


			/// <summary>Returns the result of a componentwise decrement operation on a float2 vector.</summary>

			inline static float2 operator -- (float2 val) { return float2(--val.x, --val.y); }


			/// <summary>Returns the result of a componentwise less than operation on two float2 vectors.</summary>

			inline static bool2 operator < (const float2& lhs, const float2& rhs) { return bool2(lhs.x < rhs.x, lhs.y < rhs.y); }

			/// <summary>Returns the result of a componentwise less than operation on a float2 vector and a float value.</summary>

			inline static bool2 operator < (const float2& lhs, float rhs) { return bool2(lhs.x < rhs, lhs.y < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float2 vector.</summary>

			inline static bool2 operator < (float lhs, const float2& rhs) { return bool2(lhs < rhs.x, lhs < rhs.y); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float2 vectors.</summary>

			inline static bool2 operator <= (const float2& lhs, const float2& rhs) { return bool2(lhs.x <= rhs.x, lhs.y <= rhs.y); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float2 vector and a float value.</summary>

			inline static bool2 operator <= (const float2& lhs, float rhs) { return bool2(lhs.x <= rhs, lhs.y <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float2 vector.</summary>

			inline static bool2 operator <= (float lhs, const float2& rhs) { return bool2(lhs <= rhs.x, lhs <= rhs.y); }


			/// <summary>Returns the result of a componentwise greater than operation on two float2 vectors.</summary>

			inline static bool2 operator > (const float2& lhs, const float2& rhs) { return bool2(lhs.x > rhs.x, lhs.y > rhs.y); }

			/// <summary>Returns the result of a componentwise greater than operation on a float2 vector and a float value.</summary>

			inline static bool2 operator > (const float2& lhs, float rhs) { return bool2(lhs.x > rhs, lhs.y > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float2 vector.</summary>

			inline static bool2 operator > (float lhs, const float2& rhs) { return bool2(lhs > rhs.x, lhs > rhs.y); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float2 vectors.</summary>

			inline static bool2 operator >= (const float2& lhs, const float2& rhs) { return bool2(lhs.x >= rhs.x, lhs.y >= rhs.y); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float2 vector and a float value.</summary>

			inline static bool2 operator >= (const float2& lhs, float rhs) { return bool2(lhs.x >= rhs, lhs.y >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float2 vector.</summary>

			inline static bool2 operator >= (float lhs, const float2& rhs) { return bool2(lhs >= rhs.x, lhs >= rhs.y); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float2 vector.</summary>

			inline static float2 operator - (float2 val) { return float2(-val.x, -val.y); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float2 vector.</summary>

			inline static float2 operator + (float2 val) { return float2(+val.x, +val.y); }


			/// <summary>Returns the result of a componentwise equality operation on two float2 vectors.</summary>

			inline static bool2 operator == (const float2& lhs, const float2& rhs) { return bool2(lhs.x == rhs.x, lhs.y == rhs.y); }

			/// <summary>Returns the result of a componentwise equality operation on a float2 vector and a float value.</summary>

			inline static bool2 operator == (const float2& lhs, float rhs) { return bool2(lhs.x == rhs, lhs.y == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float2 vector.</summary>

			inline static bool2 operator == (float lhs, const float2& rhs) { return bool2(lhs == rhs.x, lhs == rhs.y); }


			/// <summary>Returns the result of a componentwise not equal operation on two float2 vectors.</summary>

			inline static bool2 operator != (const float2& lhs, const float2& rhs) { return bool2(lhs.x != rhs.x, lhs.y != rhs.y); }

			/// <summary>Returns the result of a componentwise not equal operation on a float2 vector and a float value.</summary>

			inline static bool2 operator != (const float2& lhs, float rhs) { return bool2(lhs.x != rhs, lhs.y != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float2 vector.</summary>

			inline static bool2 operator != (float lhs, const float2& rhs) { return bool2(lhs != rhs.x, lhs != rhs.y); }
#pragma endregion
#pragma region float2x2
			struct float2x2
			{
				float2 c0, c1;
				float2x2() : c0(), c1() {}
				float2x2(float m00, float m01,
					float m10, float m11) :c0(float2(m00, m10)), c1(float2(m01, m11)) {}
				float2x2(float2 c0, float2 c1) : c0(c0), c1(c1) {}
				float2x2(float v) : c0(v), c1(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float2x2 matrices.</summary>

			inline static float2x2 operator * (const float2x2& lhs, const float2x2& rhs) { return float2x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float2x2 matrix and a float value.</summary>

			inline static float2x2 operator * (const float2x2& lhs, float rhs) { return float2x2(lhs.c0 * rhs, lhs.c1 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float2x2 matrix.</summary>

			inline static float2x2 operator * (float lhs, const float2x2& rhs) { return float2x2(lhs * rhs.c0, lhs * rhs.c1); }


			/// <summary>Returns the result of a componentwise addition operation on two float2x2 matrices.</summary>

			inline static float2x2 operator + (const float2x2& lhs, const float2x2& rhs) { return float2x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

			/// <summary>Returns the result of a componentwise addition operation on a float2x2 matrix and a float value.</summary>

			inline static float2x2 operator + (const float2x2& lhs, float rhs) { return float2x2(lhs.c0 + rhs, lhs.c1 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float2x2 matrix.</summary>

			inline static float2x2 operator + (float lhs, const float2x2& rhs) { return float2x2(lhs + rhs.c0, lhs + rhs.c1); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float2x2 matrices.</summary>

			inline static float2x2 operator - (const float2x2& lhs, const float2x2& rhs) { return float2x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float2x2 matrix and a float value.</summary>

			inline static float2x2 operator - (const float2x2& lhs, float rhs) { return float2x2(lhs.c0 - rhs, lhs.c1 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float2x2 matrix.</summary>

			inline static float2x2 operator - (float lhs, const float2x2& rhs) { return float2x2(lhs - rhs.c0, lhs - rhs.c1); }


			/// <summary>Returns the result of a componentwise division operation on two float2x2 matrices.</summary>

			inline static float2x2 operator / (const float2x2& lhs, const float2x2& rhs) { return float2x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

			/// <summary>Returns the result of a componentwise division operation on a float2x2 matrix and a float value.</summary>

			inline static float2x2 operator / (const float2x2& lhs, float rhs) { return float2x2(lhs.c0 / rhs, lhs.c1 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float2x2 matrix.</summary>

			inline static float2x2 operator / (float lhs, const float2x2& rhs) { return float2x2(lhs / rhs.c0, lhs / rhs.c1); }


			/// <summary>Returns the result of a componentwise increment operation on a float2x2 matrix.</summary>

			inline static float2x2 operator ++ (float2x2 val) { return float2x2(++val.c0, ++val.c1); }


			/// <summary>Returns the result of a componentwise decrement operation on a float2x2 matrix.</summary>

			inline static float2x2 operator -- (float2x2 val) { return float2x2(--val.c0, --val.c1); }


			/// <summary>Returns the result of a componentwise less than operation on two float2x2 matrices.</summary>

			inline static bool2x2 operator < (const float2x2& lhs, const float2x2& rhs) { return bool2x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

			/// <summary>Returns the result of a componentwise less than operation on a float2x2 matrix and a float value.</summary>

			inline static bool2x2 operator < (const float2x2& lhs, float rhs) { return bool2x2(lhs.c0 < rhs, lhs.c1 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float2x2 matrix.</summary>

			inline static bool2x2 operator < (float lhs, const float2x2& rhs) { return bool2x2(lhs < rhs.c0, lhs < rhs.c1); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float2x2 matrices.</summary>

			inline static bool2x2 operator <= (const float2x2& lhs, const float2x2& rhs) { return bool2x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float2x2 matrix and a float value.</summary>

			inline static bool2x2 operator <= (const float2x2& lhs, float rhs) { return bool2x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float2x2 matrix.</summary>

			inline static bool2x2 operator <= (float lhs, const float2x2& rhs) { return bool2x2(lhs <= rhs.c0, lhs <= rhs.c1); }


			/// <summary>Returns the result of a componentwise greater than operation on two float2x2 matrices.</summary>

			inline static bool2x2 operator > (const float2x2& lhs, const float2x2& rhs) { return bool2x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

			/// <summary>Returns the result of a componentwise greater than operation on a float2x2 matrix and a float value.</summary>

			inline static bool2x2 operator > (const float2x2& lhs, float rhs) { return bool2x2(lhs.c0 > rhs, lhs.c1 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float2x2 matrix.</summary>

			inline static bool2x2 operator > (float lhs, const float2x2& rhs) { return bool2x2(lhs > rhs.c0, lhs > rhs.c1); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float2x2 matrices.</summary>

			inline static bool2x2 operator >= (const float2x2& lhs, const float2x2& rhs) { return bool2x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float2x2 matrix and a float value.</summary>

			inline static bool2x2 operator >= (const float2x2& lhs, float rhs) { return bool2x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float2x2 matrix.</summary>

			inline static bool2x2 operator >= (float lhs, const float2x2& rhs) { return bool2x2(lhs >= rhs.c0, lhs >= rhs.c1); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float2x2 matrix.</summary>

			inline static float2x2 operator - (float2x2 val) { return float2x2(-val.c0, -val.c1); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float2x2 matrix.</summary>

			inline static float2x2 operator + (float2x2 val) { return float2x2(+val.c0, +val.c1); }


			/// <summary>Returns the result of a componentwise equality operation on two float2x2 matrices.</summary>

			inline static bool2x2 operator == (const float2x2& lhs, const float2x2& rhs) { return bool2x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

			/// <summary>Returns the result of a componentwise equality operation on a float2x2 matrix and a float value.</summary>

			inline static bool2x2 operator == (const float2x2& lhs, float rhs) { return bool2x2(lhs.c0 == rhs, lhs.c1 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float2x2 matrix.</summary>

			inline static bool2x2 operator == (float lhs, const float2x2& rhs) { return bool2x2(lhs == rhs.c0, lhs == rhs.c1); }


			/// <summary>Returns the result of a componentwise not equal operation on two float2x2 matrices.</summary>

			inline static bool2x2 operator != (const float2x2& lhs, const float2x2& rhs) { return bool2x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

			/// <summary>Returns the result of a componentwise not equal operation on a float2x2 matrix and a float value.</summary>

			inline static bool2x2 operator != (const float2x2& lhs, float rhs) { return bool2x2(lhs.c0 != rhs, lhs.c1 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float2x2 matrix.</summary>

			inline static bool2x2 operator != (float lhs, const float2x2& rhs) { return bool2x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region float2x3
			struct float2x3
			{
				float2 c0, c1, c2;
				float2x3() : c0(), c1(), c2() {}
				float2x3(float m00, float m01, float m02,
					float m10, float m11, float m12)
				{
					c0 = float2(m00, m10);
					c1 = float2(m01, m11);
					c2 = float2(m02, m12);
				}
				float2x3(float2 c0, float2 c1, float2 c2) : c0(c0), c1(c1), c2(c2) {}
				float2x3(float v) : c0(v), c1(v), c2(v) {}
			};

			/// <summary>Returns the result of a componentwise multiplication operation on two float2x3 matrices.</summary>

			inline static float2x3 operator * (const float2x3& lhs, const float2x3& rhs) { return float2x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float2x3 matrix and a float value.</summary>

			inline static float2x3 operator * (const float2x3& lhs, float rhs) { return float2x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float2x3 matrix.</summary>

			inline static float2x3 operator * (float lhs, const float2x3& rhs) { return float2x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


			/// <summary>Returns the result of a componentwise addition operation on two float2x3 matrices.</summary>

			inline static float2x3 operator + (const float2x3& lhs, const float2x3& rhs) { return float2x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

			/// <summary>Returns the result of a componentwise addition operation on a float2x3 matrix and a float value.</summary>

			inline static float2x3 operator + (const float2x3& lhs, float rhs) { return float2x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float2x3 matrix.</summary>

			inline static float2x3 operator + (float lhs, const float2x3& rhs) { return float2x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float2x3 matrices.</summary>

			inline static float2x3 operator - (const float2x3& lhs, const float2x3& rhs) { return float2x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float2x3 matrix and a float value.</summary>

			inline static float2x3 operator - (const float2x3& lhs, float rhs) { return float2x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float2x3 matrix.</summary>

			inline static float2x3 operator - (float lhs, const float2x3& rhs) { return float2x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


			/// <summary>Returns the result of a componentwise division operation on two float2x3 matrices.</summary>

			inline static float2x3 operator / (const float2x3& lhs, const float2x3& rhs) { return float2x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

			/// <summary>Returns the result of a componentwise division operation on a float2x3 matrix and a float value.</summary>

			inline static float2x3 operator / (const float2x3& lhs, float rhs) { return float2x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float2x3 matrix.</summary>

			inline static float2x3 operator / (float lhs, const float2x3& rhs) { return float2x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }


			/// <summary>Returns the result of a componentwise increment operation on a float2x3 matrix.</summary>

			inline static float2x3 operator ++ (float2x3 val) { return float2x3(++val.c0, ++val.c1, ++val.c2); }


			/// <summary>Returns the result of a componentwise decrement operation on a float2x3 matrix.</summary>

			inline static float2x3 operator -- (float2x3 val) { return float2x3(--val.c0, --val.c1, --val.c2); }


			/// <summary>Returns the result of a componentwise less than operation on two float2x3 matrices.</summary>

			inline static bool2x3 operator < (const float2x3& lhs, const float2x3& rhs) { return bool2x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

			/// <summary>Returns the result of a componentwise less than operation on a float2x3 matrix and a float value.</summary>

			inline static bool2x3 operator < (const float2x3& lhs, float rhs) { return bool2x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float2x3 matrix.</summary>

			inline static bool2x3 operator < (float lhs, const float2x3& rhs) { return bool2x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float2x3 matrices.</summary>

			inline static bool2x3 operator <= (const float2x3& lhs, const float2x3& rhs) { return bool2x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float2x3 matrix and a float value.</summary>

			inline static bool2x3 operator <= (const float2x3& lhs, float rhs) { return bool2x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float2x3 matrix.</summary>

			inline static bool2x3 operator <= (float lhs, const float2x3& rhs) { return bool2x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


			/// <summary>Returns the result of a componentwise greater than operation on two float2x3 matrices.</summary>

			inline static bool2x3 operator > (const float2x3& lhs, const float2x3& rhs) { return bool2x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

			/// <summary>Returns the result of a componentwise greater than operation on a float2x3 matrix and a float value.</summary>

			inline static bool2x3 operator > (const float2x3& lhs, float rhs) { return bool2x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float2x3 matrix.</summary>

			inline static bool2x3 operator > (float lhs, const float2x3& rhs) { return bool2x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float2x3 matrices.</summary>

			inline static bool2x3 operator >= (const float2x3& lhs, const float2x3& rhs) { return bool2x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float2x3 matrix and a float value.</summary>

			inline static bool2x3 operator >= (const float2x3& lhs, float rhs) { return bool2x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float2x3 matrix.</summary>

			inline static bool2x3 operator >= (float lhs, const float2x3& rhs) { return bool2x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float2x3 matrix.</summary>

			inline static float2x3 operator - (float2x3 val) { return float2x3(-val.c0, -val.c1, -val.c2); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float2x3 matrix.</summary>

			inline static float2x3 operator + (float2x3 val) { return float2x3(+val.c0, +val.c1, +val.c2); }


			/// <summary>Returns the result of a componentwise equality operation on two float2x3 matrices.</summary>

			inline static bool2x3 operator == (const float2x3& lhs, const float2x3& rhs) { return bool2x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

			/// <summary>Returns the result of a componentwise equality operation on a float2x3 matrix and a float value.</summary>

			inline static bool2x3 operator == (const float2x3& lhs, float rhs) { return bool2x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float2x3 matrix.</summary>

			inline static bool2x3 operator == (float lhs, const float2x3& rhs) { return bool2x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


			/// <summary>Returns the result of a componentwise not equal operation on two float2x3 matrices.</summary>

			inline static bool2x3 operator != (const float2x3& lhs, const float2x3& rhs) { return bool2x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

			/// <summary>Returns the result of a componentwise not equal operation on a float2x3 matrix and a float value.</summary>

			inline static bool2x3 operator != (const float2x3& lhs, float rhs) { return bool2x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float2x3 matrix.</summary>

			inline static bool2x3 operator != (float lhs, const float2x3& rhs) { return bool2x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region float2x4
			struct float2x4
			{
				float2 c0, c1, c2, c3;
				float2x4() : c0(), c1(), c2(), c3() {}
				float2x4(float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13)
				{
					c0 = float2(m00, m10);
					c1 = float2(m01, m11);
					c2 = float2(m02, m12);
					c3 = float2(m03, m13);
				}
				float2x4(float2 c0, float2 c1, float2 c2, float2 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
				float2x4(float v) : c0(v), c1(v), c2(v), c3(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float2x4 matrices.</summary>

			inline static float2x4 operator * (const float2x4& lhs, const float2x4& rhs) { return float2x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float2x4 matrix and a float value.</summary>

			inline static float2x4 operator * (const float2x4& lhs, float rhs) { return float2x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float2x4 matrix.</summary>

			inline static float2x4 operator * (float lhs, const float2x4& rhs) { return float2x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


			/// <summary>Returns the result of a componentwise addition operation on two float2x4 matrices.</summary>

			inline static float2x4 operator + (const float2x4& lhs, const float2x4& rhs) { return float2x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

			/// <summary>Returns the result of a componentwise addition operation on a float2x4 matrix and a float value.</summary>

			inline static float2x4 operator + (const float2x4& lhs, float rhs) { return float2x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float2x4 matrix.</summary>

			inline static float2x4 operator + (float lhs, const float2x4& rhs) { return float2x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float2x4 matrices.</summary>

			inline static float2x4 operator - (const float2x4& lhs, const float2x4& rhs) { return float2x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float2x4 matrix and a float value.</summary>

			inline static float2x4 operator - (const float2x4& lhs, float rhs) { return float2x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float2x4 matrix.</summary>

			inline static float2x4 operator - (float lhs, const float2x4& rhs) { return float2x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


			/// <summary>Returns the result of a componentwise division operation on two float2x4 matrices.</summary>

			inline static float2x4 operator / (const float2x4& lhs, const float2x4& rhs) { return float2x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

			/// <summary>Returns the result of a componentwise division operation on a float2x4 matrix and a float value.</summary>

			inline static float2x4 operator / (const float2x4& lhs, float rhs) { return float2x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float2x4 matrix.</summary>

			inline static float2x4 operator / (float lhs, const float2x4& rhs) { return float2x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


			/// <summary>Returns the result of a componentwise increment operation on a float2x4 matrix.</summary>

			inline static float2x4 operator ++ (float2x4 val) { return float2x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


			/// <summary>Returns the result of a componentwise decrement operation on a float2x4 matrix.</summary>

			inline static float2x4 operator -- (float2x4 val) { return float2x4(--val.c0, --val.c1, --val.c2, --val.c3); }


			/// <summary>Returns the result of a componentwise less than operation on two float2x4 matrices.</summary>

			inline static bool2x4 operator < (const float2x4& lhs, const float2x4& rhs) { return bool2x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

			/// <summary>Returns the result of a componentwise less than operation on a float2x4 matrix and a float value.</summary>

			inline static bool2x4 operator < (const float2x4& lhs, float rhs) { return bool2x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float2x4 matrix.</summary>

			inline static bool2x4 operator < (float lhs, const float2x4& rhs) { return bool2x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float2x4 matrices.</summary>

			inline static bool2x4 operator <= (const float2x4& lhs, const float2x4& rhs) { return bool2x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float2x4 matrix and a float value.</summary>

			inline static bool2x4 operator <= (const float2x4& lhs, float rhs) { return bool2x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float2x4 matrix.</summary>

			inline static bool2x4 operator <= (float lhs, const float2x4& rhs) { return bool2x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


			/// <summary>Returns the result of a componentwise greater than operation on two float2x4 matrices.</summary>

			inline static bool2x4 operator > (const float2x4& lhs, const float2x4& rhs) { return bool2x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

			/// <summary>Returns the result of a componentwise greater than operation on a float2x4 matrix and a float value.</summary>

			inline static bool2x4 operator > (const float2x4& lhs, float rhs) { return bool2x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float2x4 matrix.</summary>

			inline static bool2x4 operator > (float lhs, const float2x4& rhs) { return bool2x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float2x4 matrices.</summary>

			inline static bool2x4 operator >= (const float2x4& lhs, const float2x4& rhs) { return bool2x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float2x4 matrix and a float value.</summary>

			inline static bool2x4 operator >= (const float2x4& lhs, float rhs) { return bool2x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float2x4 matrix.</summary>

			inline static bool2x4 operator >= (float lhs, const float2x4& rhs) { return bool2x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float2x4 matrix.</summary>

			inline static float2x4 operator - (float2x4 val) { return float2x4(-val.c0, -val.c1, -val.c2, -val.c3); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float2x4 matrix.</summary>

			inline static float2x4 operator + (float2x4 val) { return float2x4(+val.c0, +val.c1, +val.c2, +val.c3); }


			/// <summary>Returns the result of a componentwise equality operation on two float2x4 matrices.</summary>

			inline static bool2x4 operator == (const float2x4& lhs, const float2x4& rhs) { return bool2x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

			/// <summary>Returns the result of a componentwise equality operation on a float2x4 matrix and a float value.</summary>

			inline static bool2x4 operator == (const float2x4& lhs, float rhs) { return bool2x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float2x4 matrix.</summary>

			inline static bool2x4 operator == (float lhs, const float2x4& rhs) { return bool2x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


			/// <summary>Returns the result of a componentwise not equal operation on two float2x4 matrices.</summary>

			inline static bool2x4 operator != (const float2x4& lhs, const float2x4& rhs) { return bool2x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

			/// <summary>Returns the result of a componentwise not equal operation on a float2x4 matrix and a float value.</summary>

			inline static bool2x4 operator != (const float2x4& lhs, float rhs) { return bool2x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float2x4 matrix.</summary>

			inline static bool2x4 operator != (float lhs, const float2x4& rhs) { return bool2x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }



#pragma endregion
#pragma region float3
			struct float3 {
				float x, y, z;
				float3() : x(0), y(0), z(0) {}
				float3(float x, float y, float z) : x(x), y(y), z(z) {}
				float3(float v) : x(v), y(v), z(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float3 vectors.</summary>

			inline static float3 operator * (const float3& lhs, const float3& rhs) { return float3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float3 vector and a float value.</summary>

			inline static float3 operator * (const float3& lhs, float rhs) { return float3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float3 vector.</summary>

			inline static float3 operator * (float lhs, const float3& rhs) { return float3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z); }


			/// <summary>Returns the result of a componentwise addition operation on two float3 vectors.</summary>

			inline static float3 operator + (const float3& lhs, const float3& rhs) { return float3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }

			/// <summary>Returns the result of a componentwise addition operation on a float3 vector and a float value.</summary>

			inline static float3 operator + (const float3& lhs, float rhs) { return float3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float3 vector.</summary>

			inline static float3 operator + (float lhs, const float3& rhs) { return float3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float3 vectors.</summary>

			inline static float3 operator - (const float3& lhs, const float3& rhs) { return float3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float3 vector and a float value.</summary>

			inline static float3 operator - (const float3& lhs, float rhs) { return float3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float3 vector.</summary>

			inline static float3 operator - (float lhs, const float3& rhs) { return float3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z); }


			/// <summary>Returns the result of a componentwise division operation on two float3 vectors.</summary>

			inline static float3 operator / (const float3& lhs, const float3& rhs) { return float3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

			/// <summary>Returns the result of a componentwise division operation on a float3 vector and a float value.</summary>

			inline static float3 operator / (const float3& lhs, float rhs) { return float3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float3 vector.</summary>

			inline static float3 operator / (float lhs, const float3& rhs) { return float3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z); }


			/// <summary>Returns the result of a componentwise increment operation on a float3 vector.</summary>

			inline static float3 operator ++ (float3 val) { return float3(++val.x, ++val.y, ++val.z); }


			/// <summary>Returns the result of a componentwise decrement operation on a float3 vector.</summary>

			inline static float3 operator -- (float3 val) { return float3(--val.x, --val.y, --val.z); }


			/// <summary>Returns the result of a componentwise less than operation on two float3 vectors.</summary>

			inline static bool3 operator < (const float3& lhs, const float3& rhs) { return bool3(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z); }

			/// <summary>Returns the result of a componentwise less than operation on a float3 vector and a float value.</summary>

			inline static bool3 operator < (const float3& lhs, float rhs) { return bool3(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float3 vector.</summary>

			inline static bool3 operator < (float lhs, const float3& rhs) { return bool3(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float3 vectors.</summary>

			inline static bool3 operator <= (const float3& lhs, const float3& rhs) { return bool3(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float3 vector and a float value.</summary>

			inline static bool3 operator <= (const float3& lhs, float rhs) { return bool3(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float3 vector.</summary>

			inline static bool3 operator <= (float lhs, const float3& rhs) { return bool3(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z); }


			/// <summary>Returns the result of a componentwise greater than operation on two float3 vectors.</summary>

			inline static bool3 operator > (const float3& lhs, const float3& rhs) { return bool3(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z); }

			/// <summary>Returns the result of a componentwise greater than operation on a float3 vector and a float value.</summary>

			inline static bool3 operator > (const float3& lhs, float rhs) { return bool3(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float3 vector.</summary>

			inline static bool3 operator > (float lhs, const float3& rhs) { return bool3(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float3 vectors.</summary>

			inline static bool3 operator >= (const float3& lhs, const float3& rhs) { return bool3(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float3 vector and a float value.</summary>

			inline static bool3 operator >= (const float3& lhs, float rhs) { return bool3(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float3 vector.</summary>

			inline static bool3 operator >= (float lhs, const float3& rhs) { return bool3(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float3 vector.</summary>

			inline static float3 operator - (float3 val) { return float3(-val.x, -val.y, -val.z); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float3 vector.</summary>

			inline static float3 operator + (float3 val) { return float3(+val.x, +val.y, +val.z); }


			/// <summary>Returns the result of a componentwise equality operation on two float3 vectors.</summary>

			inline static bool3 operator == (const float3& lhs, const float3& rhs) { return bool3(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z); }

			/// <summary>Returns the result of a componentwise equality operation on a float3 vector and a float value.</summary>

			inline static bool3 operator == (const float3& lhs, float rhs) { return bool3(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float3 vector.</summary>

			inline static bool3 operator == (float lhs, const float3& rhs) { return bool3(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z); }


			/// <summary>Returns the result of a componentwise not equal operation on two float3 vectors.</summary>

			inline static bool3 operator != (const float3& lhs, const float3& rhs) { return bool3(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z); }

			/// <summary>Returns the result of a componentwise not equal operation on a float3 vector and a float value.</summary>

			inline static bool3 operator != (const float3& lhs, float rhs) { return bool3(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float3 vector.</summary>

			inline static bool3 operator != (float lhs, const float3& rhs) { return bool3(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z); }


#pragma endregion
#pragma region float3x2
			struct float3x2
			{
				float3 c0, c1;
				float3x2() : c0(), c1() {}
				float3x2(float m00, float m01,
					float m10, float m11,
					float m20, float m21)
				{
					c0 = float3(m00, m10, m20);
					c1 = float3(m01, m11, m21);
				}

				float3x2(float3 c0, float3 c1) : c0(c0), c1(c1) {}
				float3x2(float v) : c0(v), c1(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float3x2 matrices.</summary>

			inline static float3x2 operator * (const float3x2& lhs, const float3x2& rhs) { return float3x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float3x2 matrix and a float value.</summary>

			inline static float3x2 operator * (const float3x2& lhs, float rhs) { return float3x2(lhs.c0 * rhs, lhs.c1 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float3x2 matrix.</summary>

			inline static float3x2 operator * (float lhs, const float3x2& rhs) { return float3x2(lhs * rhs.c0, lhs * rhs.c1); }


			/// <summary>Returns the result of a componentwise addition operation on two float3x2 matrices.</summary>

			inline static float3x2 operator + (const float3x2& lhs, const float3x2& rhs) { return float3x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

			/// <summary>Returns the result of a componentwise addition operation on a float3x2 matrix and a float value.</summary>

			inline static float3x2 operator + (const float3x2& lhs, float rhs) { return float3x2(lhs.c0 + rhs, lhs.c1 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float3x2 matrix.</summary>

			inline static float3x2 operator + (float lhs, const float3x2& rhs) { return float3x2(lhs + rhs.c0, lhs + rhs.c1); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float3x2 matrices.</summary>

			inline static float3x2 operator - (const float3x2& lhs, const float3x2& rhs) { return float3x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float3x2 matrix and a float value.</summary>

			inline static float3x2 operator - (const float3x2& lhs, float rhs) { return float3x2(lhs.c0 - rhs, lhs.c1 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float3x2 matrix.</summary>

			inline static float3x2 operator - (float lhs, const float3x2& rhs) { return float3x2(lhs - rhs.c0, lhs - rhs.c1); }


			/// <summary>Returns the result of a componentwise division operation on two float3x2 matrices.</summary>

			inline static float3x2 operator / (const float3x2& lhs, const float3x2& rhs) { return float3x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

			/// <summary>Returns the result of a componentwise division operation on a float3x2 matrix and a float value.</summary>

			inline static float3x2 operator / (const float3x2& lhs, float rhs) { return float3x2(lhs.c0 / rhs, lhs.c1 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float3x2 matrix.</summary>

			inline static float3x2 operator / (float lhs, const float3x2& rhs) { return float3x2(lhs / rhs.c0, lhs / rhs.c1); }


			/// <summary>Returns the result of a componentwise increment operation on a float3x2 matrix.</summary>

			inline static float3x2 operator ++ (float3x2 val) { return float3x2(++val.c0, ++val.c1); }


			/// <summary>Returns the result of a componentwise decrement operation on a float3x2 matrix.</summary>

			inline static float3x2 operator -- (float3x2 val) { return float3x2(--val.c0, --val.c1); }


			/// <summary>Returns the result of a componentwise less than operation on two float3x2 matrices.</summary>

			inline static bool3x2 operator < (const float3x2& lhs, const float3x2& rhs) { return bool3x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

			/// <summary>Returns the result of a componentwise less than operation on a float3x2 matrix and a float value.</summary>

			inline static bool3x2 operator < (const float3x2& lhs, float rhs) { return bool3x2(lhs.c0 < rhs, lhs.c1 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float3x2 matrix.</summary>

			inline static bool3x2 operator < (float lhs, const float3x2& rhs) { return bool3x2(lhs < rhs.c0, lhs < rhs.c1); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float3x2 matrices.</summary>

			inline static bool3x2 operator <= (const float3x2& lhs, const float3x2& rhs) { return bool3x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float3x2 matrix and a float value.</summary>

			inline static bool3x2 operator <= (const float3x2& lhs, float rhs) { return bool3x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float3x2 matrix.</summary>

			inline static bool3x2 operator <= (float lhs, const float3x2& rhs) { return bool3x2(lhs <= rhs.c0, lhs <= rhs.c1); }


			/// <summary>Returns the result of a componentwise greater than operation on two float3x2 matrices.</summary>

			inline static bool3x2 operator > (const float3x2& lhs, const float3x2& rhs) { return bool3x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

			/// <summary>Returns the result of a componentwise greater than operation on a float3x2 matrix and a float value.</summary>

			inline static bool3x2 operator > (const float3x2& lhs, float rhs) { return bool3x2(lhs.c0 > rhs, lhs.c1 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float3x2 matrix.</summary>

			inline static bool3x2 operator > (float lhs, const float3x2& rhs) { return bool3x2(lhs > rhs.c0, lhs > rhs.c1); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float3x2 matrices.</summary>

			inline static bool3x2 operator >= (const float3x2& lhs, const float3x2& rhs) { return bool3x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float3x2 matrix and a float value.</summary>

			inline static bool3x2 operator >= (const float3x2& lhs, float rhs) { return bool3x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float3x2 matrix.</summary>

			inline static bool3x2 operator >= (float lhs, const float3x2& rhs) { return bool3x2(lhs >= rhs.c0, lhs >= rhs.c1); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float3x2 matrix.</summary>

			inline static float3x2 operator - (float3x2 val) { return float3x2(-val.c0, -val.c1); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float3x2 matrix.</summary>

			inline static float3x2 operator + (float3x2 val) { return float3x2(+val.c0, +val.c1); }


			/// <summary>Returns the result of a componentwise equality operation on two float3x2 matrices.</summary>

			inline static bool3x2 operator == (const float3x2& lhs, const float3x2& rhs) { return bool3x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

			/// <summary>Returns the result of a componentwise equality operation on a float3x2 matrix and a float value.</summary>

			inline static bool3x2 operator == (const float3x2& lhs, float rhs) { return bool3x2(lhs.c0 == rhs, lhs.c1 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float3x2 matrix.</summary>

			inline static bool3x2 operator == (float lhs, const float3x2& rhs) { return bool3x2(lhs == rhs.c0, lhs == rhs.c1); }


			/// <summary>Returns the result of a componentwise not equal operation on two float3x2 matrices.</summary>

			inline static bool3x2 operator != (const float3x2& lhs, const float3x2& rhs) { return bool3x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

			/// <summary>Returns the result of a componentwise not equal operation on a float3x2 matrix and a float value.</summary>

			inline static bool3x2 operator != (const float3x2& lhs, float rhs) { return bool3x2(lhs.c0 != rhs, lhs.c1 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float3x2 matrix.</summary>

			inline static bool3x2 operator != (float lhs, const float3x2& rhs) { return bool3x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region float3x3
			struct float3x3
			{
				float3 c0, c1, c2;
				float3x3() : c0(), c1(), c2() {}
				float3x3(float m00, float m01, float m02,
					float m10, float m11, float m12,
					float m20, float m21, float m22)
				{
					c0 = float3(m00, m10, m20);
					c1 = float3(m01, m11, m21);
					c2 = float3(m02, m12, m22);
				}
				float3x3(float3 c0, float3 c1, float3 c2) : c0(c0), c1(c1), c2(c2) {}
				float3x3(float v) : c0(v), c1(v), c2(v) {}
				
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float3x3 matrices.</summary>

			inline static float3x3 operator * (const float3x3& lhs, const float3x3& rhs) { return float3x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float3x3 matrix and a float value.</summary>

			inline static float3x3 operator * (const float3x3& lhs, float rhs) { return float3x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float3x3 matrix.</summary>

			inline static float3x3 operator * (float lhs, const float3x3& rhs) { return float3x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


			/// <summary>Returns the result of a componentwise addition operation on two float3x3 matrices.</summary>

			inline static float3x3 operator + (const float3x3& lhs, const float3x3& rhs) { return float3x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

			/// <summary>Returns the result of a componentwise addition operation on a float3x3 matrix and a float value.</summary>

			inline static float3x3 operator + (const float3x3& lhs, float rhs) { return float3x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float3x3 matrix.</summary>

			inline static float3x3 operator + (float lhs, const float3x3& rhs) { return float3x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float3x3 matrices.</summary>

			inline static float3x3 operator - (const float3x3& lhs, const float3x3& rhs) { return float3x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float3x3 matrix and a float value.</summary>

			inline static float3x3 operator - (const float3x3& lhs, float rhs) { return float3x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float3x3 matrix.</summary>

			inline static float3x3 operator - (float lhs, const float3x3& rhs) { return float3x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


			/// <summary>Returns the result of a componentwise division operation on two float3x3 matrices.</summary>

			inline static float3x3 operator / (const float3x3& lhs, const float3x3& rhs) { return float3x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

			/// <summary>Returns the result of a componentwise division operation on a float3x3 matrix and a float value.</summary>

			inline static float3x3 operator / (const float3x3& lhs, float rhs) { return float3x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float3x3 matrix.</summary>

			inline static float3x3 operator / (float lhs, const float3x3& rhs) { return float3x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

			/// <summary>Returns the result of a componentwise increment operation on a float3x3 matrix.</summary>

			inline static float3x3 operator ++ (float3x3 val) { return float3x3(++val.c0, ++val.c1, ++val.c2); }


			/// <summary>Returns the result of a componentwise decrement operation on a float3x3 matrix.</summary>

			inline static float3x3 operator -- (float3x3 val) { return float3x3(--val.c0, --val.c1, --val.c2); }


			/// <summary>Returns the result of a componentwise less than operation on two float3x3 matrices.</summary>

			inline static bool3x3 operator < (const float3x3& lhs, const float3x3& rhs) { return bool3x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

			/// <summary>Returns the result of a componentwise less than operation on a float3x3 matrix and a float value.</summary>

			inline static bool3x3 operator < (const float3x3& lhs, float rhs) { return bool3x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float3x3 matrix.</summary>

			inline static bool3x3 operator < (float lhs, const float3x3& rhs) { return bool3x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float3x3 matrices.</summary>

			inline static bool3x3 operator <= (const float3x3& lhs, const float3x3& rhs) { return bool3x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float3x3 matrix and a float value.</summary>

			inline static bool3x3 operator <= (const float3x3& lhs, float rhs) { return bool3x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float3x3 matrix.</summary>

			inline static bool3x3 operator <= (float lhs, const float3x3& rhs) { return bool3x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


			/// <summary>Returns the result of a componentwise greater than operation on two float3x3 matrices.</summary>

			inline static bool3x3 operator > (const float3x3& lhs, const float3x3& rhs) { return bool3x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

			/// <summary>Returns the result of a componentwise greater than operation on a float3x3 matrix and a float value.</summary>

			inline static bool3x3 operator > (const float3x3& lhs, float rhs) { return bool3x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float3x3 matrix.</summary>

			inline static bool3x3 operator > (float lhs, const float3x3& rhs) { return bool3x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float3x3 matrices.</summary>

			inline static bool3x3 operator >= (const float3x3& lhs, const float3x3& rhs) { return bool3x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float3x3 matrix and a float value.</summary>

			inline static bool3x3 operator >= (const float3x3& lhs, float rhs) { return bool3x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float3x3 matrix.</summary>

			inline static bool3x3 operator >= (float lhs, const float3x3& rhs) { return bool3x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float3x3 matrix.</summary>

			inline static float3x3 operator - (float3x3 val) { return float3x3(-val.c0, -val.c1, -val.c2); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float3x3 matrix.</summary>

			inline static float3x3 operator + (float3x3 val) { return float3x3(+val.c0, +val.c1, +val.c2); }


			/// <summary>Returns the result of a componentwise equality operation on two float3x3 matrices.</summary>

			inline static bool3x3 operator == (const float3x3& lhs, const float3x3& rhs) { return bool3x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

			/// <summary>Returns the result of a componentwise equality operation on a float3x3 matrix and a float value.</summary>

			inline static bool3x3 operator == (const float3x3& lhs, float rhs) { return bool3x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float3x3 matrix.</summary>

			inline static bool3x3 operator == (float lhs, const float3x3& rhs) { return bool3x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


			/// <summary>Returns the result of a componentwise not equal operation on two float3x3 matrices.</summary>

			inline static bool3x3 operator != (const float3x3& lhs, const float3x3& rhs) { return bool3x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

			/// <summary>Returns the result of a componentwise not equal operation on a float3x3 matrix and a float value.</summary>

			inline static bool3x3 operator != (const float3x3& lhs, float rhs) { return bool3x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float3x3 matrix.</summary>

			inline static bool3x3 operator != (float lhs, const float3x3& rhs) { return bool3x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region float3x4
			struct float3x4
			{
				float3 c0, c1, c2, c3;
				float3x4() : c0(), c1(), c2(), c3() {}
				float3x4(float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23)
				{
					c0 = float3(m00, m10, m20);
					c1 = float3(m01, m11, m21);
					c2 = float3(m02, m12, m22);
					c3 = float3(m03, m13, m23);
				}
				float3x4(float3 c0, float3 c1, float3 c2, float3 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
				float3x4(float v) : c0(v), c1(v), c2(v), c3(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float3x4 matrices.</summary>

			inline static float3x4 operator * (const float3x4& lhs, const float3x4& rhs) { return float3x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float3x4 matrix and a float value.</summary>

			inline static float3x4 operator * (const float3x4& lhs, float rhs) { return float3x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float3x4 matrix.</summary>

			inline static float3x4 operator * (float lhs, const float3x4& rhs) { return float3x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


			/// <summary>Returns the result of a componentwise addition operation on two float3x4 matrices.</summary>

			inline static float3x4 operator + (const float3x4& lhs, const float3x4& rhs) { return float3x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

			/// <summary>Returns the result of a componentwise addition operation on a float3x4 matrix and a float value.</summary>

			inline static float3x4 operator + (const float3x4& lhs, float rhs) { return float3x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float3x4 matrix.</summary>

			inline static float3x4 operator + (float lhs, const float3x4& rhs) { return float3x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float3x4 matrices.</summary>

			inline static float3x4 operator - (const float3x4& lhs, const float3x4& rhs) { return float3x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float3x4 matrix and a float value.</summary>

			inline static float3x4 operator - (const float3x4& lhs, float rhs) { return float3x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float3x4 matrix.</summary>

			inline static float3x4 operator - (float lhs, const float3x4& rhs) { return float3x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


			/// <summary>Returns the result of a componentwise division operation on two float3x4 matrices.</summary>

			inline static float3x4 operator / (const float3x4& lhs, const float3x4& rhs) { return float3x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

			/// <summary>Returns the result of a componentwise division operation on a float3x4 matrix and a float value.</summary>

			inline static float3x4 operator / (const float3x4& lhs, float rhs) { return float3x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float3x4 matrix.</summary>

			inline static float3x4 operator / (float lhs, const float3x4& rhs) { return float3x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }

			/// <summary>Returns the result of a componentwise increment operation on a float3x4 matrix.</summary>

			inline static float3x4 operator ++ (float3x4 val) { return float3x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


			/// <summary>Returns the result of a componentwise decrement operation on a float3x4 matrix.</summary>

			inline static float3x4 operator -- (float3x4 val) { return float3x4(--val.c0, --val.c1, --val.c2, --val.c3); }


			/// <summary>Returns the result of a componentwise less than operation on two float3x4 matrices.</summary>

			inline static bool3x4 operator < (const float3x4& lhs, const float3x4& rhs) { return bool3x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

			/// <summary>Returns the result of a componentwise less than operation on a float3x4 matrix and a float value.</summary>

			inline static bool3x4 operator < (const float3x4& lhs, float rhs) { return bool3x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float3x4 matrix.</summary>

			inline static bool3x4 operator < (float lhs, const float3x4& rhs) { return bool3x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float3x4 matrices.</summary>

			inline static bool3x4 operator <= (const float3x4& lhs, const float3x4& rhs) { return bool3x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float3x4 matrix and a float value.</summary>

			inline static bool3x4 operator <= (const float3x4& lhs, float rhs) { return bool3x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float3x4 matrix.</summary>

			inline static bool3x4 operator <= (float lhs, const float3x4& rhs) { return bool3x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


			/// <summary>Returns the result of a componentwise greater than operation on two float3x4 matrices.</summary>

			inline static bool3x4 operator > (const float3x4& lhs, const float3x4& rhs) { return bool3x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

			/// <summary>Returns the result of a componentwise greater than operation on a float3x4 matrix and a float value.</summary>

			inline static bool3x4 operator > (const float3x4& lhs, float rhs) { return bool3x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float3x4 matrix.</summary>

			inline static bool3x4 operator > (float lhs, const float3x4& rhs) { return bool3x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float3x4 matrices.</summary>

			inline static bool3x4 operator >= (const float3x4& lhs, const float3x4& rhs) { return bool3x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float3x4 matrix and a float value.</summary>

			inline static bool3x4 operator >= (const float3x4& lhs, float rhs) { return bool3x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float3x4 matrix.</summary>

			inline static bool3x4 operator >= (float lhs, const float3x4& rhs) { return bool3x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float3x4 matrix.</summary>

			inline static float3x4 operator - (float3x4 val) { return float3x4(-val.c0, -val.c1, -val.c2, -val.c3); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float3x4 matrix.</summary>

			inline static float3x4 operator + (float3x4 val) { return float3x4(+val.c0, +val.c1, +val.c2, +val.c3); }


			/// <summary>Returns the result of a componentwise equality operation on two float3x4 matrices.</summary>

			inline static bool3x4 operator == (const float3x4& lhs, const float3x4& rhs) { return bool3x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

			/// <summary>Returns the result of a componentwise equality operation on a float3x4 matrix and a float value.</summary>

			inline static bool3x4 operator == (const float3x4& lhs, float rhs) { return bool3x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float3x4 matrix.</summary>

			inline static bool3x4 operator == (float lhs, const float3x4& rhs) { return bool3x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


			/// <summary>Returns the result of a componentwise not equal operation on two float3x4 matrices.</summary>

			inline static bool3x4 operator != (const float3x4& lhs, const float3x4& rhs) { return bool3x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

			/// <summary>Returns the result of a componentwise not equal operation on a float3x4 matrix and a float value.</summary>

			inline static bool3x4 operator != (const float3x4& lhs, float rhs) { return bool3x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float3x4 matrix.</summary>

			inline static bool3x4 operator != (float lhs, const float3x4& rhs) { return bool3x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region float4
			struct float4 {
				float x, y, z, w;
				float4() : x(0), y(0), z(0), w(0) {}
				float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
				float4(float v) : x(v), y(v), z(v), w(v) {}
				float4(float3 xyz, float w) : w(w)
				{
					x = xyz.x;
					y = xyz.y;
					z = xyz.z;
				}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float4 vectors.</summary>

			inline static float4 operator * (const float4& lhs, const float4& rhs) { return float4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float4 vector and a float value.</summary>

			inline static float4 operator * (const float4& lhs, float rhs) { return float4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float4 vector.</summary>

			inline static float4 operator * (float lhs, const float4& rhs) { return float4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }


			/// <summary>Returns the result of a componentwise addition operation on two float4 vectors.</summary>

			inline static float4 operator + (const float4& lhs, const float4& rhs) { return float4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }

			/// <summary>Returns the result of a componentwise addition operation on a float4 vector and a float value.</summary>

			inline static float4 operator + (const float4& lhs, float rhs) { return float4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float4 vector.</summary>

			inline static float4 operator + (float lhs, const float4& rhs) { return float4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float4 vectors.</summary>

			inline static float4 operator - (const float4& lhs, const float4& rhs) { return float4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float4 vector and a float value.</summary>

			inline static float4 operator - (const float4& lhs, float rhs) { return float4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float4 vector.</summary>

			inline static float4 operator - (float lhs, const float4& rhs) { return float4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w); }


			/// <summary>Returns the result of a componentwise division operation on two float4 vectors.</summary>

			inline static float4 operator / (const float4& lhs, const float4& rhs) { return float4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }

			/// <summary>Returns the result of a componentwise division operation on a float4 vector and a float value.</summary>

			inline static float4 operator / (const float4& lhs, float rhs) { return float4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float4 vector.</summary>

			inline static float4 operator / (float lhs, const float4& rhs) { return float4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w); }

			/// <summary>Returns the result of a componentwise increment operation on a float4 vector.</summary>

			inline static float4 operator ++ (float4 val) { return float4(++val.x, ++val.y, ++val.z, ++val.w); }


			/// <summary>Returns the result of a componentwise decrement operation on a float4 vector.</summary>

			inline static float4 operator -- (float4 val) { return float4(--val.x, --val.y, --val.z, --val.w); }


			/// <summary>Returns the result of a componentwise less than operation on two float4 vectors.</summary>

			inline static bool4 operator < (const float4& lhs, const float4& rhs) { return bool4(lhs.x < rhs.x, lhs.y < rhs.y, lhs.z < rhs.z, lhs.w < rhs.w); }

			/// <summary>Returns the result of a componentwise less than operation on a float4 vector and a float value.</summary>

			inline static bool4 operator < (const float4& lhs, float rhs) { return bool4(lhs.x < rhs, lhs.y < rhs, lhs.z < rhs, lhs.w < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float4 vector.</summary>

			inline static bool4 operator < (float lhs, const float4& rhs) { return bool4(lhs < rhs.x, lhs < rhs.y, lhs < rhs.z, lhs < rhs.w); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float4 vectors.</summary>

			inline static bool4 operator <= (const float4& lhs, const float4& rhs) { return bool4(lhs.x <= rhs.x, lhs.y <= rhs.y, lhs.z <= rhs.z, lhs.w <= rhs.w); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float4 vector and a float value.</summary>

			inline static bool4 operator <= (const float4& lhs, float rhs) { return bool4(lhs.x <= rhs, lhs.y <= rhs, lhs.z <= rhs, lhs.w <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float4 vector.</summary>

			inline static bool4 operator <= (float lhs, const float4& rhs) { return bool4(lhs <= rhs.x, lhs <= rhs.y, lhs <= rhs.z, lhs <= rhs.w); }


			/// <summary>Returns the result of a componentwise greater than operation on two float4 vectors.</summary>

			inline static bool4 operator > (const float4& lhs, const float4& rhs) { return bool4(lhs.x > rhs.x, lhs.y > rhs.y, lhs.z > rhs.z, lhs.w > rhs.w); }

			/// <summary>Returns the result of a componentwise greater than operation on a float4 vector and a float value.</summary>

			inline static bool4 operator > (const float4& lhs, float rhs) { return bool4(lhs.x > rhs, lhs.y > rhs, lhs.z > rhs, lhs.w > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float4 vector.</summary>

			inline static bool4 operator > (float lhs, const float4& rhs) { return bool4(lhs > rhs.x, lhs > rhs.y, lhs > rhs.z, lhs > rhs.w); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float4 vectors.</summary>

			inline static bool4 operator >= (const float4& lhs, const float4& rhs) { return bool4(lhs.x >= rhs.x, lhs.y >= rhs.y, lhs.z >= rhs.z, lhs.w >= rhs.w); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float4 vector and a float value.</summary>

			inline static bool4 operator >= (const float4& lhs, float rhs) { return bool4(lhs.x >= rhs, lhs.y >= rhs, lhs.z >= rhs, lhs.w >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float4 vector.</summary>

			inline static bool4 operator >= (float lhs, const float4& rhs) { return bool4(lhs >= rhs.x, lhs >= rhs.y, lhs >= rhs.z, lhs >= rhs.w); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float4 vector.</summary>

			inline static float4 operator - (float4 val) { return float4(-val.x, -val.y, -val.z, -val.w); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float4 vector.</summary>

			inline static float4 operator + (float4 val) { return float4(+val.x, +val.y, +val.z, +val.w); }


			/// <summary>Returns the result of a componentwise equality operation on two float4 vectors.</summary>

			inline static bool4 operator == (const float4& lhs, const float4& rhs) { return bool4(lhs.x == rhs.x, lhs.y == rhs.y, lhs.z == rhs.z, lhs.w == rhs.w); }

			/// <summary>Returns the result of a componentwise equality operation on a float4 vector and a float value.</summary>

			inline static bool4 operator == (const float4& lhs, float rhs) { return bool4(lhs.x == rhs, lhs.y == rhs, lhs.z == rhs, lhs.w == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float4 vector.</summary>

			inline static bool4 operator == (float lhs, const float4& rhs) { return bool4(lhs == rhs.x, lhs == rhs.y, lhs == rhs.z, lhs == rhs.w); }


			/// <summary>Returns the result of a componentwise not equal operation on two float4 vectors.</summary>

			inline static bool4 operator != (const float4& lhs, const float4& rhs) { return bool4(lhs.x != rhs.x, lhs.y != rhs.y, lhs.z != rhs.z, lhs.w != rhs.w); }

			/// <summary>Returns the result of a componentwise not equal operation on a float4 vector and a float value.</summary>

			inline static bool4 operator != (const float4& lhs, float rhs) { return bool4(lhs.x != rhs, lhs.y != rhs, lhs.z != rhs, lhs.w != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float4 vector.</summary>

			inline static bool4 operator != (float lhs, const float4& rhs) { return bool4(lhs != rhs.x, lhs != rhs.y, lhs != rhs.z, lhs != rhs.w); }


#pragma endregion
#pragma region float4x2
			struct float4x2
			{
				float4 c0, c1;
				float4x2() : c0(), c1() {}
				float4x2(float m00, float m01,
					float m10, float m11,
					float m20, float m21,
					float m30, float m31)
				{
					c0 = float4(m00, m10, m20, m30);
					c1 = float4(m01, m11, m21, m31);
				}
				float4x2(float4 c0, float4 c1) : c0(c0), c1(c1) {}
				float4x2(float v) : c0(v), c1(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float4x2 matrices.</summary>

			inline static float4x2 operator * (const float4x2& lhs, const float4x2& rhs) { return float4x2(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float4x2 matrix and a float value.</summary>

			inline static float4x2 operator * (const float4x2& lhs, float rhs) { return float4x2(lhs.c0 * rhs, lhs.c1 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float4x2 matrix.</summary>

			inline static float4x2 operator * (float lhs, const float4x2& rhs) { return float4x2(lhs * rhs.c0, lhs * rhs.c1); }


			/// <summary>Returns the result of a componentwise addition operation on two float4x2 matrices.</summary>

			inline static float4x2 operator + (const float4x2& lhs, const float4x2& rhs) { return float4x2(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1); }

			/// <summary>Returns the result of a componentwise addition operation on a float4x2 matrix and a float value.</summary>

			inline static float4x2 operator + (const float4x2& lhs, float rhs) { return float4x2(lhs.c0 + rhs, lhs.c1 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float4x2 matrix.</summary>

			inline static float4x2 operator + (float lhs, const float4x2& rhs) { return float4x2(lhs + rhs.c0, lhs + rhs.c1); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float4x2 matrices.</summary>

			inline static float4x2 operator - (const float4x2& lhs, const float4x2& rhs) { return float4x2(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float4x2 matrix and a float value.</summary>

			inline static float4x2 operator - (const float4x2& lhs, float rhs) { return float4x2(lhs.c0 - rhs, lhs.c1 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float4x2 matrix.</summary>

			inline static float4x2 operator - (float lhs, const float4x2& rhs) { return float4x2(lhs - rhs.c0, lhs - rhs.c1); }


			/// <summary>Returns the result of a componentwise division operation on two float4x2 matrices.</summary>

			inline static float4x2 operator / (const float4x2& lhs, const float4x2& rhs) { return float4x2(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1); }

			/// <summary>Returns the result of a componentwise division operation on a float4x2 matrix and a float value.</summary>

			inline static float4x2 operator / (const float4x2& lhs, float rhs) { return float4x2(lhs.c0 / rhs, lhs.c1 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float4x2 matrix.</summary>

			inline static float4x2 operator / (float lhs, const float4x2& rhs) { return float4x2(lhs / rhs.c0, lhs / rhs.c1); }

			/// <summary>Returns the result of a componentwise increment operation on a float4x2 matrix.</summary>

			inline static float4x2 operator ++ (float4x2 val) { return float4x2(++val.c0, ++val.c1); }


			/// <summary>Returns the result of a componentwise decrement operation on a float4x2 matrix.</summary>

			inline static float4x2 operator -- (float4x2 val) { return float4x2(--val.c0, --val.c1); }


			/// <summary>Returns the result of a componentwise less than operation on two float4x2 matrices.</summary>

			inline static bool4x2 operator < (const float4x2& lhs, const float4x2& rhs) { return bool4x2(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1); }

			/// <summary>Returns the result of a componentwise less than operation on a float4x2 matrix and a float value.</summary>

			inline static bool4x2 operator < (const float4x2& lhs, float rhs) { return bool4x2(lhs.c0 < rhs, lhs.c1 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float4x2 matrix.</summary>

			inline static bool4x2 operator < (float lhs, const float4x2& rhs) { return bool4x2(lhs < rhs.c0, lhs < rhs.c1); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float4x2 matrices.</summary>

			inline static bool4x2 operator <= (const float4x2& lhs, const float4x2& rhs) { return bool4x2(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float4x2 matrix and a float value.</summary>

			inline static bool4x2 operator <= (const float4x2& lhs, float rhs) { return bool4x2(lhs.c0 <= rhs, lhs.c1 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float4x2 matrix.</summary>

			inline static bool4x2 operator <= (float lhs, const float4x2& rhs) { return bool4x2(lhs <= rhs.c0, lhs <= rhs.c1); }


			/// <summary>Returns the result of a componentwise greater than operation on two float4x2 matrices.</summary>

			inline static bool4x2 operator > (const float4x2& lhs, const float4x2& rhs) { return bool4x2(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1); }

			/// <summary>Returns the result of a componentwise greater than operation on a float4x2 matrix and a float value.</summary>

			inline static bool4x2 operator > (const float4x2& lhs, float rhs) { return bool4x2(lhs.c0 > rhs, lhs.c1 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float4x2 matrix.</summary>

			inline static bool4x2 operator > (float lhs, const float4x2& rhs) { return bool4x2(lhs > rhs.c0, lhs > rhs.c1); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float4x2 matrices.</summary>

			inline static bool4x2 operator >= (const float4x2& lhs, const float4x2& rhs) { return bool4x2(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float4x2 matrix and a float value.</summary>

			inline static bool4x2 operator >= (const float4x2& lhs, float rhs) { return bool4x2(lhs.c0 >= rhs, lhs.c1 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float4x2 matrix.</summary>

			inline static bool4x2 operator >= (float lhs, const float4x2& rhs) { return bool4x2(lhs >= rhs.c0, lhs >= rhs.c1); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float4x2 matrix.</summary>

			inline static float4x2 operator - (float4x2 val) { return float4x2(-val.c0, -val.c1); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float4x2 matrix.</summary>

			inline static float4x2 operator + (float4x2 val) { return float4x2(+val.c0, +val.c1); }


			/// <summary>Returns the result of a componentwise equality operation on two float4x2 matrices.</summary>

			inline static bool4x2 operator == (const float4x2& lhs, const float4x2& rhs) { return bool4x2(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1); }

			/// <summary>Returns the result of a componentwise equality operation on a float4x2 matrix and a float value.</summary>

			inline static bool4x2 operator == (const float4x2& lhs, float rhs) { return bool4x2(lhs.c0 == rhs, lhs.c1 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float4x2 matrix.</summary>

			inline static bool4x2 operator == (float lhs, const float4x2& rhs) { return bool4x2(lhs == rhs.c0, lhs == rhs.c1); }


			/// <summary>Returns the result of a componentwise not equal operation on two float4x2 matrices.</summary>

			inline static bool4x2 operator != (const float4x2& lhs, const float4x2& rhs) { return bool4x2(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1); }

			/// <summary>Returns the result of a componentwise not equal operation on a float4x2 matrix and a float value.</summary>

			inline static bool4x2 operator != (const float4x2& lhs, float rhs) { return bool4x2(lhs.c0 != rhs, lhs.c1 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float4x2 matrix.</summary>

			inline static bool4x2 operator != (float lhs, const float4x2& rhs) { return bool4x2(lhs != rhs.c0, lhs != rhs.c1); }


#pragma endregion
#pragma region float4x3
			struct float4x3
			{
				float4 c0, c1, c2;
				float4x3() : c0(), c1(), c2() {}
				float4x3(float m00, float m01, float m02,
					float m10, float m11, float m12,
					float m20, float m21, float m22,
					float m30, float m31, float m32)
				{
					c0 = float4(m00, m10, m20, m30);
					c1 = float4(m01, m11, m21, m31);
					c2 = float4(m02, m12, m22, m32);
				}
				float4x3(float4 c0, float4 c1, float4 c2) : c0(c0), c1(c1), c2(c2) {}
				float4x3(float v) : c0(v), c1(v), c2(v) {}
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float4x3 matrices.</summary>

			inline static float4x3 operator * (const float4x3& lhs, const float4x3& rhs) { return float4x3(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float4x3 matrix and a float value.</summary>

			inline static float4x3 operator * (const float4x3& lhs, float rhs) { return float4x3(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float4x3 matrix.</summary>

			inline static float4x3 operator * (float lhs, const float4x3& rhs) { return float4x3(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2); }


			/// <summary>Returns the result of a componentwise addition operation on two float4x3 matrices.</summary>

			inline static float4x3 operator + (const float4x3& lhs, const float4x3& rhs) { return float4x3(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2); }

			/// <summary>Returns the result of a componentwise addition operation on a float4x3 matrix and a float value.</summary>

			inline static float4x3 operator + (const float4x3& lhs, float rhs) { return float4x3(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float4x3 matrix.</summary>

			inline static float4x3 operator + (float lhs, const float4x3& rhs) { return float4x3(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float4x3 matrices.</summary>

			inline static float4x3 operator - (const float4x3& lhs, const float4x3& rhs) { return float4x3(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float4x3 matrix and a float value.</summary>

			inline static float4x3 operator - (const float4x3& lhs, float rhs) { return float4x3(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float4x3 matrix.</summary>

			inline static float4x3 operator - (float lhs, const float4x3& rhs) { return float4x3(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2); }


			/// <summary>Returns the result of a componentwise division operation on two float4x3 matrices.</summary>

			inline static float4x3 operator / (const float4x3& lhs, const float4x3& rhs) { return float4x3(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2); }

			/// <summary>Returns the result of a componentwise division operation on a float4x3 matrix and a float value.</summary>

			inline static float4x3 operator / (const float4x3& lhs, float rhs) { return float4x3(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float4x3 matrix.</summary>

			inline static float4x3 operator / (float lhs, const float4x3& rhs) { return float4x3(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2); }

			/// <summary>Returns the result of a componentwise increment operation on a float4x3 matrix.</summary>

			inline static float4x3 operator ++ (float4x3 val) { return float4x3(++val.c0, ++val.c1, ++val.c2); }


			/// <summary>Returns the result of a componentwise decrement operation on a float4x3 matrix.</summary>

			inline static float4x3 operator -- (float4x3 val) { return float4x3(--val.c0, --val.c1, --val.c2); }


			/// <summary>Returns the result of a componentwise less than operation on two float4x3 matrices.</summary>

			inline static bool4x3 operator < (const float4x3& lhs, const float4x3& rhs) { return bool4x3(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2); }

			/// <summary>Returns the result of a componentwise less than operation on a float4x3 matrix and a float value.</summary>

			inline static bool4x3 operator < (const float4x3& lhs, float rhs) { return bool4x3(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float4x3 matrix.</summary>

			inline static bool4x3 operator < (float lhs, const float4x3& rhs) { return bool4x3(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float4x3 matrices.</summary>

			inline static bool4x3 operator <= (const float4x3& lhs, const float4x3& rhs) { return bool4x3(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float4x3 matrix and a float value.</summary>

			inline static bool4x3 operator <= (const float4x3& lhs, float rhs) { return bool4x3(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float4x3 matrix.</summary>

			inline static bool4x3 operator <= (float lhs, const float4x3& rhs) { return bool4x3(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2); }


			/// <summary>Returns the result of a componentwise greater than operation on two float4x3 matrices.</summary>

			inline static bool4x3 operator > (const float4x3& lhs, const float4x3& rhs) { return bool4x3(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2); }

			/// <summary>Returns the result of a componentwise greater than operation on a float4x3 matrix and a float value.</summary>

			inline static bool4x3 operator > (const float4x3& lhs, float rhs) { return bool4x3(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float4x3 matrix.</summary>

			inline static bool4x3 operator > (float lhs, const float4x3& rhs) { return bool4x3(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float4x3 matrices.</summary>

			inline static bool4x3 operator >= (const float4x3& lhs, const float4x3& rhs) { return bool4x3(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float4x3 matrix and a float value.</summary>

			inline static bool4x3 operator >= (const float4x3& lhs, float rhs) { return bool4x3(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float4x3 matrix.</summary>

			inline static bool4x3 operator >= (float lhs, const float4x3& rhs) { return bool4x3(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float4x3 matrix.</summary>

			inline static float4x3 operator - (float4x3 val) { return float4x3(-val.c0, -val.c1, -val.c2); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float4x3 matrix.</summary>

			inline static float4x3 operator + (float4x3 val) { return float4x3(+val.c0, +val.c1, +val.c2); }


			/// <summary>Returns the result of a componentwise equality operation on two float4x3 matrices.</summary>

			inline static bool4x3 operator == (const float4x3& lhs, const float4x3& rhs) { return bool4x3(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2); }

			/// <summary>Returns the result of a componentwise equality operation on a float4x3 matrix and a float value.</summary>

			inline static bool4x3 operator == (const float4x3& lhs, float rhs) { return bool4x3(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float4x3 matrix.</summary>

			inline static bool4x3 operator == (float lhs, const float4x3& rhs) { return bool4x3(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2); }


			/// <summary>Returns the result of a componentwise not equal operation on two float4x3 matrices.</summary>

			inline static bool4x3 operator != (const float4x3& lhs, const float4x3& rhs) { return bool4x3(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2); }

			/// <summary>Returns the result of a componentwise not equal operation on a float4x3 matrix and a float value.</summary>

			inline static bool4x3 operator != (const float4x3& lhs, float rhs) { return bool4x3(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float4x3 matrix.</summary>

			inline static bool4x3 operator != (float lhs, const float4x3& rhs) { return bool4x3(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2); }


#pragma endregion
#pragma region float4x4
			struct float4x4
			{
				float4 c0, c1, c2, c3;
				float4x4() : c0(), c1(), c2(), c3() {}
				float4x4(float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33)
				{
					c0 = float4(m00, m10, m20, m30);
					c1 = float4(m01, m11, m21, m31);
					c2 = float4(m02, m12, m22, m32);
					c3 = float4(m03, m13, m23, m33);
				}
				float4x4(float4 c0, float4 c1, float4 c2, float4 c3) : c0(c0), c1(c1), c2(c2), c3(c3) {}
				float4x4(float v) : c0(v), c1(v), c2(v), c3(v) {}

				float4x4(float3x3 rotation, float3 translation)
				{
					c0 = float4(rotation.c0, 0.0f);
					c1 = float4(rotation.c1, 0.0f);
					c2 = float4(rotation.c2, 0.0f);
					c3 = float4(translation, 1.0f);
				}

				
			};


			/// <summary>Returns the result of a componentwise multiplication operation on two float4x4 matrices.</summary>

			inline static float4x4 operator * (const float4x4& lhs, const float4x4& rhs) { return float4x4(lhs.c0 * rhs.c0, lhs.c1 * rhs.c1, lhs.c2 * rhs.c2, lhs.c3 * rhs.c3); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float4x4 matrix and a float value.</summary>

			inline static float4x4 operator * (const float4x4& lhs, float rhs) { return float4x4(lhs.c0 * rhs, lhs.c1 * rhs, lhs.c2 * rhs, lhs.c3 * rhs); }

			/// <summary>Returns the result of a componentwise multiplication operation on a float value and a float4x4 matrix.</summary>

			inline static float4x4 operator * (float lhs, const float4x4& rhs) { return float4x4(lhs * rhs.c0, lhs * rhs.c1, lhs * rhs.c2, lhs * rhs.c3); }


			/// <summary>Returns the result of a componentwise addition operation on two float4x4 matrices.</summary>

			inline static float4x4 operator + (const float4x4& lhs, const float4x4& rhs) { return float4x4(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3); }

			/// <summary>Returns the result of a componentwise addition operation on a float4x4 matrix and a float value.</summary>

			inline static float4x4 operator + (const float4x4& lhs, float rhs) { return float4x4(lhs.c0 + rhs, lhs.c1 + rhs, lhs.c2 + rhs, lhs.c3 + rhs); }

			/// <summary>Returns the result of a componentwise addition operation on a float value and a float4x4 matrix.</summary>

			inline static float4x4 operator + (float lhs, const float4x4& rhs) { return float4x4(lhs + rhs.c0, lhs + rhs.c1, lhs + rhs.c2, lhs + rhs.c3); }


			/// <summary>Returns the result of a componentwise subtraction operation on two float4x4 matrices.</summary>

			inline static float4x4 operator - (const float4x4& lhs, const float4x4& rhs) { return float4x4(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float4x4 matrix and a float value.</summary>

			inline static float4x4 operator - (const float4x4& lhs, float rhs) { return float4x4(lhs.c0 - rhs, lhs.c1 - rhs, lhs.c2 - rhs, lhs.c3 - rhs); }

			/// <summary>Returns the result of a componentwise subtraction operation on a float value and a float4x4 matrix.</summary>

			inline static float4x4 operator - (float lhs, const float4x4& rhs) { return float4x4(lhs - rhs.c0, lhs - rhs.c1, lhs - rhs.c2, lhs - rhs.c3); }


			/// <summary>Returns the result of a componentwise division operation on two float4x4 matrices.</summary>

			inline static float4x4 operator / (const float4x4& lhs, const float4x4& rhs) { return float4x4(lhs.c0 / rhs.c0, lhs.c1 / rhs.c1, lhs.c2 / rhs.c2, lhs.c3 / rhs.c3); }

			/// <summary>Returns the result of a componentwise division operation on a float4x4 matrix and a float value.</summary>

			inline static float4x4 operator / (const float4x4& lhs, float rhs) { return float4x4(lhs.c0 / rhs, lhs.c1 / rhs, lhs.c2 / rhs, lhs.c3 / rhs); }

			/// <summary>Returns the result of a componentwise division operation on a float value and a float4x4 matrix.</summary>

			inline static float4x4 operator / (float lhs, const float4x4& rhs) { return float4x4(lhs / rhs.c0, lhs / rhs.c1, lhs / rhs.c2, lhs / rhs.c3); }


			/// <summary>Returns the result of a componentwise increment operation on a float4x4 matrix.</summary>

			inline static float4x4 operator ++ (float4x4 val) { return float4x4(++val.c0, ++val.c1, ++val.c2, ++val.c3); }


			/// <summary>Returns the result of a componentwise decrement operation on a float4x4 matrix.</summary>

			inline static float4x4 operator -- (float4x4 val) { return float4x4(--val.c0, --val.c1, --val.c2, --val.c3); }


			/// <summary>Returns the result of a componentwise less than operation on two float4x4 matrices.</summary>

			inline static bool4x4 operator < (const float4x4& lhs, const float4x4& rhs) { return bool4x4(lhs.c0 < rhs.c0, lhs.c1 < rhs.c1, lhs.c2 < rhs.c2, lhs.c3 < rhs.c3); }

			/// <summary>Returns the result of a componentwise less than operation on a float4x4 matrix and a float value.</summary>

			inline static bool4x4 operator < (const float4x4& lhs, float rhs) { return bool4x4(lhs.c0 < rhs, lhs.c1 < rhs, lhs.c2 < rhs, lhs.c3 < rhs); }

			/// <summary>Returns the result of a componentwise less than operation on a float value and a float4x4 matrix.</summary>

			inline static bool4x4 operator < (float lhs, const float4x4& rhs) { return bool4x4(lhs < rhs.c0, lhs < rhs.c1, lhs < rhs.c2, lhs < rhs.c3); }


			/// <summary>Returns the result of a componentwise less or equal operation on two float4x4 matrices.</summary>

			inline static bool4x4 operator <= (const float4x4& lhs, const float4x4& rhs) { return bool4x4(lhs.c0 <= rhs.c0, lhs.c1 <= rhs.c1, lhs.c2 <= rhs.c2, lhs.c3 <= rhs.c3); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float4x4 matrix and a float value.</summary>

			inline static bool4x4 operator <= (const float4x4& lhs, float rhs) { return bool4x4(lhs.c0 <= rhs, lhs.c1 <= rhs, lhs.c2 <= rhs, lhs.c3 <= rhs); }

			/// <summary>Returns the result of a componentwise less or equal operation on a float value and a float4x4 matrix.</summary>

			inline static bool4x4 operator <= (float lhs, const float4x4& rhs) { return bool4x4(lhs <= rhs.c0, lhs <= rhs.c1, lhs <= rhs.c2, lhs <= rhs.c3); }


			/// <summary>Returns the result of a componentwise greater than operation on two float4x4 matrices.</summary>

			inline static bool4x4 operator > (const float4x4& lhs, const float4x4& rhs) { return bool4x4(lhs.c0 > rhs.c0, lhs.c1 > rhs.c1, lhs.c2 > rhs.c2, lhs.c3 > rhs.c3); }

			/// <summary>Returns the result of a componentwise greater than operation on a float4x4 matrix and a float value.</summary>

			inline static bool4x4 operator > (const float4x4& lhs, float rhs) { return bool4x4(lhs.c0 > rhs, lhs.c1 > rhs, lhs.c2 > rhs, lhs.c3 > rhs); }

			/// <summary>Returns the result of a componentwise greater than operation on a float value and a float4x4 matrix.</summary>

			inline static bool4x4 operator > (float lhs, const float4x4& rhs) { return bool4x4(lhs > rhs.c0, lhs > rhs.c1, lhs > rhs.c2, lhs > rhs.c3); }


			/// <summary>Returns the result of a componentwise greater or equal operation on two float4x4 matrices.</summary>

			inline static bool4x4 operator >= (const float4x4& lhs, const float4x4& rhs) { return bool4x4(lhs.c0 >= rhs.c0, lhs.c1 >= rhs.c1, lhs.c2 >= rhs.c2, lhs.c3 >= rhs.c3); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float4x4 matrix and a float value.</summary>

			inline static bool4x4 operator >= (const float4x4& lhs, float rhs) { return bool4x4(lhs.c0 >= rhs, lhs.c1 >= rhs, lhs.c2 >= rhs, lhs.c3 >= rhs); }

			/// <summary>Returns the result of a componentwise greater or equal operation on a float value and a float4x4 matrix.</summary>

			inline static bool4x4 operator >= (float lhs, const float4x4& rhs) { return bool4x4(lhs >= rhs.c0, lhs >= rhs.c1, lhs >= rhs.c2, lhs >= rhs.c3); }


			/// <summary>Returns the result of a componentwise unary Minus operation on a float4x4 matrix.</summary>

			inline static float4x4 operator - (float4x4 val) { return float4x4(-val.c0, -val.c1, -val.c2, -val.c3); }


			/// <summary>Returns the result of a componentwise unary plus operation on a float4x4 matrix.</summary>

			inline static float4x4 operator + (float4x4 val) { return float4x4(+val.c0, +val.c1, +val.c2, +val.c3); }


			/// <summary>Returns the result of a componentwise equality operation on two float4x4 matrices.</summary>

			inline static bool4x4 operator == (const float4x4& lhs, const float4x4& rhs) { return bool4x4(lhs.c0 == rhs.c0, lhs.c1 == rhs.c1, lhs.c2 == rhs.c2, lhs.c3 == rhs.c3); }

			/// <summary>Returns the result of a componentwise equality operation on a float4x4 matrix and a float value.</summary>

			inline static bool4x4 operator == (const float4x4& lhs, float rhs) { return bool4x4(lhs.c0 == rhs, lhs.c1 == rhs, lhs.c2 == rhs, lhs.c3 == rhs); }

			/// <summary>Returns the result of a componentwise equality operation on a float value and a float4x4 matrix.</summary>

			inline static bool4x4 operator == (float lhs, const float4x4& rhs) { return bool4x4(lhs == rhs.c0, lhs == rhs.c1, lhs == rhs.c2, lhs == rhs.c3); }


			/// <summary>Returns the result of a componentwise not equal operation on two float4x4 matrices.</summary>

			inline static bool4x4 operator != (const float4x4& lhs, const float4x4& rhs) { return bool4x4(lhs.c0 != rhs.c0, lhs.c1 != rhs.c1, lhs.c2 != rhs.c2, lhs.c3 != rhs.c3); }

			/// <summary>Returns the result of a componentwise not equal operation on a float4x4 matrix and a float value.</summary>

			inline static bool4x4 operator != (const float4x4& lhs, float rhs) { return bool4x4(lhs.c0 != rhs, lhs.c1 != rhs, lhs.c2 != rhs, lhs.c3 != rhs); }

			/// <summary>Returns the result of a componentwise not equal operation on a float value and a float4x4 matrix.</summary>

			inline static bool4x4 operator != (float lhs, const float4x4& rhs) { return bool4x4(lhs != rhs.c0, lhs != rhs.c1, lhs != rhs.c2, lhs != rhs.c3); }


#pragma endregion
#pragma region Basic


			/// <summary>Returns the Tangent of a float value.</summary>
			inline static float Tan(float x) { return (float)tan(x); }

			/// <summary>Returns the componentwise Tangent of a float2 vector.</summary>
			inline static float2 Tan(float2 x) { return float2(Tan(x.x), Tan(x.y)); }

			/// <summary>Returns the componentwise Tangent of a float3 vector.</summary>
			inline static float3 Tan(float3 x) { return float3(Tan(x.x), Tan(x.y), Tan(x.z)); }

			/// <summary>Returns the componentwise Tangent of a float4 vector.</summary>
			inline static float4 Tan(float4 x) { return float4(Tan(x.x), Tan(x.y), Tan(x.z), Tan(x.w)); }


			/// <summary>Returns the hyperbolic Tangent of a float value.</summary>
			inline static float Tanh(float x) { return (float)tanh(x); }

			/// <summary>Returns the componentwise hyperbolic Tangent of a float2 vector.</summary>
			inline static float2 Tanh(float2 x) { return float2(Tanh(x.x), Tanh(x.y)); }

			/// <summary>Returns the componentwise hyperbolic Tangent of a float3 vector.</summary>
			inline static float3 Tanh(float3 x) { return float3(Tanh(x.x), Tanh(x.y), Tanh(x.z)); }

			/// <summary>Returns the componentwise hyperbolic Tangent of a float4 vector.</summary>
			inline static float4 Tanh(float4 x) { return float4(Tanh(x.x), Tanh(x.y), Tanh(x.z), Tanh(x.w)); }


			/// <summary>Returns the arcTangent of a float value.</summary>
			inline static float Atan(float x) { return (float)atan(x); }

			/// <summary>Returns the componentwise arcTangent of a float2 vector.</summary>
			inline static float2 Atan(float2 x) { return float2(Atan(x.x), Atan(x.y)); }

			/// <summary>Returns the componentwise arcTangent of a float3 vector.</summary>
			inline static float3 Atan(float3 x) { return float3(Atan(x.x), Atan(x.y), Atan(x.z)); }

			/// <summary>Returns the componentwise arcTangent of a float4 vector.</summary>
			inline static float4 Atan(float4 x) { return float4(Atan(x.x), Atan(x.y), Atan(x.z), Atan(x.w)); }


			/// <summary>Returns the 2-argument arcTangent of a pair of float values.</summary>
			inline static float Atan2(float y, float x) { return (float)atan2(y, x); }

			/// <summary>Returns the componentwise 2-argument arcTangent of a pair of floats2 vectors.</summary>
			inline static float2 Atan2(float2 y, float2 x) { return float2(Atan2(y.x, x.x), Atan2(y.y, x.y)); }

			/// <summary>Returns the componentwise 2-argument arcTangent of a pair of floats3 vectors.</summary>
			inline static float3 Atan2(float3 y, float3 x) { return float3(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z)); }

			/// <summary>Returns the componentwise 2-argument arcTangent of a pair of floats4 vectors.</summary>
			inline static float4 Atan2(float4 y, float4 x) { return float4(Atan2(y.x, x.x), Atan2(y.y, x.y), Atan2(y.z, x.z), Atan2(y.w, x.w)); }


			/// <summary>Returns the CoSine of a float value.</summary>
			inline static float Cos(float x) { return (float)cos(x); }

			/// <summary>Returns the componentwise CoSine of a float2 vector.</summary>
			inline static float2 Cos(float2 x) { return float2(Cos(x.x), Cos(x.y)); }

			/// <summary>Returns the componentwise CoSine of a float3 vector.</summary>
			inline static float3 Cos(float3 x) { return float3(Cos(x.x), Cos(x.y), Cos(x.z)); }

			/// <summary>Returns the componentwise CoSine of a float4 vector.</summary>
			inline static float4 Cos(float4 x) { return float4(Cos(x.x), Cos(x.y), Cos(x.z), Cos(x.w)); }


			/// <summary>Returns the hyperbolic CoSine of a float value.</summary>
			inline static float Cosh(float x) { return (float)cosh(x); }

			/// <summary>Returns the componentwise hyperbolic CoSine of a float2 vector.</summary>
			inline static float2 Cosh(float2 x) { return float2(Cosh(x.x), Cosh(x.y)); }

			/// <summary>Returns the componentwise hyperbolic CoSine of a float3 vector.</summary>
			inline static float3 Cosh(float3 x) { return float3(Cosh(x.x), Cosh(x.y), Cosh(x.z)); }

			/// <summary>Returns the componentwise hyperbolic CoSine of a float4 vector.</summary>
			inline static float4 Cosh(float4 x) { return float4(Cosh(x.x), Cosh(x.y), Cosh(x.z), Cosh(x.w)); }

			/// <summary>Returns the arcCoSine of a float value.</summary>
			inline static float Acos(float x) { return (float)acos((float)x); }

			/// <summary>Returns the componentwise arcCoSine of a float2 vector.</summary>
			inline static float2 Acos(float2 x) { return float2(Acos(x.x), Acos(x.y)); }

			/// <summary>Returns the componentwise arcCoSine of a float3 vector.</summary>
			inline static float3 Acos(float3 x) { return float3(Acos(x.x), Acos(x.y), Acos(x.z)); }

			/// <summary>Returns the componentwise arcCoSine of a float4 vector.</summary>
			inline static float4 Acos(float4 x) { return float4(Acos(x.x), Acos(x.y), Acos(x.z), Acos(x.w)); }


			/// <summary>Returns the Sine of a float value.</summary>
			inline static float Sin(float x) { return (float)sin((float)x); }

			/// <summary>Returns the componentwise Sine of a float2 vector.</summary>
			inline static float2 Sin(float2 x) { return float2(Sin(x.x), Sin(x.y)); }

			/// <summary>Returns the componentwise Sine of a float3 vector.</summary>
			inline static float3 Sin(float3 x) { return float3(Sin(x.x), Sin(x.y), Sin(x.z)); }

			/// <summary>Returns the componentwise Sine of a float4 vector.</summary>
			inline static float4 Sin(float4 x) { return float4(Sin(x.x), Sin(x.y), Sin(x.z), Sin(x.w)); }



			/// <summary>Returns the hyperbolic Sine of a float value.</summary>
			inline static float Sinh(float x) { return (float)sinh((float)x); }

			/// <summary>Returns the componentwise hyperbolic Sine of a float2 vector.</summary>
			inline static float2 Sinh(float2 x) { return float2(Sinh(x.x), Sinh(x.y)); }

			/// <summary>Returns the componentwise hyperbolic Sine of a float3 vector.</summary>
			inline static float3 Sinh(float3 x) { return float3(Sinh(x.x), Sinh(x.y), Sinh(x.z)); }

			/// <summary>Returns the componentwise hyperbolic Sine of a float4 vector.</summary>
			inline static float4 Sinh(float4 x) { return float4(Sinh(x.x), Sinh(x.y), Sinh(x.z), Sinh(x.w)); }


			/// <summary>Returns the arcSine of a float value.</summary>
			inline static float Asin(float x) { return (float)asin((float)x); }

			/// <summary>Returns the componentwise arcSine of a float2 vector.</summary>
			inline static float2 Asin(float2 x) { return float2(Asin(x.x), Asin(x.y)); }

			/// <summary>Returns the componentwise arcSine of a float3 vector.</summary>
			inline static float3 Asin(float3 x) { return float3(Asin(x.x), Asin(x.y), Asin(x.z)); }

			/// <summary>Returns the componentwise arcSine of a float4 vector.</summary>
			inline static float4 Asin(float4 x) { return float4(Asin(x.x), Asin(x.y), Asin(x.z), Asin(x.w)); }


			/// <summary>Returns the Dot product of two float values. Equivalent to multiplication.</summary>
			inline static float Dot(float x, float y) { return x * y; }

			/// <summary>Returns the Dot product of two float2 vectors.</summary>
			inline static float Dot(float2 x, float2 y) { return x.x * y.x + x.y * y.y; }

			/// <summary>Returns the Dot product of two float3 vectors.</summary>
			inline static float Dot(float3 x, float3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }

			/// <summary>Returns the Dot product of two float4 vectors.</summary>
			inline static float Dot(float4 x, float4 y) { return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w; }

			/// <summary>Returns the square root of a float value.</summary>
			inline static float Sqrt(float x) { return sqrt((double)x); }

			/// <summary>Returns the componentwise square root of a float2 vector.</summary>
			inline static float2 Sqrt(float2 x) { return float2(Sqrt(x.x), Sqrt(x.y)); }

			/// <summary>Returns the componentwise square root of a float3 vector.</summary>
			inline static float3 Sqrt(float3 x) { return float3(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z)); }

			/// <summary>Returns the componentwise square root of a float4 vector.</summary>
			inline static float4 Sqrt(float4 x) { return float4(Sqrt(x.x), Sqrt(x.y), Sqrt(x.z), Sqrt(x.w)); }


			/// <summary>Returns the reciprocal square root of a float value.</summary>
			inline static float Rsqrt(float x) { return 1.0f / Sqrt(x); }

			/// <summary>Returns the componentwise reciprocal square root of a float2 vector.</summary>
			inline static float2 Rsqrt(float2 x) { return 1.0f / Sqrt(x); }

			/// <summary>Returns the componentwise reciprocal square root of a float3 vector.</summary>
			inline static float3 Rsqrt(float3 x) { return 1.0f / Sqrt(x); }

			/// <summary>Returns the componentwise reciprocal square root of a float4 vector</summary>
			inline static float4 Rsqrt(float4 x) { return 1.0f / Sqrt(x); }

			/// <summary>Returns a Normalized version of the float2 vector x by scaling it by 1 / Length(x).</summary>
			inline static float2 Normalize(float2 x) { return Rsqrt(Dot(x, x)) * x; }

			/// <summary>Returns a Normalized version of the float3 vector x by scaling it by 1 / Length(x).</summary>
			inline static float3 Normalize(float3 x) { return Rsqrt(Dot(x, x)) * x; }

			/// <summary>Returns a Normalized version of the float4 vector x by scaling it by 1 / Length(x).</summary>
			inline static float4 Normalize(float4 x) { return Rsqrt(Dot(x, x)) * x; }

			/// <summary>Returns the Length of a float2 vector.</summary>
			inline static float Length(float2 x) { return sqrt(Dot(x, x)); }

			/// <summary>Returns the Length of a float3 vector.</summary>
			inline static float Length(float3 x) { return sqrt(Dot(x, x)); }

			/// <summary>Returns the Length of a float4 vector.</summary>
			inline static float Length(float4 x) { return sqrt(Dot(x, x)); }




			/// <summary>Returns the squared Length of a float value. Equivalent to squaring the value.</summary>
			inline static float Lengthsq(float x) { return x * x; }

			/// <summary>Returns the squared Length of a float2 vector.</summary>
			inline static float Lengthsq(float2 x) { return Dot(x, x); }

			/// <summary>Returns the squared Length of a float3 vector.</summary>
			inline static float Lengthsq(float3 x) { return Dot(x, x); }

			/// <summary>Returns the squared Length of a float4 vector.</summary>
			inline static float Lengthsq(float4 x) { return Dot(x, x); }


			/// <summary>Returns the Distance between two float2 vectors.</summary>
			inline static float Distance(float2 x, float2 y) { return Length(y - x); }

			/// <summary>Returns the Distance between two float3 vectors.</summary>
			inline static float Distance(float3 x, float3 y) { return Length(y - x); }

			/// <summary>Returns the Distance between two float4 vectors.</summary>
			inline static float Distance(float4 x, float4 y) { return Length(y - x); }



			/// <summary>Returns the Distance between two float values.</summary>
			inline static float Distancesq(float x, float y) { return (y - x) * (y - x); }

			/// <summary>Returns the Distance between two float2 vectors.</summary>
			inline static float Distancesq(float2 x, float2 y) { return Lengthsq(y - x); }

			/// <summary>Returns the Distance between two float3 vectors.</summary>
			inline static float Distancesq(float3 x, float3 y) { return Lengthsq(y - x); }

			/// <summary>Returns the Distance between two float4 vectors.</summary>
			inline static float Distancesq(float4 x, float4 y) { return Lengthsq(y - x); }



			/// <summary>Returns the Cross product of two float3 vectors.</summary>
			inline static float3 Cross(float3 x, float3 y) {
				float3 retVal = x * float3(y.y, y.z, y.x) - float3(x.y, x.z, x.x) * y;
				return float3(retVal.y, retVal.z, retVal.x);
			}

			/// <summary>Returns the Sine and CoSine of the input float value x through the out parameters s and c.</summary>
			inline static void SinCos(float x, float* s, float* c) { *s = Sin(x); *c = Cos(x); }

			/// <summary>Returns the componentwise Sine and CoSine of the input float2 vector x through the out parameters s and c.</summary>
			inline static void SinCos(float2 x, float2* s, float2* c) { *s = Sin(x); *c = Cos(x); }

			/// <summary>Returns the componentwise Sine and CoSine of the input float3 vector x through the out parameters s and c.</summary>
			inline static void SinCos(float3 x, float3* s, float3* c) { *s = Sin(x); *c = Cos(x); }

			/// <summary>Returns the componentwise Sine and CoSine of the input float4 vector x through the out parameters s and c.</summary>
			inline static void SinCos(float4 x, float4* s, float4* c) { *s = Sin(x); *c = Cos(x); }


			/// <summary>Returns the Minimum of two float values.</summary>
			inline static float Min(float x, float y) { return x < y ? x : y; }

			/// <summary>Returns the componentwise Minimum of two float2 vectors.</summary>
			inline static float2 Min(float2 x, float2 y) { return float2(Min(x.x, y.x), Min(x.y, y.y)); }

			/// <summary>Returns the componentwise Minimum of two float3 vectors.</summary>
			inline static float3 Min(float3 x, float3 y) { return float3(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z)); }

			/// <summary>Returns the componentwise Minimum of two float4 vectors.</summary>
			inline static float4 Min(float4 x, float4 y) { return float4(Min(x.x, y.x), Min(x.y, y.y), Min(x.z, y.z), Min(x.w, y.w)); }


			/// <summary>Returns the Maximum of two float values.</summary>
			inline static float Max(float x, float y) { return x > y ? x : y; }

			/// <summary>Returns the componentwise Maximum of two float2 vectors.</summary>
			inline static float2 Max(float2 x, float2 y) { return float2(Max(x.x, y.x), Max(x.y, y.y)); }

			/// <summary>Returns the componentwise Maximum of two float3 vectors.</summary>
			inline static float3 Max(float3 x, float3 y) { return float3(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z)); }

			/// <summary>Returns the componentwise Maximum of two float4 vectors.</summary>
			inline static float4 Max(float4 x, float4 y) { return float4(Max(x.x, y.x), Max(x.y, y.y), Max(x.z, y.z), Max(x.w, y.w)); }

			inline static float Lerp(float x, float y, float s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
			inline static float2 Lerp(float2 x, float2 y, float s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
			inline static float3 Lerp(float3 x, float3 y, float s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the interpolation parameter s.</summary>
			inline static float4 Lerp(float4 x, float4 y, float s) { return x + s * (y - x); }


			/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
			inline static float2 Lerp(float2 x, float2 y, float2 s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
			inline static float3 Lerp(float3 x, float3 y, float3 s) { return x + s * (y - x); }

			/// <summary>Returns the result of a componentwise linear interpolating from x to y uSing the corresponding components of the interpolation parameter s.</summary>
			inline static float4 Lerp(float4 x, float4 y, float4 s) { return x + s * (y - x); }

			/// <summary>Returns the result of normalizing a floating point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static float Unlerp(float a, float b, float x) { return (x - a) / (b - a); }

			/// <summary>Returns the componentwise result of normalizing a floating point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static float2 Unlerp(float2 a, float2 b, float2 x) { return (x - a) / (b - a); }

			/// <summary>Returns the componentwise result of normalizing a floating point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static float3 Unlerp(float3 a, float3 b, float3 x) { return (x - a) / (b - a); }

			/// <summary>Returns the componentwise result of normalizing a floating point value x to a range [a, b]. The opposite of Lerp. Equivalent to (x - a) / (b - a).</summary>
			inline static float4 Unlerp(float4 a, float4 b, float4 x) { return (x - a) / (b - a); }

			/// <summary>Returns the result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
			inline static float Remap(float a, float b, float c, float d, float x) { return Lerp(c, d, Unlerp(a, b, x)); }

			/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
			inline static float2 Remap(float2 a, float2 b, float2 c, float2 d, float2 x) { return Lerp(c, d, Unlerp(a, b, x)); }

			/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
			inline static float3 Remap(float3 a, float3 b, float3 c, float3 d, float3 x) { return Lerp(c, d, Unlerp(a, b, x)); }

			/// <summary>Returns the componentwise result of a non-Clamping linear Remapping of a value x from [a, b] to [c, d].</summary>
			inline static float4 Remap(float4 a, float4 b, float4 c, float4 d, float4 x) { return Lerp(c, d, Unlerp(a, b, x)); }

			/// <summary>Returns the result of Clamping the value x into the interval [a, b], where x, a and b are float values.</summary>
			inline static float Clamp(float x, float a, float b) { return Max(a, Min(b, x)); }

			/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are float2 vectors.</summary>
			inline static float2 Clamp(float2 x, float2 a, float2 b) { return Max(a, Min(b, x)); }

			/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are float3 vectors.</summary>
			inline static float3 Clamp(float3 x, float3 a, float3 b) { return Max(a, Min(b, x)); }

			/// <summary>Returns the result of a componentwise Clamping of the value x into the interval [a, b], where x, a and b are float4 vectors.</summary>
			inline static float4 Clamp(float4 x, float4 a, float4 b) { return Max(a, Min(b, x)); }

			inline static float select_shuffle_component(float4 a, float4 b, char component)
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

			inline static float4 shuffle(float4 a, float4 b, char x, char y, char z, char w)
			{
				return float4(
					select_shuffle_component(a, b, x),
					select_shuffle_component(a, b, y),
					select_shuffle_component(a, b, z),
					select_shuffle_component(a, b, w));
			}

			inline static float4 movelh(float4 a, float4 b)
			{
				return shuffle(a, b, 0, 1, 4, 5);
			}
			inline static float4 movehl(float4 a, float4 b)
			{
				return shuffle(b, a, 2, 3, 6, 7);
			}
			// SSE shuffles
			inline static float4 unpacklo(float4 a, float4 b)
			{
				return shuffle(a, b, 0, 4, 1, 5);
			}
			inline static float4 unpackhi(float4 a, float4 b)
			{
				return shuffle(a, b, 2, 6, 3, 7);
			}
#pragma endregion
#pragma region Component
			/// <summary>Returns the Maximum component of a float2 vector.</summary>
			inline static float CMax(float2 x) { return Max(x.x, x.y); }

			/// <summary>Returns the Maximum component of a float3 vector.</summary>
			inline static float CMax(float3 x) { return Max(Max(x.x, x.y), x.z); }

			/// <summary>Returns the Maximum component of a float4 vector.</summary>
			inline static float CMax(float4 x) { return Max(Max(x.x, x.y), Max(x.z, x.w)); }

			/// <summary>Returns the horizontal sum of components of a float2 vector.</summary>
			inline static float Csum(float2 x) { return x.x + x.y; }

			/// <summary>Returns the horizontal sum of components of a float3 vector.</summary>
			inline static float Csum(float3 x) { return x.x + x.y + x.z; }

			/// <summary>Returns the horizontal sum of components of a float4 vector.</summary>
			inline static float Csum(float4 x) { return (x.x + x.y) + (x.z + x.w); }

#pragma endregion

#pragma region Transpose
			/// <summary>Return the float2x2 Transpose of a float2x2 matrix.</summary>
			inline float2x2 Transpose(float2x2 v)
			{
				return float2x2(
					v.c0.x, v.c0.y,
					v.c1.x, v.c1.y);
			}
			/// <summary>Return the float3x2 Transpose of a float2x3 matrix.</summary>
			inline float3x2 Transpose(float2x3 v)
			{
				return float3x2(
					v.c0.x, v.c0.y,
					v.c1.x, v.c1.y,
					v.c2.x, v.c2.y);
			}
			/// <summary>Return the float4x2 Transpose of a float2x4 matrix.</summary>
			inline float4x2 Transpose(float2x4 v)
			{
				return float4x2(
					v.c0.x, v.c0.y,
					v.c1.x, v.c1.y,
					v.c2.x, v.c2.y,
					v.c3.x, v.c3.y);
			}
			/// <summary>Return the float2x3 Transpose of a float3x2 matrix.</summary>
			inline float2x3 Transpose(float3x2 v)
			{
				return float2x3(
					v.c0.x, v.c0.y, v.c0.z,
					v.c1.x, v.c1.y, v.c1.z);
			}
			/// <summary>Return the float3x3 Transpose of a float3x3 matrix.</summary>
			inline float3x3 Transpose(float3x3 v)
			{
				return float3x3(
					v.c0.x, v.c0.y, v.c0.z,
					v.c1.x, v.c1.y, v.c1.z,
					v.c2.x, v.c2.y, v.c2.z);
			}
			/// <summary>Return the float4x3 Transpose of a float3x4 matrix.</summary>
			inline static float4x3 Transpose(float3x4 v)
			{
				return float4x3(
					v.c0.x, v.c0.y, v.c0.z,
					v.c1.x, v.c1.y, v.c1.z,
					v.c2.x, v.c2.y, v.c2.z,
					v.c3.x, v.c3.y, v.c3.z);
			}
			/// <summary>Return the float2x4 Transpose of a float4x2 matrix.</summary>
			inline static float2x4 Transpose(float4x2 v)
			{
				return float2x4(
					v.c0.x, v.c0.y, v.c0.z, v.c0.w,
					v.c1.x, v.c1.y, v.c1.z, v.c1.w);
			}
			/// <summary>Return the float3x4 Transpose of a float4x3 matrix.</summary>
			inline static float3x4 Transpose(float4x3 v)
			{
				return float3x4(
					v.c0.x, v.c0.y, v.c0.z, v.c0.w,
					v.c1.x, v.c1.y, v.c1.z, v.c1.w,
					v.c2.x, v.c2.y, v.c2.z, v.c2.w);
			}
			/// <summary>Return the float4x4 Transpose of a float4x4 matrix.</summary>
			inline static float4x4 Transpose(float4x4 v)
			{
				return float4x4(
					v.c0.x, v.c0.y, v.c0.z, v.c0.w,
					v.c1.x, v.c1.y, v.c1.z, v.c1.w,
					v.c2.x, v.c2.y, v.c2.z, v.c2.w,
					v.c3.x, v.c3.y, v.c3.z, v.c3.w);
			}

#pragma endregion
#pragma region Inverse
			/// <summary>Returns the float2x2 full Inverse of a float2x2 matrix.</summary>
			inline float2x2 Inverse(float2x2 m)
			{
				float a = m.c0.x;
				float b = m.c1.x;
				float c = m.c0.y;
				float d = m.c1.y;

				float det = a * d - b * c;

				return float2x2(d, -b, -c, a) * (1.0f / det);
			}
			/// <summary>Returns the float3x3 full Inverse of a float3x3 matrix.</summary>
			inline float3x3 Inverse(float3x3 m)
			{
				float3 c0 = m.c0;
				float3 c1 = m.c1;
				float3 c2 = m.c2;

				float3 t0 = float3(c1.x, c2.x, c0.x);
				float3 t1 = float3(c1.y, c2.y, c0.y);
				float3 t2 = float3(c1.z, c2.z, c0.z);

				float3 m0 = t1 * float3(t2.y, t2.z, t2.x) - float3(t1.y, t1.z, t1.x) * t2;
				float3 m1 = float3(t0.y, t0.z, t0.x) * t2 - t0 * float3(t2.y, t2.z, t2.x);
				float3 m2 = t0 * float3(t1.y, t1.z, t1.x) - t0 * float3(t2.y, t2.z, t2.x) * t1;

				float rcpDet = 1.0f / Csum(float3(t0.z, t0.x, t0.y) * m0);
				return float3x3(m0, m1, m2) * rcpDet;
			}
			// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
			inline static float3x4 fastInverse(float3x4 m)
			{
				float3 c0 = m.c0;
				float3 c1 = m.c1;
				float3 c2 = m.c2;
				float3 pos = m.c3;

				float3 r0 = float3(c0.x, c1.x, c2.x);
				float3 r1 = float3(c0.y, c1.y, c2.y);
				float3 r2 = float3(c0.z, c1.z, c2.z);

				pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);

				return float3x4(r0, r1, r2, pos);
			}
			/// <summary>Returns the float4x4 full Inverse of a float4x4 matrix.</summary>
			inline static float4x4 Inverse(float4x4 m)
			{
				float4 c0 = m.c0;
				float4 c1 = m.c1;
				float4 c2 = m.c2;
				float4 c3 = m.c3;

				float4 r0y_r1y_r0x_r1x = movelh(c1, c0);
				float4 r0z_r1z_r0w_r1w = movelh(c2, c3);
				float4 r2y_r3y_r2x_r3x = movehl(c0, c1);
				float4 r2z_r3z_r2w_r3w = movehl(c3, c2);

				float4 r1y_r2y_r1x_r2x = shuffle(c1, c0, 1, 2, 5, 6);
				float4 r1z_r2z_r1w_r2w = shuffle(c2, c3, 1, 2, 5, 6);
				float4 r3y_r0y_r3x_r0x = shuffle(c1, c0, 3, 0, 7, 4);
				float4 r3z_r0z_r3w_r0w = shuffle(c2, c3, 3, 0, 7, 4);

				float4 r0_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 2, 0, 4, 6);
				float4 r1_wzyx = shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, 3, 1, 5, 7);
				float4 r2_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 2, 0, 4, 6);
				float4 r3_wzyx = shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, 3, 1, 5, 7);
				float4 r0_xyzw = shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, 2, 0, 4, 6);

				// Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
				float4 inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
				float4 inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
				float4 inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

				// Expand inner terms back to 4 components. zw signs still need to be flipped
				float4 inner12 = shuffle(inner12_23, inner12_23, 0, 2, 6, 4);
				float4 inner23 = shuffle(inner12_23, inner12_23, 1, 3, 7, 5);

				float4 inner02 = shuffle(inner02_13, inner02_13, 0, 2, 6, 4);
				float4 inner13 = shuffle(inner02_13, inner02_13, 1, 3, 7, 5);

				// Calculate Minors
				float4 Minors0 = r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;

				float4 denom = r0_xyzw * Minors0;

				// Horizontal sum of denoMinator. Free sign flip of z and w compensates for misSing flip in inner terms.
				denom = denom + shuffle(denom, denom, 1, 0, 7, 6);   // x+y        x+y            z+w            z+w
				denom = denom - shuffle(denom, denom, 2, 2, 4, 4);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

				float4 rcp_denom_ppnn = float4(1.0f) / denom;
				float4x4 res;
				res.c0 = Minors0 * rcp_denom_ppnn;

				float4 inner30 = shuffle(inner30_01, inner30_01, 0, 2, 6, 4);
				float4 inner01 = shuffle(inner30_01, inner30_01, 1, 3, 7, 5);

				float4 Minors1 = r2_wzyx * inner30 - r0_wzyx * inner23 - r3_wzyx * inner02;
				res.c1 = Minors1 * rcp_denom_ppnn;

				float4 Minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
				res.c2 = Minors2 * rcp_denom_ppnn;

				float4 Minors3 = r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
				res.c3 = Minors3 * rcp_denom_ppnn;
				return res;
			}
			// Fast matrix Inverse for rigid transforms (Orthonormal basis and translation)
			inline static float4x4 fastInverse(float4x4 m)
			{
				float4 c0 = m.c0;
				float4 c1 = m.c1;
				float4 c2 = m.c2;
				float4 pos = m.c3;

				float4 zero = float4(0);

				float4 t0 = unpacklo(c0, c2);
				float4 t1 = unpacklo(c1, zero);
				float4 t2 = unpackhi(c0, c2);
				float4 t3 = unpackhi(c1, zero);

				float4 r0 = unpacklo(t0, t1);
				float4 r1 = unpackhi(t0, t1);
				float4 r2 = unpacklo(t2, t3);

				pos = -(r0 * pos.x + r1 * pos.y + r2 * pos.z);
				pos.w = 1.0f;

				return float4x4(r0, r1, r2, pos);
			}
#pragma endregion
#pragma region Determinant
			/// <summary>Returns the Determinant of a float2x2 matrix.</summary>
			inline float Determinant(float2x2 m)
			{
				float a = m.c0.x;
				float b = m.c1.x;
				float c = m.c0.y;
				float d = m.c1.y;

				return a * d - b * c;
			}
			/// <summary>Returns the Determinant of a float3x3 matrix.</summary>
			inline float Determinant(float3x3 m)
			{
				float3 c0 = m.c0;
				float3 c1 = m.c1;
				float3 c2 = m.c2;

				float m00 = c1.y * c2.z - c1.z * c2.y;
				float m01 = c0.y * c2.z - c0.z * c2.y;
				float m02 = c0.y * c1.z - c0.z * c1.y;

				return c0.x * m00 - c1.x * m01 + c2.x * m02;
			}
			/// <summary>Returns the Determinant of a float4x4 matrix.</summary>
			inline static float Determinant(float4x4 m)
			{
				float4 c0 = m.c0;
				float4 c1 = m.c1;
				float4 c2 = m.c2;
				float4 c3 = m.c3;

				float m00 = c1.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c1.z * c3.w - c1.w * c3.z) + c3.y * (c1.z * c2.w - c1.w * c2.z);
				float m01 = c0.y * (c2.z * c3.w - c2.w * c3.z) - c2.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c2.w - c0.w * c2.z);
				float m02 = c0.y * (c1.z * c3.w - c1.w * c3.z) - c1.y * (c0.z * c3.w - c0.w * c3.z) + c3.y * (c0.z * c1.w - c0.w * c1.z);
				float m03 = c0.y * (c1.z * c2.w - c1.w * c2.z) - c1.y * (c0.z * c2.w - c0.w * c2.z) + c2.y * (c0.z * c1.w - c0.w * c1.z);

				return c0.x * m00 - c1.x * m01 + c2.x * m02 - c3.x * m03;
			}

#pragma endregion
}