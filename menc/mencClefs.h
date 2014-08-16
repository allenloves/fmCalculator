/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencClefs_h
#define mencClefs_h

#include "mencStaffs.h"
#include "mencIntervals.h"

namespace menc
{
  
  class Clefs
  {

  public:
    
    static const Clef Treble=1;
    static const Clef Bass=2;
    
    static const Clef Treble8va=3;
    static const Clef Bass8va=4;
    static const Clef Treble15ma=5;
    static const Clef Bass15ma=6;
    
    static const Clef Soprano=7;
    static const Clef MezzoSoprano=8;
    static const Clef Alto=9;
    static const Clef TenorVoice=10;
    static const Clef TenorCello=11;
    static const Clef BaritoneC=12;
    static const Clef BaritoneF=13;
    static const Clef SubBass=14;
    static const Clef FrenchViolin=15;
    static const Clef Percussion=16;
    
    static const Clef Empty=0;
    
    static LineSpace position(Clef c)
    {
      switch(c)
        {
        case Treble:
        case MezzoSoprano:
        case TenorVoice:
          return FiveLineStaff::LineBelowMiddleLine;
          
        case Bass:
        case TenorCello:
          return FiveLineStaff::LineAboveMiddleLine;
          
        case FrenchViolin:
        case Soprano:
          return FiveLineStaff::BottomLine;
          
        case BaritoneC:
        case SubBass:
          return FiveLineStaff::TopLine;
          
        case Percussion:
        case Alto:
        case BaritoneF:
        default:
          return FiveLineStaff::MiddleLine;
        }
    }
    
    static LineSpace position(Clef c, Note n)
    {
      int np = n.letter() + n.octave() * 7;
      int cp;
      
      switch(c)
        {
        case Treble:
        case FrenchViolin:
          cp = (Letters::G + 4 * 7);
          break;
        case TenorVoice:
          cp = (Letters::G + 3 * 7);
          break;
        case Treble8va:
          cp = (Letters::G + 5 * 7);
        case Treble15ma:
          cp = (Letters::G + 6 * 7);
        case Bass:
        case BaritoneF:
        case SubBass:
          cp = (Letters::F + 3 * 7);
          break;
        case Bass8va:
          cp = (Letters::F + 2 * 7);
          break;
        case Bass15ma:
          cp = (Letters::F + 1 * 7);
          break;
        case Soprano:
          cp = (Letters::G + 4 * 7);
          break;
        case MezzoSoprano:
        case TenorCello:
        case Alto:
        case Percussion:
        default:
          cp = (Letters::C + 4 * 7);
          break;    
        }
      
      return np - cp  + position(c);
    }
    
    static Note noteFromPosition(Clef c, LineSpace ls, Accidental a=Accidentals::Natural)
    {
      Note n(4,Letters::C,Accidentals::Natural); //middle C
      LineSpace n_ls=position(c,n);
      int ls_delta=ls-n_ls;
      
      if(ls_delta==0)
        {
          n.accidental(a);
          return n;
        }
      
      bool ascending=true;
      if(ls_delta<0)
        {
          ls_delta=-ls_delta;
          ascending=false;
        }
      
      //We actually have to do a transposition...
      int octaves = (ls_delta - 1) / 7;
      IntervalDistance dist = (ls_delta % 7) + IntervalDistances::Unison;
      
      if(dist==IntervalDistances::Unison)
        dist=IntervalDistances::Octave; //convert to 'unison' to octave
      
      /*We are just picking an arbitrary quality. The accidental passed as the 
        parameter to the function will overwrite the accidental that results from 
        this quality.*/
      IntervalQuality qual;
      
      if(ascending)
        qual = IntervalQualities::Major;
      else //To prevent accidentals from possibly overflow the Note range...
        qual = IntervalQualities::Minor;
      
      //Make sure we use "perfect" for the 4th, 5th, and octave.
      if(IntervalDistances::isPerfect(dist))
        qual=IntervalQualities::Perfect;
      // HKT
      n = Interval::transpose(n, Interval(octaves,dist,qual,ascending));
      if(n.valid())
        n.accidental(a); //Validate the note.
      return n;
    }
    
    static String toString(Clef c)
    {
      switch (c)
        {
        case Treble:
          return "treble";
        case Bass:
          return "bass";
        case Alto:
          return "alto";
        case TenorVoice:
          return "tenor voice";
        case TenorCello:
          return "tenor cello";
        case Percussion:
          return "percussion";
        case Soprano:
          return "soprano";
        case MezzoSoprano:
          return "mezzo-soprano";
        case BaritoneC:
          return "c-baritone";
        case BaritoneF:
          return "f-baritone";
        case FrenchViolin:
          return "French violin";
        case Treble8va:
          return "treble 8va";
        case Treble15ma:
          return "treble 15ma";
        case Bass8va:
          return "bass 8va";
        case Bass15ma:
          return "bass 15ma";
        case SubBass:
          return "subbass";
        default:
          return "empty";
        }
    }
    
    static String toPrettyString(Clef c)
    {
      return toString(c);
    }

    static Clef fromString(String name)
    {
      if (name=="treble")
        return Treble;
      else if (name=="bass")
        return Bass;
      else if (name=="alto")
        return Alto;
      else if (name=="tenor voice")
        return TenorVoice;
      else if (name=="tenor cello")
        return TenorCello;
      else if (name=="percussion")
        return Percussion;
      else if(name=="soprano")
        return Soprano;
      else if(name=="mezzo-soprano")
        return MezzoSoprano;
      else if(name=="c-baritone")
        return BaritoneC;
      else if(name=="f-baritone")
        return BaritoneF;
      else if(name=="French violin")
        return FrenchViolin;
      else if(name=="treble 8va")
        return Treble8va;
      else if(name=="treble 15ma")
        return Treble15ma;
      else if(name=="bass 8va")
        return Bass8va;
      else if(name=="bass 15ma")
        return Bass15ma;
      else if(name=="subbass")
        return SubBass;
      else
        return Empty;
    }
  };
}

#endif
