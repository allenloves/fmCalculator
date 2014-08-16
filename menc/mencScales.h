/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencScales_h
#define mencScales_h

#include "mencPitches.h"

namespace menc
{

  class ScaleDegrees
  {
    static const int DegreeShift=4;

  public:

    static const int Diatonic = 0;
    static const int Lowered = 1;
    static const int Raised = 2;

    static const ScaleDegree Empty=0;
    static const ScaleDegree Tonic = 1 << DegreeShift;
    static const ScaleDegree LoweredTonic = Tonic + Lowered;
    static const ScaleDegree RaisedTonic = Tonic + Raised;
    static const ScaleDegree Supertonic = 2 << DegreeShift;
    static const ScaleDegree LoweredSupertonic = Supertonic + Lowered;
    static const ScaleDegree RaisedSupertonic = Supertonic + Raised;
    static const ScaleDegree Mediant = 3 << DegreeShift;
    static const ScaleDegree LoweredMediant = Mediant + Lowered;
    static const ScaleDegree RaisedMediant = Mediant + Raised;
    static const ScaleDegree Subdominant = 4 << DegreeShift;
    static const ScaleDegree LoweredSubdominant = Subdominant + Lowered;
    static const ScaleDegree RaisedSubdominant = Subdominant + Raised;

    static const ScaleDegree Dominant = 5 << DegreeShift;
    static const ScaleDegree LoweredDominant = Dominant + Lowered;
    static const ScaleDegree RaisedDominant = Dominant + Raised;

    static const ScaleDegree Submediant = 6 << DegreeShift;
    static const ScaleDegree LoweredSubmediant = Submediant + Lowered;
    static const ScaleDegree RaisedSubmediant = Submediant + Raised;

    static const ScaleDegree LeadingTone = 7 << DegreeShift;
    static const ScaleDegree LoweredLeadingTone = LeadingTone + Lowered;
    static const ScaleDegree RaisedLeadingTone = LeadingTone + Raised;

    static const ScaleDegree Wild = (8 << DegreeShift) + Lowered + Raised;


    static int inflection(ScaleDegree s)
    {
      return (s & 0xF);
    }

    static bool isDiatonic(ScaleDegree s)
    {
      return (inflection(s)==Diatonic);
    }

    static bool isRaised(ScaleDegree s)
    {
      return (inflection(s)==Raised);
    }

    static bool isLowered(ScaleDegree s)
    {
      return (inflection(s)==Lowered);
    }

    static bool isWild(ScaleDegree s)
    {
      return (s==Wild);
    }

    static int degree(ScaleDegree s)
    {
      return (s & 0xF0);
    }

    static int rank(ScaleDegree s)
    {
      return (degree(s) >> DegreeShift);
    }

    static ScaleDegree fromRank(int r)
    {
      if(r <= 0 || r > 7)
        return Empty;
      else
        return (r << DegreeShift);
    }

    /** convert a pitch to a scale degree based off C */

    static ScaleDegree fromPitch(Pitch p)
    {
      switch (p)
        {
        case Pitches::Cf: return LoweredTonic;
        case Pitches::C: return Tonic;
        case Pitches::Cs: return RaisedTonic;
        case Pitches::Df: return LoweredSupertonic;
        case Pitches::D: return Supertonic;
        case Pitches::Ds: return RaisedSupertonic;
        case Pitches::Ef: return LoweredMediant;
        case Pitches::E: return Mediant;
        case Pitches::Es: return RaisedMediant;
        case Pitches::Ff: return LoweredSubdominant;
        case Pitches::F: return Subdominant;
        case Pitches::Fs: return RaisedSubdominant;
        case Pitches::Gf: return LoweredDominant;
        case Pitches::G: return Dominant;
        case Pitches::Gs: return RaisedDominant;
        case Pitches::Af: return LoweredSubmediant;
        case Pitches::A: return Submediant;
        case Pitches::As: return RaisedSubmediant;
        case Pitches::Bf: return LoweredLeadingTone;
        case Pitches::B: return LeadingTone;
        case Pitches::Bs: return RaisedLeadingTone;
        default: return Empty;
        }
    }

    static Pitch toPitch(ScaleDegree deg)
    {
      switch (deg)
        {
        case LoweredTonic: return Pitches::Cf;
        case Tonic: return Pitches::C;
        case RaisedTonic: return Pitches::Cs;
        case LoweredSupertonic: return Pitches::Df;
        case Supertonic: return Pitches::D;
        case RaisedSupertonic: return Pitches::Ds;
        case LoweredMediant: return Pitches::Ef;
        case Mediant: return Pitches::E;
        case RaisedMediant: return Pitches::Es;
        case LoweredSubdominant: return Pitches::Ff;
        case Subdominant: return Pitches::F;
        case RaisedSubdominant: return Pitches::Fs;
        case LoweredDominant: return Pitches::Gf;
        case Dominant: return Pitches::G;
        case RaisedDominant: return Pitches::Gs;
        case LoweredSubmediant: return Pitches::Af;
        case Submediant: return Pitches::A;
        case RaisedSubmediant: return Pitches::As;
        case LoweredLeadingTone: return Pitches::Bf;
        case LeadingTone: return Pitches::B;
        case RaisedLeadingTone: return Pitches::Bs;
        default: return Pitches::Empty;
        }
    }

    static String toString(ScaleDegree d)
    {
      if (d==Empty) return "Empty";
      String str;
      str=String::intToString(rank(d));
      if (isLowered(d))
        {
          String pre ("b");
          pre += str;
          return pre;
        }
      else if (isRaised(d))
        {
          String pre ("#");
          pre += str;
          return pre;
        }
      return str;
    }

    String toPrettyString(ScaleDegree d)
    {
      if (d==Empty) return "Empty";
      String str;
      if (isRaised(d))
        str="Raised ";
      else if (isLowered(d))
        str="Lowered";
      switch (degree(d))
      {
      case Tonic:
        str += "Tonic"; break;
      case Supertonic:
        str += "Supertonic"; break;
      case Mediant:
        str += "Mediant"; break;
      case Subdominant:
        str += "Subdominant"; break;
      case Dominant:
        str += "Domiant"; break;
      case Submediant:
        str += "Submediant"; break;
      case LeadingTone:
        str += "LeadingTone"; break;
      default:
        return "Empty";
      }
      return str;
    }
  };
}

#endif

