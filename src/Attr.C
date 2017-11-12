#include "Attr.H"
#include "Document.H"

Attr_Impl::Attr_Impl(const std::string & tagName, dom::Document * document) : Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	Node_Impl::document	= document;
}

Attr_Impl::Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document) :
  Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	Node_Impl::document	= document;
	setValue(value);
}

Attr_Impl::~Attr_Impl() {}

void Attr_Impl::serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
{
	*writer << " " << getName() << "=\"" << getValue() << "\"";
}

const std::string &	Attr_Impl::getName(void)
{
	return Node_Impl::getNodeName();
}

const std::string &	Attr_Impl::getValue(void)
{
	return Node_Impl::getNodeValue();
}

void			Attr_Impl::setValue(const std::string & value)
{
	Node_Impl::setNodeValue(value);
}

dom::Element *		Attr_Impl::getOwnerElement(void)
{
	return (dom::Element *)Node_Impl::getParentNode();
}

dom::Node * Attr_Impl::clone()
{
	if (getOwnerDocument() == 0)
	{
		return 0;
	}
	cloneWithFactory(getOwnerDocument());
}

dom::Node* Attr_Impl::cloneWithFactory(dom::Document* factory)
{
	dom::Attr* newAttribute = factory->createAttribute(getName());
	newAttribute->setValue(getValue());
	return newAttribute;
}
