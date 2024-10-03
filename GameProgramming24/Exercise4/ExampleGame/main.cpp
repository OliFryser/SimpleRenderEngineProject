#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"

#include "Game/ComponentController.h"
#include "Game/ComponentRendererSprite.h"

void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();

MyEngine::Engine engine;

glm::vec2 window_size = glm::vec2(1200, 800);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

int main() {
	engine.WIN_SIZE = window_size;
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;

	renderer.setWindowSize(window_size);
	renderer.init();
	camera.setWindowCoordinates();

	

	engine.Init();

	renderer.startEventLoop();
}

void InitGame() {
	atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");

	auto gameObject = engine.CreateGameObject("GameObject");
	auto playerController = std::shared_ptr<Asteroids::ComponentController>(new Asteroids::ComponentController());
	auto playerRenderer = std::make_shared<Asteroids::ComponentRendererSprite>();
	gameObject->AddComponent(playerController);
	gameObject->AddComponent(playerRenderer);

	playerRenderer->sprite = atlas->get("playerShip2_red.png");
}

void ProcessEvents(SDL_Event& event) { 
	engine.ProcessEvents(event);
}

void Update(float deltaTime) {
	engine.Update(deltaTime);
}

void Render() {
	engine.Render();
}