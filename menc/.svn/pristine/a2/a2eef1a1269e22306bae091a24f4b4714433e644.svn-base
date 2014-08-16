/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef coremusic_Score_h
#define coremusic_Score_h

#include "menc.h"
#include "coremusicPart.h"
#include "coremusicSettings.h"

namespace menc
{

  /** A class that manages score data. It can contain settings and
      parts. **/

  class Score
  {

  public:

    /** A class for iterating all the score data in a score by
        time-point. To define a parser, inherit from this class and
        implement its momentHandlerCallback() function. See
        doMoments() for more information. **/

    class MomentHandler
    {
    public:

      virtual ~MomentHandler() {}

      /** Callback to happen on every moment (time point) in the
          score. Score is the score being parsed, momentDuration is
          the current moment's rhythmic duration (0 for non-note data)
          and momentData is the array of score data contained in the
          current moment. Depending on how doMoments() is called
          positions in the array might contain NULLs. See doMoments()
          for more information. **/

      virtual void momentHandlerCallback(menc::Score* score, menc::Ratio momentDuration,
                                         menc::Array<ScoreData*>& momentData) = 0;

      /** Callback to happen just before iteration begins. **/

      virtual void momentHandlerInitialize(menc::Score* score) {};

      /** Callback to happen just after iteration stops. **/

      virtual void momentHandlerFinalize(menc::Score* score) {};
    };

  private:

    /** An array of parts, each representing an independent time line
        in the score. **/

    menc::Array<Part*> parts;  

    /** An array of settings, each holding a named property or default
        value for the score. **/

    Settings settings;

  public:

    /** Score constructor. **/

    Score()
    {
    }

    /** Score constructor with array of parts. Once parts are added
        they are owned by the score and should not be deleted. **/

    Score(Array<Part*>& scoreParts)
    {
      for (int i=0; i<scoreParts.size(); i++)
        parts.add(scoreParts.getUnchecked(i));
    }

    /** Score destructor deletes all parts and settings. **/

    ~Score()
    {
      settings.clearAllSettings(); 
      parts.clearWithDelete();
    }

    /** Return the settings of the score. **/

    Settings& getSettings()
    {
      return settings;
    }

    /** Returns the setting with the specified name or NULL if it does
        not exist. **/

    Setting* findSetting(String name)
    {
      return settings.findSetting(name);
    }

    /** Adds a setting to the score. Once settings are added they are
        owned by the score and should not be deleted.**/

    void addSetting(Setting* setting)
    {
      settings.addSetting(setting);
    }

    /** Returns the score's array of parts. **/

    menc::Array<menc::Part*>& getParts()
    {
      return parts;
    }

    /** Return the number of parts in the score. **/

    int numParts()
    {
      return parts.size();
    }

    /** Return the part at the specified index. **/

    Part* getPart(int index)
    {
      return parts[index];
    }

    /** Appends a new part to the score. Once a part is added it is
        owned by the score and should not be deleted. **/

    void addPart(Part* p)
    {
      parts.add(p);
    }

    /** Iterates all score data in the score by time-point, advancing
    time by the smallest simulaneous rhythmic increment found in all
    parts. To iterate score data first define a subclass of
    MomentHandler to accept score data and then pass an instance of
    this class to doMoments(). Your MomentHandler's
    momentHandlerCallback() will then be called on all moments in the
    score and passed the current moment duration and an array of score
    data for that moment in the same order as the parts are defined in
    the score.

    For example, if the partwise data for a measure is:

        Part1:  Key Q E E H     Bar
        Part2:  Key H.      Q   Bar
        Part3:  Key Q Q   Q E E Bar
        Part4:  Key Q Q   Q Q   Bar

    then the moments (duration and array) will be:

       Dur   Part1 Part2 Part3 Part4
             -----------------------
        0    [Key   Key   Key   Key]
        Q    [Q     H.    Q     Q]    
        E    [E     H.    Q     Q]
        E    [E     H.    Q     Q]
        Q    [H     H.    Q     Q]
        E    [H     Q     E     Q]
        E    [H     Q     E     Q]
        0    [Bar   Bar   Bar   Bar]

    If onlyFresh is true then objects apper in moments only the first
    time they are touched:

       Dur   Part1 Part2 Part3 Part4
             -----------------------
        0    [Bar   Bar   Bar   Bar]
        Q    [Q     H.    Q     Q]    
        E    [E     -     Q     Q]
        E    [E     -     -     -]
        Q    [H     -     Q     Q]
        E    [-     Q     E     Q]
        E    [-     -     E     -]
        0    [Bar   Bar   Bar   Bar]
    **/

    void doMoments(MomentHandler* handler, bool onlyFresh=false)
    {
      // arrays of partwise data, each index for a different part
      menc::Array<int> indexes;            // indexes to data in the current moment
      menc::Array<menc::Ratio> durations;  // durations of data in the current moment
      menc::Array<bool> started;           // true if data just added to moment
      menc::Array<ScoreData*> moment;      // array of data passed to handler

      // Call user's initalize method 
      handler->momentHandlerInitialize(this);

      // initalize arrays with index to first data in each part and
      // its duration. the duration of non-note data is 0. if a part
      // has no data then its index will be -1.
      for (int i=0; i<numParts(); i++)
      {
        menc::Part* part=getPart(i);
        durations.add(0);
        started.add(true);
        indexes.add( (part->numScoreData()>0) ? 0 : -1);
        if (indexes[i]>-1)
          durations[i]=part->getScoreData(indexes[i])->getDuration();
        //durations[i]=getMomentDuration(part->getScoreData(indexes[i]));
        moment.add(NULL); // passed to handler
      }

      menc::Ratio currenttime=0;
      while (true)
      {
        // iterate each part, look at the current note in that part
        // and set momentdur to the smallest duration found in any
        // part. stop the entire loop if all indexes are -1.
        menc::Ratio momentdur=0;
        bool done=true;
        for (int i=0; i<indexes.size(); i++)
          if (indexes[i]>-1) // valid indexes are 0 and above
          {
            done=false;
            if ((durations[i]>0) && (durations[i]<momentdur || momentdur==0))
              momentdur=durations[i];
          }
        if (done)
          break;

        // call the user's handler passing it momentdur and the
        // scoredata from each part. if onlyFresh is true then data
        // are added to the array on their first appearance and set to
        // NULL on subsequent appearances.

        for (int i=0; i<indexes.size(); i++)
          moment[i] = (!onlyFresh || (onlyFresh && started[i])) ? getPart(i)->getScoreData(indexes[i]) : NULL;
        handler->momentHandlerCallback(this, momentdur, moment);
    
        // now subtract momentdur from durations. for any moment == 0 increment
        // its index to its next note and set its next duration

        // FIXME: This will go into an infinite loop if data is out of
        // sync, ie if 0 duration data is mixed with note data in the same
        // moment!!!!!

        for (int i=0; i<durations.size(); i++)
        {
          menc::Ratio dif=durations[i]-momentdur;
          durations[i] = dif;
          started[i]=false;
          if (durations[i]<=0)
          {
            menc::Part* part=getPart(i);
            // increment to next index or -1 if there is none
            if ((++indexes[i])==part->numScoreData()) indexes[i]=-1;
            if (indexes[i]>-1)
            {
              started[i]=true;
              durations[i]=part->getScoreData(indexes[i])->getDuration();
              //durations[i]=getMomentDuration(part->getScoreData(indexes[i]));
            }
          }
        }
        currenttime += momentdur;
      }

      // Call user's finalize method 
      handler->momentHandlerFinalize(this);
    }

  };
  
}

#endif

