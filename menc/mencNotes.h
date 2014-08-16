/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencNotes_h
#define mencNotes_h

#include "mencBitfields.h"
#include "mencPitches.h"
#include <math.h>  // for 'pow' and 'log'
#include <iostream>

namespace menc
{

  /** when you construct a note be sure to set valid(true) **/

  class Note : public TypedBitfield<NoteBitfield>
  {

  private:
 
   //Valid ranges for MIDI key number
    static const int lowestValidMIDIKeyNumber = 0;
    static const int highestValidMIDIKeyNumber = 127;

    //LSB

    //BIT 0: Force accidental to appear as cautionary (0, 1) = 1 bit
    static const int i_Force = 0; //index
    static const int n_Force = 1; //number of bits

    //BITS 1-4 (SIGNED): Tuning (-7 to 7) = 3 bits + 1 bit sign
    static const int i_Tune = 1; //index
    static const int n_Tune = 4; //number of bits

    //BITS 5-7: Accidental (#,b,##,bb,nat) = 3 bit
    static const int i_Accidental = 5; //index
    static const int n_Accidental = 3; //number of bits

    //BITS 8-10: Letter (0-6) = 3 bit
    static const int i_Letter = 8; //index
    static const int n_Letter = 3; //number of bits

    //BITS 11-14: Octave number (0 to 15) = 4 bits
    static const int i_Octave = 11; //index
    static const int n_Octave = 4; //number of bits

    //BITS 15-16: Voice number (1 to 4) = 2 bits
    static const int i_Voice = 15; //index
    static const int n_Voice = 2; //number of bits

    //BITS 17: Rest (0, 1) = 1 bit
    static const int i_Rest = 17; //index
    static const int n_Rest = 1; //number of bits

    //BITS 18-22: 5 unused bits

    //MSB

    int getLetterWiseIndex(void) const
    {
      //Assumes the accidental, letter, octave are contiguous
      //and reads them as one so that it is easy to compare
      //notes based off of their vertical staff-wise position
      //(as in, which one would be higher on the staff)
      //So D-flat 5 > C-sharp 5, even though their MIDI key numbers
      //would be the same.
      return read(i_Accidental, n_Accidental + n_Letter + n_Octave);
    }

    void enforceMIDIKeyNumberRange(void)
    {
      int m = toMIDIKeyNumber();
      std::cout << "m=" << m << "\n";
      if(m >= lowestValidMIDIKeyNumber && m <= highestValidMIDIKeyNumber)
        valid(true);
      else
        valid(false);
    }

  public:

    Note(Pitch p, Octave o=4)
      {
        semitoneTuning(0);
        forceAccidental(false);
        octave(o);
        letter(Pitches::toLetter(p));
        accidental(Pitches::toAccidental(p));
        valid(true);
      }
    
    Note(Octave newOctave, Letter newLetter, Accidental newAccidental,  bool forcedAccidental=false)
      {
        semitoneTuning(0);
        forceAccidental(forcedAccidental);
        octave(newOctave);
        letter(newLetter);
        accidental(newAccidental);
        valid(true);
      }
    
    Note(int newMIDIKeyNumber, bool preferSharp=true)
      {
        fromMIDIKeyNumber(newMIDIKeyNumber, preferSharp);
        valid(true);
      }
    
    Note()
      {
        semitoneTuning(0);
        forceAccidental(false);
        fromMIDIKeyNumber(0, false);
        valid(true);
      }

    Note(String name)
    {
      fromString(name);
    }

    String toString(void)
    {
      String str = Letters::toString(letter());
      if (valid())
        {
          if(!isRest())
            {
              str += Accidentals::toString(accidental());
              str += Octaves::toString(octave());
            }
          else
            str = "R";
        }
      else
        str = "invalid";
      return str;
    }

    String toPrettyString (void)
      {
        String str = Letters::toPrettyString(letter());
        if (valid())
          {
            if (!isRest())
              {
                str += Accidentals::toPrettyString(accidental());
                str += Octaves::toPrettyString(octave());
              }
            else
              str = "R";
          }
        else
          str = "invalid";
        return str;
      }

    /** Constructs a note from its string representation, or an empty
       note if the string is invalid.  A valid note name consists of
       an uppercase Letter (C D E F G A B) followed by an optional
       Accidental (f ff b bb s ss # ##) followed by an octave
       0-15. **/

