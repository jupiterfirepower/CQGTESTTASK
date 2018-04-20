!/bin/bash
g++ -std=c++1z -pipe -Wall main.cpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine
#clang++-6.0 -std=c++1z -pipe -Wall -I . main.cpp matchengine.hpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine