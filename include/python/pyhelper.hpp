#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include <python/Python.h>


class CPyInstance
{
public:
	CPyInstance()
	{
		Py_Initialize();
	}

	~CPyInstance(){
		Py_Finalize();	
	}
};

#endif