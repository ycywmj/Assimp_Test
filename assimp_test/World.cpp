#include <iostream>

#include "World.h"

//vector<GameObject> World::BoundingWalls;
//GameObject World::BoundingWalls[2];


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

	//SetBoundingWall();
	cameraPlayer.SetBoundingBox(0.1, 0.1, 0.1);

	CurrentX = 0;
	CurrentZ = 0;
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
	
	cout << camera->GetPosition().x << camera->GetPosition().z << endl << endl;

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
	//CheckBoundingBox();

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
	
	cameraPlayer.SetBoundingBox(0.1, 0.1, 0.1);

	//Creat Bounding box wall
	GameObject BoundingWall;
	BoundingWall.Postition(13, 1, -2);
	BoundingWall.SetBoundingBox(0.5, 1, 20);
	BoundingWalls[0] = BoundingWall;

	GameObject BoundingWall2;
	BoundingWall2.Postition(8, 1, -15);
	BoundingWall2.SetBoundingBox(10, 1, 0.5);
	BoundingWalls[1] = BoundingWall;
}
void World::CheckBoundingBox()
{
	//set camera bounding box
	
	//Creat Bounding box wall
	GameObject BoundingWall;
	BoundingWall.Postition(13, 1, -2);
	BoundingWall.SetBoundingBox(0.5, 1, 20);
	BoundingWalls[0] = BoundingWall;
	cout << BoundingWall.GetPostitionX() << endl;

	GameObject BoundingWall2;
	BoundingWall2.Postition(8, 1, -15);
	BoundingWall2.SetBoundingBox(10, 1, 0.5);
	BoundingWalls[1] = BoundingWall2;
	cout << BoundingWall2.GetPostitionX() << endl;

	//cout << BoundingWall2.GetPostitionX() << endl;
	/*for (int i = 0; i < 1; i++)
	{
		if (BoundingWalls[i].processCollision(cameraPlayer))
		{
			//camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
			cout << "CCCC" << endl;
		}
	}*/

	if (BoundingWall.processCollision(cameraPlayer))
	{
		//camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
		cout << "CCCC" << endl;
	}
	if (BoundingWall2.processCollision(cameraPlayer))
	{
		//camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
		cout << "CCCC" << endl;
	}


}

