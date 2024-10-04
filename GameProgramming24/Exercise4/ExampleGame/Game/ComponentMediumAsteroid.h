#pragma once

#include "ComponentAsteroid.h"

namespace Asteroids {
	class ComponentMediumAsteroid : public ComponentAsteroid {
	public:
		float CollisionRadius = 20.0f;

		void Init() override;
		void OnCollision(MyEngine::GameObject*) override;

	private:
		void SpawnSmallAsteroid(float);
	};
}