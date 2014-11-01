CXX = clang++
CXXFLAGS = -std=c++11 -Wall -g

all: asm.cc
	$(CXX) -o as $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -vf as
