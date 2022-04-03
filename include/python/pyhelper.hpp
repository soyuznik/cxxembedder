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
/**
 * It calls a python function from C++
 *
 * @param file The name of the python file to be executed. It should be located in PYSRCDIR dir
 * @param funcptr The name of the function to call.
 *
 * @return The return value is the status.
 */
inline int __callpy_noarg(string funcptr) {
    PyObject* pFunc;
    PyObject* pArgs, * pValue;
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, funcptr.c_str());
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pValue = PyObject_CallObject(pFunc, NULL);
        }
        else {
            /* Checking if there is an error. If there is an error, it prints it out. */
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", funcptr);
        }
        Py_XDECREF(pFunc);

    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", file.c_str());
        return 1;
    }

    return 0;
}
/**
 * It calls a Python function with args from C++.
 *
 * @param file The name of the python file to be executed.
 * @param funcptr The name of the function to call.
 * @param args A vector of strings that are the arguments to pass to the Python function.
 *
 * @return The return value is the status.
 */
inline int __callpy_warg(string funcptr, vector<string>* args) {
    PyObject* pFunc;
    PyObject* pArgs, * pValue;
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, funcptr.c_str());
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(args->size());
            for (i = 0; i < args->size(); ++i) {
                string str = args->at(i);
                pValue = PyUnicode_FromString(str.c_str());
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: ");
                PyObject_Print(pValue, stdout, 0);
                printf("\n");
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr, "Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", funcptr.c_str());
        }
        Py_XDECREF(pFunc);

    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", file.c_str());
        return 1;
    }

    return 0;
}
//calls py function and gets its arg
inline std::string __callpy_getarg(string funcptr) {
    PyObject* pFunc;
    PyObject* pValue;
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, funcptr.c_str());
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pValue = PyObject_CallObject(pFunc, NULL);
            if (pValue != NULL) {
                printf("Result of call: ");
                PyObject_Print(pValue, stdout, 0);
                printf("\n");
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr, "Call failed\n");
                
            }
        }
        else {
            /* Checking if there is an error. If there is an error, it prints it out. */
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", funcptr);
        }
        Py_XDECREF(pFunc);

    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", file.c_str());
       
    }

    return PyUnicode_AsUTF8(pValue);
}
#endif