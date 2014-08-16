/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencStaffs_h
#define mencStaffs_h

#include "mencTypes.h"

namespace menc
{
  
  class FiveLineStaff
  {
  public:
    static const LineSpace TopLine=4;
    static const LineSpace LineBelowTopLine=3;
    static const LineSpace LineAboveMiddleLine=2;
    static const LineSpace SpaceAboveMiddleLine=1;
    static const LineSpace MiddleLine=0;
    static const LineSpace SpaceBelowMiddleLine=-1;
    static const LineSpace LineBelowMiddleLine=-2;
    static const LineSpace SpaceAboveBottomLine=-3;
    static const LineSpace BottomLine=-4;
  };
  
}

#endif
