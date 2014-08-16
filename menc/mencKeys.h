/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencKeys_h
#define mencKeys_h

#include "mencIntervals.h"

namespace menc
{

  class KeySignatures
  {

  public:

    static const KeySignature Empty = 0;
    static const KeySignature SevenFlats = 1;
    static const KeySignature SixFlats = 2;
    static const KeySignature FiveFlats = 3;
    static const KeySignature FourFlats = 4;
    static const KeySignature ThreeFlats = 5;
    static const KeySignature TwoFlats = 6;
    static const KeySignature OneFlat = 7;
    static const KeySignature NoAccidentals = 8;
    static const KeySignature OneSharp = 9;
    static const KeySignature TwoSharps = 10;
    static const KeySignature ThreeSharps = 11;
    static const KeySignature FourSharps = 12;
    static const KeySignature FiveSharps = 13;
    static const KeySignature SixSharps = 14;
    static const KeySignature SevenSharps = 15;
    static const KeySignature Special = 16;

    /** return the number of accidentals (-7 to 7) of a keysig **/

    static int numberOfAccidentals(KeySignature keysig)
    {
      return (keysig - NoAccidentals);
    }
    
    /** return a string describing the key signaure (number of sharps and flats) */

    static String toString(KeySignature sig)
    {
      switch (sig)
        {
        case Empty: return "Empty";
        case SevenFlats: return "Seven Flats";
        case SixFlats: return "Six Flats";
        case FiveFlats: return "Five Flats";
        case FourFlats: return "Four Flats";
        case ThreeFlats: return "Three Flats";
        case TwoFlats: return "Two Flats";
        case OneFlat: return "One Flat";
        case NoAccidentals: return "No Accidentals";
        case OneSharp: return "One Sharp";
        case TwoSharps: return "Two Sharps";
        case ThreeSharps: return "Three Sharps";
        case FourSharps: return "Four Sharps";
        case FiveSharps: return "Five Sharps";
        case SixSharps: return "Six Sharps";
        case SevenSharps: return "Seven Sharps";
        case Special: return "Special Signature";
        default: return "";
        }
    }
  };
  
  class Modes
  {

  public:

    static const Mode Empty = 0;
    static const Mode Ionian = 1;
    static const Mode Dorian = 2;
    static const Mode Phrygian = 3;
    static const Mode Lydian = 4;
    static const Mode Mixolydian = 5;
    static const Mode Aeolian = 6;
    static const Mode Locrian = 7;
    static const Mode Major = Ionian;
    static const Mode Minor = Aeolian;
    static const Mode Wild = 8;

    /** return the string name of the mode **/

    static String toString(Mode m)
    {
      if (m==Modes::Empty) return "empty";
      if (m==Modes::Major) return "Major";
      if (m==Modes::Minor) return "Minor";
      if (m==Modes::Ionian) return "Ionian";
      if (m==Modes::Dorian) return "Dorian";
      if (m==Modes::Phrygian) return "Phrygian";
      if (m==Modes::Lydian) return "Lydian";
      if (m==Modes::Mixolydian) return "Mixolydian";
      if (m==Modes::Aeolian) return "Aeolian";
      if (m==Modes::Locrian) return "Locrian";
      if (m==Modes::Wild) return "*";
      return "empty";
    }
    
    /** return a mode from the given string name. return Modes::Empty on failure. **/

    static Mode fromString(String s)
    {
      if (s.equalsIgnoreCase("Major")) return Major;
      if (s.equalsIgnoreCase("Minor")) return Minor;
      if (s.equalsIgnoreCase("Ionian")) return Ionian;
      if (s.equalsIgnoreCase("Dorian")) return Dorian;
      if (s.equalsIgnoreCase("Phrygian")) return Phrygian;
      if (s.equalsIgnoreCase("Lydian")) return Lydian;
      if (s.equalsIgnoreCase("Mixolydian")) return Mixolydian;
      if (s.equalsIgnoreCase("Aeolian")) return Aeolian;
      if (s.equalsIgnoreCase("Locrian")) return Locrian; 
      if (s=="*") return Wild; 
      return Empty;
    }
  };

