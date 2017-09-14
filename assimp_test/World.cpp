#include <iostream>

#include "World.h"
#include "TextureMap.h"

//map<int, GameObject> World::BoundingWalls;
//vector<GameObject> World::BoundingWalls;
//GameObject World::BoundingWalls[2];

//GameObject World::cameraPlayer;
//GameObject World::BoundingWall;
//GameObject World::BoundingWall2;

World::~World(){
	if (graphics_handler){
		delete graphics_handler;
		graphics_handler = NULL;
	}
}

void World::InitializeGame(){

	Bench.Load(graphics_handler, "res/models/bench/bench1.obj");
	Bench2.Load(graphics_handler, "res/models/bench2/bench2.obj");


	chair1.Load(graphics_handler, "res/models/chair1/chair1.obj");
	chair2.Load(graphics_handler, "res/models/chair2/chair2.obj");

	table1.Load(graphics_handler, "res/models/table1/table1.obj");

	Scene.Load(graphics_handler, "res/models/scene/scense.obj");


	SetBoundingWall();

	cameraPlayer.Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
	cameraPlayer.SetBoundingBox(0.1f, 0.1f, 0.1f);
	

	CurrentX = 0;
	CurrentZ = 0;

	//texture2d.SetTextureCount(1);
	//texture2d.LoadRawTexture2D( "", 860, 640, CREDIT_TEXTURE);
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
	
cout << camera->GetPosition().x << endl << camera->GetPosition().z << endl << endl;

	//Render Model


	DrawBench1();
	DrawBench2();
	DrawChair1();
	DrawChair2();
	DrawTable1();


	cameraPlayer.Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

	Scene.Scale(0.1f, 0.1f, 0.1f);
	Scene.Render(graphics_handler);
	//Scene.Render(graphics_handler);
	CheckBoundingBox();

	CurrentX = camera->GetPosition().x;
	CurrentZ = camera->GetPosition().z;
}

