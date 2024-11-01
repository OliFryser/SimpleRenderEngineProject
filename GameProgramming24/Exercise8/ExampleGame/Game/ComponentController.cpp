#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	assert(serializedData["jumpSpeed"].IsNumber() && "No jump speed in JSON");
	assert(serializedData["movSpeed"].IsNumber() && "No move speed in JSON");

	_jumpSpeed = serializedData["jumpSpeed"].GetFloat();
	_movSpeed = serializedData["movSpeed"].GetFloat();

	auto gameObject = GetGameObject();
	_rigidBody = gameObject.lock().get()->FindComponent<ComponentPhysicsBody>();
}

void ComponentController::Update(float deltaTime) {
	_rigidBody.lock().get()->setLinearVelocity(glm::vec2(_movSpeed * deltaTime, 0));
	if (_jump) {
		_rigidBody.lock().get()->addImpulse(glm::vec2(0, 100 * deltaTime));
		_jump = false;
	}
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym) {
		case SDLK_SPACE:
			_jump = event.type == SDL_KEYDOWN;
			break;
		default:
			break;
	}
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
}