 class Keys
  {
    static const int ModeShift = 4;

  public:

    static const Key Empty = 0;

    static const Key C_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::NoAccidentals;
    static const Key C_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::TwoFlats;
    static const Key C_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::FourFlats;
    static const Key C_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::OneSharp;
    static const Key C_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::OneFlat;
    static const Key C_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::ThreeFlats;
    static const Key C_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::FiveFlats;
    static const Key C_Major = C_Ionian;
    static const Key C_Minor = C_Aeolian;

    static const Key Cs_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::SevenSharps;
    static const Key Cs_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::FiveSharps;
    static const Key Cs_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::ThreeSharps;
    static const Key Cs_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::SixSharps;
    static const Key Cs_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::FourSharps;
    static const Key Cs_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::TwoSharps;
    static const Key Cs_Major = Cs_Ionian;
    static const Key Cs_Minor = Cs_Aeolian;

    static const Key Df_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::FiveFlats;
    static const Key Df_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::SevenFlats;
    static const Key Df_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::FourFlats;
    static const Key Df_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::SixFlats;
    static const Key Df_Major = Df_Ionian;

    static const Key D_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::TwoSharps;
    static const Key D_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::NoAccidentals;
    static const Key D_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::TwoFlats;
    static const Key D_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::ThreeSharps;
    static const Key D_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::OneSharp;
    static const Key D_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::OneFlat;
    static const Key D_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::ThreeFlats;
    static const Key D_Major = D_Ionian;
    static const Key D_Minor = D_Aeolian;

    static const Key Ds_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::SevenSharps;
    static const Key Ds_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::FiveSharps;
    static const Key Ds_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::SixSharps;
    static const Key Ds_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::FourSharps;
    static const Key Ds_Minor = Ds_Aeolian;

    static const Key Ef_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::ThreeFlats;
    static const Key Ef_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::FiveFlats;
    static const Key Ef_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::SevenFlats;
    static const Key Ef_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::TwoFlats;
    static const Key Ef_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::FourFlats;
    static const Key Ef_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::SixFlats;
    static const Key Ef_Major = Ef_Ionian;
    static const Key Ef_Minor = Ef_Aeolian;

    static const Key E_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::FourSharps;
    static const Key E_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::TwoSharps;
    static const Key E_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::NoAccidentals;
    static const Key E_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::FiveSharps;
    static const Key E_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::ThreeSharps;
    static const Key E_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::OneSharp;
    static const Key E_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::OneFlat;
    static const Key E_Major = E_Ionian;
    static const Key E_Minor = E_Aeolian;

    static const Key F_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::OneFlat;
    static const Key F_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::ThreeFlats;
    static const Key F_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::FiveFlats;
    static const Key F_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::NoAccidentals;
    static const Key F_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::TwoFlats;
    static const Key F_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::FourFlats;
    static const Key F_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::SixFlats;
    static const Key F_Major = F_Ionian;
    static const Key F_Minor = F_Aeolian;

    static const Key Fs_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::SixSharps;
    static const Key Fs_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::FourSharps;
    static const Key Fs_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::TwoSharps;
    static const Key Fs_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::SevenSharps;
    static const Key Fs_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::FiveSharps;
    static const Key Fs_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::ThreeSharps;
    static const Key Fs_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::OneSharp;
    static const Key Fs_Major = Fs_Ionian;
    static const Key Fs_Minor = Fs_Aeolian;

    static const Key Gf_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::SixFlats;
    static const Key Gf_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::FiveFlats;
    static const Key Gf_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::SevenFlats;
    static const Key Gf_Major = Gf_Ionian;

    static const Key G_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::OneSharp;
    static const Key G_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::OneFlat;
    static const Key G_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::ThreeFlats;
    static const Key G_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::TwoSharps;
    static const Key G_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::NoAccidentals;
    static const Key G_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::TwoFlats;
    static const Key G_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::FourFlats;
    static const Key G_Major = G_Ionian; 
    static const Key G_Minor = G_Aeolian;

