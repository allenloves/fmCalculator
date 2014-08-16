/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef mencString_h
#define mencString_h

#include <string>

/** String is a lightweight string. This implementation uses
    basic_string and char. if you switch over to wstring then make
    sure you also update the StringChar typedef in mencTypes.h. **/

namespace menc
{
  struct String : public std::string
  {
    /*The following were taken from the (constructor), operator=, operator +=,
    and operator[] links at http://www.cplusplus.com/reference/string/string .
    They should duplicate the functionality of the std::string class exactly.*/
    
    //Constructors
    String() : std::string() {};
    String(const String& str) : std::string(str) {}
    String(const String& str, size_t pos, size_t n = npos) : 
      std::string(str, pos, n) {}
    String(const char* s, size_t n) : std::string(s, n) {}
    String(const char* s) : std::string(s) {};
    String(size_t n, char c) : std::string(n, c) {};
    
    //Operator =
    String& operator = (const String& str)
      {(*(std::string*)this) = (std::string)str; return *this;}
    String& operator = (const char* s) {*(std::string*)this = s; return *this;}
    String& operator = (char c) {*(std::string*)this = c; return *this;}
    
    //Operator +=
    String& operator += (const String& str)
      {(*(std::string*)this) += (std::string)str; return *this;}
    String& operator += (const char* s)
      {*(std::string*)this += s; return *this;}
    String& operator += (char c) {*(std::string*)this += c; return *this;}

    //Operator []
    const char& operator [] (size_t pos) const
      {return (*(std::string*)this)[pos];}
    char& operator [] (size_t pos) {return (*(std::string*)this)[pos];}
    
    const char* c(void) {return c_str();}
    
    //--------------------------------------------------------------------------
      
    ///Return true if the string is empty.
    bool isEmpty(void) const
    {
      return length() == 0;
    }

    ///Return true if the string is not empty.
    bool isNotEmpty(void) const
    {
      return !isEmpty();
    }

    ///Convert string to upper case version.
    String toUpperCase(void) const
    {
      String up(*this);
      for(unsigned int i = 0; i < up.length(); i++)
        up[i] = toupper(up[i]);
      return up;
    }

    ///Convert string to lower case version.
    String toLowerCase(void) const
    {
      String low(*this);
      for(unsigned int i = 0; i < low.length(); i++)
        low[i] = tolower(low[i]);
      return low;
    }

    ///Return true if two strings are the same.
    bool equals(const String other) const
    {
      return (compare(other) == 0);
    }

    ///Return true if two strings are the same ignoring case.
    bool equalsIgnoreCase(const String str2) const
    {
      #ifdef _MSC_VER //for Windows
        return stricmp(c_str(), str2.c_str()) == 0;
      #else //for everyone else
        return strcasecmp(c_str(), str2.c_str()) == 0;
      #endif
    }

    /** Returns a substring of a string, where start is starting position of the
    substring and end is its (exclusive) ending position. start defaults to the
    beginning of the string and end defaults to the end of string. **/

    String substring(int start = 0, int end = -1) const
    {
      if(end < 0)
        end = length();
      return substr(start, end - start).c_str();
    }

    ///Return true if string contains char (case sensitive).
    bool containsChar(const StringChar ch) const
    {
      return find(ch) != npos;
    }

    /// Return position of char in string or -1 if not found.
    int indexOfChar(const StringChar chr) const
    {
      size_t i=find(chr);
      return (i == npos) ? -1 : i;
    }

    ///Replace instances of char1 with char2.
    String replaceChar(StringChar char1, StringChar char2) const
    {
      String s(*this);
      for(size_t i = 0; i < s.length(); i++)
        if(s[i] == char1)
          s[i] = char2;
      return s;
    }

    ///Return true if string contains substring.
    bool contains(const String& sub) const
    {
      return find(sub) != npos;
    }

    /** Returns true if string starts with the substring to check. **/

    bool startsWith(const String& check) const
    {
      size_t len = check.length();
      if (len <= length())
        return (compare(0, len, check) == 0);
      else
        return false;
    }

    /** Returns true if string ends with the substring to check. **/

