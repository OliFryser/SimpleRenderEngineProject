#include "ComponentController.h"

#include <iostream>

#include "Engine/MyEngine.h"

namespace Asteroids {
	void ComponentController::Init() {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		parent->position = engine->GetScreenSize() / 2.f;
		_acceleration = 0.0f;
		_velocity = 0.0f;
	}

	void ComponentController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();
		
		if (_shoot) {
			Shoot(parent);
		}

		HandleRotate(parent, deltaTime);
		HandleMove(parent, deltaTime);

		HandleBounds(parent, engine);
	}

	void ComponentController::HandleRotate(MyEngine::GameObject* parent, float deltaTime) const {
		float rotationAmount;
		if (_left) {
			rotationAmount = RotSpeed * deltaTime;
		}
		else if (_right) {
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

		if (_forward) {
			if (_acceleration <= MaxAcceleration)
				_acceleration += currentAccelerationAmount;

			_velocity += _acceleration * deltaTime;
		}
		else {
			if (_acceleration >= currentAccelerationAmount)
				_acceleration -= currentAccelerationAmount;
			else {
				// prevents negative acceleration
				// TODO: Is there a better way to do this?
				_acceleration = 0;
			}

			_velocity *= DampingFactor;

		}

		if (_velocity > MaxSpeed)
			_velocity = MaxSpeed;

		parent->position = parent->position + direction * _velocity * deltaTime;
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

	void ComponentController::Shoot(MyEngine::GameObject* parent) {

	}

	void ComponentController::KeyEvent(SDL_Event& event)
	{
		switch (event.key.keysym.sym) {
			case SDLK_w:
				_forward = event.type == SDL_KEYDOWN;
				break;
			case SDLK_a:
				_left = event.type == SDL_KEYDOWN;
			case SDLK_d:
				_right = event.type == SDL_KEYDOWN;
			case SDLK_SPACE:
				_shoot = event.type = SDL_KEYDOWN;
		}
	}
}