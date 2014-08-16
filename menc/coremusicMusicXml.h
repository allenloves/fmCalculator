/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef coremusic_MusicXml_h
#define coremusic_MusicXml_h

/*=======================================================================*
      This file is only included if --xerces build option is specified!
 *=======================================================================*/

#include "coremusicXerces.h"
namespace menc
{

  /** MusicXmlDocument is a class that handles loading, validating and
  parsing MusicXML documents. You MUST call
  xercesc::XMLPlatformUtils::Initialize() before you use this
  class.**/

  class MusicXmlDocument : public XercesXmlDocument
  {

  public: 

    Score* parseSATB()
    {
      xercesc::DOMElement* rootnode=getDocumentElement();
      menc::Array<xercesc::DOMElement*> partnodes;
      menc::Array<menc::String> partnames;
      menc::Array<menc::Instrument> partinsts;

      Score* satb=0;
      if (!rootnode)
        return 0;
      if (!getPartNodes(rootnode, partnodes, partnames, partinsts))
      {
        std::cout << "failed to load parts!\n";
        return 0;
      }
      Array<ScoreData*> partdata;
      Array<Part*> scoreparts;
      for (int i=0; i<partnodes.size(); i++)
      {
        if (parsePart(partnodes[i], partdata))
        {
          scoreparts.add(new Part(i, partdata, partnames[i], partinsts[i]));
          partdata.clear();
        }
        else
        {
          partdata.clearWithDelete();
          break;
        }
      }
      if (scoreparts.size()==partnodes.size())
      {
        satb=new Score(scoreparts);
        menc::String title="";
        int number=0;
        parseHeader(rootnode, title, number);
        if (title.isNotEmpty())
          satb->addSetting(new Setting("title", title));
        if (number>0)
          satb->addSetting(new Setting("number", number));        
      }
      else
      {
        scoreparts.clearWithDelete();
      }
      return satb;
    }

    /** Returns part nodes and associated meta data. Parts are added
        to the array in the order their score-part definitions appear
        in the file. **/

    bool getPartNodes(xercesc::DOMElement* root, menc::Array<xercesc::DOMElement*>& partarray,
                      menc::Array<menc::String>&namearray, menc::Array<menc::Instrument>&instarray)
    {
      int Xsiz=256;
      XMLCh Xstr[Xsiz];

      // first gather all <score-part> objects (getElementsByTag names
      // collects all nodes with the specified tag).
      xercesc::XMLString::transcode("score-part", Xstr, Xsiz);
      xercesc::DOMNodeList* descs=root->getElementsByTagName(Xstr);

      // gather all the <part> objects. these hold the actual score
      // data and are linked to <score-part> elements by ID
      xercesc::XMLString::transcode("part", Xstr, Xsiz);
      xercesc::DOMNodeList* parts=root->getElementsByTagName(Xstr);

      // sanity check in case we are loading non-validated document
      if (parts->getLength() != descs->getLength()) 
        return false;

      // std::cout << "numparts=" << descs->getLength() << "\n";

      // iterate all <score-parts>, fetching each associated part
      // using the score-parts's id.  add part objects, names and
      // instruments to the arrays

      for (uint i=0; i<descs->getLength(); i++)
      {
        xercesc::DOMElement* info=(xercesc::DOMElement*)descs->item(i);
        xercesc::DOMElement* name=menc::XercesXmlDocument::findElement(info,"part-name");
        if (!name) return false; // sanity check on required <part-name> element
        namearray.add( menc::XercesXmlDocument::getNodeText(name));
        // parse instrument specification. this is an optional mxml
        // element so we try the part name no instrument is explicitly
        // provided. part instrument defaults to Piano if spec is not
        // provided or can't be parsed.
        xercesc::DOMElement* inst=menc::XercesXmlDocument::findElement(info,"score-instrument");
        menc::Instrument ins=menc::Instruments::Empty;
        if (inst)
        {
          xercesc::DOMElement* inam=menc::XercesXmlDocument::findElement(inst,"instrument-name");
          if (inam)
            ins=menc::Instruments::fromString(menc::XercesXmlDocument::getNodeText(inam));
          else
            std::cout << "WARNING: unsupported score-part instrument: '" 
                      << menc::XercesXmlDocument::getNodeText(inam) << "'\n";
        }
        else // if no explict instrument try the part name
        {
          ins=menc::Instruments::fromString(namearray.last());
        }

        if (ins==menc::Instruments::Empty)
          ins=menc::Instruments::Piano;
        //        std::cout << "instrument=" << menc::Instruments::toString(ins) << "\n";
        instarray.add(ins);

        // part id attribute of a <part-name> element links the
        // <part-name> element to its <part> element
        menc::String pid="";  
        pid=menc::XercesXmlDocument::getAttributeText(info, "id");
        bool found=false;
        // search all the <parts> for the part id of the current <score-part>
        for (uint j=0; pid.isNotEmpty() && j<parts->getLength(); j++)
          if (pid == menc::XercesXmlDocument::getAttributeText((xercesc::DOMElement*)parts->item(j), "id"))
          {
            partarray.add((xercesc::DOMElement*)parts->item(j));
            found=true;
            break;
          }
        // sanity check
        if (!found)
          return false;
      }
      return true;
    }

