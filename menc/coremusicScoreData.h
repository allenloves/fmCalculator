/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef coremusic_ScoreData_h
#define coremusic_ScoreData_h

#include "menc.h"

namespace menc
{

  /*=====================================================================*
    ScoreData
   *=====================================================================*/

  /** A base class for objects that hold menc score data to be
      analyzed or displayed. **/

  class ScoreData
  {
     
  public:
    
    virtual ~ScoreData() {};

    /** Impelemeted by subclasses to return a string reprentation of
        their data. **/

    virtual menc::String toString() = 0;

    /** Returns the time duration of the data, defaults to 0.
        Subclasses that manage their own durations can override this
        function. **/

    virtual menc::Ratio getDuration()
    {
      return menc::Ratio(0);
    }

  }; 

  /*=====================================================================*
    NoteData
   *=====================================================================*/

  /** NoteData holds data for objects with pitch (including Rest) and
      duration. **/

  class NoteData : public ScoreData
  {

  private:

    Ratio beat; 
    Ratio duration; 
    Note note; 
    Array<Mark> marks;
    Array<Beam> beams;
    Array<Slur> slurs;
    bool chord;

  public:
    
    NoteData(NoteData& other)
    {
      beat = other.beat;
      duration = other.duration;
      note = other.note;
      marks.n(other.marks.n());
      beams.n(other.beams.n());
      slurs.n(other.slurs.n());
      for(int i = 0; i < marks.n(); i++) marks[i] = other.marks[i];
      for(int i = 0; i < beams.n(); i++) beams[i] = other.beams[i];
      for(int i = 0; i < slurs.n(); i++) slurs[i] = other.slurs[i];
      chord = other.chord;
    }
    
    NoteData(Ratio b=0, Ratio d=0, Note n=-1)
      : beat(b), duration(d), note(n), chord(false)
    {
    }
    
    NoteData(Ratio b, Ratio d, Note n, 
             Array<Mark>& markdata, Array<Beam>& beamdata, Array<Slur>& slurdata)
      : beat(b), duration(d), note(n), chord(false)
    {
      // FIXME: TEST AND USE MENC ARRAY COPY
      for (int i=0; i<markdata.size(); i++)
        marks.add(markdata.getUnchecked(i));
      for (int i=0; i<beamdata.size(); i++)
        beams.add(beamdata.getUnchecked(i));
      for (int i=0; i<slurdata.size(); i++)
        slurs.add(slurdata.getUnchecked(i));
    }

    ~NoteData() 
    {
      marks.clear();
      beams.clear();
      slurs.clear();
    }
    
    void setBeat(Ratio b)
    {
      beat = b;
    }
    
    menc::Ratio getBeat()
    {
      return beat;
    }

    /** Returns the duration of the event in the score. **/

    Ratio getDuration()
    {
      return duration;
    }
    
    /** Sets the duration of the event in the score. **/

    void setDuration(Ratio d)
    {
      duration=d;
    }
    
   /** Returns the Note of the event. **/
    
    Note getNote()
    {
      return note;
    }
    
    void setNote(Note n)
    {
      note=n;
    }

    bool isRest()
    {
      return note.isRest();
    }

    bool inChord()
    {
      return chord;
    }

    /** Returns the number of marks attached to the note. **/

    int numMarks()
    {
      return marks.size();
    }

    /** Return true if mark is already a mark in the note. **/

    bool containsMark(Mark mark)
    {
      return marks.contains(mark);
    }

    /** Return mark at index or Marks::Empty if there are no marks. **/

    Mark getMark(int index)
    {
      return marks.getUnchecked(index);
    }

    /** Add a mark to note event **/

    void addMark(Mark mark)
    {
      marks.add(mark);
    }

    menc::Array<Mark>& getMarks()
    {
      return marks;
    }

    menc::Array<menc::Beam>& getBeams()
    {
      return beams;
    }

    menc::Array<menc::Slur>& getSlurs()
    {
      return slurs;
    }
    
    void addSlur(Slur slur)
    {
      slurs.add(slur);
    }
    
    bool hasTieBegin(void)
    {
      for(int i = 0; i < slurs.size(); i++)
        if(slurs[i] == menc::Slurs::TieBegin)
          return true;
      return false;
    }
    
    bool hasTieEnd(void)
    {
      for(int i = 0; i < slurs.size(); i++)
        if(slurs[i] == menc::Slurs::TieEnd)
          return true;
      return false;
    }

    menc::String toString()
    {
      menc::String str ("<Note");
      str += " beat: ";
      str += getBeat().toString();
      str += " dur: ";
      str += duration.toString();
      str += " note: ";
      str += note.toString();
      if (chord)
        str += "*";
      if (marks.size()>0)
      {
        str += " marks: ";
        for (int i=0; i<marks.size(); i++)
        {
          if (i>0) str += ",";
          str += menc::Marks::toString(marks.getUnchecked(i));
        }
      }
      if (beams.size()>0)
      {
        str += " beams: ";
        for (int i=0; i<beams.size(); i++)
        {
          if (i>0) str += ",";
          str += menc::Beams::toString(beams.getUnchecked(i));
        }
      }
      if (slurs.size()>0)
      {
        str += " slurs: ";
        for (int i=0; i<slurs.size(); i++)
        {
          if (i>0) str += ",";
          str += menc::Slurs::toString(slurs.getUnchecked(i));
        }
      }
      str += ">";
      return str;
    }

  };
  
  class ClefData : public ScoreData
  {

  public:
    
    menc::Clef clef;

    ClefData( Clef clf)
      : clef(clf)
    {
    }
    
    ~ClefData()
    {
    }

    menc::String toString()
    {
      menc::String str ("<Clef ");
      //      str += " time: ";
      //      str += getTime().toString();
      //      str += " clef: ";
      str += menc::Clefs::toString(clef);
      str += ">";
      return str;
    }

  };
  
  class MeterData : public ScoreData
  {

  public:
    
    menc::Meter meter;
    
    MeterData(int sig)
      : meter(sig)
    {
    }
    
    ~MeterData()
    {
    }
    
    menc::String toString()
    {
      menc::String str ("<Meter ");
      str += menc::Meters::toString(meter);
      str += ">";
      return str;
    }

  };
  
  class KeyData : public ScoreData
  {

  public:
    
    menc::Key key;
    
    KeyData(int sig)
      : key(sig)
    {
    }
    
    ~KeyData()
    {
    }

    menc::String toString()
    {
      menc::String str ("<Key ");
      str += menc::Keys::toString(key);
      str += ">";
      return str;
    }

  };
  
  class BarlineData : public ScoreData
  {

  public:
    
    menc::Barline barline;
    
    BarlineData(int bline)
      : barline(bline)
    {
    }
    
    ~BarlineData()
    {
    }

    menc::String toString()
    {
      menc::String str ("<Barline ");
      str += menc::Barlines::toString(barline);
      str += ">";
      return str;
    }

  };
  
  class TempoData : public ScoreData
  {

  public:
    
    double tempo;
    
    TempoData(double data)
      : tempo(data)
    {
    }
    
    ~TempoData()
    {
    }
    
    menc::String toString()
    {
      menc::String str ("<Tempo ");
      str += menc::String::doubleToString(tempo);
      str += ">";
      return str;
    }

  };
 
}

#endif
