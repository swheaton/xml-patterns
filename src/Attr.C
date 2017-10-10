#include "Attr.H"

dom::Attr::Attr(const std::string & tagName, dom::Document * document) : Node(tagName, dom::Node::ATTRIBUTE_NODE), attrImpl(new Attr_Impl(tagName, document)) {}
dom::Attr::Attr(const std::string & tagName, const std::string & value, dom::Document * document) : Node(tagName, dom::Node::ATTRIBUTE_NODE), attrImpl(new Attr_Impl(tagName, value, document)) {}

void dom::Attr::serialize(std::fstream * writer, WhitespaceStrategy * whitespace) {attrImpl->serialize(writer, whitespace); }

const std::string &	dom::Attr::getName(void) {attrImpl->getName(); }
const std::string &	dom::Attr::getValue(void) {attrImpl->getValue(); }
void			dom::Attr::setValue(const std::string & value) {attrImpl->setValue(value); }
dom::Element *		dom::Attr::getOwnerElement(void) {attrImpl->getOwnerElement(); }

dom::Attr_Impl::Attr_Impl(const std::string & tagName, dom::Document * document) : Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	Node_Impl::document	= document;
}

dom::Attr_Impl::Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document) :
  Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	Node_Impl::document	= document;
	setValue(value);
}

dom::Attr_Impl::~Attr_Impl() {}

void dom::Attr_Impl::serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
{
	*writer << " " << getName() << "=\"" << getValue() << "\"";
}

const std::string &	dom::Attr_Impl::getName(void)
{
	return Node_Impl::getNodeName();
}

const std::string &	dom::Attr_Impl::getValue(void)
{
	return Node_Impl::getNodeValue();
}

void			dom::Attr_Impl::setValue(const std::string & value)
{
	Node_Impl::setNodeValue(value);
}

dom::Element *		dom::Attr_Impl::getOwnerElement(void)
{
	return (dom::Element *)Node_Impl::getParentNode();
}
