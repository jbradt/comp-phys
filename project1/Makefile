CXX=clang++

# FLAGS=-Wall -O2 -std=c++11
FLAGS=-Wall -O0 -std=c++11 -g -gdwarf-2

solve: solve.cpp
	$(CXX) $(FLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f solve
