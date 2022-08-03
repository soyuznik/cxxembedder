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
#include "cxxembedder/Python.h"
#define PYSRCDIR "python/LIBS/"


///// LUA ///////
///  include headers /////
extern "C"{

////////////////////
///
///   should add python x32 or x64 (need to check)
///   for lua i should add x32 as right now only x64
///
///
#include "cxxembedder/lua-mingw64_v5.4.2/include/lua.h"
#include "cxxembedder/lua-mingw64_v5.4.2/include/lauxlib.h"
#include "cxxembedder/lua-mingw64_v5.4.2/include/lualib.h"
}
#ifdef _WIN32
#pragma comment(lib , "cxxembeddder/_cxxlib/liblua53.a")
#endif

///////////////////////
#include <conio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>


#define __CXXcall  static inline
#define __CXXdef  static
#define __CXXERROR(x)  std::cerr << x << std::endl;
#define PY_SSIZE_T_CLEAN


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



//set PATH to the script // this is for the modules python installs // __path is the location of the modules
__CXXcall void  py__initialize_path(std::string path__) {
    std::string _path;
/*-----ENTER LOCAL SCOPE*/{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL){
        __CXXERROR("[ERROR] Failed to get current working directory")
        __CXXERROR("FILE : " << __FILE__ << " / LINE :" << __LINE__ )
        __CXXERROR("getcwd() error");
    }
    _path = cwd;
/*------EXIT LOCAL SCOPE*/}

    std::replace(_path.begin(), _path.end(), '\\', '/');;
    try {
        PyRun_SimpleString("import sys");
    }
    catch (...){
        __CXXERROR("[ERROR] : Python isnt initialized")
        __CXXERROR("FILE : " << __FILE__ << " / LINE :" << __LINE__)
        return;
    };
    PyRun_SimpleString((std::string("sys.path.append(\"") + _path + std::string(path__) + std::string("\")")).c_str());



    return;
};
///////////////////////////////////////////////////////////////////
/// header only global variables                              ////
//////////////////////////////////////////////////////////////////
__CXXdef std::string LANGUAGE;
__CXXdef lua_State *LuaInstance;
/////////////////////////////////////////////////////////////////


class CXXEInstance
{
public:
    bool __run = true;
    __CXXcall void __manage_run_call(std::string __raw_string_literal){
        if(LANGUAGE == "Python" || LANGUAGE == "python"){
            int handle = PyRun_SimpleString(__raw_string_literal.c_str());
            if(handle != 0){ //failure
                __CXXERROR("[ERROR] Python exception")
                __CXXERROR("FILE : " << __FILE__ << " / LINE :" << __LINE__ )
                __CXXERROR("PyRun_SimpleString() error");
            }
        }
        if(LANGUAGE == "Lua" || LANGUAGE == "lua"){
            int handle = luaL_dostring(LuaInstance, __raw_string_literal.c_str());
            if(handle != LUA_OK){
                __CXXERROR("[ERROR] " << lua_tostring(LuaInstance , -1))
                __CXXERROR("FILE : " << __FILE__ << " / LINE :" << __LINE__)
                __CXXERROR("luaL_dostring() error");
            }
        }
    }
    CXXEInstance(const std::string __argL)
	{
        LANGUAGE = __argL;
        if(LANGUAGE == "Python" || LANGUAGE == "python"){
             Py_Initialize(); // create scope instance
             py__initialize_path(PYSRCDIR);
             delete LuaInstance;
        }
        if(LANGUAGE == "Lua" || LANGUAGE == "lua"){
           LuaInstance = luaL_newstate(); // create instance
           luaL_openlibs(LuaInstance);



        }
    };

    ~CXXEInstance(){
        if(LANGUAGE == "Python" || LANGUAGE == "python"){
             Py_Finalize();
        }
    };
};

#define create_scope(x) for(x)
#define __CXXInstance(x) __CXXdef CXXEInstance INS = CXXEInstance(x); INS.__run; INS.__run = false
#define embed_language(x) create_scope(__CXXInstance(x))
#define embed_language_inscope(x) __CXXdef CXXEInstance INS = CXXEInstance(x); INS.__run; INS.__run = false


/// START PYTHON BEFORE RUN_PYTHON           or          RUN_PYTHONI
///                   |(without inline)\           |(run python inline (I))
// CALL THIS ONLY IN "inline" FUNCTIONS!!!!
#define run(x) CXXEInstance::__manage_run_call(x);
#define run_inline(x) CXXEInstance::__manage_run_call(#x);


