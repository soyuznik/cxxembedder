#include "python/__CXX_EMBED_HELPER.hpp"
#include <iostream>

using namespace std;

void caller(){
    embed_language("python"){
       run("print('hi')");
    }
}


int main()
{
    caller();

    return 0;
}