    /** Parse score for composition's title and number, return false
        if neither is there. **/

    bool parseHeader(xercesc::DOMElement* root, menc::String& title, int& number)
    {
      xercesc::DOMElement* work = menc::XercesXmlDocument::findElement(root, "work");
      if (work)
      {
        xercesc::DOMElement* node1=menc::XercesXmlDocument::findElement(work, "work-title");
        if (node1) title=getNodeText(node1);
        xercesc::DOMElement* node2=menc::XercesXmlDocument::findElement(work, "work-number");
        if (node2) number=getNodeText(node2).toInt();
        return (node1 || node2);
      }
      return false;
    }

    bool parsePart(xercesc::DOMElement* part, Array<ScoreData*>& scoredata)
    {
      XMLCh Xattributes [32];
      XMLCh Xsound [32];
      XMLCh Xtempo [32];
      XMLCh Xnote [32];
      XMLCh Xbarline [32];
      XMLCh Xforward [32];
      XMLCh Xbackward [32];
      XMLCh Ximplicit [32];
      XMLCh Xyes [32];
      xercesc::XMLString::transcode("attributes", Xattributes, 32);
      xercesc::XMLString::transcode("sound", Xsound, 32);
      xercesc::XMLString::transcode("tempo", Xtempo, 32);
      xercesc::XMLString::transcode("note", Xnote, 32);
      xercesc::XMLString::transcode("barline", Xbarline, 32);
      xercesc::XMLString::transcode("forward", Xforward, 32);     
      xercesc::XMLString::transcode("backward", Xbackward, 32);     
      xercesc::XMLString::transcode("implicit", Ximplicit, 32);     
      xercesc::XMLString::transcode("yes", Xyes, 32);     

      // Globals to maintain current state during parsing
      int gDivisions=1;
      menc::Ratio gTime=0;   // current time in score (advanced by notes)
      menc::Ratio gBeat=0;   // current beat time in measure (advanced by notes)
      menc::Ratio gMeas=0;   // current full measure duration for current meter
      menc::Ratio gKey=menc::Keys::Empty;  // current key
      menc::Meter gMeter=menc::Meters::Empty; // current meter
      int gTempo = 0;

      // iterate all the measures in the part

      //if (print) std::cout << "#(\n";
      for (xercesc::DOMElement* meas=part->getFirstElementChild(); meas!=NULL; meas=meas->getNextElementSibling())
      {
        menc::Barline barline=menc::Barlines::Bar;    // barline normally implit in each measure.
        bool partial=(xercesc::XMLString::compareIString( meas->getAttribute(Ximplicit), Xyes)==0);  // incomplete measure?
        gBeat=menc::Ratio(0,1); // assume downbeart (but check for implict measures later)
        // iterate all the elements in the measure
        for (xercesc::DOMElement* data=meas->getFirstElementChild(); data!=NULL; data=data->getNextElementSibling())
        {
          const XMLCh* tag = data->getTagName();
          //      std::cout << "tag=" << menc::XercesXmlDocument::xmlToString(tag) << "\n";      
          if (xercesc::XMLString::compareIString(tag,Xattributes)==0) // <attributes>
          {
            int divs=gDivisions;
            menc::Key key=menc::Keys::Empty;
            menc::Meter meter=menc::Meters::Empty;
            menc::Clef clef=menc::Clefs::Empty;
            if (parseAttributes(data, divs, key, meter, clef))
            {
              if (gDivisions!=divs)
              {
                gDivisions=divs;
              }
              if (clef!=menc::Clefs::Empty)
              {
                //if (print) printClef(gTime, clef);
                scoredata.add(new ClefData(clef));
              }
              if (key!=menc::Keys::Empty)
              {
                gKey=key;
                //if (print) printKey(gTime, key);
                scoredata.add(new KeyData(key));
              }
              if (meter!=menc::Meters::Empty)
              {
                gMeter=meter;
                gMeas=menc::Meters::measureDuration(gMeter);
                //if (print) printMeter(gTime, meter);
                scoredata.add(new MeterData(meter));
              }
            }
            else
              std::cout << "Warning: parseAttributes() FAILED\n";
          }
          else if (xercesc::XMLString::compareIString(tag,Xnote)==0) // <note>
          {
            // If we are the first note in a partial measure find out what
            // beat we are on by subtracting the remaining durations in
            // the measure from the current meter's full measure dur
            if (partial)
            {
              ////std::cout << "have partial measure\n";
              menc::Ratio sum (0,1);
              // sum durs of this and all remaining notes in measure
              for (xercesc::DOMElement* x=data; x!=NULL; x=x->getNextElementSibling())
              {
                //std::cout << "tag=" << menc::XercesXmlDocument::xmlToString(x->getTagName()) << "\n";
                if (xercesc::XMLString::compareIString(x->getTagName(), Xnote)==0)
                {
                  menc::Ratio dur (0,1);
                  if (parseDuration(x,gDivisions,dur))
                    sum = sum + dur;
                }
              }
              gBeat=gMeas-sum;
              partial=false;
            }
            menc::Note note;
            menc::Ratio dur (0,0);
            menc::Array<menc::Mark> marks;
            menc::Array<menc::Beam> beams;
            menc::Array<menc::Slur> slurs;

            if (parseNote(data, gDivisions, dur, note, marks, beams, slurs))
            {
              //if (print) printNote(gTime, menc::Meters::determineStress(gMeter, gBeat), dur, note, marks, beams, slurs);
              scoredata.add(new NoteData(gBeat, dur, note, marks, beams, slurs));
              gTime = gTime + dur;
              gBeat = gBeat + dur;
            }
          }
          else if (xercesc::XMLString::compareIString(tag,Xsound)==0) // <sound>
          {
            const XMLCh* tempo=data->getAttribute(Xtempo);
            if (tempo)
            {
              gTempo=xercesc::XMLString::parseInt(tempo);
              //if (print) printTempo(gTime, gTempo);
              scoredata.add(new TempoData(gTempo));
            }
          }
          else if (xercesc::XMLString::compareIString(tag,Xforward)==0) // <forward>
          {
            // ADD ME
          }
          else if (xercesc::XMLString::compareIString(tag,Xbackward)==0) // <backward>
          {
            // ADD ME
          }
          else if (xercesc::XMLString::compareIString(tag,Xbarline)==0) // <barline>
          {
            menc::Barline bl=menc::Barlines::Empty;
            if (parseBarline(data, bl))
            {
              barline=bl;
            }
            else
              std::cout << "Warning: parseBarline() FAILED (time " << gTime.toString() << ")\n";
          }
        }
        // done iterating all the elements in the measure
        if (barline!=menc::Barlines::Empty)
        {
          //if (print) printBarline(gTime, barline);
          scoredata.add(new BarlineData(barline));
        }
      }
      //if (print) std::cout << ")\n";
      return true;
    }
    /** parse measure attributes from a <mesure> **/

