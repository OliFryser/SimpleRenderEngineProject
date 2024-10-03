#pragma once

#include "Engine/Component.h"

namespace Asteroids {
	class ComponentController : public MyEngine::Component {
		const float RotSpeed = 50;
		const float AccelerationAmount = 150.0f;
		const float MaxAcceleration = 50.0f;
		const float DampingFactor = 0.95f;
		const float MaxSpeed = 150.0f;

		bool _forward;
		bool _left;
		bool _right;
		bool _shoot;
	
		float _velocity;
		float _acceleration;
		float _rotation;

		void HandleMove(MyEngine::GameObject* parent, float deltaTime);
		void HandleRotate(MyEngine::GameObject* parent, float deltaTime) const;
		void HandleBounds(MyEngine::GameObject* parent, MyEngine::Engine* engine);
		void Shoot(MyEngine::GameObject* parent);
	
	public:

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event&) override;
	};
}