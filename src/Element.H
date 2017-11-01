#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "Node.H"
#include "NamedNodeMap.H"
#include "ValidChildren.H"

namespace dom
{
	class Attr;
	class NodeList;
	class Document;

	class Element : public virtual Node
	{
	public:
		virtual ~Element() {}

		//
		// Chain of Responsibility
		//
		virtual void			HandleRequest(std::string & event)					= 0;

		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace)		= 0;

		virtual const std::string &	getAttribute(const std::string & name)					= 0;
		virtual Attr *			getAttributeNode(const std::string & name)				= 0;
		virtual NodeList *		getElementsByTagName(const std::string & tagName)			= 0;
		virtual const std::string &	getTagName(void)							= 0;
		virtual bool			hasAttribute(const std::string & name)					= 0;
		virtual void			removeAttribute(const std::string & name)				= 0;
		virtual Attr *			removeAttributeNode(Attr * oldAttr)					= 0;
		virtual void			setAttribute(const std::string & name, const std::string & value)	= 0;
		virtual Attr *			setAttributeNode(Attr * newAttr)					= 0;

		virtual dom::NamedNodeMap *	getAttributes(void)							= 0;
		virtual bool			hasAttributes(void)							= 0;
	};
};

class Element_Impl : public virtual dom::Element, Node_Impl
{
private:
	NamedNodeMap_Impl	attributes;
protected:
	Element_Impl(const std::string & tagName, dom::Document * document);
public:
	friend class Document_Impl;

	virtual ~Element_Impl();

	//
	// Chain of Responsibility
	//
	virtual void			HandleRequest(std::string & event);

	//
	// Serialization Data Extraction Strategy
	//
	virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace);

	virtual const std::string &	getAttribute(const std::string & name);
	virtual dom::Attr *		getAttributeNode(const std::string & name);
	virtual dom::NodeList *		getElementsByTagName(const std::string & tagName);
	virtual const std::string &	getTagName(void);
	virtual bool			hasAttribute(const std::string & name);
	virtual void			removeAttribute(const std::string & name);
	virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr);
	virtual void			setAttribute(const std::string & name, const std::string & value);
	virtual dom::Attr *		setAttributeNode(dom::Attr * newAttr);

	virtual dom::NamedNodeMap *	getAttributes(void)	{ return &attributes; }
	virtual bool			hasAttributes(void)	{ return attributes.size() > 0; }
};

class ElementDecorator : public virtual dom::Element
{
};

class XMLValidator;
namespace dom
{
	class NodeList;
};

class ElementValidator : public virtual ElementDecorator, public virtual Node_Impl
{
private:
	dom::Element *	parent;
	ValidChildren *	schemaElement;
public:
	ElementValidator(dom::Element * _parent, XMLValidator * xmlValidator);

	//
	// Chain of Responsibility
	//
	virtual void			HandleRequest(std::string & event)		{ parent->HandleRequest(event); }

	//
	// Serialization Data Extraction Strategy
	//
	virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
	  { parent->serialize(writer, whitespace); }

	//
	// Undecorated pass-through methods.
	//
	virtual const std::string &	getAttribute(const std::string & name)		{ return parent->getAttribute(name); }
	virtual dom::Attr *		getAttributeNode(const std::string & name)	{ return parent->getAttributeNode(name); }
	virtual dom::NodeList *		getElementsByTagName(const std::string & tagName)
	  { return parent->getElementsByTagName(tagName); }
	virtual const std::string &	getTagName(void)				{ return parent->getTagName(); }
	virtual bool			hasAttribute(const std::string & name)		{ return parent->hasAttribute(name); }
	virtual void			removeAttribute(const std::string & name)	{ parent->removeAttribute(name); }
	virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr) { return parent->removeAttributeNode(oldAttr); }

	//
	// Decorated Methods
	//
	virtual void			setAttribute(const std::string & name, const std::string & value);
	virtual dom::Attr *		setAttributeNode(dom::Attr * newAttr);
	virtual dom::Node *		insertBefore(dom::Node * newChild, dom::Node * refChild);
	virtual dom::Node *		replaceChild(dom::Node * newChild, dom::Node * oldChild);
	virtual dom::Node *		appendChild(dom::Node * newChild);

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
	virtual dom::NodeList *		getChildNodes(void)				{ return parent->getChildNodes(); }
	virtual dom::Node *		getFirstChild(void)				{ return parent->getFirstChild(); }
	virtual dom::Node *		getLastChild(void)				{ return parent->getLastChild(); }
	virtual dom::Node *		getPreviousSibling(void)			{ return parent->getPreviousSibling(); }
	virtual dom::Node *		getNextSibling(void)				{ return parent->getNextSibling(); }
	virtual dom::Document *		getOwnerDocument(void)				{ return parent->getOwnerDocument(); }
	virtual dom::Node *		removeChild(Node * oldChild)			{ return parent->removeChild(oldChild); }
	virtual bool			hasChildNodes(void)				{ return parent->hasChildNodes(); }
	virtual const std::string &	getLocalName(void)				{ return parent->getLocalName(); }
};

