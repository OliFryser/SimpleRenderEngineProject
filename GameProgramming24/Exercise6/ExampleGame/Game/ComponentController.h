#pragma once

#include "Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void Render(sre::RenderPass&) override;

private:
	float mov_speed;
	float rot_speed;

	bool _forward, _backward, _left, _right;

	void Rotate(float rotateSpeed, float deltaTime, glm::mat4& transform);
};