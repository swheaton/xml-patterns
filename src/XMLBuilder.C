#include "XMLBuilder.H"
#include "XMLTokenizer.H"
#include "ElementProxy.H"

XMLBuilder* XMLBuilder::_instance = 0;
XMLBuilder* XMLBuilder::getInstance()
{
	if (_instance == 0)
	{
		_instance = new XMLBuilder;
	}
	return _instance;
}

XMLBuilder::XMLBuilder()
{
	this->domFactory = new Document_Impl;
}

dom::Document * XMLBuilder::beginDocument()
{
	Document_Impl * newDocument = new Document_Impl;
	// We have a document, now make it the concrete factory!
	this->domFactory = newDocument;
	return newDocument;
}

dom::Element * XMLBuilder::addElement(dom::Element * element, std::string elementName, const std::string& fileName, int fileOffset)
{
	dom::Element * newElt = domFactory->createElement(elementName);
	dom::Element* newElement = new ElementProxy(newElt, fileName, fileOffset);
	element->appendChild(newElement);
	return newElement;
}

dom::Element * XMLBuilder::addElement(dom::Document * document, std::string elementName, const std::string& fileName, int fileOffset)
{
	dom::Element* newElement = new ElementProxy(domFactory->createElement(elementName), fileName, fileOffset);
	document->appendChild(newElement);
	return newElement;
}
dom::Attr * XMLBuilder::addAttribute(dom::Element * element, std::string attrName, std::string attrValue)
{
	dom::Attr* newAttribute = domFactory->createAttribute(attrName);
	newAttribute->setValue(attrValue);
	element->setAttributeNode(newAttribute);
	return newAttribute;
}
dom::Text * XMLBuilder::addText(dom::Element * element, std::string text)
{
	dom::Text* newText = domFactory->createTextNode(text);
	element->appendChild(newText);
	return newText;
}