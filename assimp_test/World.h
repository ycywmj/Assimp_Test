#pragma once

#include "Graphics.h"
#include "GameStatus.h"
#include "GameObject.h"

class World{
public:
	World(){
		game_status = GAME_PLAYING;
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

	GameObject test_obj;
};
