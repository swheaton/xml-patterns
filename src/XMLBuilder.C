#include "XMLBuilder.H"
#include "XMLTokenizer.H"

DefaultXMLBuilder::DefaultXMLBuilder()
{
	this->domFactory = new Document_Impl;
}

dom::Document * DefaultXMLBuilder::beginDocument()
{
	Document_Impl * newDocument = new Document_Impl;
	// We have a document, now make it the concrete factory!
	this->domFactory = newDocument;
	return newDocument;
}

dom::Element * DefaultXMLBuilder::addElement(dom::Element * element, std::string elementName)
{
	dom::Element* newElement = domFactory->createElement(elementName);
	element->appendChild(newElement);
	return newElement;
}

dom::Element * DefaultXMLBuilder::addElement(dom::Document * document, std::string elementName)
{
	dom::Element* newElement = domFactory->createElement(elementName);
	document->appendChild(newElement);
	return newElement;
}
dom::Attr * DefaultXMLBuilder::addAttribute(dom::Element * element, std::string attrName, std::string attrValue)
{
	dom::Attr* newAttribute = domFactory->createAttribute(attrName);
	newAttribute->setValue(attrValue);
	element->setAttributeNode(newAttribute);
	return newAttribute;
}
dom::Text * DefaultXMLBuilder::addText(dom::Element * element, std::string text)
{
	dom::Text* newText = domFactory->createTextNode(text);
	element->appendChild(newText);
	return newText;
}

dom::Document * XMLParseDirector::parseFile(std::string fileName)
{
  XMLTokenizer	tokenizer(fileName);

  XMLTokenizer::XMLToken *	token	= 0;
  dom::Document * document = 0;
  dom::Element * currElt = 0;
  bool firstElt = false, tagCloseStart = false;
  std::string attrName = "";

  do
  {
	  if (token != 0)
	  {
		  delete	token;
	  }
	  token	= tokenizer.getNextToken();
	  
	  switch (token->getTokenType())
	  {
		  case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			if (currElt != 0)
			{
			  builder->addAttribute(currElt, attrName, token->getToken());
			  attrName = "";
			}
			  break;
		  case XMLTokenizer::XMLToken::PROLOG_END:
		  		document = builder->beginDocument();
		  		firstElt = true;
			  break;

		  case XMLTokenizer::XMLToken::ELEMENT:
			if (!tagCloseStart)
			{
				if (firstElt)
				{
					currElt = builder->addElement(document, token->getToken());
					firstElt = false;
				}
				else
				{
					currElt = builder->addElement(currElt, token->getToken());
				}
			}
			else
			{
				currElt = dynamic_cast<dom::Element*>(currElt->getParentNode());
			}
			  break;
		  case XMLTokenizer::XMLToken::ATTRIBUTE:
			  attrName = token->getToken();
			  break;				   				   				   				   				   				   				 	     					        
		  case XMLTokenizer::XMLToken::NULL_TAG_END:
			currElt = dynamic_cast<dom::Element*>(currElt->getParentNode());
			  break;
		  case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			tagCloseStart = true;
			  break;
		  case XMLTokenizer::XMLToken::VALUE:
			builder->addText(currElt, token->getToken());
			  break;
		  case XMLTokenizer::XMLToken::TAG_END:
			if (tagCloseStart)
				tagCloseStart = false;
			  break;
		  default:
			  break;
	  }
  } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);
  delete	token;
  return document;
}