void World::DrawBench1()
{
	float scale = 0.06f;
	float height = -0.1f;
	//on grass
	Bench.Postition(10.0f, height, -8.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(10.0f, height, -3.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(10.0f, height, 2.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench.Render(graphics_handler);

	//outside of room
	Bench.Postition(2.0f, height, 2.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(0.0f, height, 2.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(-2.0f, height, 2.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(4.0f, height, -3.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(0.0f, height, -3.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(-4.0f, height, -3.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench.Render(graphics_handler);

	Bench.Postition(-8.0f, height, -3.0f);
	Bench.Scale(scale, scale, scale);
	Bench.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench.Render(graphics_handler);
}

void World::DrawBench2()
{
	float scale = 0.038f;
	float height = 0.75f;

	Bench2.Postition(-9.0f, height, -6.3f);
	Bench2.Scale(scale, scale, scale);
	Bench2.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2.Render(graphics_handler);

	Bench2.Postition(-15.0f, height, -6.3f);
	Bench2.Scale(scale, scale, scale);
	Bench2.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2.Render(graphics_handler);

	Bench2.Postition(-21.0f, height, -6.3f);
	Bench2.Scale(scale, scale, scale);
	Bench2.Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2.Render(graphics_handler);

}

void World::DrawChair1()
{
	float scale = 0.033f;
	float height = 0.1f;

	chair1.Postition(-18.0f, height,-1.6f);
	chair1.Scale(scale, scale, scale);
	chair1.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	chair1.Render(graphics_handler);

	chair1.Postition(-17.0f, height, -2.6f);
	chair1.Scale(scale, scale, scale);
	chair1.Rotate(0.0f, 1.0f, 0.0f, 75.0f);
	chair1.Render(graphics_handler);
}

void World::DrawChair2()
{
	float scale = 0.035f;
	float height = 0.2f;

	chair2.Postition(-9.0f, height, -5.5f);
	chair2.Scale(scale, scale, scale);
	chair2.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	chair2.Render(graphics_handler);

	chair2.Postition(-15.0f, height, -5.5f);
	chair2.Scale(scale, scale, scale);
	chair2.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	chair2.Render(graphics_handler);

	chair2.Postition(-14.0f, height, -5.5f);
	chair2.Scale(scale, scale, scale);
	chair2.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	chair2.Render(graphics_handler);

	chair2.Postition(-21.0f, height, -5.5f);
	chair2.Scale(scale, scale, scale);
	chair2.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	chair2.Render(graphics_handler);
}

void World::DrawTable1()
{
	float scale = 0.05f;
	float height = 0.2f;

	table1.Postition(-18.0f, height, -2.6f);
	table1.Scale(scale, scale, scale);
	table1.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	table1.Render(graphics_handler);

	table1.Postition(-21.0f, height, -1.0f);
	table1.Scale(scale, scale, scale);
	table1.Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	table1.Render(graphics_handler);
}


void World::SetBoundingWall()
{
	
	//brick walls
	BoundingWall = new GameObject();
	BoundingWall->Postition(13.0f, 1.0f, -2.0f);
	BoundingWall->SetBoundingBox(1.0f, 1.0f, 30.0f);
	BoundingWalls[1] = *BoundingWall;

	BoundingWall = new GameObject();
	BoundingWall->Postition(8.0f, 1.0f, -15.0f);
	BoundingWall->SetBoundingBox(15.0f, 1.0f, 0.5f);
	BoundingWalls[2] = *BoundingWall;

	BoundingWall = new GameObject();
	BoundingWall->Postition(0.0f, 1.0f, -11.0f);
	BoundingWall->SetBoundingBox(1.5f, 1.0f, 9.5f);
	BoundingWalls[3] = *BoundingWall;

	//off-white color wall
	BoundingWall = new GameObject();
	BoundingWall->Postition(-6.0f, 1.0f, 6.5f);
	BoundingWall->SetBoundingBox(50.0f, 1.0f, 0.5f);
	BoundingWalls[4] = *BoundingWall;

	//iron fence wall
	BoundingWall = new GameObject();
	BoundingWall->Postition(-16.0f, 1.0f, -6.8f);
	BoundingWall->SetBoundingBox(32.0f, 1.0f, 0.5f);
	BoundingWalls[5] = *BoundingWall;

	BoundingWall = new GameObject();
	BoundingWall->Postition(-29.0f, 1.0f, 0.0f);
	BoundingWall->SetBoundingBox(0.5f, 1.0f, 20.0f);
	BoundingWalls[6] = *BoundingWall;

	//room wall
	BoundingWall = new GameObject();
	BoundingWall->Postition(-20.0f, 1.0f, -4.0f);
	BoundingWall->SetBoundingBox(10.0f, 1.0f, 0.5f);
	BoundingWalls[7] = *BoundingWall;

	BoundingWall = new GameObject();
	BoundingWall->Postition(-27.5f, 1.0f, -2.0f);
	BoundingWall->SetBoundingBox(0.5f, 1.0f, 4.0f);
	BoundingWalls[8] = *BoundingWall;

	BoundingWall = new GameObject();
	BoundingWall->Postition(-23.0f, 1.0f, 0.5f);
	BoundingWall->SetBoundingBox(14.0f, 1.0f, 1.0f);
	BoundingWalls[9] = *BoundingWall;

	BoundingWall = new GameObject();
	BoundingWall->Postition(-15.0f, 1.0f, 2.5f);
	BoundingWall->SetBoundingBox(0.5f, 1.0f, 7.6f);
	BoundingWalls[10] = *BoundingWall;

}


void World::CheckBoundingBox()
{
	//set camera bounding box


	//cout << BoundingWall2.GetPostitionX() << endl;
	for (int i = 0; i < 10; i++)
	{
		//BoundingWalls[i + 1].DrawBoundingBox();

		if (BoundingWalls[i+1].processCollision(cameraPlayer))
		{
			camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
			//cout << "CCCC" << endl;
		}
	}

	


}

