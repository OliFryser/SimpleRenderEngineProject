#pragma once

#include "Engine/Component.h"

namespace Asteroids {
	class ComponentController : public MyEngine::Component {
		float RotSpeed;
		float AccelerationAmount;
		float MaxAcceleration;
		float DampingFactor;
		float MaxSpeed;
		float ShotInterval;
		float EasingFactor;

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
		void Shoot(MyEngine::GameObject*, MyEngine::Engine*);
	
	public:

		ComponentController();

		void Initialize(picojson::value&) override;
		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event&) override;
		void OnCollision(MyEngine::GameObject*) override;
	};
}