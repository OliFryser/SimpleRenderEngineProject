#include "ComponentRendererSprite.h"

namespace Asteroids {
	void ComponentRendererSprite::Render(sre::SpriteBatch::SpriteBatchBuilder& builder) {
		MyEngine::GameObject* parent = GetGameObject();

		sprite.setPosition(parent->position);
		sprite.setRotation(parent->rotation);
		sprite.setScale(parent->scale);
		builder.addSprite(sprite);
	}
}