    static const Key Gs_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::SixSharps;
    static const Key Gs_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::FourSharps;
    static const Key Gs_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::SevenSharps;
    static const Key Gs_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::FiveSharps;
    static const Key Gs_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::ThreeSharps;
    static const Key Gs_Minor = Gs_Aeolian;

    static const Key Af_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::FourFlats;
    static const Key Af_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::SixFlats;
    static const Key Af_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::ThreeFlats;
    static const Key Af_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::FiveFlats;
    static const Key Af_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::SevenFlats;
    static const Key Af_Major = Af_Ionian;
    static const Key Af_Minor = Af_Aeolian;

    static const Key A_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::ThreeSharps;
    static const Key A_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::OneSharp;
    static const Key A_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::OneFlat;
    static const Key A_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::FourSharps;
    static const Key A_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::TwoSharps;
    static const Key A_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::NoAccidentals;
    static const Key A_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::TwoFlats;
    static const Key A_Major = A_Ionian;
    static const Key A_Minor = A_Aeolian;

    static const Key As_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::SixSharps;
    static const Key As_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::SevenSharps;
    static const Key As_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::FiveSharps;
    static const Key As_Minor = As_Aeolian;

    static const Key Bf_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::TwoFlats;
    static const Key Bf_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::FourFlats;
    static const Key Bf_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::SixFlats;
    static const Key Bf_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::OneFlat;
    static const Key Bf_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::ThreeFlats;
    static const Key Bf_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::FiveFlats;
    static const Key Bf_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::SevenFlats;
    static const Key Bf_Major = Bf_Ionian;
    static const Key Bf_Minor = Bf_Aeolian;

    static const Key B_Ionian = (Modes::Ionian << ModeShift) + KeySignatures::FiveSharps;
    static const Key B_Dorian = (Modes::Dorian << ModeShift) + KeySignatures::ThreeSharps;
    static const Key B_Phrygian = (Modes::Phrygian << ModeShift) + KeySignatures::OneSharp;
    static const Key B_Lydian = (Modes::Lydian << ModeShift) + KeySignatures::SixSharps;
    static const Key B_Mixolydian = (Modes::Mixolydian << ModeShift) + KeySignatures::FourSharps;
    static const Key B_Aeolian = (Modes::Aeolian << ModeShift) + KeySignatures::TwoSharps;
    static const Key B_Locrian = (Modes::Locrian << ModeShift) + KeySignatures::NoAccidentals;
    static const Key B_Major = B_Ionian;
    static const Key B_Minor = B_Aeolian;
    
    /** return the mode of a key **/

    static Mode mode(Key k)
    {
      return (k >> ModeShift);
    }
    
    /** return the key signaure of a key **/

    static KeySignature signature(Key k)
    {
      return (k & 15);
    }
    
    /** return the number of accidentals (-7 to 7) or a key **/

    static int accidentals(Key k)
    {
      return (k & 15)-8;
    }
    
    /** return the tonic pitch of a key **/

    static Pitch tonic(Key k)
    {
      static Pitch CycleOfFifths[15]
        = {Pitches::Cf, Pitches::Gf,Pitches::Df, Pitches::Af,Pitches::Ef,
           Pitches::Bf, Pitches::F, Pitches::C,  Pitches::G, Pitches::D,
           Pitches::A,  Pitches::E, Pitches::B,  Pitches::Fs,Pitches::Cs};
      KeySignature s=signature(k);
      Mode m=mode(k);
      if(s==Empty || m==Empty) return Pitches::Empty;
      Note n (Pitches::C, 4);
      n.pitch( CycleOfFifths[s-1] );
      switch (m) 
        {
        case Modes::Ionian:
          return n.pitch();
          break;
        case Modes::Dorian:
          return Interval::transpose(n, Interval(IntervalTypes::MajorSecond)).pitch();
          break;
        case Modes::Phrygian:
          return Interval::transpose(n, Interval(IntervalTypes::MajorThird)).pitch();
          break;
        case Modes::Lydian:
          return Interval::transpose(n, Interval(IntervalTypes::PerfectFourth)).pitch();
          break;
        case Modes::Mixolydian:
          return Interval::transpose(n, Interval(IntervalTypes::PerfectFifth)).pitch();
          break;
        case Modes::Aeolian:
          return Interval::transpose(n, Interval(IntervalTypes::MajorSixth)).pitch();
          break;
        case Modes::Locrian:
          return Interval::transpose(n, Interval(IntervalTypes::MajorSeventh)).pitch();
          break;
        default:
          return Pitches::Empty;
        }
      return Pitches::Empty;
    }
    
