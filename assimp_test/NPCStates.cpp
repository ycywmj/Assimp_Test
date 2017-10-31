#include "NPCStates.h"

#include <iostream>
#include "NPCs.h"
#include "World.h"
#include "Singleton.h"
using namespace std;

void Flee::Enter(NPCs *npc){
	cout << "Enter Flee state" << endl;
}

void Flee::Execute(NPCs *npc){

	if (0)
	{
		if (0)
			npc->changeState(&wander_state::Instance());
	}


	cout << "Execute Flee state" << endl;
}

void Flee::Exit(NPCs *npc){
	cout << "Exit Flee state" << endl;
}



void Wander::Enter(NPCs *npc){
	cout << "Enter Wander state" << endl;
}

void Wander::Execute(NPCs *npc){


	vector2D targetPos(10.0f, -8.0f);   //position to move to
	vector2D targetXZ(npc->GetPosition().x, npc->GetPosition().z);    //our current position
	vector2D targetVel(0.0f, 0.001f);      //our current velocity

	World *World_Instance = Singleton<World>::Instance();
	double timeDiff= World_Instance->GetGameTotalTime();

	moveTo(targetXZ, targetPos, targetVel, timeDiff);

	double z = targetXZ.getY() - targetPos.getY();
	double x = targetXZ.getX() - targetPos.getX();
	double angle = atan2(x, z) * 180 / PI;

	glm::vec4 NewRotation;
	NewRotation.x = 0;
	NewRotation.y = 0;
	NewRotation.z= 0;
	NewRotation.w = angle-180;

	npc->setX(targetXZ.getX());
	npc->setZ(targetXZ.getY());
	npc->setRotation(NewRotation);

	//cout << npc->GetPosition().x << endl;
	//cout << npc->GetPosition().z << endl << endl;
	//cout << timeDiff << endl;

	/*if (0)
	{
		if (0)
			npc->changeState(&flee_state::Instance());
	}*/

	//cout << "Execute Wander state" << endl;
}

void Wander::Exit(NPCs *npc){
	cout << "Exit walk state" << endl;
}