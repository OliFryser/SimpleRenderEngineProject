#include "ComponentLaser.h"

#include "Engine/MyEngine.h"

namespace Asteroids {

	void ComponentLaser::Init() 
	{
		auto engine = MyEngine::Engine::GetInstance();
		_startTime = engine->GetTime();

		auto parent = GetGameObject();
		_direction =
			glm::vec2(
				-glm::sin(glm::radians(parent->rotation)),
				glm::cos(glm::radians(parent->rotation)));

		parent->scale = { .75f, .75f };
	}

	void ComponentLaser::Update(float deltaTime)
	{
		auto engine = MyEngine::Engine::GetInstance();
		float lifeTime = engine->GetTime() - _startTime;

		auto parent = GetGameObject();
		if (lifeTime >= MaxLifeTime) {
			parent->Destroy();
			return;
		}

		parent->position += _direction * Velocity * deltaTime;
	}
}