/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencAccidentals_h
#define mencAccidentals_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{

  /** Accidentals enumerates the standard accidental markings **/

  class Accidentals
  {

  public:

    static const Accidental DoubleFlat = 0;
    static const Accidental Flat = 1;
    static const Accidental Natural = 2;
    static const Accidental Sharp = 3;
    static const Accidental DoubleSharp = 4;
    static const Accidental Wild = 7;
    static const Accidental Empty = -1;

    /** Return the Accidental of a pitch **/
    static Accidental fromPitch(Pitch pitch)
    {
      if (pitch >= 0)
        return pitch % LetterMod;
      else
        return Empty;
    }
    
    /** Returns an Accidental from its string reprentation or
        Accidentals::Empty if the string cannot be parsed as an
        accidental. Accidentals are: 'f' or 'b' for Flat and 's' or
        '#' for sharp. A note without sharp or flat is automatically
        natural but a single 'n' is also allowed in the name. Start
        is the starting position in the string to begin parsing and
        end is the exclusive ending position. Start and end default to
        0 and the length of the string, respectively. */
    
    static Accidental fromString(String name, const int start = 0, const int end = 0)
    {
      int stop = (end > 0) ? end : name.length();
      // Count number of 'f' and 's' or alterantes 'b' and '#'.
      // an empty string == natural
      int number_f = 0;
      int number_s = 0;
      int number_n = 0;
      // look at all chars if we hit unexpected char return empty
      for (int i = start; i < stop; i++)
        if (name[i] == 'f' || name[i] == 'b')
          number_f++;
        else if (name[i] == 's' || name[i] == '#')
          number_s++;
        else if (name[i] == 'n')
          number_n++;
        else
          return Empty;
      // Make sure there are no conflicts.
      if (number_f==2 && !number_s && !number_n)
        return DoubleFlat;
      else if (number_f == 1 && !number_s && !number_n)
        return Flat;
      else if (number_s == 2 && !number_f && !number_n)
        return DoubleSharp;
      else if (number_s == 1 && !number_f && !number_n)
        return Sharp;
      else if (number_n < 2 && !number_s && !number_f)
        return Natural;
      else
        return Empty;
    }
    
    /** Return 's' 'f' string representation of accidental */

    static String toString(Accidental accidental, bool forceNatural=false)
    {
      if (accidental == DoubleFlat)
        return "ff";
      else if (accidental == Flat)
        return "f";
      else if (accidental == Sharp)
        return "s";
      else if (accidental == DoubleSharp)
        return "ss";
      else if (accidental == Natural)
        return (forceNatural) ? "n" : "";
      else if (accidental == Wild)
        return "*";
      else
        return "empty";
    }
    
    /** Return '#' 'b' string representation of accidental */

    static String toPrettyString(Accidental accidental)
    {
      if (accidental == DoubleFlat)
        return "bb";
      else if(accidental == Flat)
        return "b";
      else if(accidental == Sharp)
        return "#";
      else if(accidental == DoubleSharp)
        return "##";
      else if(accidental == Natural)
        return "";
      else
        return "empty";
    }
    
  };
  
}

#endif
