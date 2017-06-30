#ifndef ANGLIB_HPP
#define ANGLIB_HPP 1

#include <cmath>
#include <iostream>

namespace anglib
{
	namespace Const 
	{
		const short SEC_IN_DEG = 3600;
		const short MIN_IN_DEG = 60;
		const short DEG_IN_HOUR = 15;
		const short DEG_IN_2PI = 360;
		const double SEC_IN_RAD = 360 * 60 * 60 / (2 * M_PI);
		const double MIN_AT_HOUR = double(1) / MIN_IN_DEG;
		const double SEC_AT_HOUR = double(1) / SEC_IN_DEG;
		const double PRECISION_COMPARE = 1e-13;
	}

	template <typename IntType>
	class Deg
	{
		double sec_;
		IntType min_, deg_;

	public:

		Deg() noexcept : sec_(0), min_(0), deg_(0) {}

		Deg(const Deg & d) noexcept : sec_(d.sec_), min_(d.min_), deg_(d.deg_) {}

		Deg(const IntType deg__, const IntType min__, const double sec__) noexcept : sec_(sec__), min_(min__), deg_(deg__)
		{}

		Deg(double rad) noexcept 
		{
    		sec_ = Const::SEC_IN_RAD * rad;
			deg_ = sec_ / Const::SEC_IN_DEG;
			sec_ -= Const::SEC_IN_DEG * deg_;
			min_ = sec_ / Const::MIN_IN_DEG;
			sec_ -= Const::MIN_IN_DEG * min_;
		}

		~Deg() noexcept {}

		IntType min() const noexcept
		{
			return min_;
		}

		IntType deg() const noexcept
		{
			return deg_;
		}

		double sec() const noexcept
		{
			return sec_;
		}

		double toRad() const noexcept 
		{
			return (sec_ / Const::SEC_IN_DEG + double(min_) / Const::MIN_IN_DEG + deg_) * M_PI / 180;
		}

		double toSec() const noexcept
		{
			return deg_ * Const::SEC_IN_DEG + min_ * Const::MIN_IN_DEG + sec_;
		}

		double toHour() const noexcept
		{
			return toSec() / (Const::SEC_IN_DEG * Const::DEG_IN_HOUR);
		}

		template <typename AIntType>
		AIntType mod_2pi() const noexcept
		{
			AIntType z = fabs(double(this->deg_) / Const::DEG_IN_2PI);
			return z;
		}

		//---NONCONST!-----
		void mod_2pi() noexcept
		{
			this->deg_ = this->deg_ % Const::DEG_IN_2PI;
		}

		friend std::ostream & operator<<(std::ostream & s, const Deg & dg)
		{
			s << dg.deg_ << " deg " << dg.min_ << " min " << dg.sec_ << " sec";
			return s;
		}

		friend const Deg operator+(const Deg & dl, const Deg & dr) noexcept
		{
			return Deg(dr.toRad() + dl.toRad());
		}

		template <typename AriphmeticType>
		friend const Deg operator+(const Deg & dl, const AriphmeticType & add) noexcept
		{
			return Deg(dl.toRad() + add);
		}

		template <typename AriphmeticType>
		friend const Deg operator+(const AriphmeticType & add, const Deg & dl) noexcept
		{
			return Deg(dl.toRad() + add);
		}

		friend const Deg operator-(const Deg & dl, const Deg & dr) noexcept
		{
			return Deg(dl.toRad() - dr.toRad());
		}

		template <typename AriphmeticType>
		friend const Deg operator-(const Deg & dl, const AriphmeticType & subd) noexcept
		{
			return Deg(dl.toRad() - subd);
		}

		template <typename AriphmeticType>
		friend const Deg operator-(const AriphmeticType & subd, const Deg & dl) noexcept
		{
			return Deg(subd - dl.toRad());
		}

		template <typename AriphmeticType>
		friend const Deg operator* (const Deg & dl, const AriphmeticType & mult) noexcept
		{
			return Deg(dl.toRad() * mult);
		}

		template <typename AriphmeticType>
		friend const Deg operator/ (const Deg & dl, const AriphmeticType & divs) noexcept
		{
			return Deg(dl.toRad() / divs);
		}

		bool operator==(const Deg & a)
		{
			return a->deg_ == this->deg_ && this->min_ == a->min_ && dabs(a->sec_ - this->sec_) < Const::PRECISION_COMPARE;
		}
	};

	template <typename IntType>
	class Hour
	{
		double sec_;
		IntType min_, hour;

	public:

		Hour() noexcept : sec_(0), min_(0), hour(0) {}

		Hour(const Hour & h) noexcept : sec_(h.sec_), min_(h.min_), hour(h.hour) {}
		Hour(short hour_, short min__, double sec__) noexcept : sec_(sec__), min_(min__), hour(hour_)
		{}

		Hour(double rad) noexcept
		{
    		sec_ = Const::SEC_IN_RAD * rad / 15;
			hour = sec_ / Const::SEC_IN_DEG;
			sec_ -= Const::SEC_IN_DEG * hour;
			min_ = sec_ / Const::MIN_IN_DEG;
			sec_ -= Const::MIN_IN_DEG * min_;
		}

		double toSec() const noexcept
		{
			return (hour * Const::SEC_IN_DEG + min_ * Const::MIN_IN_DEG +
						sec_) * 15 ;
		}

		double toHour() const noexcept
		{
			return toSec() / (Const::SEC_IN_DEG * 15);
		}

		double toRad() const noexcept
		{
			return toSec() / Const::SEC_IN_RAD;
		}

		friend std::ostream & operator<<(std::ostream &s, const Hour &hr)
		{
			s << hr.hour << " h " << hr.min_ << " m " << hr.sec_ << " s";
			return s;
		}

		const Hour & operator+(const Hour & hr) noexcept
		{
			return Hour(this->toRad() + hr.toRad());
		}

		const Hour & operator-(const Hour & hr) noexcept
		{
			return Hour(this->toRad() - hr.toRad());
		}

		template <typename AriphmeticType>
		const Hour & operator*(const AriphmeticType & mult) noexcept
		{
			return Hour(this->toRad() * mult);
		}

		template <typename AriphmeticType>
		const Hour & operator/(const AriphmeticType & divs) noexcept
		{
			return Hour(this->toRad() / divs);
		}
	};

	namespace Const
	{
		Deg<short> pi = Deg<short>(180, 0, 0);
	}


	//--------------implementations another ops-----------------
	template <typename IntType>
	inline bool operator==(const Deg<IntType> & a, const Deg<IntType> & b)
	{
		return a->deg_ == b->deg_ && b->min_ == a->min_ && dabs(a->sec_ - b->sec_) < Const::PRECISION_COMPARE;
	}
}
#endif
