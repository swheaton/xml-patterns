#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "Node.H"
#include "NamedNodeMap.H"

namespace dom
{
	class Attr;
	class NodeList;
	class Document;
	class Text;

	class Element : public virtual Node
	{
	public:
		virtual ~Element() {}

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
		virtual std::string toString()										= 0;
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
	virtual std::string toString();
};

// This class is a Decorator for an Element, which allows subclasses to add
//	further functionality on top of Element's modification functions
class ElementDecorator : public virtual dom::Element
{
public:
	ElementDecorator(dom::Element *);
	virtual dom::Node * appendChild(dom::Element * newChild);
	virtual dom::Node * appendChild(dom::Text * newChild);
	virtual void setAttribute(const std::string & name, const std::string & value);
	virtual void setAttributeNode(dom::Attr * newAttr);

private:
	dom::Element * decoratedElement;
};

// This class is a ConcreteDecorator to the ElementDecorator.
//	It will decorate the Element's modifications functions to throw DOMException if
//	adding the node or attribute is not valid
class ValidationElementDecorator : public ElementDecorator, public virtual Element_Impl
{
public:
	ValidationElementDecorator(dom::Element *, XMLValidator*);
	virtual dom::Node * appendChild(dom::Element * newChild);
	virtual dom::Node * appendChild(dom::Text * newChild);
	virtual void setAttribute(const std::string & name, const std::string & value);
	virtual void setAttributeNode(dom::Attr * newAttr);

	
private:
	XMLValidator validator;
	// Makes validation exception with description and type
	static dom::DOMException makeValidationException();
};

#endif // ELEMENT_H
