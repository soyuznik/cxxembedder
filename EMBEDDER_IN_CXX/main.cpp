#include "cxxembedder.hpp"


using namespace std;

void caller(){
    embed_language("angelscript"){
       run("int i = -1;");
    }
}


int main()
{
    caller();
    return 0;
}
