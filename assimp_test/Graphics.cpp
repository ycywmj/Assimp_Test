#include <string>

#include "Graphics.h"
#include "World.h"
#include "Camera.h"
#include "GameStatus.h"

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

	screen_width = 1024; screen_height = 768;
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
	glfwSetMouseButtonCallback(window, MouseButtonCallbackWrap);

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
	shader_2d = new Shader("res/shaders/2d_imgs.vs", "res/shaders/2d_imgs.frag");
	
	// Draw in wireframe
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	Camera* camera_instance = Singleton<Camera>::Instance();
	projection = glm::perspective(camera_instance->GetZoom(), (float)screen_width / (float)screen_height, 0.1f, 100.0f); 

	World *world_instance = Singleton<World>::Instance();
	world_instance->InitializeGame();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		GameLoop();

	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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
	glClearColor(42.0f/ 255.0f, 74.0f / 255.0f, 117.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	shader->Use();

	// camera lookat function
	Camera* camera_instance = Singleton<Camera>::Instance();
	glm::mat4 view = glm::lookAt(camera_instance->GetPosition(),
		camera_instance->GetPosition() + camera_instance->GetFront(),
		camera_instance->GetUp());
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	// end

	World *world_instance = Singleton<World>::Instance();
	world_instance->UpdateGame();

	// Swap the buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// Moves/alters the camera positions based on user input
void OpenGL::DoMovement()
{
	Camera* camera_instance = Singleton<Camera>::Instance();
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera_instance->ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera_instance->ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera_instance->ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera_instance->ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void OpenGL::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	GameStatus* game_status = Singleton<GameStatus>::Instance();
	if ((*game_status) == GAME_PLAYING){
		if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
		{
			*game_status = GAME_CREDIT_PAGE;
		}

		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
			{
				keys[key] = true;
				//cout << key << endl;
			}
			else if (action == GLFW_RELEASE)
			{
				keys[key] = false;
			}
		}
	}
	/*else if ((*game_status) == GAME_CREDIT_PAGE){
		if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}*/
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

	Camera* camera_instance = Singleton<Camera>::Instance();
	camera_instance->ProcessMouseMovement(xOffset, yOffset);
}

void OpenGL::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods){
	GameStatus* game_status = Singleton<GameStatus>::Instance();
	if ((*game_status) == GAME_CREDIT_PAGE){
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
			World* world_instance = Singleton<World>::Instance();
			world_instance->GameDestruction();
			exit(0);
		}
	}
}

void OpenGL::LoadModel(string fname)
{
	for (map<string, Model*>::iterator it = Models.begin(); it != Models.end(); ++it)
	{
		if (fname == it->first)
			return;
	}
	ourModel = new Model();
	ourModel->Load(fname);
	Models[fname] = ourModel;

}

void OpenGL::RenderModel(string fname,glm::vec3 Pos, glm::vec3 Sca, glm::vec4 Rot){
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(Pos.x, Pos.y, Pos.z)); 
	model = glm::scale(model, glm::vec3(Sca.x, Sca.y, Sca.z));	
	model = glm::rotate(model, glm::radians(Rot.w), glm::vec3(Rot.x, Rot.y, Rot.z));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Models[fname]->Draw(*shader);
}

void OpenGL::Load2DTexture(string fname){

	for (map<string, unsigned int*>::iterator it = Textures_2d.begin(); it != Textures_2d.end(); ++it)
	{
		if (fname == it->first)
			return;
	}

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		0.9f, 0.9f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.9f, -0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.9f, 0.9f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
	ourTexture = new unsigned int;
	glGenTextures(1, &(*ourTexture));
	glBindTexture(GL_TEXTURE_2D, (*ourTexture)); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(fname.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	Textures_2d[fname] = ourTexture;

}

void OpenGL::Render2DTexture(string fname){
	// render
	// ------
	glClearColor(42.0f / 255.0f, 74.0f / 255.0f, 117.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind Texture
	glBindTexture(GL_TEXTURE_2D, *(Textures_2d[fname]));

	// render container
	shader_2d->Use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D,0);

}

void OpenGL::loadBox(glm::vec3 pos, glm::vec3 siz)
{
	BoxModel = new DrawBox();
	BoxModel->LoadBox(pos, siz);
}

void OpenGL::drawBox()
{
	BoxModel->Draw();
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