    bool parseAttributes(xercesc::DOMElement* attr, int& divs, menc::Key& key, menc::Meter& meter, menc::Clef& clef)
    {
      XMLCh Xdivisions [32];
      XMLCh Xkey [32];
      XMLCh Xtime [32];
      XMLCh Xclef [32];
      xercesc::XMLString::transcode("divisions", Xdivisions, 32);
      xercesc::XMLString::transcode("key", Xkey, 32);
      xercesc::XMLString::transcode("time", Xtime, 32);
      xercesc::XMLString::transcode("clef", Xclef, 32);

      xercesc::DOMElement* data=NULL;
      const XMLCh* tag=NULL;
      //  std::cout << "  numchilds=" << attr->getChildElementCount() << "\n";

      for (data=attr->getFirstElementChild(); data!=NULL; data=data->getNextElementSibling())
      {
        tag = data->getTagName();
        //    std::cout << "  tag=" << menc::XercesXmlDocument::xmlToString(tag) << "\n" ;
        if (xercesc::XMLString::compareIString(tag,Xdivisions)==0)
        {
          int i=menc::XercesXmlDocument::getNodeText(data).toInt();
          if (i<1) return false;
          divs=i;
        }
        else if (xercesc::XMLString::compareIString(tag,Xkey)==0)
        {
          xercesc::DOMElement* node=data->getFirstElementChild(); // <fifths>
          int fifths=menc::XercesXmlDocument::getNodeText(node).toInt();      
          node=node->getNextElementSibling(); // <mode>
          menc::String mode=menc::XercesXmlDocument::getNodeText(node);
          key=menc::Keys::fromSignatureAndMode(menc::KeySignatures::NoAccidentals + fifths,
                                               menc::Modes::fromString(mode));
        }
        else if (xercesc::XMLString::compareIString(tag,Xtime)==0)
        {
          xercesc::DOMElement* node=data->getFirstElementChild(); // <beats>
          menc::String str=menc::XercesXmlDocument::getNodeText(node);
          str += "/";
          node=node->getNextElementSibling(); // <beat-type>
          str += menc::XercesXmlDocument::getNodeText(node);
          meter=menc::Meters::fromString(str);
        }
        else if (xercesc::XMLString::compareIString(tag,Xclef)==0)
        {
          xercesc::DOMElement* node=data->getFirstElementChild(); // <sign>
          menc::String sign=menc::XercesXmlDocument::getNodeText(node);
          node=node->getNextElementSibling(); // <line>
          int line=menc::XercesXmlDocument::getNodeText(node).toInt();
          if (sign.equalsIgnoreCase("G"))
          {
            switch (line)
            {
            case 1: clef=menc::Clefs::FrenchViolin; break;
            case 2: clef=menc::Clefs::Treble; break;
            case 5: clef=menc::Clefs::SubBass; break;
            default: return false;
            }
          }
          else if (sign.equalsIgnoreCase("F"))
          {
            switch (line)
            {
            case 3: clef=menc::Clefs::BaritoneF; break;
            case 4: clef=menc::Clefs::Bass; break;
            case 5: clef=menc::Clefs::SubBass; break;
            default: return false;
            }
          }
          else if (sign.equalsIgnoreCase("C"))
          {
            switch (line)
            {
            case 1: clef=menc::Clefs::Soprano; break;
            case 2: clef=menc::Clefs::MezzoSoprano; break;
            case 3: clef=menc::Clefs::Alto; break;
            case 4: clef=menc::Clefs::TenorCello; break;
            case 5: clef=menc::Clefs::BaritoneC; break;
            default: return false;
            }
          }
          else
            return false;
        }
        //xercesc::XMLString::release(&tag);
      }
      return true;
    }

