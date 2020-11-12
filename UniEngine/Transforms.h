#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {

	struct UNIENGINE_API EulerRotation : ComponentBase {
		glm::vec3 Value;
		bool operator ==(const EulerRotation& other) const {
			return other.Value == Value;
		}
	};

	struct UNIENGINE_API LocalEulerRotation : ComponentBase {
		glm::vec3 Value;
		bool operator ==(const LocalEulerRotation& other) const {
			return other.Value == Value;
		}
	};

	struct UNIENGINE_API Translation : ComponentBase {
		glm::vec3 Value;
		bool operator ==(const Translation& other) const {
			return other.Value == Value;
		}
	};
	struct UNIENGINE_API Scale : ComponentBase {
		glm::vec3 Value;
		bool operator ==(const Scale& other) const {
			return other.Value == Value;
		}
	};
	struct UNIENGINE_API Rotation : ComponentBase {
		glm::quat Value;
		bool operator ==(const Rotation& other) const {
			return other.Value == Value;
		}
	};
	struct UNIENGINE_API LocalTranslation : ComponentBase
	{
		glm::vec3 Value;
		bool operator ==(const LocalTranslation& other) const {
			return other.Value == Value;
		}
	};
	struct UNIENGINE_API LocalScale : ComponentBase {
		glm::vec3 Value;
		bool operator ==(const LocalScale& other) const {
			return other.Value == Value;
		}
	};
	struct UNIENGINE_API LocalRotation : ComponentBase {
		glm::quat Value;
		bool operator ==(const LocalRotation& other) const {
			return other.Value == Value;
		}
	};
	struct UNIENGINE_API LocalToWorld : ComponentBase {
		glm::mat4 Value;
		bool operator ==(const LocalToWorld& other) const {
			return other.Value == Value;
		}
		glm::vec3 GetPosition() const
		{
			return Value[3];
		}
	};
	struct UNIENGINE_API LocalToParent : ComponentBase {
		glm::mat4 Value;
		bool operator ==(const LocalToParent& other) const {
			return other.Value == Value;
		}
	};
}