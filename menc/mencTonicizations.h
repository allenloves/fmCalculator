/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencTonicizations_h
#define mencTonicizations_h

#include "mencTypes.h"

namespace menc
{
  
  /** An enumeration of the different types of tonicizations */

  class Tonicizations
  {

  public:

    static const Tonicization Empty = 0;
    static const Tonicization Direct = 1;
    static const Tonicization Secondary = 2;
    static const Tonicization Pivot = 4;

  };
  
}

#endif
