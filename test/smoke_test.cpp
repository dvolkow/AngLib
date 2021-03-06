//#include <my_dev/anglib.hpp>

#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <map>
#include <set>
#include "../debug/anglib.hpp"

using anglib::Const;// Угол в 180 градусов
using anglib::Deg; // Тип для хранения градусного представления
using anglib::Hour; // Тип для хранения часового предствления

using std::unordered_set;
using std::unordered_map;
using std::map;
using std::set;
using std::unordered_multiset;
using std::unordered_multimap;
using std::multimap;
using std::multiset;
using std::priority_queue;

void println();

int main()
{
	Deg zero; // -- по-умолчанию, нулевой угол
	Hour hzero;

	std::cout << zero << "\n"; // -- можно выводить так
	std::cout << hzero << "\n";

	std::cout << "size Deg zero: " << sizeof(zero) << "\n";
	std::cout << "size Hout hzero: " << sizeof(hzero) << "\n";

	//--Конструктор от арифметического типа, приводящегося
	//--к double, порождает угол с радианной мерой, равной
	//--значению в double, к которому привелся тип.
	Deg radian(1); //  -- угол в один радиан
	Hour hradian(1);

//	Deg test('a'); //--THIS IS NOT COMPILE!
//	Hour test('a', 0, 'd'); //--THIS IS NOT COMPILE!
//	std::cout << test << "\n";

	std::cout << radian << "\n";
	std::cout << hradian << "\n";

	//--Конструктор от списка: два значения одинаковых целых
	//--арифметических типов, и double.
	Deg a(0, 1, 2.08); // -- угол 1' 2.08"
	Hour ha(0, 1, 2.08); // -- угол 1m 2.08s

	std::cout << a << "\n";
	std::cout << ha << "\n";

	Deg b(-15, 300, -61); // -- такой список будет коррект-
							 // -- но обработан согласно ариф-
							 // -- метике -15g + 300' - 61",
							 // -- что может быть использовано
							 // -- в вычислениях с сильно отли-
							 // -- чающимися по порядку значе-
							 // -- ниями
	Hour hb(-15, 300, -61);  // -- аналогично для Hour

	std::cout << b << "\n";
	std::cout << hb << "\n";

	//--Копирующий конструктор от любой допустимой параметриза-
	//--ции:
	Deg c(a); // -- Deg (c) != Deg (a) в смысле ти-
				   // -- пов, но можно приводить один к другому:
	Deg d = c;

	std::cout << c << "\n";
	std::cout << d << "\n";

	Hour hc(ha);
	Hour hd = hc;

	d = hc, hd = c; // -- допустимы и такие приведения, разве не
					// -- здорово?!)

	std::cout << c << "\n";
	std::cout << d << "\n";
	std::cout << hc << "\n";
	std::cout << hd << "\n";
	println();

	//--Сравнение углов 
	Deg da1(180, 1, 0), da2(180, 0, 0.899);
	Hour ha1(24, 1, 0), ha2(24, 0, 0.899);

	std::cout << "da1: " << da1 << "\n" << "da2: " << da2 << "\n"
			  << "ha1: " << ha1 << "\n" << "ha2: " << ha2 << "\n";   
								// -- обратите внимание, что
								// -- для нормального приоритета
								// -- операции между << ставим 
								// -- скобки:
	std::cout << "da1 < da2 ? " << (da1 < da2) << "\n"; 
	std::cout << "da1 > da2 ? " << (da1 > da2) << "\n"; 
	std::cout << "da1 == da2 ? " << (da1 == da2) << "\n"; 
	std::cout << "da1 != da2 ? " << (da1 != da2) << "\n"; 
								// -- аналогично для часовых мер
	std::cout << "ha1 < ha2 ? " << (ha1 < ha2) << "\n"; 
	std::cout << "ha1 > ha2 ? " << (ha1 > ha2) << "\n"; 
	std::cout << "ha1 == ha2 ? " << (ha1 == ha2) << "\n"; 
	std::cout << "ha1 != ha2 ? " << (ha1 != ha2) << "\n"; 
								// -- возможны сравнения в разных
								// -- мерах: 
	std::cout << "da1 < ha1 ? " << (da1 < ha2) << "\n"; 
	std::cout << "da2 > ha2 ? " << (ha1 > da2) << "\n"; 
	std::cout << "ha1 == da1 ? " << (da1 == ha2) << "\n"; 
	std::cout << "ha1 != da1 ? " << (da1 != ha1) << "\n"; 
	println();
								

	//--Арифметика 

	//--Допустимо складывать углы в различных мерах и вычитать их
	//--друг из друга:						
	std::cout << "radian + radian = " << (radian + radian) << "\n";
	std::cout << "radian - radian = " << (radian - radian) << "\n";

	//----ВАЖНО!
	//--Если складываются два угла в различных мерах, то тип резу-
	//--льтата определяется ЛЕВЫМ операндом. Например, ниже вывод
	//--будет в часах:
	std::cout << "ha1 + da1 = " << (ha1 + da1) << "\n";
	std::cout << "ha1 - da1 = " << (ha1 - da1) << "\n";
	std::cout << "da2 + ha1 = " << (da2 + ha1) << "\n";
	std::cout << "da2 - ha1 = " << (da2 - ha1) << "\n";
	println();

	//--Углы можно умножать и делить на числовые типы, и обратно:
	std::cout << "radian * 3.14 = " << (radian * 3.14) << "\n";
	std::cout << "PI * radian = " << (M_PI * radian) << "\n";
	std::cout << "radian / 2 * PI = " << (M_PI * radian / 2) << "\n";
	//--При делении числа на угол происходит преобразование число-
	//--вого типа в угловой, т.е. подразумевается, что делят угол в
	//--радианной мере:
	std::cout << "1 / radian = " << (1 / radian) << "\n"; 
	std::cout << "PI / 360deg = " << (M_PI / Deg(360, 0, 0)) << "\n"; 
	//--Углы можно делить друг на друга. Результат double:
	std::cout << "ha1 / ha2 = " << (ha1 / ha2) << "\n"; 
	std::cout << "da2 / ha1 = " << (da1 / ha1) << "\n"; 
	println();
	

	//--При операциях с числовыми типами происходят аналогичные 
	//--преобразования числовых типов в углы:
	std::cout << "ha1 + 1 = " << (ha1 + 1) << "\n";
	std::cout << "1 + radian = " << (1 + radian) << "\n";
	std::cout << "PI + da1 = " << (M_PI + da1) << "\n";
	std::cout << "da2 - PI/2 = " << (da2 - M_PI/2) << "\n";
	println();

	//--Приведения углов
	
	//--Можно приводить углы к заданному диапазону значений
	//--Функция-член mod_2pi приводит значение угла к проме-
	//--жутку [-360, 360] (или [-24, 24]):
	//----ВНИМАНИЕ! функция изменяет состояние класса
	Deg ten_rad(100*radian);
	Hour hten_rad(100*radian);
//	std::cout << "100 rad: " << ten_rad << "\n";
//	std::cout << "100 rad: " << hten_rad << "\n";
//	ten_rad.mod_2pi();
//	hten_rad.mod_2pi();
//	std::cout << "reduce 100 rad: " << ten_rad << "\n";
//	std::cout << "reduce 100 rad: " << hten_rad << "\n";
//	println();

	//--Можно узнать число оборотов с помощью константной 
	//--параметризованной функцией:
	ten_rad = 100 * radian;
	hten_rad = 100 * radian;
//	std::cout << "In 100 rad: " << ten_rad.mod_2pi<int>() << " circles\n";
//	std::cout << "In 100 rad: " << hten_rad.mod_2pi<int>() << " circles\n";
//	println();

	//--Нормализация к виду положительного, меньше 2pi ра-
	//--диан угла:
	Deg denormalize_angle = Deg(-275,0,0);
	Hour hdenormalize_angle = Hour(-15,-25,-34);
//	std::cout << "Not normalize angle: " << denormalize_angle << "\n";
//	std::cout << "Not normalize angle(h): " << hdenormalize_angle << "\n";
//
//	denormalize_angle.normalize();
//	hdenormalize_angle.normalize();
//	std::cout << "Normalize angle: " << denormalize_angle << "\n";
//	std::cout << "Normalize angle(h): " << hdenormalize_angle << "\n";
//	println();

	//--Операторы ввода
//	std::cout << "Input your angle (deg min sec): \n";
	
//	Deg in_d;
//	Hour in_h;
//	std::cin >> in_d;
//	std::cout << in_d << "\n";

//	std::cout << "Input your angle (hour m s): \n";
//	std::cin >> in_h;
//	std::cout << in_h << "\n";

	//--Операторы типа +=:
	std::cout << "Other ops (type +=): \n";
	ha1 += 1;

	std::cout << "da1: " << da1 << "\n";
	da1 += 1;
	std::cout << "da1 += ha1: " << da1 << "\n";
	short a1 = 1;
	int b1 = 1;
	long c1 = 1;
	long long d1 = 1;
	float f1 = 1;
	double e1 = 1;
	a1 -= da1;
	b1 -= da1;
	c1 -= da1;
	d1 -= da1;
	f1 -= da1;
	e1 -= da1;
	std::cout << "1 -= da1: " << a1 << "\n";
	std::cout << "1 -= da1: " << b1 << "\n";
	std::cout << "1 -= da1: " << c1 << "\n";
	std::cout << "1 -= da1: " << d1 << "\n";
	std::cout << "1 -= da1: " << f1 << "\n";
	std::cout << "1 -= da1: " << e1 << "\n";

//	if (f1)
//		std::cout << "lol!\n";
//
//	da1 = ha1 - 'd'; // --  NOT COMPILE!

	Deg tmp_pi = Const::PI();
	tmp_pi *= 2;
	std::cout << "pi *= 2: " << tmp_pi << "\n";
	tmp_pi /= 4;
	std::cout << "pi /= 2: " << tmp_pi << "\n";
	println();

	std::cout << "INC:\n";
	std::cout << "tmp_pi: " << tmp_pi << "\n";
	std::cout << "tmp_pi++: " << ++tmp_pi << "\n";
	println();
	std::cout << "DEC:\n";
	std::cout << "tmp_pi: " << tmp_pi << "\n";
	std::cout << "--tmp_pi:" << --tmp_pi << "\n";
	println();

	//--Унaрные операторы:
	-a;
	ha1 = -da2 + (++ha2);

	Hour hpi = Const::PI();
	std::cout << hpi << "\n";

	// -- Ordered containers 
	set<Deg> dset;
	set<Hour> hrset;

	dset.insert(da1);
	dset.insert(da2);
	dset.insert(da2);
	std::cout  << dset.count(da1) << " " << dset.count(da2) << "\n";

	hrset.insert(da1);
	hrset.insert(da2);
	hrset.insert(da2);
	std::cout  << hrset.count(da1) << " " << hrset.count(da2) << "\n";
	
	multiset<Deg> dmset;
	multiset<Hour> hmrset;

	dmset.insert(da1);
	dmset.insert(da2);
	dmset.insert(da2);
	std::cout  << dmset.count(da1) << " " << dmset.count(da2) << "\n";

	hmrset.insert(da1);
	hmrset.insert(da2);
	hmrset.insert(da2);
	std::cout  << hmrset.count(da1) << " " << hmrset.count(da2) << "\n";

	map<Deg, int> degmap;
	map<Hour, int> hourmap;
	
	degmap.insert(std::make_pair(da1, 2));
	hourmap.insert(std::make_pair(da1, 2));
	hourmap.insert(std::make_pair(da2, 2));

	multimap<Deg, int> degmmap;
	multimap<Hour, int> hourmmap;
	
	degmmap.insert(std::make_pair(da1, 2));
	hourmmap.insert(std::make_pair(da2, 2));
	hourmmap.insert(std::make_pair(da2, 4));
	std::cout  << degmmap.count(da1) << " " << hourmmap.count(da2) << "\n";

	priority_queue<Deg> degqu;
	priority_queue<Hour> hourqu;

	degqu.push(da1);
	degqu.push(da2);
	degqu.push(ha2);
	degqu.push(ha1);
	hourqu.push(ha1);
	hourqu.push(ha2);
	hourqu.push(da2);
	hourqu.push(da1);

	std::cout << std::less_equal<Deg>()(ha1, ha2) << "\n";
	// -- Unordered containers
	unordered_set<Deg> degset;
	unordered_set<Hour> hourset;

	degset.insert(da1);
	degset.insert(da1);
	degset.insert(ha1);
	hourset.insert(ha1);
	hourset.insert(ha1);
	hourset.insert(da1);

	unordered_multiset<Deg> degumset;
	unordered_multiset<Hour> hourumset;

	degumset.insert(da1);
	degumset.insert(da1);
	degumset.insert(ha1);
	hourumset.insert(ha1);
	hourumset.insert(ha1);
	hourumset.insert(da1);
	
	unordered_map<Deg, int> degumap;
	unordered_map<Hour, int> hourumap;

	degumap.insert(std::make_pair(da1, 2));
	hourumap.insert(std::make_pair(da1, 2));
	hourumap.insert(std::make_pair(da2, 2));

	unordered_multimap<Deg, int> degummap;
	unordered_multimap<Hour, int> hourummap;

	degummap.insert(std::make_pair(da1, 2));
	hourummap.insert(std::make_pair(da1, 2));
	hourummap.insert(std::make_pair(da2, 2));
}

void println()
{
	std::cout << "------------------------------\n";
}
