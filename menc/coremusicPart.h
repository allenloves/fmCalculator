/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef coremusic_Part_h
#define coremusic_Part_h

#include "menc.h"

namespace menc
{

  /** A part contains a list of score data. **/

  class Part 
  {

  private:

    /** A unique identifier for the part in the score. **/

    int id; 

    /** The name of the part in the score. **/

    menc::String name;

    /** The playback instrument of the part. **/

    menc::Instrument inst;

    /** The array of score data. **/

    Array<ScoreData*> scoredata;
    
  public:
    
    /** Part constructor. partId is the unique identifier of the part
        in the score.  **/

    Part(int partId, menc::String partName="", menc::Instrument partInst=menc::Instruments::Empty)
      : id (partId),
        name (partName),
        inst (partInst)
    {
    }

    /** Part constructor with array of scoredata. Once elements are added
        they are owned by the part and should not be deleted! **/

    Part(int partId, Array<ScoreData*>& data, menc::String partName="", menc::Instrument partInst=menc::Instruments::Empty)
      : id (partId),
        name (partName),
        inst (partInst)
    {
      //      std::cout << "partname=" << name << ", partinst=" << inst << "\n";
      // FIXME: menc array copy?
      for (int i=0; i<data.size(); i++)
        scoredata.add(data.getUnchecked(i));
    }
      /** Part destructor.**/

    ~Part()
    {
      scoredata.clearWithDelete();
    }
    
    /** Returns the unique identifier of the part in the score. **/

    int getId()
    {
      return id;
    }

    /** Returns the name of the part in the score. **/

    menc::String getName()
    {
      return name;
    }

    /** Sets the name of the part in the score. **/

    void setName(menc::String partName)
    {
      name=partName;
    }

    /** Returns the playback instrument of the part. **/

    menc::Instrument getInstrument()
    {
      return inst;
    }

    /** Sets the playback instrument of the part. **/

    void setInstrument(menc::Instrument partInst)
    {
      inst=partInst;
    }
    /** Returns the number of score data in the part. **/

    int numScoreData()
    {
      return scoredata.size();
    }

    /** Returns a pointer to the score data stored at index. **/

    ScoreData* getScoreData(int index)
    {
      return scoredata.getUnchecked(index);
    }

    /** Removes the score data at index. If delete is true then the
        object is deleted after it is removed from the part. **/

    void removeScoreData(int index, bool del=false)
    {
      menc::ScoreData* d=NULL;
      if (del) d=scoredata[index];
      scoredata.remove(index);
      if (del && d) delete d;
    }

    /** Return a pointer to the note data stored at index or null if
        the data is not a note. **/

    NoteData* getNoteData(int index)
    {
      ScoreData* d=scoredata[index];
      NoteData* x=dynamic_cast<NoteData*> (d);
      return x;
    }

    /** Append score data to the part's array of score data. **/

    void addScoreData(ScoreData* e)
    {
      scoredata.add(e);
    }

  };

}

#endif

