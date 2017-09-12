#include <iostream>

#include "World.h"

World::~World(){
	if (graphics_handler){
		delete graphics_handler;
		graphics_handler = NULL;
	}
	
	if (camera){
		delete camera;
		camera = NULL;
	};
}

void World::RunGame(const char* api){
	graphics_handler = graphics_factory.Create(api);
	if (!graphics_handler){
		std::cout << "graphics_handler = NULL" << std::endl;
		getchar();
		return;
	}

	if (api == "OpenGL"){
		graphics_handler->CreateGameWindow();
	}
}

void World::UpdateGame(){
	if (game_status != GAME_PLAYING){
		if (game_status == GAME_DONE){
			GameDestruction();
			exit(0);
		}

		if (game_status == GAME_MAIN_MENU){
			// ui.mainMenu(512, 512, 0, 0); //texture2d.Display2DTexture(512, 512, 0, 0, GAME_MAIN_MENU_TEXTURE);
		}

		if (game_status == GAME_HELP_MENU){
			//texture2d.Display2DTexture(512, 512, 0, 0, GAME_HELP_MENU_TEXTURE);
		}

		if (game_status == GAME_CREDIT_PAGE){
			//texture2d.Display2DTexture(512, 512, 0, 0, CREDIT_TEXTURE);
		}

	}
}

//Camera access functions

GLfloat World::GetZoom(){
	return camera->GetZoom();
}

void World::GetViewMatrix(glm::mat4* viewPointer){
	*viewPointer = camera->GetViewMatrix();
}

void World::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime){
	camera->ProcessKeyboard(direction, deltaTime);
}

void World::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset){
	camera->ProcessMouseMovement(xOffset, yOffset);
}