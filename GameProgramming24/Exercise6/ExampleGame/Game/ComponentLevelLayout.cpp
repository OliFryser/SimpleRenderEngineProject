#include "ComponentLevelLayout.h"

#include "Engine/MyEngine.h"
#include "ComponentRendererMesh.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

void ComponentLevelLayout::Init(rapidjson::Value& serializedData)
{
	auto& levelValue = serializedData["level"];
	
	assert(levelValue.IsArray() && levelValue.Size());

	for (int j = 0; j < levelValue.Size(); j++)
	{
		for (int i = 0; i < levelValue[j].Size(); i++)
		{
			int element = levelValue[j][i].GetInt();
			CreateCube(element, i, j);
		}
	}
}

void ComponentLevelLayout::CreateCube(int textureIndex, int x, int y)
{
	if (textureIndex == -1) return;
	auto engine = MyEngine::Engine::GetInstance();
	glm::vec3 position = glm::vec3(x, 0, y);

	// Create serializedData for MeshRenderer
	rapidjson::Document document;
	rapidjson::Value value(rapidjson::kObjectType);
	value.AddMember("textureIndex", textureIndex, document.GetAllocator());
	auto meshRenderer = std::make_shared<ComponentRendererMesh>();

	auto gameObject = engine->CreateGameObject("cube" + std::to_string(x) + std::to_string(y));
	auto p_gameObject = gameObject.lock().get();
	auto transform =
		glm::translate(position) *
		glm::mat4_cast(glm::quat(glm::radians(glm::vec3(0, 0, 0)))) *
		glm::scale(glm::vec3(1, 1, 1));
	
	p_gameObject->SetTransform(transform);
	p_gameObject->AddComponent(meshRenderer);

	meshRenderer->Init(value);
	
	std::cout
		<< "Created " << p_gameObject->GetName()
		<< ", x: " << p_gameObject->GetPosition().x
		<< ", y: " << p_gameObject->GetPosition().y
		<< ", z: " << p_gameObject->GetPosition().z << std::endl;
}
