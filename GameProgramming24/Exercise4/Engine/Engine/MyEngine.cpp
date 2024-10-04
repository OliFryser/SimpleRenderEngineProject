#include "MyEngine.h"

#include <random>

#include "sre/RenderPass.hpp"

namespace MyEngine {
	Engine* Engine::_instance = nullptr;

	void Engine::QueueForDeletion(std::shared_ptr<GameObject> gameObject, std::shared_ptr<GameObject> parent) {
		auto entry = std::make_shared<struct DeletionEntry>();
		entry->gameObject = gameObject;
		entry->parent = parent;
		_deletion_queue.push_back(entry);
	}

	Engine::Engine() {
		frame = 0.0f;
		time = 0.0f;

		assert(_instance == nullptr && " Only one instance of MyEngine::Engine allowed!");
		_instance = this;

		_root = std::make_shared<GameObject>();
		_root->SetName("root");
	}

	glm::vec2 Engine::GetScreenSize() const
	{
		return WIN_SIZE;
	}

	void Engine::Init() {
		// initializes random generator
		std::srand(std::time(nullptr));

		_camera.setWindowCoordinates();

		_root->Init();
	}

	void Engine::ProcessEvents(SDL_Event& event) {
		_root->KeyEvent(event);
	}

	void Engine::Update(float deltaTime) {
		++frame;
		time += deltaTime;
		_root->Update(deltaTime);
	}

	void Engine::Render()
	{
		sre::RenderPass renderPass = sre::RenderPass::create()
			.withCamera(_camera)
			.withClearColor(true, { .1, .1, .2, 1 })
			.build();

		sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();

		_root->Render(spriteBatchBuilder);

		auto spriteBatch = spriteBatchBuilder.build();
		renderPass.draw(spriteBatch);

		ClearDeletionQueue();
	}

	GameObject* Engine::CreateGameObject(std::string name) {
		auto ret = std::make_shared<GameObject>();
		ret->_self = ret;
		ret->_parent = _root;
		ret->SetName(name);
		_root->AddChild(ret);

		return ret.get();
	}

	GameObject* Engine::CreateGameObjectWithParent(std::string name, GameObject* parent) {
		auto ret = std::make_shared<GameObject>();
		ret->_self = ret;
		ret->_parent = parent->_self;
		ret->SetName(name);
		parent->AddChild(ret);

		return ret.get();
	}

	void Engine::ClearDeletionQueue()
	{
		for each (auto entry in _deletion_queue)
		{
			entry->parent->RemoveChild(entry->gameObject);
		}
		_deletion_queue.clear();
	}
}