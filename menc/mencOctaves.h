/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencOctaves_h
#define mencOctaves_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{
  /** Octave values from 0 to 15 **/

  class Octaves
  {
  public:

    static const Octave Empty = -1;
    static const Octave LowestOctave = 0;
    static const Octave HighestOctave = 15;

    /** Returns true if oct is a valid octave otherwise returns false. **/

    static bool isInRange(Octave oct)
    {
      return ((oct >= LowestOctave) && (oct <= HighestOctave));
    }

    /** Returns an octave number from its string representation or
        Octaves::Empty if the string cannot be parsed as an
        octave. Valid octave numbers are 0 to 15 inclusive. FIXME:
        what about the 00 octave?? **/

    static Octave fromString(String name, const int start = 0, const int end = 0)
    {
      // Add each digit found to the final octave number, return Empty
      // on non-digit char
      int stop = (end > 0) ? end : name.length();
      Octave octave=0;
      bool found = false;
      for (int i=start; i<stop; i++)
        {
          char letter = (char)name[i];
          if (letter >= 48 && letter <= 57)
            {
              octave *= 10;
              octave += (letter-48);
              found = true;
            }
          else
            return Empty;
        }
      if (found && isInRange(octave))
        return octave;
      else
        return Empty;
    }

    /** Return string representation of Octave. The ocatave below C0 appends an extra 0 in its name, 
        ie C00 etc **/

    static String toString(Octave octave)
    {
      String octaveString;
      if (octave>=0)
        octaveString += String::intToString(octave);
      else
        for (int i=0; i<-octave+1 ;i++)
          octaveString += "0";
      return octaveString;
    }

    static String toPrettyString(Octave octave)
    {
      return toString(octave);
    }
  };
}

#endif
