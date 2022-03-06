
#define PY_SSIZE_T_CLEAN
#include <python/Python.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
#define PYSRCDIR "/PythonSrc/"

PyObject* pName, * pModule, * pFunc;
PyObject* pArgs, * pValue;
int i;
string file;

namespace Keys {
   char     ADD = '\ue025'         ;
   char     ALT = '\ue00a'         ;
   char     ARROW_DOWN = '\ue015'  ;
   char     ARROW_LEFT = '\ue012'  ;
   char     ARROW_RIGHT = '\ue014' ;
   char     ARROW_UP = '\ue013'    ;
   char     BACKSPACE = '\ue003'   ;
   char     BACK_SPACE = '\ue003'  ;
   char     CANCEL = '\ue001'      ;
   char     CLEAR = '\ue005'       ;
   char     COMMAND = '\ue03d'     ;
   char     CONTROL = '\ue009'     ;
   char     DECIMAL = '\ue028'     ;
   char     DELETE = '\ue017'      ;
   char     DIVIDE = '\ue029'      ;
   char     DOWN = '\ue015'        ;
   char     END = '\ue010'         ;
   char     ENTER = '\ue007'       ;
   char     EQUALS = '\ue019'      ;
   char     ESCAPE = '\ue00c'      ;
   char     F1 = '\ue031'          ;
   char     F10 = '\ue03a'         ;
   char     F11 = '\ue03b'         ;
   char     F12 = '\ue03c'         ;
   char     F2 = '\ue032'          ;
   char     F3 = '\ue033'          ;
   char     F4 = '\ue034'          ;
   char     F5 = '\ue035'          ;
   char     F6 = '\ue036'          ;
   char     F7 = '\ue037'          ;
   char     F8 = '\ue038'          ;
   char     F9 = '\ue039'          ;
   char     HELP = '\ue002'        ;
   char     HOME = '\ue011'        ;
   char     INSERT = '\ue016'      ;
   char     LEFT = '\ue012'        ;
   char     LEFT_ALT = '\ue00a'    ;
   char     LEFT_CONTROL = '\ue009';
   char     LEFT_SHIFT = '\ue008'  ;
   char     META = '\ue03d'        ;
   char     MULTIPLY = '\ue024'    ;
   char     NUMPAD0 = '\ue01a'     ;
   char     NUMPAD1 = '\ue01b'     ;
   char     NUMPAD2 = '\ue01c'     ;
   char     NUMPAD3 = '\ue01d'     ;
   char     NUMPAD4 = '\ue01e'     ;
   char     NUMPAD5 = '\ue01f'     ;
   char     NUMPAD6 = '\ue020'     ;
   char     NUMPAD7 = '\ue021'     ;
   char     NUMPAD8 = '\ue022'     ;
   char     NUMPAD9 = '\ue023'     ;
   char     PAGE_DOWN = '\ue00f'   ;
   char     PAGE_UP = '\ue00e'     ;
   char     PAUSE = '\ue00b'       ;
   char     RETURN = '\ue006'      ;
   char     RIGHT = '\ue014'       ;
   char     SEMICOLON = '\ue018'   ;
   char     SEPARATOR = '\ue026'   ;
   char     SHIFT = '\ue008'       ;
   char     SPACE = '\ue00d'       ;
   char     SUBTRACT = '\ue027'    ;
   char     TAB = '\ue004'         ;
   char     UP = '\ue013'          ;
}

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
     
     return 0;
 }

/**
 * It calls the Python function `getInteger` from the `pyemb3` module.
 */
int main()
{
    Py_Initialize();// ENTRY PYTHON


    __initialize_path("pyemb3");
    std::vector<string>* vec1 = new std::vector<string>;
    vec1->push_back(" ");
    __callpy_warg("init_selenium", vec1);
    delete vec1;

    std::vector<string>* vec2 = new std::vector<string>;
    vec2->push_back("https://www.google.com/");
    __callpy_warg("get_search", vec2);
    delete vec2;

    ///html/body/div[1]/div[3]/form/div[1]/div[1]/div[1]/div[1]/div/div[2]/input

    std::vector<string>* vec3 = new std::vector<string>;
    vec3->push_back("/html/body/div[1]/div[3]/form/div[1]/div[1]/div[1]/div[1]/div/div[2]/input");
    __callpy_warg("get_elem_XPATH", vec3);
    delete vec3;

    std::vector<string>* vec4 = new std::vector<string>;
    vec4->push_back("0");
    __callpy_warg("click_ELEMENT", vec4);
    delete vec4;

    Py_Finalize(); // EXIT PYTHON
    
   
}