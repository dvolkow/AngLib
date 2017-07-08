#include "../debug/anglib.hpp"

using anglib::Deg;
using anglib::Hour;
using anglib::Const::pi;

typedef Deg dint;
typedef Hour hint;

int main()
{
	//Test Deg class
	dint a; // -- define
	dint b = dint(pi.toRad()); 
	dint c = a + b + 3;
	dint d = a - b - 1;
	
	std::cout << "a = " << a << "\n";
	std::cout << "b = " << b << "\n";
	std::cout << "c = " << c << "\n";
	std::cout << "d = " << d << "\n";

	Deg init_test = {5,1,-20};
	std::cout << "init_test = " << init_test << "\n";

	dint e = b / 3;
	e = 3 / b;
	dint f = e * 3;
	f = 3 * e;
	dint g = a + (2 - b - c * 2 + d / 3) * 5;

	std::cout << "e = " << e << "\n";
	std::cout << "f = " << f << "\n";
	std::cout << "g = " << g << "\n";

	std::cout << "left and right ops test\n";
	std::cout << ((5 - f) == (f - 5)) << "\n";
	std::cout << "==: " << (pi == Deg(b.toRad())) << "\n";
	std::cout << "==: " << (pi == Deg(0)) << "\n";
	std::cout << "==: " << (pi == M_PI) << "\n";

	//Test Hour class
	hint k; // -- define
	hint l = hint(pi.toRad()); 
	hint m = k + l; 
	hint n = k - l;
	
	std::cout << "k = " << k << "\n";
	std::cout << "l = " << l << "\n";
	std::cout << "m = " << m << "\n";
	std::cout << "n = " << n << "\n";

	hint o = l / 3;
	o = 3 / l;
	hint p = o * 3;
	p = 3 * o;
	hint r = k + (2 - l - m * 2 + n / 3) * 5;

	std::cout << "o = " << o << "\n";
	std::cout << "p = " << p << "\n";
	std::cout << "r = " << r << "\n";

	std::cout << "left and right ops test\n";
	std::cout << ((5 - p) == (p - 5)) << "\n";
	std::cout << "==: " << (pi == Deg(l.toRad())) << "\n";

	std::cout << "\nCompare ops:\n";
	std::cout << "a > b ? " << (a > b) << "\n";
	std::cout << "a < b ? " << (a < b) << "\n";
	std::cout << "a > p ? " << (a > p) << "\n";
	std::cout << "a < p ? " << (a < p) << "\n";
	std::cout << "o < p ? " << (o < p) << "\n";
	std::cout << "o > p ? " << (o > p) << "\n";
	std::cout << "o < a ? " << (o < a) << "\n";
	std::cout << "o > a ? " << (o > a) << "\n";


	std::cout << "Basic test passed.\n\n";

	std::cout << "Test correct convert & construct: Deg\n";
	std::cout << "Radian = " << dint(1) << "\n";
	std::cout << "Radian = " << dint(1).toSec() << " sec\n";
	std::cout << "Radian = " << dint(1).toHour() << " hours\n";
	std::cout << "Radian = " << dint(1).toRad() << " rad\n";
	std::cout << "Radian = " << dint(1).toDeg() << " deg\n\n";

	std::cout << "Test correct convert & construct: Hour\n";
	std::cout << "Radian = " << hint(1) << "\n";
	std::cout << "Radian = " << hint(1).toSec() << " sec\n";
	std::cout << "Radian = " << hint(1).toHour() << " hours\n";
	std::cout << "Radian = " << hint(1).toRad() << " rad\n";
	std::cout << "Radian = " << hint(1).toDeg() << " deg\n";

	std::cout << "\nTest ops between different types:\n";
	std::cout << (c + p) << "\n" << (p + c) << "\n"; 
	std::cout << (c - p) << "\n" << (p - c) << "\n";

	std::cout << "\nAnother expressions:\n";
	std::cout << (a + 2 - 4 * o - (d * 4 - 2 / (o - b * 8)).toRad() + 0.2 * g - f * 0.45 - 1) << "\n";

//	std::cout << "\nNormalize:\n";
//	dint tst_normalize(-1005);
//	std::cout << tst_normalize << "\n";
//	tst_normalize.mod_2pi();
//	std::cout << tst_normalize << "\n";
//	tst_normalize.normalize();
//	std::cout << tst_normalize << "\n";
//	hint tst_normalize2(-105, 0, 25);
//	std::cout << tst_normalize2 << "\n";
//	tst_normalize2.mod_2pi();
//	std::cout << tst_normalize2 << "\n";
//	tst_normalize2.normalize();
//	std::cout << tst_normalize2 << "\n";
//
//	std::cout << "\nConstructors:\n";
//	Deg<short> tmp(b);
//	Deg<long long> ltmp(tmp);
//	std::cout << tmp << "\n" << b << "\n" << ltmp << "\n";
//	Deg<long> long_of_hour(o);
//	Hour<short> hour_of_deg(long_of_hour);
//	std::cout << long_of_hour << "\n" << o << "\n" << hour_of_deg << "\n";
	std::cout << "Second test passed.\n\n";

	std::cout << "Rumb = " << anglib::Const::rumb << "\n";
	std::cout << "Grad = " << anglib::Const::grad << "\n";
	std::cout << "Thousd(USSR) = " << anglib::Const::thousandy << "\n";
}
