/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencChords_h
#define mencChords_h

#include "mencTypes.h"
#include "mencScales.h"
#include "mencOctaves.h"
#include "mencNotes.h"
#include "mencIntervals.h"
#include "mencArray.h"

namespace menc
{

  /** ChordQualities enumerate the possible triad and seventh tone types. max is 4 bits */

  class ChordQualities
  {

  public:
    
    static const ChordQuality Empty = 0;
    static const ChordQuality Diminished = 1;
    static const ChordQuality Minor = 2;
    static const ChordQuality Major = 3;
    static const ChordQuality Augmented = 4;  
    //Qualities for aug6 chords: dim. root and 3rd, 3rd and 5th
    static const ChordQuality DimThirdMajThird = 5;
    static const ChordQuality MajThirdDimThird = 6;
    static const ChordQuality MinThirdDimThird = 7;
    static const ChordQuality Wild = 0xF;
    
    static bool isMajor(ChordQuality qual)
    {
      return qual==Major;
    }
    
    static bool isMinor(ChordQuality qual)
    {
      return qual==Minor;
    }
    
    static bool isDiminished(ChordQuality qual)
    {
      return qual==Diminished;
    }
    
    static bool isAugmented(ChordQuality qual)
    {
      return qual==Augmented;
    }
    
    static bool isAugmentedSixth(ChordQuality qual)
    {
      return (qual==DimThirdMajThird ||
              qual==MajThirdDimThird ||  
              qual==MinThirdDimThird);
    }

    static bool isWild(ChordQuality qual)
    {
      return (qual==Wild);
    }

    static String toString(int q) 
    {
      if (q==Diminished) return "d";
      else if (q==Minor) return "m";
      else if (q==Major) return "M";
      else if (q==Augmented) return "A";
      else if (q==DimThirdMajThird) return "z";
      else if (q==MajThirdDimThird) return "Z";
      else if (q==Wild) return "*";
      else return "empty";
    }
    
    static String toPrettyString(int q) 
    {
      if (q==Diminished) return "Diminished";
      else if (q==Minor) return "Minor";
      else if (q==Major) return "Major";
      else if (q==Augmented) return "Augmented";
      else if (q==DimThirdMajThird)
        return "Diminished Third Major Third";
      else if (q==MajThirdDimThird) 
        return "Major Third Diminished Third";
      else return "empty";
    }
  };
  
  /** ChordIds: lower 4 bits type the triad and upper 4 bits type the
     seventh tone above the triad. Thus the upper nibble is 0 for all
     triads and greater than 0 for seventh chords. */

  class ChordIds
  {

  private:

    static const int SeventhBits = 4;

  public:

    static const ChordId Empty = 0;
    static const ChordId Unknown = Empty;
    static const ChordId DiminishedTriad = ChordQualities::Diminished;
    static const ChordId MinorTriad = ChordQualities::Minor;
    static const ChordId MajorTriad = ChordQualities::Major;
    static const ChordId AugmentedTriad = ChordQualities::Augmented;
    
    //(theoretical) triads for aug6 chords, eg: a# c e [g] and f# a# c [e]
    static const ChordId DimThirdMajThirdTriad = ChordQualities::DimThirdMajThird; 
    
    static const ChordId MajThirdDimThirdTriad = ChordQualities::MajThirdDimThird;
    
    static const ChordId MinThirdDimThirdTriad = ChordQualities::MinThirdDimThird;
    
    // seventh type, first word is triad, second is 7th
    static const ChordId DiminishedDiminishedSeventh = (ChordQualities::Diminished << SeventhBits) | DiminishedTriad;
    static const ChordId DiminishedSeventh = DiminishedDiminishedSeventh;

    static const ChordId DiminishedMinorSeventh = (ChordQualities::Minor << SeventhBits) | DiminishedTriad;
    static const ChordId HalfDiminishedSeventh = DiminishedMinorSeventh;

    static const ChordId MinorMinorSeventh = (ChordQualities::Minor << SeventhBits) | MinorTriad;
    static const ChordId MinorSeventh = MinorMinorSeventh;

    static const ChordId MinorMajorSeventh = (ChordQualities::Major << SeventhBits) | MinorTriad;

    static const ChordId MajorMinorSeventh = (ChordQualities::Minor << SeventhBits) | MajorTriad;
    static const ChordId DominantSeventh = MajorMinorSeventh;

