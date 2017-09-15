#pragma once

// OpenGL libraries
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
//#include "Camera.h"
#include "Model.h"
// OpenGL end

// General libraries
#include "Singleton.h"

#include <map>

using namespace std;

class Graphics{
public:
	Graphics(){};
	~Graphics(){};
	Graphics(const Graphics & cpy){
		this->screen_width = cpy.screen_width;
		this->screen_height = cpy.screen_height;
	};

	virtual void CreateGameWindow() = 0;
	virtual void LoadModel(string fname) = 0;
	virtual void RenderModel(string fname,glm::vec3 Pos, glm::vec3 Sca, glm::vec4 Rot) = 0;
	virtual void Load2DTexture(string fname) = 0;
	virtual void Render2DTexture(string fname) = 0;

	int GetScreenWidth(){ return screen_width; };
	int GetScreenHeight(){ return screen_height; };
									
protected:
	int screen_width, screen_height;
};

class OpenGL : public Graphics{
public:
	OpenGL(){
		//camera = new Camera(glm::vec3(1.0f, 1.0f, 1.0f));
	};
	~OpenGL(){
		if (shader){
			delete shader;
			shader = NULL;
		}
		if (shader_2d){
			delete shader_2d;
			shader_2d = NULL;
		}
		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	};
	OpenGL(const OpenGL & cpy){};

	void CreateGameWindow();

	void LoadModel(string fname);
	void RenderModel(string fname,glm::vec3 Pos, glm::vec3 Sca, glm::vec4 Rot);

	void Load2DTexture(string fname);
	void Render2DTexture(string fname);

	void LoadBox();
	void DrawBox();
	
private:
	void GameLoop();

	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	void MouseCallback(GLFWwindow *window, double xPos, double yPos);
	void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	void DoMovement();

	// mem var
	// window 
	GLFWwindow *window;

	// projection
	glm::mat4 projection;

	glm::mat4 model;

	// key
	bool keys[1024];

	// time
	double deltaTime = 0.0;
	double lastFrame = 0.0;

	// Camera
	//Camera *camera;
	double lastX = 400.0, lastY = 300.0;
	bool firstMouse = true;

	// models
	Shader *shader;
	// Load models
	Model *ourModel;
	map < string, Model* > Models;

	// 2D textureing shader
	Shader *shader_2d;
	unsigned int VBO, VAO, EBO;
	unsigned int *ourTexture;
	map < string, unsigned int* > Textures_2d;

	// wrap the callback func
	static OpenGL *opengl_instance;
	void SetInstance(){ opengl_instance = this; };
	static void KeyCallbackWrap(GLFWwindow *window, int key, int scancode, int action, int mode){
		opengl_instance->KeyCallback(window, key, scancode, action, mode);
	}
	static void MouseCallbackWrap(GLFWwindow *window, double xPos, double yPos){
		opengl_instance->MouseCallback(window, xPos, yPos);
	}
	static void MouseButtonCallbackWrap(GLFWwindow *window, int button, int action, int mods){
		opengl_instance->MouseButtonCallback(window, button, action, mods);
	}
};

class GraphicsFactory{
public:
	GraphicsFactory(){};
	~GraphicsFactory(){};
	GraphicsFactory(const GraphicsFactory & cpy){};

	Graphics* Create(const char* type);
};
