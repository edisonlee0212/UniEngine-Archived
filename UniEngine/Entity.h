#pragma once
#include "Misc.h"
#include "Math.h"
#include "SharedComponent.h"
namespace UniEngine {
	class Entity
	{
		uint _Key;
		Entity* _Parent;
		std::unordered_map<std::size_t, SharedComponent*>* _SharedComponents;
		friend class EntityManager;
		template <typename T>
		T* GetSharedComponent();
		template <class T>
		void SetSharedComponent(T* value);
		Entity(uint key);
		~Entity();
		void SetParent(Entity* parent);
	public:
		uint Key();
	};
	template<typename T>
	inline T* Entity::GetSharedComponent()
	{
		auto key = typeid(T).hash_code();
		auto search = _SharedComponents->find(key);
		if (search != _SharedComponents.end()) {
			return dynamic_cast<T*>(search->second);
		}
		return nullptr;
	}
	template<class T>
	inline void Entity::SetSharedComponent(T* value)
	{
		auto key = typeid(T).hash_code();
		auto search = _SharedComponents->find(key);
		if (search != _SharedComponents.end()) {
			search->second = dynamic_cast<SharedComponent*>(value);
			return;
		}
		_SharedComponents->insert(key, dynamic_cast<SharedComponent*>(value));
	}
}