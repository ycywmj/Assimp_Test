#pragma once

// Std. Includes
#include <vector>

// GL Includes
//#define GLEW_STATIC
//#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW				= -90.0f;
const float PITCH			=  0.0f;
const float SPEED			=  6.0f;
const float SENSITIVTY		=  0.25f;
const float ZOOM			=  45.0f;
const bool FIX_Y			=  true;
const float FIX_Y_VALUE		=  1.25f;

/**
* @class Camera
* @brief  Manages the camera functionality
*
* An abstract camera class that processes input and calculates the corresponding Eular Angles,
* Vectors and Matrices for use in OpenGL
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
class Camera
{
public:

	/**
	* @brief  Constructor for the Camera with Vectors
	*
	* Initialises camera variables
	*
	* @param  position - vector3 for position
	* @param  up - up vector3 
	* @param  yaw - float for YAW
	* @param  pitch - float for pitch
	* 
	*/
    Camera( glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ), float yaw = YAW, float pitch = PITCH ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), movementSpeed( SPEED ), mouseSensitivity( SENSITIVTY ), zoom( ZOOM )
    {
        this->position = position;
		if (FIX_Y) this->position.y = FIX_Y_VALUE;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors( );
    }
    
	/**
	* @brief  Constructor for the Camera with Vectors
	*
	* Initialises camera variables
	*
	* @param  posX - float X position
	* @param  posY - float Y position
	* @param  posZ - float Z position
	* @param  upX - float X up vector
	* @param  upY - float Y up vector
	* @param  upZ - float Z up vector
	* @param  yaw - float for YAW
	* @param  pitch - float for pitch
	* 
	*/
    Camera( float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), movementSpeed( SPEED ), mouseSensitivity( SENSITIVTY ), zoom( ZOOM )
    {
        this->position = glm::vec3( posX, posY, posZ );
		if (FIX_Y) this->position.y = FIX_Y_VALUE;
        this->worldUp = glm::vec3( upX, upY, upZ );
        this->yaw = yaw;
        this->pitch = pitch;
        this->updateCameraVectors( );
    }
    
	/**
	* @brief  returns players looking direction
	*
	* Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	*
	* @return glm::mat4 - the direction the player is looking in
	*/
    glm::mat4 GetViewMatrix( )
    {
        return glm::lookAt( this->position, this->position + this->front, this->up );
    }
    
	/**
	* @brief  Processes keys
	*
	* Processes input received from any keyboard-like input system. 
	* Accepts input parameter in the form of camera defined ENUM 
	* (to abstract it from windowing systems)
	*
	* @param  direction - Camera_Movement 
	* @param  deltaTime- float
	* @return void
	*/
	void ProcessKeyboard( Camera_Movement direction, float deltaTime )
    {
        float velocity = this->movementSpeed * deltaTime;
        
        if ( direction == FORWARD )
        {
            this->position += this->front * velocity;
        }
        
        if ( direction == BACKWARD )
        {
            this->position -= this->front * velocity;
        }
        
        if ( direction == LEFT )
        {
            this->position -= this->right * velocity;
        }
        
        if ( direction == RIGHT )
        {
            this->position += this->right * velocity;
        }

		if (FIX_Y) this->position.y = FIX_Y_VALUE;
    }
    
	/**
	* @brief  Processes Mouse movements
	*
	* Processes input received from a mouse input system. 
	* Expects the offset value in both the x and y direction.
	*
	* @param  xOffset - float
	* @param  yOffset- float
	* @param  constrainPitch- GLboolean = true
	* @return void
	*/
	void ProcessMouseMovement( float xOffset, float yOffset, GLboolean constrainPitch = true )
    {
        xOffset *= this->mouseSensitivity;
        yOffset *= this->mouseSensitivity;
        
        this->yaw   += xOffset;
        this->pitch += yOffset;
        
        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if ( constrainPitch )
        {
            if ( this->pitch > 89.0f )
            {
                this->pitch = 89.0f;
            }
            
            if ( this->pitch < -89.0f )
            {
                this->pitch = -89.0f;
            }
        }
        
        // Update Front, Right and Up Vectors using the updated Eular angles
        this->updateCameraVectors( );
    }
    
	/**
	* @brief  can be used to process mouse scroll
	* Processes input received from a mouse scroll-wheel event. 
	* Only requires input on the vertical wheel-axis
	* @return void
	*/
	void ProcessMouseScroll( float yOffset )
    {
        
    }
    
	/**
	* @brief  getter for zoom
	* @return floar - zoom
	*/
    float GetZoom( )
    {
        return this->zoom;
    }
    
	/**
	* @brief  getter for zoom
	* @return floar - zoom
	*/
    glm::vec3 GetPosition( )
    {
        return this->position;
    }
    
	/**
	* @brief  getter for front
	* @return glm::vec3 - front
	*/
    glm::vec3 GetFront( )
    {
        return this->front;
    }

	/**
	* @brief  getter for up
	* @return glm::vec3 - up
	*/
	glm::vec3 GetUp()
	{
		return this->up;
	}

	/**
	* @brief  setter for position
	* @param x - float, the X position
	* @param y - float, the Y position
	* @param z - float, the Z position
	* @return void
	*/
	void SetPostion(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
    
private:
    // Camera Attributes
	/// Camera position x,y,z
    glm::vec3 position;

	/// Camera front attributes x,y,z
    glm::vec3 front;

	/// Camera up attributes x,y,z
    glm::vec3 up;

	/// Camera right attributes x,y,z
    glm::vec3 right;

	/// World up attributes
    glm::vec3 worldUp;
    
    /// Eular Angles Yaw
    float yaw;

	/// Eular Angles Pitch
    float pitch;
    
    // Camera options
	/// Camera movement speed
    float movementSpeed;

	/// Camera rotation sensitivity
    float mouseSensitivity;

	/// Camera zoom attributes
    float zoom;
    
	/**
	* @brief  Calculates the front vector from the Camera's (updated) Eular Angles
	*
	* @return void
	*/
    void updateCameraVectors( )
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos( glm::radians( this->yaw ) ) * cos( glm::radians( this->pitch ) );
        front.y = sin( glm::radians( this->pitch ) );
        front.z = sin( glm::radians( this->yaw ) ) * cos( glm::radians( this->pitch ) );
        this->front = glm::normalize( front );
        // Also re-calculate the Right and Up vector
        this->right = glm::normalize( glm::cross( this->front, this->worldUp ) );  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        this->up = glm::normalize( glm::cross( this->right, this->front ) );
    }
};
