/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencPitches_h
#define mencPitches_h

#include "mencLetters.h"
#include "mencAccidentals.h"

namespace menc
{

 /** Pitches enumerates all possible combinations of Letter (L) and
     Accidental (A) in 6 bits: LLLAAA */

  class Pitches
  {
    //  private:
    //    static const int32 LetterBits = 3;
    //    static const int32 LetterMod  = 1 << LetterBits;
  public:
    static const Pitch Cff = (Letters::C << LetterBits) + Accidentals::DoubleFlat;
    static const Pitch Cf  = (Letters::C << LetterBits) + Accidentals::Flat;
    static const Pitch C   = (Letters::C << LetterBits) + Accidentals::Natural;
    static const Pitch Cs  = (Letters::C << LetterBits) + Accidentals::Sharp;
    static const Pitch Css = (Letters::C << LetterBits) + Accidentals::DoubleSharp;

    static const Pitch Dff = (Letters::D << LetterBits) + Accidentals::DoubleFlat;
    static const Pitch Df  = (Letters::D << LetterBits) + Accidentals::Flat;
    static const Pitch D   = (Letters::D << LetterBits) + Accidentals::Natural;
    static const Pitch Ds  = (Letters::D << LetterBits) + Accidentals::Sharp;
    static const Pitch Dss = (Letters::D << LetterBits) + Accidentals::DoubleSharp;

    static const Pitch Eff = (Letters::E << LetterBits) + Accidentals::DoubleFlat;
    static const Pitch Ef  = (Letters::E << LetterBits) + Accidentals::Flat;
    static const Pitch E   = (Letters::E << LetterBits) + Accidentals::Natural;
    static const Pitch Es  = (Letters::E << LetterBits) + Accidentals::Sharp;
    static const Pitch Ess = (Letters::E << LetterBits) + Accidentals::DoubleSharp;

    static const Pitch Fff = (Letters::F << LetterBits) + Accidentals::DoubleFlat;
    static const Pitch Ff  = (Letters::F << LetterBits) + Accidentals::Flat;
    static const Pitch F   = (Letters::F << LetterBits) + Accidentals::Natural;
    static const Pitch Fs  = (Letters::F << LetterBits) + Accidentals::Sharp;
    static const Pitch Fss = (Letters::F << LetterBits) + Accidentals::DoubleSharp;

    static const Pitch Gff = (Letters::G << LetterBits) + Accidentals::DoubleFlat;
    static const Pitch Gf  = (Letters::G << LetterBits) + Accidentals::Flat;
    static const Pitch G   = (Letters::G << LetterBits) + Accidentals::Natural;
    static const Pitch Gs  = (Letters::G << LetterBits) + Accidentals::Sharp;
    static const Pitch Gss = (Letters::G << LetterBits) + Accidentals::DoubleSharp;

    static const Pitch Aff = (Letters::A << LetterBits) + Accidentals::DoubleFlat;
    static const Pitch Af  = (Letters::A << LetterBits) + Accidentals::Flat;
    static const Pitch A   = (Letters::A << LetterBits) + Accidentals::Natural;
    static const Pitch As  = (Letters::A << LetterBits) + Accidentals::Sharp;
    static const Pitch Ass = (Letters::A << LetterBits) + Accidentals::DoubleSharp;

    static const Pitch Bff = (Letters::B << LetterBits) + Accidentals::DoubleFlat;
    static const Pitch Bf  = (Letters::B << LetterBits) + Accidentals::Flat;
    static const Pitch B   = (Letters::B << LetterBits) + Accidentals::Natural;
    static const Pitch Bs  = (Letters::B << LetterBits) + Accidentals::Sharp;
    static const Pitch Bss = (Letters::B << LetterBits) + Accidentals::DoubleSharp;

    static const Pitch Wild = (Letters::Wild << LetterBits) + Accidentals::Wild;
    static const Pitch Empty = -1;

    friend class Accidentals;
    friend class Letters;

    /** Create a Pitch from a Letter and Accidental **/

    static Pitch fromLetterAccidental(Letter letter, Accidental accidental)
    {
      if(letter >= 0 && accidental >= 0)
        return (letter << LetterBits) + accidental;
      else
        return Empty;
    }

    /** Return Accidental value of a Pitch **/

    static Accidental toAccidental(Pitch pitch)
    {
      if(pitch >= 0)
        return pitch % LetterMod;
      else
        return Empty;
    }

    /** Return Letter value of a Pitch **/
    static Letter toLetter(Pitch pitch)
    {
      if (pitch >= 0)
        return pitch >> LetterBits;
      else
        return Empty;
    }

    /** Returns a Pitch from its string representation or
        Pitches::Empty if the string cannot be parsed as a
        pitch. Start is the starting position in the string to begin
        parsing and end is the exclusive ending position. Start and
        end default to 0 and the length of the string,
        respectively. **/

    static Pitch fromString(String name, const int start = 0, const int end = 0)
    {
      if (name.isEmpty()) return Empty;
      Letter l = Letters::fromChar(name[start]);
      if (l == Letters::Empty) return Empty;
      Accidental a = Accidentals::fromString(name, start+1, end);
      if (a == Accidentals::Empty) return Empty;
      return fromLetterAccidental(l,a);
    }
    
    /** Return string representation of a Pitch as upper case letter and lower case accidental **/
    static String toString(Pitch pitch)
    {
      if (pitch==Empty) return "empty";
      if (pitch==Wild) return "*";
      String pitchString = Letters::toString(toLetter(pitch));
      pitchString += Accidentals::toString(toAccidental(pitch));
      return pitchString;
    }
    
    /** Same as toString but using '#' and 'b' for accidental **/
    static String toPrettyString(Pitch pitch)
    {
      if (pitch==Empty) return "empty";
      if (pitch==Wild) return "*";
      String pitchString = Letters::toPrettyString(toLetter(pitch));
      String accidentalString = Accidentals::toPrettyString(toAccidental(pitch));
      if (!accidentalString.isEmpty())
        pitchString += accidentalString;
      return pitchString;
    }
  };
}

#endif