    /** Parse <note> data. **/

    bool parseNote(xercesc::DOMElement* node, int divisions, menc::Ratio& duration, menc::Note& note,
                   menc::Array<menc::Mark>& marks,
                   menc::Array<menc::Beam>& beams,
                   menc::Array<menc::Slur>& slurs)
    {
      XMLCh Xgrace [32];
      XMLCh Xcue [32];
      XMLCh Xchord [32];
      XMLCh Xunpitched [32];
      XMLCh Xpitch [32];
      XMLCh Xrest [32];
      XMLCh Xduration [32];
      XMLCh Xtype [32];
      XMLCh Xdot [32];
      XMLCh Xbeam [32];
      XMLCh Xnotations [32];
      xercesc::XMLString::transcode("grace", Xgrace, 32);
      xercesc::XMLString::transcode("cue", Xcue, 32);
      xercesc::XMLString::transcode("chord", Xchord, 32);
      xercesc::XMLString::transcode("unpitched", Xunpitched, 32);
      xercesc::XMLString::transcode("pitch", Xpitch, 32);
      xercesc::XMLString::transcode("rest", Xrest, 32);
      xercesc::XMLString::transcode("duration", Xduration, 32);
      xercesc::XMLString::transcode("type", Xtype, 32);
      xercesc::XMLString::transcode("dot", Xdot, 32);
      xercesc::XMLString::transcode("beam", Xbeam, 32);
      xercesc::XMLString::transcode("notations", Xnotations, 32);

      int ndots=0;
      menc::Ratio dur (0,0);
      menc::Ratio typ (0,0);
      // iterate all the elements of the note
      for (xercesc::DOMElement* data=node->getFirstElementChild(); data!=NULL; data=data->getNextElementSibling())
      {
        const XMLCh* tag = data->getTagName();
        //    std::cout << "  tag=" << menc::XercesXmlDocument::xmlToString(tag) << "\n" ;

        // we dont handle these elements yet
        if (xercesc::XMLString::compareIString(tag,Xgrace)==0) //<grace>
          return false;
        if (xercesc::XMLString::compareIString(tag,Xcue)==0) //<cue>
          return false;
        if (xercesc::XMLString::compareIString(tag,Xchord)==0) //<chord>
          return false;
        if (xercesc::XMLString::compareIString(tag,Xunpitched)==0) //<unpitched>
          return false;

        // at this point the note is either a <rest> or a <pitch>
        if (xercesc::XMLString::compareIString(tag,Xrest)==0) // <rest/>
        {
          note=menc::Note("R");
        }
        else if (xercesc::XMLString::compareIString(tag,Xpitch)==0) // <pitch>
        {
          node=data->getFirstElementChild(); // <step>
          menc::String str=menc::XercesXmlDocument::getNodeText(node).toUpperCase();
          // parse the optional <alter> element
          XMLCh Xalter [32];
          xercesc::XMLString::transcode("alter", Xalter, 32);
          node=node->getNextElementSibling();  // <alter> ? 
          if (xercesc::XMLString::compareIString(node->getTagName(),Xalter)==0)
          {
            int alter=menc::XercesXmlDocument::getNodeText(node).toInt();
            switch (alter)
            {
            case -2: str += "ff"; break;
            case -1: str += "f";  break;
            case  0: break;
            case  1: str += "s";  break;
            case  2: str += "ss"; break;
            default: return false;
            }
            node=node->getNextElementSibling();
          }
          str += menc::XercesXmlDocument::getNodeText(node); // <octave>
          note=menc::Note(str);
          //      std::cout << "note=" << note.toString() << "\n";
          if (note.isEmpty()) return false;
        }
        else if (xercesc::XMLString::compareIString(tag,Xduration)==0) // <duration>
        {
          int n=menc::XercesXmlDocument::getNodeText(data).toInt();
          if (n<1) return false;
          menc::Ratio q (1,4);
          menc::Ratio d (n,divisions);
          dur=q*d;
        }
        else if (xercesc::XMLString::compareIString(tag,Xtype)==0) // <type>
        {
          menc::String str=menc::XercesXmlDocument::getNodeText(data);
          if (str.equalsIgnoreCase("quarter")) typ=menc::Ratio(1,4);
          else if (str.equalsIgnoreCase("eighth")) typ=menc::Ratio(1,8);
          else if (str.equalsIgnoreCase("half")) typ=menc::Ratio(1,2);
          else if (str.equalsIgnoreCase("16th")) typ=menc::Ratio(1,16);
          else if (str.equalsIgnoreCase("whole")) typ=menc::Ratio(1,1);
          else if (str.equalsIgnoreCase("32nd")) typ=menc::Ratio(1,32);
          else if (str.equalsIgnoreCase("breve")) typ=menc::Ratio(2,1);
          else if (str.equalsIgnoreCase("64th")) typ=menc::Ratio(1,64);
          else if (str.equalsIgnoreCase("long")) typ=menc::Ratio(4,1);
          else if (str.equalsIgnoreCase("128th")) typ=menc::Ratio(1,128);
          else return false;
        }
        else if (xercesc::XMLString::compareIString(tag,Xdot)==0)
        {
          ndots++;
        }
        else if (xercesc::XMLString::compareIString(tag,Xbeam)==0) // <beam>
        {
          menc::BeamLevel level=menc::BeamLevels::Empty;
          menc::BeamPart part=menc::BeamParts::Empty;
          int num=menc::XercesXmlDocument::getAttributeText(data, "number").toInt(); // 1 ... 6
          switch (num)
          {
          case 1: level=menc::BeamLevels::Eighth; break;
          case 2: level=menc::BeamLevels::Sixteenth; break;
          case 3: level=menc::BeamLevels::ThirtySecond; break;
          case 4: level=menc::BeamLevels::SixtyFourth; break;
          case 5: level=menc::BeamLevels::HundredTwentyEighth; break;
          case 6: return false; // punt on mxml's 256th note!
          default: return false;
          }
          menc::String str=menc::XercesXmlDocument::getNodeText(data);
          if (str.equalsIgnoreCase("begin"))
            part=menc::BeamParts::Begin;
          else if (str.equalsIgnoreCase("end"))
            part=menc::BeamParts::End;
          else if (str.equalsIgnoreCase("continue"))
            part=menc::BeamParts::Continue;
          else if (str.equalsIgnoreCase("forward hook"))
            part=menc::BeamParts::PartialForward;
          else if (str.equalsIgnoreCase("backward hook"))
            part=menc::BeamParts::PartialBackward;
          else return false;
          beams.add(menc::Beams::fromLevelAndPart(level, part));
        }
        else if (xercesc::XMLString::compareIString(tag,Xnotations)==0) // <notations>
        {
          XMLCh Xtied [32];
          XMLCh Xtype [32];
          XMLCh Xstart [32];
          XMLCh Xstop [32];
          XMLCh Xfermata [32];
          XMLCh Xdynamics [32];
          xercesc::XMLString::transcode("tied", Xtied, 32);
          xercesc::XMLString::transcode("type", Xtype, 32);
          xercesc::XMLString::transcode("start", Xstart, 32);
          xercesc::XMLString::transcode("stop", Xstop, 32);
          xercesc::XMLString::transcode("fermata", Xfermata, 32);
          xercesc::XMLString::transcode("dynamics", Xdynamics, 32);
          // iterate each <notation> element
          for (xercesc::DOMElement* elem=data->getFirstElementChild(); elem!=NULL; elem=elem->getNextElementSibling())
          {
            const XMLCh* nam = elem->getTagName();
            if (xercesc::XMLString::compareIString(nam,Xtied)==0) 
            {
              if (xercesc::XMLString::compareIString(elem->getAttribute(Xtype),Xstart)==0) // type="start"
                slurs.add((menc::Slur)menc::Slurs::TieBegin);
              else
                slurs.add((menc::Slur)menc::Slurs::TieEnd);
            }
            else if (xercesc::XMLString::compareIString(nam,Xfermata)==0)
            {
              menc::Mark m = menc::Marks::Fermata; 
              marks.add(m);
            }
            else if (xercesc::XMLString::compareIString(nam,Xdynamics)==0) // <dynamics>
            {
              // FINISH ME
            }
          }
        }
      }
      // prefer using <type> over <duration> for rhythm value
      if (!typ.isEmpty())
      {
        duration=typ;
        for (int d=0; d<ndots; d++)
        {
          typ=typ*menc::Ratio(1,2);
          duration=duration+typ;
        }
      }
      else
        duration=dur;

      return true;
    }