    static const ChordId MajorMajorSeventh = (ChordQualities::Major << SeventhBits) | MajorTriad;
    static const ChordId MajorSeventh =   MajorMajorSeventh;

    static const ChordId AugmentedMajorSeventh = (ChordQualities::Major << SeventhBits) | AugmentedTriad;
    static const ChordId ItalianAugmentedSixth = DimThirdMajThirdTriad;
    static const ChordId GermanAugmentedSixth = (ChordQualities::Diminished << SeventhBits) | DimThirdMajThirdTriad;
    static const ChordId FrenchAugmentedSixth = (ChordQualities::Minor << SeventhBits) | MajThirdDimThirdTriad;
    static const ChordId SwissAugmentedSixth = (ChordQualities::Diminished << SeventhBits) | MinThirdDimThirdTriad;

    /** Returns true if the chord id is a seventh. **/

    static const bool isSeventh(ChordId id)
    {
      return ((id & 0xF0) > 0) && ((id & 0x0F) > 0);
    }

    /** Returns true if the chord id is a triad. **/

    static const bool isTriad(ChordId id)
    {
      return ((id & 0xF0) == 0) && ((id & 0x0F) > 0);
    }
    
  };

  /** chord members enumerate the possible chord notes. max is 4 bits. */

  class ChordMembers
  {

  public:

    static const ChordMember Empty =   0;
    static const ChordMember Root =    1 << 0;
    static const ChordMember Third =   1 << 1;
    static const ChordMember Fifth =   1 << 2;
    static const ChordMember Seventh = 1 << 3;
    static const ChordMember Wild = 0xF;

    static bool isMember(int val, ChordMember m)
    {
      return ((val && m) == m);
    }

    static String toString(ChordMember m)
    {
      switch(m)
      {
      case Root :
        return "1";
      case Third :
        return "3";
      case Fifth :
        return "5";
      case Seventh :
        return "7";
      case Wild :
        return "*";
      case Empty :
        return "empty";
      default :
        return "unknown";
      }
    }

    static String toPrettyString(ChordMember m)
    {
      switch (m)
      {
      case Root :
        return "root";
      case Third :
        return "third";
      case Fifth :
        return "fifth";
      case Seventh :
        return "seventh";
      case Wild :
        return "wild";
      case Empty :
        return "empty";
      default :
        return "unknown";
      }
    }
  };

  /** ChordInversions enumerate the possible triad and seventh chord inversions. */

  class ChordInversions
  {

  public:

    static const ChordInversion Empty = 0;
    static const ChordInversion RootPosition = 1;
    static const ChordInversion FirstInversion = 2;
    static const ChordInversion SecondInversion = 3;
    static const ChordInversion ThirdInversion = 4;
    static const ChordInversion Wild = 0xF;
    
    static String toString(ChordInversion inv)
    {
      if (inv==ChordInversions::RootPosition)
        return "0";
      else if (inv==ChordInversions::FirstInversion)
        return "1";
      else if (inv==ChordInversions::SecondInversion)
        return "2";
      else if (inv==ChordInversions::ThirdInversion)
        return "3";
      else if (inv==ChordInversions::Wild)
        return "*";
      else 
        return "Empty";
    }
  };


/** ChordType
    5432 1098 7654 3210     (16 bits)
    ---- ---- ---- -000     untyped          Triad nibble
    ---- ---- ---- -001     diminished triad  
    ---- ---- ---- -010     minor triad
    ---- ---- ---- -011     major triad   
    ---- ---- ---- -100     augmented triad
    ---- ---- ---- -101     aug6 triad
    ---- ---- -001 -nnn     diminished 7th   7th nibble
    ---- ---- -010 -nnn     minor 7th
    ---- ---- -010 -nnn     major 7th
    ---- ---- -100 -nnn     augmented 7th 
    ---- 0001 ---- ----     root position    Inversion nibble
    ---- 0010 ---- ----     1st inversion
    ---- 0011 ---- ----     2nd inversion
    ---- 0100 ---- ----     3rd inversion
    0001 ---- ---- ----     missing root     Incomplete nibble
    0010 ---- ---- ----     missing 3rd
    0100 ---- ---- ----     missing 5th
    1000 ---- ---- ----     missing 7th
**/

  class ChordType : public TypedBitfield<ChordTypeBitfield>
  {
    
  private:
    
