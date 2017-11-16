#include "EmotionStates.h"

#include <iostream>
#include "NPCs.h"
#include "World.h"
#include "Singleton.h"
using namespace std;

void Happy::Enter(NPCs *npc){
	//stateTime = 0.0;

	cout << "Enter Flee state" << endl;
}

void Happy::Execute(NPCs *npc){

	npc->UpdateModel("happy");
	if (npc->getEmotions().x < -0.3)
	{
		npc->changeEmotionState(&sad_state::Instance());
	}

	if ((npc->getEmotions().x >= -0.3) && (npc->getEmotions().x <= 0.3))
	{
		npc->changeEmotionState(&normal_state::Instance());
	}

}

void Happy::Exit(NPCs *npc){
	cout << "Exit Flee state" << endl;
	npc->GetPlayer()->setActions(0);
}



void Sad::Enter(NPCs *npc){
	cout << "Enter Flee state" << endl;
}

void Sad::Execute(NPCs *npc){
	npc->UpdateModel("sad");
	if (npc->getEmotions().x > 0.3)
	{
		npc->changeEmotionState(&happy_state::Instance());
	}

	if ((npc->getEmotions().x >= -0.3) && (npc->getEmotions().x <= 0.3))
	{
		npc->changeEmotionState(&normal_state::Instance());
	}
}

void Sad::Exit(NPCs *npc){
	cout << "Exit Sad state" << endl;
}


void Normal::Enter(NPCs *npc){
	
	cout << "Enter Normal state" << endl;
}

void Normal::Execute(NPCs *npc){

	npc->UpdateModel("normal");
	if (npc->getEmotions().x > 0.3)
	{
		npc->changeEmotionState(&happy_state::Instance());
	}

	if (npc->getEmotions().x < -0.3)
	{
		npc->changeEmotionState(&sad_state::Instance());
	}
	
}

void Normal::Exit(NPCs *npc){
	cout << "Exit Normal state" << endl;
}