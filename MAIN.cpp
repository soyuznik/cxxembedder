#define PY_SSIZE_T_CLEAN
#include <python/Python.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <python/pyhelper.hpp>


using namespace std;
#define PYSRCDIR "/PythonSrc/"

PyObject* pModule;
PyObject* pName;
int i;
string file;




inline int  __initialize_path(string __file) {
    file = __file;
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
    PyRun_SimpleString((string("sys.path.append(\"") + _path + string(PYSRCDIR) + string("\")")).c_str());

    pName = PyUnicode_DecodeFSDefault(file.c_str());
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

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
    PyObject  *pFunc;
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

/**
 * It calls the Python function `getInteger` from the `pyemb3` module.
 */
int main()
{
    CPyInstance inst;

    __initialize_path("pyemb3");

    std::vector<string>* vec1 = new std::vector<string>;
    vec1->push_back(" ");
    __callpy_warg("init_selenium", vec1);
    delete vec1;

    std::vector<string>* vec2 = new std::vector<string>;
    vec2->push_back("https://www.google.com/");
    __callpy_warg("get_search", vec2);
    delete vec2;

    std::vector<string>* vec3 = new std::vector<string>;
    vec3->push_back("q");
    __callpy_warg("get_elem_NAME", vec3);
    delete vec3;

    std::vector<string>* vec4 = new std::vector<string>;
    vec4->push_back("0");
    __callpy_warg("click_ELEMENT", vec4);
    delete vec4;


    std::vector<string>* vec5 = new std::vector<string>;
    vec5->push_back("0");
    vec5->push_back("HELLO");
    __callpy_warg("type_ELEMENT", vec5);
    delete vec5;

    std::vector<string>* vec6 = new std::vector<string>;
    vec6->push_back("0");
    vec6->push_back("u/ENTER");
    __callpy_warg("type_ELEMENT", vec6);
    delete vec6;




}