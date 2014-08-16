/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencMarks_h
#define mencMarks_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{
  
    /**
       Marks are notations that are (typically) attached to
       notes. Marks are organized into groups and encoded as:

       76543210 76543210
       gggggggg --------    Group
       -------- vvvvvvvv    Value

    **/

  class Marks
  {

  private:

    static const int Shift = 8;

  public:

    /// Mark groups

    static const int Dynamic = 1 << Shift;
    static const int Articulation = 2 << Shift;  
    static const int Ornament = 3 << Shift;  
    static const int Miscellaneous = 4 << Shift;  

    /// Marks by group

    static const Mark Empty   = 0;

    static const Mark Niente  = Dynamic + 1;
    static const Mark PPPP    = Dynamic + 2;
    static const Mark PPP     = Dynamic + 3;
    static const Mark PP      = Dynamic + 4;
    static const Mark P       = Dynamic + 5;
    static const Mark MP      = Dynamic + 6;
    static const Mark MF      = Dynamic + 7;
    static const Mark F       = Dynamic + 8;
    static const Mark FF      = Dynamic + 9;
    static const Mark FFF     = Dynamic + 10;
    static const Mark FFFF    = Dynamic + 11;
    static const Mark SFZ     = Dynamic + 12;
    static const Mark CrescendoBegin   = Dynamic + 13;
    static const Mark CrescendoEnd     = Dynamic + 14;
    static const Mark DecrescendoBegin = Dynamic + 15;
    static const Mark DecrescendoEnd   = Dynamic + 16;

    static const Mark Fermata       = Articulation + 1;
    static const Mark Staccato      = Articulation + 2;
    static const Mark Staccatissimo = Articulation + 3;
    static const Mark Marcato       = Articulation + 4;
    static const Mark Tenuto        = Articulation + 5;
    static const Mark MezzoStacatto = Articulation + 6;
    static const Mark Martellato    = Articulation + 7;
    static const Mark Arco          = Articulation + 8;
    static const Mark Pizz          = Articulation + 9;
    static const Mark LeftPizz      = Articulation + 10;
    static const Mark SnapPizz      = Articulation + 11;
    static const Mark Harmonic      = Articulation + 12;
    static const Mark DownBow       = Articulation + 13;
    static const Mark UpBow         = Articulation + 14;

    static const Mark Trill   = Ornament + 1;  
    static const Mark Mordent = Ornament + 2;
    static const Mark Turn    = Ornament + 3;

    static const Mark PedalDown = Miscellaneous + 1;
    static const Mark PedalUp   = Miscellaneous + 2;

    static int getMarkGroup(Mark m)
    {
      return (m & 0xFF00) ;
    }

    static bool isDynamic(Mark m)
    {
      return (getMarkGroup(m)==Dynamic) ;
    }

    static bool isArticulation(Mark m)
    {
      return (getMarkGroup(m)==Articulation) ;
    }

    static String toString(Mark m)
    {
      switch(m)
        {
        case Fermata: return "fermata";
        case Niente: return "niente";
        case PPPP: return "pppp";
        case PPP: return "ppp";
        case PP: return "pp";
        case P: return "p";
        case MP: return "mp";
        case MF: return "mf";
        case F: return "f";
        case FF: return "ff";
        case FFF: return "fff";
        case FFFF: return "ffff";
        case SFZ: return "sfz";
        default: return "";
        }
    }

    static Mark fromString(String s)
    {
      if (s.equalsIgnoreCase("fermata")) return Fermata;
      if (s.equalsIgnoreCase("niente")) return Niente;
      if (s.equalsIgnoreCase("ppp")) return PPPP;
      if (s.equalsIgnoreCase("ppp")) return PPP;
      if (s.equalsIgnoreCase("pp")) return PP;
      if (s.equalsIgnoreCase("p")) return P;
      if (s.equalsIgnoreCase("mp")) return MP;
      if (s.equalsIgnoreCase("mf")) return MF;
      if (s.equalsIgnoreCase("f")) return F;
      if (s.equalsIgnoreCase("ff")) return FF;
      if (s.equalsIgnoreCase("fff")) return FFF;
      if (s.equalsIgnoreCase("ffff")) return FFFF;
      if (s.equalsIgnoreCase("sfz")) return SFZ;
      return Empty;
    }
  };
}

#endif
