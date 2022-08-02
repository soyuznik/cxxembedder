#pragma once
//
//----- WARNING ----
//   ALWAYS INCLUDE THIS FILE FIRST
//   AND IF YOU START_PYTHON INSIDE A
//   FUNCTION ALWAYS INLINE IT
//   ELSE YOU WILL GET SOME RANDOM
//   ERRORS IN PYTHON HEADERS AND
//   YOU WILL START CRYING AND HAVE
//   NOT A SINGLE CLUE WHAT TO DO!!
//
//   ALSO IF YOU CANT COMPILE
//   BECAUSE OF FILESYSTEM UPDATE
//   C++ version to 17.
//   DEFINE PYSRCDIR AS THE DIR
//   WHERE ALL YOUR MODULES ARE
//   INSTALLED AND DONT FORGET
//   TO INCLUDE THE PYTHON .lib
//   and .dll
//
#include "./Python.h"
#define PYSRCDIR "python/LIBS/"
#define __CXXEMBEDDERcall  static inline
#define __CXXEMBEDDERdef  static
#define PY_SSIZE_T_CLEAN
#include <conio.h>
#include <iostream>
#include <string>
#include <algorithm>


#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

    #define IS_OS_WINDOWS 0
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#define IS_OS_WINDOWS 1
#include <direct.h>
// Microsoft wants us to use _getcwd instead of getcwd, which breaks POSIX
// compatibility. See the following link for more information:
// https://stackoverflow.com/questions/7582394/strdup-or-strdup
// Therefore we must disable the compiler warning if we want to use getcwd
// to maintain POSIX compatibility. This is accomplished with the following
// line.
#pragma warning(disable : 4996)
#endif



//set PATH to the script
__CXXEMBEDDERcall void  __initialize_path(std::string path__) {
    std::string _path;
/*-----ENTER LOCAL SCOPE*/{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL){
        std::cout << "[ERROR] Failed to get current working directory" << std::endl;
        std::cout << "FILE : " << __FILE__ << "/ LINE :" << __LINE__ <<std::endl;
        perror("getcwd() error");
    }
    _path = cwd;
/*------EXIT LOCAL SCOPE*/}

    std::replace(_path.begin(), _path.end(), '\\', '/');;
    try {
        PyRun_SimpleString("import sys");
    }
    catch (...){
        std::cout << "[ERROR] -> INITIALIZE START PYTHON FIRST !\n";
        return;
    };
    PyRun_SimpleString((std::string("sys.path.append(\"") + _path + std::string(path__) + std::string("\")")).c_str());



    return;
};
static std::string LANGUAGE;
class CXXEMBEDDERInstance
{
public:
    bool __run = true;

    __CXXEMBEDDERcall void __manage_run_call(std::string lang_code){
        if(LANGUAGE == "Python" || LANGUAGE == "python"){
            PyRun_SimpleString(lang_code.c_str());
        }
    }
    CXXEMBEDDERInstance(const std::string __argL)
	{
        LANGUAGE = __argL;
        if(LANGUAGE == "Python" || LANGUAGE == "python"){
             Py_Initialize();
              __initialize_path(PYSRCDIR);
        }
    };

    ~CXXEMBEDDERInstance(){
        if(LANGUAGE == "Python" || LANGUAGE == "python"){
             Py_Finalize();
        }
    };
};


#define create_scope(x) for(x)
#define CXXEMBEDDER_instance(x) __CXXEMBEDDERdef CXXEMBEDDERInstance INS = CXXEMBEDDERInstance(x); INS.__run; INS.__run = false
#define embed_language(x) create_scope(CXXEMBEDDER_instance(x))
#define embed_language_inscope(x) __CXXEMBEDDERdef CXXEMBEDDERInstance INS = CXXEMBEDDERInstance(x); INS.__run; INS.__run = false
/// START PYTHON BEFORE RUN_PYTHON           or          RUN_PYTHONI
///                   |(without inline)\           |(run python inline (I))
// CALL THIS ONLY IN "inline" FUNCTIONS!!!!
#define run(x) CXXEMBEDDERInstance::__manage_run_call(x);
#define run_inline(x) CXXEMBEDDERInstance::__manage_run_call(#x);


