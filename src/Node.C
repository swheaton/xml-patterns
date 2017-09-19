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
	return *nodes.begin();
}

dom::Node *		Node_Impl::getLastChild(void)
{
	return *(--nodes.end());
}

dom::Node *		Node_Impl::getPreviousSibling(void)
{
	return getSibling(-1);
}

dom::Node *		Node_Impl::getNextSibling(void)
{
	return getSibling(1);
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

dom::Node *		Node_Impl::getSibling(int direction)
{
	if (parent == 0)
		return 0;

	dom::NodeList::iterator	i	= parent->getChildNodes()->find(this);

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

// ChildNodeIterator implementation follows
dom::NodeIterator* Node_Impl::createChildIterator()
{
	return new ChildNodeIterator(this);
}

ChildNodeIterator::ChildNodeIterator(dom::Node* node)
{
	// We actually want to start iteration at first element after passed-in node
	currNode = node;
	this->next();
}
void ChildNodeIterator::next()
{
	// Already at end, don't seg fault!
	if (this->currNode == 0)
	{
		return;
	}
	
	// Yes, the logic is a bit more complicated than maybe it needs to be, but
	//	this way I don't need stack storage, just the current Node pointer.
	dom::Node* nextNode = this->currNode;

	// goUpTree is true if we need to go up the tree at a lower node to see if
	//	the parents have any siblings
	bool goUpTree = false, first = true;
	while (first || goUpTree)
	{
		first = false;
		// Go to children first - but don't go back down to children if we just
		//	came from there due to goUpTree
		if (first && this->currNode->hasChildNodes())
		{
			this->currNode = nextNode->getFirstChild();
			goUpTree = false;
		}
		// Then, go to next sibling
		else if (nextNode = nextNode->getNextSibling())
		{
			this->currNode = nextNode;
			goUpTree = false;
		}
		// Then, go back up to parent before deciding that we're done.
		else if (nextNode = nextNode->getParentNode())
		{
			goUpTree = true;
		}
		// Got all the way here, this must be the end of the line.
		else
		{
			goUpTree = false;
			this->currNode = nullptr;
		}
	}
}

bool ChildNodeIterator::isDone() const
{
	return this->currNode == nullptr;
}

dom::Node* ChildNodeIterator::currentItem() const
{
	return this->currNode;
}