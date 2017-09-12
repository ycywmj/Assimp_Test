#include "GameObject.h"

GameObject::GameObject(const char* fname){
	this->source_fname = fname;
	LoadModel(source_fname.c_str());
}

void GameObject::LoadModel(const char* fname){
	//ourModel = new Model("res/models/bench.obj");
	ourModel = new Model(fname);
}