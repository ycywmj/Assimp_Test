#ifndef __AISINGLETON_H
#define __AISINGLETON_H
#if _MCS_VER >= 1020
#pragma once
#endif
template <class T>
class singleton
{
public:
	static T& Instance() {
		static T _instance;
		return _instance;
	}
private:
	singleton();          // ctor hidden
	~singleton();          // dtor hidden
	singleton(singleton const&);    // copy ctor hidden
	singleton& operator=(singleton const&);
};

#endif