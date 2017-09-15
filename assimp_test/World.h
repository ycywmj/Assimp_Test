#pragma once

#include "Graphics.h"
#include "GameStatus.h"
#include "GameObject.h"
#include "Camera.h"
#include "Singleton.h"


//---------------------------------------------------------------------------------

/**
* @class World
* @brief  Manages the running of the game world
*
* World is responsible for the running of the game world, this consists of
* Initialising the world, Running the world, Updating the wolrd. It also
* is curently responsible for the location of objects within the scene
*
* @author Liam Goerke
* @version 01
* @date 10/09/2017
*
* @author ChengYu Yang
* @version 02
* @date 15/09/2017 
*
*
*
*/

class World{
public:
	/**
	* @brief  Constructor
	*
	* Initialises game_status singleton and sets game status to GAME_PLAYING
	*/
	World(){
		game_status = Singleton<GameStatus>::Instance();
		*game_status = GAME_PLAYING;
		camera = Singleton<Camera>::Instance();
	};
	/**
	* @brief  Destructor
	*/
	~World();
	/**
	* @brief  Copy constructor
	*/
	World(const World & cpy){};

	/**
	* @brief  Initializes the game world
	* This function loads initial models, sets bounding boxes and sets the players initial values
	* @return void
	*/
	void InitializeGame();

	/**
	* @brief  Runs the simulation world
	* Calls the graphics handler to create a game windwo
	* @param api - a string to determine which graphics to use (currently OpenGL)
	* @return void
	*/
	void RunGame(const char* api);

	/**
	* @brief  Updates the world 
	* Checks the curent game status and reacts accordingly
	* Makes calls to render models, update player values and checks for collisisons
	* @return void
	*/
	void UpdateGame();

	/**
	* @brief  Willl be responsible for destruction of game
	* 
	* @return void
	*/
	void GameDestruction(){};
	
	/**
	* @brief  Loads the scene
	* Loads the scene model
	* 
	* @return void
	*/
	void InitialScene();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void InitialBench1();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void InitialBench2();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void InitialChair1();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void InitialChair2();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void InitialTable1();
	
	/**
	* @brief  Loads 2D exit texture on screen
	*
	* @return void
	*/
	void Initial2DTexture();
	
	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void DrawScene();

	/**
	* @brief  Draws Scene
	*
	* @return void
	*/
	void DrawBench1();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void DrawBench2();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void DrawChair1();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void DrawChair2();

	/**
	* @brief  Loads model into world
	*
	* @return void
	*/
	void DrawTable1();

	/**
	* @brief  Sets the scenes bounding walls
	*
	* @return void
	*/
	void SetBoundingWall();

	/**
	* @brief  Checks for collissions between player and AABB's
	*
	* @return void
	*/
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