    /** return a key given a key signaure and a mode **/

    static Key fromSignatureAndMode(KeySignature s, Mode m)
    {
      return (m << ModeShift) + s;
    }
    
    /** return a key given a pitch and mode **/

    static Key fromPitchAndMode(Pitch p, Mode m)
    {
      static Pitch CycleOfFifths[15]
        = {Pitches::Cf, Pitches::Gf,Pitches::Df, Pitches::Af,Pitches::Ef,
           Pitches::Bf, Pitches::F, Pitches::C,  Pitches::G, Pitches::D,
           Pitches::A,  Pitches::E, Pitches::B,  Pitches::Fs,Pitches::Cs};
      Note n (Pitches::C, 4);
      n.pitch(p);
      switch (m) {
      case Modes::Ionian:
        break;
      case Modes::Dorian:
        p=Interval::transpose(n, Interval(IntervalTypes::MajorSecondDown)).pitch();
        break;
      case Modes::Phrygian:
        p=Interval::transpose(n, Interval(IntervalTypes::MajorThirdDown)).pitch();
        break;
      case Modes::Lydian:
        p=Interval::transpose(n, Interval(IntervalTypes::PerfectFourthDown)).pitch();
        break;
      case Modes::Mixolydian:
        p=Interval::transpose(n, Interval(IntervalTypes::PerfectFifthDown)).pitch();
        break;
      case Modes::Aeolian:
        p=Interval::transpose(n, Interval(IntervalTypes::MajorSixthDown)).pitch();
        break;
      case Modes::Locrian:
        p=Interval::transpose(n, Interval(IntervalTypes::MajorSeventhDown)).pitch();
        break;
      default:
        return Empty;
      }
      for (int i=0; i<15; i++)
        if( CycleOfFifths[i] == p) 
          return fromSignatureAndMode((i+1), m);
      return Empty;
    }
    
    /** return true if pitch is diatonic in key **/

    static bool isPitchTonal(Pitch p, Key k)
    {
      KeySignature sig=signature(k);
      switch (p)
        {
        case Pitches::Ff:
          return (sig == KeySignatures::SevenFlats);
        case Pitches::Cf:
          return (sig == KeySignatures::SevenFlats || 
                  sig == KeySignatures::SixFlats);
        case Pitches::Gf:
          return (sig >= KeySignatures::SevenFlats && 
                  sig <= KeySignatures::FiveFlats);
        case Pitches::Df:
          return (sig >= KeySignatures::SevenFlats && 
                  sig <= KeySignatures::FourFlats);
        case Pitches::Af:
          return (sig >= KeySignatures::SevenFlats && 
                  sig <= KeySignatures::ThreeFlats);
        case Pitches::Ef:
          return (sig >= KeySignatures::SevenFlats && 
                  sig <= KeySignatures::TwoFlats);
        case Pitches::Bf:
          return (sig >= KeySignatures::SevenFlats && 
                  sig <= KeySignatures::OneFlat);
        case Pitches::F:
          return (sig >= KeySignatures::SixFlats && 
                  sig <= KeySignatures::NoAccidentals);
        case Pitches::C:
          return (sig >= KeySignatures::FiveFlats && 
                  sig <= KeySignatures::OneSharp);
        case Pitches::G:
          return (sig >= KeySignatures::FourFlats && 
                  sig <= KeySignatures::TwoSharps);
        case Pitches::D:
          return (sig >= KeySignatures::ThreeFlats && 
                  sig <= KeySignatures::ThreeSharps);
        case Pitches::A:
          return (sig >= KeySignatures::TwoFlats && 
                  sig <= KeySignatures::FourSharps);
        case Pitches::E:
          return (sig >= KeySignatures::OneFlat && 
                  sig <= KeySignatures::FiveSharps);
        case Pitches::B:
          return (sig >= KeySignatures::NoAccidentals && 
                  sig <= KeySignatures::SixSharps);
        case Pitches::Fs:
          return (sig >= KeySignatures::OneSharp && 
                  sig <= KeySignatures::SevenSharps);
        case Pitches::Cs:
          return (sig >= KeySignatures::TwoSharps && 
                  sig <= KeySignatures::SevenSharps);
        case Pitches::Gs:
          return (sig >= KeySignatures::ThreeSharps && 
                  sig <= KeySignatures::SevenSharps);
        case Pitches::Ds:
          return (sig >= KeySignatures::FourSharps && 
                  sig <= KeySignatures::SevenSharps);
        case Pitches::As:
          return (sig >= KeySignatures::FiveSharps && 
                  sig <= KeySignatures::SevenSharps);
        case Pitches::Es:
          return (sig == KeySignatures::SixSharps || 
                  sig == KeySignatures::SevenSharps);
        case Pitches::Bs:
          return (sig == KeySignatures::SevenSharps);
        default:
          return false;
        }
    }
    
