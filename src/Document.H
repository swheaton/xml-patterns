#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <fstream>
#include <stack>

#include "Node.H"
#include "ValidChildren.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;
	class Document_Impl;

	/*class Iterator
	{
	public:
		virtual bool	hasNext()	= 0;
		virtual Node *	next()		= 0;
	};*/

	class Document : public virtual Node
	{
	public:
		Document(void);
		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace);

		virtual Element *	createElement(const std::string & tagName);
		virtual Text *		createTextNode(const std::string & data);
		virtual Attr *		createAttribute(const std::string & name);
		virtual Element *	getDocumentElement();

		//
		// Iterator Factory
		//
		//virtual Iterator *	createIterator(Node * node);
	private:
		Document_Impl* docImpl;
	};

	class Document_Impl : public virtual Node_Impl
	{
		friend class Document;
	public:
		Document_Impl(void);
	
		virtual ~Document_Impl();
	
		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace);
	
		virtual dom::Element *	createElement(const std::string & tagName);
		virtual dom::Text *	createTextNode(const std::string & data);
		virtual dom::Attr *	createAttribute(const std::string & name);
		virtual dom::Element *	getDocumentElement();
	
		//
		// Iterator Factory
		//
		//dom::Iterator *		createIterator(dom::Node * node);
	};
	
	/*class DOMIterator : public virtual dom::Iterator
	{
	private:
		dom::Node *			firstNode;
		std::stack<dom::NodeList *>	listStack;
		std::stack<int>			indexStack;
	
		friend class Document_Impl;
	
		DOMIterator(dom::Node * startWithNode, Document_Impl * document);
		dom::Node * elementAt(dom::NodeList * currentList, int currentIndex);
	public:
		virtual bool		hasNext();
		virtual dom::Node *	next();
	};*/
	
	/*class DocumentDecorator : public virtual dom::Document
	{
	};
	
	class XMLValidator;
	
	class DocumentValidator : public virtual DocumentDecorator, public virtual Node_Impl
	{
	private:
		dom::Document *	parent;
		ValidChildren *	schemaElement;
	public:
		DocumentValidator(dom::Document * _parent, XMLValidator * xmlValidator);
	
		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
		  { parent->serialize(writer, whitespace); }
	
		//
		// Undecorated pass-through methods.
		//
		virtual dom::Element *	createElement(const std::string & tagName)	{ return parent->createElement(tagName); }
		virtual dom::Text *	createTextNode(const std::string & data)	{ return parent->createTextNode(data); }
		virtual dom::Attr *	createAttribute(const std::string & name)	{ return parent->createAttribute(name); }
		virtual dom::Element *	getDocumentElement()				{ return parent->getDocumentElement(); }
	
		//
		// Decorated Methods
		//
		virtual dom::Node *	insertBefore(dom::Node * newChild, dom::Node * refChild);
		virtual dom::Node *	replaceChild(dom::Node * newChild, dom::Node * oldChild);
		virtual dom::Node *	appendChild(dom::Node * newChild);
	
		//
		// Iterator Factory
		//
		dom::Iterator *		createIterator(dom::Node * node)		{ return parent->createIterator(node); }
	};*/
};

#endif // DOCUMENT_H
