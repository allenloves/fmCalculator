/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
  *=======================================================================*/

#ifndef mencSlurs_h
#define mencSlurs_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{

  /** Slurs encode type and side info for ties and slurs. Encoded as:

          76543210    
          ttttpppp    t=type s=side
  **/

  class Slurs
  {

  public:

    // Slur types
    static const int TieType = 1 << 4;
    static const int SlurType = 2 << 4;

    // Slur sides
    static const int Left = 1 ;
    static const int Right = 2 ;

    // Slurs
    static const Slur Empty = 0;
    static const Slur TieBegin = TieType + Left;
    static const Slur TieEnd = TieType + Right;
    static const Slur SlurBegin = SlurType + Left;
    static const Slur SlurEnd =  SlurType + Right;

    static Slur fromString(String str)
    {
      if (str.equalsIgnoreCase("tie-begin")) return TieBegin;
      if (str.equalsIgnoreCase("tie-end")) return TieEnd;
      if (str.equalsIgnoreCase("slur-begin")) return SlurBegin;
      if (str.equalsIgnoreCase("slur-end")) return SlurEnd;
      return Empty;
    }

    static String toString(Slur st)
    {
      switch (st)
      {
      case TieBegin: return "tie-begin";
      case TieEnd: return "tie-end";
      case SlurBegin: return "slur-begin";
      case SlurEnd: return "slur-end";
      default: return "";
      }
    }

  };

}

#endif
