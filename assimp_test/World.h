#pragma once

#include "Graphics.h"
#include "GameStatus.h"
#include "GameObject.h"
#include "Camera.h"
#include "Singleton.h"

class World{
public:
	World(){
		game_status = Singleton<GameStatus>::Instance();
		*game_status = GAME_PLAYING;
		camera = Singleton<Camera>::Instance();
	};
	~World();
	World(const World & cpy){};

	void InitializeGame();
	void RunGame(const char* api);
	void UpdateGame();
	void GameDestruction(){};
	
	void InitialBench1();
	void InitialBench2();
	void InitialChair1();
	void InitialChair2();
	void InitialTable1();
	void InitialScene();
	void Initial2DTexture();

	void DrawBench1();
	void DrawBench2();
	void DrawChair1();
	void DrawChair2();
	void DrawTable1();
	void DrawScene();

	void SetBoundingWall();
	void CheckBoundingBox();

private:
	GraphicsFactory graphics_factory;
	Graphics* graphics_handler;

	GameStatus *game_status;
	Camera* camera;
	
	float CurrentX;
	float CurrentZ;

	int numberOfBenchs;
	
	GameObject cameraPlayer;

	GameObject Scene;


	map<int, GameObject> BoundingWalls;
	GameObject *BoundingWall;

	map<int, GameObject> Bench1s;
	GameObject *Bench1;

	map<int, GameObject> Bench2s;
	GameObject *Bench2;

	map<int, GameObject> Chair1s;
	GameObject *Chair1;

	map<int, GameObject> Chair2s;
	GameObject *Chair2;

	map<int, GameObject> Table1s;
	GameObject *Table1;


};