    /** parse barline data from a <barline> element. returns true if
        successful **/

    bool parseBarline(xercesc::DOMElement* bar, menc::Barline& barline)
    {
      XMLCh Xlocation [32];
      XMLCh Xright [32];
      XMLCh Xbarstyle [32];
      XMLCh Xending [32];
      XMLCh Xrepeat [32];

      xercesc::XMLString::transcode("location", Xlocation, 32);
      xercesc::XMLString::transcode("right", Xright, 32);
      xercesc::XMLString::transcode("bar-style", Xbarstyle, 32);
      xercesc::XMLString::transcode("ending", Xending, 32);
      xercesc::XMLString::transcode("repeat", Xrepeat, 32);

      // give up if this is not an explict right-side barline...
      if (xercesc::XMLString::compareIString(bar->getAttribute(Xlocation),Xright)!=0)
        return false;

      for (xercesc::DOMElement* data=bar->getFirstElementChild(); data!=NULL; data=data->getNextElementSibling())
      {
        const XMLCh* tag = data->getTagName();
        //std::cout << "  tag=" << menc::XercesXmlDocument::xmlToString(tag) << "\n" ;

        if (xercesc::XMLString::compareIString(tag,Xbarstyle)==0) // <barstyle>
        {
          menc::String str=menc::XercesXmlDocument::getNodeText(data);
          // not sure what barlines are lurking out there so im
          // checking explicitly for now
          if (str.equalsIgnoreCase("regular"))
            barline=menc::Barlines::Bar;
          else if (str.equalsIgnoreCase("light-light"))
            barline=menc::Barlines::InteriorDoubleBar;
          else if (str.equalsIgnoreCase("light-heavy"))
            barline=menc::Barlines::DoubleBar;
          else if (str.equalsIgnoreCase("heavy-heavy"))
            barline=menc::Barlines::fromLine(menc::Barlines::HeavyHeavy);
          else if (str.equalsIgnoreCase("heavy-light"))
            barline=menc::Barlines::fromLine(menc::Barlines::HeavyLight);
          else if (str.equalsIgnoreCase("none"))
            barline=menc::Barlines::fromLine(menc::Barlines::Invisible);
          else
          {
            std::cout << "BARLINE FAILURE ON '" << str << "'\n";
            return false;
          }
        }
        else if (xercesc::XMLString::compareIString(tag,Xending)==0) // <ending>
        {
          // FIXME: CANT HANDLE THIS YET
          menc::String str=menc::XercesXmlDocument::getNodeText(data);
          std::cout << "BARLINE FAILURE ON '" << str << "'\n";
          return false;
        }
        else if (xercesc::XMLString::compareIString(tag,Xrepeat)==0) // <repeat>
        {
          XMLCh Xdirection [32];
          XMLCh Xforward [32];
          XMLCh Xbackward [32];
          xercesc::XMLString::transcode("direction", Xdirection, 32);
          xercesc::XMLString::transcode("forward", Xforward, 32);
          xercesc::XMLString::transcode("backward", Xbackward, 32);
          if (xercesc::XMLString::compareIString(data->getAttribute(Xdirection),Xforward)==0)
            barline=menc::Barlines::BeginRepeatBar;
          else if (xercesc::XMLString::compareIString(data->getAttribute(Xdirection),Xbackward)==0)
            barline=menc::Barlines::EndRepeatBar;
          else 
          {
            menc::String str=menc::XercesXmlDocument::getNodeText(data);
            std::cout << "BARLINE FAILURE ON '" << str << "'\n";

            // FIXME: SINCE YOU CANT HAVE MORE THAN ONE REPEAT ELEMENT, I
            // DONT UNDERSTAND HOW MXML ENCODES INTERIOR REPEAT BARS...
            return false; 
          }
        }
      }
      return true;
    }

