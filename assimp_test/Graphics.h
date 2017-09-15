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


/**
* @class Graphics
* @brief  Manages all of the openGL functionality
*
* Graphics contains all of the openGL code, keeping it seperate from the rest of the program
*
* @author Liam Goerke
* @version 01
* @date 10/09/2017
*
* @author Kin Pan Mak
* @version 02
* @date 15/09/2017
*
*
*/
class Graphics{
public:
	/**
	* @brief  constructor
	*/
	Graphics(){};

	/**
	* @brief  Destructor
	*/
	~Graphics(){};

	/**
	* @brief  copy constructor
	* @Param cpy, a graphics class pointer
	*/
	Graphics(const Graphics & cpy){
		this->screen_width = cpy.screen_width;
		this->screen_height = cpy.screen_height;
	};

	/**
	* @brief  pure virtual function
	* @return void
	*/
	virtual void CreateGameWindow() = 0;

	/**
	* @brief  pure virtual function
	* @param fname, a string indidcating the filename
	* @return void
	*/
	virtual void LoadModel(string fname) = 0;

	/**
	* @brief  pure virtual function
	* @param fname - a string indidcating the filename
	* @param Pos - a vector3 for position
	* @param Sca - a vector 3 for Scale
	* @param Rot - a vector4 for rotation
	* @return void
	*/
	virtual void RenderModel(string fname,glm::vec3 Pos, glm::vec3 Sca, glm::vec4 Rot) = 0;

	/**
	* @brief  pure virtual function
	* @param fname, a string indidcating the filename
	* @return void
	*/
	virtual void Load2DTexture(string fname) = 0;

	/**
	* @brief  pure virtual function
	* @param fname - a string indidcating the filename
	* @return void
	*/
	virtual void Render2DTexture(string fname) = 0;

	/**
	* @brief  Getter function for screen width
	* 
	* @return int - screen_width
	*/
	int GetScreenWidth(){ return screen_width; };
	
	/**
	* @brief  Getter function for screen height
	*
	* @return int - screen_height
	*/
	int GetScreenHeight(){ return screen_height; };
									
protected:
	///the screen width and height
	int screen_width, screen_height;
};

class OpenGL : public Graphics{
public:
	/**
	* @brief  constructor
	*/
	OpenGL(){};

	/**
	* @brief  Destructor
	*/
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

	/**
	* @brief  copy constructor
	* @Param cpy, a graphics class pointer
	*/
	OpenGL(const OpenGL & cpy){};

	/**
	* @brief  Initialize the GLFW window and create the window
	* @return void
	*/
	void CreateGameWindow();

	/**
	* @brief  Load the model file and bind in the model map
	* @param fname, a string indidcating the filename
	* @return void
	*/
	void LoadModel(string fname);

	/**
	* @brief  Render the model by finding the specific model file name from the model map
	* @param fname - a string indidcating the filename
	* @param Pos - a vector3 for position
	* @param Sca - a vector 3 for Scale
	* @param Rot - a vector4 for rotation
	* @return void
	*/
	void RenderModel(string fname,glm::vec3 Pos, glm::vec3 Sca, glm::vec4 Rot);

	/**
	* @brief  Load the texture file and bind in the 2d texture map
	* @param fname, a string indidcating the filename
	* @return void
	*/
	void Load2DTexture(string fname);

	/**
	* @brief  Render the 2d texture by finding the specific texture file name from the 2d texture map
	* @param fname, a string indidcating the filename
	* @return void
	*/
	void Render2DTexture(string fname);

	void LoadBox();
	void DrawBox();
	
private:
	/**
	* @brief  Handles all the activities the game window will process
	* @return void
	*/
	void GameLoop();

	/**
	* @brief  Handles keyboard input
	* @param same template as the original function
	* @return void
	*/
	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	
	/**
	* @brief  Handles mouse movement input
	* @param same template as the original function
	* @return void
	*/
	void MouseCallback(GLFWwindow *window, double xPos, double yPos);

	/**
	* @brief  Handles mouse clicking event
	* @param same template as the original function
	* @return void
	*/
	void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

	/**
	* @brief  Handles camera movement
	* @return void
	*/
	void DoMovement();

	// mem var
	/// GLFW window 
	GLFWwindow *window;

	/// Camera projection
	glm::mat4 projection;

	glm::mat4 model;

	/// keys from keyboard
	bool keys[1024];

	/// time elapsed
	double deltaTime = 0.0;
	/// time elapsed
	double lastFrame = 0.0;

	// Camera
	double lastX = 400.0, lastY = 300.0;
	bool firstMouse = true;

	// models
	/// shader
	Shader *shader;
	// Load models
	/// Stores the model just loaded up
	Model *ourModel;

	/// Model asset
	map < string, Model* > Models;

	// 2D textureing shader
	/// shader for 2d texturing
	Shader *shader_2d;
	
	unsigned int VBO, VAO, EBO;

	/// Stores the texture just loaded up
	unsigned int *ourTexture;

	/// 2D Texture asset
	map < string, unsigned int* > Textures_2d;

	/// wrap the callback func
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

	/**
	* @brief  Creates a new graphics api object to graphics handler
	* @param type, name of graphics api
	* @return graphics api pointer
	*/
	Graphics* Create(const char* type);
};
