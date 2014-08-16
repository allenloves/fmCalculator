/*=======================================================================*
  Copyright (C) 2009-20110 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencInstruments_h
#define mencInstruments_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{

  /** The Instruments class encodes basic information about musical
      instruments. Only a small set is provided for now, almost all
      are defined in:

      /usr/local/share/fomus/fomus.conf **/

  class Instruments
  {
   
  public:

    static const Instrument Empty = 0;

    static const Instrument Soprano = 1;
    static const Instrument MezzoSoprano = 2;
    static const Instrument Alto = 3;
    static const Instrument Contralto = 4;
    static const Instrument Tenor = 5;
    static const Instrument Baritone = 6;
    static const Instrument Bass = 7;
    static const Instrument SopranoChoir = 8;
    static const Instrument AltoChoir = 9;
    static const Instrument TenorChoir = 10;
    static const Instrument BassChoir = 11;
  
    static const Instrument Violin = 16;
    static const Instrument Viola = 17;
    static const Instrument Cello = 18;
    static const Instrument Contrabass = 19;
    static const Instrument DoubleBass = Contrabass;

    static const Instrument Flute = 32;
    static const Instrument Oboe = 33;
    static const Instrument BfClarinet = 34;
    static const Instrument Clarinet = BfClarinet;
    static const Instrument Bassoon = 35;

    static const Instrument CTrumpet  = 48;
    static const Instrument Trumpet  = CTrumpet;
    static const Instrument FrenchHorn  = 49;
    static const Instrument Horn  = FrenchHorn;
    static const Instrument TenorTrombone = 50;
    static const Instrument Trombone = TenorTrombone;
    static const Instrument Tuba = 51;

    static const Instrument Piano = 64;

    static int minNote(Instrument inst)
    {
      switch (inst)
      {
      case Soprano: return 56;
      case MezzoSoprano: return 55;
      case Alto: return 54;
      case Contralto: return 53;
      case Tenor: return 43;
      case Baritone: return 42;
      case Bass: return 34;
      case SopranoChoir: return 60;
      case AltoChoir: return 53; // 54
      case TenorChoir: return 47; // 48
      case BassChoir: return 40;
      case Violin: return 55;
      case Viola: return 48;
      case Cello: return 36;
      case Contrabass: return 28;
      case Flute: return 60;
      case Oboe: return 58;
      case BfClarinet: return 50;
      case Bassoon: return 34;
      case CTrumpet: return 52;
      case FrenchHorn: return 35;
      case TenorTrombone: return 40;
      case Tuba: return 26;
      case Piano: return 22;
      default: return -1;
      }
    }

    static int maxNote(Instrument inst)
    {
      switch (inst)
      {
      case Soprano: return 87;
      case MezzoSoprano: return 82;
      case Alto: return 80;
      case Contralto: return 78;
      case Tenor: return 66;
      case Baritone: return 67;
      case Bass: return 65;
      case SopranoChoir: return 81;
      case AltoChoir: return 74; //77
      case TenorChoir: return 67; //69
      case BassChoir: return 60; // 62
      case Violin: return 103;
      case Viola: return 93;
      case Cello: return 84;
      case Contrabass: return 67;
      case Flute: return 96;
      case Oboe: return 91;
      case BfClarinet: return 91;
      case Bassoon: return 72;
      case CTrumpet: return 84;
      case FrenchHorn: return 77;
      case TenorTrombone: return 72;
      case Tuba: return 67;
      case Piano: return 108;
      default: return -1;
      }
    }

    static int transposition(Instrument inst)
    {
      switch (inst)
      {
      case BfClarinet: return -2;
      case Contrabass: return -12;
      case FrenchHorn: return -5;
      default: return 0;
      }
    }

    static int midiProg(Instrument inst)
    {
      switch (inst)
      {
      case Soprano: return 52;
      case MezzoSoprano: return 52;
      case Alto: return 52;
      case Contralto: return 52;
      case Tenor: return 53;
      case Baritone: return 53;
      case Bass: return 53;
      case SopranoChoir: return 52;
      case AltoChoir: return 52;
      case TenorChoir: return 53;
      case BassChoir: return 53;
      case Violin: return 40;
      case Viola: return 41;
      case Cello: return 42;
      case Contrabass: return 43;
      case Flute: return 73;
      case Oboe: return 68;
      case BfClarinet: return 71;
      case Bassoon: return 70;
      case CTrumpet: return 56;
      case FrenchHorn: return 60;
      case TenorTrombone: return 57;
      case Tuba: return 58;
      case Piano: return 0;
      default: return -1;
      }
    }

    static String toString(Instrument inst)
    {
      switch (inst)
      {
      case Soprano: return "Soprano";
      case MezzoSoprano: return "Mezzo-Soprano";
      case Alto: return "Alto";
      case Contralto: return "Contralto";
      case Tenor: return "Tenor";
      case Baritone: return "Baritone";
      case Bass: return "Bass";
      case SopranoChoir: return "Soprano Choir";
      case AltoChoir: return "Alto Choir";
      case TenorChoir: return "Tenor Choir";
      case BassChoir: return "Bass Choir";
      case Violin: return "Violin";
      case Viola: return "Viola";
      case Cello: return "Cello";
      case Contrabass: return "Contrabass";
      case Flute: return "Flute";
      case Oboe: return "Oboe";
      case BfClarinet: return "Bf Clarinet";
      case Bassoon: return "Bassoon";
      case CTrumpet: return "C Trumpet";
      case FrenchHorn: return "French Horn";
      case TenorTrombone: return "Tenor Trombone";
      case Tuba: return "Tuba";
      case Piano: return "Piano";
      default: return "";
      }
    }

    static Instrument fromString(String str)
    {
      if (str.equalsIgnoreCase("Soprano")) return Soprano;
      if (str.equalsIgnoreCase("Mezzo-Soprano")) return MezzoSoprano;
      if (str.equalsIgnoreCase("Alto")) return Alto;
      if (str.equalsIgnoreCase("Contralto")) return Contralto;
      if (str.equalsIgnoreCase("Tenor")) return Tenor;
      if (str.equalsIgnoreCase("Baritone")) return Baritone;
      if (str.equalsIgnoreCase("Bass")) return Bass;
      if (str.equalsIgnoreCase("Soprano Choir")) return SopranoChoir;
      if (str.equalsIgnoreCase("Alto Choir")) return AltoChoir;
      if (str.equalsIgnoreCase("Tenor Choir")) return TenorChoir;
      if (str.equalsIgnoreCase("Bass Choir")) return BassChoir;
      if (str.equalsIgnoreCase("Violin")) return Violin;
      if (str.equalsIgnoreCase("Viola")) return Viola;
      if (str.equalsIgnoreCase("Cello")) return Cello;
      if (str.equalsIgnoreCase("Contrabass")) return Contrabass;
      if (str.equalsIgnoreCase("Flute")) return Flute;
      if (str.equalsIgnoreCase("Oboe")) return Oboe;
      if (str.equalsIgnoreCase("Bf Clarinet")) return BfClarinet;
      if (str.equalsIgnoreCase("Bassoon")) return Bassoon;
      if (str.equalsIgnoreCase("C Trumpet")) return CTrumpet;
      if (str.equalsIgnoreCase("French Horn")) return FrenchHorn;
      if (str.equalsIgnoreCase("Tenor Trombone")) return TenorTrombone;
      if (str.equalsIgnoreCase("Tuba")) return Tuba;
      if (str.equalsIgnoreCase("Piano")) return Piano;
      return Empty;
    }

  };

}
#endif



