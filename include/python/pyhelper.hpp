#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include <python/Python.h>

#define IGNORE_EXCEPTIONS(stmt) \
try {                           \
  stmt ;                        \
} catch (...) {                 \
}
class CPyInstance
{
public:
	CPyInstance()
	{
		Py_Initialize();
	}

	~CPyInstance(){
		IGNORE_EXCEPTIONS(Py_Finalize());	
	}
};

#endif