#ifndef ATTR_H
#define ATTR_H

#include <string>
#include <fstream>

#include "Node.H"

namespace dom
{
	class Document;
	class Element;

	class Attr_Impl;
	class Attr : public virtual Node
	{
	protected:
		Attr(const std::string & tagName, dom::Document * document);
		Attr(const std::string & tagName, const std::string & value, dom::Document * document);
	public:
		friend class Element_Impl;
		friend class Document_Impl;
		virtual ~Attr() {}

		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace);

		virtual const std::string &	getName(void)				;
		virtual const std::string &	getValue(void)				;
		virtual void			setValue(const std::string & value)	;
		virtual Element *		getOwnerElement(void)			;
		
	private:
		Attr_Impl * attrImpl;
	};

	class Attr_Impl : public virtual Node_Impl
	{
	protected:
		Attr_Impl(const std::string & tagName, dom::Document * document);
		Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document);
	public:
		friend class Attr;
	
		virtual ~Attr_Impl();
	
		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace);
	
		virtual const std::string &	getName(void);
		virtual const std::string &	getValue(void);
		virtual void			setValue(const std::string & value);
		virtual dom::Element *		getOwnerElement(void);
	
		//
		// Overridden functions for conforming to Composite Leaf node behavior.
		//
		virtual Node *			insertBefore(Node * newChild, Node * refChild)	{ return 0; }
		virtual Node *			replaceChild(Node * newChild, Node * oldChild)	{ return 0; }
		virtual Node *			removeChild(Node * oldChild)			{ return 0; }
		virtual Node *			appendChild(Node * newChild)			{ return 0; }
	};
};

#endif // ATTR_H
