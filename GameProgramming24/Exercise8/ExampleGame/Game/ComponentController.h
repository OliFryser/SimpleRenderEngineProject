#pragma once

#include "Engine/Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other) override;

private:
	std::weak_ptr<ComponentPhysicsBody> _rigidBody;
	glm::vec3 _mov;
	float _movSpeed;
	float _jumpSpeed;
	bool _jump;
};