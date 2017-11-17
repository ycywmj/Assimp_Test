#pragma once

// reference: https://www.codeproject.com/Articles/1921/Singleton-Pattern-its-implementation-with-C

/**
* @class Singleton
* @brief Singleton class for general usage
*
* @author Kin Pan Mak
* @version 01
* @date 01/09/2017
*
*
*/
template <class T>
class Singleton{
public:
	/**
	* @brief  get the pointer static instance of the object
	* @return pointer instance of the object
	*/
	static T* Instance(){
		if (!instance_flag){
			ret = new T();
			instance_flag = true;
			return ret;
		}
		else{
			return ret;
		}
	};

private:
	/**
	* @brief  ctor hidden
	*/
	Singleton();

	/**
	* @brief  dtor hidden
	*/
	~Singleton(){ instance_flag = false; };

	/**
	* @brief  copy ctor hidden
	* @param object copy
	*/
	Singleton(Singleton const&);

	/**
	* @brief  assignment operator hidden
	* @param object assign to
	*/
	Singleton& operator = (Singleton const&);

	/// true if the object is already created
	static bool instance_flag;

	/// member object
	static T* ret;
};

template <class T>
bool Singleton<T>::instance_flag = false;

template <class T>
T* Singleton<T>::ret = 0;
