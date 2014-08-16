/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencTones_h
#define mencTones_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{
  
  class ToneIds
  {
    
    static const int SubtypeShift = 4;
    
  public:
    
    static const ToneId Empty = 0;
    static const ToneId ChordTone = 1;
    static const ToneId Neighbor = 2;
    static const ToneId Passing = 3;
    static const ToneId Escape = 4;
    static const ToneId Changing = 5;
    static const ToneId Appogiatura = 6;
    static const ToneId Anticipation = 7;
    static const ToneId Pedal = 8;
    static const ToneId Suspension = 9;
    static const ToneId Retardation = 10;
    static const ToneId Ornament = 11;
    static const ToneId UnidentifiedNHT = 12;
    static const ToneId NonChordTone = UnidentifiedNHT;
    // qualities
    static const ToneId Root = 1;   
    static const ToneId Third = 2;   
    static const ToneId Fifth = 3;   
    static const ToneId Seventh = 4;
    static const ToneId Lower = 5;
    static const ToneId Upper = 6;
    static const ToneId _76 = 7;
    static const ToneId _43 = 8;
    static const ToneId _98 = 9;
    static const ToneId _23 = 10;
    static const ToneId _21 = 11;
    static const ToneId _78 = 12;
    
    static const ToneId RootOfChord = (Root << SubtypeShift) + ChordTone;
    static const ToneId ThirdOfChord = (Third << SubtypeShift) + ChordTone;
    static const ToneId FifthOfChord = (Fifth << SubtypeShift) + ChordTone;
    static const ToneId SeventhOfChord = (Seventh << SubtypeShift) + ChordTone;
    static const ToneId LowerNeighbor = (Lower << SubtypeShift) + Neighbor;
    static const ToneId UpperNeighbor = (Upper << SubtypeShift) + Neighbor;
    static const ToneId LowerPassing = (Lower << SubtypeShift) + Passing;
    static const ToneId UpperPassing = (Upper << SubtypeShift) + Passing;
    static const ToneId LowerEscape = (Lower << SubtypeShift) + Escape;
    static const ToneId UpperEscape = (Upper << SubtypeShift) + Escape;
    static const ToneId LowerChanging = (Lower << SubtypeShift) + Changing;
    static const ToneId UpperChanging = (Upper << SubtypeShift) + Changing;
    static const ToneId LowerAppogiatura = (Lower << SubtypeShift) + Appogiatura;
    static const ToneId UpperAppogiatura = (Upper << SubtypeShift) + Appogiatura;
    static const ToneId LowerAnticipation = (Lower << SubtypeShift) + Anticipation;
    static const ToneId UpperAnticipation = (Upper << SubtypeShift) + Anticipation;
    static const ToneId LowerPedal = (Lower << SubtypeShift) + Pedal;
    static const ToneId UpperPedal = (Upper << SubtypeShift) + Pedal;
    static const ToneId SevenSixSuspension = (_76 << SubtypeShift) + Suspension;
    static const ToneId FourThreeSuspension = (_43 << SubtypeShift) + Suspension;
    static const ToneId NineEightSuspension = (_98 << SubtypeShift) + Suspension;
    static const ToneId TwoThreeSuspension = (_23 << SubtypeShift) + Suspension;
    static const ToneId TwoOneSuspension = (_21 << SubtypeShift) + Suspension;
    static const ToneId SevenEightRitardation = (_78 << SubtypeShift) + Retardation;
    static const ToneId TwoThreeRitardation = (_23 << SubtypeShift) + Retardation;
  };
  
  /** Tone Types (8 bits)
      Quality Type
      -------------
      0000    empty
      root    chord
      third   chord
      fifth   chord
      lower   passing
      upper   passing
      lower   escape 
      upper   escape 
      lower   changing
      upper   changing
      lower   appogiatura
      upper   appogiatura
      lower   anticipation
      upper   anticipation
      lower   pedal
      upper   pedal
      lower   ornament
      upper   ornament
      7-6     suspension
      4-3     suspension
      9-8     suspension
      2-3     suspension (bass)
      2-1     suspension
      7-8    retardation
      2-3    retardation
  **/
  
  class ToneType : public TypedBitfield<ToneTypeBitfield>
  {
    
  private:
    
    static const int i_AllFields = 0;
    static const int n_AllFields = 8;
    static const int i_Type = 0;
    static const int n_Type = 4;
    static const int i_Quality = 4;
    static const int n_Quality = 4;
    
    bool testTypeAndQuality(ToneId ty, ToneId sub) 
    {
      if (type()==ty)
        if (sub==0) return true;
        else return (quality()==sub);
      else return false;
    }
  public:
    
    ToneType() 
      {
        write(i_AllFields, n_AllFields, ToneIds::Empty);
      }
    
    ToneType(ToneId id) 
      {
        write(i_AllFields, n_AllFields, id);
      }
    
    ToneType(ToneId qual, ToneId typ)
      {
        write(i_Quality, n_Quality, qual);
        write(i_Type, n_Type, typ);
      }
    
    ToneId typeAndQuality() const
    {
      return (ToneId)read(i_AllFields, n_AllFields);
    } 
    
    bool isEmpty()
    {
      return (read(i_AllFields, n_AllFields) == ToneIds::Empty);
    }
    
    ToneId type()
    {
      return (ToneId)read(i_Type, n_Type);
    }
    
    void type(ToneId ty)
    {
      write(i_Type, n_Type, ty);
    }
    
    ToneId quality()
    {
      return (ToneId)read(i_Quality, n_Quality);
    }
    
    void quality(ToneId ty)
    {
      write(i_Quality, n_Quality, ty);
    }
    
    bool isSame(ToneId id) 
    {
      return (id == typeAndQuality());
    }
    
    bool isChordTone(ToneId sub=0) 
    {
      return testTypeAndQuality(ToneIds::ChordTone, sub);
    }
    
    bool isRootOfChord() 
    {
      return testTypeAndQuality(ToneIds::ChordTone, ToneIds::Root);
    }
    
    bool isThirdOfChord() 
    {
      return testTypeAndQuality(ToneIds::ChordTone, ToneIds::Third);
    }
    
    bool isFifthOfChord() 
    {
      return testTypeAndQuality(ToneIds::ChordTone, ToneIds::Fifth);
    }
    
    bool isSeventhOfChord()
    {
      return testTypeAndQuality(ToneIds::ChordTone, ToneIds::Seventh);
    }
    
    /** true if the tone is a non chord tone. if typ is not empty then
        it shoud be the basic nht type or fully qualified nht type to
        test for. **/
    
    bool isNonChordTone(ToneId typ=0) 
    {
      if (type() > ToneIds::ChordTone)
        if (typ == 0) return true;
        else if (typ<16) return (type()==typ);
        else return (typeAndQuality()==typ);
      else return false;
    }
    
    bool isNHT(ToneId typ=0)
    {
      return isNonChordTone(typ);
    }
    
    bool isNeighborTone(ToneId qual=0) 
    {
      return testTypeAndQuality(ToneIds::Neighbor, qual);
    }
    
    bool isPassingTone(ToneId qual=0)
    {
      return testTypeAndQuality(ToneIds::Passing, qual);
    } 
    
    bool isEscapeTone(ToneId qual=0)
    {
      return testTypeAndQuality(ToneIds::Escape, qual);
    }
    
    bool isChangingTone(ToneId qual=0)
    {
      return testTypeAndQuality(ToneIds::Changing, qual);
    }
    
    bool isAppogiaturaTone(ToneId qual=0)
    {
      return testTypeAndQuality(ToneIds::Appogiatura, qual);
    }
    
    bool isAnticipationTone(ToneId qual=0)
    {
      return testTypeAndQuality(ToneIds::Anticipation, qual);
    }
    
    bool isPedalTone(ToneId qual=0)
    {
      return testTypeAndQuality(ToneIds::Pedal, qual);
    }
    
    bool isSuspensionTone(ToneId qual=0)
    {
      return testTypeAndQuality(ToneIds::Suspension, qual);
    }
    
    bool isRetardationTone(ToneId qual=0) 
    {
      return testTypeAndQuality(ToneIds::Retardation, qual);
    }
    
    bool isOrnamentTone(ToneId qual=0) 
    {
      return testTypeAndQuality(ToneIds::Ornament, qual);
    }
    
    /** wildcard match of tonetype to other, where Empty field(s) in
        other are always true wrt corresponding field in tonetype **/
    
    bool match(ToneType tok)
    {
      if (tok.isEmpty()) 
        return true;
      else
        return (tok.typeAndQuality()==typeAndQuality());
    }
    
    String toString() const
    {
      switch ( typeAndQuality() ) 
          {
          case ToneIds::RootOfChord:
            return "1";
          case ToneIds::ThirdOfChord:
            return "3";
          case ToneIds::FifthOfChord:
            return "5";
          case ToneIds::SeventhOfChord:
            return "7";
          case ToneIds::LowerNeighbor:
          case ToneIds::UpperNeighbor:
          case ToneIds::Neighbor:
            return "NT";
          case ToneIds::LowerPassing:
          case ToneIds::UpperPassing:
          case ToneIds::Passing:
            return "PT";
          case ToneIds::LowerEscape:
          case ToneIds::UpperEscape:
          case ToneIds::Escape:
            return "ET";
          case ToneIds::LowerChanging:
          case ToneIds::UpperChanging:
          case ToneIds::Changing:
            return "CT";
          case ToneIds::LowerAppogiatura :
          case ToneIds::UpperAppogiatura :
          case ToneIds::Appogiatura :
            return "APP";
          case ToneIds::LowerAnticipation :
          case ToneIds::UpperAnticipation :
          case ToneIds::Anticipation :
            return "ANT";
          case ToneIds::LowerPedal :
          case ToneIds::UpperPedal :
          case ToneIds::Pedal :
            return "PED";
          case ToneIds::SevenSixSuspension :
            return "76";
          case ToneIds::FourThreeSuspension :
            return "43";
          case ToneIds::NineEightSuspension :
            return "98";
          case ToneIds::TwoThreeSuspension :
            return "23";
          case ToneIds::TwoOneSuspension :
            return "21";
          case ToneIds::Suspension:
            return "SUS";
          case ToneIds::SevenEightRitardation :
            return "R78";
          case ToneIds::TwoThreeRitardation :
            return "R23";
          case ToneIds::Retardation:
            return "RET";
          case ToneIds::Ornament:
            return "ORN";
          case ToneIds::UnidentifiedNHT :
            return "NHT";
          case ToneIds::Empty :
          default:
            return "empty";
          }
      }
  };
}

#endif
