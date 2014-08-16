/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencRhythms_h
#define mencRhythms_h

#include "mencRational.h"

namespace menc
{

  struct RhythmicUnits
  {
    static const RhythmicUnit Empty = 0;

    static const RhythmicUnit Longa = 1;
    static const RhythmicUnit Breve = 2;
    static const RhythmicUnit Whole = 3;
    static const RhythmicUnit Half = 4;
    static const RhythmicUnit Quarter = 5;
    static const RhythmicUnit _8th = 6;
    static const RhythmicUnit _16th = 7;
    static const RhythmicUnit _32nd = 8;
    static const RhythmicUnit _64th = 9;
    static const RhythmicUnit _128th = 10;
    static const RhythmicUnit _256th = 11;
    static const RhythmicUnit _512th = 12;

    static const RhythmicUnit Dotted       = 1 << 4;
    static const RhythmicUnit DoubleDotted = 2 << 4;
    static const RhythmicUnit TripleDotted = 3 << 4;

    static inline int numberOfDots(RhythmicUnit r)
    {
      return r >> 4;
    }

    static inline int numberOfDots(Ratio rat)
    {
      return numberOfDots(toRhythmicUnit(rat));
    }

    static inline RhythmicUnit baseUnit(RhythmicUnit r)
    {
      return r % 16;
    }

    static inline RhythmicUnit baseUnit(Ratio rat)
    {
      return baseUnit(toRhythmicUnit(rat));
    }

    static inline int numberOfFlags(RhythmicUnit r)
    {
      int flags = baseUnit(r) - Quarter;
      return flags > 0 ? flags : 0;
    }

    static inline int numberOfFlags(Ratio rat)
    {
      return numberOfFlags(toRhythmicUnit(rat));
    }

    static inline bool isSolidNotehead(RhythmicUnit r)
    {
      return baseUnit(r) >= Quarter;
    }

    static inline bool isSolidNotehead(Ratio rat)
    {
      return isSolidNotehead(toRhythmicUnit(rat));
    }

    static inline RhythmicUnit makeRhythmicUnit(RhythmicUnit base, 
      int  dots)
    {
      return (base % 16) + (RhythmicUnit)(dots << 4);
    }

    static inline Ratio toRatio(RhythmicUnit r)
    {
      /*This code uses lookup tables to compute the ratio mathematically
      in lookup time, O(1). The complexity of the rhythmic unit does not
      affect the time that it takes to compute its durational ratio.*/
      int _2_to_the[16] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
      RhythmicUnit b = baseUnit(r);
      int dots = numberOfDots(r);
      Ratio rat = 4;
      rat /= _2_to_the[b-1];
      rat += rat * (Ratio)(_2_to_the[dots]-1) / _2_to_the[dots];

      return rat;
    }

    static inline RhythmicUnit toRhythmicUnit(Ratio rat)
    {
      /*This is a little slow because it is just sitting here looping
      through all the possibilities in order to match a ratio to a rhythm.
      A better algorithm would use some sort of binary search, or perhaps
      even one large lookup for numerators and denominators.*/
      for(int dots=0;dots<=3;dots++)
        for(RhythmicUnit base=Longa;base<=_512th;base++)
          if(rat==toRatio(makeRhythmicUnit(base,dots)))
            return makeRhythmicUnit(base,dots);

      return Empty;
    }
  };
}

#endif
