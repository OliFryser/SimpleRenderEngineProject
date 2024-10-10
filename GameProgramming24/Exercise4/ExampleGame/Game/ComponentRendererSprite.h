#pragma once

#include "sre/SpriteAtlas.hpp"
#include "sre/Sprite.hpp"

#include "Engine/Component.h"

namespace Asteroids {
	class ComponentRendererSprite : public MyEngine::Component {
	public:
		sre::Sprite sprite;

		void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
		void Initialize(picojson::value&) override;
	};
}