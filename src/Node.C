#include "Node.H"

Node_Impl::Node_Impl(const std::string & n, short type) : name(n), nodeType(type), parent(0), document(0)
{
	this->name	= name;
	nodeType	= type;
}

Node_Impl::~Node_Impl()
{
}

const std::string &	Node_Impl::getNodeName(void)
{
	return name;
}

const std::string &	Node_Impl::getNodeValue(void)
{
	return value;
}

void			Node_Impl::setNodeValue(const std::string & nodeValue)
{
	value	= nodeValue;
}

short			Node_Impl::getNodeType(void)
{
	return nodeType;
}

dom::Node *		Node_Impl::getParentNode(void)
{
	return parent;
}

dom::NodeList *		Node_Impl::getChildNodes(void)
{
	return &nodes;
}

dom::Node *		Node_Impl::getFirstChild(void)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "getFirstChild() not allowed");

	return 0;
}

dom::Node *		Node_Impl::getLastChild(void)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "getLastChild() not allowed");

	return 0;
}

dom::Node *		Node_Impl::getPreviousSibling(void)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "getPreviousSibling() not allowed");

	return 0;
}

dom::Node *		Node_Impl::getNextSibling(void)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "getNextSibling() not allowed");

	return 0;
}

dom::Document *		Node_Impl::getOwnerDocument(void)
{
	return document;
}

dom::Node *		Node_Impl::insertBefore(dom::Node * newChild, dom::Node * refChild)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "insertBefore() not allowed");

	return newChild;
}

dom::Node *		Node_Impl::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "replaceChild() not allowed");

	return oldChild;
}

dom::Node *		Node_Impl::removeChild(dom::Node * oldChild)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "removeChild() not allowed");

	return 0;
}

dom::Node *		Node_Impl::appendChild(dom::Node * newChild)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "appendChild() not allowed");

	return 0;
}

bool			Node_Impl::hasChildNodes(void)
{
	return nodes.size() > 0;
}

const std::string &	Node_Impl::getLocalName(void)
{
	return name;
}

void Node_Impl::setParent(dom::Node * parent)
{
	this->parent	= parent;
}