    static const int i_AllFields = 0;
    static const int n_AllFields = 16;
    static const int i_Triad = 0;
    static const int n_Triad = 4;
    static const int i_Seventh = 4;
    static const int n_Seventh = 4;
    static const int i_Type = 0; //type = (seventh OR triad)
    static const int n_Type = 8;
    static const int i_Inversion = 8;
    static const int n_Inversion = 4;
    static const int i_Incomplete = 12;
    static const int n_Incomplete = 4;   
    
  public:
    
    ChordType()
    {
      type(ChordQualities::Empty);
      inversion(ChordInversions::Empty);
      incomplete(ChordMembers::Empty);
    }
    
    ChordType(ChordQuality typ, ChordInversion inv, ChordMember inc)
    {
      type(typ);
      inversion(inv);
      incomplete(inc);
    }

    ChordType(ChordQuality tri, ChordQuality sev, ChordInversion inv, ChordMember inc)
    {
      triad(tri);
      seventh(sev);
      inversion(inv);
      incomplete(inc);
    }
    
    ChordType(String text)
    {
      int len=text.length();
      int tri=0, sev=0, inv=0, mis=0, pos=0, num=len, omi=len;
      for (int i=0; i<len; i++) 
      {
        if (('0' <= text[i] ) && (text[i] <= '9')) 
        {
          if (num==len) num=i;
        }
        else if (text[i]=='~') omi=i;
      }
      pos=(num<omi) ? num : omi;
      //  std::cout << text << " len=" << len << " num=" << num << " omi=" << omi << std::endl;
      for (int i=0; i<pos; i++)
        switch ( text[i] ) 
        {
        case 'M':
          if (i==0) tri=ChordQualities::Major; 
          else sev=ChordQualities::Major; 
          break;
        case 'm':
          if (i==0) tri=ChordQualities::Minor; 
          else sev=ChordQualities::Minor; 
          break;
        case 'd':
          if (i==0) tri=ChordQualities::Diminished; 
          else sev=ChordQualities::Diminished; 
          break;
        case 'A':
          if (i==0) tri=ChordQualities::Augmented; 
          else sev=ChordQualities::Augmented; 
          break;
        case 'z':
          if (i==0) tri=ChordQualities::DimThirdMajThird; 
          break;
        case 'Z':
          if (i==0) tri=ChordQualities::MajThirdDimThird; 
          break;
        default:
          break;
        }
      //  std::cout << "tri=" << tri << " sev=" << sev << std::endl;
      if (num<omi) 
      {
        if (num<omi-1) 
        {
          if (text[num]=='6' && text[num+1]=='3')
            inv=ChordInversions::FirstInversion;
          if (text[num]=='6' && text[num+1]=='5')
            inv=ChordInversions::FirstInversion;
          else if (text[num]=='6' && text[num+1]=='4')
            inv=ChordInversions::SecondInversion;
          else if (text[num]=='4' && text[num+1]=='3')
            inv=ChordInversions::SecondInversion;
          else if (text[num]=='4' && text[num+1]=='2')
            inv=ChordInversions::ThirdInversion;
        }
        else if (text[num]=='6') 
          inv=ChordInversions::FirstInversion;
      } 
      
      for (int i=omi+1;i<len;i++) 
      {
        if (text[i]=='1') mis |= ChordMembers::Root;
        else if (text[i]=='3') mis |= ChordMembers::Third;
        else if (text[i]=='5') mis |= ChordMembers::Fifth;
        else if (text[i]=='7') mis |= ChordMembers::Seventh;
      }
      triad(tri);
      seventh(sev);
      inversion(inv);
      incomplete(mis);
    }
    
    ~ChordType()
    {
    }
    
    ChordQuality triad()
    {
      return read(i_Triad, n_Triad);
    }
    
    void triad(ChordQuality val)
    {
      return write(i_Triad, n_Triad, val);
    }
    
    ChordQuality seventh()
    {
      return read(i_Seventh, n_Seventh);
    }
    
    void seventh(ChordQuality val)
    {
      return write(i_Seventh, n_Seventh, val);
    }
    
    ChordQuality type()
    {
      return read(i_Type, n_Type);
    }

    void type(ChordQuality val)
    {
      return write(i_Type, n_Type, val);
    }
    
    ChordInversion inversion()
    {
      return read(i_Inversion, n_Inversion);
    }
    
    void inversion(ChordInversion val)
    {
      return write(i_Inversion, n_Inversion,val);
    }

    ChordMember incomplete()
    {
      return read(i_Incomplete, n_Incomplete);
    }

