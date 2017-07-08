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

		Deg(Deg & d) noexcept : Angle(d.toRad()) {}

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

		friend std::istream & operator>>(std::istream &s, Deg &dg) noexcept
		{
			double sec, min, deg;
			s >> deg >> min >> sec; 
			dg = Deg(deg, min, sec);
			return s;
		}

	};

	class Hour : public Angle 
	{
		void get_imag(proxy_imag &) const noexcept;
	public:
		Hour() noexcept : Angle(0) {}

		Hour(Hour & h) noexcept : Angle(h.toRad()) {}

		template<typename AriphmeticType>
		Hour(const AriphmeticType a) noexcept : Angle(a) {}
		
		//--Constructor: angle(hour, min, sec)
		template<typename AriphmeticTypeA, typename AriphmeticTypeB, typename AriphmeticTypeC>
		Hour(const AriphmeticTypeA hour_, const AriphmeticTypeB min_, const AriphmeticTypeC sec_) noexcept
		{
			angle_ = (sec_ + min_ * Const::MIN_IN_DEG + hour_ * Const::SEC_IN_DEG) / Const::HSEC_IN_RAD;
		}

		Hour(Deg & d) noexcept;

		~Hour() noexcept {}

		friend std::ostream & operator<<(std::ostream & s, const Hour & hr) noexcept 
		{
			proxy_imag tmp;
			hr.get_imag(tmp);
    		s << tmp.dh << " h " << tmp.min << " m " << tmp.sec << " s";
			return s;
		}

		friend std::istream & operator>>(std::istream &s, Hour &h) noexcept
		{
			double sec, min, hour;
			s >> hour >> min >> sec; 
			h = Hour(hour, min, sec);
			return s;
		}
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

	void Hour::get_imag(proxy_imag & tmp) const noexcept
	{
		tmp.sec = Const::SEC_IN_RAD * angle_ / Const::DEG_IN_HOUR;
		tmp.dh = static_cast<long>(tmp.sec / Const::SEC_IN_DEG);
		tmp.sec -= Const::SEC_IN_DEG * tmp.dh;
		tmp.min = static_cast<short>(tmp.sec / Const::MIN_IN_DEG);
		tmp.sec -= Const::MIN_IN_DEG * tmp.min;
	}
}

#endif