    void fromString(String name)
    {
      if (name == "R")  // a rest is a legal note value
        isRest(true);
      else
        {
          int len = name.length();
          int pos;
          for (pos = 0; pos < len; pos++)
            if (String::isDigitChar(name[pos])) // FIXME: do we have negative octaves??
              break;
          if (pos == len) // octave digit is required!
            isEmpty(true); 
          // everything before pos is Pitch
          else
            {
              Pitch p = Pitches::fromString(name, 0, pos);
              //std::cout << "acc=" << Pitches::toAccidental(p) << " " << Accidentals::toString(Pitches::toAccidental(p))  << " pos=" << pos << " pitch=" << Pitches::toString(p) << "\n";
              if (p == Pitches::Empty) // invalid pitch
                isEmpty(true);
              else
                {
                  // all chars above pos must be digit
                  int end;
                  for (end = pos+1; end < len; end++)
                    if (!String::isDigitChar(name[end]))
                      break;
                  if (end < len)
                    isEmpty(true);
                  else
                    {
                      Octave o = Octaves::fromString(name, pos, len);
                      if (o == Octaves::Empty)
                        isEmpty(true);
                      else
                        {
                          letter(Pitches::toLetter(p));
                          accidental(Pitches::toAccidental(p));
                          octave(o);
                          valid(true);
                        }
                    }
                }
            }
        }
    }

    Octave octave(void) const
    {
      return read(i_Octave,n_Octave) - 1;
    }

    void octave(Octave newOctave)
    {
      write(i_Octave,n_Octave,newOctave + 1);
    }

    Letter letter(void) const
    {
      //C = 0, D = 1, E = 2, F = 3, etc.
      return (Letter)read(i_Letter,n_Letter);
    }

    void letter(Letter newLetter)
    {
      write(i_Letter,n_Letter,newLetter);
    }

    Accidental accidental(void) const
    {
      return (Accidental)read(i_Accidental,n_Accidental);
    }

    void accidental(Accidental newAccidental)
    {
      write(i_Accidental,n_Accidental,newAccidental);
    }

    Pitch pitch(void) const
    {
      return Pitches::fromLetterAccidental(letter(),accidental());
    }

    void pitch(Pitch newPitch)
    {
      letter(Pitches::toLetter(newPitch));
      accidental(Pitches::toAccidental(newPitch));
    }

    int toMIDIKeyNumber(void)
    {
      Octave o = octave();
      Letter l = letter();
      Accidental a = accidental();
      int chromatic_pitch;
      
      //Convert letter to chromatic pitch
      if(l<3)
        chromatic_pitch = l * 2 + a - 2;
      else
        chromatic_pitch = l * 2 + a - 3;
      
      //Multiply octave by 12 and add the chromatic pitch
      return o * 12 + chromatic_pitch + 12;
    }
    
    void fromMIDIKeyNumber(int newMIDIKeyNumber, bool preferSharp=true)
    {
      //enforce the range
      if(newMIDIKeyNumber < lowestValidMIDIKeyNumber 
         || newMIDIKeyNumber > highestValidMIDIKeyNumber)
        {
          valid(false);
          return;
        }
      
      Octave o=(newMIDIKeyNumber/12)-1;
      Letter l=Letters::Empty;
      Accidental a=Accidentals::Empty;
      int chromatic_pitch=newMIDIKeyNumber%12;
      
      if(preferSharp)
        {
          switch(chromatic_pitch)
            {
            case 0:
            case 2:
            case 4:
              l=chromatic_pitch/2;
              a=2; //nat
              break;
            case 1:
            case 3:
              l=chromatic_pitch/2;
              a=3; //sharp
              break;
            case 5:
            case 7:
            case 9:
            case 11:
              l=chromatic_pitch/2+1;
              a=2; //nat
              break;
            case 6:
            case 8:
            case 10:
              l=chromatic_pitch/2;
              a=3; //sharp
            }
        }
      else
        {
          switch(chromatic_pitch)
            {
            case 0:
            case 2:
            case 4:
              l=chromatic_pitch/2;
              a=2; //nat
              break;
            case 1:
            case 3:
              l=chromatic_pitch/2+1;
              a=1; //flat
              break;
            case 5:
            case 7:
            case 9:
            case 11:
              l=chromatic_pitch/2+1;
              a=2; //nat
              break;
            case 6:
            case 8:
            case 10:
              l=chromatic_pitch/2+1;
              a=1; //flat
            }
        }
      
      octave(o);
      letter(l);
      accidental(a);
    }
    
    bool forceAccidental(void)
    {
      return readBool(i_Accidental);
    }
    void forceAccidental(bool forcedAccidental)
    {
      writeBool(i_Accidental, forcedAccidental);
    }
    