    void incomplete(ChordMember val)
    {
      return write(i_Incomplete, n_Incomplete,val);
    }

    int allFields()
    {
      return read(i_AllFields, n_AllFields);
    }
    
    /** true is chord is not determined **/

    bool isEmpty()
    {
      return ((type() == ChordQualities::Empty) &&
              (inversion() == ChordInversions::Empty) &&
              (incomplete() == ChordMembers::Empty));
    }

    /** true is chord is determined **/

    bool isChord()
    {
      return (type() != ChordQualities::Empty);
    }

    /** true if chord is identical to other including inversions and
        missing members **/

    bool isSame(ChordType other)
    {
      return (allFields() == other.allFields());
    }

    /** true if chord is the same type of chord (triad or seventh) as
        other without regard to inversion or missing members **/

    bool isSameType(ChordType other)
    {
      return (type() == other.type());
    }
    
    bool isTriad()
    {
      return ((triad() != ChordQualities::Empty) &&
              (seventh() == ChordQualities::Empty));
    }
    
    bool isSeventh()
    {
      return ((triad() != ChordQualities::Empty) &&
              (seventh() != ChordQualities::Empty));
    }
    
    bool isInversion(ChordInversion inv)
    {
      // test if chord is in inversion inv
      return (inversion() == inv);
    }

    bool isInverted()
    {
      // true if not in root position
      return (inversion() > ChordInversions::RootPosition);
    }

    /** Returns true if triad or seventh is in root position. **/
    bool isRootPosition()
    {
      return (inversion() == ChordInversions::RootPosition);
    }
    
    /** Returns true if triad or seventh is in first inversion. **/
    bool isFirstInversion()
    {
      return (inversion() == ChordInversions::FirstInversion);
    }
    
    /** Returns true if triad or seventh is in second inversion. **/
    bool isSecondInversion()
    {
      return (inversion() == ChordInversions::SecondInversion);
    }
    
    /** Returns true if seventh is in third inversion. **/
    bool isThirdInversion()
    {
      return (inversion() == ChordInversions::ThirdInversion);
    }
    
    /** Predicates for testing wild card components */

    bool isWildTriad()
    {
      return (triad()==ChordQualities::Wild);
    }

    bool isWildSeventh()
    {
      return (seventh()==ChordQualities::Wild);
    }

    bool isWildInversion()
    {
      return (inversion()==ChordInversions::Wild);
    }

    bool isWildType()
    {
      return (isWildTriad() && isWildSeventh());
    }

    bool isFullyWild()
    {
      return (isWildTriad() && isWildSeventh() && isWildInversion());
    }

    /** return version in root position info **/
    
    ChordType makeRootPosition()
    {
      // return type with inversion info stripped off.
      return ChordType(type(), ChordInversions::RootPosition, incomplete());
    }
    
    ChordType makeBasic()
    {
      return ChordType(type(), ChordInversions::RootPosition, ChordMembers::Empty);
    }
    
    bool isMissing(ChordMember mem)
    {
      // test if chord is missing members
      //return (incomplete() == mem);
      return ((incomplete() & mem) == mem);
    }
    
    bool isIncomplete()
    {
      // true if chord is missing any members
      return (incomplete() != ChordMembers::Empty);
    }
    
    bool isComplete()
    {
      // true if chord not missing any members
      return (incomplete() == ChordMembers::Empty);
    }
    
    /** return version missing member info **/
    
    ChordType makeComplete()
    {
      // return type with complete members
      return ChordType(type(), inversion(), ChordMembers::Empty);
    }

    /** return version without inversion and missing member info **/
    
    bool isMajor()
    {
      // true if chord is based on major triad
      return (triad() == ChordIds::MajorTriad);
    }
    
    bool isMinor()
    {
      /// true if chord is based on minor triad
      return (triad() == ChordIds::MinorTriad);
    }
    
    bool isDiminished()
    {
      /// true if chord is based on diminished triad
      return (triad() == ChordIds::DiminishedTriad);
    }
    
    bool isAugmented()
    {
      /// true if chord is based on augmented triad
      return (triad() == ChordIds::AugmentedTriad);
    }
    
    bool isMajorTriad()
    {
      /// true if chord is strictly a Major triad
      return (type() == ChordIds::MajorTriad);
    }
    
    bool isMinorTriad()
    {
      /// true if chord is strictly a Minor triad
      return (type() == ChordIds::MinorTriad);
    }
    
