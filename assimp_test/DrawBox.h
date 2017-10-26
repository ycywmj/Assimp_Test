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
		shader3 = new Shader("res/shaders/Box.vs", "res/shaders/Box.frag");

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
			-0.5f, -0.5f, 0.0f, // Left
			0.5f, -0.5f, 0.0f, // Right
			0.0f, 0.5f, 0.0f  // Top
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

		setupMesh(vertices2, indices2);
	}

	// Render the mesh
	void Draw()
	{

		//glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//Draw mesh
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUseProgram(shader3->Program);
		//shader->Use();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		//cout << "aaaaaaa" << endl;

	}

private:
	unsigned int vao, vbo;
	Shader *shader3;
	//glm::mat4 projection;
	//Camera* camera_instance = Singleton<Camera>::Instance();
	//glm::mat4 view;
	//float vertices[24];
	//unsigned int indices[8];

	void setupMesh(float vertices2[], unsigned int indices[])
	{
		static const GLfloat vertices[] = {
			-1.0f, -1.0f, -1.0f, // triangle 1 : begin
			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, // triangle 1 : end
			1.0f, 1.0f, -1.0f, // triangle 2 : begin
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f, // triangle 2 : end
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0);
	};
};