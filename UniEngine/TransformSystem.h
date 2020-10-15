#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
namespace UniEngine {

#pragma region Predefined Componenets
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
	};
	struct UNIENGINE_API LocalToParent : ComponentBase {
		glm::mat4 Value;
		bool operator ==(const LocalToParent& other) const {
			return other.Value == Value;
		}
	};
	
#pragma endregion


	struct ChildInfo {
		Entity Child;
		LocalToParent LastLTP;
		LocalToWorld LastPLTW;
	};
	class UNIENGINE_API TransformSystem :
		public SystemBase
	{
		bool _AddCheck;
		EntityQuery _ERR;
		EntityQuery _LERR;
		
		EntityQuery _P;
		EntityQuery _PR;
		EntityQuery _PS;
		EntityQuery _PRS;
		EntityQuery _R;
		EntityQuery _RS;
		EntityQuery _S;

		EntityQuery _LP;
		EntityQuery _LPR;
		EntityQuery _LPS;
		EntityQuery _LPRS;
		EntityQuery _LR;
		EntityQuery _LRS;
		EntityQuery _LS;

		size_t _CurrentStoredHierarchyVersion = INT_MAX;
		std::vector<std::pair<Entity, ChildInfo>> _CachedParentHierarchies;
		void CalculateLtwRecursive(LocalToWorld pltw, Entity entity);
		void CollectHierarchy(std::vector<std::pair<Entity, ChildInfo>>* container, Entity entity);
	public:
		void OnCreate() override;
		void OnDestroy() override;
		void Update() override;
	};

}