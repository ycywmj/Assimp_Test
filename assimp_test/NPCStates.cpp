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

	int PathSize = npc->getPath().size();

	//cout << i;
	vector2D targetPos(npc->getPath()[i].x, npc->getPath()[i].y);   //position to move to
	vector2D targetXZ(npc->GetPosition().x, npc->GetPosition().z);    //our current position
	vector2D targetVel(1.0f, 1.0f);      //our current velocity

	World *World_Instance = Singleton<World>::Instance();
	double timeDiff = World_Instance->GetDeltaTime();

	moveTo(targetXZ, targetPos, targetVel, timeDiff);

	//cout << timeDiff << endl;
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

	if ((targetXZ.getX() == npc->getPath()[i].x) && (targetXZ.getY() == npc->getPath()[i].y))
	{
		i = (rand() % PathSize);
		//cout << targetVel.getY()<<endl;
		//npc->setCurrentEvent(0.0f, 0.0f);
		//npc->changeState(&emotions_state::Instance());
	}


	if (npc->processCollision(npc->GetPlayer()) && npc->GetPlayer()->isPlayerKicking())
	{

		npc->setCurrentEvent(0.5f, 0.5f);
		npc->changeState(&emotions_state::Instance());
	}

	npc->GetPlayer()->setActions(0);


	

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


void Emotions::Enter(NPCs *npc){
	cout << "Enter Emotions state" << endl;
}

void Emotions::Execute(NPCs *npc){

	glm::vec2 FinalEmotion;

	FinalEmotion.x = npc->getCurrentEvent().x * 1 + npc->getMoods().x / 2 + npc->getTraits().x *0.05 + npc->getPersonalities().x * 0.01;
	FinalEmotion.y = npc->getCurrentEvent().y * 1 + npc->getMoods().y / 2 + npc->getTraits().y * 0.05 + npc->getPersonalities().y * 0.01;
	
	npc->setEmotions(FinalEmotion.x, FinalEmotion.y);
	npc->setMoods(npc->getCurrentEvent().x * 0.5 + npc->getMoods().x, npc->getCurrentEvent().y * 0.5 + npc->getMoods().y);
	npc->setTraits(npc->getCurrentEvent().x * 0.05 + npc->getTraits().x, npc->getCurrentEvent().y * 0.05 + npc->getTraits().y);
	npc->setPersonalities(npc->getCurrentEvent().x * 0.01 + npc->getPersonalities().x, npc->getCurrentEvent().y * 0.01 + npc->getPersonalities().y);

	/*if (0)
	{
		if (0)
			npc->changeState(&wander_state::Instance());
	}*/

	if (FinalEmotion.x >= 0)
	{
		npc->changeState(&happy_state::Instance());
	}

	if (FinalEmotion.x < 0)
	{
		npc->changeState(&sad_state::Instance());
	}


	//cout << FinalEmotion.x << endl;
	//cout << FinalEmotion.y << endl;
}

void Emotions::Exit(NPCs *npc){
	cout << "Exit Emotions state" << endl;
}


void Happy::Enter(NPCs *npc){
	stateTime = 0.0;

	cout << "Enter Flee state" << endl;
}

void Happy::Execute(NPCs *npc){

	World *World_Instance = Singleton<World>::Instance();
	stateTime += World_Instance->GetDeltaTime();

	double z = npc->GetPosition().z - npc->GetPlayer()->GetPosition().z;
	double x = npc->GetPosition().x - npc->GetPlayer()->GetPosition().x;
	double angle = atan2(x, z) * 180 / PI;

	glm::vec4 NewRotation;
	NewRotation.x = 0;
	NewRotation.y = 0;
	NewRotation.z = 0;
	NewRotation.w = angle - 180;

	npc->setRotation(NewRotation);

	if (stateTime > 5.0)
	{
		npc->changeState(&wander_state::Instance());
	}
	cout << "I am Happy" << endl;


}

void Happy::Exit(NPCs *npc){
	cout << "Exit Flee state" << endl;
	npc->GetPlayer()->setActions(0);
}



void Sad::Enter(NPCs *npc){
	cout << "Enter Flee state" << endl;
}

void Sad::Execute(NPCs *npc){


	cout << "Sad!!!!" << endl;
}

void Sad::Exit(NPCs *npc){
	cout << "Exit Flee state" << endl;
}