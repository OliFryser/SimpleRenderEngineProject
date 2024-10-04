#pragma once

#include "Engine/MyEngine.h"

namespace Asteroids {
	class Utils {
	private:
		static Utils* _instance;

		// Private Constructor
		Utils() {
			Atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");
		}

	public:
		Utils(const Utils& obj) = delete;

		std::shared_ptr<sre::SpriteAtlas> Atlas;

		// Static method to get the Singleton instance
		static Utils* GetInstance() {
			if (_instance == nullptr) {
				_instance = new Utils();
			}
			return _instance;
		}

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
	};
}