
#define PY_SSIZE_T_CLEAN
#include <python/Python.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
#define PYSRCDIR "/PythonSrc/"



/**
 * It calls a python function from C++
 * 
 * @param file The name of the python file to be executed. It should be located in PYSRCDIR dir
 * @param funcptr The name of the function to call.
 * 
 * @return The return value is the status.
 */
 int __callpy_noarg(string file, string funcptr) {
    PyObject* pName, * pModule, * pFunc;
    PyObject* pArgs, * pValue;
    int i;
   
    /* This is a way to get the current directory of the notebook. */
    std::filesystem::path path = std::filesystem::current_path();
    std::string _path = path.string();
    /* A way to get the current directory of the notebook. */
    std::replace(_path.begin(), _path.end(), '\\', '/');
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString((string("sys.path.append(\"") + _path + string(PYSRCDIR) + string("\")")).c_str());
    pName = PyUnicode_DecodeFSDefault(file.c_str());
    /* Error checking of pName left out */
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, funcptr.c_str());
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pValue = PyObject_CallObject(pFunc , NULL);
        }
        else {
            /* Checking if there is an error. If there is an error, it prints it out. */
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", funcptr);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", file.c_str());
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;

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
 int __callpy_warg(string file, string funcptr, vector<string>* args) {
     PyObject* pName, * pModule, * pFunc;
     PyObject* pArgs, * pValue;
     int i;
     /* This is a way to get the current directory of the notebook. */
     std::filesystem::path path = std::filesystem::current_path();
     std::string _path = path.string();
     /* A way to get the current directory of the notebook. */
     std::replace(_path.begin(), _path.end(), '\\', '/');
     Py_Initialize();
     PyRun_SimpleString("import sys");
     PyRun_SimpleString((string("sys.path.append(\"") + _path + string(PYSRCDIR) + string("\")")).c_str());
    
     pName = PyUnicode_DecodeFSDefault(file.c_str());
     /* Error checking of pName left out */

     pModule = PyImport_Import(pName);
     Py_DECREF(pName);

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
                 printf("Result of call: %ld\n", PyLong_AsLong(pValue));
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
         Py_DECREF(pModule);
     }
     else {
         PyErr_Print();
         fprintf(stderr, "Failed to load \"%s\"\n", file.c_str());
         return 1;
     }
     if (Py_FinalizeEx() < 0) {
         return 120;
     }
     return 0;
 }

/**
 * It calls the Python function `getInteger` from the `pyemb3` module.
 */
int main()
{
    vector<string> args;
    args.push_back("5");
    args.push_back("8");
    int result = __callpy_warg("pyemb2", "test", &args);
    cout << "__call exited with code --   " + std::to_string(result) << endl;
   
}