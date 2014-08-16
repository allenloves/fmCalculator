/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef coremusic_Xerces_h
#define coremusic_Xerces_h

/*=======================================================================*
      This file is only included if --xerces build option is specified!
 *=======================================================================*/

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/XMLChar.hpp>

namespace menc
{

  /** XercesXmlDocument handles validating and loading xml documents
      via Xerces. Use loadDocument() to load an xml document from a
      file or from an in-memory string. If loading is successful call
      getDocumentElement() to return the document's top element node
      else use getLastLoadError() to return the error message if
      loading failed. Note that you MUST call
      xercesc::XMLPlatformUtils::Initialize() in your main loop before
      you use this class. **/

  class XercesXmlDocument : public xercesc::DOMErrorHandler
  {

  protected:

    bool errorOccured;                /// set true if loading failed
    String xmlLoadErrorString;        /// possible resulting error string
    xercesc::DOMLSParser* parser;     /// interal parser for loading
    xercesc::DOMDocument *document;   /// the document element node on success
       
  public:

    /** XercesXmlDocument constructor **/

  XercesXmlDocument() 
    : errorOccured(false),
      xmlLoadErrorString(""),
      parser (NULL),
      document (NULL)
    {
    }
    
    /** XercesXmlDocument destructor **/

    virtual ~XercesXmlDocument()
    {
      clear();
    }
    
    /**  Clears document to empty state. An element pointer that was
         returned by loadDocumentElement() will now be invalid after
         this function is called. **/

    void clear()
    {
      xmlLoadErrorString.clear();
      errorOccured=false;
      if (parser) delete parser;
      document=NULL;
    }

    /**  Returns the XML document element on success, or NULL if the
         loading was unsuccessful. If an element is returned it is
         owned by the document's parser so never delete this node
         yourself.  If an error occured and no document element was
         returned then you can call getLastLoadError() to access the
         error text. **/

    xercesc::DOMElement* getDocumentElement() 
    {
      if (document)
        return document->getDocumentElement();
      else
        return NULL;
    }

    /** Returns true if an error occured during loading. **/

    bool getErrorOccured() const {return errorOccured;}

    /** Returns the error string associated with the last error **/

    String& lastLoadError() {return xmlLoadErrorString;}

    /** Optionally validates and then loads an xlm document. if isFile
        is true then source is a pathname to an xml file to
        load. Otherwise source is the actual xml string to load.
        Returns true if the document loads, otherwise false. If
        loading is successful then use getDocumentElement() to return
        the top document node from the document. Note that the
        XmlDocument owns this element so never delete it. **/

    bool loadDocument(String source, bool isFile, bool validate=true)
    {
      clear();
      XMLCh Xbuf [256];   // scratch buffer for transcoding short xerces strings.
      xercesc::XMLString::transcode("LS", Xbuf, 255);
      xercesc::DOMImplementation *impl = xercesc::DOMImplementationRegistry::getDOMImplementation(Xbuf);
      parser = ((xercesc::DOMImplementationLS*)impl)->createLSParser(xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, 0);
      
      if (parser->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMValidate, true))
        parser->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMValidate, validate);

      if (!validate)
      {
        // its not enough to turn off validate, you also have to turn off external dtd reading
        XMLCh Xnoload [256];   
        xercesc::XMLString::transcode("http://apache.org/xml/features/nonvalidating/load-external-dtd", Xnoload, 256);
        if (parser->getDomConfig()->canSetParameter(Xnoload, true))
          parser->getDomConfig()->setParameter(Xnoload, false);
      }

