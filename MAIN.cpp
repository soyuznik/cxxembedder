
#define PY_SSIZE_T_CLEAN
#include <python/Python.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <python/pyhelper.hpp>


using namespace std;
#define PYSRCDIR "/PythonSrc/"

PyObject* pName, * pModule, * pFunc;
PyObject* pArgs, * pValue;
int i;
string file;



namespace Keys {
    string     ADD = string{ '\ue025' };
    string     ALT = string{ '\ue00a' };
    string     ARROW_DOWN = string{ '\ue015' };
    string     ARROW_LEFT = string{ '\ue012' };
    string     ARROW_RIGHT = string{ '\ue014' };
    string     ARROW_UP = string{ '\ue013' };
    string     BACKSPACE = string{ '\ue003' };
    string     BACK_SPACE = string{ '\ue003' };
    string     CANCEL = string{ '\ue001' };
    string     CLEAR = string{ '\ue005' };
    string     COMMAND = string{ '\ue03d' };
    string     CONTROL = string{ '\ue009' };
    string     DECIMAL = string{ '\ue028' };
    string     DELETE = string{ '\ue017' };
    string     DIVIDE = string{ '\ue029' };
    string     DOWN = string{ '\ue015' };
    string     END = string{ '\ue010' };
    string     ENTER = string{ '\ue007' };
    string     EQUALS = string{ '\ue019' };
    string     ESCAPE = string{ '\ue00c' };
    string     F1 = string{ '\ue031' };
    string     F10 = string{ '\ue03a' };
    string     F11 = string{ '\ue03b' };
    string     F12 = string{ '\ue03c' };
    string     F2 = string{ '\ue032' };
    string     F3 = string{ '\ue033' };
    string     F4 = string{ '\ue034' };
    string     F5 = string{ '\ue035' };
    string     F6 = string{ '\ue036' };
    string     F7 = string{ '\ue037' };
    string     F8 = string{ '\ue038' };
    string     F9 = string{                     '\ue039'          };
    string     HELP = string{                     '\ue002'        };
    string     HOME = string{                  '\ue011'        };
    string     INSERT = string{               '\ue016'      };
    string     LEFT = string{                '\ue012'        };
    string     LEFT_ALT = string{                  '\ue00a'    };
    string     LEFT_CONTROL = string{                               '\ue009'};
    string     LEFT_SHIFT = string{                             '\ue008'  };
    string     META = string{                   '\ue03d'        };
    string     MULTIPLY = string{                '\ue024'    };
    string     NUMPAD0 = string{                          '\ue01a'     };
    string     NUMPAD1 = string{                          '\ue01b'     };
    string     NUMPAD2 = string{                          '\ue01c'     };
    string     NUMPAD3 = string{                          '\ue01d'     };
    string     NUMPAD4 = string{                          '\ue01e'     };
    string     NUMPAD5 = string{                          '\ue01f'     };
    string     NUMPAD6 = string{                          '\ue020'     };
    string     NUMPAD7 = string{                          '\ue021'     };
    string     NUMPAD8 = string{                          '\ue022'     };
    string     NUMPAD9 = string{                          '\ue023'     };
    string     PAGE_DOWN = string{              '\ue00f'   };
    string     PAGE_UP = string{               '\ue00e'     };
    string     PAUSE = string{              '\ue00b'       };
    string     RETURN = string{                '\ue006'      };
    string     RIGHT = string{                 '\ue014'       };
    string     SEMICOLON = string{                     '\ue018'   };
    string     SEPARATOR = string{             '\ue026'   };
    string     SHIFT = string{                      '\ue008'       };
    string     SPACE = string{                    '\ue00d'       };
    string     SUBTRACT = string{                  '\ue027'    };
    string     TAB = string{                   '\ue004'         };
    string     UP = string{                        '\ue013' };
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
    vec6->push_back(Keys::ENTER);
    __callpy_warg("type_ELEMENT", vec6);
    delete vec6;



   
}