#include "ComponentController.h"

#include <iostream>

#include "Engine/MyEngine.h"
#include "ComponentLaser.h"
#include "ComponentRendererSprite.h"
#include "Utils.h"

namespace Asteroids {
	ComponentController::ComponentController(sre::Sprite laserSprite) {
		_laserSprite = laserSprite;
		_shoot = false;
		_forward = false;
		_left = false;
		_right = false;

		// initialize the variables in contstructor
		_acceleration = 0;
		_velocity = 0;
		_lastShotTime = 0;
		_rotation = 0;
	}

	void ComponentController::Init()
	{
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();
		
		auto screenSize = engine->GetScreenSize();

		parent->position = { screenSize.x * .5f, screenSize.y * .25f };
		parent->scale = { .75f, .75f };
		_acceleration = 0.0f;
		_velocity = 0.0f;
	}

	void ComponentController::Update(float deltaTime) 
	{
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();
		
		if (_shoot) {
			Shoot(parent, engine);
		}

		HandleRotate(parent, deltaTime);
		HandleMove(parent, deltaTime);

		HandleBounds(parent, engine);
	}

	void ComponentController::HandleRotate(MyEngine::GameObject* parent, float deltaTime) const 
	{
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
			float normalizedAcceleration = _acceleration / MaxAcceleration;

			if (_acceleration <= MaxAcceleration) {

				if (_acceleration > 0) {
					float easedAccelerationFactor = EaseOut(normalizedAcceleration);
					_acceleration += easedAccelerationFactor * currentAccelerationAmount;
				}
				else {
					// initial acceleration should not be eased
					_acceleration += currentAccelerationAmount;
				}
			}

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

	float ComponentController::EaseOut(float t) const
	{
		return 1.0f - pow(1.0f - t, EasingFactor);
	}

	void ComponentController::Shoot(MyEngine::GameObject* parent, MyEngine::Engine* engine) 
	{
		if (engine->GetTime() - _lastShotTime < ShotInterval) 
			    return;

		auto gameObject = engine->CreateGameObjectWithParent("Laser", parent);

		auto laserComponent = std::make_shared<ComponentLaser>();
		auto laserRenderer = std::make_shared<ComponentRendererSprite>();
		laserRenderer->sprite = _laserSprite;

		gameObject->AddComponent(laserComponent);
		gameObject->AddComponent(laserRenderer);

		gameObject->position = parent->position;
		gameObject->rotation = parent->rotation;

		gameObject->Init();

		_lastShotTime = engine->GetTime();
	}

	void ComponentController::KeyEvent(SDL_Event& event)
	{
		switch (event.key.keysym.sym) {
			case SDLK_w:
				_forward = event.type == SDL_KEYDOWN;
				break;
			case SDLK_a:
				_left = event.type == SDL_KEYDOWN;
				break;
			case SDLK_d:
				_right = event.type == SDL_KEYDOWN;
				break;
			case SDLK_SPACE:
				_shoot = event.type == SDL_KEYDOWN;
				break;
			default:
				break;
		}
	}
}