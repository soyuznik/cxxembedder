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
#include "cxxembedder/python/Python.h"
#define PYSRCDIR "python/LIBS/"
///// LUA ///////
///  include headers /////
extern "C"{
#include "cxxembedder/lua-mingw64_v5.4.2/include/lua.h"
#include "cxxembedder/lua-mingw64_v5.4.2/include/lauxlib.h"
#include "cxxembedder/lua-mingw64_v5.4.2/include/lualib.h"
}
///////////////////////
#include <conio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

//angel script
namespace angelscript{
using std::string;
#include "cxxembedder/angelscript/include/angelscript.h"
int ExecuteString(asIScriptEngine *engine, const char *code, void *ref, int refTypeId, asIScriptModule *mod, asIScriptContext *ctx)
{
    // Wrap the code in a function so that it can be compiled and executed
    string funcCode = " ExecuteString() {\n";
    funcCode += code;
    funcCode += "\n;}";

    // Determine the return type based on the type of the ref arg
    funcCode = engine->GetTypeDeclaration(refTypeId, true) + funcCode;

    // GetModule will free unused types, so to be on the safe side we'll hold on to a reference to the type
    asITypeInfo *type = 0;
    if( refTypeId & asTYPEID_MASK_OBJECT )
    {
        type = engine->GetTypeInfoById(refTypeId);
        if( type )
            type->AddRef();
    }

    // If no module was provided, get a dummy from the engine
    asIScriptModule *execMod = mod ? mod : engine->GetModule("ExecuteString", asGM_ALWAYS_CREATE);

    // Now it's ok to release the type
    if( type )
        type->Release();

    // Compile the function that can be executed
    asIScriptFunction *func = 0;
    int r = execMod->CompileFunction("ExecuteString", funcCode.c_str(), -1, 0, &func);
    if( r < 0 )
        return r;

    // If no context was provided, request a new one from the engine
    asIScriptContext *execCtx = ctx ? ctx : engine->RequestContext();
    r = execCtx->Prepare(func);
    if (r >= 0)
    {
        // Execute the function
        r = execCtx->Execute();

        // Unless the provided type was void retrieve it's value
        if (ref != 0 && refTypeId != asTYPEID_VOID)
        {
            if (refTypeId & asTYPEID_OBJHANDLE)
            {
                // Expect the pointer to be null to start with
                assert(*reinterpret_cast<void**>(ref) == 0);
                *reinterpret_cast<void**>(ref) = *reinterpret_cast<void**>(execCtx->GetAddressOfReturnValue());
                engine->AddRefScriptObject(*reinterpret_cast<void**>(ref), engine->GetTypeInfoById(refTypeId));
            }
            else if (refTypeId & asTYPEID_MASK_OBJECT)
            {
                // Use the registered assignment operator to do a value assign.
                // This assumes that the ref is pointing to a valid object instance.
                engine->AssignScriptObject(ref, execCtx->GetAddressOfReturnValue(), engine->GetTypeInfoById(refTypeId));
            }
            else
            {
                // Copy the primitive value
                memcpy(ref, execCtx->GetAddressOfReturnValue(), engine->GetSizeOfPrimitiveType(refTypeId));
            }
        }
    }

    // Clean up
    func->Release();
    if( !ctx ) engine->ReturnContext(execCtx);

    return r;
}
int ExecuteString(asIScriptEngine *engine, const char *code, asIScriptModule *mod, asIScriptContext *ctx)
{
    return ExecuteString(engine, code, 0, asTYPEID_VOID, mod, ctx);
}
}//namespace angelscript

#define __CXXcall  static inline
#define __CXXdef  static
#define __CXXsdef  static inline
#define __CXXERROR(x)  std::cerr << x << std::endl;
#define PY_SSIZE_T_CLEAN


#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
    #define IS_OS_WINDOWS 0
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#define __IS_OS_WINDOWS 1
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

__CXXcall std::string __manage_lowercase_match(std::string data){
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return data;
}
#define __CXXmatch(x) __manage_lowercase_match(x)
///////////////////////////////////////////////////////////////////
/// header only global variables                              ////
//////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////


class CXXEInstance
{
private:
    __CXXsdef std::string LANGUAGE;
    __CXXsdef lua_State *LuaInstance;
    __CXXsdef angelscript::asIScriptEngine *engine;
    __CXXsdef angelscript::asIScriptContext *ctx;
public:
    bool __run = true;
    __CXXcall void __manage_run_call(std::string __raw_string_literal){
        if(__CXXmatch(LANGUAGE) == "python"){
            int handle = PyRun_SimpleString(__raw_string_literal.c_str());
            if(handle != 0){ //failure
                __CXXERROR("[ERROR] Python exception")
                __CXXERROR("FILE : " << __FILE__ << " / LINE :" << __LINE__ )
                __CXXERROR("PyRun_SimpleString() error");
            }
        }
        if(__CXXmatch(LANGUAGE) == "lua"){
            int handle = luaL_dostring(LuaInstance, __raw_string_literal.c_str());
            if(handle != LUA_OK){
                __CXXERROR("[ERROR] " << lua_tostring(LuaInstance , -1))
                __CXXERROR("FILE : " << __FILE__ << " / LINE :" << __LINE__)
                __CXXERROR("luaL_dostring() error");
            }
        }
        if(__CXXmatch(LANGUAGE) == "angelscript"){
            //int ExecuteString(asIScriptEngine *engine, const char *code, void *ret, int retTypeId, asIScriptModule *mod = 0, asIScriptContext *ctx = 0);
            int handle = angelscript::ExecuteString(engine , __raw_string_literal.c_str() ,  NULL , ctx);
            if(handle != 0){
                __CXXERROR("[ERROR] handle: " << handle)
                __CXXERROR("FILE : " << __FILE__ << " / LINE :" << __LINE__)
                __CXXERROR("angelscript ExecuteString() error");
                const angelscript::asIScriptFunction *function = ctx->GetExceptionFunction();
                // Determine the exception that occurred
                std::string exception = ctx->GetExceptionString();
                if(exception.empty()){
                    exception = "Syntax error";
                }
                __CXXERROR(std::string("description: ") + exception                                 );
                __CXXERROR(std::string("function: ") + function->GetDeclaration()                   );
                __CXXERROR(std::string("module: ") + function->GetModuleName()                      );
                __CXXERROR(std::string("section: ") + function->GetScriptSectionName()              );
                __CXXERROR(std::string("line: ") + std::to_string(ctx->GetExceptionLineNumber())    );
            }
        }

    }
    CXXEInstance(const std::string __argL)
	{
        LANGUAGE = __argL;
        if(__CXXmatch(LANGUAGE) == "python"){
             Py_Initialize(); // create scope instance
             py__initialize_path(PYSRCDIR);
        }
        if(__CXXmatch(LANGUAGE) == "lua"){
           LuaInstance = luaL_newstate(); // create instance
           luaL_openlibs(LuaInstance);
        }
        if(__CXXmatch(LANGUAGE) == "angelscript"){
            // Create the script engine
            engine = angelscript::asCreateScriptEngine();
            ctx = engine->CreateContext();

        }
    };

    ~CXXEInstance(){
        if(__CXXmatch(LANGUAGE) == "python"){
             Py_Finalize();
        }
        if(__CXXmatch(LANGUAGE) == "angelscript"){
             ctx->Release();
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
#define run(...) CXXEInstance::__manage_run_call(__VA_ARGS__);
#define run_inline(...) CXXEInstance::__manage_run_call(#__VA_ARGS__);