    /** Parse duration from a <note>, <forward> or <backward>
    element. If the element is a note use its <type> and <dot/>
    elements (if available) otherwise use <duration>. Returns true if
    duration is successfully parsed otherwise false. **/

    bool parseDuration(xercesc::DOMElement* elem, int divisions, menc::Ratio& duration)
    {
      //std::cout << "parseDuration, tag: " << menc::XercesXmlDocument::xmlToString(elem->getNodeName()) << "\n";

      XMLCh Xstr [32];
      xercesc::XMLString::transcode("type", Xstr, 32); 
      xercesc::DOMNodeList* type=elem->getElementsByTagName(Xstr);
      // if we are a note then prefer using the <type> and <dot> elements
      if (type->getLength()==1)
      {
        //    std::cout << "PARSING <TYPE> LEN=1\n";
        menc::String str=menc::XercesXmlDocument::getNodeText(type->item(0));
        //   std::cout << "TEXT=" << str << "\n";
        menc::Ratio dur (0,0);
        if (str.equalsIgnoreCase("quarter")) dur=menc::Ratio(1,4);
        else if (str.equalsIgnoreCase("eighth")) dur=menc::Ratio(1,8);
        else if (str.equalsIgnoreCase("half")) dur=menc::Ratio(1,2);
        else if (str.equalsIgnoreCase("16th")) dur=menc::Ratio(1,16);
        else if (str.equalsIgnoreCase("whole")) dur=menc::Ratio(1,1);
        else if (str.equalsIgnoreCase("32nd")) dur=menc::Ratio(1,32);
        else if (str.equalsIgnoreCase("breve")) dur=menc::Ratio(2,1);
        else if (str.equalsIgnoreCase("64th")) dur=menc::Ratio(1,64);
        else if (str.equalsIgnoreCase("long")) dur=menc::Ratio(4,1);
        else if (str.equalsIgnoreCase("128th")) dur=menc::Ratio(1,128);
        else return false;
        xercesc::XMLString::transcode("dot", Xstr, 32);
        xercesc::DOMNodeList* dots=elem->getElementsByTagName(Xstr);
        int ndots=dots->getLength();
        //    std::cout << "NDOTS=" << ndots << "\n";
        if (ndots>0)
          duration = dur + (dur * menc::Ratio (1,1) - menc::Ratio(1, (2^ndots)));
        else
          duration=dur;
      }
      else
      {
        //    std::cout << "PARSING <DURATION>\n";
        xercesc::XMLString::transcode("duration", Xstr, 32);
        xercesc::DOMNodeList* temp=elem->getElementsByTagName(Xstr);
        if (temp->getLength()==1) // <duration>
        {
          //      std::cout << "HAVE <DURATION>\n";
          int div=menc::XercesXmlDocument::getNodeText(temp->item(0)).toInt();
          if (div<1) return false;
          menc::Ratio q (1,4);
          menc::Ratio d (div,divisions);
          duration=q*d;
        }
        else
        {
          //      std::cout << "NO <DURATION>, returning false\n";
          return false;
        }
      }
      return true;
    }

