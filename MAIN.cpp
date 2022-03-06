
#define PY_SSIZE_T_CLEAN
#include <python/Python.h>
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;


int __callpy_noarg(string file, string funcptr) {
    PyObject* pName, * pModule, * pFunc;
    PyObject* pArgs, * pValue;
    int i;



    Py_Initialize();
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
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", funcptr);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", file);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;

    }
    return 0;
}
    
int main()
{
    int result = __callpy_noarg("pyemb3", "getInteger");
    cout << "__call exited with code -- " + std::to_string(result);
   
}