    bool isDiminishedTriad()
    {
      /// true if chord is strictly a Diminished triad
      return (type() == ChordIds::DiminishedTriad);
    }
    
    bool isAugmentedTriad()
    {
      /// true if chord is strictly an Augmented triad
      return (type() == ChordIds::AugmentedTriad);
    }
    
    bool isDiminishedSeventh()
    {
      /// true if chord is strictly a Diminished seventh
      return (type() == ChordIds::DiminishedSeventh);
    }
    
    bool isHalfDiminishedSeventh()
    {
      /// true if chord is strictly an Half-Diminished seventh
      return (type() == ChordIds::HalfDiminishedSeventh);
    }
    
    bool isMinorSeventh()
    {
      /// true if chord is strictly a Minor seventh
      return (type() == ChordIds::MinorSeventh);
    }
    
    bool isDominantSeventh()
    {
      /// true if chord is strictly a Dominant seventh
      return (type() == ChordIds::DominantSeventh);
    }
    
    bool isMajorSeventh()
    {
      /// true if chord is strictly a Major seventh
      return (type() == ChordIds::MajorSeventh);
    }
    
    bool isAugmentedSixth(ChordId subtype=ChordIds::Empty)
    {
      /// true if chord is an AugmentedSixth or one a 
      int typ=type();
      if (subtype==ChordIds::Empty)
        return ((typ == ChordIds::ItalianAugmentedSixth) ||
                (typ == ChordIds::GermanAugmentedSixth) ||
                (typ == ChordIds::FrenchAugmentedSixth) ||
                (typ == ChordIds::SwissAugmentedSixth)
                );
      else
        return (typ == subtype);
    }
    
    bool isConsonant()
    {
      return (isMajorTriad() || isMinorTriad());
    }

    bool isDissonant()
    {
      return (! isConsonant() );
    }

    // Warning: these two functions are from the lisp code and
    // should be rethought or combined.

    bool isAmbiguous()
    {
      if (isMissing(ChordMembers::Third)) 
      {
        if ( isMajorTriad() ) return true;
        if ( isMajorSeventh()) return true;
        if ( isDominantSeventh() ) return true;
      }
      return false;
    }
    
    bool isFuzzySeventh()
    {
      if (isSeventh()) 
      {
        if ((isMissing(ChordMembers::Third) ||
             isMissing(ChordMembers::Fifth))
            &&
            // this too inclusive as it finds things like
            // dm42~3 and Mm~5
            //	 ( (seventh() == ChordQualities::Major) ||
            //	   (seventh() == ChordQualities::Minor)))
            // This is what the lisp code does:
            (isMajorSeventh() || isMinorSeventh())
            )
          return true;
        else
          return false;
      }
      return false;
    }

    bool isSimplerThan(ChordType other)
    {
      // true if this is simpler than other, where (1) complete chords are
      // simpler than incomplete (2) triads are simpler than sevenths (3)
      // root position is simpler than inversion.
      // warning, 
      if ( isTriad() ) 
      {
        if ( isComplete() )
        {
          if ( (! other.isTriad()) ||
               other.isIncomplete() ||
               other.inversion() > inversion() )
            return true;
          else 
            return false;
        }
        else
          return false; 
      }
      else if ( isSeventh() )
      {
        if ( isComplete() )
        {
          if ( other.isSeventh() && 
               other.isIncomplete() )
            return true;
          else
            return false;
        }
        else
          return false;
      }
      else 
        return false;
    }
    
    ChordType simplest(ChordType other)
    {
      // return this or other, whichever is simpler
      //  if ( isSimplerThan(other) ) return *this;
      //  return other;
      if ( isSimplerThan(other) )
      {
        if (other.isSimplerThan(*this)) 
          return ChordType();
        else
          return *this;
      }  
      else if ( other.isSimplerThan(*this) )
        return other;
      else
        return ChordType();
    }
    
    /** wildcard match of chordtype to other, where Empty field(s) in
        other are always true wrt corresponding field in chordtype **/
    
    bool match(ChordType tok)
    {
      bool t,i;
      if (tok.type()==ChordQualities::Empty)
        t=true;
      else
        t=(tok.type()==type());
      if (tok.inversion()==ChordInversions::Empty)
        i=true;
      else
        i=(tok.inversion()==inversion());
      return (t && i);
    }
    
