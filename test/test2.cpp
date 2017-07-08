#include "../debug/anglib.hpp"

using namespace anglib;

int main()
{
	Deg a(40);
	std::cout << a.toRad() << "\n";
	std::cout << sizeof(a) << "\n";

	Deg b(57, 17, 45.5101);
	std::cout << b.toRad() << "\n";
	std::cout << b << "\n";
	Deg c(57, 17, 45.5102);
	std::cout << c << "\n";

//	std::cin >> c;
//	std::cout << c << "\n";

	Hour h;
	std::cin >> h;
	std::cout << h << "\n";
}
