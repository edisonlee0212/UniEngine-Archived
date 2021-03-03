#pragma once
#include "UniEngineAPI.h"
#include "Singleton.h"
#include "Entity.h"
namespace UniEngine {
	class UNIENGINE_API ComponentFactory : public Singleton<ComponentFactory>
	{
		std::unordered_map<std::string, std::function<std::shared_ptr<ComponentBase>(size_t&, size_t&)>> m_componentDataGenerators;
		std::unordered_map<std::string, std::function<Serializable* (size_t&)>> m_classComponentGenerators;
	public:
		template <typename T = Serializable>
		static bool RegisterComponentData();
		template <typename T = ComponentBase>
		static bool RegisterSerializable();
		static bool Register(const std::string& id, const std::function<std::shared_ptr<ComponentBase>(size_t&, size_t&)>& func);
		static std::shared_ptr<ComponentBase> ProduceComponentData(const std::string& id, size_t& hashCode, size_t& size);
		static bool Register(const std::string& id, const std::function<Serializable* (size_t&)>& func);
		static Serializable* ProduceSerializableObject(const std::string& id, size_t& hashCode);
	};

	template <typename T>
	bool ComponentFactory::RegisterComponentData()
	{
		std::string id = typeid(T).name();
		return Register(id, [](size_t& hashCode, size_t& size)
			{
				hashCode = typeid(T).hash_code();
				size = sizeof(T);
				return std::move(std::dynamic_pointer_cast<ComponentBase>(std::make_shared<T>()));
			}
		);
	}

	template <typename T>
	bool ComponentFactory::RegisterSerializable()
	{
		std::string id = typeid(T).name();
		return Register(id, [](size_t& hashCode)
			{
				hashCode = typeid(T).hash_code();
				return dynamic_cast<Serializable*>(new T());
			}
		);
	}



	template <typename T = ComponentBase>
	class UNIENGINE_API ComponentDataRegistration
	{
	public:
		ComponentDataRegistration(int none)
		{
			std::string id = typeid(T).name();
			ComponentFactory::Register(id, [](size_t& hashCode, size_t& size)
				{
					hashCode = typeid(T).hash_code();
					size = sizeof(T);
					return std::move(std::dynamic_pointer_cast<ComponentBase>(std::make_shared<T>()));
				}
			);
		}
	};

	template <typename T = Serializable>
	class UNIENGINE_API SerializableRegistration
	{
	public:
		SerializableRegistration(int none)
		{
			std::string id = typeid(T).name();
			ComponentFactory::Register(id, [](size_t& hashCode)
				{
					hashCode = typeid(T).hash_code();
					return dynamic_cast<Serializable*>(new T());
				}
			);
		}
	};

}