#include <string>

#include "Graphics.h"
#include "World.h"
#include "Singleton.h"

OpenGL* OpenGL::opengl_instance;

void OpenGL::CreateGameWindow(){
	SetInstance();

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//glewInit();

	screen_width = 1500; screen_height = 1000;
	window = glfwCreateWindow(screen_width, screen_height, "ICT398 - PlentoonGame", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &screen_width, &screen_height);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallbackWrap);
	glfwSetCursorPosCallback(window, MouseCallbackWrap);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Define the viewport dimensions
	glViewport(0, 0, screen_width, screen_height);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	// Setup and compile our shaders
	shader = new Shader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");

	// Load models
	ourModel = new Model("res/models/bench.obj");
	//Model ourModel("res/models/Futuristic_Bike/Futuristic-Bike.obj");

	// Draw in wireframe
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	//access world class through singleton, Pointer reference to be implemented
	World *world_instance = Singleton<World>::Instance();
	

	projection = glm::perspective(world_instance->GetZoom(), (float)screen_width / (float)screen_height, 0.1f, 100.0f);

	World *world_instance = Singleton<World>::Instance();
	world_instance->InitializeGame();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		GameLoop();
	}

	glfwTerminate();
}

void OpenGL::GameLoop(){
	// Set frame time
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Check and call events
	glfwPollEvents();
	DoMovement();

	// Clear the colorbuffer
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();

	//Allow access to world class
	World *world_instance = Singleton<World>::Instance();

	//glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 view;//glm::mat4* viewPointer = &view;
	world_instance->GetViewMatrix(&view);
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	//RenderModel(ourModel);

	World *world_instance = Singleton<World>::Instance();
	world_instance->UpdateGame();

	// Swap the buffers
	glfwSwapBuffers(window);
}

// Moves/alters the camera positions based on user input
void OpenGL::DoMovement()
{
	World *world_instance = Singleton<World>::Instance();

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		world_instance->ProcessKeyboard(FORWARD, deltaTime);
		//camera->ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		world_instance->ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		world_instance->ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		world_instance->ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void OpenGL::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void OpenGL::MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	double xOffset = xPos - lastX;
	double yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	World *world_instance = Singleton<World>::Instance();

	world_instance->ProcessMouseMovement(xOffset, yOffset);
}

void OpenGL::RenderModel(Model* ourModel){
	// Draw the loaded model
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	ourModel->Draw(*shader);
}

Graphics* GraphicsFactory::Create(const char* type){
	std::string type_str = type;
	if (type_str == "OpenGL"){
		return new OpenGL;
	}
	/*
	else if (type_str == "DirectX"){
		return new DirectX;
	}
	*/
	else{
		return NULL;
	}
}