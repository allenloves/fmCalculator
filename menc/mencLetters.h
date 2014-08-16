/*=======================================================================*
  Copyright (C) 2009-20110 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencLetters_h
#define mencLetters_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{

  /** Letters enumerate letter names of pitches and notes **/

  class Letters
  {
  public:
    static const Letter C = 0;
    static const Letter D = 1;
    static const Letter E = 2;
    static const Letter F = 3;
    static const Letter G = 4;
    static const Letter A = 5;
    static const Letter B = 6;
    static const Letter Wild = 7;
    static const Letter Empty = -1;

    /** return a pitch's letter name **/

    static Letter fromPitch(Pitch pitch)
    {
      if(pitch >= 0)
        return pitch >> LetterBits;
      else
        return Empty;
    }

    /** Returns a Letter from its char representation or
        Letters::Empty if invalid. **/

    static Letter fromChar(char ch)
    {
      if (ch == 'C') return C;
      else if (ch == 'D') return D;
      else if (ch == 'E') return E;
      else if (ch == 'F') return F;
      else if (ch == 'G') return G;
      else if (ch == 'A') return A;
      else if (ch == 'B') return B;
      else if (ch == '*') return Wild;
      else return Empty;
    }

    /** Returns a Letter from its string representation or
        Letters::Empty if invalid. **/

    static Letter fromString(String str)
    {
      if (str == "C") return C;
      else if (str == "D") return D;
      else if (str == "E") return E;
      else if (str == "F") return F;
      else if (str == "G") return G;
      else if (str == "A") return A;
      else if (str == "B") return B;
      else if (str == "*") return Wild;
      else return Empty;
    }

   /** return (upper case) string representation of letter **/
 
   static String toString(Letter letter)
    {
      if (letter == C) return "C";
      else if (letter == D) return "D";
      else if (letter == E) return "E";
      else if (letter == F) return "F";
      else if (letter == G) return "G";
      else if (letter == A) return "A";
      else if (letter == B) return "B";
      else if (letter == Wild) return "*";
      else return "empty";
    }

    /** same as toString **/

    static String toPrettyString(Letter letter)
    {
      return toString(letter); //'Pretty' letter is the same thing...
    }
  };
}
#endif
