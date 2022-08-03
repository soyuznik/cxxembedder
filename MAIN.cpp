#include "python/cxxembedder.hpp"
#include <iostream>

using namespace std;

void caller(){
    embed_language("python"){
       run_inline(print('hi'));
    }
}


int main()
{
    caller();
    return 0;
}
