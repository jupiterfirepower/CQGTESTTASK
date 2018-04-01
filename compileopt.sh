!/bin/bash
g++ -std=c++1z -pipe -Wall -I . main.cpp matchengine.hpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine
#clang++-5.0 -std=c++1z -pipe -Wall -I ~/Documents/VSCODE main.cpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine