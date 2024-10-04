#include "ComponentMediumAsteroid.h"

#include "Engine/MyEngine.h"
#include "ComponentRendererSprite.h"
#include "ComponentSmallAsteroid.h"
#include "Utils.h"

namespace Asteroids {
	void ComponentMediumAsteroid::Init()
	{
		ComponentAsteroid::Init();
		auto engine = MyEngine::Engine::GetInstance();

		engine->CreateCircleCollider(GetGameObject(), CollisionRadius);
	}

	void ComponentMediumAsteroid::OnCollision(MyEngine::GameObject* other)
	{
		if (other->GetName() == "Laser") {
			other->Destroy();

			SpawnSmallAsteroid(10.0f);
			SpawnSmallAsteroid(-10.0f);

			GetGameObject()->Destroy();
		}
	}

	void ComponentMediumAsteroid::SpawnSmallAsteroid(float offset)
	{
		auto engine = MyEngine::Engine::GetInstance();
		auto parent = GetGameObject();

		auto asteroidObject = engine->CreateGameObject("Asteroid");
		auto small = std::make_shared<ComponentSmallAsteroid>();
		auto spriteRenderer = std::make_shared<ComponentRendererSprite>();
		spriteRenderer->sprite = Utils::GetInstance()->Atlas->get("meteorGrey_small2.png");

		asteroidObject->position = glm::vec2(parent->position.x + offset, parent->position.y);

		asteroidObject->AddComponent(spriteRenderer);
		asteroidObject->AddComponent(small);

		spriteRenderer->Init();
		small->Init();
	}

}