    bool endsWith(const String& check) const
    {
      size_t pos = length() - check.length();
      if (pos < length())
        return (compare(pos, check.length(), check) == 0);
      else
        return false;
    }

     ///Return true if string contains only characters in chars.
    bool containsOnlyChars(const String& chars, int pos = 0) const
    {
      for(size_t i = pos; i < length(); i++)
        if(!chars.containsChar(at(i)))
          return false;
      return true;
    }

    /// Return true if string contains any of the characters in chars.
    bool containsChars(const String& chars, int pos = 0) const
    {
      for (size_t i=pos; i<length(); i++)
        if (chars.containsChar(at(i))) return true;
      return false;
    }

    /// Return copy of string with any character in chars removed from copy.
    String removeChars(const String& chars) const
    {
      String newstr(*this);
      for (int i=length()-1; i>=0; i--)
        if (chars.containsChar(newstr[i]))
          newstr.erase(i,1);
      return newstr;
    }

    ///Add string quote chars to start and end of str.
    String quoted(void) const
    {
      String s = "\"";
      s += *this;
      s += "\"";
      return s;
    }

    ///Advance pos in string while characters are in chars.
    int advanceChars(const String& chars, int pos = 0) const
    {
      if(pos < 0)
        return pos;
      int len = length();
      if(pos >= len)
        return pos;
      while(pos < len && chars.containsChar(at(pos)))
        pos++;
      return pos;
    }

    ///Advance pos in string while characters are not in chars.
    int advanceNotChars(const String& chars, int pos = 0) const
    {
      if(pos < 0)
        return pos;
      int len = length();
      if(pos >= len)
        return pos;
      while(pos < len && (!chars.containsChar(at(pos))))
        pos++;
      return pos;
    }
    
    ///Parse string as an integer.

    int toInt()
    {
      return atoi(c_str());
    }

    ///Parse string as a floating point number.

    double toDouble()
    {
      return atof(c_str());
    }

    /** Return true if string is "true" "yes" "y" "1" otherwise false **/

    const bool toBool()
    {
      if ((*this == "true") || (*this == "yes") || (*this == "y") || (*this == "1"))
        return true;
      else if ((*this == "false") || (*this == "no") || (*this == "n") || (*this == "0"))
        return false;
      return false; // no way to return invald...
    }

   /// destructively remove any characters in white from the start and end of string.

    void trim(String white = " ")
    {
      int pos = length()-1;
      while (pos>=0 && white.containsChar(at(pos))) erase(pos--);
      while(length()>0 && white.containsChar(at(0))) erase(0,1);
    }

    /** Parses the next token from string begining at the start index
        and skipping past any introductory white space. If the
        function returns true then the reference parameter tok
        contains the next token and the reference parameter start is
        set to one position past the end of token.  If the function
        returns false then no token was encountered and the reference
        parameters are not assigned. **/

    bool parseToken(String& tok, int& start, const String white = " ")
    {
      int len=length();
      int pos=start;
      while (pos<len && white.containsChar(at(pos))) pos++;
      if (pos<len)
        {
          int beg=pos;
          while (pos<len && !white.containsChar(at(pos))) pos++;
          // end now on next white char after token or at len
          start=pos;
          tok=substring(beg,pos);
          return true;
        }
      return false;
    }

    //--------------------------------------------------------------------------
    
    //Static functions here...
    
    /** Return string representation of int. **/

    static String intToString(int number)
    {
      //More than enough space for decimal long with sign and null.
      StringChar buffer[32];
      snprintf(buffer, 32, "%d", number);
      return String(buffer);
    }

    /** Return string representation of double. **/

    static String doubleToString(double number)
    {
      //More than enough space for double with sign and null.
      StringChar buffer[64];
      snprintf(buffer, 64, "%g", number);
      return String(buffer);
    }

    /** Return string representation of bool. **/

    static String boolToString(bool value)
    {
      if (value) 
        return "true";
      else
        return "false";
    }

    ///Return true if character is a digit.
    static bool isDigitChar(StringChar ch)
    {
      return '0' <= ch && ch <= '9';
    }
  }; 
}
#endif
