#pragma once

#include <list>
#include <memory>
#include <string>

#include "sre/SpriteBatch.hpp"

namespace MyEngine {
	class Component;
	class CircleCollider;

	class GameObject {
		friend class Engine;

		// public API
	public:
		glm::vec2 position;
		glm::vec2 scale{1.0f, 1.0f};
		float rotation;

		~GameObject();

		void Init();
		void Update(float);
		void Render(sre::SpriteBatch::SpriteBatchBuilder&);
		void KeyEvent(SDL_Event&);

		void AddChild(std::shared_ptr<GameObject>);
		void AddComponent(std::shared_ptr<Component>);
		void RemoveChild(std::shared_ptr<GameObject>);
		void Destroy();

		void OnCollision(std::shared_ptr<CircleCollider>);

		std::string GetName();
		void SetName(std::string);
		
		// private fields
	private:
		std::weak_ptr<GameObject> _parent;
		std::weak_ptr<GameObject> _self;
		std::list<std::shared_ptr<GameObject>> _children = {};
		std::list< std::shared_ptr<Component>> _components = {};
		std::string _name;
	};
}