/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencIntervals_h
#define mencIntervals_h

#include "mencNotes.h"
#include "mencScales.h"
#include <stdlib.h>       // for 'abs'

namespace menc
{

  /** IntervalDistance measures the number of lines/spaces that an Interval spans **/

  class IntervalDistances
  {
  public:
    static const IntervalDistance Unison = 1;
    static const IntervalDistance Second = 2;
    static const IntervalDistance Third = 3;
    static const IntervalDistance Fourth = 4;
    static const IntervalDistance Fifth = 5;
    static const IntervalDistance Sixth = 6;
    static const IntervalDistance Seventh = 7;
    static const IntervalDistance Octave = 8;
    static const IntervalDistance Empty = -1;

    /** create an IntervalDistance from octave and letter information **/

  static IntervalDistance betweenNotes(int octave1, Letter letter1,  int octave2, Letter letter2)
  {
    int letter_index1 = octave1 * 7 + letter1;
    int letter_index2 = octave2 * 7 + letter2;

    int letter_distance = abs(letter_index1 - letter_index2);

    if(letter_distance%7==0 && letter_distance!=0)
      return Octave;
    else
      return Unison+(letter_distance%7);
  }

  static int octaves(int octave1, Letter letter1, int octave2, Letter letter2)
  {
    int letter_index1 = octave1 * 7 + letter1;
    int letter_index2 = octave2 * 7 + letter2;

    int letter_distance = abs(letter_index1 - letter_index2);

    /*Notice that since Octave is a valid normal interval, we actually don't 
    want to start counting additional octaves until a major ninth, which is why
    we have (letter_distance - 1) / 7.*/
    if(letter_distance > 7)
      return((letter_distance-1) / 7);
    else
      return 0;
  }

    /** Predicates for distances spanned **/
  
  static bool isUnison(IntervalDistance distance)
    {
      return(distance == Unison);
    }
  
  static bool isSecond(IntervalDistance distance)
    {
      return(distance == Second);
    }
  
  static bool isThird(IntervalDistance distance)
    {
      return(distance == Third);
    }
  
  static bool isFourth(IntervalDistance distance)
    {
      return(distance == Fourth);
    }
  
  static bool isFifth(IntervalDistance distance)
    {
      return(distance == Fifth);
    }
  
  static bool isSixth(IntervalDistance distance)
    {
      return(distance == Sixth);
    }
  
  static bool isSeventh(IntervalDistance distance)
    {
      return(distance == Seventh);
    }
  
  static bool isOctave(IntervalDistance distance)
    {
      return(distance == Octave);
    }

    /** less useful predicates **/

    static bool isSkip(IntervalDistance distance)
      {
        return (distance == Third);
      }
    
    static bool isLeap(IntervalDistance distance)
      {
        return (distance >= Fourth);
      }
    
    static bool isSkipOrLeap(IntervalDistance distance)
      {
        return (distance >= Third);
      }
    
    static bool isPerfect(IntervalDistance distance)
      {
        return (distance == Unison || 
                distance == Fourth || 
                distance == Fifth ||
                distance == Octave);
      }
    
    static bool isImperfect(IntervalDistance distance)
      {
        return (! isPerfect(distance) );
      }
    
    static IntervalDistance fromString(String name)
    {
      if(name == "unison" )
        return Unison;
      else if (name == "2nd" || name == "second" )
        return Second;
      else if (name == "3rd" || name == "third" )
        return Third;
      else if (name == "4th" || name == "fourth" )
        return Fourth;
      else if (name == "5th" || name == "fifth" )
        return Fifth;
      else if (name == "6th" || name == "sixth" )
        return Sixth;
      else if (name == "7th" || name == "seventh" )
        return Seventh;
      else if (name == "octave" )
        return Octave;
      else
        return Empty;
    }

    static String toString(IntervalDistance distance)
    {
      String distance_string;
      if (distance == IntervalDistances::Empty)
        distance_string = "empty";
      else
        distance_string = String::intToString(distance);
      return distance_string;
    }

    static String toPrettyString(IntervalDistance distance)
    {
      if (distance == Unison)
        return "unison";
      else if (distance == Octave)
        return "octave";
      else if (distance == Second)
        return "second";
      else if (distance == Third)
        return "third";
      else if (distance == Fourth)
        return "fourth";
      else if (distance == Fifth)
        return "fifth";
      else if (distance == Sixth)
        return "sixth";
      else if (distance == Seventh)
        return "seventh";
      else
        return "empty";
    }
  };
  
  
  /** Interval qualites, from quintuply diminished (F## to Bbb) to quintuply augmented **/
  
  class IntervalQualities
  {
  public:    
    static const IntervalQuality QuintuplyDiminished = 0;
    static const IntervalQuality QuadruplyDiminished = 1;
    static const IntervalQuality TriplyDiminished = 2; 
    static const IntervalQuality DoublyDiminished = 3;
    static const IntervalQuality Diminished = 4;
    static const IntervalQuality Minor = 5;
    static const IntervalQuality Perfect = 6;
    static const IntervalQuality Major = 7;
    static const IntervalQuality Augmented = 8;
    static const IntervalQuality DoublyAugmented = 9;
    static const IntervalQuality TriplyAugmented = 10;
    static const IntervalQuality QuadruplyAugmented = 11;
    static const IntervalQuality QuintuplyAugmented = 12;
    
    static const IntervalQuality Empty = -1;
    static const IntervalQuality AnyQuality = Empty;
    