    /** returns the membership of pitch in key, where membership is one of 
        ScaleDegrees::Diatonic, ScaleDegrees::Lowered or ScaleDegrees::Raised **/

    static int pitchMembership(Pitch p, Key k)
    {
      KeySignature sig=signature(k);
      switch (p)
        {
        case Pitches::Ff:
          if (sig == KeySignatures::SevenFlats)
            return ScaleDegrees::Diatonic;
          else 
            return ScaleDegrees::Lowered;
        case Pitches::Cf:
          if (sig == KeySignatures::SevenFlats || 
              sig == KeySignatures::SixFlats)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Lowered;
        case Pitches::Gf:
          if (sig >= KeySignatures::SevenFlats && 
              sig <= KeySignatures::FiveFlats)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Lowered;
        case Pitches::Df:
          if (sig >= KeySignatures::SevenFlats && 
              sig <= KeySignatures::FourFlats)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Lowered;
        case Pitches::Af:
          if (sig >= KeySignatures::SevenFlats && 
              sig <= KeySignatures::ThreeFlats)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Lowered;
        case Pitches::Ef:
          if (sig >= KeySignatures::SevenFlats && 
              sig <= KeySignatures::TwoFlats)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Lowered;
        case Pitches::Bf:
          if (sig >= KeySignatures::SevenFlats && 
              sig <= KeySignatures::OneFlat)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Lowered;
        case Pitches::F:
          if (sig >= KeySignatures::SixFlats && 
              sig <= KeySignatures::NoAccidentals)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Lowered;
        case Pitches::C:
          if (sig >= KeySignatures::FiveFlats && 
              sig <=  KeySignatures::OneSharp)
            return ScaleDegrees::Diatonic;
          else if (sig > KeySignatures::OneSharp)
            return ScaleDegrees::Lowered;
          else
            return ScaleDegrees::Raised;
        case Pitches::G:
          if (sig >= KeySignatures::FourFlats && 
              sig <= KeySignatures::TwoSharps)
            return ScaleDegrees::Diatonic;
          else if (sig > KeySignatures::TwoSharps)
            return ScaleDegrees::Lowered;
          else
            return ScaleDegrees::Raised;
        case Pitches::D:
          if (sig >= KeySignatures::ThreeFlats && 
              sig <= KeySignatures::ThreeSharps)
            return ScaleDegrees::Diatonic;
          else if (sig > KeySignatures::ThreeSharps)
            return ScaleDegrees::Lowered;
          else
            return ScaleDegrees::Raised;
        case Pitches::A:
          if (sig >= KeySignatures::TwoFlats && 
              sig <= KeySignatures::FourSharps)
            return ScaleDegrees::Diatonic;
          else if (sig > KeySignatures::FourSharps)
            return ScaleDegrees::Lowered;
          else
            return ScaleDegrees::Raised;
        case Pitches::E:
          if (sig >= KeySignatures::OneFlat && 
              sig <= KeySignatures::FiveSharps)
            return ScaleDegrees::Diatonic;
          else if (sig > KeySignatures::FiveSharps)
            return ScaleDegrees::Lowered;
          else
            return ScaleDegrees::Raised;
        case Pitches::B:
          if (sig >= KeySignatures::NoAccidentals && 
              sig <= KeySignatures::SixSharps)
            return ScaleDegrees::Diatonic;
          else if (sig > KeySignatures::SixSharps)
            return ScaleDegrees::Lowered;
          else
            return ScaleDegrees::Raised;
        case Pitches::Fs:
          if (sig >= KeySignatures::OneSharp && 
              sig <= KeySignatures::SevenSharps)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Raised;
        case Pitches::Cs:
          if (sig >= KeySignatures::TwoSharps && 
              sig <= KeySignatures::SevenSharps)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Raised;
        case Pitches::Gs:
          if (sig >= KeySignatures::ThreeSharps && 
              sig <= KeySignatures::SevenSharps)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Raised;
        case Pitches::Ds:
          if (sig >= KeySignatures::FourSharps && 
              sig <= KeySignatures::SevenSharps)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Raised;
        case Pitches::As:
          if (sig >= KeySignatures::FiveSharps && 
              sig <= KeySignatures::SevenSharps)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Raised;
        case Pitches::Es:
          if (sig == KeySignatures::SixSharps || 
              sig == KeySignatures::SevenSharps)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Raised;
        case Pitches::Bs:
          if  (sig == KeySignatures::SevenSharps)
            return ScaleDegrees::Diatonic;
          else
            return ScaleDegrees::Raised;
        default:
          if (Pitches::toAccidental(p) == Accidentals::DoubleSharp)
            return ScaleDegrees::Raised;
          else
            return ScaleDegrees::Lowered;
        }
    }
    
