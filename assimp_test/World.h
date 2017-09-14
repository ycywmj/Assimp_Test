#pragma once

#include "Graphics.h"
#include "GameStatus.h"
#include "GameObject.h"
#include "Camera.h"
#include "Singleton.h"
#include "Texture2D.h"

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
	
	void DrawBench1();
	void DrawBench2();
	void DrawChair1();
	void DrawChair2();
	void DrawTable1();

	void SetBoundingWall();
	void CheckBoundingBox();

private:
	GraphicsFactory graphics_factory;
	Graphics* graphics_handler;

	GameStatus game_status;
	Camera* camera;
	
	float CurrentX;
	float CurrentZ;

	int numberOfBenchs;

	GameObject Bench;
	
	GameObject Bench2;

	GameObject chair1;

	GameObject chair2;

	GameObject cameraPlayer;

	GameObject table1;

	GameObject Scene;


	map<int, GameObject> BoundingWalls;
	GameObject *BoundingWall;


};