    static IntervalQuality betweenNotes(int octave1, Letter letter1, Accidental accidental1, int octave2, Letter letter2, Accidental accidental2)
      {
    const IntervalQuality transition_table[7][7] =
    {
      /*      C       D       E       F          G       A       B      */
      /*C*/  {Perfect,Major  ,Major  ,Perfect   ,Perfect,Major  ,Major  },
      /*D*/  {Minor  ,Perfect,Major  ,Minor     ,Perfect,Perfect,Major  },
      /*E*/  {Minor  ,Minor  ,Perfect,Minor     ,Minor  ,Perfect,Perfect},
      /*F*/  {Perfect,Major  ,Major  ,Perfect   ,Major  ,Major  ,Augmented},
      /*G*/  {Perfect,Perfect,Major  ,Minor     ,Perfect,Major  ,Major  },
      /*A*/  {Minor  ,Perfect,Perfect,Minor     ,Minor  ,Perfect,Major  },
      /*B*/  {Minor  ,Minor  ,Perfect,Diminished,Minor  ,Minor  ,Perfect}
    };

    int letter_index1 = octave1 * 7 + letter1;
    int letter_index2 = octave2 * 7 + letter2;

    if(letter_index1 == letter_index2) //Unison
    {
      if(accidental1 < accidental2) //Augmented
        return Augmented + (accidental2 - accidental1 - 1);
      else if(accidental2 < accidental1) //Diminished unison = augmented unison
        return Augmented + (accidental1 - accidental2 - 1);
      else
        return Perfect;
    }

    if(letter_index2 < letter_index1) //Descending interval
    {
      //Simply swap to make comparisons easier.
      int swap = letter2;
      letter2 = letter1;
      letter1 = swap;

      swap = accidental2;
      accidental2 = accidental1;
      accidental1 = swap;
    }

    /*We can assume now that the info for letter1/2, accidental1/2 
    refer to notes such that note 2 > note 1.*/
    IntervalQuality base_value = transition_table[letter1][letter2];

    //If there are no accidentals, then use the transition table as is.
    if(accidental1 == accidental2)
      return base_value;

    /*There are accidentals at this point, so take care of each case using the 
    transition table base value as starting point and adding a point for each 
    augmentation and subtracting a point for each diminution.*/

    /*Compute the change in accidental (number of points to be added or 
    subtracted).*/
    int accidental_delta;
    if(accidental1 < accidental2)
      accidental_delta = accidental2 - accidental1 - 1;
    else
      accidental_delta = accidental1 - accidental2 - 1;

    //Calculate the interval quality using the delta.
    switch(base_value)
    {
    case Diminished: //Note can only occur for perfect interval 5th/4th.
      if(accidental1 < accidental2) //Augmented
      {
        if(accidental_delta == 0)
          return Perfect;
        else
          return Augmented + accidental_delta - 1;
      }
      else //Diminished
        return DoublyDiminished - accidental_delta;
    case Minor:
      if(accidental1 < accidental2) //Augmented
        return Major + accidental_delta;
      else //Diminished
        return Diminished - accidental_delta;
    case Perfect:
      if(accidental1 < accidental2) //Augmented
        return Augmented + accidental_delta;
      else //Diminished
        return Diminished - accidental_delta;
    case Major:
      if(accidental1 < accidental2) //Augmented
        return Augmented + accidental_delta;
      else //Diminished
        return Minor - accidental_delta;
    case Augmented:
      if(accidental1 < accidental2) //Augmented
      {
        return DoublyAugmented + accidental_delta;
      }
      else //Diminished
        if(accidental_delta == 0)
          return Perfect;
        else
          return Diminished - accidental_delta + 1;
    default:
      return Empty;
    }
  }
    static bool isCommonQuality(IntervalQuality quality)
    {
      switch(quality)
        {
        case Perfect:
        case Major:
        case Minor:
        case Augmented:
        case Diminished:
          return true;
        default:
          return false;
        }
    }
    
    /** predicate for testing interval qualities */
    
    static bool isQuintuplyDiminished(IntervalQuality quality)
    {
      return (quality==QuintuplyDiminished);
    }
    
    static bool isQuadruplyDiminished(IntervalQuality quality)
    {
      return (quality==QuadruplyDiminished);
    }
    
    static bool isTriplyDiminished(IntervalQuality quality)
    {
      return (quality==TriplyDiminished);
    }
    
    static bool isDoublyDiminished(IntervalQuality quality)
    {
      return (quality==DoublyDiminished);
    }
    
    static bool isDiminished(IntervalQuality quality)
    {
      return (quality==Diminished);
    }
    
    static bool isMinor(IntervalQuality quality)
    {
      return (quality==Minor);
    }
    
    static bool isPerfect(IntervalQuality quality)
    {
      return (quality==Perfect);
    }
    
    static bool isMajor(IntervalQuality quality)
    {
      return (quality==Major);
    }
    
    static bool isAugmented(IntervalQuality quality)
    {
      return (quality==Augmented);
    }
    
    static bool isDoublyAugmented(IntervalQuality quality)
    {
      return (quality==DoublyAugmented);
    }
    
    static bool isTriplyAugmented(IntervalQuality quality)
    {
      return (quality==TriplyAugmented);
    }
    
    static bool isQuadruplyAugmented(IntervalQuality quality)
    {
      return (quality==QuadruplyAugmented);
    }
    
    static bool isQuintuplyAugmented(IntervalQuality quality)
    {
      return (quality==QuintuplyAugmented);
    }
    
    static IntervalQuality fromString(String name)
    {
      if (name == "P")
        return Perfect;
      else if (name == "M")
        return Major;
      else if (name == "m")
        return Minor;
      else if (name == "d")
        return Diminished;
      else if (name == "A")
        return Augmented;
      else if (name == "dd")
        return DoublyDiminished;
      else if (name == "AA")
        return DoublyAugmented;
      else if (name == "ddd")
        return TriplyDiminished;
      else if (name == "AAA")
        return TriplyAugmented;
      else if (name == "dddd")
        return QuadruplyDiminished;
      else if (name == "AAAA")
        return QuadruplyAugmented;
      else if (name == "ddddd")
        return QuintuplyDiminished;
      else if (name == "AAAAA")
        return QuintuplyAugmented;
      else
        return Empty;
    }
    
