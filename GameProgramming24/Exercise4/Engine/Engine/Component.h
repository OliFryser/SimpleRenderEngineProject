#pragma once

#pragma once

#include <memory>

#include "sre/RenderPass.hpp"

#include "GameObject.h"

namespace MyEngine {
	class Component {
		friend class GameObject;

	private:

	public:
		virtual void Init() {};
		virtual void Update(float) {};
		virtual void Render(sre::SpriteBatch::SpriteBatchBuilder&) {};
		virtual void KeyEvent(SDL_Event&) {};
		virtual void OnCollision(GameObject*) {};
		
		GameObject* GetGameObject();

	private:
		std::weak_ptr<GameObject> _gameObject;

		void SetGameObject(std::weak_ptr<GameObject>);
	};
}