#include <iostream>

#include "World.h"


World::~World(){
	if (graphics_handler){
		delete graphics_handler;
		graphics_handler = NULL;
	}
}

void World::InitializeGame(){

	//Initial Models
	InitialBench1();
	InitialBench2();
	InitialChair1();
	InitialChair2();
	InitialTable1();
	InitialScene();

	Initial2DTexture();

	//Initial wall collision detection
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
	if (*game_status != GAME_PLAYING){
		if (*game_status == GAME_DONE){
			GameDestruction();
			exit(0);
		}

		if (*game_status == GAME_MAIN_MENU){
			// ui.mainMenu(512, 512, 0, 0); //texture2d.Display2DTexture(512, 512, 0, 0, GAME_MAIN_MENU_TEXTURE);
		}

		if (*game_status == GAME_HELP_MENU){
			//texture2d.Display2DTexture(512, 512, 0, 0, GAME_HELP_MENU_TEXTURE);
		}

		if (*game_status == GAME_CREDIT_PAGE){
			//texture2d.Display2DTexture(512, 512, 0, 0, CREDIT_TEXTURE);.
			graphics_handler->Render2DTexture("res/2d_imgs/Credit.jpg");
		}

	}

	//Render Models
	DrawBench1();
	DrawBench2();
	DrawChair1();
	DrawChair2();
	DrawTable1();
	DrawScene();

	cameraPlayer.Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

	CheckBoundingBox();

	CurrentX = camera->GetPosition().x;
	CurrentZ = camera->GetPosition().z;
}

void World::InitialScene()
{
	Scene.Load(graphics_handler, "res/models/scene/scense.obj");
	Scene.Scale(0.1f, 0.1f, 0.1f);
}

void World::InitialBench1()
{
	float scale = 0.06f;
	float height = -0.1f;
	string fileName = "res/models/bench/bench1.obj";
	//on grass

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(10.0f, height, -8.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[1] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(10.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[2] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(10.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[3] = *Bench1;

	
	//outside of room
	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(2.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[4] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(0.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[5] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(-2.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[6] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(4.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1s[7] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(0.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1s[8] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(-4.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1s[9] = *Bench1;

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(-8.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1s[10] = *Bench1;
	
}

void World::InitialBench2()
{
	float scale = 0.038f;
	float height = 0.75f;
	string fileName = "res/models/bench2/bench2.obj";

	Bench2 = new GameObject();
	Bench2->Load(graphics_handler, fileName);
	Bench2->Postition(-9.0f, height, -6.3f);
	Bench2->Scale(scale, scale, scale);
	Bench2->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2s[1] = *Bench2;

	Bench2 = new GameObject();
	Bench2->Load(graphics_handler, fileName);
	Bench2->Postition(-15.0f, height, -6.3f);
	Bench2->Scale(scale, scale, scale);
	Bench2->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2s[2] = *Bench2;

	Bench2 = new GameObject();
	Bench2->Load(graphics_handler, fileName);
	Bench2->Postition(-21.0f, height, -6.3f);
	Bench2->Scale(scale, scale, scale);
	Bench2->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2s[3] = *Bench2;
}

void World::InitialChair1()
{
	float scale = 0.033f;
	float height = 0.1f;
	string fileName = "res/models/chair1/chair1.obj";

	Chair1 = new GameObject();
	Chair1->Load(graphics_handler, fileName);
	Chair1->Postition(-18.0f, height, -1.6f);
	Chair1->Scale(scale, scale, scale);
	Chair1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair1s[1] = *Chair1;

	Chair1 = new GameObject();
	Chair1->Load(graphics_handler, fileName);
	Chair1->Postition(-17.0f, height, -2.6f);
	Chair1->Scale(scale, scale, scale);
	Chair1->Rotate(0.0f, 1.0f, 0.0f, 75.0f);
	Chair1s[2] = *Chair1;
}

void World::InitialChair2()
{
	float scale = 0.035f;
	float height = 0.2f;
	string fileName = "res/models/chair2/chair2.obj";

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-9.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2s[1] = *Chair2;

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-15.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2s[2] = *Chair2;

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-14.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2s[3] = *Chair2;

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-21.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2s[4] = *Chair2;
}

void World::InitialTable1()
{
	float scale = 0.05f;
	float height = 0.2f;
	string fileName = "res/models/table1/table1.obj";

	Table1 = new GameObject();
	Table1->Load(graphics_handler, fileName);
	Table1->Postition(-18.0f, height, -2.6f);
	Table1->Scale(scale, scale, scale);
	Table1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Table1s[1] = *Table1;

	Table1 = new GameObject();
	Table1->Load(graphics_handler, fileName);
	Table1->Postition(-21.0f, height, -1.0f);
	Table1->Scale(scale, scale, scale);
	Table1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Table1s[2] = *Table1;
}

void World::Initial2DTexture(){
	graphics_handler->Load2DTexture("res/2d_imgs/Credit.jpg");
}


void World::DrawScene()
{
	Scene.Render(graphics_handler);
}

void World::DrawBench1()
{
	for (int i = 0; i < Bench1s.size(); i++)
	{
		Bench1s[i + 1].Render(graphics_handler);
	}
}

void World::DrawBench2()
{
	for (int i = 0; i < Bench2s.size(); i++)
	{
		Bench2s[i + 1].Render(graphics_handler);
	}
}

void World::DrawChair1()
{
	for (int i = 0; i < Chair1s.size(); i++)
	{
		Chair1s[i + 1].Render(graphics_handler);
	}
}

void World::DrawChair2()
{
	for (int i = 0; i < Chair2s.size(); i++)
	{
		Chair2s[i + 1].Render(graphics_handler);
	}
}

void World::DrawTable1()
{
	for (int i = 0; i < Table1s.size(); i++)
	{
		Table1s[i + 1].Render(graphics_handler);
	}
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
	//check wall bounding box
	for (int i = 0; i < BoundingWalls.size(); i++)
	{
		if (BoundingWalls[i+1].processCollision(cameraPlayer))
		{
			camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
		}
	}

	//check bench1 bounding box
	for (int i = 0; i < Bench1s.size(); i++)
	{
		if (Bench1s[i + 1].processCollision(cameraPlayer))
		{
			camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
		}
	}


}

