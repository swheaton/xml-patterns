#ifndef ELEMENT_PROXY_H
#define ELEMENT_PROXY_H

#include "Node.H"
#include "XMLBuilder.H"
#include "Element.H"

class ElementProxy : public virtual dom::Element, public virtual Node_Impl
{
private:
	dom::Element *	parent;
	int offset;
	std::string fileName;
	
	virtual void loadChildren();
public:
	ElementProxy(dom::Element * _parent, std::string _fileName, int _offset) :
	    Node_Impl("", dom::Node::ELEMENT_NODE),
	    parent(_parent),
	    fileName(_fileName),
	    offset(_offset) {}

	//
	// Serialization Data Extraction Strategy
	//
	virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
	  { parent->serialize(writer, whitespace); }

	//
	// pass-through methods.
	//
	virtual const std::string &	getAttribute(const std::string & name)		{ return parent->getAttribute(name); }
	virtual dom::Attr *		getAttributeNode(const std::string & name)	{ return parent->getAttributeNode(name); }
	virtual dom::NodeList *		getElementsByTagName(const std::string & tagName)
	  { return parent->getElementsByTagName(tagName); }
	virtual const std::string &	getTagName(void)				{ return parent->getTagName(); }
	virtual bool			hasAttribute(const std::string & name)		{ return parent->hasAttribute(name); }
	virtual void			removeAttribute(const std::string & name)	{ parent->removeAttribute(name); }
	virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr) { return parent->removeAttributeNode(oldAttr); }
	virtual void			setAttribute(const std::string & name, const std::string & value) { return parent->setAttribute(name, value); }
	virtual dom::Attr *		setAttributeNode(dom::Attr * newAttr) { return parent->setAttributeNode(newAttr); }

	//
	// Proxy Methods - need to load children before getting children
	//
	virtual bool			hasChildNodes(void)				{ loadChildren(); return parent->hasChildNodes(); }
	virtual dom::Node *		appendChild(dom::Node * newChild) {loadChildren(); return parent->appendChild(newChild); }
	virtual dom::NodeList *		getChildNodes(void)				{ loadChildren(); return parent->getChildNodes(); }
	virtual dom::Node *		getFirstChild(void)				{ loadChildren(); return parent->getFirstChild(); }
	virtual dom::Node *		getLastChild(void)				{ loadChildren(); return parent->getLastChild(); }

	//
	// Reimplemented Node members
	//
	virtual dom::NamedNodeMap *	getAttributes(void)				{ return parent->getAttributes(); }
	virtual bool			hasAttributes(void)				{ return parent->hasAttributes(); }
	virtual const std::string &	getNodeName(void)				{ return parent->getNodeName(); }
	virtual const std::string &	getNodeValue(void)				{ return parent->getNodeValue(); }
	virtual void			setNodeValue(const std::string & nodeValue)	{ parent->setNodeValue(nodeValue); }
	virtual short			getNodeType(void)				{ return parent->getNodeType(); }
	virtual dom::Node *		getParentNode(void)				{ return parent->getParentNode(); }
	virtual dom::Node *		getPreviousSibling(void)			{ return parent->getPreviousSibling(); }
	virtual dom::Node *		getNextSibling(void)				{ return parent->getNextSibling(); }
	virtual dom::Document *		getOwnerDocument(void)				{ return parent->getOwnerDocument(); }
	virtual dom::Node *		removeChild(Node * oldChild)			{ return parent->removeChild(oldChild); }
	virtual const std::string &	getLocalName(void)				{ return parent->getLocalName(); }
	virtual dom::Node *		insertBefore(dom::Node * newChild, dom::Node * refChild) {return parent->insertBefore(newChild, refChild); }
	virtual dom::Node *		replaceChild(dom::Node * newChild, dom::Node * oldChild) {return parent->replaceChild(newChild, oldChild);}
};

#endif
