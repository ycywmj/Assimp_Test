#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "SOIL2/SOIL2.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

using namespace std;

/**
* @class World
* @brief  Manages the running of the game world
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

class Model
{
public:
    /*  Functions   */
	/**
	* @brief  Constructor, expects a filepath to a 3D model.
	*/
    Model()
    {
    }

	/**
	* @brief   Loads the Model
	* @param path - string, the pathname to load
	* @return void
	*/
	void Load(string path)
	{
		this->loadModel(path);
	}
    
	/**
	* @brief   Draws the model, and thus all its meshes
	* @param shader - the shader class
	* @return void
	*/
    void Draw( Shader shader )
    {
        for ( GLuint i = 0; i < this->meshes.size( ); i++ )
        {
            this->meshes[i].Draw( shader );
        }
    }
    
private:
    /*  Model Data  */
	/// vector of meshes of the model
    vector<Mesh> meshes;
	/// file path of the model
    string directory;
	/// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Texture> textures_loaded;
    
    /*  Functions   */
	/**
	* @brief   Load the texture from file
	* @param path, file path of the texture
	* @param directory, file directory
	* @return void
	*/
	GLint TextureFromFile(const char *path, string directory)
	{
		//Generate texture ID and load texture data
		string filename = string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height, n;

		unsigned char * image = stbi_load(filename.c_str(), &width, &height, &n, 3);

		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		//SOIL_free_image_data( image );

		return textureID;
	}

	/**
	* @brief   Load the model from file
	* @param path, file path of the model
	* @return void
	*/
    void loadModel( string path )
    {
        // Read file via ASSIMP
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );
        
        // Check for errors
        if( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString( ) << endl;
            return;
        }
        // Retrieve the directory path of the filepath
        this->directory = path.substr( 0, path.find_last_of( '/' ) );
        
        // Process ASSIMP's root node recursively
        this->processNode( scene->mRootNode, scene );
    }
    
	/**
	* @brief   Process of the mesh node 
	* @param node, node
	* @param scene, scene
	* @return void
	*/
    void processNode( aiNode* node, const aiScene* scene )
    {
        // Process each mesh located at the current node
        for ( GLuint i = 0; i < node->mNumMeshes; i++ )
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            
            this->meshes.push_back( this->processMesh( mesh, scene ) );
        }
        
        for ( GLuint i = 0; i < node->mNumChildren; i++ )
        {
            this->processNode( node->mChildren[i], scene );
        }
    }
    
	/**
	* @brief   Process of the mesh
	* @param mesh, mesh pointer
	* @param scene, scene pointer
	* @return the mesh after process
	*/
    Mesh processMesh( aiMesh *mesh, const aiScene *scene )
    {
        // Data to fill
        vector<Vertex> vertices;
        vector<GLuint> indices;
        vector<Texture> textures;
        
        // Walk through each of the mesh's vertices
        for ( GLuint i = 0; i < mesh->mNumVertices; i++ )
        {
            Vertex vertex;
            glm::vec3 vector; 
            
            // Positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            
            // Normals
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
            
            // Texture Coordinates
            if( mesh->mTextureCoords[0] ) // Does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
            {
                vertex.TexCoords = glm::vec2( 0.0f, 0.0f );
            }
            
            vertices.push_back( vertex );
        }
        
        // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for ( GLuint i = 0; i < mesh->mNumFaces; i++ )
        {
            aiFace face = mesh->mFaces[i];
            // Retrieve all indices of the face and store them in the indices vector
            for ( GLuint j = 0; j < face.mNumIndices; j++ )
            {
                indices.push_back( face.mIndices[j] );
            }
        }
        
        // Process materials
        if( mesh->mMaterialIndex >= 0 )
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            
            // 1. Diffuse maps
            vector<Texture> diffuseMaps = this->loadMaterialTextures( material, aiTextureType_DIFFUSE, "texture_diffuse" );
            textures.insert( textures.end( ), diffuseMaps.begin( ), diffuseMaps.end( ) );
            
            // 2. Specular maps
            /*vector<Texture> specularMaps = this->loadMaterialTextures( material, aiTextureType_SPECULAR, "texture_specular" );
            textures.insert( textures.end( ), specularMaps.begin( ), specularMaps.end( ) );*/
        }
        
        // Return a mesh object created from the extracted mesh data
        return Mesh( vertices, indices, textures );
    }

	/**
	* @brief   Load the texture materials
	* @param mat, material
	* @param type, type of material
	* @param typeName, name of the type
	* @return void
	*/
    vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, string typeName )
    {
        vector<Texture> textures;
        
        for ( GLuint i = 0; i < mat->GetTextureCount( type ); i++ )
        {
            aiString str;
            mat->GetTexture( type, i, &str );
            
            // Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            GLboolean skip = false;
            
            for ( GLuint j = 0; j < textures_loaded.size( ); j++ )
            {
                if( textures_loaded[j].path == str )
                {
                    textures.push_back( textures_loaded[j] );
                    skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
                    
                    break;
                }
            }
            
            if( !skip )
            {   // If texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile( str.C_Str( ), this->directory );
                texture.type = typeName;
                texture.path = str;
                textures.push_back( texture );
                
                this->textures_loaded.push_back( texture );  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        
        return textures;
    }
};
