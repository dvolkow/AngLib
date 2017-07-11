#ifndef ANGLIB_HPP
#define ANGLIB_HPP 1

#include <cmath>
#include <iostream>

namespace anglib
{

#ifndef OLD_ANGLIB__

	class Deg;
	class Hour; 

	struct proxy_imag
	{
		double sec;
		long dh;
		short min;
	};

	class Const
	{
		Const ();
		virtual ~Const () = 0;

	public:
		static short SEC_IN_DEG() noexcept { return 3600; }
		static short MIN_IN_DEG() noexcept { return 60; }
		static short DEG_IN_HOUR() noexcept { return 15; }
		static short HOUR_IN_2PI() noexcept { return 24; }
		static short DEG_IN_2PI() noexcept { return 360; }

		static double SEC_IN_RAD() noexcept { return DEG_IN_2PI() * SEC_IN_DEG() / (2 * M_PI); }
		static double HSEC_IN_RAD() noexcept { return HOUR_IN_2PI() * SEC_IN_DEG() / (2 * M_PI); }

		static double MIN_AT_HOUR() noexcept { return double(1) / MIN_IN_DEG(); }
		static double SEC_AT_HOUR() noexcept { return double(1) / SEC_IN_DEG(); }

		static double PRECISION_COMPARE() noexcept { return 1e-13; }

		static Deg PI() noexcept;
		static Deg RAD() noexcept;
		static Deg DEG() noexcept;
		static Hour HOUR() noexcept;
		static Deg RUMB() noexcept;
		static Deg GRAD() noexcept;
		static Deg THOUSANDTH() noexcept;
	};

	Const::~Const() {} 
	
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
		Angle(const AriphmeticType a) noexcept : angle_(static_cast<double>(a)) {}

		//--Constructor: angle(deg, min, sec)
		template<typename AriphmeticTypeA, typename AriphmeticTypeB,
				 						   typename AriphmeticTypeC>
		Angle(const AriphmeticTypeA a, const AriphmeticTypeB b,
			  							   const AriphmeticTypeC c) noexcept;

		double toRad() const noexcept
		{
			return angle_;
		}

		double toArcSec() const noexcept
		{
			return Const::SEC_IN_RAD() * angle_;
		}

		double toHSec() const noexcept
		{
			return Const::HSEC_IN_RAD() * angle_;
		}

		double toHour() const noexcept
		{
			return toArcSec() / (Const::SEC_IN_DEG() * Const::DEG_IN_HOUR());
		}

		double toDeg() const noexcept
		{
			return toArcSec() / Const::SEC_IN_DEG();
		}

		~Angle () {}

		// Type conversion operators:
		operator short() const noexcept
		{
			return static_cast<short>(angle_);
		}
	
		operator int() const noexcept
		{
			return static_cast<int>(angle_);
		}
	
		operator long() const noexcept  
		{
			return static_cast<long>(angle_);
		}
	
		operator long long() const noexcept
		{
			return static_cast<long long>(angle_);
		}
	
		operator float() const noexcept
		{
			return static_cast<float>(angle_);
		}
	
		operator double() const noexcept
		{
			return static_cast<double>(angle_);
		}
	
