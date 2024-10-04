#pragma once
#include "ComponentAsteroid.h"

namespace Asteroids {
	class ComponentSmallAsteroid : public ComponentAsteroid {
	public:
		float CollisionRadius = 10.0f;

		void Init() override;
		void OnCollision(MyEngine::GameObject*) override;
	};
}