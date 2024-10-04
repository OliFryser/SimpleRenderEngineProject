#pragma once

#include "ComponentAsteroid.h"

namespace Asteroids {
	class ComponentLargeAsteroid : public ComponentAsteroid {
	public:
		float CollisionRadius = 50.0f;

		void Init() override;
		void OnCollision(MyEngine::GameObject*) override;
	
	private:
		void SpawnMediumAsteroid(float);
	};
}