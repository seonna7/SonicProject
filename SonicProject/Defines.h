#pragma once

#define CREATE_SINGLE(classname)		\
private:								\
	classname() { }						\
public:									\
	static classname* GetInstance()		\
	{									\
		static classname s_instance;	\
		return &s_instance;				\
	}						

#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(ptr, msg)	  \
{								  \
assert(ptr != nullptr&&msg);	  \
delete ptr;						  \
ptr = nullptr;					  \
}								  \


#define PixelSize		3