    /** transpose the key by the given interval distance **/

    static Key transpose(Key key, int dist)
    {
      bool neg=dist<0; // true if we are transposing downward
      dist=abs(dist) % 12;  // eliminate compound intervals
      if (dist==0) return key; // return if no distance
      
      KeySignature signatures[15] =
        {KeySignatures::SevenFlats, KeySignatures::SixFlats,
         KeySignatures::FiveFlats, KeySignatures::FourFlats,
         KeySignatures::ThreeFlats, KeySignatures::TwoFlats,
         KeySignatures::OneFlat,
         KeySignatures::NoAccidentals,
         KeySignatures::OneSharp,
         KeySignatures::TwoSharps, KeySignatures::ThreeSharps,
         KeySignatures::FourSharps,KeySignatures::FiveSharps,
         KeySignatures::SixSharps, KeySignatures::SevenSharps};
      
      KeySignature sig=Keys::signature(key);  // home sig
      int home=-1;   // index of home sig in signatures
      for (int i=0; i<15 && home==-1; i++) // find sig's position
        if (signatures[i]==sig)
          home=i;
      if (home==-1) return key; // shouldn't happen...
      
      // distances holds the number of fifths to move from the home sig to
      // effect the key transposition of dist number of steps.  so if
      // dist=1 the new key will be 7 (or -5) positions away from the home
      // position in the signature array. the furthest key away is a
      // tritone so indexes are only 0 to 6 (where index 0 never actually
      // ocurs since moving by 0 steps cant happen)
      
      int distances[7] = {0, 7, 2, 9, 4, 11, 6};
      
      // use complement if downward motion
      if (neg) 
        {
          dist=12-dist;
          neg=!neg;
        }
      
      // use complement if larger than tritone
      if (dist>6)
        {
          dist=12-dist;
          neg=!neg;
        }
      
      // north is upward transposition amount. south is downward
      // amount. every transpostion has both a north and south solution.
      // so if we are doing a positive (northward) transpostion use the
      // north distace if home+north is a valid signature (eg <15) else
      // add the southward amount
      
      int north, south, next;
      if (!neg)  // upward transposition
        {
          north=distances[dist];
          south=(12-north)*-1;
          if ((home+north) >= 15)
            next=home+south;
          else
            {
              // moving north is possible. but if south is also possible
              // and south results in a smaller keysig then choose it
              // otherwise use north
              if ((home+south>=0) && abs(KeySignatures::numberOfAccidentals(signatures[home+south])) 
                  < abs(KeySignatures::numberOfAccidentals(signatures[home+north])))
                next=home+south;
              else
                next=home+north;
            }
        }
      else
        {
          south=distances[dist]*-1;
          north=(12+south);
          if ((home+south) < 0)
            next=home+north;
          else
            {
              // moving south is possible. but if north is also possible
              // and north results in a smaller keysig then choose it
              // otherwise use north
              if ((home+north<15) && abs(KeySignatures::numberOfAccidentals(signatures[home+north])) 
                  < abs(KeySignatures::numberOfAccidentals(signatures[home+south])))
                next=home+north;
              else
                next=home+south;
            }
        }
      return Keys::fromSignatureAndMode(signatures[next], Keys::mode(key));
    }  
    
