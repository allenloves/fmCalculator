/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencMeters_h
#define mencMeters_h

#include "mencRational.h"

namespace menc
{
  typedef Ratio Beat;
  
  class MetricWeights
  {
  public:
    static const MetricWeight Downbeat = 4;
    static const MetricWeight Strong = 3;
    static const MetricWeight Beat = 2;
    static const MetricWeight OffBeatOnDivision = 1;
    static const MetricWeight OffBeatOffDivision = 0;
    
    static String toString(MetricWeight s)
    {
      switch (s) 
        {
        case Downbeat:
          return ">";
        case Strong:
          return "=";
        case Beat:
          return "_";
        case OffBeatOnDivision:
          return ":";
        case OffBeatOffDivision:
          return ".";
        default:
          return "";
        }
    }

    static String toPrettyString(MetricWeight s)
    {
      return toString(s);
    }
  };

  class Meters
  {
  public:
    static const Meter Empty = 0;
    
    static const Meter CommonTime = 1;
    static const Meter CutTime = 2;
    
    static const Meter TwoTwo = 3;
    static const Meter ThreeTwo = 4;
    static const Meter FourTwo = 5;
    
    static const Meter TwoFour = 6;
    static const Meter ThreeFour = 7;
    static const Meter FourFour = 8;
    static const Meter SixFour = 9;
    static const Meter NineFour = 10;
    static const Meter TwelveFour = 11;
    
    static const Meter SixEight = 12;
    static const Meter NineEight = 13;
    static const Meter TwelveEight = 14;
    static const Meter Special = 15;
    
    static int numerator(Meter m)
    {
      switch(m)
        {
        case CommonTime:
          return 4;
        case CutTime:
          return 2;
        case TwoFour:
        case TwoTwo:
          return 2;
        case ThreeFour:
        case ThreeTwo:
          return 3;
        case FourFour:
        case FourTwo:
          return 4;
        case SixEight:
        case SixFour:
          return 6;
        case NineEight:
        case NineFour:
          return 9;
        case TwelveEight:
        case TwelveFour:
          return 12;
        default:
          return -1;
        }
    }
    
    static int denominator(Meter m)
    {
      switch(m)
        {
        case CommonTime:
          return 4;
        case CutTime:
          return 2;
        case TwoTwo:
        case ThreeTwo:
        case FourTwo:
          return 2;
        case TwoFour:
        case ThreeFour:
        case FourFour:
        case SixFour:
        case NineFour:
        case TwelveFour:
          return 4;
        case SixEight:
        case NineEight:
        case TwelveEight:
          return 8;
        default:
          return -1;
        }
    }
    
    static bool isSimple(Meter m)
    {
      switch(m)
        {
        case CommonTime:
        case CutTime:
        case TwoTwo:
        case ThreeTwo:
        case FourTwo:
        case TwoFour:
        case ThreeFour:
        case FourFour:
          return true;
        case SixEight:
        case NineEight:
        case TwelveEight:
        case SixFour:
        case NineFour:
        case TwelveFour:
        default:
          return false;
        }
    }
    
    static bool isCompound(Meter m)
    {
      return (!isSimple(m));
    }
    