    static String toString(IntervalQuality quality)
    {
      switch (quality)
        {
        case Perfect:
          return "P";
        case Major:
          return "M";
        case Minor:
          return "m";
        case Diminished:
          return "d";
        case Augmented:
          return "A";
        case DoublyDiminished:
          return "dd";
        case DoublyAugmented:
          return "AA";
        case TriplyDiminished:
          return "ddd";
        case TriplyAugmented:
          return "AAA";
        case QuadruplyDiminished:
          return "dddd";
        case QuadruplyAugmented:
          return "AAAA";
        case QuintuplyDiminished:
          return "ddddd";
        case QuintuplyAugmented:
          return "AAAAA";
        default:
          return "empty";
        }
    }
    
    static String toPrettyString(IntervalQuality quality)
    {
      switch (quality)
        {
        case Perfect:
          return "perfect";
        case Major:
          return "major";
        case Minor:
          return "minor";
        case Diminished:
          return "diminished";
        case Augmented:
          return "augmented";
        case DoublyDiminished:
          return "doubly-diminished";
        case DoublyAugmented:
          return "double-augmented";
        case TriplyDiminished:
          return "triply-diminished";
        case TriplyAugmented:
          return "triply-augmented";
        case QuadruplyDiminished:
          return "quadruply-diminished";
        case QuadruplyAugmented:
          return "quadruply-augmented";
        case QuintuplyDiminished:
          return "quintuply-diminished";
        case QuintuplyAugmented:
          return "quintuply-augmented";
        default:
          return "empty";
        }
    }
  };

  class IntervalTypes
  {
  private:
    static const int32 QualityBits = 4;
  public:
    static const IntervalType Empty = 0;
    static const IntervalType DiminishedUnison = (IntervalQualities::Diminished << QualityBits) + IntervalDistances::Unison;
    static const IntervalType PerfectUnison = (IntervalQualities::Perfect << QualityBits) + IntervalDistances::Unison;
    static const IntervalType AugmentedUnison = (IntervalQualities::Augmented << QualityBits) + IntervalDistances::Unison;
    static const IntervalType DiminishedSecond = (IntervalQualities::Diminished << QualityBits) + IntervalDistances::Second;
    static const IntervalType MinorSecond = (IntervalQualities::Minor << QualityBits) + IntervalDistances::Second;
    static const IntervalType MajorSecond = (IntervalQualities::Major << QualityBits) + IntervalDistances::Second;
    static const IntervalType AugmentedSecond = (IntervalQualities::Augmented << QualityBits) + IntervalDistances::Second;
    static const IntervalType DiminishedThird = (IntervalQualities::Diminished << QualityBits) + IntervalDistances::Third;
    static const IntervalType MinorThird = (IntervalQualities::Minor << QualityBits) + IntervalDistances::Third;
    static const IntervalType MajorThird = (IntervalQualities::Major << QualityBits) + IntervalDistances::Third;
    static const IntervalType AugmentedThird = (IntervalQualities::Augmented << QualityBits) + IntervalDistances::Third;
    static const IntervalType DiminishedFourth = (IntervalQualities::Diminished << QualityBits) + IntervalDistances::Fourth;
    static const IntervalType PerfectFourth = (IntervalQualities::Perfect << QualityBits) + IntervalDistances::Fourth;
    static const IntervalType AugmentedFourth = (IntervalQualities::Augmented << QualityBits) + IntervalDistances::Fourth;
    static const IntervalType DiminishedFifth = (IntervalQualities::Diminished << QualityBits) + IntervalDistances::Fifth;
    static const IntervalType PerfectFifth = (IntervalQualities::Perfect << QualityBits) + IntervalDistances::Fifth;
    static const IntervalType AugmentedFifth = (IntervalQualities::Augmented << QualityBits) + IntervalDistances::Fifth;
    static const IntervalType DiminishedSixth = (IntervalQualities::Diminished << QualityBits) + IntervalDistances::Sixth;
    static const IntervalType MinorSixth = (IntervalQualities::Minor << QualityBits) + IntervalDistances::Sixth;
    static const IntervalType MajorSixth = (IntervalQualities::Major << QualityBits) + IntervalDistances::Sixth;
    static const IntervalType AugmentedSixth = (IntervalQualities::Augmented << QualityBits) + IntervalDistances::Sixth;
    static const IntervalType DiminishedSeventh = (IntervalQualities::Diminished << QualityBits) + IntervalDistances::Seventh;
    static const IntervalType MinorSeventh = (IntervalQualities::Minor << QualityBits) + IntervalDistances::Seventh;
    static const IntervalType MajorSeventh = (IntervalQualities::Major << QualityBits) + IntervalDistances::Seventh;
    static const IntervalType AugmentedSeventh = (IntervalQualities::Augmented << QualityBits) + IntervalDistances::Seventh;
    static const IntervalType PerfectOctave = (IntervalQualities::Perfect << QualityBits) + IntervalDistances::Octave;

