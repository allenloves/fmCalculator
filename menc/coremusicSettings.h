/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef coremusic_Settings_h
#define coremusic_Settings_h

namespace menc 
{
  
  /** A setting is a named menc value. **/

  class Setting
  {

  public:

    /** ValueType types the value stored in a setting.  **/

    typedef uint32 ValueType;

    /** Enumerations of the value types. low byte holds basic C type of the value,
        high byte holds menc subtypes **/

    // byte 1 holds basic type
    static const ValueType Empty        = 0;
    static const ValueType BoolValue    = 0x0001;
    static const ValueType IntValue     = 0x0002;
    static const ValueType DoubleValue  = 0x0003;
    static const ValueType StringValue  = 0x0004;
    static const ValueType NoteValue    = 0x0005;
    static const ValueType RatioValue   = 0x0006;
    // byte 2 holds sub type
    static const ValueType MeterValue   = 0x0010 + IntValue;
    static const ValueType KeyValue     = 0x0020 + IntValue;
    static const ValueType MarkValue    = 0x0030 + IntValue;

    /** Returns ValueType from external (xml) name. **/

    static const ValueType stringToValueType(String xml)
    { 
      if (xml.equals("boolean")) return BoolValue;
      if (xml.equals("integer")) return IntValue;
      if (xml.equals("float")) return DoubleValue;
      if (xml.equals("string")) return StringValue;
      if (xml.equals("note")) return NoteValue;
      if (xml.equals("ratio")) return RatioValue;
      if (xml.equals("meter")) return MeterValue;
      if (xml.equals("key")) return KeyValue;
      if (xml.equals("mark")) return MarkValue;
      return Empty;
    }

    /** Returns external (xml) name of ValueType. **/

    static const String valueTypeToString(ValueType type)
    { 
      switch (type)
        {
        case BoolValue: return "boolean" ;
        case IntValue: return "integer" ;
        case DoubleValue: return "float" ;
        case StringValue: return "string" ;
        case NoteValue: return "note" ;
        case RatioValue: return "ratio" ;
        case MeterValue: return "meter" ;
        case KeyValue: return "key" ;
        case MarkValue: return "mark" ;
        default: return "empty";
        }
    }

  private:

    String name;
    ValueType type;
    union ValueUnion
    {
      bool boolValue;
      int intValue;
      double doubleValue;
      String* stringValue;
      int64 int64Value;
    };
    ValueUnion value;   

  public:

    /** Setting constructor **/

    Setting()
      : name(""), type(Empty)
    {
      value.int64Value=0;
    }

    /** Constructor for bool and bool subtype settings.  **/

    Setting(const String settingName, const bool settingValue, const ValueType subType = Empty)
      : name (settingName)
    {
      if (subType == Empty) type = BoolValue; else type = subType;
      value.boolValue = settingValue;
    }

    /** Constructor for int and int subtype settings.  **/

    Setting(const String settingName, const int settingValue, const ValueType subType = Empty)
      : name (settingName) 
    {
      if (subType == Empty) type = IntValue; else type = subType;
      value.intValue = settingValue;
    }

    /** Constructor for double and double subtype settings.  **/

    Setting(const String settingName, const double settingValue, const ValueType subType = Empty)
      : name (settingName)
    {
      if (subType == Empty) type = DoubleValue; else type = subType;
      value.doubleValue = settingValue;
    }

    /** Constructor for string and string subtype settings.  **/

    Setting(const String settingName, char* settingValue, const ValueType subType = Empty)
      : name (settingName)
    {
      if (subType == Empty) type = StringValue; else type = subType;
      value.stringValue = new String(settingValue);
    }

    /** Constructor for string and string subtype settings.  **/

    Setting(const String settingName, const String& settingValue, const ValueType subType = Empty)
      : name (settingName)
    {
      if (subType == Empty) type = StringValue; else type = subType;
      const char* cstr=settingValue.c_str();
      value.stringValue=new String(cstr);
    }

    /** Constructor for Note setting.  **/

    Setting(const String settingName, Note settingValue, const ValueType subType = Empty)
      : name (settingName)
    {
      if (subType == Empty) type = NoteValue; else type = subType;
      // Arrrg have to store note destructured;
      Pitch p=settingValue.pitch();
      Octave o=settingValue.octave();
      // FIXME: THIS ISNT SAFE
      value.intValue=(p<<16)+o;
    }