    static MetricWeight determineStress(Meter m, Beat beat)
    {
      beat = Ratio::mod(beat, Ratio(numerator(m),denominator(m)));
      
      if(beat==0)
        return MetricWeights::Downbeat;
      
      switch(m)
        {
        case CommonTime:
        case FourFour:
          if(beat==(Ratio)2/4)
            return MetricWeights::Strong;
          else if(beat.den()==4)
            return MetricWeights::Beat;
          else if(beat.den()==8)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case FourTwo:
          if(beat==(Ratio)2/2)
            return MetricWeights::Strong;
          else if(beat.den()==2)
            return MetricWeights::Beat;
          else if(beat.den()==4)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case CutTime:
        case TwoTwo:
          if(beat==(Ratio)1/2)
            return MetricWeights::Beat;
          else if(beat.den()==4)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
        case TwoFour:
          if(beat==(Ratio)1/4)
            return MetricWeights::Beat;
          else if(beat.den()==8)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
        case ThreeFour:
          if(beat==(Ratio)1/4 || beat==(Ratio)2/4)
            return MetricWeights::Beat;
          else if(beat.den()==8)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case ThreeTwo:
          if(beat==(Ratio)1/2 || beat==(Ratio)2/2)
            return MetricWeights::Beat;
          else if(beat.den()==4)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case SixEight: //Compound
          if(beat==(Ratio)3/8)
            return MetricWeights::Beat;
          else if(beat.den()==8 || beat.den()==4 || beat.den()==2 || beat.den()==1)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case SixFour: //Compound
          if(beat==(Ratio)3/4)
            return MetricWeights::Beat;
          else if(beat.den()==4 || beat.den()==2 || beat.den()==1 )
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case NineEight: //Compound
          if(beat==(Ratio)3/8 || beat==(Ratio)6/8)
            return MetricWeights::Beat;
          else if(beat.den()==8 || beat.den()==4 || beat.den()==2 || beat.den()==1)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case NineFour: //Compound
          if(beat==(Ratio)3/4 || beat==(Ratio)3/2)
            return MetricWeights::Beat;
          else if(beat.den()==4 || beat.den()==2 || beat.den()==1 )
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case TwelveEight: //Compound
          if(beat==(Ratio)6/8)
            return MetricWeights::Strong;
          else if(beat==(Ratio)3/8 || beat==(Ratio)9/8)
            return MetricWeights::Beat;
          else if(beat.den()==8 || beat.den()==4 || beat.den()==2 || beat.den()==1)
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        case TwelveFour: //compound
          if(beat==(Ratio)3/4)
            return MetricWeights::Strong;
          else if(beat==(Ratio)3/4 || beat==(Ratio)9/4)
            return MetricWeights::Beat;
          else if(beat.den()==4 || beat.den()==2 || beat.den()==1 )
            return MetricWeights::OffBeatOnDivision;
          else
            return MetricWeights::OffBeatOffDivision;
          
        default:
          return MetricWeights::Beat;
        }
    }
    
    /** Returns the amount of time one measure of the meter occupies
        in notational units: 1/4 = quarter, 1 = whole note, etc. **/

    static Ratio measureDuration(Meter m)
    {
      return Ratio(numerator(m), denominator(m));
    }

    static String toString(Meter m)
    {
      if (m==Empty)
        return "empty";
      if (m==Special)
        return "special";
      String meter_string=String::intToString(numerator(m));
      meter_string += "/";
      meter_string += String::intToString(denominator(m));
      return meter_string;
    }
    
    static String toPrettyString(Meter m)
    {
      return toString(m);
    }

    static Meter fromString(String name)
    {
      if (name.contains("ut"))
        return Meters::CutTime;
      else if (name.contains("ommon"))
        return Meters::CommonTime;
      else 
        {
          String num="";
          String den="";
          for (size_t i=0; i < name.length(); i++) 
            {
              if (name[i]=='/') 
                {
                  num=name.substring(0, i);
                  den=name.substring(i+1);
                  break;
                }
            }
          if (den=="2") 
            {
              if (num=="2")
                return Meters::TwoTwo;
              else if (num=="3")
                return Meters::ThreeTwo;
              else if (num=="4")
                return Meters::FourTwo;
            }
          else if (den=="4") 
            {
              if (num=="2")
                return Meters::TwoFour;
              else if (num=="3")
                return Meters::ThreeFour;
              else if (num=="4")
                return Meters::FourFour;
            }
          else if (den=="8") 
            {
              if (num=="6")
                return Meters::SixEight;
              else if (num=="9")
                return Meters::NineEight;
              else if (num=="12")
                return Meters::TwelveEight;
            }
          return Meters::Empty;
        }
    } 
  };
}
#endif
