#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "SceneGraphParser.h"

#include "Engine/MyEngine.h"

#include "Game/ComponentController.h"
#include "Game/ComponentRendererSprite.h"
#include "Game/ComponentLargeAsteroid.h"

int main();
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

	SceneGraphParser::InitGameFromSceneGraph("data/AsteroidsScene.json");
	//InitGame();

	engine.Init();

	renderer.startEventLoop();
}

void InitGame() {
	atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");

	auto gameObject = engine.CreateGameObject("Player");
	auto playerController = std::make_shared<Asteroids::ComponentController>();
	auto playerRenderer = std::make_shared<Asteroids::ComponentRendererSprite>();
	engine.CreateCircleCollider(gameObject, 37.5f);
	gameObject->AddComponent(playerController);
	gameObject->AddComponent(playerRenderer);

	playerRenderer->sprite = atlas->get("playerShip2_red.png");

	std::string asteroids[]{ "meteorGrey_big2.png", "meteorGrey_med2.png", "meteorGrey_small2.png" };

	for (int i = 0; i < 5; i++) {
		auto asteroidGameObject = engine.CreateGameObject("Asteroid");
		auto asteroid = std::make_shared<Asteroids::ComponentLargeAsteroid>();
		auto asteroidRenderer = std::make_shared<Asteroids::ComponentRendererSprite>();
		asteroidGameObject->AddComponent(asteroid);
		asteroidGameObject->AddComponent(asteroidRenderer);

		std::string spriteName = asteroids[0];
		auto sprite = atlas->get(spriteName);
		asteroidRenderer->sprite = sprite;
	}
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