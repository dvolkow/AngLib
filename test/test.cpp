#include "../debug/anglib.hpp"

using anglib::Deg;
using anglib::Hour;
using anglib::Const::pi;

typedef Deg<int> dint;
typedef Hour<int> hint;

int main()
{
	//Test Deg class
	dint a; // -- define
	dint b = dint(pi.toRad()); 
	dint c = a + b;
	dint d = a - b;
	
	std::cout << "a = " << a << "\n";
	std::cout << "b = " << b << "\n";
	std::cout << "c = " << c << "\n";
	std::cout << "d = " << d << "\n";

	dint e = b / 3;
	dint f = e * 3;
	dint g = a + (2 - b - c * 2 + d / 3) * 5;

	std::cout << "e = " << e << "\n";
	std::cout << "f = " << f << "\n";
	std::cout << "g = " << g << "\n";

	std::cout << "g.mod_2pi = " << g.mod_2pi<int>() << "\n";
	std::cout << "g.mod_2pi const = " << g << "\n";
	g.mod_2pi(); 
	std::cout << "g after nonconst = " << g << "\n";

	std::cout << "left and right ops test\n";
	std::cout << ((5 - f) == (f - 5)) << "\n";
	std::cout << "==: " << (pi == Deg<short>(b.toRad())) << "\n";

}
