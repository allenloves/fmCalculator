/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencRational_h
#define mencRational_h

#include "mencTypes.h"
#include "mencString.h"
#include <math.h>

namespace menc
{
  ///A templated class for expressing rational numbers.
  template <class IntegralType>
  class Rational
  {
  protected:
    /**The numerator of the Rational number. It is always expressed in its
    simplest form.*/
    IntegralType n;

    /**The denominator of the Rational number. It is always expressed in its
    simplest form.*/
    IntegralType d;

    void simplifySign(void)
    {
      if(d<0)
      {
        n=-n;
        d=-d;
      }
    }

    void simplifyRatio(void)
    {
      if(d==0) //Indeterminate form
      {
        n=0;
        return;
      }

      if(n==0) //Zero: assume denominator of one for consistency.
      {
        d=1;
        return;
      }

      IntegralType g = gcd(n,d);
      while(g!=1)
      {
        n = n / g;
        d = d / g;
        g = gcd(n,d);
      }
    }

    void simplify(void)
    {
      simplifySign();
      simplifyRatio();
    }

  public:
    
    /** Constructor for an empty ratio (not 0!) **/

    Rational() : n(0), d(0) {}

    Rational(IntegralType numerator, IntegralType denominator)
    {
      n=numerator;
      d=denominator;
      simplify();
    }

    Rational(IntegralType whole_number)
    {
      n=whole_number;
      d=1;
    }

    Rational(String str)
    {
      *this = fromString(str);
    }

    IntegralType num(void)
    {
      return n;
    }

    IntegralType den(void)
    {
      return d;
    }

    bool isDeterminate(void)
    {
      return (d!=0);
    }

    bool isWhole(void)
    {
      return (d==1);
    }

    bool isEmpty(void)
    {
      return (d==0);
    }

    bool isInvalid(void)
    {
      return isEmpty();
    }

    static IntegralType gcd(IntegralType a, IntegralType b)
    {
      //Test for zeroes.
      if(a == 0 || b == 0)
        return 0;

      //"Naturalize" the numbers.
      if(a < 0) a = -a;
      if(b < 0) b = -b;

      //Use the iterative Euclidean algorithm.
      //For more information, see:
      //http://en.wikipedia.org/wiki/Euclidean_algorithm#Using_iteration
      IntegralType t;
      while(b!=0)
      {
        t = b;
        b = a % b;
        a = t;
      }
      return a;
    }

    static IntegralType lcm(IntegralType a, IntegralType b)
    {
      //Test for zeroes.
      if(a == 0 || b == 0)
        return 0;

      //"Naturalize" the numbers.
      if(a < 0) a = -a;
      if(b < 0) b = -b;

      //Use the gcd to calculate the lcm
      return (a * b) / gcd(a,b);
    }

    static Rational<IntegralType> mod(
      Rational<IntegralType> a, 
      Rational<IntegralType> b)
    {
      IntegralType new_d=lcm(a.d,b.d);
      IntegralType a_mult=new_d/a.d;
      IntegralType b_mult=new_d/b.d;
      a.n*=a_mult;
      b.n*=b_mult;
      a.d=new_d;
      b.d=new_d;

      //Now a and b have the same denominator.
      IntegralType new_n=a.n % b.n;

      return Rational<IntegralType>(new_n,new_d);
    }

    //--------------------//
    //Operator definitions//
    //--------------------//

    Rational<IntegralType> operator+(Rational<IntegralType> other)
    {
      IntegralType lcd = lcm(d,other.d);
      IntegralType new_d = lcd;
      IntegralType new_n = n * (lcd / d) + other.n * (lcd / other.d);
      return Rational<IntegralType>(new_n,new_d);
    }

    Rational<IntegralType> operator+(IntegralType other)
    {
      return *this + Rational<IntegralType>(other,1);
    }

    Rational<IntegralType> operator+(String other)
    {
      return *this + Rational<IntegralType>(other);
    }

    Rational<IntegralType> operator-(Rational<IntegralType> other)
    {
      IntegralType lcd = lcm(d,other.d);
      IntegralType new_d = lcd;
      IntegralType new_n = n * (lcd / d) - other.n * (lcd / other.d);
      return Rational<IntegralType>(new_n,new_d);
    }