    /** return a key from a string containingg a pitch and a mode delimited by space, - or _. 
        Returns Keys::Empty on failure. **/

    static Key fromString (String str)
    {
      int i=0, l=str.length();
      for (i=0; i<l; i++)
        if ((str[i] == '-') || (str[i] == '_') || (str[i] == ' ')) 
          break;
      if (i<l)
        {
          Pitch ton=Pitches::fromString(str, 0, i);
          if (ton==Pitches::Empty) return Empty;
          Mode mod=Modes::fromString(str.substring(i+1, l));
          if (mod==Modes::Empty) return Empty;
          return fromPitchAndMode(ton,mod);
        }
      else return Empty;
    }
    
    /** returns a string containing the keys' pitch and a mode delimited by space eg C# Minor **/

    static String toPrettyString(Key k)
    {
      Pitch p=tonic(k);
      Mode m=mode(k);
      if ((m==Modes::Empty) && (p==Pitches::Empty)) return "empty";
      String s=Pitches::toPrettyString(p);
      s += " ";
      s += Modes::toString(m);
      return s;
    }
    
    static String toString(Key k)
    {
      Pitch p=tonic(k);
      Mode m=mode(k);
      if ((m==Modes::Empty) && (p==Pitches::Empty)) return "empty";
      String s=Pitches::toPrettyString(p);
      s += "-";
      s += Modes::toString(m);
      return s;
    }
    
    /** return a key label (a string consisting of a case-sensitive pitch
        OR a case-insensitive pitch followed by a case-sensitive M or m) 
        from a pitch and mode **/

    static String toLabelFromPitchAndMode(Pitch p, Mode m)
    {
      String s=Pitches::toPrettyString(p);
      if (m==Modes::Minor)
        s=s.toLowerCase();
      else if (m==Modes::Major)
        ;
      else if (m==Modes::Wild)
        if (p==Pitches::Wild)
          ;
        else 
          s += "*";
      else
        s += "?";
      s += ":";
      return s;
    }

    /** parse a pitch and mode from a key label (a string consisting of a case-sensitive pitch
        OR a case-insensitive pitch followed by a case-sensitive M or m). return false on failure.  **/

