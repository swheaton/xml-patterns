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
	static XMLBuilder* getInstance();
  virtual dom::Document * beginDocument();
	virtual dom::Element * addElement(dom::Element * element, std::string elementName, const std::string& fileName, int beginOffset);
	virtual dom::Element * addElement(dom::Document * document, std::string elementName, const std::string& fileName, int beginOffset);
	virtual dom::Attr * addAttribute(dom::Element * element, std::string attrName, std::string attrValue);
	virtual dom::Text * addText(dom::Element * element, std::string text);

protected:
	XMLBuilder();

private:
	static XMLBuilder* _instance;
	dom::Document * domFactory;
};

#endif // XML_BUILDER_H