    static const IntervalType AugmentedUnisonDown = -AugmentedUnison;
    static const IntervalType PerfectUnisonDown = -PerfectUnison;
    static const IntervalType DiminishedSecondDown = -DiminishedSecond;
    static const IntervalType MinorSecondDown = -MinorSecond;
    static const IntervalType MajorSecondDown = -MajorSecond;
    static const IntervalType AugmentedSecondDown = -AugmentedSecond;
    static const IntervalType DiminishedThirdDown = -DiminishedThird;
    static const IntervalType MinorThirdDown = -MinorThird;
    static const IntervalType MajorThirdDown = -MajorThird;
    static const IntervalType AugmentedThirdDown = -AugmentedThird;
    static const IntervalType DiminishedFourthDown = -DiminishedFourth;
    static const IntervalType PerfectFourthDown = -PerfectFourth;
    static const IntervalType AugmentedFourthDown = -AugmentedFourth;
    static const IntervalType DiminishedFifthDown = -DiminishedFifth;
    static const IntervalType PerfectFifthDown = -PerfectFifth;
    static const IntervalType AugmentedFifthDown = -AugmentedFifth;
    static const IntervalType DiminishedSixthDown = -DiminishedSixth;
    static const IntervalType MinorSixthDown = -MinorSixth;
    static const IntervalType MajorSixthDown = -MajorSixth;
    static const IntervalType AugmentedSixthDown = -AugmentedSixth;
    static const IntervalType DiminishedSeventhDown = -DiminishedSeventh;
    static const IntervalType MinorSeventhDown = -MinorSeventh;
    static const IntervalType MajorSeventhDown = -MajorSeventh;
    static const IntervalType AugmentedSeventhDown = -AugmentedSeventh;
    static const IntervalType PerfectOctaveDown = -PerfectOctave;

    //Helpers...

    static IntervalType fromQualityAndDistance(IntervalQuality qual, IntervalDistance dist)
    {
      return (IntervalType)((qual << QualityBits) + dist);
    }

    static IntervalQuality toQuality(IntervalType type)
    {
      return abs(type) >> QualityBits;
    }

    static IntervalDistance toDistance(IntervalType type)
    {
      return abs(type) % (1 << QualityBits);
    }

    static bool isAscending(IntervalType type)
    {
      return (type>=0); //possible because both can't be zero (zero, won't be shared)
    }

    static String toString(IntervalType type)
    {
      String type_string = "";
      IntervalQuality q=toQuality(type);
      IntervalDistance d=toDistance(type);
      type_string += IntervalQualities::toString(q);
      type_string += IntervalDistances::toString(d);
      return type_string;
    }

    static String toPrettyString(IntervalType type)
    {
      String type_string = "";
      IntervalQuality q=toQuality(type);
      IntervalDistance d=toDistance(type);
      type_string += IntervalQualities::toPrettyString(q);
      type_string += " ";
      type_string += IntervalDistances::toPrettyString(d);
      return type_string;
    }

    static IntervalType fromString(String name)
    {
      IntervalQuality q=IntervalQualities::fromString(name);
      IntervalDistance d=IntervalDistances::fromString(name);
      return (q << QualityBits) + d;
    }
  };

  class Interval : public TypedBitfield<IntervalBitfield>
  {

  private:
    //LSB

    //BIT 0: Direction Ascending (true/false) = 1 bit
    static const int i_Direction = 0;

    //BITS 1-4: Intervallic Quality (0-12) = 4 bits
    static const int i_Quality = 1;
    static const int n_Quality = 4;

    //BITS 5-7: Intervallic Distance (1-8) = 3 bits
    static const int i_Distance = 5;
    static const int n_Distance = 3;

    //BITS 8-11: Additional Octaves (0 to 15) = 4 bits
    static const int i_Octaves = 8;
    static const int n_Octaves = 4;

    //BITS 12-22: Unused

    //MSB

    //Internal helpers

    static int semitonesFromQualityAndDistance(IntervalQuality quality, IntervalDistance distance)
    {
      if(quality==IntervalQualities::Empty)
        return Invalid;
      
      else if(quality <= IntervalQualities::Diminished && quality >= 
              IntervalQualities::QuintuplyDiminished)
        {
          switch(distance)
            {
            case IntervalDistances::Second:
              return 0 - (IntervalQualities::Diminished - quality);
            case IntervalDistances::Third:
              return 2 - (IntervalQualities::Diminished - quality);
            case IntervalDistances::Fourth:
              return 4 - (IntervalQualities::Diminished - quality);
            case IntervalDistances::Fifth:
              return 6 - (IntervalQualities::Diminished - quality);
            case IntervalDistances::Sixth:
              return 7 - (IntervalQualities::Diminished - quality);
            case IntervalDistances::Seventh:
              return 9 - (IntervalQualities::Diminished - quality);
            case IntervalDistances::Octave:
              return 11 - (IntervalQualities::Diminished - quality);
            }
        }
      else if(quality == IntervalQualities::Minor)
        {
          switch(distance)
            {
            case IntervalDistances::Second:
              return 1;
            case IntervalDistances::Third:
              return 3;
            case IntervalDistances::Sixth:
              return 8;
            case IntervalDistances::Seventh:
              return 10;
            }
        }
      else if(quality == IntervalQualities::Perfect)
        {
          switch(distance)
            {
            case IntervalDistances::Unison:
              return 0;
            case IntervalDistances::Fourth:
              return 5;
            case IntervalDistances::Fifth:
              return 7;
            case IntervalDistances::Octave:
              return 12;
            }
        }
      else if(quality == IntervalQualities::Major)
        {
          switch(distance)
            {
            case IntervalDistances::Second:
              return 2;
            case IntervalDistances::Third:
              return 4;
            case IntervalDistances::Sixth:
              return 9;
            case IntervalDistances::Seventh:
              return 11;
            }
        }
      else if(quality >= IntervalQualities::Augmented && quality <= 
              IntervalQualities::QuintuplyAugmented)
        {
          switch(distance)
            {
            case IntervalDistances::Unison:
              return 1 + (quality - IntervalQualities::Augmented);
            case IntervalDistances::Second:
              return 3 + (quality - IntervalQualities::Augmented);
            case IntervalDistances::Third:
              return 5 + (quality - IntervalQualities::Augmented);
            case IntervalDistances::Fourth:
              return 6 + (quality - IntervalQualities::Augmented);
            case IntervalDistances::Fifth:
              return 8 + (quality - IntervalQualities::Augmented);
            case IntervalDistances::Sixth:
              return 10 + (quality - IntervalQualities::Augmented);
            case IntervalDistances::Seventh:
              return 12 + (quality - IntervalQualities::Augmented);
            case IntervalDistances::Octave:
              return 13 + (quality - IntervalQualities::Augmented);
            }
        }
      return Invalid;
    }
    