class Director;

class ElementProxy : public virtual dom::Element
{
private:
	dom::Element *	realSubject;
	bool		realized;
	Director *	director;

	void	realize(void);
public:
	ElementProxy(dom::Element * _realSubject, Director * _director) :
	  realSubject(_realSubject),
	  director(_director),
	  realized(false)
	{
	}
	virtual ~ElementProxy() {}

	//
	// Chain of Responsibility
	//
	virtual void			HandleRequest(std::string & event)		{ realSubject->HandleRequest(event); }

	virtual dom::NodeList *		getChildNodes(void);
	virtual dom::Node *		getFirstChild(void);
	virtual dom::Node *		getLastChild(void);
	virtual bool			hasChildNodes(void);

	//
	// Passthrough Element members.
	//
	virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace) {realSubject->serialize(writer, whitespace);}

	virtual const std::string &	getAttribute(const std::string & name)		{ return realSubject->getAttribute(name); }
	virtual dom::Attr *		getAttributeNode(const std::string & name) { return realSubject->getAttributeNode(name); }
	virtual dom::NodeList *		getElementsByTagName(const std::string & tagName)
	  { return realSubject->getElementsByTagName(tagName); }
	virtual const std::string &	getTagName(void)				{ return realSubject->getTagName(); }
	virtual bool			hasAttribute(const std::string & name)		{ return realSubject->hasAttribute(name); }
	virtual void			removeAttribute(const std::string & name)	{ realSubject->removeAttribute(name); }
	virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr) {return realSubject->removeAttributeNode(oldAttr);}
	virtual void			setAttribute(const std::string & name, const std::string & value)
	  { realSubject->setAttribute(name, value); }
	virtual dom::Attr *		setAttributeNode(dom::Attr * newAttr)	{ return realSubject->setAttributeNode(newAttr); }

	virtual dom::NamedNodeMap *	getAttributes(void)				{ return realSubject->getAttributes(); }
	virtual bool			hasAttributes(void)				{ return realSubject->hasAttributes(); }
	virtual const std::string &	getNodeName(void)				{ return realSubject->getNodeName(); }
	virtual const std::string &	getNodeValue(void)				{ return realSubject->getNodeValue(); }
	virtual void			setNodeValue(const std::string & nodeValue)	{ realSubject->setNodeValue(nodeValue); }
	virtual short			getNodeType(void)				{ return realSubject->getNodeType(); }
	virtual dom::Node *		getParentNode(void)				{ return realSubject->getParentNode(); }
	virtual dom::Node *		getPreviousSibling(void)			{ return realSubject->getPreviousSibling();}
	virtual dom::Node *		getNextSibling(void)				{ return realSubject->getNextSibling(); }
	virtual dom::Document *		getOwnerDocument(void)				{ return realSubject->getOwnerDocument(); }
	virtual dom::Node *		removeChild(Node * oldChild)			{return realSubject->removeChild(oldChild);}
	virtual const std::string &	getLocalName(void)				{ return realSubject->getLocalName(); }
};

#endif // ELEMENT_H
