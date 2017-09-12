#include <iostream>

#include "World.h"

World::~World(){
	if (graphics_handler){
		delete graphics_handler;
		graphics_handler = NULL;
	}
}

void World::InitializeGame(){
	Bench.Load(graphics_handler, "res/models/bench/bench.obj");
	//Bench2.Load(graphics_handler, "res/models/bench/bench.obj");


	Scene.Load(graphics_handler, "res/models/scene/scense.obj");
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

	//Render Model
	Bench.Postition(1.0f, 0.0f, 0.0f);
	Bench.Scale(0.1f, 0.1f, 0.1f);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(10.0f, 0.0f, 0.0f);
	Bench.Scale(0.1f, 0.1f, 0.1f);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench.Render(graphics_handler);

	Scene.Scale(0.1f, 0.1f, 0.1f);
	Scene.Render(graphics_handler);
	//Scene.Render(graphics_handler);

}