    Rational<IntegralType> operator-(IntegralType other)
    {
      return *this - Rational<IntegralType>(other,1);
    }

    Rational<IntegralType> operator-(String other)
    {
      return *this - Rational<IntegralType>(other);
    }

    Rational<IntegralType> operator*(Rational<IntegralType> other)
    {
      IntegralType new_n = n * other.n;
      IntegralType new_d = d * other.d;
      return Rational<IntegralType>(new_n,new_d);
    }

    Rational<IntegralType> operator*(IntegralType other)
    {
      return *this * Rational<IntegralType>(other,1);
    }

    Rational<IntegralType> operator*(String other)
    {
      return *this * Rational<IntegralType>(other);
    }

    Rational<IntegralType> operator/(Rational<IntegralType> other)
    {
      IntegralType new_n = n * other.d;
      IntegralType new_d = d * other.n;
      return Rational<IntegralType>(new_n,new_d);
    }

    Rational<IntegralType> operator/(IntegralType other)
    {
      return *this / Rational<IntegralType>(other,1);
    }

    Rational<IntegralType> operator/(String other)
    {
      return *this / Rational<IntegralType>(other);
    }

    Rational<IntegralType> operator+=(Rational<IntegralType> other)
    {
      *this = *this + other;
      return *this;
    }

    Rational<IntegralType> operator+=(IntegralType other)
    {
      *this = *this + Rational<IntegralType>(other,1);
      return *this;
    }

    Rational<IntegralType> operator+=(String other)
    {
      *this = *this + Rational<IntegralType>(other);
      return *this;
    }

    Rational<IntegralType> operator-=(Rational<IntegralType> other)
    {
      *this = *this + other;
      return *this;
    }

    Rational<IntegralType> operator-=(IntegralType other)
    {
      *this = *this - Rational<IntegralType>(other,1);
      return *this;
    }

    Rational<IntegralType> operator-=(String other)
    {
      *this = *this - Rational<IntegralType>(other);
      return *this;
    }

    Rational<IntegralType> operator*=(Rational<IntegralType> other)
    {
      *this = *this * other;
      return *this;
    }

    Rational<IntegralType> operator*=(IntegralType other)
    {
      *this = *this * Rational<IntegralType>(other,1);
      return *this;
    }

    Rational<IntegralType> operator*=(String other)
    {
      *this = *this * Rational<IntegralType>(other);
      return *this;
    }

    Rational<IntegralType> operator/=(Rational<IntegralType> other)
    {
      *this = *this / other;
      return *this;
    }

    Rational<IntegralType> operator/=(IntegralType other)
    {
      *this = *this / Rational<IntegralType>(other,1);
      return *this;
    }

    Rational<IntegralType> operator/=(String other)
    {
      *this = *this / Rational<IntegralType>(other);
      return *this;
    }

    Rational<IntegralType> operator=(Rational<IntegralType> other)
    {
      n=other.n;
      d=other.d;
      return *this;
    }

    Rational<IntegralType> operator=(IntegralType other)
    {
      n=other;
      d=1;
      return *this;
    }

    Rational<IntegralType> operator=(String other)
    {
      *this = fromString(other);
      return *this;
    }

    Rational<IntegralType> operator++(int dummy)
    {
      n = n + d;
      return *this;
    }

    Rational<IntegralType> operator--(int dummy)
    {
      n = n - d;
      return *this;
    }

    Rational<IntegralType> operator-()
    {
      return (*this * -1);
    }

    bool operator==(Rational<IntegralType> other)
    {
      return (n == other.n && d == other.d);
    }

    bool operator==(IntegralType other)
    {
      return (n == other && d == 1);
    }

    bool operator==(String other)
    {
      Rational<IntegralType> r(other);
      return (n == r.n && d == r.d);
    }

    bool operator!=(Rational<IntegralType> other)
    {
      return (n != other.n || d != other.d);
    }

    bool operator!=(IntegralType other)
    {
      return (n != other || d != 1);
    }

    bool operator!=(String other)
    {
      Rational<IntegralType> r(other);
      return (n != r.n || d != r.d);
    }