    /** Constructor for Ratio setting.  **/

   Setting(const String settingName, Ratio settingValue, const ValueType subType = Empty)
      : name (settingName)
    {
      if (subType == Empty) type = RatioValue; else type = subType;
      // Arrrg have to store ratios destructured;
      int64 n=settingValue.num();
      // FIXME: THIS ISNT SAFE
      n=(n & 0xFFFFFFFF)<<32;
      n += settingValue.den();
      value.int64Value=n;
    }

    /** Setting destructor.  **/

   ~Setting()
    {
      if (getBasicType() == StringValue)
        if (value.stringValue != NULL)
          delete value.stringValue;
      }

    /** Returns the name of the setting. **/

    String getName()
    {
      return name;
    }

    /** Returns the value type of the setting. **/

    ValueType getType()
    {
      return type;
    }

    /** Returns the basic value type of the setting. **/

    ValueType getBasicType()
    {
      return (type & 0xF);
    }

    /** Returns true if the setting's type matches the type to check. **/

    bool isType(ValueType check)
    {
      return (type == check);
    }

    /** Returns true is setting is empty. **/

    bool isEmpty()
    {
      return (type == Empty);
    }

    /** Returns the bool value of setting. **/

    const bool getBoolValue()
    {
      return value.boolValue;
    }

    /** Returns the int value of setting. **/

    const int getIntValue()
    {
      return value.intValue;
    }

    /** Returns the int64 value of setting. **/

    const int64 getInt64Value()
    {
      return value.int64Value;
    }

    /** Returns the double value of setting. **/

    const double getDoubleValue()
    {
      return value.doubleValue;
    }

    /** Returns the String value of setting. **/

    const String& getStringValue()
    {
      return *(value.stringValue);
    }

    /** Returns the Meter value of setting. **/

    const Meter getMeterValue()
    {
      return (Meter)value.intValue;
    }

    /** Returns the Key value of setting. **/

    const Key getKeyValue()
    {
      return (Key)value.intValue;
    }

    /** Returns the Mark value of setting. **/

    const Mark getMarkValue()
    {
      return (Mark)value.intValue;
    }

   /** Returns the Note value of setting. **/

    Note getNoteValue()
    {
      // FIXME: WARNING THIS ISNT SAFE
      int32 v=value.intValue;
      Octave o = (v & 0xffff);
      v = (v >> 16);
      Pitch p = v;
      return Note(p, o);
    }

    /** Returns the Ratio value of setting. **/

    Ratio getRatioValue()
    {
      // FIXME: WARNING THIS ISNT SAFE
      int64 v=value.int64Value;
      int32 d = (v & 0xffffffff);
      v = (v >> 32);
      int32 n = v;
      return Ratio(n,d);
    }

    /** Returns a string xml representation of a setting.  **/

    const String toXmlString()
    {
      String str ("<setting name='");
      str += getName();
      str += "' type='";
      str += valueTypeToString(getType());
      str += "'>";
      switch (getType())
        {
        case Setting::BoolValue: 
          str += String::boolToString(getBoolValue());
          break;
        case Setting::IntValue:
          str += String::intToString(getIntValue());
          break;
        case Setting::DoubleValue:
          str += String::doubleToString(getDoubleValue());
          break;
        case Setting::StringValue: 
          str += getStringValue();
          break;
        case Setting::NoteValue:
          str += getNoteValue().toString();
          break;
        case Setting::RatioValue:
          str += getRatioValue().toString();
          break;
        case Setting::MarkValue:
          str += Marks::toString(getMarkValue());
          break;
        case Setting::KeyValue:
          str += Keys::toString(getKeyValue());
          break;
        case Setting::MeterValue:
          str += Meters::toString(getMeterValue());
          break;
        default:
          return "";
        }
      str += "</setting>";
      return str;
    }

    /** Returns a Lisp representation of a setting.  **/

