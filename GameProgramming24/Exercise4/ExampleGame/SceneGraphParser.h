#pragma once

#include "picojson.h"
#include <stdexcept>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Engine/MyEngine.h"
#include "Engine/Component.h"
#include "Engine/CircleCollider.h"
#include "Game/ComponentController.h"
#include "Game/ComponentLargeAsteroid.h"
#include "Game/ComponentRendererSprite.h"

namespace SceneGraphParser {

	void CreateGameObject(picojson::value, MyEngine::Engine* engine, MyEngine::GameObject* parent = nullptr);
	void CreateComponent(std::string typeId, picojson::value& serializedData, MyEngine::GameObject* parent, MyEngine::Engine* engine);
	std::shared_ptr<MyEngine::Component> GetComponentFromTypeId(const std::string& typeId);

	void InitGameFromSceneGraph(std::string sceneGraphPath)
	{
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();

		std::ifstream jsonFile(sceneGraphPath);

		if (!jsonFile.is_open()) {
			std::cerr << "Error: Could not open the scene graph json file" << std::endl;
		}

		std::stringstream buffer;
		buffer << jsonFile.rdbuf();  // Read the whole file into a stringstream
		std::string jsonContent = buffer.str();  // Convert stringstream to string

		picojson::value value;
		std::string err = picojson::parse(value, jsonContent);
		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		// check if the type of the value is "object"
		if (!value.is<picojson::object>()) {
			std::cerr << "JSON is not an object" << std::endl;
			exit(2);
		}

		picojson::value gameObjects = value.get("root").get("children");
		
		if (!gameObjects.is<picojson::array>()) {
			std::cerr << "roots children is not an array" << std::endl;
			exit(2);
		}

		for (auto& child : gameObjects.get<picojson::array>()) {
			CreateGameObject(child, engine);
		}
	}

	void CreateGameObject(picojson::value child, MyEngine::Engine* engine, MyEngine::GameObject* parent) 
	{
		auto& jsonObject = child.get<picojson::object>();
		std::string name = "";

		for (auto& pair : jsonObject) {
			name = pair.first;
		}
		
		if (name == "") {
			std::cerr << "No name for game object" << std::endl;
			return;
		}

		MyEngine::GameObject* gameObject;
		if (parent != nullptr) {
			gameObject = engine->CreateGameObjectWithParent(name, parent);
		}
		else {
			gameObject = engine->CreateGameObject(name);
		}
		
		auto& transform = jsonObject[name].get("transform").get<picojson::array>();

		auto& position = transform[0].get<picojson::array>();
		
		gameObject->position = glm::vec2{
			position[0].get<double>(),
			position[1].get<double>()
		};

		gameObject->rotation = transform[1].get<double>();

		auto& scale = transform[2].get<picojson::array>();
		gameObject->scale = glm::vec2{
			scale[0].get<double>(),
			scale[1].get<double>()
		};

		for (auto& component : jsonObject[name].get("components").get<picojson::array>()) {
			std::string typeId = component.get("typeId").get<std::string>();
			picojson::value& serializedData = component.get("serializedData");

			CreateComponent(typeId, serializedData, gameObject, engine);
		}
	}
	
	void CreateComponent(std::string typeId, picojson::value& serializedData, MyEngine::GameObject* parent, MyEngine::Engine* engine)
	{
		if (typeId == "CIRCLE_COLLIDER") {
			auto radius = serializedData.get("Radius").get<double>();
			engine->CreateCircleCollider(parent, radius);
			return;
		}

		auto component = GetComponentFromTypeId(typeId);
		component->Initialize(serializedData);
		parent->AddComponent(component);
	}

	std::shared_ptr<MyEngine::Component> GetComponentFromTypeId(const std::string& typeId)
	{
		if (typeId == "CONTROLLER")
			return std::make_shared<Asteroids::ComponentController>();
		
		else if (typeId == "RENDERER_SPRITE")
			return std::make_shared<Asteroids::ComponentRendererSprite>();
		
		else if (typeId == "LARGE_ASTEROID")
			return std::make_shared<Asteroids::ComponentLargeAsteroid>();

		else throw std::invalid_argument("No component with typeId " + typeId + "\n");
	}
}