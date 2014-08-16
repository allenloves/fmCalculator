/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef coremusic_SatbXml_h
#define coremusic_SatbXml_h

/*=======================================================================*
      This file is only included if --xerces build option is specified!
 *=======================================================================*/

#include "coremusicXerces.h"

namespace menc
{

  /** SatbXmlDocument handle loading and validating CC1-style Xml
      docuemnts. Before you use this class you MUST call
      xercesc::XMLPlatformUtils::Initialize() **/

  class SatbXmlDocument : public XercesXmlDocument
  {

  public:

    SatbXmlDocument () 
      : XercesXmlDocument()
    {
    }

    virtual ~SatbXmlDocument () 
    {
    }

    /** Loads an satb from an xml source. if isFile is true then
        source is a pathname to an xml file else source contains the
        xml text directly. Loading returns NULL on failure, in which
        case you can call lastLoadError() to retrieve the error string
        for printing. **/

    Score* xmlLoadSATB(String source, bool isFile)
    {
      Score* satb=NULL;
      menc::String partnames[4] = {"Soprano", "Alto", "Tenor", "Bass" };
      menc::Instrument partinsts[4]={menc::Instruments::SopranoChoir, menc::Instruments::AltoChoir, menc::Instruments::TenorChoir, menc::Instruments::BassChoir};
      // If the parse was successful, read the document data from the DOM tree
      if (loadDocument(source,isFile))
      {
        XMLCh Xbuf [128];
        // std::cout << "No DOM Errors!\n";
        // at this point we have a valid <satb> with <settings>, <parts>
        // and (optional) <theory> elements
        xercesc::DOMElement* satbnode = getDocumentElement();
        xercesc::DOMElement* settingsnode = satbnode->getFirstElementChild();
        xercesc::DOMElement* partsnode = settingsnode->getNextElementSibling();
          
        // the satb's 'type=' attr contains the validated ScoreType
        {
          xercesc::XMLString::transcode("type", Xbuf, 255);
          menc::String type = xmlToString(satbnode->getAttribute(Xbuf));
          satb=new Score();
          // NB: MTW voices are in BTAS order! (id 0 is bass)
          for (int i=0; i<4; i++)
            satb->addPart(new Part(i, partnames[i], partinsts[i]));
        }
          
        // iterate all the settings and add them to the satb or abort
        // the loop on error.
        for (xercesc::DOMElement* node = settingsnode->getFirstElementChild();
             node != NULL && !errorOccured;
             node = node->getNextElementSibling())
        {
          if (!xmlLoadSATBSetting(satb, node))
          {
            errorOccured = true;
            break;
          }
        }
          
        //for (int i=0;i<satb->getSettings().numSettings();i++)
        //std::cout << satb->getSettings().getSetting(i)->toXmlString() << "\n";
          
        // temporary sanity check to insure that all required settings
        // are defined for bach chorales (this isnt done by the dtd yet)
        if (true)
        {
          if (!xmlHackInsureBachChoraleSettings(satb))
            errorOccured = true;
        }
          
        // now parse the voices. in the xml file these are stored
        // soprano to bass (soprano is id 0)
        if (!errorOccured)
        {
          int voice = 0;
          for (xercesc::DOMElement* node = partsnode->getFirstElementChild();
               node != NULL && !errorOccured;
               node = node->getNextElementSibling())
          {
            if (!xmlLoadSATBPart(satb, node, voice))
            {
              errorOccured=true;
              break;
            }
            voice++;
          }
        } 
          
        if (errorOccured)
        {
          delete satb;
          satb=0;
        }
      }
      return satb;
    }

    /** (internal function) parses a setting from its xml node and add
        it to the satb. return false if we encounted an error while
        parsing **/

