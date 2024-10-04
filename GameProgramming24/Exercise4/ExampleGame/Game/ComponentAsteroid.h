#pragma once

#include "Engine/Component.h"

namespace Asteroids {
	class ComponentAsteroid : public MyEngine::Component {
		glm::vec2 _velocity;
		float _rotationAmount;
	
	public:
		void Init() override;
		void Update(float) override;
	};
}