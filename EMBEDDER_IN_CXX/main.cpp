#define CXX_EMBED_ALL 1
#include "cxxembedder.hpp"


using namespace std;

void caller(){
    embed_language("python"){
       run("print('hi');");
    }
}


int main()
{
    caller();
    return 0;
}