		operator long double() const noexcept
		{
			return static_cast<long double>(angle_);
		}

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
			angle_ = (double(sec_) / Const::SEC_IN_DEG() + double(min_) / Const::MIN_IN_DEG() + deg_) * M_PI / 180;
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
			angle_ = (sec_ + min_ * Const::MIN_IN_DEG() + hour_ * Const::SEC_IN_DEG()) / Const::HSEC_IN_RAD();
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
		tmp.sec = Const::SEC_IN_RAD() * angle_;
		tmp.dh = static_cast<long>(tmp.sec / Const::SEC_IN_DEG());
		tmp.sec -= Const::SEC_IN_DEG() * static_cast<double>(tmp.dh);
		tmp.min = static_cast<short>(tmp.sec / Const::MIN_IN_DEG());
		tmp.sec -= Const::MIN_IN_DEG() * static_cast<double>(tmp.min);
	}

	void Hour::get_imag(proxy_imag & tmp) const noexcept
	{
		tmp.sec = Const::SEC_IN_RAD() * angle_ / Const::DEG_IN_HOUR();
		tmp.dh = static_cast<long>(tmp.sec / Const::SEC_IN_DEG());
		tmp.sec -= Const::SEC_IN_DEG() * static_cast<double>(tmp.dh);
		tmp.min = static_cast<short>(tmp.sec / Const::MIN_IN_DEG());
		tmp.sec -= Const::MIN_IN_DEG() * static_cast<double>(tmp.min);
	}

	Deg Const::PI() noexcept { return Deg(180, 0, 0); }
	Deg Const::RAD() noexcept { return Deg(1); }
	Deg Const::DEG() noexcept { return Deg(1, 0, 0); }
	Hour Const::HOUR() noexcept { return Hour(1, 0, 0); }

	Deg RUMB() noexcept { return Deg(11, 15, 0); }
	Deg GRAD() noexcept { return Deg(M_PI / 200); }
	Deg THOUSANDTH() noexcept { return Deg(M_PI / 3000); }

	//--------------implementations another ops-----------------
	//
	//---------------------EQUALS and NOTEQUALS----------
	//---------------------        ==          ----------
	inline bool operator==(const Deg & a, const Deg & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE();
	}

	inline bool operator==(const Deg & a, const Hour & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE();
	}

	inline bool operator==(const Hour & a, const Deg & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE();
	}

	inline bool operator==(const Hour & a, const Hour & b) noexcept
	{
		return fabs(a.toRad() - b.toRad()) < Const::PRECISION_COMPARE();
	}

	template <typename AriphmeticType>
	inline bool operator==(const Deg & a, const AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE();
	}

	template <typename AriphmeticType>
	inline bool operator==(const AriphmeticType & b, const Deg & a) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE();
	}

	template <typename AriphmeticType>
	inline bool operator==(const Hour & a, const AriphmeticType & b) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE();
	}

	template <typename AriphmeticType>
	inline bool operator==(const AriphmeticType & b, const Hour & a) noexcept
	{
		return fabs(a.toRad() - double(b)) < Const::PRECISION_COMPARE();
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
		return Deg(dl.toRad() * static_cast<double>(dr));
	}

	template <typename AriphmeticType>
	inline const Deg operator*(const AriphmeticType & dr, const Deg & dl) noexcept
	{
		return Deg(static_cast<double>(dr) * dl.toRad());
	}

	template <typename AriphmeticType>
	inline const Hour operator*(const Hour & dl, const AriphmeticType & dr) noexcept
	{
		return Hour(dl.toRad() * static_cast<double>(dr));
	}

	template <typename AriphmeticType>
	inline const Hour operator*(const AriphmeticType & dr, const Hour & dl) noexcept
	{
		return Hour(static_cast<double>(dr) * dl.toRad());
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

#else

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

		friend std::istream & operator>>(std::istream &s, Deg &dg)
		{
			IntType min, deg;
			double sec;
			s >> deg >> min >> sec; 
			dg = Deg(deg, min, sec);
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

		friend std::istream & operator>>(std::istream &s, Hour &hr)
		{
			IntType min, hour;
			double sec;
			s >> hour >> min >> sec; 
			hr = Hour(hour, min, sec);
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

	//---ATTENTION!---specific semantic
	template <typename IntType>
	inline double operator/ (const Deg<IntType> & a, const Deg<IntType> & b) noexcept
	{
		return a.toRad() / b.toRad();
	}

	//---ATTENTION!---specific semantic
	template <typename IntTypeA, typename IntTypeB>
	inline double operator/ (const Deg<IntTypeA> & a, const Deg<IntTypeB> & b) noexcept
	{
		return a.toRad() / b.toRad();
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

	//---ATTENTION!---specific semantic
	template <typename IntType>
	inline double operator/ (const Hour<IntType> & a, const Hour<IntType> & b) noexcept
	{
		return a.toRad() / b.toRad();
	}

	//---ATTENTION!---specific semantic
	template <typename IntTypeA, typename IntTypeB>
	inline double operator/ (const Hour<IntTypeA> & a, const Hour<IntTypeB> & b) noexcept
	{
		return a.toRad() / b.toRad();
	}

	//Deg / Hour cases
	//---ATTENTION!---specific semantic
	template <typename IntTypeD, typename IntTypeH>
	inline double operator/ (const Deg<IntTypeD> & d, const Hour<IntTypeH> & h) noexcept
	{
		return d.toRad() / h.toRad();
	}
	
	//---ATTENTION!---specific semantic
	template <typename IntTypeD, typename IntTypeH>
	inline double operator/ (const Hour<IntTypeH> & h, const Deg<IntTypeD> & d) noexcept
	{
		return h.toRad() / d.toRad();
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

	//---------------------Ops += type of----------
	//---------------------+= ---------------------
	//---Deg
	template <typename IntType, typename AriphmeticType>
	inline Deg<IntType> & operator+=(Deg<IntType> & d, const AriphmeticType a) noexcept
	{
		d = d + a;
		return d;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator+=(AriphmeticType & a, const Deg<IntType> & d) noexcept
	{
		a = a + d.toRad();
		return a;
	}

	template <typename IntTypeA, typename IntTypeB>
	inline Deg<IntTypeA> & operator+=(Deg<IntTypeA> & a, const Deg<IntTypeB> & b) noexcept
	{
		a = a + b;
		return a;
	}

	template <typename IntTypeD, typename IntTypeH>
	inline Deg<IntTypeD> & operator+=(Deg<IntTypeD> & d, const Hour<IntTypeH> & h) noexcept
	{
		d = d + h;
		return d;
	}

	//---Hour
	template <typename IntType, typename AriphmeticType>
	inline Hour<IntType> & operator+=(Hour<IntType> & h, const AriphmeticType a) noexcept
	{
		h = h + a;
		return h;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator+=(AriphmeticType & a, const Hour<IntType> & h) noexcept
	{
		a = a + h.toRad();
		return a;
	}

	template <typename IntTypeA, typename IntTypeB>
	inline Hour<IntTypeA> & operator+=(Hour<IntTypeA> & a, const Hour<IntTypeB> & b) noexcept
	{
		a = a + b;
		return a;
	}

	template <typename IntTypeD, typename IntTypeH>
	inline Hour<IntTypeD> & operator+=(Hour<IntTypeD> & h, const Deg<IntTypeH> & d) noexcept
	{
		h = d + h;
		return h;
	}

	//----------------------= ---------------------
	//---Deg
	template <typename IntType, typename AriphmeticType>
	inline Deg<IntType> & operator-=(Deg<IntType> & d, const AriphmeticType a) noexcept
	{
		d = d - a;
		return d;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator-=(AriphmeticType & a, const Deg<IntType> & d) noexcept
	{
		a = a - d.toRad();
		return a;
	}

	template <typename IntTypeA, typename IntTypeB>
	inline Deg<IntTypeA> & operator-=(Deg<IntTypeA> & a, const Deg<IntTypeB> & b) noexcept
	{
		a = a - b;
		return a;
	}

	template <typename IntTypeD, typename IntTypeH>
	inline Deg<IntTypeD> & operator-=(Deg<IntTypeD> & d, const Hour<IntTypeH> & h) noexcept
	{
		d = d - h;
		return d;
	}

	//---Hour
	template <typename IntType, typename AriphmeticType>
	inline Hour<IntType> & operator-=(Hour<IntType> & h, const AriphmeticType a) noexcept
	{
		h = h - a;
		return h;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator-=(AriphmeticType & a, const Hour<IntType> & h) noexcept
	{
		a = a - h.toRad();
		return a;
	}

	template <typename IntTypeA, typename IntTypeB>
	inline Hour<IntTypeA> & operator-=(Hour<IntTypeA> & a, const Hour<IntTypeB> & b) noexcept
	{
		a = a - b;
		return a;
	}

	template <typename IntTypeD, typename IntTypeH>
	inline Hour<IntTypeD> & operator-=(Hour<IntTypeD> & h, const Deg<IntTypeH> & d) noexcept
	{
		h = h - d;
		return h;
	}

	//---------------------*= ---------------------
	//---Deg
	template <typename IntType, typename AriphmeticType>
	inline Deg<IntType> & operator*=(Deg<IntType> & d, const AriphmeticType a) noexcept
	{
		d = d * a;
		return d;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator*=(AriphmeticType & a, const Deg<IntType> & d) noexcept
	{
		a = a * d.toRad();
		return a;
	}

	//---Hour
	template <typename IntType, typename AriphmeticType>
	inline Hour<IntType> & operator*=(Hour<IntType> & h, const AriphmeticType a) noexcept
	{
		h = h * a;
		return h;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator*=(AriphmeticType & a, const Hour<IntType> & h) noexcept
	{
		a = a * h.toRad();
		return a;
	}

	//---------------------/= ---------------------
	//---Deg
	template <typename IntType, typename AriphmeticType>
	inline Deg<IntType> & operator/=(Deg<IntType> & d, const AriphmeticType a) noexcept
	{
		d = d / a;
		return d;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator/=(AriphmeticType & a, const Deg<IntType> & d) noexcept
	{
		a = a / d.toRad();
		return a;
	}

	//---Hour
	template <typename IntType, typename AriphmeticType>
	inline Hour<IntType> & operator/=(Hour<IntType> & h, const AriphmeticType a) noexcept
	{
		h = h / a;
		return h;
	}

	template <typename IntType, typename AriphmeticType>
	inline AriphmeticType & operator/=(AriphmeticType & a, const Hour<IntType> & h) noexcept
	{
		a = a / h.toRad();
		return a;
	}

	//---------------------Op ++ ------------------
	template <typename IntType>
	inline Deg<IntType> & operator++(Deg<IntType> & a) noexcept
	{
		a += Deg<IntType>(0, 0, 1);
		return a;
	}

	template <typename IntType>
	inline Hour<IntType> & operator++(Hour<IntType> & a) noexcept
	{
		a += Hour<IntType>(0, 0, 1);
		return a;
	}

	//---------------------Op -- ------------------
	template <typename IntType>
	inline Deg<IntType> & operator--(Deg<IntType> & a) noexcept
	{
		a -= Deg<IntType>(0, 0, 1);
		return a;
	}

	template <typename IntType>
	inline Hour<IntType> & operator--(Hour<IntType> & a) noexcept
	{
		a -= Hour<IntType>(0, 0, 1);
		return a;
	}

	//---------------------UNARY + and - ----------
	template <typename IntType>
	inline const Deg<IntType> & operator+(const Deg<IntType> & a) noexcept
	{
		return a;
	}

	template <typename IntType>
	inline const Hour<IntType> & operator+(const Hour<IntType> & a) noexcept
	{
		return a;
	}
	
	template <typename IntType>
	inline const Deg<IntType> operator-(const Deg<IntType> & a) noexcept
	{
		return Deg<IntType>(-a.toRad());
	}

	template <typename IntType>
	inline const Hour<IntType> operator-(const Hour<IntType> & a) noexcept
	{
		return Hour<IntType>(-a.toRad());
	}


#endif // -- end OLD_ANGLIB__
}

#endif // -- end ANGLIB_HPP
