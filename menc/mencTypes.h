/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencTypes_h
#define mencTypes_h

#define MENC_NAMESPACE_BEGIN namespace menc {
#define MENC_NAMESPACE_END }

namespace menc
{
  typedef signed char                 int8;
  typedef unsigned char               uint8;
  typedef signed short                int16;
  typedef unsigned short              uint16;
  typedef signed int                  int32;
  typedef unsigned int                uint32;
  typedef signed long long            int64;
  typedef unsigned long long          uint64;

  //Each type is stored in the upper 8 bits automatically.
  //Thus, the type can be an arbitrary integer from 0 to 255.
  typedef int32 BitfieldType;

  //Note/Interval bitfields
  static const BitfieldType NoteBitfield = 1;
  static const BitfieldType IntervalBitfield = 2;

  //Analysis bitfields
  static const BitfieldType ChordTypeBitfield = 3;
  static const BitfieldType ToneTypeBitfield = 4;
  static const BitfieldType AnnotationBitfield = 5;

  // Pitches bits
  static const int32 LetterBits = 3;
  static const int32 LetterMod  = 1 << LetterBits;

  //----------------//
  //Type Definitions//
  //----------------//

  typedef char StringChar;

  typedef int16 Accidental;
  typedef int16 Letter;
  typedef int16 Pitch;
  typedef int16 Octave;
  typedef uint16 ScaleDegree;

  typedef int16 RatioPart;

  typedef int16 IntervalQuality;
  typedef int16 IntervalDistance;
  typedef int16 IntervalType;

  typedef int16 ChordQuality;
  typedef int16 ChordId;
  typedef int16 ChordMember;
  typedef int16 ChordInversion;

  typedef uint16 ToneId ;
  typedef int16 KeySignature;
  typedef int16 Mode;
  typedef int16 Key;
  typedef uint16 Amplitude;
  typedef uint16 Mark;

  typedef int16 Meter;
  typedef int16 MetricWeight;

  typedef int16 Clef;
  typedef int16 LineSpace;

  typedef int16 RhythmicUnit;
  typedef int16 Tonicization;

  typedef int16 BeamLevel;
  typedef int16 BeamPart;
  typedef int16 Beam;
  typedef int16 Slur;
  typedef int16 Barline;
  typedef int16 Instrument;

}

#endif
