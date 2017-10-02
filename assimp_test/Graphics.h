#ifndef GRAPHICS_H
#define GRAPHICS_H

// OpenGL
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLUT
#include <GL/freeglut.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include "Singleton.h"

class Graphics{
public:
	Graphics(){};
	~Graphics(){};
	Graphics(const Graphics & cpy){
		this->screen_width = cpy.screen_width;
		this->screen_height = cpy.screen_height;
	};

	virtual void CreateGameWindow() = 0;

	virtual void OpenPolygonMode() = 0;
	virtual void ClosePolygonMode() = 0;
	virtual void WarpPointerToCentre() = 0;


	int GetScreenWidth(){ return screen_width; };
	int GetScreenHeight(){ return screen_height; };
									
protected:
	int screen_width, screen_height;
};

class OpenGL : public Graphics{
public:
	OpenGL(){
		window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", nullptr, nullptr);
		projection = glm::perspective(camera->GetZoom(), (float)screen_width / (float)screen_height, 0.1f, 100.0f);
		camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		shader = new Shader("res/shaders/modelLoading.vs", "res/shaders/modelLoading.frag");
		ourModel = new Model("res/models/bench.obj");
	};
	~OpenGL(){
		if (camera){
			delete camera;
			camera = NULL;
		}
		if (shader){
			delete shader;
			shader = NULL;
		}
		if (ourModel){
			delete ourModel;
			ourModel = NULL;
		}
	};
	OpenGL(const OpenGL & cpy){};
	
private:
	void CreateGameWindow();
	void GameLoop();

	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	void MouseCallback(GLFWwindow *window, double xPos, double yPos);
	void DoMovement();

	void OpenPolygonMode(){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	};
	void ClosePolygonMode(){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	};
	void WarpPointerToCentre(){
		glutWarpPointer(screen_width / 2, screen_height / 2);
	};

	// mem var
	// window 
	GLFWwindow *window;

	// projection
	glm::mat4 projection;

	// key
	bool keys[1024];

	// time
	double deltaTime = 0.0;
	double lastFrame = 0.0;

	// Camera
	Camera *camera;
	double lastX = 400.0, lastY = 300.0;
	bool firstMouse = true;

	// models
	// Setup and compile our shaders
	Shader *shader;

	// Load models
	Model *ourModel;
	//Model ourModel("res/models/Futuristic_Bike/Futuristic-Bike.obj");

	// wrap the callback func
	static OpenGL *opengl_instance;
	void SetInstance(){ opengl_instance = this; };
	static void KeyCallbackWrap(GLFWwindow *window, int key, int scancode, int action, int mode){
		opengl_instance->KeyCallback(window, key, scancode, action, mode);
	}
	static void MouseCallbackWrap(GLFWwindow *window, double xPos, double yPos){
		opengl_instance->MouseCallback(window, xPos, yPos);
	}
};

class GraphicsFactory{
public:
	GraphicsFactory(){};
	~GraphicsFactory(){};
	GraphicsFactory(const GraphicsFactory & cpy){};

	Graphics* Create(const char* type);
};

#endif