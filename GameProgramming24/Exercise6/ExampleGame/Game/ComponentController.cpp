#include "ComponentController.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "glm/glm.hpp"
#include "SDL.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();

	/*std::cout << "Initialized Controller with rotSpeed: " << rot_speed << " and movSpeed: " << mov_speed << std::endl;*/
}

void ComponentController::Update(float deltaTime) {
	glm::mat4 transform = GetGameObject()->GetTransform();
	if (_left)
		Rotate(rot_speed, deltaTime, transform);
	if (_right)
		Rotate(-rot_speed, deltaTime, transform);
	if (_forward) 
	{
		glm::mat4 translation = glm::translate(GetGameObject()->GetForwardVector() * mov_speed * deltaTime);
		transform = translation * transform;
	}
	if (_backward) 
	{
		glm::mat4 translation = glm::translate(GetGameObject()->GetForwardVector() * -mov_speed * deltaTime);
		transform = translation * transform;
	}
	GetGameObject()->SetTransform(transform);
}

void ComponentController::Rotate(float rotateSpeed, float deltaTime, glm::mat4& transform)
{
	glm::vec3 axis(0, 1, 0);
	float angle = glm::radians(rotateSpeed * deltaTime);
	glm::mat4 rotation = glm::rotate(angle, axis);
	transform = transform * rotation;
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym) 
	{
		case SDLK_w:
			_forward = event.type == SDL_KEYDOWN;
			break;
		case SDLK_s:
			_backward = event.type == SDL_KEYDOWN;
			break;
		case SDLK_a:
			_left = event.type == SDL_KEYDOWN;
			break;
		case SDLK_d:
			_right = event.type == SDL_KEYDOWN;
			break;
	}
}

void ComponentController::Render(sre::RenderPass&) {
	auto gameObject = GetGameObject();
	glm::vec3 position = gameObject->GetPosition();
	glm::vec3 _rotation = gameObject->GetEulerAngles();
	glm::vec3 scale = gameObject->GetScale();

	ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 85), ImGuiCond_Always);
	ImGui::Begin("ComponentController::Render", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	if (ImGui::DragFloat3("Position", &(position.x)))
		gameObject->SetPosition(position);
	if (ImGui::DragFloat3("Rotation", &(_rotation.x)))
		gameObject->SetEulerAngles(_rotation);
	if (ImGui::DragFloat3("Scale", &(scale.x)))
		gameObject->SetScale(scale);
	ImGui::End();
}
