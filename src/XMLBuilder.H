#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include "Node.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

// Abstract Builder that provides default blank implementations of useful build
//	functions for creating an XML DOM tree
class XMLBuilder
{
public:
  	virtual dom::Document * beginDocument() {}
	virtual dom::Element * addElement(dom::Element * element, std::string elementName) {}
	virtual dom::Element * addElement(dom::Document * document, std::string elementName) {}
	virtual dom::Attr * addAttribute(dom::Element * element, std::string attrName, std::string attrValue) {}
	virtual dom::Text * addText(dom::Element * element, std::string text) {}
  
protected:
	dom::AbstractDOMFactory * domFactory;
};

// ConcreteBuilder that can be used to build a DOM tree
class DefaultXMLBuilder : public XMLBuilder
{
public:
	// Concrete DOM factory we'll use is Document_Impl
	DefaultXMLBuilder();
	virtual dom::Document * beginDocument();
	virtual dom::Element * addElement(dom::Element * element, std::string elementName);
	virtual dom::Element * addElement(dom::Document * document, std::string elementName);
	virtual dom::Attr * addAttribute(dom::Element * element, std::string attrName, std::string attrValue);
	virtual dom::Text * addText(dom::Element * element, std::string text);
};

// Director for XML Parsing and DOM building. Uses builder passed to it
class XMLParseDirector
{
private:
  XMLBuilder * builder;
public:
  XMLParseDirector(XMLBuilder* builder) : 
    builder(builder) {}
  ~XMLParseDirector() {if (builder != 0) delete builder;}

  dom::Document * parseFile(std::string fileName);
};
#endif // XML_BUILDER_H
