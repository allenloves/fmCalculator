/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencBitfields_h
#define mencBitfields_h

#include "mencTypes.h"
#include "mencString.h"

namespace menc
{
  template <class Size>
  class Bitfield
  {
  private: 
    //Derived classes should not have to know about the internal representation
    Size bits;

  protected:
    inline void write(Size bit_index, Size bits_to_take, Size value)
    {
      uint32 masks[33] = {0, //0
        1,3,7,15,31,63,127,255, //1-8
        511,1023,2047,4095,8191,16383,32767,65535, //9-16
        131071,262143,524287,1048575,2097151,4194303,8388607,16777215, //17-24
        33554431,67108863,134217727,268435455,536870911,1073741823,2147483647,
          0xFFFFFFFF}; //25-31

      //Operator Key
      // |   Inclusive OR
      // ^   Exclusive OR (T + T = F)
      // &   AND
      // <<  Shift bits UP by some number
      // >>  Shift bits DOWN by some number

      //WRITE Algorithm
      //Efficiency: 2 OR, 2 AND, 1 BITSHIFT = 5 bitwise operations
      bits = 
      ( //1-out anything in the mask area and leave the rest untouched, 
        //i.e. rrrrrrr11rrr
        bits 

        |

        (
        (Size)masks[bits_to_take] << bit_index  //COMPILER OPTIMIZED CONSTANT
        )
      )

      &  

      ( //i.e. 111111vv111, where v is an arbitrary data value
        (
          ( //Prevent overflow errors by masking bits higher than the range
            (Size)value 
            & 
            (Size)masks[bits_to_take] //COMPILER OPTIMIZED CONSTANT
          )
          <<
          bit_index
        )

        | 

        ( //The following creates an 'inverse' of the transposed mask, 
          //i.e. 11111100111
          (Size)masks[sizeof(Size)<<3] 
          ^
          (
            (Size)masks[bits_to_take] << bit_index
          )
        ) //COMPILER OPTIMIZED CONSTANT
      );
    }

    inline Size read(Size bit_index=0, Size bits_to_take=32) const
    {
      uint32 masks[33] = {0, //0
        1,3,7,15,31,63,127,255, //1-8
        511,1023,2047,4095,8191,16383,32767,65535, //9-16
        131071,262143,524287,1048575,2097151,4194303,8388607,16777215, //17-24
        33554431,67108863,134217727,268435455,536870911,1073741823,2147483647,
          0xFFFFFFFF}; //25-31

      //Operator Key
      // |   Inclusive OR
      // ^   Exclusive OR (T + T = F)
      // &   AND
      // <<  Shift bits UP by some number
      // >>  Shift bits DOWN by some number

      //READ Algorithm
      //Efficiency: 1 BITSHIFT, 1 AND = 2 bitwise operations
      return (bits >> bit_index) & (Size)masks[bits_to_take];
    }

    inline bool readBool(Size bit_index) const
    {
      return (read(bit_index,1)==1);
    }

    inline void writeBool(Size bit_index, bool boolValue)
    {
      if(boolValue)
        write(bit_index,1,1);
      else
        write(bit_index,1,0);
    }

    inline int readSignedInteger(Size bit_index, Size total_bits) const
    {
      if(readBool(bit_index+total_bits-1))
        return -((int)read(bit_index,total_bits-1));
      else
        return read(bit_index,total_bits-1);
    }

    inline void writeSignedInteger(Size bit_index, Size total_bits, int value)
    {
      if(value<0)
      {
        writeBool(bit_index+total_bits-1,true);
        write(bit_index,total_bits-1,(Size)(-value));
      }
      else
      {
        writeBool(bit_index+total_bits-1,false);
        write(bit_index,total_bits-1,(Size)value);
      }
    }

  public:
    Bitfield(){bits=0;}
    ~Bitfield(){bits=0;}

    bool operator==(Bitfield<Size> otherBitfield) const
    {
      return (bits==otherBitfield.bits);
    }

    bool operator!=(Bitfield<Size> otherBitfield) const
    {
      return (bits!=otherBitfield.bits);
    }
  };

  //////////////////////////
  //Bitfield Type Template//
  //////////////////////////

  typedef int32 BitfieldType;

  template <BitfieldType TemplateType>
  class TypedBitfield : public Bitfield<uint32>
  {
  protected:
    static const BitfieldType Type = TemplateType;
  public:
    TypedBitfield(void)
    {
      write(24,8,TemplateType); //Set upper 24 bits to the new type.
      writeBool(23,true); //Assume that the bitfield is valid to begin with.
    }

    BitfieldType readType(void) const
    {
      return read(24,8);
    }

    bool valid(void) const
    {
      return (read(23,1)==1);
    }

    void valid(bool isValid)
    {
      if(isValid)
        writeBool(23,true);
      else
        write(0,24,0); //This erases all of the information except the type.
    }

    String toBitfieldString(void) const
    {
      String bits_string = "";
      bits_string += " ------------------------\n";
      bits_string += " BIT #:    11111111112222\n";
      bits_string += " 012345678901234567890123\n";
      bits_string += " ------------------------\n";
      bits_string += "[";
      for (int i=0; i<23; i++)
      {
        if (readBool(i))
          bits_string += "1";
        else
          bits_string += "0";
      }
      if (readBool(23))
        bits_string += "V";
      else
        bits_string += "X";
      bits_string += " | ";
      bits_string += readType();
      bits_string += "]";
      return bits_string;
    }
  };
}

#endif
