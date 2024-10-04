#include "ComponentLargeAsteroid.h"

#include "Engine/MyEngine.h"
#include "ComponentRendererSprite.h"
#include "ComponentMediumAsteroid.h"
#include "Utils.h"

namespace Asteroids {
	void ComponentLargeAsteroid::Init()
	{
		ComponentAsteroid::Init();
		auto engine = MyEngine::Engine::GetInstance();
		auto parent = GetGameObject();

		auto screenSize = engine->GetScreenSize();
		auto randomX = engine->GetRandomNumber(0, screenSize.x);
		auto randomY = engine->GetRandomNumber(0, screenSize.y);
		parent->position = glm::vec2(randomX, randomY);

		engine->CreateCircleCollider(GetGameObject(), CollisionRadius);
	}

	void ComponentLargeAsteroid::OnCollision(MyEngine::GameObject* other)
	{
		if (other->GetName() == "Laser") {
			other->Destroy();

			SpawnMediumAsteroid(-10.0f);
			SpawnMediumAsteroid(10.0f);

			GetGameObject()->Destroy();
		}
	}

	void ComponentLargeAsteroid::SpawnMediumAsteroid(float offset)
	{
		auto engine = MyEngine::Engine::GetInstance();
		auto parent = GetGameObject();

		auto asteroidObject = engine->CreateGameObject("Asteroid");
		auto medium = std::make_shared<ComponentMediumAsteroid>();
		auto spriteRenderer = std::make_shared<ComponentRendererSprite>();

		spriteRenderer->sprite = Utils::GetInstance()->Atlas->get("meteorGrey_med2.png");

		asteroidObject->position = glm::vec2(parent->position.x + offset, parent->position.y);

		asteroidObject->AddComponent(medium);
		asteroidObject->AddComponent(spriteRenderer);

		spriteRenderer->Init();
		medium->Init();
	}
}