    static bool fromLabelToPitchAndMode(String label, Pitch& pitch, Mode& mode)
    {
      int len=label.length();
      if (len<1) return false;
      Mode ode=Modes::Major;
      Letter let=Letters::Empty;
      Accidental acc=Accidentals::Natural;
      int pos=0;
      switch (label[pos])
        {
        case 'c': ode=Modes::Minor; case 'C': let=Letters::C; break;
        case 'd': ode=Modes::Minor; case 'D': let=Letters::D; break;
        case 'e': ode=Modes::Minor; case 'E': let=Letters::E; break;
        case 'f': ode=Modes::Minor; case 'F': let=Letters::F; break;
        case 'g': ode=Modes::Minor; case 'G': let=Letters::G; break;
        case 'a': ode=Modes::Minor; case 'A': let=Letters::A; break;
        case 'b': ode=Modes::Minor; case 'B': let=Letters::B; break;
        case '*': ode=Modes::Wild; let=Letters::Wild; acc=Accidentals::Wild; break;
        default: return false;
        }
      pos++;
      String sharps("sS#");
      String flats("fFb");
      if (pos<len && sharps.containsChar(label[pos]))
        {
          if (let==Letters::Wild) return false;
          acc=Accidentals::Sharp;
          pos++;
        }
      else if (pos<len && flats.containsChar(label[pos]))
        {
          if (let==Letters::Wild) return false;
          acc=Accidentals::Flat;
          pos++;
        }

      if (pos<len && label[pos]=='M')
        {
          ode=Modes::Major;
          pos++;
        }
      else if (pos<len && label[pos]=='m')
        {
          ode=Modes::Minor;
          pos++;
        }
      else if (pos<len && label[pos]=='*')
        {
          ode=Modes::Wild;
          pos++;
        }
      // allow only dangling ':'
      if (len>pos+1 || (len==pos+1 && label[pos]!=':'))
        return false;
      pitch=Pitches::fromLetterAccidental(let,acc);
      mode=ode;
      return true;
    }

    /** return a string label consisting of a case-sensitive pitch
        OR (if 'usem' is true) a case-insensitive pitch followed by a
        case-sensitive M or m. the key label delimiter ':' is always
        appended as the suffix. **/

    static String toLabel(Key k, bool usem=false)
    {
      if (k==Keys::Empty)
        return "Empty:";
      String s=Pitches::toPrettyString(tonic(k));
      Mode m=mode(k);
      if (m==Modes::Minor)
        if (usem)
          s += "m";
        else
          s=s.toLowerCase();
      else if (m==Modes::Major)
        if (usem)
          s += "M";
        else
          ;
      else
        s += "?";
      s += ":";
      return s;
    }

    /** return a major or minor Key from a key label consisting of a
        case-sensitive pitch OR a case-insensitive pitch followed by a
        case-sensitive 'm' or 'M'. the string is permitted to contain
        the label delimiter ':' as its suffix **/

    static Key fromLabel(String lab)
    {
      int len=lab.length();
      if (len<1) return Empty;
      Mode mode=Modes::Major;
      Letter let=Letters::Empty;
      Accidental acc=Accidentals::Natural;
      int pos=0;
      switch (lab[pos])
        {
        case 'c': mode=Modes::Minor; case 'C': let=Letters::C; break;
        case 'd': mode=Modes::Minor; case 'D': let=Letters::D; break;
        case 'e': mode=Modes::Minor; case 'E': let=Letters::E; break;
        case 'f': mode=Modes::Minor; case 'F': let=Letters::F; break;
        case 'g': mode=Modes::Minor; case 'G': let=Letters::G; break;
        case 'a': mode=Modes::Minor; case 'A': let=Letters::A; break;
        case 'b': mode=Modes::Minor; case 'B': let=Letters::B; break;
        default: return Empty;
        }
      pos++;
      String sharps("sS#");
      String flats("fFb");
      if (pos<len && sharps.containsChar(lab[pos]))
        {
          acc=Accidentals::Sharp;
          pos++;
        }
      else if (pos<len && flats.containsChar(lab[pos]))
        {
          acc=Accidentals::Flat;
          pos++;
        }
      if (pos<len && lab[pos]=='M')
        {
          mode=Modes::Major;
          pos++;
        }
      else if (pos<len && lab[pos]=='m')
        {
          mode=Modes::Minor;
          pos++;
        }
      // allow only dangling ':'
      if (len>pos+1 || (len==pos+1 && lab[pos]!=':'))
        return Empty;
      Pitch pitch=Pitches::fromLetterAccidental(let,acc);
      return Keys::fromPitchAndMode(pitch,mode);
      }
  };
}

#endif








