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

// Re-implemented child management functions for Composite pattern
dom::Node *		Document_Impl::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	nodes.insert(index, newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);
	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		Document_Impl::removeChild(dom::Node * oldChild)
{
	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		Document_Impl::appendChild(dom::Node * newChild)
{
	// Already has child, can't have another one
	if (this->hasChildNodes())
		throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Document can't have more than one child");
	
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	nodes.push_back(newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);

	return newChild;
}