#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include "Python.h"
#pragma comment(lib , "./python3.lib")
#pragma comment(lib , "./python39.lib")


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
#define PY_SSIZE_T_CLEAN
#include <conio.h>
#include <iostream>
#include <string>
#include <filesystem>



using namespace std;
#define PYSRCDIR 

static PyObject* pModule;
static PyObject* pName;
static int i;
string file;



//set PATH to the script
inline int  __initialize_path(string path__) {
    
    /* This is a way to get the current directory of the notebook. */
    std::filesystem::path path = std::filesystem::current_path();
    std::string _path = path.string();
    /* A way to get the current directory of the notebook. */
    std::replace(_path.begin(), _path.end(), '\\', '/');
    try {
        PyRun_SimpleString("import sys");
    }
    catch (...) {
        cout << "cpp >> INITIALIZE with <Py_Initialize();> first\n";
        return -1;
    }
    PyRun_SimpleString((string("sys.path.append(\"") + _path + string(path__) + string("\")")).c_str());

    

    return 0;
}

#define START_PYTHON CPyInstance inst; __initialize_path("/python_libs/");
#define RUN_PYTHON(x) PyRun_SimpleString(#x);

#endif