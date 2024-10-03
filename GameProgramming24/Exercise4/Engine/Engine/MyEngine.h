#pragma once

#include <chrono>

#include "sre/Camera.hpp"
#include "sre/SpriteAtlas.hpp"
#include "SDL.h"

#include "GameObject.h"


class GameObject;

namespace MyEngine {
	class Engine {
	private:
		static Engine* _instance;
	public:
		static Engine* GetInstance() { return _instance; }
	public:
		glm::vec2 WIN_SIZE = glm::vec2(800, 600);
		const std::chrono::duration<double> MAX_FRAME_TIME = std::chrono::duration<double>(1 / 60.0);

		Engine();

		void Init();
		void ProcessEvents(SDL_Event& event);
		void Update(float);
		void Render();

		glm::vec2 GetScreenSize() const;

		int GetFrame() const { return frame; }
		float GetTime() const { return time; }

		GameObject* CreateGameObject(std::string name);

	private:
		std::shared_ptr<GameObject> _root;

		int frame;
		float time;

		unsigned char input = -1;
		bool b_show_debug_window = false;

		sre::Camera _camera;
	};
}