    static const int Invalid = -128;

  public:

    //Constructors

    Interval()
      {
        //Set to perfect unison.
        octaves(0);
        distance(IntervalDistances::Unison);
        quality(IntervalQualities::Perfect);
        ascending(true);
      }

    Interval(String name)
    {
      fromString(name);
    }

    Interval(IntervalType type)
      {
        octaves(0);
        //This is a mess...
        if (type==IntervalTypes::Empty)
          {
            distance(IntervalDistances::Empty);
            quality(IntervalQualities::Empty);
            ascending(true);
          }
        else 
          {
            distance(IntervalTypes::toDistance(type));
            quality(IntervalTypes::toQuality(type));
            ascending(IntervalTypes::isAscending(type));
          }
      }

    Interval(Note note1, Note note2)
      {
        betweenNotes(note1,note2);
      }
    
    /** Return an ascending, less-than-one octave interval between a pitch and a note.*/

    Interval(Pitch p, Note n)
      {
        Octave o=n.octave();
        Letter l=n.letter();
        Accidental a=n.accidental();
        Note x=Note(o, l, a);
        x.pitch(p);
        /// HKT FIX
        ///        if (x > n) x=x.transpose(IntervalTypes::PerfectOctaveDown);
        if (x>n)
          x.octave(x.octave()-1);
        *this=Interval(x,n);
      }
    
    /** Return an ascending, less-than-one octave interval between two pitches.*/

    Interval(Pitch p1, Pitch p2)
    {
      //Return an ascending, less-than-one octave interval between two pitches.
      Note n1=Note(p1,4);
      Note n2=Note(p2,4);
      /// HKT FIX
      ///      if (n1 > n2) n1=n1.transpose(IntervalTypes::PerfectOctaveDown);
      if (n1>n2)
        n1.octave(n1.octave()-1);
      *this=Interval(n1,n2);
    }


    //    Interval(Key key1, Key key2);

    Interval(int Octaves, IntervalDistance Distance, IntervalQuality Quality, bool Ascending=true)
      {
        octaves(Octaves);
        distance(Distance);
        quality(Quality);
        ascending(Ascending);
      }

    /** convert interval to a scale degree above some nominal tonic else empty */
    
    ScaleDegree toScaleDegree()
    {
      switch (distance())
        {
        case IntervalDistances::Unison:
          switch (quality())
            {
            case IntervalQualities::Diminished: return ScaleDegrees::LoweredTonic;
            case IntervalQualities::Perfect: return ScaleDegrees::Tonic;
            case IntervalQualities::Augmented: return ScaleDegrees::RaisedTonic;
            default: return ScaleDegrees::Empty;
            }
        case IntervalDistances::Second:
          switch (quality())
            {
            case IntervalQualities::Minor: return ScaleDegrees::LoweredSupertonic;
            case IntervalQualities::Major: return ScaleDegrees::Supertonic;
            case IntervalQualities::Augmented: return ScaleDegrees::RaisedSupertonic;
            default: return ScaleDegrees::Empty;
            }
        case IntervalDistances::Third:
          switch (quality())
            {
            case IntervalQualities::Minor: return ScaleDegrees::LoweredMediant;
            case IntervalQualities::Major: return ScaleDegrees::Mediant;
            case IntervalQualities::Augmented: return ScaleDegrees::RaisedMediant;
            default: return ScaleDegrees::Empty;
            }
        case IntervalDistances::Fourth:
          switch (quality())
            {
            case IntervalQualities::Diminished: return ScaleDegrees::LoweredSubdominant;
            case IntervalQualities::Perfect: return ScaleDegrees::Subdominant;
            case IntervalQualities::Augmented: return ScaleDegrees::RaisedSubdominant;
            default: return ScaleDegrees::Empty;
            }
        case IntervalDistances::Fifth:
          switch (quality())
            {
            case IntervalQualities::Diminished: return ScaleDegrees::LoweredDominant;
            case IntervalQualities::Perfect: return ScaleDegrees::Dominant;
            case IntervalQualities::Augmented: return ScaleDegrees::RaisedDominant;
            default: return ScaleDegrees::Empty;
            }
        case IntervalDistances::Sixth:
          switch (quality())
            {
            case IntervalQualities::Minor: return ScaleDegrees::LoweredSubmediant;
            case IntervalQualities::Major: return ScaleDegrees::Submediant;
            case IntervalQualities::Augmented: return ScaleDegrees::RaisedSubmediant;
            default: return ScaleDegrees::Empty;
            }
        case IntervalDistances::Seventh:
          switch (quality())
            {
            case IntervalQualities::Minor: return ScaleDegrees::LoweredLeadingTone;
            case IntervalQualities::Major: return ScaleDegrees::LeadingTone;
            case IntervalQualities::Augmented: return ScaleDegrees::RaisedLeadingTone;
            default: return ScaleDegrees::Empty;
            }
        default: return ScaleDegrees::Empty;
        }
    }

    /** return the interval distance of a scale degree above some nominal tonic */

