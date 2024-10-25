#include "ComponentLevelLayout.h"

#include "Engine/MyEngine.h"
#include "ComponentRendererMesh.h"

void ComponentLevelLayout::Init(rapidjson::Value& serializedData)
{
	assert(serializedData["dimX"].IsInt());
	assert(serializedData["dimY"].IsInt());
	
	dimX = serializedData["dimX"].GetInt();
	dimY = serializedData["dimY"].GetInt();

	assert(dimX > 0);
	assert(dimY > 0);

	auto& levelValue = serializedData["level"];

	std::vector<int> level{ };
	
	assert(levelValue.IsArray() && levelValue.Size() == dimY);

	for (int j = 0; j < dimY; j++)
	{
		for (int i = 0; i < dimX; i++)
		{
			int element = levelValue[j][i].GetInt();
			level.push_back(element);

			CreateCube(element, i, j);
		}
	}
	PrintLevel(level);
	
	
}

void ComponentLevelLayout::PrintLevel(std::vector<int>& level)
{
	std::cout << "Printing level: " << std::endl;
	for (int j = 0; j < dimY; j++)
	{
		std::cout << "[ ";
		for (int i = 0; i < dimX; i++)
		{
			std::cout << level[j * dimX + i] << " ";
		}
		std::cout << " ]" << std::endl;
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
	gameObject.lock().get()->SetPosition(position);
	gameObject.lock().get()->AddComponent(meshRenderer);
	meshRenderer->Init(value);

	std::cout
		<< "Created " << gameObject.lock().get()->GetName()
		<< ", x: " << gameObject.lock().get()->GetPosition().x
		<< ", y: " << gameObject.lock().get()->GetPosition().y
		<< ", z: " << gameObject.lock().get()->GetPosition().z << std::endl;
}
