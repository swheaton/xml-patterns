#include "Attr.H"
#include "Visitor.H"

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

void Attr_Impl::Accept(Visitor * visitor)
{
	visitor->VisitAttribute(this);
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

dom::Node * Attr_Impl::cloneNode(bool deep)
{
	return new Attr_Impl(getName(), getValue(), getOwnerDocument());
}
