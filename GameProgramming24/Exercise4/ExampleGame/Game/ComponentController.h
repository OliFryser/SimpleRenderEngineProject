#pragma once

#include "Engine/Component.h"

namespace Asteroids {
	class ComponentController : public MyEngine::Component {
		const float RotSpeed = 75;
		const float AccelerationAmount = 200.0f;
		const float MaxAcceleration = 50.0f;
		const float DampingFactor = 0.95f;
		const float MaxSpeed = 150.0f;
		const float ShotInterval = 0.5f;
		const float EasingFactor = 2.0f;

		bool _forward;
		bool _left;
		bool _right;
		bool _shoot;
	
		float _velocity;
		float _acceleration;
		float _rotation;

		float _lastShotTime;

		sre::Sprite _laserSprite;

		void HandleMove(MyEngine::GameObject* parent, float deltaTime);
		float EaseOut(float t) const;
		void HandleRotate(MyEngine::GameObject* parent, float deltaTime) const;
		void HandleBounds(MyEngine::GameObject*, MyEngine::Engine*);
		void Shoot(MyEngine::GameObject*, MyEngine::Engine*);
	
	public:

		ComponentController(sre::Sprite laserSprite);

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event&) override;
	};
}