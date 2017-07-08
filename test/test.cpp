#include "../debug/anglib.hpp"
#include <cassert>

using anglib::Deg;
using anglib::Hour;
using anglib::Const;

int main()
{
	//--1. Конструкторы
	Deg dg; 
	Deg dg1(1);
	Deg dg2(-1.5);
	Deg dg3 = {3};
	Deg dg4 = {3, 300, -100};

	Hour hr;
	Hour hr1(1);
	Hour hr2(-1.5);
	Hour hr3 = {3};
	Hour hr4 = {3, 300, -100};

	Deg dg_a(hr1);
	assert(dg_a == hr1);

	Hour hr_a(dg3);
	assert(hr_a == dg3);

	//--2. Приведения
	short sh_a = hr_a;
	int i_a = hr1;
	long l_a = hr2;
	long long ll_a = hr4;
	float f_a = hr;

	sh_a = dg3;
	i_a = dg2;
	l_a = dg;
	ll_a = dg4;
	f_a = dg2;

	dg = sh_a;
	dg = i_a;
	dg = l_a;
	dg = ll_a;
	dg = f_a;

	std::cout << "Smoke test passed!\n"; 
}
