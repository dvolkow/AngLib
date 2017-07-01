#include "../debug/anglib.hpp"

using anglib::Const::pi; // Угол в 180 градусов
using anglib::Deg; // Тип для хранения градусного представления
using anglib::Hour; // Тип для хранения часового предствления

//-------Для параметризации рекомендуется использовать 
//---знаковые целые типы, например:
typedef Deg<short> degshort;
typedef Hour<short> hourshort;

typedef Deg<int> degint;
typedef Hour<int> hourint;

//-------Плохой выбор:
typedef Deg<uint> udegint;
typedef Hour<uint> uhourint;


int main()
{
	degshort zero; // -- по-умолчанию, нулевой угол
	hourshort hzero;

	std::cout << zero << "\n"; // -- можно выводить так
	std::cout << hzero << "\n";

	//--Конструктор от арифметического типа, приводящегося
	//--к double, порождает угол с радианной мерой, равной
	//--значению в double, к которому привелся тип.
	degshort radian(1); //  -- угол в один радиан
	hourshort hradian(1);

	std::cout << radian << "\n";
	std::cout << hradian << "\n";

	//--Конструктор от списка: два значения одинаковых целых
	//--арифметических типов, и double.
	degint a(0, 1, 2.08); // -- угол 1' 2.08"
	hourint ha(0, 1, 2.08); // -- угол 1m 2.08s

	std::cout << a << "\n";
	std::cout << ha << "\n";

	degint b(-15, 300, -61); // -- такой список будет коррект-
							 // -- но обработан согласно ариф-
							 // -- метике -15g + 300' - 61",
							 // -- что может быть использовано
							 // -- в вычислениях с сильно отли-
							 // -- чающимися по порядку значе-
							 // -- ниями
	hourint hb(-15, 300, -61);  // -- аналогично для Hour

	std::cout << b << "\n";
	std::cout << hb << "\n";

	//--Копирующий конструктор от любой допустимой параметриза-
	//--ции:
	degshort c(a); // -- degshort (c) != degint (a) в смысле ти-
				   // -- пов, но можно приводить один к другому:
	degint d = c;

	std::cout << c << "\n";
	std::cout << d << "\n";

	hourshort hc(ha);
	hourint hd = hc;

	d = hc, hd = c; // -- допустимы и такие приведения, разве не
					// -- здорово?!)

	std::cout << c << "\n";
	std::cout << d << "\n";
	std::cout << hc << "\n";
	std::cout << hd << "\n";

	//--Сравнение углов 
	degshort da1(180, 1, 0), da2(180, 0, 0.899);
	hourint ha1(24, 1, 0), ha2(24, 0, 0.899);

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
								// -- мерах: TODO -- убрать необ-
								// -- ходимость приведения
	std::cout << "da1 < ha1 ? " << (da1 < degshort(ha1)) << "\n"; 
	std::cout << "da2 > ha2 ? " << (degshort(ha2) > da2) << "\n"; 
	std::cout << "ha1 == da1 ? " << (ha1 == hourint(da1)) << "\n"; 
	std::cout << "ha1 != da1 ? " << (degshort(ha1) != da1) << "\n"; 
								

	//--Арифметика 

	//--Допустимо складывать углы в различных мерах и вычитать их
	//--друг из друга:						TODO -- убрать необ-
								// -- ходимость приведения
	std::cout << "radian + radian = " << (radian + radian) << "\n";
	std::cout << "radian - radian = " << (radian - radian) << "\n";

	//----ВАЖНО!
	//--Если складываются два угла в различных мерах, то тип резу-
	//--льтата определяется ЛЕВЫМ операндом. Например, ниже вывод
	//--будет в часах:
	std::cout << "ha1 + da1 = " << (ha1 + hourint(da1)) << "\n";

	//--Углы можно умножать и делить на числовые типы, и обратно:
	std::cout << "radian * 3.14 = " << (radian * 3.14) << "\n";
	std::cout << "PI * radian = " << (M_PI * radian) << "\n";
	std::cout << "radian / 2 * PI = " << (M_PI * radian / 2) << "\n";
	//--При делении числа на угол происходит преобразование число-
	//--вого типа в угловой, т.е. подразумевается, что делят угол в
	//--радианной мере:
	std::cout << "1 / radian = " << (1 / radian) << "\n"; //TODO косяк!
	
	
	
	
	
	
	

}
