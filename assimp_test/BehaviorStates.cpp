#include "BehaviorStates.h"

#include <iostream>
#include "NPCs.h"
#include "World.h"
#include "Singleton.h"
using namespace std;



void Wander::Enter(NPCs *npc){
	stateTime = 0.0;
	cout << "Enter Wander state" << endl;
}

void Wander::Execute(NPCs *npc){

	int PathSize = npc->getPath().size();

	World *World_Instance = Singleton<World>::Instance();
	stateTime += World_Instance->GetDeltaTime();

	//cout << i;
	vector2D targetPos(npc->getPath()[i].x, npc->getPath()[i].y);   //position to move to
	vector2D targetXZ(npc->GetPosition().x, npc->GetPosition().z);    //our current position
	vector2D targetVel(npc->GetMoveSpeed(), npc->GetMoveSpeed());      //our current velocity

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

	//path finding
	if ((targetXZ.getX() == npc->getPath()[i].x) && (targetXZ.getY() == npc->getPath()[i].y))
	{
		i = (rand() % PathSize);
		//cout << targetVel.getY()<<endl;
		//npc->setCurrentEvent(0.0f, 0.0f);
		//npc->changeState(&emotions_state::Instance());
	}

	//check if player is kicking
	if (npc->processCollision(npc->GetPlayer()) && npc->GetPlayer()->isPlayerKicking())
	{

		npc->setCurrentEvent(-0.3f, -0.3f);
		npc->changeState(&emotions_state::Instance());
	}

	//check if player is praising
	if (npc->processCollision(npc->GetPlayer()) && npc->GetPlayer()->isPlayerPraising())
	{

		npc->setCurrentEvent(0.2f, 0.2f);
		npc->changeState(&emotions_state::Instance());
	}

	//check with all agents if they see each other
	for (int i = 1; i <= npc->GetAgents().size(); i++)
	{
		if ((npc->processDetectView(npc->GetAgents()[i])) && (npc->GetPosition().x != npc->GetAgents()[i]->GetPosition().x)
			&& (stateTime>10.0))
		{
			npc->changeState(&say_hi_state::Instance());
		}
	}

	//check if see any affordance objs
	for (int i = 0; i < npc->GetAffordanceObj().size(); i++)
	{
		//cout << npc->GetAffordanceObj().size() << endl;
		if ((npc->processDetectView(npc->GetAffordanceObj()[i])) && (npc->getTargetObject() == -1) && (stateTime>10.0)
			&& !npc->GetPlayer()->isPlayerLifting())
		{
			npc->setTargetObject(i);

			for (int j = 0; j < npc->GetAffordanceObj()[i]->getAffordance().size(); j++)
			{
				cout << npc->GetAffordanceObj()[i]->getAffordance().size() << endl;

				if (npc->GetAffordanceObj()[i]->getAffordance()[j] == "standable")
				{
					//cout << "Move away!!!!" << endl;
					//cout << i<< endl;

					npc->changeState(&stand_state::Instance());
				}

				if (npc->GetAffordanceObj()[i]->getAffordance()[j] == "liftable")
				{
					//cout << "Move away!!!!" << endl;
					//cout << i<< endl;
					
					npc->changeState(&lift_state::Instance());
				}


			}

		}

	}


	//npc->GetPlayer()->setActions(0);


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

	//calculate new emotion
	FinalEmotion.x = npc->getCurrentEvent().x * 1 + npc->getMoods().x / 2 + npc->getTraits().x *0.05 + npc->getPersonalities().x * 0.01;
	FinalEmotion.y = npc->getCurrentEvent().y * 1 + npc->getMoods().y / 2 + npc->getTraits().y * 0.05 + npc->getPersonalities().y * 0.01;
	
	//set emotions, moods, traits, personalities back to npc
	npc->setEmotions(FinalEmotion.x, FinalEmotion.y);
	npc->setMoods(npc->getCurrentEvent().x * 0.5 + npc->getMoods().x, npc->getCurrentEvent().y * 0.5 + npc->getMoods().y);
	npc->setTraits(npc->getCurrentEvent().x * 0.05 + npc->getTraits().x, npc->getCurrentEvent().y * 0.05 + npc->getTraits().y);
	npc->setPersonalities(npc->getCurrentEvent().x * 0.01 + npc->getPersonalities().x, npc->getCurrentEvent().y * 0.01 + npc->getPersonalities().y);

	npc->changeState(&response_state::Instance());
}