      if (parser->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMNamespaces, true))
        parser->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMNamespaces, true);
      if (parser->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMDatatypeNormalization, true))
        parser->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMDatatypeNormalization, true);
      if (parser->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMElementContentWhitespace, true))
        parser->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMElementContentWhitespace, false);
      
      // we ARE the error reporter...
      parser->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMErrorHandler, this); 
      xercesc::DOMLSInput* input = ((xercesc::DOMImplementationLS*)impl)->createLSInput();
      xercesc::LocalFileInputSource* fileSource = 0;   // XML source for file input
      xercesc::MemBufInputSource* memSource = 0;       // XML source for memory input
      
      if (isFile) // read input from file
      {
        xercesc::XMLString::transcode(source.c_str(), Xbuf, 255);
        fileSource = new xercesc::LocalFileInputSource(Xbuf);
        input->setByteStream(fileSource);
      }
      else // read input from string in memory
      {
        memSource = new xercesc::MemBufInputSource((const XMLByte*)source.c_str(),
                                                   static_cast<const XMLSize_t>(source.length()*sizeof(StringChar)),
                                                   "memxml",
                                                   false);
        input->setByteStream(memSource);
      }
      
      // validate and load the doc
      try
      {
        document = parser->parse(input);
      }
      catch (const xercesc::XMLException& toCatch)
      {
        String msg (xmlToString(toCatch.getMessage()));
        xmlLoadErrorString += "XML Exception: ";
        xmlLoadErrorString += msg;
        errorOccured=true;
      }
      catch (const xercesc::DOMException& toCatch)
      {
        String msg (xmlToString(toCatch.getMessage()));
        xmlLoadErrorString += "DOM Exception: ";
        xmlLoadErrorString += msg;
        errorOccured=true;
      }
      catch (...)
      {
        xmlLoadErrorString += "Caught unknown exception!\n" ;
        errorOccured=true;
      }
      
      if (errorOccured )
      {
        delete parser;
        parser=NULL;
        document=NULL;
      }
      // clean up temp stuctures
      if (isFile)
      {
        delete fileSource;
      }
      else
      {
        delete memSource;
      }
      delete input;

      return !errorOccured;
    }

    /** Searches for the first child element of parent that matches
        name or NULL if one is not found.  Name can also be a series
        of names separated by '/', in which case searching recurses on
        each element name until the last name is found or NULL is
        returned. **/

    static xercesc::DOMElement* findElement(xercesc::DOMElement* parent, menc::String path)
    {
      int more=path.indexOfChar('/'); // index of remainder of path or -1
      XMLCh nbuf [128];
      xercesc::DOMElement* node=NULL;        

      xercesc::XMLString::transcode(path.substring(0, more).c_str(), nbuf, 128);
      for (node=parent->getFirstElementChild(); node!=NULL; node=node->getNextElementSibling())
      {
        if (xercesc::XMLString::compareString(node->getTagName(), nbuf)==0)
          break;
      }
      // found a node, recurs if more in path else return the node
      if (node)
        if (more>-1)
          return findElement(node, path.substring(more+1));
        else
          return node;
      else
        return NULL;
    }

   static String getNodeName(xercesc::DOMNode* node)
    {
      //      const XMLCh* tmp=node->getNodeName();
      //menc::String name=xmlToString(tmp);
      //xercesc::XMLString::release(&tmp);   
      return ""; //name;
    }


    /** Return the text content of the specified element node. The
        node can be an element or an attribute. FIXME: THIS NEEDS TO
        DELETE THE TEMPORARY XMLCH **/

    static String getNodeText(xercesc::DOMNode* node)
    {
      XMLCh* tmp=(XMLCh*)node->getTextContent();
      menc::String str=xmlToString(tmp);
      //      xercesc::XMLString::release(&tmp);   
      return str;
    }

    /** Return the text content of the specified attribite of node. **/

    static String getAttributeText(xercesc::DOMElement* node, String attr)
    {
      XMLCh* tmp=xercesc::XMLString::transcode(attr.c_str());
      String str=xmlToString(node->getAttribute(tmp));
      xercesc::XMLString::release(&tmp);
      return str;
    }

    /** Translates a xerces string into a menc string. **/

    static String xmlToString(const XMLCh* xml)
    {
      char* raw = xercesc::XMLString::transcode(xml);
      String str (raw);
      xercesc::XMLString::release(&raw);
      return str;
    }

  private:

    /** internal handler that xerces calls whenever there is an xml
        validation error (these validation errors are not xerces
        exceptions) **/

    bool handleError(const xercesc::DOMError& err)
    {
      // ignore warnings
      if (err.getSeverity() == xercesc::DOMError::DOM_SEVERITY_WARNING)
        return true;
      errorOccured = true;
      String message = "XML Validation Error";
      xercesc::DOMLocator* loc=err.getLocation();
      if (loc!=NULL)
      {
        message += " (line ";
        message += loc->getLineNumber();
        message += ")";
      }
      message += ": ";
      message += xmlToString(err.getMessage());
      xmlLoadErrorString = message;
      return false;
    }
     
  };
  
}

#endif
