BTL=-DBTL_SHORT_ON__ -DBTL_INT_ON__ -DBTL_LONG_ON__ -DBTL_LLONG_ON__ -DBTL_FLOAT_ON__ -DBTL_DOUBLE_ON__
all: smoke_test.cpp ../debug/anglib.hpp
	$(CXX) -std=c++14 -Wall -Wextra -pedantic -Wcast-align -fuse-ld=gold -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fsanitize=address -fstack-protector -fdiagnostics-show-option smoke_test.cpp -o run_test
	./run_test
clang_: smoke_test.cpp ../debug/anglib.hpp
	clang++ -std=c++14 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Winit-self -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fsanitize=address -fsanitize=undefined -fstack-protector -fdiagnostics-show-option smoke_test.cpp -o run_test
	./run_test
debug_gcc: smoke_test.cpp ../debug/anglib.hpp
	g++ -std=c++14 -g3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Werror -Wctor-dtor-privacy -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -fdiagnostics-show-option smoke_test.cpp -o run_test
	./run_test
test_gcc: test.cpp ../debug/anglib.hpp
	g++ -std=c++14 -g3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -fdiagnostics-show-option $(BTL) test.cpp -o run_test
	./run_test
test_clang: test.cpp ../debug/anglib.hpp
	clang++ -std=c++14 -g3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wdisabled-optimization -Wfloat-equal -Wformat=2 -Winit-self -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fsanitize=address -fsanitize=undefined -fstack-protector -fdiagnostics-show-option $(BTL) test.cpp -o run_test
	./run_test
