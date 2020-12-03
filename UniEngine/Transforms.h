#pragma once
#include <gtx/matrix_decompose.hpp>

#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	struct UNIENGINE_API GlobalTransform : ComponentBase {
		glm::mat4 Value = glm::translate(glm::vec3(0.0f))* glm::mat4_cast(glm::quat(glm::vec3(0.0f)))* glm::scale(glm::vec3(1.0f));;
		bool operator ==(const GlobalTransform& other) const {
			return other.Value == Value;
		}
#pragma region Get & set
		void GetTERS(glm::vec3& t, glm::vec3& er, glm::vec3& s) const
		{
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, s, rotation, t, skew, perspective);
			er = glm::eulerAngles(rotation);
		}
		void GetTRS(glm::vec3& t, glm::quat& r, glm::vec3& s) const
		{
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, s, r, t, skew, perspective);
		}
		glm::vec3 GetPosition() const
		{
			return Value[3];
		}
		glm::vec3 GetScale() const
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			return scale;
		}
		glm::quat GetRotation() const
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			return rotation;
		}
		glm::vec3 GetEulerRotation() const
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			return glm::eulerAngles(rotation);
		}
		void SetPosition(glm::vec3 value)
		{
			Value[3].x = value.x;
			Value[3].y = value.y;
			Value[3].z = value.z;
		}
		void SetScale(glm::vec3 value)
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			Value = glm::translate(trans) * glm::mat4_cast(rotation) * glm::scale(value);
		}
		void SetRotation(glm::quat value)
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			Value = glm::translate(trans) * glm::mat4_cast(value) * glm::scale(scale);
		}
		void SetEulerRotation(glm::vec3 value)
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			Value = glm::translate(trans) * glm::mat4_cast(glm::quat(value)) * glm::scale(scale);
		}
		void SetValue(glm::vec3 position, glm::vec3 eulerRotation, glm::vec3 scale)
		{
			Value = glm::translate(position) * glm::mat4_cast(glm::quat(eulerRotation)) * glm::scale(scale);
		}
		void SetValue(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		{
			Value = glm::translate(position) * glm::mat4_cast(rotation) * glm::scale(scale);
		}
#pragma endregion
	};
	struct UNIENGINE_API Transform : ComponentBase {
		glm::mat4 Value = glm::translate(glm::vec3(0.0f)) * glm::mat4_cast(glm::quat(glm::vec3(0.0f))) * glm::scale(glm::vec3(1.0f));;
		bool operator ==(const Transform& other) const {
			return other.Value == Value;
		}
#pragma region Get & set
		void GetTERS(glm::vec3& t, glm::vec3& er, glm::vec3& s) const
		{
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, s, rotation, t, skew, perspective);
			er = glm::eulerAngles(rotation);
		}
		void GetTRS(glm::vec3& t, glm::quat& r, glm::vec3& s) const
		{
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, s, r, t, skew, perspective);
		}
		glm::vec3 GetPosition() const
		{
			return Value[3];
		}
		glm::vec3 GetScale() const
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			return scale;
		}
		glm::quat GetRotation() const
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			return rotation;
		}
		glm::vec3 GetEulerRotation() const
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			return glm::eulerAngles(rotation);
		}
		void SetPosition(glm::vec3 value)
		{
			Value[3].x = value.x;
			Value[3].y = value.y;
			Value[3].z = value.z;
		}
		void SetScale(glm::vec3 value)
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			Value = glm::translate(trans) * glm::mat4_cast(rotation) * glm::scale(value);
		}
		void SetRotation(glm::quat value)
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			Value = glm::translate(trans) * glm::mat4_cast(value) * glm::scale(scale);
		}
		void SetEulerRotation(glm::vec3 value)
		{
			glm::vec3 scale;
			glm::vec3 trans;
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(Value, scale, rotation, trans, skew, perspective);
			Value = glm::translate(trans) * glm::mat4_cast(glm::quat(value)) * glm::scale(scale);
		}
		void SetValue(glm::vec3 position, glm::vec3 eulerRotation, glm::vec3 scale)
		{
			Value = glm::translate(position) * glm::mat4_cast(glm::quat(eulerRotation)) * glm::scale(scale);
		}
		void SetValue(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		{
			Value = glm::translate(position) * glm::mat4_cast(rotation) * glm::scale(scale);
		}
#pragma endregion
	};
}