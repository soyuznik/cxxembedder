
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
 * @param file The name of the python file to be executed. It should be located in CURRENTDIR/Scripts
 * @param funcptr The name of the function to call.
 * 
 * @return The return value is the return value of the function that is being called.
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
 * It calls the Python function `getInteger` from the `pyemb3` module.
 */
int main()
{
    int result = __callpy_noarg("pyemb3", "getInteger");
    cout << "__call exited with code --   " + std::to_string(result) << endl;
   
}