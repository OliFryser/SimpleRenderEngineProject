
#include "Engine/MyEngine.h"

namespace Asteroids {
	inline void HandleBounds(MyEngine::GameObject* parent, MyEngine::Engine* engine)
	{
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
}