    static Interval fromScaleDegree(ScaleDegree deg)
      {
        switch (deg)
          {
          case ScaleDegrees::LoweredTonic:
            return Interval(0, IntervalDistances::Unison, IntervalQualities::Diminished);
          case ScaleDegrees::Tonic: 
            return Interval(0, IntervalDistances::Unison, IntervalQualities::Perfect);
          case ScaleDegrees::RaisedTonic:
            return Interval(0, IntervalDistances::Unison, IntervalQualities::Augmented);
          case ScaleDegrees::LoweredSupertonic: 
            return Interval(0, IntervalDistances::Second, IntervalQualities::Minor);
          case ScaleDegrees::Supertonic: 
            return Interval(0, IntervalDistances::Second, IntervalQualities::Major);
          case ScaleDegrees::RaisedSupertonic: 
            return Interval(0, IntervalDistances::Second, IntervalQualities::Augmented);
          case ScaleDegrees::LoweredMediant: 
            return Interval(0, IntervalDistances::Third, IntervalQualities::Minor);
          case ScaleDegrees::Mediant: 
            return Interval(0, IntervalDistances::Third, IntervalQualities::Major);
          case ScaleDegrees::RaisedMediant: 
            return Interval(0, IntervalDistances::Third, IntervalQualities::Augmented);
          case ScaleDegrees::LoweredSubdominant: 
            return Interval(0, IntervalDistances::Fourth, IntervalQualities::Diminished);
          case ScaleDegrees::Subdominant: 
            return Interval(0, IntervalDistances::Fourth, IntervalQualities::Perfect);
          case ScaleDegrees::RaisedSubdominant:
            return Interval(0, IntervalDistances::Fourth, IntervalQualities::Augmented);
          case ScaleDegrees::LoweredDominant:
            return Interval(0, IntervalDistances::Fifth, IntervalQualities::Diminished);
          case ScaleDegrees::Dominant:
            return Interval(0, IntervalDistances::Fifth, IntervalQualities::Perfect);
          case ScaleDegrees::RaisedDominant:
            return Interval(0, IntervalDistances::Fifth, IntervalQualities::Augmented);
          case ScaleDegrees::LoweredSubmediant:
            return Interval(0, IntervalDistances::Sixth, IntervalQualities::Minor);
          case ScaleDegrees::Submediant: 
            return Interval(0, IntervalDistances::Sixth, IntervalQualities::Major);
          case ScaleDegrees::RaisedSubmediant:
            return Interval(0, IntervalDistances::Sixth, IntervalQualities::Augmented);
          case ScaleDegrees::LoweredLeadingTone: 
            return Interval(0, IntervalDistances::Seventh, IntervalQualities::Minor);
          case ScaleDegrees::LeadingTone: 
            return Interval(0, IntervalDistances::Seventh, IntervalQualities::Major);
          case ScaleDegrees::RaisedLeadingTone: 
            return Interval(0, IntervalDistances::Seventh, IntervalQualities::Augmented);
          default:
            return Invalid;
          }
      }
    
    bool isEmpty()
    {
      return ((quality()==IntervalQualities::Empty) ||
              (distance()==IntervalDistances::Empty));
    }
    
    //Direction
    bool ascending(void)
    {
      return readBool(i_Direction);
    }
    
    void ascending(bool isAscending)
    {
      writeBool(i_Direction, isAscending);
    }
    
    bool descending(void)
    {
      return !ascending();
    }
    
    int directionSign(void)
    {
      if(ascending())
        return 1;
      else
        return -1;
    }
    
    void reverse(void)
    {
      ascending(!ascending());
    }
    
    //Intervallic quality
    IntervalQuality quality(void)
    {
      return read(i_Quality,n_Quality);
    }
    
    void quality(IntervalQuality newQuality)
    {
      write(i_Quality,n_Quality,newQuality);
    }
    
    //Intervallic distance
    IntervalDistance distance(void)
    {
      return read(i_Distance,n_Distance) + IntervalDistances::Unison;
    }

    void distance(IntervalDistance newDistance)
    {
      write(i_Distance, n_Distance, newDistance - IntervalDistances::Unison);
    }
    
    //Additional octaves
    int octaves(void)
    {
      return read(i_Octaves,n_Octaves);
    }
    
    void octaves(int newOctaves)
    {
      write(i_Octaves,n_Octaves,newOctaves);
    }
    
    //Semitones
    int semitones(void)
    {
      return (semitonesFromQualityAndDistance(quality(),distance()) + 
              octaves() * 12) * directionSign();
    }

    //Transposition
    void betweenNotes(Note note1, Note note2)
    {
      Accidental accidental1 = note1.accidental();
      Accidental accidental2 = note2.accidental();
      
      Letter letter1 = note1.letter();
      Letter letter2 = note2.letter();
      
      Octave octave1 = note1.octave();
      Octave octave2 = note2.octave();
      
      ascending(note1 <= note2);
      quality(IntervalQualities::betweenNotes(octave1,letter1,accidental1,
                                              octave2,letter2,accidental2));
      distance(IntervalDistances::betweenNotes(octave1,letter1,octave2,letter2));
      octaves(IntervalDistances::octaves(octave1,letter1,octave2,letter2));
    }
    
    void complement(bool truncateAdditionalOctaves=false)
    {
      distance(IntervalDistances::Octave - distance() + 
               IntervalDistances::Unison);
      quality(IntervalQualities::Perfect * 2 - quality());
      ascending(!ascending());
      if(truncateAdditionalOctaves)
        octaves(0);
    }
    
    void normalize(void)
    {
      if(distance()>IntervalDistances::Fourth)
        complement(false);
      octaves(0);
    }
    
    //Distance

    bool isUnison(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isUnison(distance());
      else
        return (IntervalDistances::isUnison(distance()) &&
                (quality() == qualityTest));
    }
    
