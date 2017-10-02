#ifndef WORLD_H
#define WORLD_H

#include "Graphics.h"
#include "GameStatus.h"

class World{
public:
	World(){
		game_status = GAME_PLAYING;
	};
	~World();
	World(const World & cpy){};

	void RunGame(const char* api);
	void UpdateGame();
	void GameDestruction(){};

private:
	GraphicsFactory graphics_factory;
	Graphics* graphics_handler;

	GameStatus game_status;
};

#endif