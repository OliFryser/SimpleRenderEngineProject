#include "ComponentController.h"

#include <iostream>

#include "Engine/MyEngine.h"

namespace Asteroids {
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

		//parent->rotation += RotSpeed * deltaTime;
		
		HandleRotate(parent, deltaTime);
		HandleMove(parent, deltaTime);

		HandleBounds(parent, engine);
	}

	void ComponentController::HandleRotate(MyEngine::GameObject* parent, float deltaTime) {
		float rotationAmount;
		if (left) {
			rotationAmount = RotSpeed * deltaTime;
		}
		else if (right) {
			rotationAmount = -RotSpeed * deltaTime;
		}
		else {
			rotationAmount = 0;
		}
		parent->rotation += rotationAmount;
	}

	void ComponentController::HandleMove(MyEngine::GameObject* parent, float deltaTime)
	{
		auto direction = glm::vec2(-glm::sin(glm::radians(parent->rotation)), glm::cos(glm::radians(parent->rotation)));
		auto currentAccelerationAmount = AccelerationAmount * deltaTime;

		if (forward) {
			if (acceleration <= MaxAcceleration)
				acceleration += currentAccelerationAmount;

			velocity += acceleration * deltaTime;
		}
		else {
			if (acceleration >= currentAccelerationAmount)
				acceleration -= currentAccelerationAmount;
			else {
				// prevents negative acceleration
				// TODO: Is there a better way to do this?
				acceleration = 0;
			}

			velocity *= DampingFactor;

		}

		if (velocity > MaxSpeed)
			velocity = MaxSpeed;

		parent->position = parent->position + direction * velocity * deltaTime;
	}

	void ComponentController::HandleBounds(MyEngine::GameObject* parent, MyEngine::Engine* engine) {
		auto screenSize = engine->GetScreenSize();

		if (parent->position.x < 0) {
			parent->position.x = screenSize.x;
		}
		else if (parent->position.x > screenSize.x) {
			parent->position.x = 0;
		}
		if (parent->position.y < 0) {
			parent->position.y = screenSize.y;
		}
		else if (parent->position.y > screenSize.y) {
			parent->position.y = 0;
		}
	}

	void ComponentController::KeyEvent(SDL_Event& event)
	{
		switch (event.key.keysym.sym) {
			case SDLK_w:
				forward = event.type == SDL_KEYDOWN;
				break;
			case SDLK_a:
				left = event.type == SDL_KEYDOWN;
			case SDLK_d:
				right = event.type == SDL_KEYDOWN;
		}
	}
}