    bool isSecond(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isSecond(distance());
      else
        return (IntervalDistances::isSecond(distance()) &&
                (quality() == qualityTest));
    }
    
    bool isThird(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isThird(distance());
      else
        return (IntervalDistances::isThird(distance()) &&
                (quality() == qualityTest));
    }
    
    bool isFourth(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isFourth(distance());
      else
        return (IntervalDistances::isFourth(distance()) &&
                (quality() == qualityTest));
    }
    
    bool isFifth(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isFifth(distance());
      else
        return (IntervalDistances::isFifth(distance()) &&
                (quality() == qualityTest));
    }
    
    bool isSixth(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isSixth(distance());
      else
        return (IntervalDistances::isSixth(distance()) &&
                (quality() == qualityTest));
    }
    
    bool isSeventh(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isSeventh(distance());
      else
        return (IntervalDistances::isSeventh(distance()) &&
                (quality() == qualityTest));
    }
    
    bool isOctave(IntervalQuality qualityTest=IntervalQualities::AnyQuality)
    {
      if(qualityTest==IntervalQualities::AnyQuality)
        return IntervalDistances::isOctave(distance());
      else
        return (IntervalDistances::isOctave(distance()) && 
                (quality() == qualityTest));
    }
    
    //Wrappers for common cases
    
    bool isPerfectUnison()
    {
      return isUnison(IntervalQualities::Perfect);
    }
    
    bool isMinorSecond()
    {
      return isSecond(IntervalQualities::Minor);
    }
    
    bool isMajorSecond()   
    {
      return isSecond(IntervalQualities::Major);
    }
    
    bool isMinorThird()
    {
      return isThird(IntervalQualities::Minor);
    }
    
    bool isMajorThird()  
    {
      return isThird(IntervalQualities::Major);
    }
    
    bool isPerfectFourth()
    {
      return isFourth(IntervalQualities::Perfect);
    }
    
    bool isAugmentedFourth()
    {
      return isFourth(IntervalQualities::Augmented);
    }
    
    bool isDiminishedFifth()
    {
      return isFifth(IntervalQualities::Diminished);
    }
    
    bool isPerfectFifth()
    {
      return isFifth(IntervalQualities::Perfect);
    }
    
    bool isMinorSixth()
    {
      return isSixth(IntervalQualities::Minor);
    }
    
    bool isMajorSixth()
    {
      return isSixth(IntervalQualities::Major);
    }
    
    bool isAugmentedSixth()
    {
      return isSixth(IntervalQualities::Augmented);
    }
    
    bool isMinorSeventh()
    {
      return isSeventh(IntervalQualities::Minor);
    }
    
    bool isMajorSeventh()
    {
      return isSeventh(IntervalQualities::Major);
    }
    
    bool isPerfectOctave()
    {
      return isOctave(IntervalQualities::Perfect);
    }
    
    //Quality
    
    bool isQuintuplyDiminished(void)
    {
      return IntervalQualities::isQuintuplyDiminished(quality());
    }
    
    bool isQuadruplyDiminished(void)
    {
      return IntervalQualities::isQuadruplyDiminished(quality());
    }
    
    bool isTriplyDiminished(void)
    {
      return IntervalQualities::isTriplyDiminished(quality());
    }
    
    bool isDoublyDiminished(void)
    {
      return IntervalQualities::isDoublyDiminished(quality());
    }
    
    bool isDiminished(void)
    {
      return IntervalQualities::isDiminished(quality());
    }
    
    bool isMinor(void)
    {
      return IntervalQualities::isMinor(quality());
    }
    
    bool isPerfect(void)
    {
      return IntervalQualities::isPerfect(quality());
    }
    
    bool isMajor(void)
    {
      return IntervalQualities::isMajor(quality());
    }
    
    bool isAugmented(void)
    {
      return IntervalQualities::isAugmented(quality());
    }
    
    bool isDoublyAugmented(void)
    {
      return IntervalQualities::isDoublyAugmented(quality());
    }
    
    bool isTriplyAugmented(void)
    {
      return IntervalQualities::isTriplyAugmented(quality());
    }
    
    bool isQuadruplyAugmented(void)
    {
      return IntervalQualities::isQuadruplyAugmented(quality());
    }
    
    bool isQuintuplyAugmented(void)
    {
      return IntervalQualities::isQuintuplyAugmented(quality());
    }
    
    //Distance+Quality distinctions
    bool isTritone(void)
    {
      if(isAugmented() && isFourth())
        return true;
      else if(isDiminished() && isFifth())
        return true;
      else
        return false;
    }
    
    // Voice-leading Predicates
    //These are true if interval is chromatic or diatonic half/whole step.

    bool isStep()
    {
      //True if interval is chromatic or diatonic half/whole step
      if (distance()<IntervalDistances::Third)
        {
          int i=abs(semitones());
          return ( (0<i) && (i<3) );
        }
      return false;
    }
    
    bool isLeap()
    {
      return IntervalDistances::isSkipOrLeap(distance());
    }
    
    bool isRepetition()
    {
      return isUnison(IntervalQualities::Perfect);
    }
    
    bool isAscending()
    {
      return ascending();
    }
    
    bool isDescending()
    {
      return descending();
    }
    
    bool isConsonant()
    {
      IntervalQuality q=quality();
      IntervalDistance d=distance();
      switch (d)
        {
        case IntervalDistances::Unison :
        case IntervalDistances::Octave :
        case IntervalDistances::Fifth :
          return (q==IntervalQualities::Perfect);
        case IntervalDistances::Third :
        case IntervalDistances::Sixth :      
          return ((q==IntervalQualities::Minor) ||
                  (q==IntervalQualities::Major));
        default:
          return false;
        }
    }
    
