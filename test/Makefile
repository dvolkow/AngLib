debug: test.cpp ../debug/anglib2.hpp
	g++ -std=c++11 -g3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -fdiagnostics-show-option test.cpp -o run_test
	./run_test
all: test.cpp ../debug/anglib.hpp
	g++ -O2 -std=c++11 -Wall -Wpedantic -Werror test.cpp -o run_test
demo:
	g++ -O2 -std=c++11 -Wall -Wpedantic -Werror sample.cpp -o run_test
	./run_test