    String toString()
    {
      String str;
      int tri=isTriad();
      if (tri) 
      {
        str = ChordQualities::toString( triad() ) ;
      }
      else if (isSeventh()) 
      {
        str = ChordQualities::toString( triad() ) ;
        str += ChordQualities::toString( seventh() );
      }
      else
        return "empty";
      
      int inv=inversion();
      if (inv==ChordInversions::FirstInversion)
        str += ((tri) ? "6" : "65" );
      else if (inv==ChordInversions::SecondInversion)
        str += ((tri) ? "64" : "43" );
      else if (inv==ChordInversions::ThirdInversion)
        str += "42";
      int inc=incomplete();
      if (inc>0) 
      {
        str += "~";
        if ((inc & 1)==1) str += "1";
        if ((inc & 2)==2) str += "3";
        if ((inc & 4)==4) str += "5";
        if ((inc & 8)==8) str += "7";
      }
      return str;
    }
    
    String toTypeString()
    {
      String str;
      if (isTriad())
      {
        str = ChordQualities::toPrettyString( triad() ).toLowerCase();
        str += " triad";
      }
      else if ( isSeventh() )
      {
        switch (type())
        {
        case ChordIds::DiminishedSeventh:
        case ChordIds::MajorSeventh:
        case ChordIds::MinorSeventh:
          str = ChordQualities::toPrettyString(triad()).toLowerCase();
          str += " seventh";
          break;
        case ChordIds::HalfDiminishedSeventh:
          str = "half-diminished seventh";
          break;
        case ChordIds::GermanAugmentedSixth:
        case ChordIds::FrenchAugmentedSixth:
          str = "augmented sixth";
          break;
        default:
          str = ChordQualities::toPrettyString(triad()).toLowerCase();
          str += "/";
          str += ChordQualities::toPrettyString(seventh()).toLowerCase();
          str += " seventh";
          break;
        }
      }
      return str;
    }
    
    String toInversionString()
    {
      if (isAugmentedSixth())
        return "";
      else if (isTriad())
      {
        if (isInversion(ChordInversions::FirstInversion))
          return "6";
        else if (isInversion(ChordInversions::SecondInversion))
          return "64";
        else if (isInversion(ChordInversions::Wild))
          return "*";
        else
          return "";
      }
      else if (isSeventh())
      {
        if (isInversion(ChordInversions::RootPosition))
          return "7";
        else if (isInversion(ChordInversions::FirstInversion))
          return "65";
        else if (isInversion(ChordInversions::SecondInversion))
          return "43";
        else if (isInversion(ChordInversions::ThirdInversion))
          return "42";
        else if (isInversion(ChordInversions::Wild))
          return "7*";
        else
          return "";
      } 
      return "";
    }
    
    String toRomanNumeralString(ScaleDegree deg)
    {
      String text;
      switch (deg)
      {
      case ScaleDegrees::LoweredTonic:
      case ScaleDegrees::Tonic: 
      case ScaleDegrees::RaisedTonic:
        text="I";
        break;
      case ScaleDegrees::LoweredSupertonic: 
        text="N";
        break;
      case ScaleDegrees::Supertonic: 
        if (isAugmentedSixth(ChordIds::FrenchAugmentedSixth))
          text="Fr";
        else
          text="II";
        break;
      case ScaleDegrees::RaisedSupertonic: 
        if (isAugmentedSixth(ChordIds::SwissAugmentedSixth))
          text="Sw";
        else
          text="II";
        break;
      case ScaleDegrees::LoweredMediant: 
      case ScaleDegrees::Mediant: 
      case ScaleDegrees::RaisedMediant: 
        text="III";
        break;
      case ScaleDegrees::LoweredSubdominant: 
      case ScaleDegrees::Subdominant: 
        text="IV";
      case ScaleDegrees::RaisedSubdominant:
        if (isAugmentedSixth(ChordIds::ItalianAugmentedSixth))
          text="It";
        else if (isAugmentedSixth(ChordIds::GermanAugmentedSixth))
          text="Ger";
        else
          text="IV";
        break;
      case ScaleDegrees::LoweredDominant:
      case ScaleDegrees::Dominant:
      case ScaleDegrees::RaisedDominant:
        text="V";
        break;
      case ScaleDegrees::LoweredSubmediant:
      case ScaleDegrees::Submediant: 
      case ScaleDegrees::RaisedSubmediant:
        text="VI";
        break;
      case ScaleDegrees::LoweredLeadingTone: 
      case ScaleDegrees::LeadingTone: 
      case ScaleDegrees::RaisedLeadingTone: 
        text="VII";
        break;
      }
      
      if (isMinor())
        text=text.toLowerCase();
      else if (isDiminished())
      {
        text=text.toLowerCase();
        text += "o";
      }
      else if (isHalfDiminishedSeventh())
      {
        text=text.toLowerCase();
        text += "/o";
      }
      else if (isAugmented())
      {
        String tmp (text);
        text="+";
        text += tmp;
      }
      else if (isWildTriad())
      {
        text="*";
      }
      text += toInversionString();
      return text;
    }
    
