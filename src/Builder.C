#include "Builder.H"
#include <iostream>

#include <ctype.h>
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void Builder::addValue(const std::string & text)
{
	std::string	trimmed	= trim(text);
	if (!notify(elementStack.top(), dom::Node::TEXT_NODE, trimmed))
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR,
		  "Invalid TEXT node '" + trimmed + "' for element " + elementStack.top()->getTagName() + ".");
	elementStack.top()->appendChild(static_cast<dom::Node *>(factory->createTextNode(trimmed)));
}

void Builder::confirmElement(const std::string & tag)
{
	// Throw an exception if trim(tag) != currentElement.getTagName()
}

void Builder::createAttribute(const std::string & attribute)
{
	std::string	trimmed	= trim(attribute);
	trimmed			= std::string(trimmed, 0, trimmed.size() - 1);
	if (currentElement != 0)	// Remove this check and let Observer handle null if we handle prolog attributes.
		if (!notify(currentElement, dom::Node::ATTRIBUTE_NODE, trimmed))
			throw dom::DOMException(dom::DOMException::VALIDATION_ERR,
			  "Invalid ATTRIBUTE node '" + trimmed + "' for element " + currentElement->getTagName() + ".");
	currentAttr	= factory->createAttribute(trimmed);
}

void Builder::createElement(const std::string & tag)
{
	std::string	trimmed	= trim(tag);
	if (!notify(elementStack.size() == 0 ? 0 : elementStack.top(), dom::Node::ELEMENT_NODE, trimmed))
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR,
		  "Invalid ELEMENT node '" + trimmed + "' for element " +
		  (elementStack.size() == 0 ? "root" : elementStack.top()->getTagName()) + ".");
	currentElement	= factory->createElement(trimmed);

	if (elementStack.size() == 0)	// This is the root element.
		factory->appendChild(currentElement);
	else
		elementStack.top()->appendChild(currentElement);
}

void Builder::createProlog(void)
{
	// null method in this implementation
}

void Builder::endProlog(void)
{
	// null method in this implementation
}

void Builder::identifyProlog(const std::string & id)
{
	// null method in this implementation
}

bool Builder::popElement(void)
{
	currentElement	= elementStack.top();
	elementStack.pop();
	return elementStack.size() > 0;
}

void Builder::pushElement(void)
{
	elementStack.push(currentElement);
	currentElement	= 0;
}

void Builder::valueAttribute(const std::string & value)
{
	std::string	trimmed	= trim(value);
	trimmed			= std::string(trimmed, 1, trimmed.size() - 2);
	if (!notify(currentAttr, dom::Node::ATTRIBUTE_NODE, trimmed))
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR,
		  "Invalid ATTRIBUTE VALUE '" + trimmed + "' for attribute " + currentAttr->getName() + ".");
	currentAttr->setValue(trimmed);

	if (currentElement != 0)	// Discard prolog attributes.  This implementation currently doesn't have
					// anything to do with them.
		currentElement->setAttributeNode(currentAttr);
}

const std::string Builder::trim(const std::string & s) const
{
	int	start_index;
	int	stop_index;

	for (start_index = 0; start_index < s.size() && isspace(s[start_index]); start_index++);
	for (stop_index = s.size() - 1; stop_index >= start_index && isspace(s[stop_index]); stop_index--);

	return std::string(s, start_index, stop_index - start_index + 1);
}