void Emotions::Exit(NPCs *npc){
	cout << "Exit Emotions state" << endl;
}


void Response::Enter(NPCs *npc){
	stateTime = 0.0;
	cout << "Enter Response state" << endl;
}

void Response::Execute(NPCs *npc){

	if (npc->GetPlayer()->isPlayerKicking())
	{
		npc->changeState(&say_stop_state::Instance());
	}

	if (npc->GetPlayer()->isPlayerPraising())
	{
		npc->changeState(&say_thanks_state::Instance());
	}
	
}

void Response::Exit(NPCs *npc){
	cout << "Exit Response state" << endl;
}

void Response1::Enter(NPCs *npc){
	stateTime = 0.0;
	cout << "Enter Response state" << endl;
}

void Response1::Execute(NPCs *npc){


		npc->UpdateModel("angry");

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

		npc->GetTexts()->setIfRenderText(true);
		npc->GetTexts()->UpdateModel("text1");
		npc->GetTexts()->Postition(npc->GetPosition().x, npc->GetPosition().y + 2.5f, npc->GetPosition().z);
		npc->GetTexts()->setRotation(NewRotation);


		if (stateTime > 5.0)
		{
			
			npc->GetTexts()->Postition(0.0f, -10.0f, 0.0f);
			//npc->GetTexts()->setIfRenderText(false);
			npc->changeState(&wander_state::Instance());
		}

		npc->GetPlayer()->setActions(0);
}

void Response1::Exit(NPCs *npc){
	cout << "Exit Response state" << endl;
}


void Response2::Enter(NPCs *npc){
	stateTime = 0.0;
	cout << "Enter Response state" << endl;
}

void Response2::Execute(NPCs *npc){


	npc->UpdateModel("happy");

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

	npc->GetTexts()->setIfRenderText(true);
	npc->GetTexts()->UpdateModel("text2");
	npc->GetTexts()->Postition(npc->GetPosition().x, npc->GetPosition().y + 2.5f, npc->GetPosition().z);
	npc->GetTexts()->setRotation(NewRotation);


	if (stateTime > 5.0)
	{
		npc->GetTexts()->Postition(0.0f, -10.0f, 0.0f);
		//npc->GetTexts()->setIfRenderText(false);
		npc->changeState(&wander_state::Instance());
	}

	npc->GetPlayer()->setActions(0);
}

void Response2::Exit(NPCs *npc){
	cout << "Exit Response state" << endl;
}

void Response3::Enter(NPCs *npc){
	stateTime = 0.0;
	cout << "Enter Response state" << endl;
}

void Response3::Execute(NPCs *npc){


	World *World_Instance = Singleton<World>::Instance();
	stateTime += World_Instance->GetDeltaTime();
	double z, x, angle;

	for (int i = 1; i <= npc->GetAgents().size(); i++)
	{
		if (npc->processDetectView(npc->GetAgents()[i]))
		{
			 z = npc->GetPosition().z - npc->GetAgents()[i]->GetPosition().z;
			 x = npc->GetPosition().x - npc->GetAgents()[i]->GetPosition().x;
			 angle = atan2(x, z) * 180 / PI;
		}
	}

	glm::vec4 NewRotation;
	NewRotation.x = 0;
	NewRotation.y = 0;
	NewRotation.z = 0;
	NewRotation.w = angle - 180;

	npc->setRotation(NewRotation);

	npc->GetTexts()->setIfRenderText(true);
	npc->GetTexts()->UpdateModel("text3");
	npc->GetTexts()->Postition(npc->GetPosition().x, npc->GetPosition().y + 2.5f, npc->GetPosition().z);
	npc->GetTexts()->setRotation(NewRotation);


	if (stateTime > 5.0)
	{
		npc->GetTexts()->Postition(0.0f, -10.0f, 0.0f);
		//npc->GetTexts()->setIfRenderText(false);
		npc->changeState(&wander_state::Instance());
	}

	npc->GetPlayer()->setActions(0);
}

