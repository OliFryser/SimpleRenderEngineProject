#include "ComponentSmallAsteroid.h"

#include "Engine/MyEngine.h"
#include "ComponentRendererSprite.h"
#include "Utils.h"

namespace Asteroids {
	void ComponentSmallAsteroid::Init()
	{
		ComponentAsteroid::Init();
		auto engine = MyEngine::Engine::GetInstance();

		engine->CreateCircleCollider(GetGameObject(), CollisionRadius);
	}

	void ComponentSmallAsteroid::OnCollision(MyEngine::GameObject* other)
	{
		if (other->GetName() == "Laser") {
			other->Destroy();
			GetGameObject()->Destroy();
		}
	}
}