    String toMissingString()
    {
      String str;
      int inc=incomplete();
      if (inc>0)
      {
        str +=  "without a ";
        String tmp;
        if ((inc & 1)==1) tmp ="root";
        if ((inc & 2)==2)
        {
          if (tmp.length()>0) 
            tmp += " and ";
          tmp += "third";
        }
        if ((inc & 4)==4)
        {
          if (tmp.length()>0)
            tmp += " and ";
          tmp += "fifth";
        }
        if ((inc & 8)==8)
        {
          if (tmp.length()>0)
            tmp += " and ";
          tmp += "seventh";
        }
        str += tmp;
      }
      return str;
    }
    
    String toPrettyString()
    {
      String text=toTypeString();
      text += " in ";
      text += toInversionString();
      if (isIncomplete())
      {
        text += " ";
        text += toMissingString();
      }
      return text;
    }

    /** Convert chord type into a chord (array of notes) built on the
        specified bass note. **/

    void toChord(Array<Note>& notes, Note bass)
    {
      switch (type())
      {
      case ChordIds::ItalianAugmentedSixth:
        notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
        notes.add(Interval::transpose(bass, IntervalTypes::AugmentedSixth));
        break;
      case ChordIds::GermanAugmentedSixth:
        notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
        notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
        notes.add(Interval::transpose(bass, IntervalTypes::AugmentedSixth));
        break;
      case ChordIds::FrenchAugmentedSixth:
        notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
        notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFourth));
        notes.add(Interval::transpose(bass, IntervalTypes::AugmentedSixth));
        break;
      case ChordIds::SwissAugmentedSixth:
        notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
        notes.add(Interval::transpose(bass, IntervalTypes::fromQualityAndDistance(IntervalQualities::DoublyAugmented, IntervalDistances::Fourth)));
        notes.add(Interval::transpose(bass, IntervalTypes::AugmentedSixth));
        break;
      case ChordIds::DiminishedSeventh:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedSeventh));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::ThirdInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedSecond));
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        default:
          return;
        }  
        break;
      case ChordIds::HalfDiminishedSeventh:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSeventh));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::ThirdInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSecond));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        default:
          return;
        }  
        break;
      case ChordIds::MinorSeventh:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSeventh));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::ThirdInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSecond));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        default:
          return;
        }  
        break;
      case ChordIds::MinorMajorSeventh:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSeventh));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::ThirdInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSecond));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        default:
          return;
        }  
        break;
      case ChordIds::DominantSeventh:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSeventh));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::ThirdInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSecond));
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        default:
          return;
        }  
        break;
      case ChordIds::MajorSeventh:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSeventh));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::ThirdInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSecond));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        default:
          return;
        }  
        break;
      case ChordIds::AugmentedMajorSeventh:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSeventh));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::ThirdInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSecond));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        default:
          return;
        }  
        break;
      case ChordIds::DiminishedTriad:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFifth));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        default:
          return;
        }
        break;
      case ChordIds::MinorTriad:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        default:
          return;
        }
        break;
      case ChordIds::MajorTriad:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFifth));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MinorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::PerfectFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MajorSixth));
          break;
        default:
          return;
        }
        break;
      case ChordIds::AugmentedTriad:
        switch (inversion())
        {
        case ChordInversions::RootPosition:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::AugmentedFifth));
          break;
        case ChordInversions::FirstInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::MajorThird));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        case ChordInversions::SecondInversion:
          notes.add(Interval::transpose(bass, IntervalTypes::DiminishedFourth));
          notes.add(Interval::transpose(bass, IntervalTypes::MinorSixth));
          break;
        default:
          return;
        }
        break;
      default:
        return;
      }
      notes.insert(0,bass);
    }

  };
}

#endif
