/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencCleffedNotes_h
#define mencCleffedNotes_h

#include "mencClefs.h"
#include "mencNotes.h"

namespace menc
{
  class CleffedNote : public TypedBitfield<NoteBitfield>
  {

  private:

    //LSB

    //BIT 0: Force accidental to appear as cautionary (0, 1) = 1 bit
    static const int i_Force = 0; //index
    static const int n_Force = 1; //number of bits

    //BITS 1: Rest (0, 1) = 1 bit
    static const int i_Rest = 1; //index
    static const int n_Rest = 1; //number of bits

    //BITS 2-6: Accidental (#,b,##,bb,nat) = 5 bit
    static const int i_Accidental = 2; //index
    static const int n_Accidental = 5; //number of bits

    //BITS 7-14: Line Space (-127 to 127) = 8 bit
    static const int i_LineSpace = 7; //index
    static const int n_LineSpace = 8; //number of bits

    //BITS 15-22: 8 unused bits

    //MSB

    int getLetterWiseIndex(void)
    {
      /*Reads accidental and line space as a single ordered value, so that it is
      easy to compare notes based off of their vertical staff-wise position (as
      in, which one would be higher on the staff). So D-flat 5 > C-sharp 5, even
      though their MIDI key numbers would be the same.*/
      return read(i_Accidental, n_Accidental) +
        (read(i_LineSpace, n_LineSpace) << n_Accidental);
    }

  public:

    CleffedNote(Clef c, Note n)
    {
      isRest(n.isRest());
      forceAccidental(n.forceAccidental());
      note(c, n);
      valid(true);
    }
    
    CleffedNote(LineSpace ls, Accidental a)
    {
      isRest(false);
      forceAccidental(false);
      accidental(a);
      lineSpace(ls);
      valid(true);
    }
    
    CleffedNote()
    {
      isRest(false);
      forceAccidental(false);
      accidental(menc::Accidentals::Natural);
      lineSpace(0);
      valid(true);
    }

    bool forceAccidental(void)
    {
      return readBool(i_Accidental);
    }

    void forceAccidental(bool forcedAccidental)
    {
      writeBool(i_Accidental, forcedAccidental);
    }
    
    bool isRest(void)
    {
      return readBool(i_Rest);
    }

    void isRest(bool rest)
    {
      if(rest)
      {
        //Erase any information pertaining to pitch.
        write(0, 23, 0);
        valid(true);
      }
      writeBool(i_Rest,rest);
    }
    
    Accidental accidental(void) const
    {
      return (Accidental)read(i_Accidental,n_Accidental);
    }

    void accidental(Accidental newAccidental)
    {
      write(i_Accidental,n_Accidental,newAccidental);
    }
    
    LineSpace lineSpace(void) const
    {
      //C = 0, D = 1, E = 2, F = 3, etc.
      return (LineSpace)readSignedInteger(i_LineSpace, n_LineSpace);
    }

    void lineSpace(LineSpace newLineSpace)
    {
      writeSignedInteger(i_LineSpace, n_LineSpace, newLineSpace);
    }
    
    Note note(Clef c)
    {
      if(isRest())
      {
        Note n;
        n.isRest(true);
        return n;
      }
      else
        return Clefs::noteFromPosition(c, lineSpace(), accidental());
    }
    
    void note(Clef c, Note n)
    {
      write(0, 23, 0);
      valid(true);
      if(n.isRest())
        isRest(true);
      else
      {
        forceAccidental(n.forceAccidental());
        accidental(n.accidental());
        lineSpace(Clefs::position(c, n));
      }
    }

    bool isEmpty(void)
    {
      return !valid();
    }
    
    void isEmpty(bool empty)
    {
      valid(!empty);
    }
    
    //Debugging
    String summarizeFields (void)
    {
      String summary;
      summary += "-------------------";
      summary += "\nforce accidental: ";
      summary += readBool(i_Force);
      summary += "\nis rest: ";
      summary += readBool(i_Rest);
      summary += "\naccidental: ";
      summary += read(i_Accidental, n_Accidental);
      summary += "\nlinespace: ";
      summary += readSignedInteger(i_LineSpace, n_LineSpace);
      summary += "\nvalid: ";
      summary += valid();
      summary += "\n-------------------";
      return summary;
    }
  };
}

#endif
