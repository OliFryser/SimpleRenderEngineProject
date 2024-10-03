#pragma once

#include "Engine/Component.h"

namespace ExampleGame {
	class ComponentController : public MyEngine::Component {
		const float RotSpeed = 50;
		const float AccelerationAmount = 150.0f;
		const float MaxAcceleration = 50.0f;
		const float DampingFactor = 0.95f;
		const float MaxSpeed = 150.0f;

	public:
		glm::vec2 position;
		float velocity;
		float acceleration;
		float rotation;

		bool forward;
		bool left;
		bool right;

		void Init() override;
		void Update(float) override;
		void HandleMove(MyEngine::GameObject* parent, float deltaTime);
		void HandleRotate(MyEngine::GameObject* parent, float deltaTime);
		void HandleBounds(MyEngine::GameObject* parent, MyEngine::Engine* engine);
		void KeyEvent(SDL_Event&) override;
	};
}