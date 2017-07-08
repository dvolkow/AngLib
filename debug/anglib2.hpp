#ifndef ANGLIB_HPP
#define ANGLIB_HPP 1

#include <cmath>
#include <iostream>

namespace anglib
{
	class Deg;
	class Hour; 

	struct proxy_imag
	{
		long double sec;
		long dh;
		short min;
	};
	
	namespace Const 
	{
		const short SEC_IN_DEG = 3600;
		const short MIN_IN_DEG = 60;
		const short DEG_IN_HOUR = 15;
		const short HOUR_IN_2PI = 24;
		const short DEG_IN_2PI = 360;

		const double SEC_IN_RAD = DEG_IN_2PI * SEC_IN_DEG / (2 * M_PI);
		const double HSEC_IN_RAD = HOUR_IN_2PI * SEC_IN_DEG / (2 * M_PI);
		const double MIN_AT_HOUR = double(1) / MIN_IN_DEG;
		const double SEC_AT_HOUR = double(1) / SEC_IN_DEG;

		const double PRECISION_COMPARE = 1e-13;
	}


	//Interface, basic class
	class Angle
	{
	protected:
		double angle_; // Here angle (rad)

	public:
		Angle() noexcept : angle_(0) {}

		//--Constructor: angle(rad)
		template<typename AriphmeticType>
		Angle(const AriphmeticType a) noexcept : angle_(a) {}

		//--Constructor: angle(deg, min, sec)
		template<typename AriphmeticTypeA, typename AriphmeticTypeB,
				 						   typename AriphmeticTypeC>
		Angle(const AriphmeticTypeA a, const AriphmeticTypeB b,
			  							   const AriphmeticTypeC c) noexcept;

		double toRad() const noexcept
		{
			return angle_;
		}

		~Angle () noexcept {}
	
	}; 

	
	class Deg : public Angle 
	{
		void get_imag(proxy_imag &) const noexcept;
	public:

		Deg() noexcept : Angle(0) {}

		template<typename AriphmeticType>
		Deg(const AriphmeticType a) noexcept : Angle(a) {}

		//--Constructor: angle(deg, min, sec)
		template<typename AriphmeticTypeA, typename AriphmeticTypeB,
				 						   typename AriphmeticTypeC>
		Deg(const AriphmeticTypeA deg_, const AriphmeticTypeB min_,
			  							   const AriphmeticTypeC sec_) noexcept
		{
			angle_ = (double(sec_) / Const::SEC_IN_DEG + double(min_) / Const::MIN_IN_DEG + deg_) * M_PI / 180;
		}

		Deg(Hour & h) noexcept;

		~Deg() noexcept {}

		friend std::ostream & operator<<(std::ostream & s, const Deg & dg) noexcept 
		{
			proxy_imag tmp;
			dg.get_imag(tmp);
    		s << tmp.dh << " deg " << tmp.min << " min " << tmp.sec << " sec";
			return s;
		}
	};

	class Hour : public Angle 
	{
	public:
		Hour() : Angle(0) {}

		template<typename AriphmeticType>
		Hour(const AriphmeticType a) : Angle(a) {}

		Hour(Deg & d) noexcept;
	};

	Hour::Hour(Deg & d) noexcept : Angle(d.toRad()) {}
	Deg::Deg(Hour & h) noexcept : Angle(h.toRad()) {}

	void Deg::get_imag(proxy_imag & tmp) const noexcept
	{
		tmp.sec = Const::SEC_IN_RAD * angle_;
		tmp.dh = static_cast<long>(tmp.sec / Const::SEC_IN_DEG);
		tmp.sec -= Const::SEC_IN_DEG * tmp.dh;
		tmp.min = static_cast<short>(tmp.sec / Const::MIN_IN_DEG);
		tmp.sec -= Const::MIN_IN_DEG * tmp.min;
	}
}

#endif
