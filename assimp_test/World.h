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
	/// Generates a specific graphics api handler object
	GraphicsFactory graphics_factory;

	/// Stores a specific graphics api that handles all the graphics work
	Graphics* graphics_handler;

	/// Status of the game program - see enum variable in GameStatus.h
	GameStatus *game_status;

	/// Camera object
	Camera* camera;
	
	/// For restoring cam pos after collusion
	float CurrentX;

	/// For restoring cam pos after collusion
	float CurrentZ;

	/// Number of benches in the virtual world
	int numberOfBenchs;
	
	/// Player itself in the world as a game object
	GameObject cameraPlayer;

	/// Whole bar scene
	GameObject Scene;

	/// Stores all the walls need to detect collusion
	map<int, GameObject> BoundingWalls;

	/// Stores multiple walls need to detect collusion
	GameObject *BoundingWall;

	/// Stores all the no.1 benches
	map<int, GameObject> Bench1s;
	
	/// Stores multiple no.1 benches
	GameObject *Bench1;

	/// Stores all the no.2 benches
	map<int, GameObject> Bench2s;

	/// Stores multiple no.2 benches
	GameObject *Bench2;

	/// Stores all the no.1 chairs
	map<int, GameObject> Chair1s;

	/// Stores multiple no.1 chairs
	GameObject *Chair1;

	/// Stores all the no.2 chairs
	map<int, GameObject> Chair2s;
	
	/// Stores multiple no.2 chairs
	GameObject *Chair2;

	/// Stores all the tables
	map<int, GameObject> Table1s;

	/// Stores multiple tables
	GameObject *Table1;


};
