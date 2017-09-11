#include "World.h"

int main()
{
	World *world = Singleton<World>::Instance();
	world->RunGame("OpenGL");

	return 0;
}
  