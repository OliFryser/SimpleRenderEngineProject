#pragma once

#include <chrono>

#include "sre/Camera.hpp"
#include "sre/SpriteAtlas.hpp"
#include "SDL.h"

#include "CircleCollider.h"
#include "GameObject.h"


class GameObject;

namespace MyEngine {
	struct DeletionEntry {
		std::shared_ptr<GameObject> parent, gameObject;
	};

	struct Line {
		glm::vec3 first, last;
	};

	class Engine {
	private:
		static Engine* _instance;
	public:
		static Engine* GetInstance() { return _instance; }
	public:
		glm::vec2 WIN_SIZE = glm::vec2(800, 600);
		const std::chrono::duration<double> MAX_FRAME_TIME = std::chrono::duration<double>(1 / 60.0);

		Engine();

		void QueueForDeletion(std::shared_ptr<GameObject>, std::shared_ptr<GameObject>);
		void ClearDeletionQueue();

		void Init();
		void ProcessEvents(SDL_Event& event);
		void Update(float);
		void Render();

		glm::vec2 GetScreenSize() const;

		int GetFrame() const { return frame; }
		int inline GetRandomNumber(int min, int max) const {
			return std::rand() % (max - min + 1) + min;
		}
		float GetTime() const { return time; }

		GameObject* CreateGameObject(std::string name);
		GameObject* CreateGameObjectWithParent(std::string name, GameObject* parent);

		void CreateCircleCollider(GameObject* gameObject, float radius);

	private:
		std::shared_ptr<GameObject> _root;
		std::list<std::shared_ptr<CircleCollider>> _colliders = {};

		std::shared_ptr<sre::SpriteAtlas> _atlas;

		int frame;
		float time;

		std::list<std::shared_ptr<struct DeletionEntry>> _deletion_queue = {};

		unsigned char input = -1;
		bool b_show_debug_window = false;

		sre::Camera _camera;

		void CheckCollisions();
	};
}