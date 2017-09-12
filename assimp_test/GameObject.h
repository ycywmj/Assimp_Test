#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "Model.h"

class GameObject{
public:
	GameObject(){};
	GameObject(const char* fname);
	~GameObject(){
		DestroyModel();
	};
	GameObject(const GameObject& cpy){};

	void LoadModel(const char* fname);
	void DestroyModel(){
		if (ourModel){
			delete ourModel;
			ourModel = NULL;
		}
	};

	Model* GetModelPtr(){
		return ourModel;
	}

private:
	std::string source_fname;
	Model *ourModel;
};

#endif