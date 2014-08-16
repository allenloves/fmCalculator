/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
  *=======================================================================*/

#ifndef mencBeams_h
#define mencBeams_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{

  /** BeamLevel enumerates all the beaming levels, ie the metric
      weight of each beam. **/

  class BeamLevels
  {

  public:

    static const BeamLevel Empty = 0;
    static const BeamLevel Eighth = 8;
    static const BeamLevel Sixteenth = 16;
    static const BeamLevel ThirtySecond = 32;
    static const BeamLevel SixtyFourth = 64;
    static const BeamLevel HundredTwentyEighth = 128;

    static BeamLevel fromString(String str)
    {
      if (str=="8") return Eighth;
      if (str=="16") return Sixteenth;
      if (str=="32") return ThirtySecond;
      if (str=="64") return SixtyFourth;
      if (str=="128") return HundredTwentyEighth;
      return Empty;
    }

    static String toString(BeamLevel lev)
    {
      switch (lev)
      {
      case Eighth: return "8";
      case Sixteenth: return "16";
      case ThirtySecond: return "32";
      case SixtyFourth: return "64";
      case HundredTwentyEighth: return "128";
      default: return "Empty";
      }
    }

  };

  /** BeamParts enumerate the left-to-right "parts" of a beam. Each
      note under a beam holds one of these values for each of its
      beams. Encoded as:

          76543210    
          sssspppp    s=style p=part
  **/

  class BeamParts
  {

  public:

    /// Styles
    static const int Standard = 1 << 4;   /// Standard beams (attach to two or more notes).
    static const int Partial  = 2 << 4;   /// Unattached or "hook" beams.
    static const int Tremolo  = 3 << 4;   /// Tremolo beams.
    static const int Feather  = 4 << 4;   /// Feather beams.

    /// Parts
    static const int Left = 1 ;    /// Start of beam.
    static const int Right = 2;    /// End of beam.
    static const int Interior = 3; /// Continues both sides (left + right)

    static const BeamPart Empty = 0;
    /** Standard beam start. **/
    static const BeamPart Begin = Standard + Left;
    /** Standard beam end. **/
    static const BeamPart End = Standard + Right;
    /** Standard beam both sides. **/
    static const BeamPart Continue = Standard + Interior;

    /** Partial (unattached) beam facing forward. **/
    static const BeamPart PartialForward = Partial + Left;
    /** Partial (unattached) beam facing backward. **/
    static const BeamPart PartialBackward = Partial + Right;

    /** Tremolo beam start. **/
    static const BeamPart TremoloBegin = Tremolo + Left;
    /** Tremolo bean end. **/
    static const BeamPart TremoloEnd = Tremolo + Right;

    /** The start of a feather beam. **/
    static const BeamPart FeatherBegin = Feather + Left;
    /** The interiour of a feather beam. **/
    static const BeamPart FeatherContinue = Feather + Interior;
    /** The end of a feather beam. **/
    static const BeamPart FeatherEnd = Feather + Right;

    /** Create a beam part from a string description. **/
    static BeamPart fromString(String str)
    {
      if (str.equalsIgnoreCase("begin")) return Begin;
      if (str.equalsIgnoreCase("end")) return End;
      if (str.equalsIgnoreCase("continue")) return Continue;
      if (str.equalsIgnoreCase("partial-forward")) return PartialForward;
      if (str.equalsIgnoreCase("partial-backward")) return PartialBackward;
      if (str.equalsIgnoreCase("tremolo-begin")) return TremoloBegin;
      if (str.equalsIgnoreCase("tremolo-end")) return TremoloEnd;
      if (str.equalsIgnoreCase("feather-begin")) return FeatherBegin;
      if (str.equalsIgnoreCase("feather-end")) return FeatherEnd;
      if (str.equalsIgnoreCase("feather-continue")) return FeatherContinue;
      return Empty;
    }

    /** Returns a string description of a beam part. **/

    static String toString(BeamPart bp)
    {
      switch (bp)
      {
      case Begin: return "begin";
      case End: return "end";
      case Continue: return "continue";
      case PartialForward: return "partial-forward";
      case PartialBackward: return "partial-backward";
      case TremoloBegin: return "tremolo-begin";
      case TremoloEnd: return "tremolo-end";
      case FeatherBegin: return "feather-begin";
      case FeatherEnd: return "feather-end";
      case FeatherContinue: return "feather-continue";
      default: return "";
      }
    }

  };

  /** Beams are defind over multiple notes where each note contains a
      beaming value where the upper byte is the BeamPart and the lower
      byte holds the BeamLevel.

          76543210 76543210
          llllllll --------    BeamLevel
          -------- sssspppp    BeamPart (s=style, p=position)

  **/

  class Beams
  {

  private:

    static const int Shift = 8;

  public:

    static const Beam Empty = 0;
    static const Beam EighthBegin = (BeamLevels::Eighth << Shift) + BeamParts::Begin;
    static const Beam EighthEnd = (BeamLevels::Eighth << Shift) + BeamParts::End;
    static const Beam EighthContinue = (BeamLevels::Eighth << Shift) + BeamParts::Continue;
    static const Beam SixteenthBegin = (BeamLevels::Eighth << Shift) + BeamParts::Begin;
    static const Beam SixteenthEnd = (BeamLevels::Sixteenth << Shift) + BeamParts::End;
    static const Beam SixteenthContinue = (BeamLevels::Sixteenth << Shift) + BeamParts::Continue;
    static const Beam ThirtySecondBegin = (BeamLevels::ThirtySecond << Shift) + BeamParts::Begin;
    static const Beam ThirtySecondEnd = (BeamLevels::ThirtySecond << Shift) + BeamParts::End;
    static const Beam ThirtySecondContinue = (BeamLevels::ThirtySecond << Shift) + BeamParts::Continue;
    static const Beam SixtyFourthBegin = (BeamLevels::SixtyFourth << Shift) + BeamParts::Begin;
    static const Beam SixtyFourthEnd = (BeamLevels::SixtyFourth << Shift) + BeamParts::End;
    static const Beam SixtyFourthContinue = (BeamLevels::SixtyFourth << Shift) + BeamParts::Continue;
    static const Beam HundredTwentyEighthBegin = (BeamLevels::HundredTwentyEighth << Shift) + BeamParts::Begin;
    static const Beam HundredTwentyEighthEnd = (BeamLevels::HundredTwentyEighth << Shift) + BeamParts::End;
    static const Beam HundredTwentyEighthContinue = (BeamLevels::HundredTwentyEighth << Shift) + BeamParts::Continue;

    static const Beam EighthTremoloBegin = (BeamLevels::Eighth << Shift) + BeamParts::Begin;
    static const Beam EighthTremoloEnd = (BeamLevels::Eighth << Shift) + BeamParts::End;
    static const Beam SixteenthTremoloBegin = (BeamLevels::Sixteenth << Shift) + BeamParts::Begin;
    static const Beam SixteenthTremoloEnd = (BeamLevels::Sixteenth << Shift) + BeamParts::End;
    static const Beam ThirtySecondTremoloBegin = (BeamLevels::ThirtySecond << Shift) + BeamParts::Begin;
    static const Beam ThirtySecondTremoloEnd = (BeamLevels::ThirtySecond << Shift) + BeamParts::End;
    static const Beam SixtyFourthTremoloBegin = (BeamLevels::SixtyFourth << Shift) + BeamParts::Begin;
    static const Beam SixtyFourthTremoloEnd = (BeamLevels::SixtyFourth << Shift) + BeamParts::End;
    static const Beam HundredTwentyEighthTremoloBegin = (BeamLevels::HundredTwentyEighth << Shift) + BeamParts::Begin;
    static const Beam HundredTwentyEighthTremoloEnd = (BeamLevels::HundredTwentyEighth << Shift) + BeamParts::End;

    static const Beam EighthPartialForward = (BeamLevels::Eighth << Shift) + BeamParts::PartialForward;   // doesn't exist
    static const Beam EighthPartialBackward = (BeamLevels::Eighth << Shift) + BeamParts::PartialBackward; // doesn't exist
    static const Beam SixteenthPartialForward = (BeamLevels::Sixteenth << Shift) + BeamParts::PartialForward;
    static const Beam SixteenthPartialBackward = (BeamLevels::Sixteenth << Shift) + BeamParts::PartialBackward;
    static const Beam ThirtySecondPartialForward = (BeamLevels::ThirtySecond << Shift) + BeamParts::PartialForward;
    static const Beam ThirtySecondPartialBackward = (BeamLevels::ThirtySecond << Shift) + BeamParts::PartialBackward;
    static const Beam SixtyFourthPartialForward = (BeamLevels::SixtyFourth << Shift) + BeamParts::PartialForward;
    static const Beam SixtyFourthPartialBackward = (BeamLevels::SixtyFourth << Shift) + BeamParts::PartialBackward;
    static const Beam HundredTwentyEighthPartialForward = (BeamLevels::HundredTwentyEighth << Shift) + BeamParts::PartialForward;
    static const Beam HundredTwentyEighthPartialBackward = (BeamLevels::HundredTwentyEighth << Shift) + BeamParts::PartialBackward;

    /** Creates a beam from a beaming level and part **/

    static Beam fromLevelAndPart (BeamLevel level, BeamPart part)
    {
      return (level << Shift) + part;
    }

    /** Returns the beaming level of a beam. **/

    static BeamLevel getBeamLevel(Beam beam)
    {
      return (beam & 0xFF00) >> Shift;
    }
    
    /** Returns the beam part of a beam **/

    static BeamPart getBeamPart(Beam beam)
    {
      return (beam & 0xFF);
    }

    static Beam fromString (String str)
    {
      int split=str.indexOfChar('-');
      if (split<0) return Empty;
      BeamLevel l=BeamLevels::fromString(str.substring(0, split));
      if (l==BeamLevels::Empty) return Empty;
      BeamPart p=BeamParts::fromString(str.substring(split+1));
      if (p==BeamParts::Empty) return Empty;
      return fromLevelAndPart(l,p);
      
    }

    static String toString (Beam beam)
    {
      BeamLevel l=getBeamLevel(beam);
      BeamPart p=getBeamPart(beam);
      if (l==BeamLevels::Empty || p==BeamParts::Empty) return "";
      String str=BeamLevels::toString(l);
      str += "-";
      str += BeamParts::toString(p);
      return str;
    }
  };

}

#endif