    bool isDissonant()
    {
      return (!isConsonant());
    }
    
    bool isSameDirection(Interval other)
    {
      return (directionSign() == other.directionSign());
    }
    
    bool isLeapSameDirection(Interval other)
    {
      return (isSameDirection(other) && isLeap() && other.isLeap());
    }
    
    //Compound/Simple
    
    bool isSimple(void)
    {
      return (octaves() == 0);
    }
    
    bool isCompound(void)
    {
      return (octaves() >= 1);
    }
    
    static Note transpose(Note note, Interval interval)
    {
      Octave o = note.octave();
      Letter l = note.letter();
      
      Octave new_o = o;
      Letter new_l = l;
      Accidental new_a = Accidentals::Natural;
      
      bool ascends = interval.ascending();
      IntervalDistance d = interval.distance();
      int extra_octaves = interval.octaves();
      
      if(ascends)
        {
          //Transpose the letter by the interval distance
          if(l + (d - 1) >= 7)
            new_o = o + 1; //traversed octave shift
          
          new_l = (l + (d - 1)) % 7;
          
          //Transpose the octaves
          new_o+=extra_octaves;
        }
      else
        {
          //Transpose the letter down by the interval distance
          if(l - (d - 1) < 0)
            new_o = o - 1; //traversed octave shift
          
          new_l = (l - (d - 1) + 14) % 7;
          
          //Transpose the octaves
          new_o-=extra_octaves;
        }
      
      //Compute the accidental by comparing semitones...
      //This is much more reliable than handling each of the horrible
      //screw cases.
      Note natural_note (Pitches::C, 4);
      natural_note.octave(new_o);
      natural_note.letter(new_l);
      natural_note.accidental(Accidentals::Natural);
      
      int referenceKeyNum = note.toMIDIKeyNumber() + interval.semitones();
      int naturalKeyNum = natural_note.toMIDIKeyNumber();
      
      new_a = Accidentals::Natural + (referenceKeyNum - naturalKeyNum);
      
      if(abs(new_a-Accidentals::Natural)>2)
        {
          //We have triple sharps/flats or higher,
          //so we clear everything out and quit.
          Note bad_note(-1);
          bad_note.valid(false);
          return bad_note;
        }
      
      Note new_note(new_o,new_l,new_a);
      return new_note;
    }
    
    //Helpers...
    
    String toString(bool showdir=false)
    {
      String interval = "";
      if (showdir && (! isUnison(IntervalQualities::Perfect) ))
        interval=(isAscending()) ? "+" : "-";
      interval += IntervalQualities::toString(quality());
      interval += IntervalDistances::toString(distance());
      int additional_octaves = octaves();
      if (additional_octaves > 0) 
        {
          interval += "+";
          interval += additional_octaves;
        }
      return interval;
    }
    
    String toPrettyString(void)
    {
        String interval = "";
        interval += IntervalQualities::toPrettyString(quality());
        interval += " ";
        interval += IntervalDistances::toPrettyString(distance());
        int additional_octaves = octaves();
        if (additional_octaves > 0) 
          {
            interval += " and ";
            interval += additional_octaves;
            if (additional_octaves>1)
              interval += " octaves";
            else
              interval += " octave";
          }
        return interval;
      }
    
    void fromString(String name)
    {
      int length = name.length();
      IntervalQuality q = IntervalQualities::Empty;
      int d_count = 0;
      int A_count = 0;
      
      //Parse the quality.
      for (int i=0;i<length;i++) 
        {
          if (name[i]=='m') 
            {
              q = IntervalQualities::Minor;
              break;
            }
          else if (name[i]=='M') 
            {
              q = IntervalQualities::Major;
              break;
            }
          else if (name[i]=='d') 
            {
              d_count++;
            }
          else if (name[i]=='A') 
            {
              A_count++;
            }
        }
      
      if (q!=IntervalQualities::Empty) 
        {
          if (d_count)
            q=IntervalQualities::Diminished-(d_count-1);
          else if (A_count)
            q=IntervalQualities::Augmented+(A_count-1);
        }
      /*Parse the distance, and also simultaneously figure out where to
        start parsing the octave.*/
      IntervalDistance d = IntervalDistances::Empty;
      int octave_info_start=length;
      for (int i=0;i<length;i++) 
        {
          int letter=name[i];
          if (letter>=48 || letter<=57) 
            {
              d=letter-48;
            }
          else if (name[i]=='+')
            octave_info_start=i+1;
        }
      //Finally parse the octave info.
      int additional_octaves=0;
      for (int i=octave_info_start;i<length;i++) 
        {
          int letter=name[i];
          if (letter>=48 || letter<=57) 
            {
              additional_octaves*=10;
              additional_octaves+=letter-48;
            }
        }
      /*Also parse the direction:
        / and < is ascending
        \ and > is descending
      */
      bool isAscending=true;
      for (int i=0;i<length;i++) 
        {
          if (name[i]=='\\' || name[i]=='>')
            isAscending=false;
        }
      
      //Store all of the information.
      ascending(isAscending);
      quality(q);
      distance(d);
      octaves(additional_octaves);
    }
    
    //Debugging
    
    String summarizeFields(void)
    {
        String summary = "-------------------";
        summary += "\ndirection: ";
        summary += String::intToString(readBool(i_Direction));
        summary += "\nquality: ";
        summary += String::intToString(read(i_Quality,n_Quality));
        summary += "\ndistance: ";
        summary += String::intToString(read(i_Distance,n_Distance));
        summary += "\nextra octaves: ";
        summary += String::intToString(read(i_Octaves,n_Octaves));
        summary += "valid: ";
        summary += String::intToString(valid());
        summary += "-------------------";
        return summary;
    }
  };
}

#endif
