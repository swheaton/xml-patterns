#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "Attr.H"
#include "NodeList.H"
#include "XMLValidator.H"

Document_Impl::Document_Impl(void) : Node_Impl("", dom::Node::DOCUMENT_NODE)
{
	Node_Impl::document	= this;
}

Document_Impl::~Document_Impl() {}

void Document_Impl::serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
{
	*writer << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
	whitespace->newLine(writer);
	getDocumentElement()->serialize(writer, whitespace);
}

dom::Element *	Document_Impl::createElement(const std::string & tagName)
{
	return new Element_Impl(tagName, this);
}

dom::Text *	Document_Impl::createTextNode(const std::string & data)
{
	return new Text_Impl(data, this);
}

dom::Attr *	Document_Impl::createAttribute(const std::string & name)
{
	return new Attr_Impl(name, this);
}

dom::Element * Document_Impl::getDocumentElement()
{
	for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
		if (dynamic_cast<dom::Element *>(*i.operator->()) != 0)
			return dynamic_cast<dom::Element *>(*i.operator->());

	return 0;
}

DocumentValidator::DocumentValidator(dom::Document * _parent, XMLValidator * xmlValidator) :
  Node_Impl("", dom::Node::DOCUMENT_NODE),
  parent(_parent)
{
	schemaElement	= *xmlValidator->findSchemaElement("");
}

dom::Node * DocumentValidator::insertBefore(dom::Node * newChild, dom::Node * refChild)
{
	if (schemaElement == 0 || schemaElement->childIsValid(newChild->getNodeName(), false))
		return parent->insertBefore(newChild, refChild);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid root node " + newChild->getNodeName() + ".");
}

dom::Node * DocumentValidator::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	if (schemaElement == 0 || schemaElement->childIsValid(newChild->getNodeName(), false))
		return parent->replaceChild(newChild, oldChild);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid root node " + newChild->getNodeName() + ".");
}

dom::Node * DocumentValidator::appendChild(dom::Node * newChild)
{
	if (schemaElement == 0 || schemaElement->childIsValid(newChild->getNodeName(), false))
		return parent->appendChild(newChild);
	else
		throw dom::DOMException(dom::DOMException::VALIDATION_ERR, "Invalid root node " + newChild->getNodeName() + ".");
}
