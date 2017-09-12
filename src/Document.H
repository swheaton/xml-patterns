#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "Node.H"

namespace dom
{
	class Element;
	class Text;
	class Attr;
	class NodeList;

	class Document : public virtual Node
	{
	public:
		virtual Element *	createElement(const std::string & tagName)	= 0;
		virtual Text *		createTextNode(const std::string & data)	= 0;
		virtual Attr *		createAttribute(const std::string & name)	= 0;
		virtual Element *	createValidatedElement(const std::string & tagName, ValidChildren*)	= 0;
		static virtual Element *	createValidatedDocument(ValidChildren*)	= 0;
		virtual Element *	getDocumentElement()				= 0;
		virtual std::string toString()							= 0;
	};
};

class Document_Impl : public virtual dom::Document, public virtual Node_Impl
{
public:
	Document_Impl(void);

	virtual ~Document_Impl();

	virtual dom::Element *	createElement(const std::string & tagName);
	virtual dom::Text *	createTextNode(const std::string & data);
	virtual dom::Attr *	createAttribute(const std::string & name);
	virtual dom::Element *	createValidatedElement(const std::string & tagName);
	static virtual Element *	createValidatedDocument(ValidChildren*);
	virtual dom::Element *	getDocumentElement();
	virtual std::string toString();
};

class DocumentCreator
{
	virtual Document* createDocument();
}

class DefaultDocumentCreator : public DocumentCreator
{
	virtual Document* createDocument()
	{
		return new Document_Impl;
	}
}

// This class is a Decorator for a document, which allows subclasses to add
//	further functionality on top of Document's appendChild method
class DocumentDecorator : public virtual dom::Document
{
public:
	DocumentDecorator(dom::Document *);
	virtual dom::Node * appendChild(dom::Element * newChild);
	
private:
	dom::Document * decoratedDocument;
};

// This class is a ConcreteDecorator to the DocumentDecorator's AbstractDecorator.
//	It will decorate the Document's appendChild function to throw DOMException if
//	adding the node will not be valid
class ValidationDocumentDecorator : public DocumentDecorator, public virtual Document_Impl
{
	ValidationDocumentDecorator(dom::Document *, XMLValidator*);
	virtual dom::Node * appendChild(dom::Element * newChild);

private:
	XMLValidator* validator;
	// Makes validation exception with description and type
	static dom::DOMException makeValidationException();
};

#endif // DOCUMENT_H