  private:

    void printKey(menc::Ratio time, menc::Key key)
    {
      std::cout << "(key " << time.toString() << " " << menc::Keys::toString(key) << ")\n";
    }

    void printTempo(menc::Ratio time, int tempo)
    {
      std::cout << "(tempo " << time.toString() << " " << tempo << ")\n";
    }

    void printMeter(menc::Ratio time, menc::Meter meter)
    {
      std::cout << "(meter " << time.toString() << " " << menc::Meters::toString(meter).replaceChar('/', ' ') << ")\n";
    }

    void printClef(menc::Ratio time, menc::Clef clef)
    {
      std::cout << "(clef " << time.toString() << " " << menc::Clefs::toString(clef) << ")\n";
    }

    void printBarline(menc::Ratio time, menc::Barline barline)
    {
      std::cout << "(barline " << time.toString() << " " << menc::Barlines::toString(barline) << ")\n";
    }

    void printNote(menc::Ratio time, menc::MetricWeight weight, menc::Ratio dur, menc::Note note, menc::Array<menc::Mark>& marks, menc::Array<menc::Beam>& beams, menc::Array<menc::Slur>& slurs)
    {
      // " [" << menc::MetricWeights::toString(weight) << "] " 
      std::cout << "(note " << time.toString() << " " << dur.toString() << " " << note.toString() ;
      // print marks
      std::cout << " (";
      for (int i=0; i<marks.size(); i++)
      {
        if (i>0) std::cout << " ";
        std::cout << menc::Marks::toString(marks[i]);
      }
      std::cout << ")";
      // print beams
      std::cout << " (";
      for (int i=0; i<beams.size(); i++)
      {
        if (i>0) std::cout << " ";
        std::cout << menc::Beams::toString(beams[i]);
      }
      std::cout << ")";
      // print slurs
      std::cout << " (";
      for (int i=0; i<slurs.size(); i++)
      {
        if (i>0) std::cout << " ";
        std::cout << menc::Slurs::toString(slurs[i]);
      }
      std::cout << ")";
      std::cout << ")\n";
    }





  };
}

#endif
