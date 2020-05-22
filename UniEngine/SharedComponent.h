#pragma once
namespace UniEngine {
	class Entity;
	class SharedComponent {
		friend class Entity;
		Entity* _Entity;
		void SetEntity(Entity* entity);
	public:
		virtual void Update() {};
		virtual void FixedUpdate() {};
	};
}