void Response3::Exit(NPCs *npc){
	cout << "Exit Response state" << endl;
}


void Response4::Enter(NPCs *npc){
	stateTime = 0.0;
	cout << "Enter lift state" << endl;
}

void Response4::Execute(NPCs *npc){

	int PathSize = npc->getPath().size();
	int target = npc->getTargetObject();

	World *World_Instance = Singleton<World>::Instance();
	double timeDiff = World_Instance->GetDeltaTime();
	

	
	//cout << target;
	vector2D targetPos(npc->GetAffordanceObj()[target]->GetPosition().x, npc->GetAffordanceObj()[target]->GetPosition().z);   //position to move to
	vector2D targetXZ(npc->GetPosition().x, npc->GetPosition().z);    //our current position
	vector2D targetVel(npc->GetMoveSpeed(), npc->GetMoveSpeed());      //our current velocity

	//

	moveTo(targetXZ, targetPos, targetVel, timeDiff);



	////cout << timeDiff << endl;
	double z = targetXZ.getY() - targetPos.getY();
	double x = targetXZ.getX() - targetPos.getX();
	double angle = atan2(x, z) * 180 / PI;

	glm::vec4 NewRotation;
	NewRotation.x = 0;
	NewRotation.y = 0;
	NewRotation.z = 0;
	NewRotation.w = angle - 180;

	npc->setX(targetXZ.getX());
	npc->setZ(targetXZ.getY());
	npc->setRotation(NewRotation);

	if (npc->GetPosition().x==npc->GetAffordanceObj()[target]->GetPosition().x)
	{
		npc->GetAffordanceObj()[target]->Postition(npc->GetPosition().x, 1.5f, npc->GetPosition().z);
		stateTime += World_Instance->GetDeltaTime();
		//cout << "lift it !!!" << endl;
		if (stateTime > 5.0)
		{	
			npc->GetAffordanceObj()[target]->Postition(npc->GetPosition().x, 0.1f, npc->GetPosition().z);
			npc->setTargetObject(-1);
			npc->changeState(&wander_state::Instance());
		}

	}


}

void Response4::Exit(NPCs *npc){
	cout << "Exit lift state" << endl;
}



void Response5::Enter(NPCs *npc){
	stateTime = 0.0;
	cout << "Enter stand state" << endl;
}

void Response5::Execute(NPCs *npc){

	int PathSize = npc->getPath().size();
	int target = npc->getTargetObject();

	World *World_Instance = Singleton<World>::Instance();
	double timeDiff = World_Instance->GetDeltaTime();
	


	cout << target;
	vector2D targetPos(npc->GetAffordanceObj()[target]->GetPosition().x, npc->GetAffordanceObj()[target]->GetPosition().z);   //position to move to
	vector2D targetXZ(npc->GetPosition().x, npc->GetPosition().z);    //our current position
	vector2D targetVel(npc->GetMoveSpeed(), npc->GetMoveSpeed());      //our current velocity


	moveTo(targetXZ, targetPos, targetVel, timeDiff);

	////cout << timeDiff << endl;
	double z = targetXZ.getY() - targetPos.getY();
	double x = targetXZ.getX() - targetPos.getX();
	double angle = atan2(x, z) * 180 / PI;

	glm::vec4 NewRotation;
	NewRotation.x = 0;
	NewRotation.y = 0;
	NewRotation.z = 0;
	NewRotation.w = angle - 180;

	npc->setX(targetXZ.getX());
	npc->setZ(targetXZ.getY());
	npc->setRotation(NewRotation);

	if (npc->GetPosition().x == npc->GetAffordanceObj()[target]->GetPosition().x)
	{
		stateTime += World_Instance->GetDeltaTime();
		npc->Postition(npc->GetPosition().x, 1.0f, npc->GetPosition().z);
		if (stateTime > 5.0)
		{
			npc->Postition(npc->GetPosition().x, 0.0f, npc->GetPosition().z);
			npc->setTargetObject(-1);
			npc->changeState(&wander_state::Instance());
		}

	}
	else
	{
		npc->Postition(npc->GetPosition().x, 0.0f, npc->GetPosition().z);
	}


}

void Response5::Exit(NPCs *npc){
	cout << "Exit stand state" << endl;
}