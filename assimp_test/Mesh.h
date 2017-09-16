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

#include "Shader.h"

using namespace std;

struct Vertex
{
    /// Position
    glm::vec3 Position;
    /// Normal
    glm::vec3 Normal;
    /// TexCoords
    glm::vec2 TexCoords;
};

struct Texture
{
	/// id of the texture
    GLuint id;
	/// texture type
    string type;
	/// file path of texture
    aiString path;
};

/**
* @class Mesh
* @brief Process the meshes of the model
*
*
*
*
* @author ChengYu Yang
* @version 01
* @date 01/09/2017
*
*
*
*/
class Mesh
{
public:
    /*  Mesh Data  */
	/// mesh vertices
    vector<Vertex> vertices;
	/// mesh indices
    vector<GLuint> indices;
	/// textures of the meshes
    vector<Texture> textures;
    
    /*  Functions  */
	/**
	* @brief  constructor
	*/
    Mesh( vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures )
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        
        // Now that we have all the required data, set the vertex buffers and its attribute pointers.
        this->setupMesh( );
    }
    
	/**
	* @brief  Render the mesh
	* @param shader, using the specific shader to render each mesh
	*/
    void Draw( Shader shader )
    {
        // Bind appropriate textures
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        
        for( GLuint i = 0; i < this->textures.size( ); i++ )
        {
            glActiveTexture( GL_TEXTURE0 + i ); 

            stringstream ss;
            string number;
            string name = this->textures[i].type;
            
            if( name == "texture_diffuse" )
            {
                ss << diffuseNr++; 
            }
            
            number = ss.str( );
            // Now set the sampler to the correct texture unit
            glUniform1i( glGetUniformLocation( shader.Program, ( name + number ).c_str( ) ), i );
            // And finally bind the texture
            glBindTexture( GL_TEXTURE_2D, this->textures[i].id );
        }
        
        //glUniform1f( glGetUniformLocation( shader.Program, "material.shininess" ), 20.0f );
        
        // Draw mesh
        glBindVertexArray( this->VAO );
        glDrawElements( GL_TRIANGLES, this->indices.size( ), GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );
        
        // Always good practice to set everything back to defaults once configured.
        for ( GLuint i = 0; i < this->textures.size( ); i++ )
        {
            glActiveTexture( GL_TEXTURE0 + i );
            glBindTexture( GL_TEXTURE_2D, 0 );
        }
    }
    
private:
    GLuint VAO, VBO, EBO;
    
	/**
	* @brief  initialize meshes
	* @return void
	*/
    void setupMesh( )
    {
        glGenVertexArrays( 1, &this->VAO );
        glGenBuffers( 1, &this->VBO );
        glGenBuffers( 1, &this->EBO );
        
        glBindVertexArray( this->VAO );
        
        glBindBuffer( GL_ARRAY_BUFFER, this->VBO );

        glBufferData( GL_ARRAY_BUFFER, this->vertices.size( ) * sizeof( Vertex ), &this->vertices[0], GL_STATIC_DRAW );
        
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->EBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->indices.size( ) * sizeof( GLuint ), &this->indices[0], GL_STATIC_DRAW );
        
        // Vertex Positions
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )0 );
        // Vertex Normals
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )offsetof( Vertex, Normal ) );
        // Vertex Texture Coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )offsetof( Vertex, TexCoords ) );
        
        glBindVertexArray( 0 );
    }
};