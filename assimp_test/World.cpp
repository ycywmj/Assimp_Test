#include "World.h"

#include "Bullet_GLM.h"

#include <iostream>

void World::GameDestruction(){
	if (game_status){
		delete game_status;
		game_status = NULL;
	}

	if (camera){
		delete camera;
		camera = NULL;
	}

	// bullet physics
	if (!bt_collision_configuration){
		delete bt_collision_configuration;
	};
	if (!bt_dispatcher){
		delete bt_dispatcher;
	};
	if (!bt_broadphase){
		delete bt_broadphase;
	};
	if (!bt_collision_world){
		delete bt_collision_world;
	};

	// after all destruction, close the window and delete graphics handler
	graphics_handler->RequestCloseWindow();

	if (graphics_handler){
		delete graphics_handler;
		graphics_handler = NULL;
	}
}

void World::InitializeGame(){

	InitialPlayer();
	InitialWorldObjects();
	//Initial wall collision detection
	//SetBoundingWall();
	
	camera->SetPostion(2.0f, 1.25f, 3.0f);


	CurrentX = 0;
	CurrentZ = 0;

	glm::vec3 Pos;
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
	delta_time = graphics_handler->GetDeltaTime();
	game_total_time += delta_time;

	DrawWorldObjects();
	DrawPlayer();
	
	PlayerActions();

	//graphics_handler->drawBox();

	//CheckBoundingBox();

	//update positions
	//UpdateObjects();
	//Render Models

	//DrawBench1();
	//DrawBench2();
	//DrawChair1();
	//DrawChair2();
	//DrawTable1();
	//DrawScene();
	//graphics_handler->drawBox();


	CheckBulletCollision();

	//CheckBoundingBox();

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
	
	CurrentX = camera->GetPosition().x;
	CurrentZ = camera->GetPosition().z;
}

//void World::UpdateObjects()
//{
//	//for (int i = 0; i < WorldObjects.size(); i++)
//	//{
//	//	//check to see if it is a scene object
//	//	if (!WorldObjects[i].GetSceneObject())
//	//	{
//	//		WorldObjects[i].UpdateObject(graphics_handler->GetDeltaTime());
//	//		
//	//	}
//	//}
//}


void World::InitialWorldObjects()
{
	Initial2DTexture();

	//Initial Models
	InitialBench1();
	InitialBench2();
	InitialChair2();
	InitialChair1();
	
	InitialTable1();
	InitialScene();
	InitialNPCs();
	//InitialPlayer();

}

