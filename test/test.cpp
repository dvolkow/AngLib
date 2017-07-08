#include "../debug/anglib.hpp"
#include <my_dev/btl.hpp>

using anglib::Deg;
using anglib::Hour;
using anglib::Const;

using btl::Test;

Test t;

int main()
{
	t.run<Deg>();
	t.run<Hour>();
	std::cout << "Smoke test passed!\n"; 
}
