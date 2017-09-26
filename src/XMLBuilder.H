#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include "Node.H"

class XMLBuilder
{
public:
  virtual dom::Document * beginDocument() {}
  virtual void addElement(dom::Document *) {}
  virtual void addAttribute(dom::Element * element) {}
  
protected:
	dom::AbstractDOMFactory * domFactory;
};

class DefaultXMLBuilder : public XMLBuilder
{
public:
	// Concrete DOM factory we'll use is Document_Impl
	DefaultXMLBuilder()
	{
		this->domFactory = new Document_Impl;
	}

	~DefaultXMLBuilder()
	{
		if (domFactory != 0)
		{
			delete domFactory;
		}
	}
	virtual dom::Document * beginDocument()
	{
		return new Document_Impl;
	}
	
	virtual dom::Element * addElement(dom::Element * element, std::string elementName)
	{
		dom::Element* newElement = domFactory->createElement(elementName);
		element->appendChild(newElement);
		return newElement;
	}
	
	virtual dom::Element * addElement(dom::Document * document, std::string elementName)
	{
		dom::Element* newElement = domFactory->createElement(elementName);
		document->appendChild(newElement);
		return newElement;
	}
	virtual dom::Attr * addAttribute(dom::Element * element, std::string attrName, std::string attrValue)
	{
		dom::Attr* newAttribute = domFactory->createAttribute(attrName);
		newAttribute->setValue(attrValue);
		element->setAttributeNode(newAttribute);
		return newAttribute;
	}
	virtual dom::Text * addText(dom::Element * element, std::string text)
	{
		dom::Text* newText = domFactory->createTextNode(text);
		element->appendChild(newText);
		return newText;
	}
};

class XMLParseDirector
{
private:
  XMLBuilder * builder;
public:
  XMLParseDirector(XMLBuilder* builder) : 
    builder(builder) {}
  ~XMLParseDirector() {if (builder != 0) delete builder;}

  dom::Document * parseFile(std::string fileName)
  {
	  XMLTokenizer	tokenizer(fileName);

	  XMLTokenizer::XMLToken *	token	= 0;

	  do
	  {
		  if (token != 0)
		  {
			  delete	token;
		  }
		  token	= tokenizer.getNextToken();
		  std::string attrName = "";
		  switch (token->getTokenType())
		  {
			  case XMLTokenizer::XMLToken::NULL_TOKEN:
				  break;
			  case XMLTokenizer::XMLToken::PROLOG_START:
				  break;
			  case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
				  builder->beginDocument();
				  break;
			  case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
				  //builder->addAttribute(attrName, token->getToken());
				  //attrName = "";
				  break;
			  case XMLTokenizer::XMLToken::PROLOG_END:
				  break;
			  case XMLTokenizer::XMLToken::TAG_START:
				  break;
			  case XMLTokenizer::XMLToken::ELEMENT:
				  break;
			  case XMLTokenizer::XMLToken::ATTRIBUTE:
				  attrName = token->getToken();
				  break;				   				   				   				   				   				   				 	     					        
			  case XMLTokenizer::XMLToken::NULL_TAG_END:
				  break;
			  case XMLTokenizer::XMLToken::TAG_CLOSE_START:
				  break;
			  case XMLTokenizer::XMLToken::VALUE:
				  break;
			  case XMLTokenizer::XMLToken::TAG_END:
				  break;
			  default:
				  break;
		  }
	  } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);
	  delete	token;
	  return 0;
  };
};
#endif // XML_BUILDER_H
