/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
  *=======================================================================*/

#ifndef mencBarlines_h
#define mencBarlines_h

#include "mencTypes.h"

namespace menc
{
  
   /** Barlines encode line style and repeat information:

          76543210 76543210
          -------- llllllll    l=line style  
          ttttrrrr --------    r=repeat, t=times
  **/
   
  class Barlines
  {

  public:
    static const int Empty = 0;

    /// Line styles
    static const int Regular = 1;
    static const int Dotted = 2;
    static const int Dashed = 3;
    static const int Heavy = 4;
    static const int LightLight = 5;
    static const int LightHeavy = 6;
    static const int HeavyLight = 7;
    static const int HeavyHeavy = 8;
    static const int LightHeavyLight = 9; //(for repeat both sides)
    static const int Tick = 10;
    static const int Short = 11;
    static const int Invisible = 12;

    /// Repeat sign attached on right, left or both sides
    static const int RepeatRight  =  0x100;
    static const int RepeatLeft   =  0x200;
    static const int RepeatBoth   =  RepeatRight+RepeatLeft;

    /// Definitions of common barline 

    static const Barline Bar=Regular;
    static const Barline DoubleBar=LightHeavy;
    static const Barline InteriorDoubleBar=LightLight;
    static const Barline BeginRepeatBar=HeavyLight + RepeatRight;
    static const Barline EndRepeatBar=LightHeavy + RepeatLeft;
    static const Barline InteriorRepeatBar=LightHeavyLight + RepeatBoth;
    static const Barline InvisibleBar=Invisible;

    /** Returns a (non-repeating) barline given a style. **/

    static Barline fromLine(int line)
    {
      if (line<Regular || line>Invisible)
        return Empty;
      return (Barline)line;
    }

    /** Returns a repeating barline given a style, repeat and times
        value, which defaults to 1 repetition. **/

    static Barline fromLineAndRepeat(int line, int repeat, int times=1)
    {
      if (repeat==Empty)
        return fromLine(line);
      if (line<Regular || line>Invisible)
        return (Barline)Empty;
      if (repeat<RepeatRight || repeat>RepeatBoth)
        return (Barline)Empty;
      // we have a repeating barline so times must be > 0
      if (times<1 || times>15)
        return (Barline)Empty;
      return (Barline)((times<<12) & repeat & line);
    }

    /** Returns the line style of the barline. **/

    static int line(Barline bline)
    {
      return (bline & 0x00FF);
    }

    /** Returns the repeat style of the barline. **/

    static int repeat(Barline bline)
    {
      return (bline & 0x0F00);
    }

    /** Strips off any times factor and returns just the line and
        repeat portions of a barline. **/

    static int barline(Barline bline)
    {
      return bline & 0x0FFF;
    }

    /** Return the number of times a repeating barline repeats. This
        will be zero for non-repeating barlines. **/

    static int times(Barline bline)
    {
      return (bline & 0xF000) >> 12;
    }

    /** Returns true if barline is a repeating barline else false. **/

    static bool isRepeat(Barline bline)
    {
      int rep=repeat(bline);
      return (rep<RepeatRight || rep>RepeatBoth) ? false : true;
    }

    /** Returns a barline from its string representation. **/

    static Barline fromString(String str)
    {
      if (str.equalsIgnoreCase("bar")) return Bar;
      if (str.equalsIgnoreCase("double-bar")) return DoubleBar;
      if (str.equalsIgnoreCase("interior-double-bar")) return InteriorDoubleBar;
      if (str.equalsIgnoreCase("begin-repeat-bar")) return BeginRepeatBar;
      if (str.equalsIgnoreCase("end-repeat-bar")) return EndRepeatBar;
      if (str.equalsIgnoreCase("interior-repeat-bar")) return InteriorRepeatBar;
      if (str.equalsIgnoreCase("invisible-bar")) return InvisibleBar;
      // mxml names
      if (str.equalsIgnoreCase("regular")) return fromLine(Regular); // same as bar
      if (str.equalsIgnoreCase("dotted")) return fromLine(Dotted);
      if (str.equalsIgnoreCase("dashed")) return fromLine(Dashed);
      if (str.equalsIgnoreCase("heavy")) return fromLine(Heavy);
      if (str.equalsIgnoreCase("light-light")) return fromLine(LightLight); // same as interior-double-bar
      if (str.equalsIgnoreCase("light-heavy")) return fromLine(LightHeavy); // same as double-bar
      if (str.equalsIgnoreCase("heavy-light")) return fromLine(HeavyLight);
      if (str.equalsIgnoreCase("heavy-heavy")) return fromLine(HeavyHeavy);
      if (str.equalsIgnoreCase("light-heavy-light")) return fromLine(LightHeavyLight);
      if (str.equalsIgnoreCase("tick")) return fromLine(Tick);
      if (str.equalsIgnoreCase("short")) return fromLine(Short);
      if (str.equalsIgnoreCase("none")) return fromLine(Invisible); // same as invisible-bar
      return Empty;
    }

    /** Returns the string representation of a barline. This does not
        handle xml names or a times factor yet! **/

    static String toString(Barline bline)
    {
      switch (barline(bline))
      {
      case Bar: return "bar"; // same as Regular       
      case DoubleBar: return "double-bar"; // same as LightHeavy
      case InteriorDoubleBar: return "interior-double-bar"; // same as LightLight
      case InvisibleBar: return "invisible-bar";
      case BeginRepeatBar: return "begin-repeat-bar";
      case EndRepeatBar: return "end-repeat-bar";
      case InteriorRepeatBar: return "interior-repeat-bar";
        //      case Regular:  return "regular";  // same as Bar
      case Dotted: return "dotted";
      case Dashed: return "dashed";
      case Heavy: return "heavy";
        //      case LightLight: return "light-light"; // same as InteriorDoubleBar
        //      case LightHeavy: return "light-heave"; // same as DoubleBar
      case HeavyLight: return "heavy-light";
      case HeavyHeavy: return "heavy-heavy";
      case Tick: return "tick";
      case Short: return "short";
      default: return "";
      }
    }

  };

}

#endif
