#include "Element.H"
#include "Attr.H"
#include "Text.H"
#include "Document.H"
#include "XMLValidator.H"

#include <iostream>
#include <ios>

Element_Impl::Element_Impl(const std::string & tagName, dom::Document * document) : Node_Impl(tagName, dom::Node::ELEMENT_NODE),
  attributes(document)
{
	Node_Impl::document	= document;
}

Element_Impl::~Element_Impl()
{
}

const std::string &	Element_Impl::getAttribute(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
			return attr->getValue();
	}

	static const std::string	empty_string("");
	return empty_string;
}

dom::Attr *		Element_Impl::getAttributeNode(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
			return attr;
	}

	return 0;
}

dom::NodeList *		Element_Impl::getElementsByTagName(const std::string & tagName)
{
	dom::NodeList *	nodeList	= new dom::NodeList();

	for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
	{
		dom::Element *	element;

		if ((element = dynamic_cast<dom::Element *>(*i.operator->())) && element->getTagName().compare(tagName)==0)
			nodeList->push_back(*i.operator->());
	}

	return nodeList;
}

const std::string &	Element_Impl::getTagName(void)
{
	return getNodeName();
}

bool			Element_Impl::hasAttribute(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
			return true;
	}

	return false;
}

void			Element_Impl::removeAttribute(const std::string & name)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
		{
			attributes.erase(i);
			return;
		}
	}
}

dom::Attr *		Element_Impl::removeAttributeNode(dom::Attr * oldAttr)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
		if (*i.operator->() == oldAttr)
		{
			dom::Attr *	attribute	= (dom::Attr *)i.operator->();
			attributes.erase(i);
			return attribute;
		}

	throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Attribute not found.");
}

void			Element_Impl::setAttribute(const std::string & name, const std::string & value)
{
	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
	{
		dom::Attr * attr = dynamic_cast<dom::Attr *>(*i.operator->());

		if (attr->getName().compare(name) == 0)
		{
			attr->setValue(value);
			return;
		}
	}

	dom::Attr *	attribute;
	attributes.push_back(attribute = new Attr_Impl(name, value, dynamic_cast<Document_Impl *>(getOwnerDocument())));
	dynamic_cast<Node_Impl *>(dynamic_cast<Node *>(attribute))->setParent(this);
}

dom::Attr *		Element_Impl::setAttributeNode(dom::Attr * newAttr)
{
	if (newAttr->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "Attribute not created by this document.");

	if (newAttr->getParentNode() != 0)
		throw dom::DOMException(dom::DOMException::INUSE_ATTRIBUTE_ERR, "Attribute in use by other element.");

	dom::Attr *	oldAttribute	= 0;

	for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end(); i++)
		if (dynamic_cast<dom::Attr *>(*i)->getName().compare(newAttr->getName()) == 0)
		{
			oldAttribute	= (dom::Attr *)i.operator->();
			attributes.erase(i);
			break;
		}

	dynamic_cast<Node_Impl *>(dynamic_cast<Node *>(newAttr))->setParent(this);
	attributes.push_back(newAttr);
	return oldAttribute;
}

dom::Node * Element_Impl::cloneNode(bool deep)
{
	dom::Element *	element	= new Element_Impl(getTagName(), getOwnerDocument());

	if (deep)
	{
		dom::NodeList *	children	= getChildNodes();

		for (dom::NodeList::iterator i = children->begin(); i != children->end(); i++)
			element->appendChild((*i)->cloneNode(deep));

		for (dom::NamedNodeMap::iterator i = attributes.begin(); i != attributes.end(); i++)
			element->setAttributeNode(dynamic_cast<dom::Attr *>((*i)->cloneNode(deep)));
	}

	return element;
}

dom::Node * ElementValidator::cloneNode(bool deep)
{
	return new ElementValidator(dynamic_cast<dom::Element *>(parent->cloneNode(deep)), schemaElement);
}

dom::Node * ElementProxy::cloneNode(bool deep)
{
	ElementProxy *	temp	= new ElementProxy(dynamic_cast<dom::Element *>(realSubject->cloneNode(deep)), director);
	temp->realize();
	return temp;
}

ElementValidator::ElementValidator(dom::Element * _parent, XMLValidator * xmlValidator) :
  Node_Impl("", dom::Node::ELEMENT_NODE),
  parent(_parent)
{
	schemaElement	= *xmlValidator->findSchemaElement(parent->getTagName());
}

void ElementValidator::setAttribute(const std::string & name, const std::string & value)
{
	if (schemaElement == 0 || schemaElement->childIsValid(name, true))
		parent->setAttribute(name, value);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid attribute " + name + ".");
}

dom::Attr * ElementValidator::setAttributeNode(dom::Attr * newAttr)
{
	if (schemaElement == 0 || schemaElement->childIsValid(newAttr->getName(), true))
		parent->setAttributeNode(newAttr);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid attribute " + newAttr->getName() + ".");
}

dom::Node * ElementValidator::insertBefore(dom::Node * newChild, dom::Node * refChild)
{
	if (schemaElement == 0 || dynamic_cast<dom::Text *>(newChild) != 0 ||
	  schemaElement->childIsValid(newChild->getNodeName(), false))
		return parent->insertBefore(newChild, refChild);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid child node " + newChild->getNodeName() + ".");
}

dom::Node * ElementValidator::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	if (schemaElement == 0 || dynamic_cast<dom::Text *>(newChild) != 0 ||
	  schemaElement->childIsValid(newChild->getNodeName(), false))
		return parent->replaceChild(newChild, oldChild);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid child node " + newChild->getNodeName() + ".");
}

dom::Node * ElementValidator::appendChild(dom::Node * newChild)
{
	if (schemaElement == 0 || dynamic_cast<dom::Text *>(newChild) != 0 ||
	  schemaElement->childIsValid(newChild->getNodeName(), false))
		return parent->appendChild(newChild);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid child node " + newChild->getNodeName() + ".");
}

void ElementProxy::realize(void)
{
	// Realize by parsing child nodes.
	realized	= true;
}

dom::NodeList * ElementProxy::getChildNodes(void)
{
	if (!realized)
		realize();

	return realSubject->getChildNodes();
}

dom::Node * ElementProxy::getFirstChild(void)
{
	if (!realized)
		realize();

	return realSubject->getFirstChild();
}

dom::Node * ElementProxy::getLastChild(void)
{
	if (!realized)
		realize();

	return realSubject->getLastChild();
}

bool ElementProxy::hasChildNodes(void)
{
	if (!realized)
		realize();

	return realSubject->hasChildNodes();
}

void Element_Impl::HandleRequest(std::string & event)
{
	const std::string	eventTemplate	= getAttribute("message");

	if (eventTemplate == event)
		std::cout << "Handling event " << event << "." << std::endl;
	else if (getParentNode() != 0 && dynamic_cast<dom::Element *>(getParentNode()) != 0)
		dynamic_cast<dom::Element *>(getParentNode())->HandleRequest(event);
	else
		std::cout << "Reached root of DOM tree without handling event '" << event << "'." << std::endl;
}
