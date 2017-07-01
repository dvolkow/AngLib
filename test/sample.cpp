#include "../debug/anglib.hpp"

using anglib::Const::pi; // Угол в 180 градусов
using anglib::Deg; // Тип для хранения градусного представления
using anglib::Hour; // Тип для хранения часового предствления

int main()
{
	std::cout << Deg<int>(-3, 60, 120) << "\n";
	std::cout << Hour<int>(0, 0, -70) << "\n";
}
