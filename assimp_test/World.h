#pragma once

#include "Graphics.h"
#include "GameStatus.h"
<<<<<<< HEAD
#include "Camera.h"
=======
#include "GameObject.h"
>>>>>>> 71f25845de60e130c0666c3b0b6f674d69a05744

class World{
public:
	World(){
		game_status = GAME_PLAYING;
		camera = new Camera(glm::vec3(0.0f, 20.0f, 50.0f));
	};
	~World();
	World(const World & cpy){};

	void InitializeGame();
	void RunGame(const char* api);
	void UpdateGame();
	void GameDestruction(){};
	
	GLfloat GetZoom();
	void GetViewMatrix(glm::mat4* viewPointer);
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset);

private:
	GraphicsFactory graphics_factory;
	Graphics* graphics_handler;
	Camera* camera;
	GameStatus game_status;

	GameObject *test_obj;
};