    bool operator>(Rational<IntegralType> other)
    {
      Rational<IntegralType> difference = *this - other;
      return (difference.n>0);
    }

    bool operator>(IntegralType other)
    {
      Rational<IntegralType> difference = *this - 
        Rational<IntegralType>(other,1);
      return (difference.n>0);
    }

    bool operator>(String other)
    {
      Rational<IntegralType> r(other);
      Rational<IntegralType> difference = *this - r;
      return (difference.n>0);
    }

    bool operator>=(Rational<IntegralType> other)
    {
      Rational<IntegralType> difference = *this - other;
      return (difference.n>=0);
    }

    bool operator>=(IntegralType other)
    {
      Rational<IntegralType> difference = *this - 
        Rational<IntegralType>(other,1);
      return (difference.n>=0);
    }

    bool operator>=(String other)
    {
      Rational<IntegralType> r(other);
      Rational<IntegralType> difference = *this - r;
      return (difference.n>=0);
    }

    bool operator<(Rational<IntegralType> other)
    {
      Rational<IntegralType> difference = *this - other;
      return (difference.n<0);
    }

    bool operator<(IntegralType other)
    {
      Rational<IntegralType> difference = *this - 
        Rational<IntegralType>(other,1);
      return (difference.n<0);
    }

    bool operator<(String other)
    {
      Rational<IntegralType> r(other);
      Rational<IntegralType> difference = *this - r;
      return (difference.n<0);
    }

    bool operator<=(Rational<IntegralType> other)
    {
      Rational<IntegralType> difference = *this - other;
      return (difference.n<=0);
    }

    bool operator<=(IntegralType other)
    {
      Rational<IntegralType> difference = *this - 
        Rational<IntegralType>(other,1);
      return (difference.n<=0);
    }

    bool operator<=(String other)
    {
      Rational<IntegralType> r(other);
      Rational<IntegralType> difference = *this - r;
      return (difference.n<=0);
    }

    //-------//
    //Helpers//
    //-------//

    String toString(void)
    {
      if (d==0) return "NaN";
      String str=String::intToString(n);
      str += "/";
      str += String::intToString(d);
      return str;
    }

    String toPrettyString(void)
    {
      if (d==0) return "indeterminate";

      String str=String::intToString(n);
 
      if (n != 0 && d != 1)  {
        str += "/";
        str += String::intToString(d);
      }
      return str;
    }

    static Rational<IntegralType> fromString(String str)
    {
      int len = str.length();
      IntegralType numerator=0;
      IntegralType denominator=0;
      bool isPastSlash=false;
      bool isInvalid=false;
      for (int i=0;i<len;i++)
      {
        char c=(char)str[i];
        if (c=='/') 
        {
          // invalid use of slash
          if (i==0 || i==len-1 || isPastSlash)
            {
              isInvalid=true;
              break;
            }
          isPastSlash=true;
        }
        else if (!isPastSlash) 
        {
          if(c>=48 && c<=57)
            numerator=numerator*10+(c-48);
          else
            {
              // invalid (non-digit) char
              isInvalid=true;
              break;
            }
        }
        else 
        {
          if(c>=48 && c<=57)
            denominator=denominator*10+(c-48);
          else
            {
              // invalid (non-digit) denominator
              isInvalid=true;
              break;
            }
        }
      }

      // denominator 0 means invalid (empty) ratio
      if (isInvalid)
        {
          numerator=0;
          denominator=0;
        }
      else
        {
        if(!isPastSlash)
          denominator=1;
        }

      return Rational<IntegralType>(numerator,denominator);
    }

    operator String(void)
    {
      return toPrettyString();
    }

    template <class numeric>
    operator numeric(void)
    {
      return to<numeric>();
    }

    template <class numeric>
    numeric to(void)
    {
      if(d==0)
        return 0; //Indeterminate case
      else
        return ((numeric)n) / ((numeric)d);
    }
  };

  //Template instantiations
  typedef Rational<int32> Ratio64;
  typedef Rational<int16> Ratio32;
  typedef Rational<int8>  Ratio16;
  typedef Ratio64 Ratio;

}

#endif