    int voice(void)
    {
      return read(i_Voice,n_Voice);
    }

    void voice(int voice)
    {
      write(i_Voice,n_Voice,voice-1);
    }
    
    bool isEmpty(void)
    {
      return !valid();
    }
    
    void isEmpty(bool empty)
    {
      valid(!empty);
    }
    
    bool isRest(void)
    {
      return readBool(i_Rest);
    }

    void isRest(bool rest)
    {
      if(rest)
        {
          //erase any information pertaining to 'notes'
          write(0,23,0);
          valid(true);
        }
      writeBool(i_Rest,rest);
    }
    
    void semitoneTuning(float normalizedSemitones)
    {
      normalizedSemitones+=(1.0/16.0);
      int t=(int)(normalizedSemitones*8.0);
      
      //If the tuning param is outside of the semitone, then
      //actually change the note.
      if(t>=8)
        {
          fromMIDIKeyNumber(toMIDIKeyNumber() + (t/8), true);
          t = t % 8;
        }
      else if(t<=8)
        {
          fromMIDIKeyNumber(toMIDIKeyNumber() + (t/8), false);
          t = -((-t)%8);
        }
      
      writeSignedInteger(i_Tune,n_Tune,t); //note: signed
    }
    
    float semitoneTuning(void)
    {
      int t=readSignedInteger(i_Tune,n_Tune);
      return ((float)t)/(float)8.0;
    }
    
    float toFrequency(void)
    {
      int m=toMIDIKeyNumber()-69; //keynum 81 = A4 = 440Hz
      float mf=((float)m + semitoneTuning()) / (float)12.0;
      return (float)440.0 * pow((float)2.0,mf);
    }
    
    void fromFrequency(float frequency, bool preferSharp=true)
    {
      float base=log(frequency/(float)440.0)/log((float)2.0);
      float mf=base*(float)12.0+(float)69.0;
      int m=(int)mf;
      float m2 = mf - (float)m;
      if(m2<=0.5)
        {
          fromMIDIKeyNumber(m,preferSharp);
          semitoneTuning(m2);
        }
      else
        {
          fromMIDIKeyNumber(m+1,preferSharp);
          semitoneTuning(m2-(float)1.0);
        }
    }

    float toPeriod(void)
    {
      return ((float)1.0)/toFrequency();
    }

    float toPeriod(float hzSampleRate)
    {
      return hzSampleRate/toFrequency();
    }
    
    //Comparison operators
    bool operator > (const Note& otherNote) const
    {
      return(getLetterWiseIndex() > otherNote.getLetterWiseIndex());
    }
    
    bool operator >= (const Note& otherNote) const
    {
      return(getLetterWiseIndex() >= otherNote.getLetterWiseIndex());
    }

    bool operator < (const Note& otherNote) const
    {
      return(getLetterWiseIndex() < otherNote.getLetterWiseIndex());
    }

    bool operator <= (const Note& otherNote) const
    {
      return(getLetterWiseIndex() <= otherNote.getLetterWiseIndex());
    }

    bool operator == (const Note& otherNote) const
    {
      return(getLetterWiseIndex() == otherNote.getLetterWiseIndex());
    }

    bool operator != (const Note& otherNote) const
    {
      return(getLetterWiseIndex() != otherNote.getLetterWiseIndex());
    }

    //Transposition HKT: MOVE THIS TO INVERVALS.H
    //WAB: This was done to stop circular dependency between Note and Interval
    //To do:
    // n2 = n1.transpose(interval)
    //Now you must do:
    // n2 = Interval::transpose(n1, interval)
    //
    //The original notation could be brought back if a menc.cpp file was added
    //to the menc repository and the method implementation brought there.
    //
    //Originally:
    //Note transpose(Interval interval);
    
    //Debugging

    String summarizeFields (void)
    {
      String summary;
      summary += "-------------------";
      summary += "\nforce accidental: ";
      summary += readBool(i_Force);
      summary += "\ntuning: ";
      summary += readSignedInteger(i_Tune,n_Tune);
      summary += "\naccidental: ";
      summary += read(i_Accidental,n_Accidental);
      summary += "\nletter: ";
      summary += read(i_Letter,n_Letter);
      summary += "\noctave: ";
      summary += read(i_Octave,n_Octave);
      summary += "\nvalid: ";
      summary += valid();
      summary += "\n-------------------";
      return summary;
    }
  };
}

#endif
