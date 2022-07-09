# Python pure scripting in C++

This project is about embedding             
python in C++ like it's part of              
it not just some random string             

For it to work you would probably
need python installed of course
and if you want to install more 
packages for the project
use 
* open cmd in root dir *
```
pip install --target=./python_libs <packagename>
```
in your cmd with the root dir.

to build you are going to need g++ 
* open cmd in root dir *
```
g++ -std=c++17 MAIN.cpp python_libs/python3.lib python_libs/python39.lib
```