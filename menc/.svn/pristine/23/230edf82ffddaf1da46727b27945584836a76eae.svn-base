/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencAmplitudes_h
#define mencAmplitudes_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{
  
  class Amplitudes 
  {
    
    static const Amplitude MaxAmplitude = 10;
    
  public:

    static const Amplitude Empty = 0;
    static const Amplitude Niente = Empty;
    static const Amplitude PPPP = 1;
    static const Amplitude PPP  = 2;
    static const Amplitude PP   = 3;
    static const Amplitude P    = 4;
    static const Amplitude MP   = 5;
    static const Amplitude MF   = 6;
    static const Amplitude F    = 7;
    static const Amplitude FF   = 8;
    static const Amplitude FFF  = 9;
    static const Amplitude FFFF = 10;

    static const double toDouble(Amplitude a)
    {
      return (double)( (double)a/(double)MaxAmplitude);
    }

    static const int toMIDI(Amplitude a)
    {
      return (int)(((double)a/(double)MaxAmplitude) * 127.0);
    }
    
    static Amplitude fromString(String s)
    {
      if (s.equalsIgnoreCase("Niente")) return Niente;
      if (s.equalsIgnoreCase("PPPP")) return PPPP;
      if (s.equalsIgnoreCase("PPP")) return PPP;
      if (s.equalsIgnoreCase("PP")) return PP;
      if (s.equalsIgnoreCase("P")) return P;
      if (s.equalsIgnoreCase("MP")) return MP;
      if (s.equalsIgnoreCase("MF")) return MF;
      if (s.equalsIgnoreCase("F")) return F;
      if (s.equalsIgnoreCase("FF")) return FF;
      if (s.equalsIgnoreCase("FFF")) return FFF;
      if (s.equalsIgnoreCase("FFFF")) return FFFF;
      return Empty;
    }

    static String toString(Amplitude a)
    {
      if (a == Niente) return "Niente";
      if (a == PPPP) return "PPPP";
      if (a == PPP) return "PPP";
      if (a == PP) return "PP";
      if (a == P) return "P";
      if (a == MP) return "MP";
      if (a == MF) return "MF";
      if (a == F) return "F";
      if (a == FF) return "FF";
      if (a == FFF) return "FFF";
      if (a == FFFF) return "FFFF";
      return "empty";
    }
  };
}

#endif
