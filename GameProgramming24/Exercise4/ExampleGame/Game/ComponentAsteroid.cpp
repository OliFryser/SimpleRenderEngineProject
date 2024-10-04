#include "ComponentAsteroid.h"

#include <random>
#include <iostream>

#include "Engine/MyEngine.h"
#include "Utils.h"

namespace Asteroids {
	void ComponentAsteroid::Init() {
		auto parent = GetGameObject();
		auto engine = MyEngine::Engine::GetInstance();

		auto screenSize = engine->GetScreenSize();
		auto randomX = engine->GetRandomNumber(0, screenSize.x);
		auto randomY = engine->GetRandomNumber(0, screenSize.y);
		auto randomRotation = engine->GetRandomNumber(0, 360);

		_velocity = glm::vec2(engine->GetRandomNumber(-100, 100), engine->GetRandomNumber(-100, 100));
		_rotationAmount = engine->GetRandomNumber(-45, 45);

		parent->rotation = randomRotation;
		parent->position = glm::vec2(randomX, randomY);

		engine->CreateCircleCollider(parent, 50.0f);
	}

	void ComponentAsteroid::Update(float deltaTime) {
		auto parent = GetGameObject();
		auto engine = MyEngine::Engine::GetInstance();

		parent->position += _velocity * deltaTime;
		parent->rotation += _rotationAmount * deltaTime;

		HandleBounds(parent, engine);
	}
}
