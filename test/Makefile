debug: test.cpp ../debug/anglib.hpp
	g++ -std=c++11 -Wall -Wpedantic test.cpp -o run_test
all: test.cpp ../debug/anglib.hpp
	g++ -O2 -std=c++11 -Wall -Wpedantic -Werror test.cpp -o run_test
run:
	./run_test
demo:
	g++ -O2 -std=c++11 -Wall -Wpedantic -Werror sample.cpp -o run_test
	./run_test

