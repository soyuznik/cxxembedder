#include "cxxembedder.hpp"
#include <iostream>

using namespace std;

void caller(){
    embed_language("lua"){
       run("print('andrei')");
    }
}


int main()
{
    caller();
    return 0;
}
