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
		const short HOUR_IN_2PI = 24;
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

		double toDeg() const noexcept
		{
			return toSec() / Const::SEC_IN_DEG;
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

		//---NONCONST!-----
		//--Reduce angle to value between 0 deg and 360 deg:
		void normalize() noexcept
		{
			mod_2pi();
			Deg tmp;

			if ((Deg(deg_, min_, sec_) > Deg(0) || 
						Deg(deg_, min_, sec_) == Deg(0)))
				return;
			else 
				tmp = Deg(deg_, min_, sec_) + Deg(360, 0, 0);

			deg_ = tmp.deg();
			min_ = tmp.min();
			sec_ = tmp.sec();
		}

		friend std::ostream & operator<<(std::ostream & s, const Deg & dg) 
		{
			s << dg.deg_ << " deg " << dg.min_ << " min " << dg.sec_ << " sec";
			return s;
		}

		bool operator==(const Deg & a)
		{
			return a.deg() == this->deg_ && this->min_ == a.min() && fabs(a.sec() - this->sec_) < Const::PRECISION_COMPARE;
		}
	};

	template <typename IntType>
	class Hour
	{
		double sec_;
		IntType min_, hour_;

	public:

		Hour() noexcept : sec_(0), min_(0), hour_(0) {}

		Hour(const Hour & h) noexcept : sec_(h.sec_), min_(h.min_), hour_(h.hour_) {}

		Hour(short hour__, short min__, double sec__) noexcept : sec_(sec__), min_(min__), hour_(hour__)
		{}

		Hour(double rad) noexcept
		{
    		sec_ = Const::SEC_IN_RAD * rad / 15;
			hour_ = sec_ / Const::SEC_IN_DEG;
			sec_ -= Const::SEC_IN_DEG * hour_;
			min_ = sec_ / Const::MIN_IN_DEG;
			sec_ -= Const::MIN_IN_DEG * min_;
		}

		~Hour() noexcept {}

		IntType min() const noexcept
		{
			return min_;
		}

		IntType hour() const noexcept
		{
			return hour_;
		}

		double sec() const noexcept
		{
			return sec_;
		}

		double toSec() const noexcept
		{
			return (hour_ * Const::SEC_IN_DEG + min_ * Const::MIN_IN_DEG +
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

		double toDeg() const noexcept
		{
			return toSec() / Const::SEC_IN_DEG;
		}

		template <typename AIntType>
		AIntType mod_2pi() const noexcept
		{
			AIntType z = fabs(double(this->hour_) / Const::HOUR_IN_2PI);
			return z;
		}

		//---NONCONST!-----
		void mod_2pi() noexcept
		{
			this->hour_ = this->hour_ % Const::HOUR_IN_2PI;
		}
		
		//---NONCONST!-----
		//--Reduce angle to value between 0 hour and 24 hour:
		void normalize() noexcept
		{
			mod_2pi();
			Hour tmp;

			if ((Hour(hour_, min_, sec_) > Hour(0) || 
						Hour(hour_, min_, sec_) == Hour(0)))
				return;
			else 
				tmp = Hour(hour_, min_, sec_) + Hour(24, 0, 0);

			hour_ = tmp.hour();
			min_ = tmp.min();
			sec_ = tmp.sec();
		}

		friend std::ostream & operator<<(std::ostream &s, const Hour &hr)
		{
			s << hr.hour_ << " h " << hr.min_ << " m " << hr.sec_ << " s";
			return s;
		}

		bool operator==(const Hour & a)
		{
			return a.hour() == this->hour_ && this->min_ == a.min() && fabs(a.sec() - this->sec_) < Const::PRECISION_COMPARE;
		}
	};

	namespace Const
	{
		Deg<short> pi = Deg<short>(180, 0, 0);
	}


	//--------------implementations another ops-----------------
	//
	//---------------------EQUALS and NOTEQUALS----------
	//---Deg
	template <typename IntType>
	inline bool operator==(const Deg<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return a.deg() == b.deg() && b.min() == a.min() && fabs(a.sec() - b.sec()) < Const::PRECISION_COMPARE;
	}

	template <typename IntType>
	inline bool operator!=(const Deg<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(const Deg<IntType> & a, AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(AriphmeticType & b, const Deg<IntType> & a) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(AriphmeticType & b, const Deg<IntType> & a) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(const Deg<IntType> & a, AriphmeticType & b) noexcept
	{
		return !(a == b);
	}
	
	//---Hour
	template <typename IntType>
	inline bool operator==(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return a.hour() == b.hour() && b.min() == a.min() && fabs(a.sec() - b.sec()) < Const::PRECISION_COMPARE;
	}

	template <typename IntType>
	inline bool operator!=(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(const Hour<IntType> & a, AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(AriphmeticType & b, const Hour<IntType> & a) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(AriphmeticType & b, const Hour<IntType> & a) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(const Hour<IntType> & a, AriphmeticType & b) noexcept
	{
		return !(a == b);
	}

	//Deg == Hour cases
	template <typename IntType>
	inline bool operator==(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	template <typename IntType>
	inline bool operator==(const Deg<IntType> & b, const Hour<IntType> & a) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	template <typename IntType>
	inline bool operator!=(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntType>
	inline bool operator!=(const Deg<IntType> & b, const Hour<IntType> & a) noexcept
	{
		return !(a == b);
	}

	//---------------------ADD----------
	//---Deg
	template <typename IntType>
	inline const Deg<IntType> operator+(const Deg<IntType> & dl, const Deg<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() + dr.toRad());
	}

	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator+(const Deg<IntType> & dl, const AriphmeticType & adds) noexcept
	{
		return Deg<IntType>(dl.toRad() + adds);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator+(const AriphmeticType & adds, const Deg<IntType> & dl) noexcept
	{
		return Deg<IntType>(adds + dl.toRad());
	}

	//---Hour
	template <typename IntType>
	inline const Hour<IntType> operator+(const Hour<IntType> & dl, const Hour<IntType> & dr) noexcept
	{
		return Hour<IntType>(dl.toRad() + dr.toRad());
	}

	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator+(const Hour<IntType> & dl, const AriphmeticType & adds) noexcept
	{
		return Hour<IntType>(dl.toRad() + adds);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator+(const AriphmeticType & adds, const Hour<IntType> & dl) noexcept
	{
		return Hour<IntType>(adds + dl.toRad());
	}

	//Deg + Hour cases
	template <typename IntType>
	inline const Hour<IntType> operator+(const Hour<IntType> & dl, const Deg<IntType> & dr) noexcept
	{
		return Hour<IntType>(dl.toRad() + dr.toRad());
	}

	template <typename IntType>
	inline const Deg<IntType> operator+(const Deg<IntType> & dl, const Hour<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() + dr.toRad());
	}

	//---------------------SUB----------
	//---Deg
	template <typename IntType>
	inline const Deg<IntType> operator-(const Deg<IntType> & dl, const Deg<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() - dr.toRad());
	}

	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator-(const Deg<IntType> & dl, const AriphmeticType & subd) noexcept
	{
		return Deg<IntType>(dl.toRad() - subd);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator-(const AriphmeticType & subd, const Deg<IntType> & dl) noexcept
	{
		return Deg<IntType>(subd - dl.toRad());
	}

	//---Hour
	template <typename IntType>
	inline const Hour<IntType> operator-(const Hour<IntType> & dl, const Hour<IntType> & dr) noexcept
	{
		return Hour<IntType>(dl.toRad() - dr.toRad());
	}

	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator-(const Hour<IntType> & dl, const AriphmeticType & subd) noexcept
	{
		return Hour<IntType>(dl.toRad() - subd);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator-(const AriphmeticType & subd, const Hour<IntType> & dl) noexcept
	{
		return Hour<IntType>(subd - dl.toRad());
	}

	//Deg - Hour cases
	template <typename IntType>
	inline const Hour<IntType> operator-(const Hour<IntType> & dl, const Deg<IntType> & dr) noexcept
	{
		return Hour<IntType>(dl.toRad() - dr.toRad());
	}

	template <typename IntType>
	inline const Deg<IntType> operator-(const Deg<IntType> & dl, const Hour<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() - dr.toRad());
	}

	//---------------------DIV----------
	//---Deg
	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator/ (const Deg<IntType> & dl, const AriphmeticType & divs) noexcept
	{
		return Deg<IntType>(dl.toRad() / divs);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator/ (const AriphmeticType & divs, const Deg<IntType> & dl) noexcept
	{
		return Deg<IntType>(divs / dl.toRad());
	}

	//---Hour
	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator/ (const Hour<IntType> & dl, const AriphmeticType & divs) noexcept
	{
		return Hour<IntType>(dl.toRad() / divs);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator/ (const AriphmeticType & divs, const Hour<IntType> & dl) noexcept
	{
		return Hour<IntType>(divs / dl.toRad());
	}

	//---------------------MUL----------
	//---Deg
	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator* (const Deg<IntType> & dl, const AriphmeticType & mult) noexcept
	{
		return Deg<IntType>(dl.toRad() * mult);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator* (const AriphmeticType & mult, const Deg<IntType> & dl) noexcept
	{
		return Deg<IntType>(dl.toRad() * mult);
	}

	//---Hour
	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator* (const Hour<IntType> & dl, const AriphmeticType & mult) noexcept
	{
		return Hour<IntType>(dl.toRad() * mult);
	}

	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator* (const AriphmeticType & mult, const Hour<IntType> & dl) noexcept
	{
		return Hour<IntType>(dl.toRad() * mult);
	}

	//---------------------GREAT_OF----------
	//---Deg
	template <typename IntType>
	inline bool operator>(const Deg<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}
	
	//---Hour
	template <typename IntType>
	inline bool operator>(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}
	
	//---Hour & Deg
	template <typename IntType>
	inline bool operator>(const Deg<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}

	template <typename IntType>
	inline bool operator>(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}

	//---------------------LESS_THAN----------
	//---Deg
	template <typename IntType>
	inline bool operator<(const Deg<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return b > a;
	}
	
	//---Hour
	template <typename IntType>
	inline bool operator<(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return b > a;
	}
	
	//---Hour & Deg
	template <typename IntType>
	inline bool operator<(const Deg<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return b > a;
	}

	template <typename IntType>
	inline bool operator<(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return b > a;
	}

}

#endif
