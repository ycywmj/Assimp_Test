#pragma once

#include "Graphics.h"
#include "GameStatus.h"
#include "GameObject.h"
#include "Camera.h"
#include "Singleton.h"

class World{
public:
	World(){
		game_status = GAME_PLAYING;
		camera = Singleton<Camera>::Instance();
	};
	~World();
	World(const World & cpy){};

	void InitializeGame();
	void RunGame(const char* api);
	void UpdateGame();
	void GameDestruction(){};

private:
	GraphicsFactory graphics_factory;
	Graphics* graphics_handler;

	GameStatus game_status;
	Camera* camera;

	int numberOfBenchs;
	GameObject Bench[2];

	//GameObject Bench2;

	GameObject Scene;
};
