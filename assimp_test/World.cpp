#include "World.h"

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

	InitialWorldObjects();
	//Initial wall collision detection
	//SetBoundingWall();
	
	camera->SetPostion(2.0f, 1.25f, 3.0f);
	cameraPlayer.Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
	cameraPlayer.SetBoundingBox(0.1f, 0.1f, 0.1f);
	btCollisionObject* new_col_obj = cameraPlayer.SetBulletBoundingBox(0.05f, 0.05f, 0.05f);
	if (new_col_obj)
		bt_collision_world->addCollisionObject(new_col_obj);

	CurrentX = 0;
	CurrentZ = 0;

	glm::vec3 Pos;
	glm::vec3 BoxSize;
	//graphics_handler->loadBox(Pos,BoxSize);
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
	DrawWorldObjects();

	cameraPlayer.Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

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

	//CheckBulletCollision();



	//graphics_handler->Render2DTexture("res/2d_imgs/Credit.jpg");




	//cout << "Camera position:" << "X:" << camera->GetPosition().x << " Y:" << camera->GetPosition().y << " Z:" << camera->GetPosition().z << endl << endl;

	//cameraPlayer.Postition(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);

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

void World::UpdateObjects()
{
	for (int i = 0; i < WorldObjects.size(); i++)
	{
		//check to see if it is a scene object
		if (!WorldObjects[i].GetSceneObject())
		{
			WorldObjects[i].UpdateObject(graphics_handler->GetDeltaTime());
			
		}
	}
}


void World::InitialWorldObjects()
{
	Initial2DTexture();

	//Initial Models
	InitialBench1();
	InitialBench2();
	InitialChair1();
	InitialChair2();
	InitialTable1();
	InitialScene();
	InitialNPCs();

}

