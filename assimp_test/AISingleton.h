#ifndef __AISINGLETON_H
#define __AISINGLETON_H
#if _MCS_VER >= 1020
#pragma once
#endif

/**
* @class AISingleton
* @brief Singleton class particularly for AI usage
*
* @author ChengYu Yang
* @version 01
* @date 15/10/2017
*
*
*/
template <class T>
class singleton
{
public:
	/**
	* @brief  get the static instance of the object
	* @return instance of the object
	*/
	static T& Instance() {
		static T _instance;
		return _instance;
	}
private:
	/**
	* @brief  ctor hidden
	*/
	singleton();

	/**
	* @brief  dtor hidden
	*/
	~singleton();

	/**
	* @brief  copy ctor hidden
	* @param object copy
	*/
	singleton(singleton const&);
	
	/**
	* @brief  assignment operator hidden
	* @param object assign to
	*/
	singleton& operator=(singleton const&);
};

#endif