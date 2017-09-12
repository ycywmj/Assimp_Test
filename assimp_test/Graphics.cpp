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
	shader = new Shader("res/shaders/modelLoader.vs", "res/shaders/modelLoader.frag");
	
	// Draw in wireframe
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	projection = glm::perspective(camera->GetZoom(), (float)screen_width / (float)screen_height, 0.1f, 100.0f); 


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


	World *world_instance = Singleton<World>::Instance();
	world_instance->UpdateGame();

	// Swap the buffers
	glfwSwapBuffers(window);
}

// Moves/alters the camera positions based on user input
void OpenGL::DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera->ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera->ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera->ProcessKeyboard(RIGHT, deltaTime);
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

	camera->ProcessMouseMovement(xOffset, yOffset);
}

void OpenGL::LoadModel(string fname)
{
	ourModel = new Model();
	ourModel->Load(fname);
	Models[fname] = ourModel;
}

void OpenGL::RenderModel(string fname,glm::vec3 Pos, glm::vec3 Sca, glm::vec4 Rot){
	shader->Use();
	
	glm::mat4 view = camera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(Pos.x, Pos.y, Pos.z)); 
	model = glm::scale(model, glm::vec3(Sca.x, Sca.y, Sca.z));	
	model = glm::rotate(model, glm::radians(Rot.w), glm::vec3(Rot.x, Rot.y, Rot.z));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//ourModel.Draw(*shader);
	Models[fname]->Draw(*shader);
	
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