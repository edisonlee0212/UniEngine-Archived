#pragma once
#include "Misc.h"
namespace UniEngine {
	class Entity;
	class SharedComponentBase {
		friend class Entity;
		Entity* _Entity;
		void SetEntity(Entity* entity);
	public:
		virtual std::size_t GetHashCode() = 0;
	};
}