void World::DrawWorldObjects()
{
	/*for (int i = 0; i < WorldObjects.size(); i++)
	{
	WorldObjects[i].Render(graphics_handler);
	}*/

	DrawBench1();
	DrawBench2();
	DrawChair1();
	DrawChair2();
	DrawTable1();
	DrawScene();
	DrawNPCs();
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

	//Bench1 = new GameObject();
	//Bench1->Load(graphics_handler, fileName);
	//Bench1->Postition(10.0f, height, -8.0f);
	//Bench1->Scale(scale, scale, scale);
	//Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	//Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	//Bench1s[1] = *Bench1;
	////WorldObjects.push_back(*Bench1);

	//Bench1 = new GameObject();
	//Bench1->Load(graphics_handler, fileName);
	//Bench1->Postition(10.0f, height, -3.0f);
	//Bench1->Scale(scale, scale, scale);
	//Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	//Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	//Bench1s[2] = *Bench1;
	////WorldObjects.push_back(*Bench1);

	//Bench1 = new GameObject();
	//Bench1->Load(graphics_handler, fileName);
	//Bench1->Postition(10.0f, height, 2.0f);
	//Bench1->Scale(scale, scale, scale);
	//Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	//Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	//Bench1s[3] = *Bench1;
	////WorldObjects.push_back(*Bench1);

	//
	////outside of room
	//Bench1 = new GameObject();
	//Bench1->Load(graphics_handler, fileName);
	//Bench1->Postition(2.0f, height, 2.0f);
	//Bench1->Scale(scale, scale, scale);
	//Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	//Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	//Bench1s[4] = *Bench1;
	////WorldObjects.push_back(*Bench1);

	//Bench1 = new GameObject();
	//Bench1->Load(graphics_handler, fileName);
	//Bench1->Postition(0.0f, height, 2.0f);
	//Bench1->Scale(scale, scale, scale);
	//Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	//Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	//Bench1s[5] = *Bench1;
	////WorldObjects.push_back(*Bench1);

	//Bench1 = new GameObject();
	//Bench1->Load(graphics_handler, fileName);
	//Bench1->Postition(-2.0f, height, 2.0f);
	//Bench1->Scale(scale, scale, scale);
	//Bench1->Rotate(0.0f, 1.0f, 0.0f, 90.0f);
	//Bench1->SetBoundingBox(3.0f, 4.0f, 2.0f);
	//Bench1s[6] = *Bench1;
	////WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	btCollisionObject* new_col_obj = Bench1->SetBulletBoundingBox(1.0f, 2.0f, 1.5f);
	Bench1->Postition(4.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	if (new_col_obj)
		bt_collision_world->addCollisionObject(new_col_obj);
	glm::vec3 vel = { -.5f, .0f, .0f };
	Bench1->SetVel(vel);
	Bench1s[1] = *Bench1;
	//WorldObjects.push_back(*Bench1);

	Bench1 = new GameObject();
	Bench1->Load(graphics_handler, fileName);
	new_col_obj = Bench1->SetBulletBoundingBox(1.0f, 2.0f, 1.5f);
	Bench1->Postition(0.0f, height, -3.0f);
	Bench1->Scale(scale, scale, scale);
	Bench1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Bench1->SetBoundingBox(2.0f, 4.0f, 3.0f);
	if (new_col_obj)
		bt_collision_world->addCollisionObject(new_col_obj);
	vel = {.3f, .0f, .0f };
	Bench1->SetVel(vel);
	Bench1s[2] = *Bench1;
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

	Chair1 = new GameObject();
	Chair1->Load(graphics_handler, fileName);
	Chair1->Postition(-18.0f, height, -1.6f);
	Chair1->Scale(scale, scale, scale);
	Chair1->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair1s[1] = *Chair1;
	//WorldObjects.push_back(*Chair1);

	Chair1 = new GameObject();
	Chair1->Load(graphics_handler, fileName);
	Chair1->Postition(-17.0f, height, -2.6f);
	Chair1->Scale(scale, scale, scale);
	Chair1->Rotate(0.0f, 1.0f, 0.0f, 75.0f);
	Chair1s[2] = *Chair1;
//	WorldObjects.push_back(*Chair1);
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
	//WorldObjects.push_back(*Chair2);

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-15.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2s[2] = *Chair2;
	//WorldObjects.push_back(*Chair2);

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-14.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2s[3] = *Chair2;
	//WorldObjects.push_back(*Chair2);

	Chair2 = new GameObject();
	Chair2->Load(graphics_handler, fileName);
	Chair2->Postition(-21.0f, height, -5.5f);
	Chair2->Scale(scale, scale, scale);
	Chair2->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Chair2s[4] = *Chair2;
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
	string fileName = "res/models/c1/c1.obj";

	Agent = new NPCs();
	Agent->Load(graphics_handler, fileName);
	Agent->Postition(-18.0f, 0.2f, -2.6f);
	Agent->Scale(scale, scale, scale);
	Agent->Rotate(0.0f, 1.0f, 0.0f, 0.0f);
	Agents[1] = *Agent;
}

void World::DrawNPCs()
{
	Agents[1].Render(graphics_handler);
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

void World::CheckBoundingBox()
{
	glm::vec3 collisionPoint;
	//check wall bounding box

	for (int i = 0; i < WorldObjects.size(); i++)
	{
		if (WorldObjects[i].processCollision(cameraPlayer, &collisionPoint))
		{
			camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
			//cout << "collision with object:"<< i << endl;
		}
	}

	for (int i = 0; i < WorldObjects.size(); i++)
	{
		for (int j=i; j < WorldObjects.size(); j++)
		{
			if (i != j)
			{
				if (WorldObjects[i].processCollision(WorldObjects[j], &collisionPoint))
				{
					Physics::ObjectCollision(&WorldObjects[i], &WorldObjects[j], collisionPoint);
					cout << "something is colliding" << endl;
					cout << "collision point" << collisionPoint.x << endl;
					//cout << "i value:" << i << endl;
					//cout << "j value: " << j << endl;
				}
			}
		}
	}

}

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
		
		//contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
		int numContacts = contactManifold->getNumContacts();
		btVector3 midPt(.0f, .0f, .0f);
		//For each contact point in that manifold
		for (int j = 0; j < numContacts; j++) {
			//Get the contact information
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			btVector3 ptA = pt.getPositionWorldOnA();
			btVector3 ptB = pt.getPositionWorldOnB();
			double ptdist = pt.getDistance();

			/*std::cout << "pt: " << pt.getAppliedImpulse() << std::endl;
			std::cout << "ptA: " << ptA.getX() << ", " << ptA.getY() << ", " << ptA.getZ() << ", " << std::endl;
			std::cout << "ptB: " << ptB.getX() << ", " << ptB.getY() << ", " << ptB.getZ() << ", " << std::endl;
			std::cout << "ptdist: " << ptdist << std::endl;*/

			
		}

		// player cant move when it is colliding with something
		// convert btvec3 to glmvec3
		glm::vec3 obAtemp((float)obA->getWorldTransform().getOrigin().getX(), 
			(float)obA->getWorldTransform().getOrigin().getY(),
			(float)obA->getWorldTransform().getOrigin().getZ());
		
		glm::vec3 obBtemp((float)obB->getWorldTransform().getOrigin().getX(),
			(float)obB->getWorldTransform().getOrigin().getY(),
			(float)obB->getWorldTransform().getOrigin().getZ());

		if (
				(
					obAtemp.x == cameraPlayer.GetPosition().x &&
					obAtemp.y == cameraPlayer.GetPosition().y &&
					obAtemp.z == cameraPlayer.GetPosition().z
				)
				||
				(
					obBtemp.x == cameraPlayer.GetPosition().x &&
					obBtemp.y == cameraPlayer.GetPosition().y &&
					obBtemp.z == cameraPlayer.GetPosition().z
				)
			){

			camera->SetPostion(CurrentX, camera->GetPosition().y, CurrentZ);
		}
	}
}

