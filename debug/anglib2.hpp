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

		Angle(const Angle & a) : angle_(a.toRad()) {}

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

		double toSec() const noexcept
		{
			return Const::SEC_IN_RAD / angle_;
		}

		double toHour() const noexcept
		{
			return toSec() / (Const::SEC_IN_DEG * Const::DEG_IN_HOUR);
		}

		double toDeg() const noexcept
		{
			return toSec() / Const::SEC_IN_DEG;
		}

		~Angle () noexcept {}
	
	}; 

	
	class Deg : public Angle 
	{
		void get_imag(proxy_imag &) const noexcept;
	public:

		Deg() noexcept : Angle(0) {}

		Deg(const Deg & d) noexcept : Angle(d.toRad()) {}

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

		Deg(const Hour & h) noexcept;

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

		Hour(const Hour & h) noexcept : Angle(h.toRad()) {}

		template<typename AriphmeticType>
		Hour(const AriphmeticType a) noexcept : Angle(a) {}
		
		//--Constructor: angle(hour, min, sec)
		template<typename AriphmeticTypeA, typename AriphmeticTypeB, typename AriphmeticTypeC>
		Hour(const AriphmeticTypeA hour_, const AriphmeticTypeB min_, const AriphmeticTypeC sec_) noexcept
		{
			angle_ = (sec_ + min_ * Const::MIN_IN_DEG + hour_ * Const::SEC_IN_DEG) / Const::HSEC_IN_RAD;
		}

		Hour(const Deg & d) noexcept;

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

	Hour::Hour(const Deg & d) noexcept : Angle(d.toRad()) {}
	Deg::Deg(const Hour & h) noexcept : Angle(h.toRad()) {}

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

	namespace Const
	{
		const Deg pi = Deg(180, 0, 0);
		const Deg rumb(11, 15, 0);
		const Deg grad(M_PI / 200);
		const Deg thousandy(M_PI / 3000);
	}

	//--------------implementations another ops-----------------
	//
	//---------------------EQUALS and NOTEQUALS----------
	//---------------------        ==          ----------
	inline bool operator==(const Deg & a, const Deg & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	inline bool operator==(const Deg & a, const Hour & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	inline bool operator==(const Hour & a, const Deg & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	inline bool operator==(const Hour & a, const Hour & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE;
	}

	template <typename AriphmeticType>
	inline bool operator==(const Deg & a, const AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE;
	}

	template <typename AriphmeticType>
	inline bool operator==(const AriphmeticType & b, const Deg & a) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE;
	}

	template <typename AriphmeticType>
	inline bool operator==(const Hour & a, const AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE;
	}

	template <typename AriphmeticType>
	inline bool operator==(const AriphmeticType & b, const Hour & a) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE;
	}

	//---------------------        !=          ----------
	inline bool operator!=(const Deg & a, const Deg & b) noexcept
	{
		return !(a == b);
	}

	inline bool operator!=(const Deg & a, const Hour & b) noexcept
	{
		return !(a == b);
	}

	inline bool operator!=(const Hour & a, const Deg & b) noexcept
	{
		return !(a == b);
	}

	inline bool operator!=(const Hour & a, const Hour & b) noexcept
	{
		return !(a == b);
	}

	template <typename AriphmeticType>
	inline bool operator!=(const Deg & a, const AriphmeticType & b) noexcept
	{
		return !(a == b);
	}

	template <typename AriphmeticType>
	inline bool operator!=(const AriphmeticType & b, const Deg & a) noexcept
	{
		return !(a == b);
	}

	template <typename AriphmeticType>
	inline bool operator!=(const Hour & a, const AriphmeticType & b) noexcept
	{
		return !(a == b);
	}

	template <typename AriphmeticType>
	inline bool operator!=(const AriphmeticType & b, const Hour & a) noexcept
	{
		return !(a == b);
	}

	//---------------------ADD----------
	inline const Deg operator+(const Deg & dl, const Deg & dr) noexcept
	{
		return Deg(dl.toRad() + dr.toRad());
	}

	inline const Deg operator+(const Deg & dl, const Hour & dr) noexcept
	{
		return Deg(dl.toRad() + dr.toRad());
	}

	inline const Hour operator+(const Hour & dl, const Deg & dr) noexcept
	{
		return Hour(dl.toRad() + dr.toRad());
	}

	inline const Hour operator+(const Hour & dl, const Hour & dr) noexcept
	{
		return Hour(dl.toRad() + dr.toRad());
	}

	template <typename AriphmeticType>
	inline const Deg operator+(const Deg & dl, const AriphmeticType & dr) noexcept
	{
		return Deg(dl.toRad() + double(dr));
	}

	template <typename AriphmeticType>
	inline const Deg operator+(const AriphmeticType & dr, const Deg & dl) noexcept
	{
		return Deg(dl.toRad() + double(dr));
	}

	template <typename AriphmeticType>
	inline const Hour operator+(const Hour & dl, const AriphmeticType & dr) noexcept
	{
		return Hour(dl.toRad() + double(dr));
	}

	template <typename AriphmeticType>
	inline const Hour operator+(const AriphmeticType & dr, const Hour & dl) noexcept
	{
		return Hour(dl.toRad() + double(dr));
	}

	//---------------------SUB----------
	inline const Deg operator-(const Deg & dl, const Deg & dr) noexcept
	{
		return Deg(dl.toRad() - dr.toRad());
	}

	inline const Deg operator-(const Deg & dl, const Hour & dr) noexcept
	{
		return Deg(dl.toRad() - dr.toRad());
	}

	inline const Hour operator-(const Hour & dl, const Deg & dr) noexcept
	{
		return Hour(dl.toRad() - dr.toRad());
	}

	inline const Hour operator-(const Hour & dl, const Hour & dr) noexcept
	{
		return Hour(dl.toRad() - dr.toRad());
	}

	template <typename AriphmeticType>
	inline const Deg operator-(const Deg & dl, const AriphmeticType & dr) noexcept
	{
		return Deg(dl.toRad() - double(dr));
	}

	template <typename AriphmeticType>
	inline const Deg operator-(const AriphmeticType & dr, const Deg & dl) noexcept
	{
		return Deg(double(dr) - dl.toRad());
	}

	template <typename AriphmeticType>
	inline const Hour operator-(const Hour & dl, const AriphmeticType & dr) noexcept
	{
		return Hour(dl.toRad() - double(dr));
	}

	template <typename AriphmeticType>
	inline const Hour operator-(const AriphmeticType & dr, const Hour & dl) noexcept
	{
		return Hour(double(dr) - dl.toRad());
	}

	//---------------------DIV----------
	inline double operator/(const Deg & dl, const Deg & dr) noexcept
	{
		return (dl.toRad() / dr.toRad());
	}

	inline double operator/(const Deg & dl, const Hour & dr) noexcept
	{
		return (dl.toRad() / dr.toRad());
	}

	inline double operator/(const Hour & dl, const Deg & dr) noexcept
	{
		return (dl.toRad() / dr.toRad());
	}

	inline double operator/(const Hour & dl, const Hour & dr) noexcept
	{
		return (dl.toRad() / dr.toRad());
	}

	//---ATTENTION!---specific semantic
	template <typename AriphmeticType>
	inline double operator/(const Deg & dl, const AriphmeticType & dr) noexcept
	{
		return (dl.toRad() / double(dr));
	}

	template <typename AriphmeticType>
	inline double operator/(const AriphmeticType & dr, const Deg & dl) noexcept
	{
		return (double(dr) / dl.toRad());
	}

	template <typename AriphmeticType>
	inline double operator/(const Hour & dl, const AriphmeticType & dr) noexcept
	{
		return (dl.toRad() / double(dr));
	}

	template <typename AriphmeticType>
	inline double operator/(const AriphmeticType & dr, const Hour & dl) noexcept
	{
		return (double(dr) / dl.toRad());
	}

	//---------------------MUL----------
	template <typename AriphmeticType>
	inline const Deg operator*(const Deg & dl, const AriphmeticType & dr) noexcept
	{
		return Deg(dl.toRad() * dr);
	}

	template <typename AriphmeticType>
	inline const Deg operator*(const AriphmeticType & dr, const Deg & dl) noexcept
	{
		return Deg(dr * dl.toRad());
	}

	template <typename AriphmeticType>
	inline const Hour operator*(const Hour & dl, const AriphmeticType & dr) noexcept
	{
		return Hour(dl.toRad() * dr);
	}

	template <typename AriphmeticType>
	inline const Hour operator*(const AriphmeticType & dr, const Hour & dl) noexcept
	{
		return Hour(dr * dl.toRad());
	}

	//---------------------GREAT_OF----------
	inline bool operator>(const Deg & a, const Deg & b) noexcept
	{
		return (a.toRad() - b.toRad()) > 0;
	}

	inline bool operator>(const Deg & a, const Hour & b) noexcept
	{
		return (a.toRad() - b.toRad()) > 0;
	}

	inline bool operator>(const Hour & a, const Deg & b) noexcept
	{
		return (a.toRad() - b.toRad()) > 0;
	}

	inline bool operator>(const Hour & a, const Hour & b) noexcept
	{
		return (a.toRad() - b.toRad()) > 0;
	}

	template <typename AriphmeticType>
	inline bool operator>(const Deg & a, const AriphmeticType & b) noexcept
	{
		return (a.toRad() - double(b)) > 0;
	}

	template <typename AriphmeticType>
	inline bool operator>(const AriphmeticType & b, const Deg & a) noexcept
	{
		return (double(b) - a.toRad()) > 0;
	}

	template <typename AriphmeticType>
	inline bool operator>(const Hour & a, const AriphmeticType & b) noexcept
	{
		return (a.toRad() - double(b)) > 0;
	}

	template <typename AriphmeticType>
	inline bool operator>(const AriphmeticType & b, const Hour & a) noexcept
	{
		return (double(b) - a.toRad()) > 0;
	}

	//---------------------LESS_THAN----------
	inline bool operator<(const Deg & a, const Deg & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	inline bool operator<(const Deg & a, const Hour & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	inline bool operator<(const Hour & a, const Deg & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	inline bool operator<(const Hour & a, const Hour & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	template <typename AriphmeticType>
	inline bool operator<(const Deg & a, const AriphmeticType & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	template <typename AriphmeticType>
	inline bool operator<(const AriphmeticType & a, const Deg & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	template <typename AriphmeticType>
	inline bool operator<(const Hour & a, const AriphmeticType & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	template <typename AriphmeticType>
	inline bool operator<(const AriphmeticType & a, const Hour & b) noexcept
	{
		return !((a == b) || (a > b));
	}

	//---------------------GREAT_OR_EQUAL----
	inline bool operator>=(const Deg & a, const Deg & b) noexcept
	{
		return !(a < b);
	}

	inline bool operator>=(const Deg & a, const Hour & b) noexcept
	{
		return !(a < b);
	}

	inline bool operator>=(const Hour & a, const Deg & b) noexcept
	{
		return !(a < b);
	}

	inline bool operator>=(const Hour & a, const Hour & b) noexcept
	{
		return !(a < b);
	}

	template <typename AriphmeticType>
	inline bool operator>=(const Deg & a, const AriphmeticType & b) noexcept
	{
		return !(a < b);
	}

	template <typename AriphmeticType>
	inline bool operator>=(const AriphmeticType & a, const Deg & b) noexcept
	{
		return !(a < b);
	}

	template <typename AriphmeticType>
	inline bool operator>=(const Hour & a, const AriphmeticType & b) noexcept
	{
		return !(a < b);
	}

	template <typename AriphmeticType>
	inline bool operator>=(const AriphmeticType & a, const Hour & b) noexcept
	{
		return !(a < b);
	}

	//---------------------LESS_OR_EQALS------
	inline bool operator<=(const Deg & a, const Deg & b) noexcept
	{
		return !(a > b);
	}

	inline bool operator<=(const Deg & a, const Hour & b) noexcept
	{
		return !(a > b);
	}

	inline bool operator<=(const Hour & a, const Deg & b) noexcept
	{
		return !(a > b);
	}

	inline bool operator<=(const Hour & a, const Hour & b) noexcept
	{
		return !(a > b);
	}

	template <typename AriphmeticType>
	inline bool operator<=(const Deg & a, const AriphmeticType & b) noexcept
	{
		return !(a > b);
	}

	template <typename AriphmeticType>
	inline bool operator<=(const AriphmeticType & a, const Deg & b) noexcept
	{
		return !(a > b);
	}

	template <typename AriphmeticType>
	inline bool operator<=(const Hour & a, const AriphmeticType & b) noexcept
	{
		return !(a > b);
	}

	template <typename AriphmeticType>
	inline bool operator<=(const AriphmeticType & a, const Hour & b) noexcept
	{
		return !(a > b);
	}

	//---------------------Ops += type of----------
	//---------------------+= ---------------------
	template <typename AriphmeticType>
	inline Deg & operator+=(Deg & d, const AriphmeticType & a) noexcept
	{
		d = d + a;
		return d;
	}

	inline Deg & operator+=(Deg & d, const Deg & a) noexcept
	{
		d = d + a;
		return d;
	}

	inline Deg & operator+=(Deg & d, const Hour & a) noexcept
	{
		d = d + a;
		return d;
	}
	
	template <typename AriphmeticType>
	inline Hour & operator+=(Hour & h, const AriphmeticType & a) noexcept
	{
		h = h + a;
		return h;
	}

	inline Hour & operator+=(Hour & d, const Deg & a) noexcept
	{
		d = d + a;
		return d;
	}

	inline Hour & operator+=(Hour & d, const Hour & a) noexcept
	{
		d = d + a;
		return d;
	}
	
	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator+=(AriphmeticType & a, const Deg & d) noexcept
	{
		a = a + d;
		return a;
	}
	
	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator+=(AriphmeticType & a, const Hour & h) noexcept
	{
		a = a + h;
		return a;
	}
	
	//----------------------= ---------------------
	template <typename AriphmeticType>
	inline Deg & operator-=(Deg & d, const AriphmeticType & a) noexcept
	{
		d = d - a;
		return d;
	}

	inline Deg & operator-=(Deg & d, const Deg & a) noexcept
	{
		d = d - a;
		return d;
	}

	inline Deg & operator-=(Deg & d, const Hour & a) noexcept
	{
		d = d - a;
		return d;
	}
	
	template <typename AriphmeticType>
	inline Hour & operator-=(Hour & h, const AriphmeticType & a) noexcept
	{
		h = h - a;
		return h;
	}

	inline Hour & operator-=(Hour & d, const Deg & a) noexcept
	{
		d = d - a;
		return d;
	}

	inline Hour & operator-=(Hour & d, const Hour & a) noexcept
	{
		d = d - a;
		return d;
	}
	
	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator-=(AriphmeticType & a, const Deg & d) noexcept
	{
		a = a - d;
		return a;
	}
	
	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator-=(AriphmeticType & a, const Hour & h) noexcept
	{
		a = a - h;
		return a;
	}
	
	//---------------------*= ---------------------
	template <typename AriphmeticType>
	inline Deg & operator*=(Deg & d, const AriphmeticType & a) noexcept
	{
		d = d * a;
		return d;
	}

	template <typename AriphmeticType>
	inline Hour & operator*=(Hour & h, const AriphmeticType & a) noexcept
	{
		h = h * a;
		return h;
	}

	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator*=(AriphmeticType & a, const Deg & d) noexcept
	{
		a = a * d;
		return a;
	}
	
	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator*=(AriphmeticType & a, const Hour & h) noexcept
	{
		a = a * h;
		return a;
	}

	//------------------   /= ---------------------
	template <typename AriphmeticType>
	inline Deg & operator/=(Deg & d, const AriphmeticType & a) noexcept
	{
		d = d / a;
		return d;
	}

	template <typename AriphmeticType>
	inline Hour & operator/=(Hour & h, const AriphmeticType & a) noexcept
	{
		h = h / a;
		return h;
	}

	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator/=(AriphmeticType & a, const Deg & d) noexcept
	{
		a = a / d;
		return a;
	}
	
	//--ATTENTION!--
	template <typename AriphmeticType>
	inline AriphmeticType & operator/=(AriphmeticType & a, const Hour & h) noexcept
	{
		a = a / h;
		return a;
	}
	
	//---------------------Op ++ ------------------
	inline Deg & operator++(Deg & a) noexcept
	{
		a += Deg(0, 0, 1);
		return a;
	}

	inline Hour & operator++(Hour & a) noexcept
	{
		a += Hour(0, 0, 1);
		return a;
	}

	//---------------------Op -- ------------------
	inline Deg & operator--(Deg & a) noexcept
	{
		a -= Deg(0, 0, 1);
		return a;
	}

	inline Hour & operator--(Hour & a) noexcept
	{
		a -= Hour(0, 0, 1);
		return a;
	}

	//---------------------UNARY + and - ----------
	inline const Deg & operator+(const Deg & a) noexcept
	{
		return a;
	}

	inline const Hour & operator+(const Hour & a) noexcept
	{
		return a;
	}
	
	inline const Deg operator-(const Deg & a) noexcept
	{
		return Deg(-a.toRad());
	}

	inline const Hour operator-(const Hour & a) noexcept
	{
		return Hour(-a.toRad());
	}
}

#endif
