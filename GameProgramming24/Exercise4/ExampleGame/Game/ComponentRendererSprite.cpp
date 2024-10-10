#include "ComponentRendererSprite.h"

namespace Asteroids {
	void ComponentRendererSprite::Render(sre::SpriteBatch::SpriteBatchBuilder& builder) {
		MyEngine::GameObject* parent = GetGameObject();

		sprite.setPosition(parent->position);
		sprite.setRotation(parent->rotation);
		sprite.setScale(parent->scale);
		builder.addSprite(sprite);
	}

	void ComponentRendererSprite::Initialize(picojson::value& serializedData)
	{
		auto atlas =
			sre::SpriteAtlas::create(
				serializedData.get("SpriteAtlasJSON").get<std::string>(),
				serializedData.get("SpriteAtlasImg").get<std::string>());

		sprite = atlas->get(serializedData.get("Sprite").get<std::string>());
	}
}