#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <GL/glut.h>

class Texture2D{
public:

	/**
	* set the total texture number
	* @param number of texture
	*/
	void SetTextureCount(const int & amount){
		m_texture = new GLuint[amount];
		glGenTextures(amount, &m_texture[0]);
	}

	/**
	* to load raw image as texture in 2d sceen
	* @param src of the img
	* @param size of the img
	* @param the texture number for mapping (identification)
	* @return bytes of glut texture
	*/
	void LoadRawTexture2D(char* img_src, const int & width, const int & height, const int & texture_no);

	/**
	* to display the texture on screen in 2d
	* @param size of the img
	* @param position of the texture
	* @param texture id will be displayed
	*/
	void Display2DTexture(const int & width, const int & height, const int & pos_x, const int & pos_y, const int & temp_img_no);

	/**
	* clear memory used to store textures
	*/
	void Clear();

	/**
	* set method for private variable
	* @param new value
	*/

	void SetScreenSize(const int & width, const int & height){
		screen_width = width;
		screen_height = height;
	}

private:
	/// screen size of the game window
	int screen_width, screen_height;

	/// pointer to display list
	GLuint* m_texture;
};

#endif