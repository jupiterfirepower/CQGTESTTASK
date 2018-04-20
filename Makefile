
CXXFLAGS = -std=c++1z -Wall -pipe -I . main.cpp matchengine.hpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine

SOURCES=$(wildcard *.cpp)
BINARIES=$(patsubst %.cpp,bin/%,$(SOURCES))

    default: $(BINARIES)

bin/%:	%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

    clean:
	rm -f $(BINARIES)