#include "ComponentController.h"

#include <iostream>

#include "Engine/MyEngine.h"

namespace ExampleGame {
	void ComponentController::Init() {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		parent->position = engine->GetScreenSize() / 2.f;
		acceleration = 0.0f;
		velocity = 0.0f;
	}

	void ComponentController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		glm::vec2 basePos = engine->GetScreenSize() / 2.f;

		//parent->rotation += RotSpeed * deltaTime;

		//std::cout << "x: " << -glm::sin(glm::radians(parent->rotation)) << ", y: " << -glm::cos(glm::radians(parent->rotation)) << std::endl;

		auto direction = glm::vec2(-glm::sin(glm::radians(parent->rotation)), glm::cos(glm::radians(parent->rotation)));

		if (move) {
			if (acceleration <= MaxAcceleration)
				acceleration += AccelerationAmount * deltaTime;
			velocity += acceleration * deltaTime;
		}
		else {
			if (acceleration >= AccelerationAmount * deltaTime)
				acceleration -= AccelerationAmount * deltaTime;
			else {
				acceleration = 0;
			}
			
			velocity *= DampingFactor;
			
		}
		
		if (velocity > MaxSpeed)
			velocity = MaxSpeed;

		std::cout << "Acceleration: " << acceleration << " Velocity: " << velocity << std::endl;
		

		auto newPos = parent->position + direction * velocity * deltaTime;

		parent->position = newPos;
	}

	void ComponentController::KeyEvent(SDL_Event& event)
	{
		switch (event.key.keysym.sym) {
			case SDLK_w:
				move = event.type == SDL_KEYDOWN;
				break;
		}
	}
}