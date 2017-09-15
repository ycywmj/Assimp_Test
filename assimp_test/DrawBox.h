#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"

using namespace std;

/**
* @class DrawBox
* @brief I draws a box
*
*
*
*
*
* @author ChengYu Yang
* @version 01
* @date 15/09/2017
*
*
*/
class DrawBox
{
public:

	/*  Functions  */
	// Constructor
	DrawBox()
	{

	}

	void LoadBox(glm::vec3 Pos, glm::vec3 Siz)
	{
		shader = new Shader("res/shaders/Box.vs", "res/shaders/Box.frag");

		glm::vec3 Si;
		Si.x = Siz.x / 2;
		Si.y = Siz.y / 2;
		Si.z = Siz.z / 2;

		float vertices[] = { Pos.x - Si.x, Pos.y + Si.y, Pos.z - Si.z,
			Pos.x + Si.x, Pos.y + Si.y, Pos.z - Si.z,
			Pos.x + Si.x, Pos.y - Si.y, Pos.z - Si.z,
			Pos.x - Si.x, Pos.y - Si.y, Pos.z - Si.z,
			Pos.x - Si.x, Pos.y - Si.y, Pos.z + Si.z,
			Pos.x + Si.x, Pos.y - Si.y, Pos.z + Si.z,
			Pos.x + Si.x, Pos.y + Si.y, Pos.z + Si.z,
			Pos.x - Si.x, Pos.y + Si.y, Pos.z + Si.z, };

		unsigned int indices[] = {
			0, 1, 2, 3,
			0, 3, 4, 7,
			4, 5, 6, 7,
			1, 2, 5, 6
		};

		float vertices2[] = {
			5.0f, 5.0f, 0.0f,  // top right
			5.0f, -5.0f, 0.0f,  // bottom right
			-5.0f, -5.0f, 0.0f,  // bottom left
			-5.0f, 5.0f, 0.0f   // top left 
		};
		unsigned int indices2[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		
		/*projection = glm::perspective(camera_instance->GetZoom(), (float)1500 / (float)1000, 0.1f, 100.0f);

		view = glm::lookAt(camera_instance->GetPosition(),
			camera_instance->GetPosition() + camera_instance->GetFront(),
			camera_instance->GetUp());
		shader->Use();*/

		this->setupMesh(vertices2, indices2);
	}

	// Render the mesh
	void Draw()
	{
		//glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		// Draw mesh
		//glUseProgram(shader->Program);
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		cout << "aaaaaaa" << endl;

	}

private:
	unsigned int VAO, VBO, EBO;
	Shader *shader;
	glm::mat4 projection;
	Camera* camera_instance = Singleton<Camera>::Instance();
	glm::mat4 view;
	//float vertices[24];
	//unsigned int indices[8];

	void setupMesh(float vertices[], unsigned int indices[])
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
	}
};