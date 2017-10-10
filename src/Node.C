#include "Node.H"

dom::Node::Node(const std::string& name, short type) : nodeImpl(new dom::Node_Impl(name, type)) {}
dom::Node::~Node() {delete nodeImpl;}
void dom::Node::serialize(std::fstream * writer, WhitespaceStrategy * whitespace) {nodeImpl->serialize(writer, whitespace); }

const std::string &	dom::Node::getNodeName(void) {nodeImpl->getNodeName(); }
const std::string &	dom::Node::getNodeValue(void) {nodeImpl->getNodeValue(); }
void			dom::Node::setNodeValue(const std::string & nodeValue) {nodeImpl->setNodeValue(nodeValue); }
short			dom::Node::getNodeType(void) {nodeImpl->getNodeType(); }
dom::Node *			dom::Node::getParentNode(void) {nodeImpl->getParentNode(); }
dom::NodeList *		dom::Node::getChildNodes(void) {nodeImpl->getChildNodes(); }
dom::Node *			dom::Node::getFirstChild(void) {nodeImpl->getFirstChild(); }
dom::Node *			dom::Node::getLastChild(void) {nodeImpl->getLastChild(); }
dom::Node *			dom::Node::getPreviousSibling(void) {nodeImpl->getPreviousSibling(); }
dom::Node *			dom::Node::getNextSibling(void) {nodeImpl->getNextSibling(); }
dom::Document *		dom::Node::getOwnerDocument(void) {nodeImpl->getOwnerDocument(); }
dom::Node *			dom::Node::insertBefore(Node * newChild, Node * refChild) {nodeImpl->insertBefore(newChild, refChild); }
dom::Node *			dom::Node::replaceChild(Node * newChild, Node * oldChild) {nodeImpl->replaceChild(newChild, oldChild); }
dom::Node *			dom::Node::removeChild(Node * oldChild) {nodeImpl->removeChild(oldChild); }
dom::Node *			dom::Node::appendChild(Node * newChild) {nodeImpl->appendChild(newChild); }
bool			dom::Node::hasChildNodes(void) {nodeImpl->hasChildNodes(); }
const std::string &	dom::Node::getLocalName(void) {nodeImpl->getLocalName(); }

dom::Node_Impl::Node_Impl(const std::string & n, short type) : name(n), nodeType(type), parent(0), document(0)
{
	this->name	= name;
	nodeType	= type;
}

dom::Node_Impl::~Node_Impl()
{
}

const std::string &	dom::Node_Impl::getNodeName(void)
{
	return name;
}

const std::string &	dom::Node_Impl::getNodeValue(void)
{
	return value;
}

void			dom::Node_Impl::setNodeValue(const std::string & nodeValue)
{
	value	= nodeValue;
}

short			dom::Node_Impl::getNodeType(void)
{
	return nodeType;
}

dom::Node *		dom::Node_Impl::getParentNode(void)
{
	return parent;
}

dom::NodeList *		dom::Node_Impl::getChildNodes(void)
{
	return &nodes;
}

dom::Node *		dom::Node_Impl::getFirstChild(void)
{
	return *nodes.begin();
}

dom::Node *		dom::Node_Impl::getLastChild(void)
{
	return *(--nodes.end());
}

dom::Node *		dom::Node_Impl::getPreviousSibling(void)
{
	return getSibling(-1);
}

dom::Node *		dom::Node_Impl::getNextSibling(void)
{
	return getSibling(1);
}

dom::Document *		dom::Node_Impl::getOwnerDocument(void)
{
	return document;
}

dom::Node *		dom::Node_Impl::insertBefore(dom::Node * newChild, dom::Node * refChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	if (refChild == 0)
	{
		nodes.push_back(newChild);
		(dynamic_cast<Node_Impl *>(newChild))->setParent(this->getParentNode());
		return newChild;
	}

	dom::NodeList::iterator	index	= nodes.find(refChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Reference Child is not a child of this node.");

	nodes.insert(++index, newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this->getParentNode());

	return newChild;
}

dom::Node *		dom::Node_Impl::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	nodes.insert(index, newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this->getParentNode());
	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		dom::Node_Impl::removeChild(dom::Node * oldChild)
{
	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		dom::Node_Impl::appendChild(dom::Node * newChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		newChild->getParentNode()->removeChild(newChild);

	nodes.push_back(newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this->getParentNode());

	return newChild;
}

bool			dom::Node_Impl::hasChildNodes(void)
{
	return nodes.size() > 0;
}

const std::string &	dom::Node_Impl::getLocalName(void)
{
	return name;
}

void dom::Node_Impl::setParent(dom::Node * parent)
{
	this->parent	= parent;
}

dom::Node *		dom::Node_Impl::getSibling(int direction)
{
	if (parent == 0)
		return 0;

	dom::NodeList::iterator	i	= parent->getChildNodes()->find(this->getParentNode());

	if (direction < 0)
	{
		if (i == parent->getChildNodes()->begin())
			return 0;
		else
			return *(--i);
	}
	else
	{
		i++;

		if (i == parent->getChildNodes()->end())
			return 0;
		else
			return *i;
	}
}
