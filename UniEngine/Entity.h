#pragma once
#include "Misc.h"
#include "FixedData.h"
#include "ComponentBase.h"
#include "SharedComponent.h"
namespace UniEngine {
	class Entity
	{
		unsigned _Key;
		Entity* _Parent;
		std::vector<Entity*> _Children;
		std::unordered_map<std::size_t, SharedComponent*>* _SharedComponents;
		friend class EntityCollection;
		Entity(unsigned key);
		void RemoveChild(Entity* child);
		~Entity();
	public:
		Entity* Parent();
		std::vector<Entity*>* Children();
		template <class T>
		void SetSharedComponent(T* value);
		template <typename T>
		T* GetSharedComponent();
		unsigned Key();
	};
	template<typename T>
	inline T* Entity::GetSharedComponent()
	{
		auto key = typeid(T).hash_code();
		auto search = _SharedComponents->find(key);
		if (search != _SharedComponents->end()) {
			return dynamic_cast<T*>(search->second);
		}
		return nullptr;
	}
	template<class T>
	inline void Entity::SetSharedComponent(T* value)
	{
		auto key = typeid(T).hash_code();
		auto search = _SharedComponents->find(key);
		if (search != _SharedComponents->end()) {
			search->second = dynamic_cast<SharedComponent*>(value);
			return;
		}
		dynamic_cast<SharedComponent*>(value)->SetEntity(this);
		_SharedComponents->insert({ key, dynamic_cast<SharedComponent*>(value) });
	}
}