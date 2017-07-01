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

		const double SEC_IN_RAD = DEG_IN_2PI * SEC_IN_DEG / (2 * M_PI);
		const double HSEC_IN_RAD = HOUR_IN_2PI * SEC_IN_DEG / (2 * M_PI);
		const double MIN_AT_HOUR = double(1) / MIN_IN_DEG;
		const double SEC_AT_HOUR = double(1) / SEC_IN_DEG;

		const double PRECISION_COMPARE = 1e-13;
	}

	template <typename IntType>
	class Hour;

	template <typename IntType>
	class Deg
	{
		double sec_;
		IntType min_, deg_;

	public:

		Deg() noexcept : sec_(0), min_(0), deg_(0) {}

		Deg(const Deg & d) noexcept : sec_(d.sec()), min_(d.min()), deg_(d.deg()) {}

		template <typename AIntType>
		Deg(const Deg<AIntType> & d) noexcept : sec_(d.sec()), min_(d.min()), deg_(d.deg()) {}

		template <typename AIntType>
		Deg(const Hour<AIntType> & d) noexcept 
		{
			Deg tmp(d.toRad());
			deg_ = tmp.deg(), min_ = tmp.min(), sec_ = tmp.sec();
		}
			
		Deg(const IntType deg__, const IntType min__, const double sec__) noexcept 		
		{
			Deg tmp((sec__ + min__ * Const::MIN_IN_DEG + deg__ * Const::SEC_IN_DEG) / Const::SEC_IN_RAD);
			sec_ = tmp.sec();
			min_ = tmp.min();
			deg_ = tmp.deg();
		}

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
			s << dg.deg() << " deg " << dg.min() << " min " << dg.sec() << " sec";
			return s;
		}

	}; // end Deg

	template <typename IntType>
	class Hour
	{
		double sec_;
		IntType min_, hour_;

	public:

		Hour() noexcept : sec_(0), min_(0), hour_(0) {}

		Hour(const Hour & h) noexcept : sec_(h.sec()), min_(h.min()), hour_(h.hour()) {}

		template <typename AIntType>
		Hour(const Hour<AIntType> & d) noexcept : sec_(d.sec()), min_(d.min()), hour_(d.hour()) {}

		template <typename AIntType>
		Hour(const Deg<AIntType> & d) noexcept 
		{
			Hour tmp(d.toRad());
			hour_ = tmp.hour(), min_ = tmp.min(), sec_ = tmp.sec();
		}

		Hour(short hour__, short min__, double sec__) noexcept 
		{
			Hour tmp((sec__ + min__ * Const::MIN_IN_DEG + hour__ * Const::SEC_IN_DEG) / Const::HSEC_IN_RAD);
			sec_ = tmp.sec();
			min_ = tmp.min();
			hour_ = tmp.hour();
		}

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

	}; // end Hour


	namespace Const
	{
		const Deg<short> pi = Deg<short>(180, 0, 0);
		const Deg<short> rumb(11, 15, 0);
		const Deg<short> grad(M_PI / 200);
		const Deg<short> thousandy(M_PI / 3000);
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

	template <typename IntTypeA, typename IntTypeB>
	inline bool operator==(const Deg<IntTypeA> & a, const Deg<IntTypeB> & b) noexcept
	{
		return a == Deg<IntTypeA>(b);
	}

	template <typename IntType>
	inline bool operator!=(const Deg<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntTypeA, typename IntTypeB>
	inline bool operator!=(const Deg<IntTypeA> & a, const Deg<IntTypeB> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(const Deg<IntType> & a, const AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(const AriphmeticType & b, const Deg<IntType> & a) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(const AriphmeticType & b, const Deg<IntType> & a) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(const Deg<IntType> & a, const AriphmeticType & b) noexcept
	{
		return !(a == b);
	}
	
	//---Hour
	template <typename IntType>
	inline bool operator==(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return a.hour() == b.hour() && b.min() == a.min() && fabs(a.sec() - b.sec()) < Const::PRECISION_COMPARE;
	}

	template <typename IntTypeA, typename IntTypeB>
	inline bool operator==(const Hour<IntTypeA> & a, const Hour<IntTypeB> & b) noexcept
	{
		return a == Hour<IntTypeA>(b);
	}

	template <typename IntType>
	inline bool operator!=(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntTypeA, typename IntTypeB>
	inline bool operator!=(const Hour<IntTypeA> & a, const Hour<IntTypeB> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(const Hour<IntType> & a, const AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator==(const AriphmeticType & b, const Hour<IntType> & a) noexcept
	{
		return fabs(a.toRad() - b) < Const::PRECISION_COMPARE;
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(const AriphmeticType & b, const Hour<IntType> & a) noexcept
	{
		return !(a == b);
	}

	template <typename IntType, typename AriphmeticType>
	inline bool operator!=(const Hour<IntType> & a, const AriphmeticType & b) noexcept
	{
		return !(a == b);
	}

	//Deg == Hour cases
	template <typename IntType>
	inline bool operator==(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	template <typename IntTypeD, typename IntTypeH>
	inline bool operator==(const Hour<IntTypeH> & h, const Deg<IntTypeD> & d) noexcept
	{
		return fabs(h.toRad() - d.toRad()) < Const::PRECISION_COMPARE;
	}

	template <typename IntType>
	inline bool operator==(const Deg<IntType> & b, const Hour<IntType> & a) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	template <typename IntTypeD, typename IntTypeH>
	inline bool operator==(const Deg<IntTypeD> & d, const Hour<IntTypeH> & h) noexcept
	{
		return fabs(h.toRad() - d.toRad()) < Const::PRECISION_COMPARE;
	}

	template <typename IntType>
	inline bool operator!=(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return !(a == b);
	}

	template <typename IntTypeD, typename IntTypeH>
	inline bool operator!=(const Hour<IntTypeH> & h, const Deg<IntTypeD> & d) noexcept
	{
		return !(d == h);
	}

	template <typename IntType>
	inline bool operator!=(const Deg<IntType> & b, const Hour<IntType> & a) noexcept
	{
		return !(a == b);
	}

	template <typename IntTypeD, typename IntTypeH>
	inline bool operator!=(const Deg<IntTypeD> & d, const Hour<IntTypeH> & h) noexcept
	{
		return !(d == h);
	}

	//---------------------ADD----------
	//---Deg
	template <typename IntType>
	inline const Deg<IntType> operator+(const Deg<IntType> & dl, const Deg<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() + dr.toRad());
	}

	template <typename IntTypeA, typename IntTypeB>
	inline const Deg<IntTypeA> operator+(const Deg<IntTypeA> & dl, const Deg<IntTypeB> & dr) noexcept
	{
		return Deg<IntTypeA>(dl.toRad() + dr.toRad());
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

	template <typename IntTypeA, typename IntTypeB>
	inline const Hour<IntTypeA> operator+(const Hour<IntTypeA> & dl, const Hour<IntTypeB> & dr) noexcept
	{
		return Hour<IntTypeA>(dl.toRad() + dr.toRad());
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

	template <typename IntTypeD, typename IntTypeH>
	inline const Hour<IntTypeH> operator+(const Hour<IntTypeH> & dl, const Deg<IntTypeD> & dr) noexcept
	{
		return Hour<IntTypeH>(dl.toRad() + dr.toRad());
	}

	template <typename IntType>
	inline const Deg<IntType> operator+(const Deg<IntType> & dl, const Hour<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() + dr.toRad());
	}

	template <typename IntTypeD, typename IntTypeH>
	inline const Deg<IntTypeD> operator+(const Deg<IntTypeD> & dl, const Hour<IntTypeH> & dr) noexcept
	{
		return Deg<IntTypeD>(dl.toRad() + dr.toRad());
	}

	//---------------------SUB----------
	//---Deg
	template <typename IntType>
	inline const Deg<IntType> operator-(const Deg<IntType> & dl, const Deg<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() - dr.toRad());
	}

	template <typename IntTypeA, typename IntTypeB>
	inline const Deg<IntTypeA> operator-(const Deg<IntTypeA> & dl, const Deg<IntTypeB> & dr) noexcept
	{
		return Deg<IntTypeA>(dl.toRad() - dr.toRad());
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

	template <typename IntTypeA, typename IntTypeB>
	inline const Hour<IntTypeA> operator-(const Hour<IntTypeA> & dl, const Hour<IntTypeB> & dr) noexcept
	{
		return Hour<IntTypeA>(dl.toRad() - dr.toRad());
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

	template <typename IntTypeD, typename IntTypeH>
	inline const Hour<IntTypeH> operator-(const Hour<IntTypeH> & dl, const Deg<IntTypeD> & dr) noexcept
	{
		return Hour<IntTypeH>(dl.toRad() - dr.toRad());
	}

	template <typename IntType>
	inline const Deg<IntType> operator-(const Deg<IntType> & dl, const Hour<IntType> & dr) noexcept
	{
		return Deg<IntType>(dl.toRad() - dr.toRad());
	}

	template <typename IntTypeD, typename IntTypeH>
	inline const Deg<IntTypeD> operator-(const Deg<IntTypeD> & dl, const Hour<IntTypeH> & dr) noexcept
	{
		return Deg<IntTypeD>(dl.toRad() - dr.toRad());
	}

	//---------------------DIV----------
	//---Deg
	template <typename AriphmeticType, typename IntType>
	inline const Deg<IntType> operator/ (const Deg<IntType> & dl, const AriphmeticType & divs) noexcept
	{
		return Deg<IntType>(dl.toRad() / divs);
	}

	//---ATTENTION!---specific semantic
	template <typename AriphmeticType, typename IntType>
	inline double operator/ (const AriphmeticType & divs, const Deg<IntType> & dl) noexcept
	{
		return divs / dl.toRad();
	}

	//---Hour
	template <typename AriphmeticType, typename IntType>
	inline const Hour<IntType> operator/ (const Hour<IntType> & dl, const AriphmeticType & divs) noexcept
	{
		return Hour<IntType>(dl.toRad() / divs);
	}

	//---ATTENTION!---specific semantic
	template <typename AriphmeticType, typename IntType>
	inline double operator/ (const AriphmeticType & divs, const Hour<IntType> & dl) noexcept
	{
		return divs / dl.toRad();
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
	
	template <typename IntTypeA, typename IntTypeB>
	inline bool operator>(const Deg<IntTypeA> & a, const Deg<IntTypeB> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}

	//---Hour
	template <typename IntType>
	inline bool operator>(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}
	
	template <typename IntTypeA, typename IntTypeB>
	inline bool operator>(const Hour<IntTypeA> & a, const Hour<IntTypeB> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}
	
	//---Hour & Deg
	template <typename IntType>
	inline bool operator>(const Deg<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}
	
	template <typename IntTypeD, typename IntTypeH>
	inline bool operator>(const Deg<IntTypeD> & d, const Hour<IntTypeH> & h) noexcept
	{
		return (h - d).toRad() < 0;
	}

	template <typename IntType>
	inline bool operator>(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return (b - a).toRad() < 0;
	}
	
	template <typename IntTypeD, typename IntTypeH>
	inline bool operator>(const Hour<IntTypeH> & h, const Deg<IntTypeD> & d) noexcept
	{
		return (h - d).toRad() < 0;
	}

	//---------------------LESS_THAN----------
	//---Deg
	template <typename IntType>
	inline bool operator<(const Deg<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return b > a;
	}
	
	template <typename IntTypeA, typename IntTypeB>
	inline bool operator<(const Deg<IntTypeA> & a, const Deg<IntTypeB> & b) noexcept
	{
		return b > a;
	}
	
	//---Hour
	template <typename IntType>
	inline bool operator<(const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return b > a;
	}
	
	template <typename IntTypeA, typename IntTypeB>
	inline bool operator<(const Hour<IntTypeA> & a, const Hour<IntTypeB> & b) noexcept
	{
		return b > a;
	}
	
	//---Hour & Deg
	template <typename IntType>
	inline bool operator<(const Deg<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return b > a;
	}
	
	template <typename IntTypeD, typename IntTypeH>
	inline bool operator<(const Deg<IntTypeD> & d, const Hour<IntTypeH> & h) noexcept
	{
		return h > d;
	}

	template <typename IntType>
	inline bool operator<(const Hour<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return b > a;
	}
	
	template <typename IntTypeD, typename IntTypeH>
	inline bool operator<(const Hour<IntTypeH> & h, const Deg<IntTypeD> & d) noexcept
	{
		return d > h;
	}
}

#endif