void World::DrawWorldObjects()
{
	/*for (int i = 0; i < WorldObjects.size(); i++)
	{
	WorldObjects[i].Render(graphics_handler);
	}*/

	DrawBench1();
	DrawBench2();
	//DrawChair1();
	//DrawChair2();
	DrawTable1();
	DrawScene();
	DrawNPCs();
	DrawAffordanceObject();
	//DrawPlayer();
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
	Bench1s[1] = Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(10.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[2] = Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(10.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[3] = Bench1;
	//WorldObjects.push_back(*Bench1);

	
	//outside of room
	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(2.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[4] = Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(0.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[5] = Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(-2.0f, height, 2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	Bench1s[6] = Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	OObtCollisionObject* new_col_obj = Bench1->SetBulletBoundingBox(1.0f, 2.0f, 1.5f);
	Bench1->Postition(4.0f, height, -2.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1->SetMass(20.0f);
	if (new_col_obj){
		new_col_obj->SetAttachObject(Bench1);
		bt_collision_world->addCollisionObject(new_col_obj);
	}
	glm::vec3 vel = { -.0f, .0f, .0f };
	Bench1->SetVel(vel);
	Bench1s[7] = Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	new_col_obj = Bench1->SetBulletBoundingBox(1.0f, 2.0f, 1.5f);
	Bench1->Postition(0.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1->SetMass(20.0f);
	if (new_col_obj){
		new_col_obj->SetAttachObject(Bench1);
		bt_collision_world->addCollisionObject(new_col_obj);
	}
	vel = {.0f, .0f, .0f };
	Bench1->SetVel(vel);
	Bench1s[8] = Bench1;
	//WorldObjects.push_back(*Bench1);

	/*Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(-4.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1s[9] = *Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	Bench1->Postition(-8.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	Bench1s[10] = *Bench1;
	//WorldObjects.push_back(*Bench1);*/
	
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
	//WorldObjects.push_back(*Bench2);

	Bench2 = new GameObject();
	Bench2->Load(graphics_handler, fileName);
	Bench2->Postition(-15.0f, height, -6.3f);
	Bench2->Scale(scale, scale, scale);
	Bench2->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2s[2] = *Bench2;
	//WorldObjects.push_back(*Bench2);

	Bench2 = new GameObject();
	Bench2->Load(graphics_handler, fileName);
	Bench2->Postition(-21.0f, height, -6.3f);
	Bench2->Scale(scale, scale, scale);
	Bench2->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	Bench2s[3] = *Bench2;
	//WorldObjects.push_back(*Bench2);
}

void World::InitialChair1()
{
	float scale = 0.033f;
	float height = 0.1f;
	string fileName = "res/models/chair1/chair1.obj";
	

	//Initial 1st chair1
	string affordance1 = "liftable";
	string affordance2 = "movable";
	string affordance3 = "kickable";
	
	vector < string > affordances1;
	affordances1.push_back(affordance1);
	affordances1.push_back(affordance2);
	affordances1.push_back(affordance3);

	Chair1 = new GameObject();
	Chair1->Load(graphics_handler, fileName);
	Chair1->Postition(-18.0f, height, -1.6f);
	Chair1->Scale(scale, scale, scale);
	Chair1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair1->SetBoundingBox(1.0f, 10.0f, 1.0f);
	Chair1->setAffordance(affordances1);
	Chair1s[1] = *Chair1;
	//WorldObjects.push_back(*Chair1);
	AffordanceObjects.push_back(Chair1);

	//Initial 2st chair1

	Chair1 = new GameObject();
	Chair1->Load(graphics_handler, fileName);
	Chair1->Postition(-17.0f, height, -2.6f);
	Chair1->Scale(scale, scale, scale);
	Chair1->SetBoundingBox(1.0f, 10.0f, 1.0f);
	Chair1->Rotate(0.0f, 1.0f, 0.0f, 75.0f);
	Chair1->setAffordance(affordances1);
	Chair1s[2] = *Chair1;
//	WorldObjects.push_back(*Chair1);
	AffordanceObjects.push_back(Chair1);
}

void World::InitialChair2()
{
	float scale = 0.035f;
	float height = 0.2f;
	string fileName = "res/models/chair2/chair2.obj";


	string affordance4 = "standable";
	string affordance5 = "kickable";


	//initial 1st chair2
	vector < string > affordances2;
	affordances2.push_back(affordance4);
	affordances2.push_back(affordance5);

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-9.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2->SetBoundingBox(1.0f, 10.0f, 1.0f);
	Chair2->setAffordance(affordances2);
	Chair2s[1] = *Chair2;
	AffordanceObjects.push_back(Chair2);
	//WorldObjects.push_back(*Chair2);


	//initial 2st chair2
	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-15.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2->SetBoundingBox(1.0f, 10.0f, 1.0f);
	Chair2->setAffordance(affordances2);
	Chair2s[2] = *Chair2;
	AffordanceObjects.push_back(Chair2);
	//WorldObjects.push_back(*Chair2);


	//initial 3st chair2
	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-14.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2->SetBoundingBox(1.0f, 10.0f, 1.0f);
	Chair2->setAffordance(affordances2);
	Chair2s[3] = *Chair2;
	AffordanceObjects.push_back(Chair2);
	//WorldObjects.push_back(*Chair2);


	//initial 4st chair2
	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-21.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2->SetBoundingBox(1.0f, 10.0f, 1.0f);
	Chair2->setAffordance(affordances2);
	Chair2s[4] = *Chair2;
	AffordanceObjects.push_back(Chair2);
	//WorldObjects.push_back(*Chair2);
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
	//WorldObjects.push_back(*Table1);

	Table1 = new GameObject();
	Table1->Load(graphics_handler, fileName);
	Table1->Postition(-21.0f, height, -1.0f);
	Table1->Scale(scale, scale, scale);
	Table1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Table1s[2] = *Table1;
	//WorldObjects.push_back(*Table1);
}

void World::Initial2DTexture(){
	graphics_handler->Load2DTexture("res/2d_imgs/Credit.jpg");
}

void World::InitialNPCs()
{
	float scale = 0.05f;
	float TextScale = 1.0f;


	//initial text models
	string text1 = "res/models/text/t1.obj";
	string text2 = "res/models/text/t2.obj";
	string text3 = "res/models/text/t3.obj";

	map<string, string> Texts;
	Texts["text1"] = text1;
	Texts["text2"] = text2;
	Texts["text3"] = text3;
	TextDialog = new GameObject();
	TextDialog->Scale(scale, -scale, scale);
	TextDialog->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	TextDialog->LoadAll(graphics_handler, Texts);

	//npc1 (green one)
	//initial different npc faces
	string fileName1 = "res/models/n1/n1_n.obj";
	string fileName2 = "res/models/n1/n1_h.obj";
	string fileName3 = "res/models/n1/n1_s.obj";
	string fileName4 = "res/models/n1/n1_a.obj";

	map<string, string> N1Files;
	N1Files["normal"] = fileName1;
	N1Files["happy"] = fileName2;
	N1Files["sad"] = fileName3;
	N1Files["angry"] = fileName4;

	vector<glm::vec2> *N1Path;
	N1Path = new vector< glm::vec2 >;
	glm::vec2 NewPath1(10.0f, -8.0f);
	glm::vec2 NewPath2(5.0f, -8.0f);
	glm::vec2 NewPath3(1.0f, 0.0f);
	N1Path->push_back(NewPath1);
	N1Path->push_back(NewPath2);
	N1Path->push_back(NewPath3);

	Agent = new NPCs();
	Agent->SetTexts(TextDialog);
	Agent->LoadAll(graphics_handler, N1Files);
	Agent->UpdateModel("normal");
	Agent->SetMoveSpeed(0.5f);
	Agent->Postition(10.0f, 0.0f, -8.0f);
	Agent->Scale(scale, scale, scale);
	Agent->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Agent->SetBoundingBox(4.0f, 4.0f, 4.0f);
	Agent->SetDetectView(6.0f, 6.0f, 6.0f);
	Agent->InitialState();
	Agent->setPath(*N1Path);
	//Agent->setEmotions(1.0f, 0.0f);
	Agent->setMoods(0.3f, 0.0f);
	Agent->setTraits(0.2f, 0.0f);
	Agent->setPersonalities(0.4f, 0.0f);
	Agents[1] = Agent;


	//npc2 (yellow one)
	fileName1 = "res/models/n2/n1_n.obj";
	fileName2 = "res/models/n2/n1_h.obj";
	fileName3 = "res/models/n2/n1_s.obj";
	fileName4 = "res/models/n2/n1_a.obj";

	map<string, string> N2Files;
	N2Files["normal"] = fileName1;
	N2Files["happy"] = fileName2;
	N2Files["sad"] = fileName3;
	N2Files["angry"] = fileName4;

	vector<glm::vec2> *N2Path;
	N2Path = new vector< glm::vec2 >;
	glm::vec2 N2Path1(10.0f, -8.0f);
	glm::vec2 N2Path2(20.0f, -0.0f);
	glm::vec2 N2Path3(-1.0f, 5.0f);
	N2Path->push_back(N2Path1);
	N2Path->push_back(N2Path2);
	N2Path->push_back(N2Path3);

	Agent = new NPCs();
	Agent->SetTexts(TextDialog);
	Agent->LoadAll(graphics_handler, N2Files);
	Agent->UpdateModel("normal");
	Agent->SetMoveSpeed(0.5f);
	Agent->Postition(10.0f, 0.0f, -8.0f);
	Agent->Scale(scale, scale, scale);
	Agent->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Agent->SetBoundingBox(4.0f, 4.0f, 4.0f);
	Agent->SetDetectView(6.0f, 6.0f, 6.0f);
	Agent->InitialState();
	Agent->setPath(*N2Path);
	//Agent->setEmotions(1.0f, 0.0f);
	Agent->setMoods(0.3f, 0.0f);
	Agent->setTraits(0.2f, 0.0f);
	Agent->setPersonalities(0.4f, 0.0f);
	Agents[2] = Agent;


	//npc3 (pink one)
	fileName1 = "res/models/n3/n1_n.obj";
	fileName2 = "res/models/n3/n1_h.obj";
	fileName3 = "res/models/n3/n1_s.obj";
	fileName4 = "res/models/n3/n1_a.obj";

	map<string, string> N3Files;
	N3Files["normal"] = fileName1;
	N3Files["happy"] = fileName2;
	N3Files["sad"] = fileName3;
	N3Files["angry"] = fileName4;

	vector<glm::vec2> *N3Path;
	N3Path = new vector< glm::vec2 >;
	glm::vec2 N3Path1(-13.0f, -1.0f);
	glm::vec2 N3Path2(-7.0f, 4.0f);
	glm::vec2 N3Path3(-6.0f, -4.0f);
	N3Path->push_back(N3Path1);
	N3Path->push_back(N3Path2);
	N3Path->push_back(N3Path3);

	Agent = new NPCs();
	Agent->SetTexts(TextDialog);
	Agent->LoadAll(graphics_handler, N3Files);
	Agent->UpdateModel("normal");
	Agent->SetMoveSpeed(0.8f);
	Agent->Postition(10.0f, 0.0f, -8.0f);
	Agent->Scale(scale, scale, scale);
	Agent->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Agent->SetBoundingBox(4.0f, 4.0f, 4.0f);
	Agent->SetDetectView(6.0f, 6.0f, 6.0f);
	Agent->InitialState();
	Agent->setPath(*N3Path);
	//Agent->setEmotions(1.0f, 0.0f);
	Agent->setMoods(-0.3f, 0.0f);
	Agent->setTraits(0.1f, 0.0f);
	Agent->setPersonalities(0.0f, 0.0f);
	Agents[3] = Agent;
}



void World::DrawNPCs()
{

	for (int i = 1; i <= Agents.size(); i++)
	{
		Agents[i]->UpdateState(cameraPlayer, Agents, AffordanceObjects);
		Agents[i]->Render(graphics_handler);
		Agents[i]->GetTexts()->Render(graphics_handler);
	}
}

void World::DrawAffordanceObject()
{
	for (int i = 0; i < AffordanceObjects.size(); i++)
	{
		AffordanceObjects[i]->Render(graphics_handler);
	}
}

void World::InitialPlayer()
{
	cameraPlayer = new Player();
	cameraPlayer->Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
	cameraPlayer->SetBoundingBox(0.1f, 0.1f, 0.1f);
	OObtCollisionObject* new_col_obj = cameraPlayer->SetBulletBoundingBox(0.05f, 0.05f, 0.05f);
	if (new_col_obj){
		new_col_obj->SetAttachObject(cameraPlayer);
		bt_collision_world->addCollisionObject(new_col_obj);
	}
}

void World::DrawPlayer()
{

	cameraPlayer->Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

}

void World::DrawScene()
{
	Scene.Render(graphics_handler);
}

void World::DrawBench1()
{
	//cout << "y pos: " << WorldObjects[7].GetPosition().y << endl;
	for (int i = 0; i < Bench1s.size(); i++)
	{
		
			//cout <<"increment" << Bench1s[i + 1].GetPosition().y << endl;
		Bench1s[i + 1]->Render(graphics_handler);
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
	BoundingWall->SetSceneObject(true);
	BoundingWalls[1] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	BoundingWall = new GameObject();
	BoundingWall->Postition(8.0f, 1.0f, -15.0f);
	BoundingWall->SetBoundingBox(15.0f, 1.0f, 0.5f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[2] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	BoundingWall = new GameObject();
	BoundingWall->Postition(0.0f, 1.0f, -11.0f);
	BoundingWall->SetBoundingBox(1.5f, 1.0f, 9.5f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[3] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	//off-white color wall
	BoundingWall = new GameObject();
	BoundingWall->Postition(-6.0f, 1.0f, 6.5f);
	BoundingWall->SetBoundingBox(50.0f, 1.0f, 0.5f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[4] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	//iron fence wall
	BoundingWall = new GameObject();
	BoundingWall->Postition(-16.0f, 1.0f, -6.8f);
	BoundingWall->SetBoundingBox(32.0f, 1.0f, 0.5f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[5] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	BoundingWall = new GameObject();
	BoundingWall->Postition(-29.0f, 1.0f, 0.0f);
	BoundingWall->SetBoundingBox(0.5f, 1.0f, 20.0f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[6] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	//room wall
	BoundingWall = new GameObject();
	BoundingWall->Postition(-20.0f, 1.0f, -4.0f);
	BoundingWall->SetBoundingBox(10.0f, 1.0f, 0.5f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[7] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	BoundingWall = new GameObject();
	BoundingWall->Postition(-27.5f, 1.0f, -2.0f);
	BoundingWall->SetBoundingBox(0.5f, 1.0f, 4.0f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[8] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	BoundingWall = new GameObject();
	BoundingWall->Postition(-23.0f, 1.0f, 0.5f);
	BoundingWall->SetBoundingBox(14.0f, 1.0f, 1.0f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[9] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

	BoundingWall = new GameObject();
	BoundingWall->Postition(-15.0f, 1.0f, 2.5f);
	BoundingWall->SetBoundingBox(0.5f, 1.0f, 7.6f);
	BoundingWall->SetSceneObject(true);
	BoundingWalls[10] = *BoundingWall;
	WorldObjects.push_back(*BoundingWall);

}

//
//void World::CheckBoundingBox()
//{
//	glm::vec3 collisionPoint;
//	//check wall bounding box
//
//	for (int i = 0; i < WorldObjects.size(); i++)
//	{
//		if (WorldObjects[i].processCollision(cameraPlayer, &collisionPoint))
//		{
//			camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
//			//cout << "collision with object:"<< i << endl;
//		}
//	}
//
//	for (int i = 0; i < WorldObjects.size(); i++)
//	{
//		for (int j=i; j < WorldObjects.size(); j++)
//		{
//			if (i != j)
//			{
//				if (WorldObjects[i].processCollision(WorldObjects[j], &collisionPoint))
//				{
//					Physics::ObjectCollision(&WorldObjects[i], &WorldObjects[j], collisionPoint);
//					cout << "something is colliding" << endl;
//					cout << "collision point" << collisionPoint.x << endl;
//					//cout << "i value:" << i << endl;
//					//cout << "j value: " << j << endl;
//				}
//			}
//		}
//	}
//
//}

void World::CheckBulletCollision(){
	//Perform collision detection
	bt_collision_world->performDiscreteCollisionDetection();

	int numManifolds = bt_collision_world->getDispatcher()->getNumManifolds();
	//std::cout << "numManifolds: " << numManifolds << std::endl;

	//For each contact manifold
	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold* contactManifold = bt_collision_world->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();
		GameObject* objA = ((OObtCollisionObject*)obA)->GetAttachObject();
		GameObject* objB = ((OObtCollisionObject*)obB)->GetAttachObject();
		
		contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
		int numContacts = contactManifold->getNumContacts();
		// player cant move when it is colliding with something
		// as well as wont apply physics
		if (objA == cameraPlayer || objB == cameraPlayer)
			camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
		else{
			btVector3 center_pt(.0f, .0f, .0f);
			btVector3 normalvec(.0f, .0f, .0f);
			double temp = 0.0;
			//For each contact point in that manifold
			for (int j = 0; j < numContacts; j++) {
				//Get the contact information
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				btVector3 ptA = pt.getPositionWorldOnA();
				btVector3 ptB = pt.getPositionWorldOnB();
				double ptdist = pt.getDistance();
				temp = ptdist; // use for outside for loop

				center_pt += ptA; // add up center pt for getting average center pt
				normalvec = pt.m_normalWorldOnB; // get normal vector for physics
			}
			center_pt /= (btScalar)numContacts; // center point = sum of pos pt / number of pts
			if (temp < 0.0 && !objA->GetIsCollided() && !objB->GetIsCollided()){
				// apply physics
				Physics::ObjectCollision(objA, objB, Bullet_GLM::BulletVec3ToGlmVec3(center_pt),
					Bullet_GLM::BulletVec3ToGlmVec3(normalvec));
				// collision delay - not collide many times at once
				objA->SetIsCollided(true);
				objB->SetIsCollided(true);
				std::cout << temp << std::endl;
			}
		}

		

	}
}

void World::StartMovingTable(){
	glm::vec3 vel = { -.5f, .0f, -.0f };
	Bench1s[7]->SetVel(vel);
	Bench1s[7]->SetAngVel(glm::vec3(.0f, 0.0f, .0f));

	vel = { .5f, .0f, -.0f };
	Bench1s[8]->SetVel(vel);
	Bench1s[8]->SetAngVel(glm::vec3(.0f, 0.0f, .0f));
}

void World::PlayerActions()
{
	float height = 0.0f;

	bool* keyPressed = graphics_handler->getPressedKey();

	if (keyPressed[70])
	{
		cameraPlayer->setActions(1);
	}

	if (keyPressed[71])
	{
		cameraPlayer->setActions(2);
	}

	if (keyPressed[67])
	{
		for (int i = 0; i < AffordanceObjects.size(); i++)
		{
			//cout << AffordanceObjects[i]->GetPosition().x << endl;
			//cout << cameraPlayer->GetPosition().x << endl;

			if (AffordanceObjects[i]->processCollision(cameraPlayer))
			{
				cameraPlayer->setIsLifting(true);
				cameraPlayer->SetObjectToLift(i);
				cout << "Collider!!!!" << endl;
			}

		}
	}

	
	if (cameraPlayer->isPlayerLifting())
	{
		//cout << cameraPlayer->GetObjectToLift() << endl;

		height = AffordanceObjects[cameraPlayer->GetObjectToLift()]->GetPosition().y;
		AffordanceObjects[cameraPlayer->GetObjectToLift()]->Postition(camera->GetRightFront().x, 0.4, camera->GetRightFront().z);
	}

	if ((keyPressed[86]) && (cameraPlayer->isPlayerLifting()))
	{
		height = AffordanceObjects[cameraPlayer->GetObjectToLift()]->GetPosition().y;
		AffordanceObjects[cameraPlayer->GetObjectToLift()]->Postition(camera->GetRightFront().x, 0.1, camera->GetRightFront().z);
		cameraPlayer->setIsLifting(false);
		cameraPlayer->SetObjectToLift(-1);
	}
	
}