    const String toLispString()
    {
      String str ("(");
      str += getName();
      //      str += "\" type ";
      //      str += valueTypeToString(getType());
      str += " ";
      switch (getType())
      {
      case Setting::BoolValue: 
        str += ((getBoolValue()) ? "#t" : "#f");
        break;
      case Setting::IntValue:
        str += String::intToString(getIntValue());
        break;
      case Setting::DoubleValue:
        str += String::doubleToString(getDoubleValue());
        break;
      case Setting::StringValue:
        str += "\"";
        str += getStringValue();
        str += "\"";
        break;
      case Setting::NoteValue:
        str += getNoteValue().toString().toLowerCase();
        break;
      case Setting::RatioValue:
        str += getRatioValue().toString();
        break;
      case Setting::MarkValue:
        str += Marks::toString(getMarkValue()).toLowerCase();
        break;
      case Setting::KeyValue:
        str += Keys::toString(getKeyValue()).toLowerCase();
        break;
      case Setting::MeterValue:
        str += Meters::toString(getMeterValue()).toLowerCase().replaceChar('/', ' ');
        break;
      default:
        return "";
      }
      str += ")";
      return str;
    }

  };

  /** Settings maintains a sets of properties that scores and other
      objects can use to hold a set of preferences or "default"
      values.  **/

  class Settings
  {

  private:

    menc::Array<Setting*> settings;

  public:

    /** Settings constructor. **/

    Settings() { }

    /** Settings destructor. **/

    ~Settings()
    {
      settings.clearWithDelete();
    }

    /** Clears all the settings currenly defined. **/

    void clearAllSettings ()
    {
      settings.clearWithDelete();
    }

    /** Returns the number of settings defined. **/

    const int numSettings()
    {
      return settings.size();
    }

    /** Adds a new setting. Once added a setting belongs to Settings and
        should not be deleted. **/

    void addSetting(Setting* set)
    {
      settings.add(set);
    }

    /** Returns the setting with name, or NULL if one does not exist. **/

    Setting* getSetting(const int index)
    {
      if ((index >= 0) && (index < numSettings()))
        return settings.getUnchecked(index);
      return NULL;
    }

    /** Returns the setting with name, or NULL if one does not exist. **/

    Setting* findSetting(const String name)
    {
      for (int i=0; i<numSettings(); i++)
        if (settings.getUnchecked(i)->getName() == name)
          return settings.getUnchecked(i);
      std::cout << "WARNING: failed to find setting '" << name << "'.\n";
      return NULL;
    }

/*=======================================================================*
  Not sure if the rest of these should be provided or not...if we want
  the ablilty to access default values for non-existing settings then
  here they are!
 *=======================================================================*/

#if 0

    /** Return the bool value of setting with name or the default
        value if the setting does not exist. **/

    const bool getBoolValue(String settingName, bool defaultValue=false)
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getBoolValue() : defaultValue;
    }

    /** Return the int value of setting with name or the default
        value if the setting does not exist. **/

    const int getIntValue(String settingName, int defaultValue=0)
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getIntValue() : defaultValue;
    }

    /** Return the int64 value of setting with name or the default
        value if the setting does not exist. **/

    const int64 getInt64Value(String settingName, int64 defaultValue=0)
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getInt64Value() : defaultValue;
    }

    /** Return the double value of setting with name or the default
        value if the setting does not exist. **/

    const double getDoubleValue(String settingName, double defaultValue=0.0)
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getDoubleValue() : defaultValue;
    }

    /** Return the meter value of setting with name or the default
        value if the setting does not exist. **/

    const Meter getMeterValue(String settingName, Meter defaultValue=Meters::Empty)
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getMeterValue() : defaultValue;
    }

    /** Return the key value of setting with name or the default
        value if the setting does not exist. **/

    const Key getKeyValue(String settingName, Key defaultValue=Keys::Empty)
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getKeyValue() : defaultValue;
    }

    const String getStringValue(String settingName, String defaultValue="")
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getStringValue() : defaultValue;
    }

    /** Return the key value of setting with name or the default
        value if the setting does not exist. **/

    Note getNoteValue(String settingName, Note defaultValue=Note(true))
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getNoteValue() : defaultValue;
    }

    /** Return the ratio value of setting with name or the default
        value if the setting does not exist. **/

    Ratio getRatioValue(String settingName, Ratio defaultValue=Ratio())
    {
      Setting* s=findSetting(settingName);
      return (s != NULL) ? s->getRatioValue() : defaultValue;
    }

#endif

  };

}

#endif