    bool xmlLoadSATBSetting(Score* satb, xercesc::DOMElement* settingnode)
    {
      //      bool errorOccured = false;
      XMLCh Xbuf [128];
      // the 'name=' attr holds the setting's name
      xercesc::XMLString::transcode("name", Xbuf, 127);
      String name = xmlToString(settingnode->getAttribute(Xbuf));
      // the 'type=' attr holds the setting's value type. this attr is
      // validated by the DTD so we dont have to check it, we just have to
      // convert it to a ValueType
      xercesc::XMLString::transcode("type", Xbuf, 127);
      Setting::ValueType type = Setting::stringToValueType(xmlToString(settingnode->getAttribute(Xbuf)));
      // text holds the actual value of the setting
      menc::String text = xmlToString(settingnode->getTextContent());
      // remove any white space from front and back
      text.trim();
      //std::cout << "setting: name='" << name << "' type='" << Setting::valueTypeToString(type) << "' text='" << text << "'\n";
      switch (type)
      {
      case Setting::BoolValue:
        {
          // no error for reading a bool 
          satb->addSetting(new Setting(name, text.toBool()));
          break;
        }
      case Setting::IntValue:
        {
          // no error for reading an int
          satb->addSetting(new Setting(name, text.toInt()));
          break;
        }
      case Setting::DoubleValue:
        {
          // no error for reading a double
          satb->addSetting(new Setting(name, text.toDouble()));
          break;
        }
      case Setting::StringValue:
        {
          // no error for reading a string
          satb->addSetting(new Setting(name, text));
          break;
        }
      case Setting::NoteValue:
        {
          Note note (text);
          if (note.isEmpty())
          {
            errorOccured = true;
            xmlLoadErrorString += "Error: XML value '";
            xmlLoadErrorString += text;
            xmlLoadErrorString += "' is not a note.";
            return false;
          }
          satb->addSetting(new Setting(name, note));
          break;
        }
      case Setting::RatioValue:
        {
          Ratio ratio (text);
          if (ratio.isEmpty())
          {
            errorOccured = true;
            xmlLoadErrorString += "Error: XML value '";
            xmlLoadErrorString += text;
            xmlLoadErrorString += "' is not a ratio.";
            return false;
          }
          satb->addSetting(new Setting(name, ratio));
          break;
        }
      case Setting::MeterValue:
        {
          Meter meter=Meters::fromString(text);
          if (meter==Meters::Empty) 
          {
            errorOccured = true;
            xmlLoadErrorString += "Error: XML value '";
            xmlLoadErrorString += text;
            xmlLoadErrorString += "' is not a meter.";
            return false;
          }
          satb->addSetting(new Setting(name, meter, Setting::MeterValue));
          break;
        }
      case Setting::KeyValue:
        {
          Key key=Keys::fromString(text);
          if (key==Keys::Empty)
          {
            errorOccured = true;
            xmlLoadErrorString += "Error: XML value '";
            xmlLoadErrorString += text;
            xmlLoadErrorString += "' is not a key.";
            return false;
          }
          satb->addSetting(new Setting (name, key, Setting::KeyValue));
          break;
        }
      case Setting::MarkValue:
        {
          Mark mark=Marks::fromString(text);
          if (mark==Marks::Empty)
          {
            errorOccured = true;
            xmlLoadErrorString += "Error: XML value '";
            xmlLoadErrorString += text;
            xmlLoadErrorString += "' is not a makr.";
            return false;
          }
          satb->addSetting(new Setting (name, mark, Setting::MarkValue));
          break;
        }
      default: // shouldn't happen
        errorOccured = true;
        return false;
      }
      return true;
    }

    /** (internal function) parses a part and fills it with the note
        events. returns false if a parse error occurs. **/

    bool xmlLoadSATBPart(Score* satb, xercesc::DOMElement* partnode, int index)
    {
      Part* part=satb->getPart(index);
      Ratio start=satb->findSetting("start")->getRatioValue();
      //      part->setTime(start);
      for (xercesc::DOMElement* node = partnode->getFirstElementChild();
           node != NULL && !errorOccured;
           node = node->getNextElementSibling())
      {
        NoteData* event = new NoteData();
        xercesc::DOMElement* param = 0;
        // <start></start>
        {
          param = node->getFirstElementChild();
          String tok = xmlToString(param->getTextContent());
          tok.trim();
          Ratio time = Ratio(tok);
          if (time.isEmpty())
          {
            errorOccured = true;
            xmlLoadErrorString += "XML error: '";
            xmlLoadErrorString += tok;                  
            xmlLoadErrorString += "' is not a valid time.";
          }
          else 
          {
            //            event->setTime(time);
          }
        }  
        if (!errorOccured)
        {
          param = param->getNextElementSibling(); // <duration></duration>
          String tok = xmlToString(param->getTextContent());
          tok.trim();
          Ratio time = Ratio(tok);
          if (time.isEmpty())
          {
            errorOccured = true;
            xmlLoadErrorString += "XML error: '";
            xmlLoadErrorString += tok;                  
            xmlLoadErrorString += "' is not a valid duration.";
          }
          else 
            event->setDuration(time);
        }
        if (!errorOccured)
        {
          param = param->getNextElementSibling(); // <note></note>
          String tok = xmlToString(param->getTextContent());
          tok.trim();
          Note note = Note(tok);
          if (note.isEmpty())
          {
            errorOccured = true;
            xmlLoadErrorString += "XML error: '";
            xmlLoadErrorString += tok;                  
            xmlLoadErrorString += "' is not a valid note.";
          }
          else 
            event->setNote(note);
        }  
        if (!errorOccured)
        {
          // process optional series of <mark></mark>
          for (param=param->getNextElementSibling(); 
               param != NULL; 
               param=param->getNextElementSibling())
          {
            String tok = xmlToString(param->getTextContent());
            Mark mark = Marks::fromString(tok);
            tok.trim();
            if (mark == Marks::Empty)
            {
              errorOccured = true;
              xmlLoadErrorString += "XML error: '";
              xmlLoadErrorString += tok;                  
              xmlLoadErrorString += "' is not a valid mark.";
            }
            else
              event->addMark(mark);
          }
        }
        if (errorOccured)
        {
          delete event;
          return false;
        }
        part->addScoreData(event);
      }
      return true;
    }
    
    /** (internal function) hack sanity check to make sure all the
        required bach chorale settings are defined. FIXME: need to
        figure out how to make the DTD enforce some settings as being
        required but also allowing all settings to be specified in any
        order... **/

    bool xmlHackInsureBachChoraleSettings(Score* satb)
    {
      static const String requiredbachchoralsettings[7]
        = {"title", "number", "key", "meter", "start", "repeat", "tempo"};
      for (int i=0; i<7; i++)
        if (!satb->findSetting(requiredbachchoralsettings[i]))
        {
          xmlLoadErrorString += "XML error: Missing required '";
          xmlLoadErrorString += requiredbachchoralsettings[i];
          xmlLoadErrorString += "' setting.\n" ;
          return false;
        }
      return true;
    }

  };

}

#endif
