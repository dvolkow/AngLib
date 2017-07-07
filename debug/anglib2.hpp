#ifndef ANGLIB_HPP
#define ANGLIB_HPP 1

#include <cmath>
#include <iostream>

namespace anglib
{
	//Interface, basic class
	class Angle
	{
	protected:
		double angle_; // Here angle (rad)

	public:
		Angle () : angle_(0) {}

		//--Constructor: angle(rad)
		template<typename AriphmeticType>
		Angle(const AriphmeticType a) : angle_(a) {}

		//--Constructor: angle(deg, min, sec)
		template<typename AriphmeticTypeA, typename AriphmeticTypeB,
				 						   typename AriphmeticTypeC>
		Angle(const AriphmeticTypeA a, const AriphmeticTypeB b,
			  							   const AriphmeticTypeC c);

		~Angle () {}
	
	}; 

	class Deg : private Angle 
	{
	public:

		double get_a()
		{
			return angle_;
		}
	};

	class Hour : private Angle 
	{
	public:
	};
}

#endif
